/*
 * (C) Radim Kolar 1997-2004
 * This is free software, see GNU Public License version 2 for
 * details.
 *
 * Simple forking WWW Server benchmark:
 *
 * Usage:
 *   webbench --help
 *
 * Return codes:
 *    0 - sucess
 *    1 - benchmark failed (server is not on-line)
 *    2 - bad param
 *    3 - internal error, fork failed
 * 
 */ 
#include "socket.c"
#include <unistd.h>
#include <sys/param.h>
#include <rpc/types.h>
#include <getopt.h>
#include <strings.h>
#include <time.h>
#include <signal.h>

/* values */
volatile int timerexpired=0;
int speed=0;
int failed=0;
int bytes=0;
/* globals */
int http10=1; /* 0 - http/0.9, 1 - http/1.0, 2 - http/1.1 */
/* Allow: GET, HEAD, OPTIONS, TRACE */
#define METHOD_GET 0
#define METHOD_HEAD 1
#define METHOD_OPTIONS 2
#define METHOD_TRACE 3
#define PROGRAM_VERSION "1.5"
int method=METHOD_GET;
int clients=1;
int force=0;
int force_reload=0;
int proxyport=80;
char *proxyhost=NULL;
int benchtime=30;
/* internal */
int mypipe[2];
char host[MAXHOSTNAMELEN];
#define REQUEST_SIZE 2048
char request[REQUEST_SIZE];

static const struct option long_options[]=    //����ṹ����getopt_long�ĵ��ĸ�������
{                                             //����ָ����ѡ������ƺͷ���״̬
 {"force",no_argument,&force,1},              //ָ������������ѡ���޲�������1����force����
 {"reload",no_argument,&force_reload,1},
 {"time",required_argument,NULL,'t'},         //�в������Ͷ�ѡ��-tһ�������Ѳ�����optarg�з���
 {"help",no_argument,NULL,'?'},               //�޲������Ͷ�ѡ��-?һ��
 {"http09",no_argument,NULL,'9'},
 {"http10",no_argument,NULL,'1'},
 {"http11",no_argument,NULL,'2'},
 {"get",no_argument,&method,METHOD_GET},
 {"head",no_argument,&method,METHOD_HEAD},
 {"options",no_argument,&method,METHOD_OPTIONS},
 {"trace",no_argument,&method,METHOD_TRACE},
 {"version",no_argument,NULL,'V'},
 {"proxy",required_argument,NULL,'p'},
 {"clients",required_argument,NULL,'c'},
 {NULL,0,NULL,0}
};

/* prototypes */
static void benchcore(const char* host,const int port, const char *request);
static int bench(void);
static void build_request(const char *url);

static void alarm_handler(int signal)
{
   timerexpired=1;
}	

static void usage(void)
{
   fprintf(stderr,
	"webbench [option]... URL\n"
	"  -f|--force               Don't wait for reply from server.\n"
	"  -r|--reload              Send reload request - Pragma: no-cache.\n"
	"  -t|--time <sec>          Run benchmark for <sec> seconds. Default 30.\n"
	"  -p|--proxy <server:port> Use proxy server for request.\n"
	"  -c|--clients <n>         Run <n> HTTP clients at once. Default one.\n"
	"  -9|--http09              Use HTTP/0.9 style requests.\n"
	"  -1|--http10              Use HTTP/1.0 protocol.\n"
	"  -2|--http11              Use HTTP/1.1 protocol.\n"
	"  --get                    Use GET request method.\n"
	"  --head                   Use HEAD request method.\n"
	"  --options                Use OPTIONS request method.\n"
	"  --trace                  Use TRACE request method.\n"
	"  -?|-h|--help             This information.\n"
	"  -V|--version             Display program version.\n"
	);
};
int main(int argc, char *argv[])  //����������������￪ʼ
{
 int opt=0;
 int options_index=0;     //����getopt_long�������һ������Ϊ0
 char *tmp=NULL;          //����ѡ��p����Ĳ����������ݴ����
 if(argc==1)              //���ն�ֻ�����������û��ѡ����߲���ʱ��������ӡ����ʹ�÷��������ҷ���2
 {
	  usage();
          return 2;
 } 

/*
getopt_long������һ���������������в����ĺ�����ԭ����
int getopt_long(int argc, char * const argv[],
const char *optstring,
const struct option *longopts, int *longindex);
argc��argv��main������������
����������optstring�Ƕ���ѡ����ַ������в�ѡ������������
���ĸ�������ʵ��һ���ṹ�壬���˵����ο����棬���������longindex��һ��0ֵ��int�ͱ����ĵ�ַ��
*/
 while((opt=getopt_long(argc,argv,"912Vfrt:p:c:?h",long_options,&options_index))!=EOF )
 {
  switch(opt)
  {
   case  0 : break;
   case 'f': force=1;break;
   case 'r': force_reload=1;break; 
   case '9': http10=0;break;
   case '1': http10=1;break;
   case '2': http10=2;break;
   case 'V': printf(PROGRAM_VERSION"\n");exit(0);
   case 't': benchtime=atoi(optarg);break;	      //���ò���ʱ�䣬ͨ��optarg���أ������ַ���תΪ���Σ�����benchtime
   case 'p':                                      //Ȼ��atoi�������ַ�����ת��Ϊint�ͣ����ת��ʧ�ܣ�atoiֱ�ӷ���0
	     /* proxy server parsing server:port */
	     tmp=strrchr(optarg,':');                   //�Ѵ���������ӡ�������ʼ��ȡ���ݴ浽tmp������
	     proxyhost=optarg;                          //�Ѵ���������������ַ�������proxyhost������
	     if(tmp==NULL)                              //���tmp�����ǿյģ�˵��ûָ���˿ںţ�
	     {                                          //ִ�����������optarg���ַ�������proxyhost�������ֱ��break
		     break;
	     }
	     if(tmp==optarg)                            //���optarg����ֻ�С���8099��֮����ַ�������˵��ȱ�ٴ����������
	     {                                          //��ӡ������Ϣ��main����2���˳���
		     fprintf(stderr,"Error in option --proxy %s: Missing hostname.\n",optarg);
		     return 2;
	     }
	     if(tmp==optarg+strlen(optarg)-1)           //���-p������һ�����ơ�192.168.1.1:���Ĵ��������������ȱ�ٶ˿ں���
	     {                                          //����tmp��һ���ַ����ĵ�ַ��ָ�򡰣�������optarg+strlen(optarg)-1��
	     	                                          //��optarg�ĵ�ַ���ϳ��ȼ�1��Ҳ���Ǹպ��ǡ������ĵ�ַ��
		     fprintf(stderr,"Error in option --proxy %s Port number is missing.\n",optarg);
		     return 2;
	     }
	     *tmp='\0';                                 //tmpָ��ĵط��պ��ǡ����������Ը��ϡ�\0��������proxyport����tmp+1���ַ�����
	     proxyport=atoi(tmp+1);break;               //���ַ���ת������κ󣬶���proxyport
   case ':':
   case 'h':
   case '?': usage();return 2;break;              //ѡ�����Ϊ���������Ϣ
   case 'c': clients=atoi(optarg);break;          //�趨�������Կͻ��˵�������ͨ��optarg���ز����������ַ���תΪ���Σ�����clients
  }
 }
 
 if(optind==argc) {                               //�����棿������һ�������ֻ�г���������ӡ���������Ϣ
                      fprintf(stderr,"webbench: Missing URL!\n");
		      usage();
		      return 2;
                    }

 if(clients==0) clients=1;                        //����ͻ�������=0��������Ϊ1
 if(benchtime==0) benchtime=60;                   //�������ʱ��=0s��������Ϊ60s
 /* Copyright */
 fprintf(stderr,"Webbench - Simple Web Benchmark "PROGRAM_VERSION"\n"
	 "Copyright (c) Radim Kolar 1997-2004, GPL Open Source Software.\n"
	 );
 build_request(argv[optind]);                     //����Ҫ���Եķ������ĵ�ַ����request���н���
 /* print bench info */
 printf("\nBenchmarking: ");
 switch(method)                                   //��ʾmethod������
 {
	 case METHOD_GET:
	 default:
		 printf("GET");break;
	 case METHOD_OPTIONS:
		 printf("OPTIONS");break;
	 case METHOD_HEAD:
		 printf("HEAD");break;
	 case METHOD_TRACE:
		 printf("TRACE");break;
 }
 printf(" %s",argv[optind]);                      //��ʾ��������ַ
 switch(http10)                                   //��ʾʹ�õ�Э��
 {
	 case 0: printf(" (using HTTP/0.9)");break;
	 case 2: printf(" (using HTTP/1.1)");break;
 }
 printf("\n");
 if(clients==1) printf("1 client");               //��ʾ׼���ö��ٸ������ͻ��˽��в���
 else
   printf("%d clients",clients);

 printf(", running %d sec", benchtime);           //��ʾ����ʱ��
 if(force) printf(", early socket close");        //���force��1�����ȴ�������ʾsocket�ر�
 if(proxyhost!=NULL) printf(", via proxy server %s:%d",proxyhost,proxyport);//��ʾ�����������ַ
 if(force_reload) printf(", forcing reload");     //������·����������ӡ��Ϣ
 printf(".\n");
 return bench();                                  //ִ�в��Ժ����������ز��Խ��
}

void build_request(const char *url)               //�ú�����Ҫ�Ƕ�Ҫ���Եķ�������ַ���н���
{                                                 //��Ȼ�������ַ�������������ֻ�����IP��ַ
  char tmp[10];
  int i;

  bzero(host,MAXHOSTNAMELEN);                     //��0���host��request����
  bzero(request,REQUEST_SIZE);

  if(force_reload && proxyhost!=NULL && http10<1) http10=1;  
  if(method==METHOD_HEAD && http10<1) http10=1;
  if(method==METHOD_OPTIONS && http10<2) http10=2;
  if(method==METHOD_TRACE && http10<2) http10=2;

  switch(method)
  {
	  default:
	  case METHOD_GET: strcpy(request,"GET");break;    //ǰ��ͨ��ѡ������޸���method�����ڰ�method����request����������
	  case METHOD_HEAD: strcpy(request,"HEAD");break;
	  case METHOD_OPTIONS: strcpy(request,"OPTIONS");break;
	  case METHOD_TRACE: strcpy(request,"TRACE");break;
  }
		  
  strcat(request," ");                              //��request�е�method��������һ���ո��

  if(NULL==strstr(url,"://"))                       //�жϵ�ַ�Ƿ���://�ַ��������û������һ�������ĵ�ַ����ʾ�����˳�
  {
	  fprintf(stderr, "\n%s: is not a valid URL.\n",url);
	  exit(2);
  }
  if(strlen(url)>1500)                              //�������Ϊɶ�趨Ϊ1500�����������ܳ���255���ַ������ԣ�
  {
         fprintf(stderr,"URL is too long.\n");
	 exit(2);
  }
  if(proxyhost==NULL)                               //�ڴ��������Ϊ�յ������
	   if (0!=strncasecmp("http://",url,7))           //��Ȼ��://�������Э�鲻��http,�����������Ϣ���˳�
	   { fprintf(stderr,"\nOnly HTTP protocol is directly supported, set --proxy for others.\n");
             exit(2);
           }
  /* protocol/host delimiter */                     //delimiter�Ƿֽ������˼
  i=strstr(url,"://")-url+3;                        //strstr�Ƿ���һ���ַ�����Ŀ���ַ����еĳ���λ�ã����û�򷵻�NULL
  /* printf("%d\n",i); */                           //�����i���ǲ��Ե�ַ��Э��ռ����λ�������http://����i=7

  if(strchr(url+i,'/')==NULL) {                     //�����Ե�ַ����ǲ����ԡ�/����β��������ǣ��������ʾ��Ϣ���˳�
                                fprintf(stderr,"\nInvalid URL syntax - hostname don't ends with '/'.\n");
                                exit(2);
                              }
  if(proxyhost==NULL)                               //��������������ַΪ��
  {
   /* get port from hostname */
   if(index(url+i,':')!=NULL &&
      index(url+i,':')<index(url+i,'/'))
   {
	   strncpy(host,url+i,strchr(url+i,':')-url-i);
	   bzero(tmp,10);
	   strncpy(tmp,index(url+i,':')+1,strchr(url+i,'/')-index(url+i,':')-1);
	   /* printf("tmp=%s\n",tmp); */
	   proxyport=atoi(tmp);
	   if(proxyport==0) proxyport=80;
   } else
   {
     strncpy(host,url+i,strcspn(url+i,"/"));
   }
   // printf("Host=%s\n",host);
   strcat(request+strlen(request),url+i+strcspn(url+i,"/"));
  } else
  {
   // printf("ProxyHost=%s\nProxyPort=%d\n",proxyhost,proxyport);
   strcat(request,url);
  }
  if(http10==1)
	  strcat(request," HTTP/1.0");
  else if (http10==2)
	  strcat(request," HTTP/1.1");
  strcat(request,"\r\n");
  if(http10>0)
	  strcat(request,"User-Agent: WebBench "PROGRAM_VERSION"\r\n");
  if(proxyhost==NULL && http10>0)
  {
	  strcat(request,"Host: ");
	  strcat(request,host);
	  strcat(request,"\r\n");
  }
  if(force_reload && proxyhost!=NULL)
  {
	  strcat(request,"Pragma: no-cache\r\n");
  }
  if(http10>1)
	  strcat(request,"Connection: close\r\n");
  /* add empty line at end */
  if(http10>0) strcat(request,"\r\n"); 
  // printf("Req=%s\n",request);
}

/* vraci system rc error kod */
static int bench(void)
{
  int i,j,k;	
  pid_t pid=0;
  FILE *f;

  /* check avaibility of target server */
  i=Socket(proxyhost==NULL?host:proxyhost,proxyport);
  if(i<0) { 
	   fprintf(stderr,"\nConnect to server failed. Aborting benchmark.\n");
           return 1;
         }
  close(i);
  /* create pipe */
  if(pipe(mypipe))
  {
	  perror("pipe failed.");
	  return 3;
  }

  /* not needed, since we have alarm() in childrens */
  /* wait 4 next system clock tick */
  /*
  cas=time(NULL);
  while(time(NULL)==cas)
        sched_yield();
  */

  /* fork childs */
  for(i=0;i<clients;i++)
  {
	   pid=fork();
	   if(pid <= (pid_t) 0)
	   {
		   /* child process or error*/
	           sleep(1); /* make childs faster */
		   break;
	   }
  }

  if( pid< (pid_t) 0)
  {
          fprintf(stderr,"problems forking worker no. %d\n",i);
	  perror("fork failed.");
	  return 3;
  }

  if(pid== (pid_t) 0)
  {
    /* I am a child */
    if(proxyhost==NULL)
      benchcore(host,proxyport,request);
         else
      benchcore(proxyhost,proxyport,request);

         /* write results to pipe */
	 f=fdopen(mypipe[1],"w");
	 if(f==NULL)
	 {
		 perror("open pipe for writing failed.");
		 return 3;
	 }
	 /* fprintf(stderr,"Child - %d %d\n",speed,failed); */
	 fprintf(f,"%d %d %d\n",speed,failed,bytes);
	 fclose(f);
	 return 0;
  } else
  {
	  f=fdopen(mypipe[0],"r");
	  if(f==NULL) 
	  {
		  perror("open pipe for reading failed.");
		  return 3;
	  }
	  setvbuf(f,NULL,_IONBF,0);
	  speed=0;
          failed=0;
          bytes=0;

	  while(1)
	  {
		  pid=fscanf(f,"%d %d %d",&i,&j,&k);
		  if(pid<2)
                  {
                       fprintf(stderr,"Some of our childrens died.\n");
                       break;
                  }
		  speed+=i;
		  failed+=j;
		  bytes+=k;
		  /* fprintf(stderr,"*Knock* %d %d read=%d\n",speed,failed,pid); */
		  if(--clients==0) break;
	  }
	  fclose(f);

  printf("\nSpeed=%d pages/min, %d bytes/sec.\nRequests: %d susceed, %d failed.\n",
		  (int)((speed+failed)/(benchtime/60.0f)),
		  (int)(bytes/(float)benchtime),
		  speed,
		  failed);
  }
  return i;
}

void benchcore(const char *host,const int port,const char *req)
{
 int rlen;
 char buf[1500];
 int s,i;
 struct sigaction sa;

 /* setup alarm signal handler */
 sa.sa_handler=alarm_handler;
 sa.sa_flags=0;
 if(sigaction(SIGALRM,&sa,NULL))
    exit(3);
 alarm(benchtime);

 rlen=strlen(req);
 nexttry:while(1)
 {
    if(timerexpired)
    {
       if(failed>0)
       {
          /* fprintf(stderr,"Correcting failed by signal\n"); */
          failed--;
       }
       return;
    }
    s=Socket(host,port);                          
    if(s<0) { failed++;continue;} 
    if(rlen!=write(s,req,rlen)) {failed++;close(s);continue;}
    if(http10==0) 
	    if(shutdown(s,1)) { failed++;close(s);continue;}
    if(force==0) 
    {
            /* read all available data from socket */
	    while(1)
	    {
              if(timerexpired) break; 
	      i=read(s,buf,1500);
              /* fprintf(stderr,"%d\n",i); */
	      if(i<0) 
              { 
                 failed++;
                 close(s);
                 goto nexttry;
              }
	       else
		       if(i==0) break;
		       else
			       bytes+=i;
	    }
    }
    if(close(s)) {failed++;continue;}
    speed++;
 }
}
