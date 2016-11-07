#include "network.h"
int main(int argc, char*argv[])
{
    int mode = validateInput(argc,argv[1],argv[2]);

    if(mode == SERVER_MODE){
        startServerMode((argv[2]));
    }else if(mode==CLIENT_MODE){
        startClientMode((argv[2]));
    }else{
        printf("Wrong set of Inputs, \n Valid input type: ./executable (s/c) PORT number\n");
    }
}
