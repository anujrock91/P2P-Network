#ifndef __network_h
#define __network_h

/*
    Keep all the essential things that you will use regularly.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <netdb.h>


#define SERVER_MODE 1
#define CLIENT_MODE 2
#define WRONG_INPUT -999

#endif // __network_h
