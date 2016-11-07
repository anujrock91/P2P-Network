#include "network.h"

int validateInput(int argc, char *argv1, char *argv2){

    //First check if the number of arguments is valid
    if(argc!=3){
        return WRONG_INPUT;
    }
    //Second check the port validations (must be >1024)

    int port = atoi(argv2);

    if(port<=1024){
        printf("Port number <= 1024 cannot be accepted");
        return WRONG_INPUT;
    }

    if(strcmp(argv1,"s")==0){
        return SERVER_MODE;
    }
    else if(strcmp(argv1,"c")==0){
        return CLIENT_MODE;
    }else{
        return WRONG_INPUT;
    }
}



char *GetIP(char *ServerName)
{


        struct addrinfo hints, *res, *returnPointer;
        int status;
        char ipstring[INET6_ADDRSTRLEN];
        static char a[100];
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if ((status = getaddrinfo(ServerName, NULL, &hints, &res)) != 0)
            {
              fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
            }

        for(returnPointer = res;returnPointer != NULL; returnPointer = returnPointer->ai_next)
            {

              void *logicaladdress;
              struct sockaddr_in *ipv4 = (struct sockaddr_in *)returnPointer->ai_addr;
              logicaladdress = &(ipv4->sin_addr);
              inet_ntop(returnPointer->ai_family, logicaladdress, ipstring, sizeof ipstring);
            }
        freeaddrinfo(res);
        strcpy(a,ipstring);
        return a;

}



char * strSeperate(char *originalString, int ElementPos)
{
    int n;
    char *str;
    char exp[3000];
    str=originalString;
    strcpy(exp,str);
    char * pch;
    char * var1;
    static char a[3000];
    n=ElementPos;

    pch = strtok (exp," ,.-");
    if(n == 1)
    {
        var1 = pch;
    }
    else if(n == 2)
    {
        pch = strtok (NULL, " ");
        var1 = pch;
    }
    else if(n == 3)
    {
        pch = strtok (NULL, " ");
        pch = strtok (NULL, " ");
        var1 = pch;
    }
    else
    {
        printf("Only three inputs are allowed");
    }

    strcpy(a,var1);
    return a;
}




int validateIpOrName(char *IPorName)
{
    if(*IPorName>=97)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}


void startServerMode(char *PortNumber)
{
    char i[20];
    strcpy(i,PortNumber);
    MainServerFunction(i);
}


void startClientMode(char *PortNumber)
{
    char i[20];
    strcpy(i,PortNumber);
    MainClientFunction(i);
}


int Help()
{
    puts("DISPLAY");
    puts("REGISTER<ServerIP> <PortNumber>");
    puts("CONNECT <destination> <port no>");
    puts("LIST");
    puts("TERMINATE");
    puts("PUT<connection id> <file name>");
    puts("SYNC");
    puts("HELP");
    return 1;
}


char * StringAddressGen(char *ServerName, char *IPAddress, char *PortNumber)
{
    char a[200];
    char b[100];
    char c[100];
    static char d[200];

    strcpy(a,ServerName);
    strcpy(b,IPAddress);
    strcpy(c,PortNumber);
    strcat(a," ");
    strcat(a,b);
    strcat(a," ");
    strcat(a,c);
    strcpy(d,a);

    return d;
}

char * TwoStringCombine(char *str1, char *str2)
{
    char a[200];
    char b[100];
    static char d[200];
    strcpy(a,str1);
    strcpy(b,str2);
    strcat(a," ");
    strcat(a,b);
    strcpy(d,a);

    return d;
}


char *IntToString(int a)
{
    int c;
    c=a;
    static char d[100];
    int len = snprintf(NULL,0,"%d",c);
    char *b = malloc(len+1);
    snprintf(b,len+1,"%d",c);
    strcpy(d,b);
    return d;
}


int wordCount(char *a)
{
    char str1[200];
    static int count;
    count = 0;
    int l;
    strcpy(str1,a);
    for (l = 0;str1[l] != '\0';l++)
    {
        if (str1[l] == ' ')
            count++;
    }
    return (count+1);
}

