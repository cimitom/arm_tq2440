#include <stdio.h>
#include <string.h>
#include <getopt.h>
static void usage()
{
    fprintf(stderr,
    "  it must be to parameter\n"
    "  -s|--str_name    the string be check\n"
    "  -c|--chr         the char to check\n"
    );
}

static const struct option long_options[] =
{
    {"str_name",required_argument,NULL,'s'},
    {"chr",required_argument,NULL,'c'},
    {NULL,0,NULL,0}
};

int main(int argc, char ** argv)
{
    int opt = 0;
    char str[20];
    char chr = 0;
    char *pChar = NULL;
    if( argc == 1)
    {
        usage();
        return 2;
    }
    
    while((opt = getopt_long(argc, argv, "s:c:",long_options,0)) != EOF)
    {
        switch(opt)
        {
            case 0:
                break;
            case 's':
                memcpy(str,optarg,strlen(optarg)+1);
                break;
            case 'c':
                chr = optarg[0];
                break;
        }
    }
    pChar = strrchr(str,chr);
    if(pChar == NULL)
    {
        printf("sorry, can not find the char\n");
    }
    else
    {
        printf("Good, the character %c position is %s\n",chr,pChar);
    }
    return 0;
}
