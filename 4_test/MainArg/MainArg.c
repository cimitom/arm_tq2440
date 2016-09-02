#include <stdio.h>
#include <getopt.h>

static void usage()
{
    fprintf(stderr,
    "-n|--name        get my name\n"
    "-b|--birthday    get my birthday\n"
    "-w|--weather     set today weather,and print\n"
    );
}

static const struct option long_options[]=
{
    {"name",no_argument,NULL,'n'},
    {"birthday",no_argument,NULL,'b'},
    {"weather",required_argument,NULL,'w'},
    {NULL,0,NULL,0}
};

int main(int argc, char ** argv)
{
    int opt = 0;
    int argc_no = 0;
    if(argc == 1)
    {
        usage();
        return 2;
    }
    while((opt=getopt_long(argc, argv, "nbw:",long_options,0))!=EOF)
    {
        switch(opt)
        {
            case 'n':
                printf("My name is Elvin\n");break;
            case 'b':
                printf("My birthday is 1985.11.22\n");break;
            case 'w':
                printf("Today's weather is %s\n",optarg);break;
        }
    }
    return 0;
}
