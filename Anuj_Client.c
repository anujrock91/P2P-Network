#include "network.h"

struct ClientConnections
{
    int ClientCount;
    char ClientConnName[1000];
    char ClientConnIP[200];
    char ClientConnPort[100];
    int sd;
    int flag;
};

void MainClientFunction(char *port)
{

        struct ClientConnections ClientConnectionsObject[10];
        int ClientConnectionsObjectLoop;
        char NullifyClientConnectionObjectDetails[] = " ";
        int ClientConnectionCount;
        int ClientSocketSender1;
        int ClientSocketSender2;
        int ClientSocketSender3;
        int ClientSocketRec;
        int ClientSocketServer;
        struct sockaddr_in ClientListner;
        struct sockaddr_in RemoteServerAddress;
        struct sockaddr_in PeerAddress1;
        struct sockaddr_in PeerAddress2;
        struct sockaddr_in PeerAddress3;
        struct sockaddr_in PeerAddressAccept;
        int PeerAddressLenAccept;
        int ClientConnect;
        int peerConnect1;
        int peerConnect2;
        int peerConnect3;
        char ClientName[100];
        int ClientPortNumber;
        int ClientAddressLength;
        int BindVarClient;
        int ClientSocketDescriptor[15];
        int MaxDescriptor;
        int ClientSocketDescriptorLoop;
        int ClientSocketRecAct;
        char ClientBufferStdin[150];
        char ClientPeerBuffer[5000];
        int ClientPeerBufferReadVal;
        fd_set socketfd;
        int NewSocketDes;
        int REGISTER;
        int GETFileReadVal;
        REGISTER = 0;
        //Getting the client name
        char ClientOriginalName[150];
        gethostname(ClientOriginalName, sizeof(ClientOriginalName));
        //char *ClientAddressStringPointer;
        //char ClientAddressString[500];

        //newly added
        struct sockaddr_storage addrAccept;
        char PeerIPAccept[INET6_ADDRSTRLEN];
        socklen_t PeerAddrLengthAccept;
        PeerAddrLengthAccept = sizeof(addrAccept);
        //Newly Added Finish

        //Getting the IP from name START
        char ClientIP[100];
        char *RecIP;
        RecIP = GetIP(ClientOriginalName);
        strcpy(ClientIP,RecIP);

        //Getting the port number
        ClientPortNumber = atoi(port);

        //Creating Client Listener Socket
        ClientListner.sin_family = AF_INET;
        inet_pton(AF_INET, ClientIP, &(ClientListner.sin_addr));
        ClientListner.sin_port = htons(ClientPortNumber);
        bzero(ClientListner.sin_zero,8);
        ClientAddressLength = sizeof(ClientListner);

        ClientSocketRec = socket(AF_INET , SOCK_STREAM , 0);
        if(ClientSocketRec < 0)
        {
        puts("Error creating Client LISTENER Socket...");
        }
        BindVarClient = bind(ClientSocketRec, (struct sockaddr *)&ClientListner, sizeof(ClientListner));
        if(BindVarClient < 0)
        {
        puts("Error Binding Client listener...");
        }
        if((listen(ClientSocketRec, 3)) < 0)
        {
        puts("Error in Listening Method...");
        }


        ClientSocketDescriptor[0] = stdin;
        ClientSocketDescriptor[1] = ClientSocketRec;
        //Setting the client Socket Descriptor Loop
        for(ClientSocketDescriptorLoop = 2; ClientSocketDescriptorLoop<15;ClientSocketDescriptorLoop++)
        {
            ClientSocketDescriptor[ClientSocketDescriptorLoop] = 0;
        }


        //Setting the Client Connection Structure Count to 0
        for(ClientConnectionsObjectLoop = 0; ClientConnectionsObjectLoop<10;ClientConnectionsObjectLoop++)
        {
            ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount = 0;
            strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnName,NullifyClientConnectionObjectDetails);
            strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnPort,NullifyClientConnectionObjectDetails);
            strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnIP,NullifyClientConnectionObjectDetails);
            ClientConnectionsObject[ClientConnectionsObjectLoop].sd = 0;
            ClientConnectionsObject[ClientConnectionsObjectLoop].flag = 0;
        }
        ClientConnectionCount = 0;
        //Running the infinite Loop
        puts("Successfully Entered Application");
        while(1)
        {
            ClientConnectionCount = 0;
            memset(ClientPeerBuffer, 0 , sizeof(ClientPeerBuffer));
            //Setting the sockets in select API
            FD_ZERO(&socketfd);
            FD_SET(0,&socketfd);
            FD_SET(ClientSocketDescriptor[1],&socketfd);
            if(0>ClientSocketDescriptor[1])
            {
            MaxDescriptor = 0;
            }
            else
            {
            MaxDescriptor = ClientSocketDescriptor[1];
            }


            //Setting up all the other sockets in select API which are non zero
            for(ClientSocketDescriptorLoop = 2; ClientSocketDescriptorLoop<15;ClientSocketDescriptorLoop++)
            {
                if(ClientSocketDescriptor[ClientSocketDescriptorLoop] !=0)
                {
                    FD_SET(ClientSocketDescriptor[ClientSocketDescriptorLoop],&socketfd);
                    if(ClientSocketDescriptor[ClientSocketDescriptorLoop]>MaxDescriptor)
                    {
                        MaxDescriptor = ClientSocketDescriptor[ClientSocketDescriptorLoop];
                    }
                }
            }

            //Checking The Activity At Every Socket In The Set Of Sockets To Be Analyzed
            ClientSocketRecAct = select( MaxDescriptor + 1 , &socketfd , NULL , NULL , NULL);
            if ((ClientSocketRecAct < 0) && (errno!=EINTR))
            {
                puts("select Error...");
            }

            //Checking the standard input output Socket
            if(FD_ISSET(0,&socketfd))
            {
                char a[150];
                char *RegisterPointer;
                char *PortPointer;
                char *TimberEnteredIP;
                char SplitStringPort[100];
                int ServerPort;
                char SplitString1[100];
                char TimberIPFinal[50];
                char *ConnectPointer;
                char SplitString2[100];
                char *IPPointer;
                char *PeerPortPointer;
                char IPPeer[100];
                char *TerminatePointer;
                char SplitString3[100];
                int IsIPorName;
                char *ObtainIPorName;
                char *GETPointer;
                char SplitString4[100];
                char *GETIDPointer;
                char GETID[10];
                char *GETFileNamePointer;
                char GETFileName[100];
                int connectFlag;
                char *PUTPointer;
                char SplitString5[200];
                char *PUTIDPointer;
                char PUTID[20];
                char *PUTFileNamePointer;
                char PUTFileName[500];

                gets(ClientBufferStdin);
                strcpy(a,ClientBufferStdin);
                char Timbername[] = "timberlake.cse.buffalo.edu";
                char *TimberIP;
                if(strcmp(a,"HELP") == 0)
                {
                    int i;
                    i = Help();
                }
                if(strcmp(a,"DISPLAY") == 0)
                {
                    printf("ProcessIP: %s \n", RecIP);
                    printf("Listening port: %d \n", ClientPortNumber);
                }

                //COMMAND REGISTER

                RegisterPointer = strSeperate(a,1);
                strcpy(SplitString1,RegisterPointer);
                if(strcmp(SplitString1,"REGISTER") == 0)
                {
                    int NumberOfTermsRegister;
                    NumberOfTermsRegister = 0;
                    NumberOfTermsRegister = wordCount(a);
                    if(NumberOfTermsRegister == 3)
                       {
                    PortPointer = strSeperate(a,3);
                    strcpy(SplitStringPort,PortPointer);
                    ServerPort = atoi(SplitStringPort);

                    TimberIP = GetIP(Timbername);
                    strcpy(TimberIPFinal,TimberIP);
                    TimberEnteredIP = strSeperate(a,2);

                    if(strcmp(TimberIPFinal,TimberEnteredIP) == 0)
                    {

                    //Creating Server Address
                    RemoteServerAddress.sin_family = AF_INET;
                    inet_pton(AF_INET, TimberIPFinal, &(RemoteServerAddress.sin_addr));
                    RemoteServerAddress.sin_port = htons(ServerPort);
                    bzero(RemoteServerAddress.sin_zero,8);
                    //Creating Server Socket
                    ClientSocketServer = socket(AF_INET , SOCK_STREAM , 0);
                    if(ClientSocketServer < 0)
                    {
                        puts("Error Creating Client SERVER Socket");
                    }
                    //Connecting Server
                    ClientConnect = connect(ClientSocketServer, (struct sockaddr *)&RemoteServerAddress, sizeof(RemoteServerAddress));
                        if(ClientConnect < 0)
                        {
                            puts("Error Connecting Server...");
                        }
                        else
                        {
                            puts("Connected to SERVER");
                            //Sending the client port
                            char ClientMSG[1000]= {0};
                            sprintf(ClientMSG,"%s",port);
                            int bytesRead;
                            if((bytesRead = send(ClientSocketServer,ClientMSG,sizeof(ClientMSG),0)) == -1)
                                {
                                    printf("Error Adding to network \n");
                                }
                            else {printf("Added to Network WELCOME\n");}
                            //Adding the connection details in Client Structure
                            ClientConnectionsObject[0].ClientCount = 1;
                            strcpy(ClientConnectionsObject[0].ClientConnIP,TimberIPFinal);
                            strcpy(ClientConnectionsObject[0].ClientConnPort,SplitStringPort);
                            ClientConnectionsObject[0].sd = ClientSocketServer;
                            strcpy(ClientConnectionsObject[0].ClientConnName,"timberlake.cse.buffalo.edu");
                            ClientConnectionsObject[0].flag = 0;
                            ClientSocketDescriptor[2] = ClientSocketServer;
                            REGISTER = 1;
                        }
                    }

                    else
                    {
                    printf("The Server IP is : %s \n",TimberIPFinal);
                    }
                }
                else{puts("See the correct format for REGISTER");}
                }

              //COMMAND LIST
                if(strcmp(a,"LIST") == 0)
                {
                    if(REGISTER != 0)
                    {
                    char ListClientMSG[2000]= {0};
                    sprintf(ListClientMSG,"%s",a);
                    int ListBytesRead;
                    if((ListBytesRead = send(ClientSocketServer,ListClientMSG,sizeof(ListClientMSG),0)) == -1)
                    {
                        puts("Server list request failed");
                    }
                    else
                    {
                        char LISTClientList[3000];
                        memset(LISTClientList,0,sizeof(LISTClientList));
                        int LISTServerSentList;
                        if((LISTServerSentList = recv(ClientSocketServer,LISTClientList,sizeof(LISTClientList),0)!=0))
                           {
                               LISTClientList[strlen(LISTClientList)] = '\0';
                               puts("THE SERVER LIST: ");
                               puts(LISTClientList);
                           }

                    }
                    }
                        printf(" \n ");
                        printf("YOUR CONNECTIONS LIST:\n");
                        for(ClientConnectionsObjectLoop = 0;ClientConnectionsObjectLoop<10;ClientConnectionsObjectLoop++)
                        {
                            if(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount != 0)
                            {
                               printf(" %d  %s  %s  %s \n", ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount,ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnName,ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnIP,ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnPort);
                            }

                        }
                }

               //CONNECT COMMAND
                ConnectPointer = strSeperate(a,1);
                strcpy(SplitString2,ConnectPointer);
                if(strcmp(SplitString2,"CONNECT") == 0)
                {
                    if(REGISTER != 0)
                    {
                    int NumberOfTermsConnect;
                    NumberOfTermsConnect = 0;
                    NumberOfTermsConnect = wordCount(a);
                    if(NumberOfTermsConnect == 3)
                      {

                    IPPointer = strSeperate(a,2);
                    IsIPorName = validateIpOrName(IPPointer);
                    if (IsIPorName == 1)
                    {
                        ObtainIPorName = GetIP(IPPointer);
                        strcpy(IPPeer,ObtainIPorName);
                    }
                    else
                    {
                        strcpy(IPPeer,IPPointer);
                    }
                    int ISIPExist;
                    connectFlag = 0;
                    for(ISIPExist = 0;ISIPExist<10;ISIPExist++)
                    {
                        if(strcmp(ClientConnectionsObject[ISIPExist].ClientConnIP,IPPeer) ==0)
                        {
                            puts("Already connected to the peer");
                            connectFlag = 1;
                        }
                    }
                    if(connectFlag == 0)
                       {

                    PeerPortPointer = strSeperate(a,3);
                    int PeerPortInt;
                    PeerPortInt = atoi(PeerPortPointer);
                    char ValidateIPPeer[2000]= {0};
                    sprintf(ValidateIPPeer,"%s",IPPeer);
                    int ConnnectBytesRead;
                    //validating if the peer to be connected exists in the network
                    if((ConnnectBytesRead = send(ClientSocketServer,ValidateIPPeer,sizeof(ValidateIPPeer),0)) == -1)
                    {
                        puts("Checking the peer in server");
                    }
                    else
                    {
                        char CONNECTIPValidated[200];
                        memset(CONNECTIPValidated,0,sizeof(CONNECTIPValidated));
                        int CONNECTIPValidatedRec;
                        if((CONNECTIPValidatedRec = recv(ClientSocketServer,CONNECTIPValidated,sizeof(CONNECTIPValidated),0)) !=0)
                           {
                               CONNECTIPValidated[strlen(CONNECTIPValidated)] = '\0';
                               //Setting a connection with the peer
                               if(strcmp(CONNECTIPValidated,"True")==0)
                                {
                                    if(ClientConnectionsObject[1].flag == 0)
                                    {
                                    //Constructing the address for peer
                                    PeerAddress1.sin_family = AF_INET;
                                    inet_pton(AF_INET, IPPeer, &(PeerAddress1.sin_addr));
                                    PeerAddress1.sin_port = htons(PeerPortInt);
                                    bzero(PeerAddress1.sin_zero,8);
                                    //Creating Client Socket
                                    ClientSocketSender1 = socket(AF_INET , SOCK_STREAM , 0);
                                    if(ClientSocketSender1 < 0)
                                    {
                                        puts("Error Creating Client SENDER Socket");
                                    }

                                    //Connecting with the peer
                                    peerConnect1 = connect(ClientSocketSender1, (struct sockaddr *)&PeerAddress1, sizeof(PeerAddress1));
                                    if(peerConnect1 < 0)
                                    {
                                        perror("Error Connecting Peer...");
                                    }
                                    else
                                    {
                                        puts("Peer Connected");
                                        //Sending the port to peer
                                        char ClientMSGPeer1[100];
                                        sprintf(ClientMSGPeer1,"%s",port);
                                        int ClientMSGPeerBytes1;
                                        if((ClientMSGPeerBytes1 = send(ClientSocketSender1,ClientMSGPeer1,sizeof(ClientMSGPeer1),0)) == -1)
                                        {
                                            printf("Adding failed \n");
                                        }
                                        else {printf("Added to peer \n");}
                                        //Updating the connection information in Client Structure
                                        ClientConnectionsObject[1].ClientCount = 2;
                                        strcpy(ClientConnectionsObject[1].ClientConnIP,IPPeer);
                                        strcpy(ClientConnectionsObject[1].ClientConnPort,PeerPortPointer);
                                        ClientConnectionsObject[1].sd = ClientSocketSender1;
                                        //Obtaining the peer name from IP
                                        struct hostent *he1;
                                        char ClientPeer1[100];
                                        struct in_addr ipv4addr1;
                                        inet_pton(AF_INET, IPPeer, &ipv4addr1);
                                        he1 = gethostbyaddr(&ipv4addr1, sizeof ipv4addr1, AF_INET);
                                        strcpy(ClientPeer1,he1->h_name);
                                        //Finishing obtaining the peer name
                                        strcpy(ClientConnectionsObject[1].ClientConnName,ClientPeer1);
                                        ClientConnectionsObject[1].flag = 1;
                                        ClientSocketDescriptor[3] = ClientSocketSender1;
                                    }
                                  }
                                  else
                                  {
                                      if(ClientConnectionsObject[2].flag == 0)
                                      {
                                           //Constructing the address for peer
                                            PeerAddress2.sin_family = AF_INET;
                                            inet_pton(AF_INET, IPPeer, &(PeerAddress2.sin_addr));
                                            PeerAddress2.sin_port = htons(PeerPortInt);
                                            bzero(PeerAddress2.sin_zero,8);
                                            //Creating Client Socket
                                            ClientSocketSender2 = socket(AF_INET , SOCK_STREAM , 0);
                                            if(ClientSocketSender2 < 0)
                                            {
                                                puts("Error Creating Client SENDER Socket");
                                            }

                                            //Connecting with the peer
                                            peerConnect2 = connect(ClientSocketSender2, (struct sockaddr *)&PeerAddress2, sizeof(PeerAddress2));
                                            if(peerConnect2 < 0)
                                            {
                                                perror("Error Connecting Peer...");
                                            }
                                            else
                                            {
                                                puts("Peer Connected");
                                                //Sending the port to peer
                                                char ClientMSGPeer2[100];
                                                sprintf(ClientMSGPeer2,"%s",port);
                                                int ClientMSGPeerBytes2;
                                                if((ClientMSGPeerBytes2 = send(ClientSocketSender2,ClientMSGPeer2,sizeof(ClientMSGPeer2),0)) == -1)
                                                {
                                                    printf("Adding To peer failed \n");
                                                }
                                                else {printf("Added to peer \n");}
                                                //Updating the connection information in Client Structure
                                                ClientConnectionsObject[2].ClientCount = 3;
                                                strcpy(ClientConnectionsObject[2].ClientConnIP,IPPeer);
                                                strcpy(ClientConnectionsObject[2].ClientConnPort,PeerPortPointer);
                                                ClientConnectionsObject[2].sd = ClientSocketSender2;
                                                //Obtaining the peer name from IP
                                                struct hostent *he2;
                                                char ClientPeer2[100];
                                                struct in_addr ipv4addr2;
                                                inet_pton(AF_INET, IPPeer, &ipv4addr2);
                                                he2 = gethostbyaddr(&ipv4addr2, sizeof ipv4addr2, AF_INET);
                                                strcpy(ClientPeer2,he2->h_name);
                                                //Finishing obtaining the peer name
                                                strcpy(ClientConnectionsObject[2].ClientConnName,ClientPeer2);
                                                ClientConnectionsObject[2].flag = 1;
                                                ClientSocketDescriptor[4] = ClientSocketSender2;
                                            }

                                      }
                                      else
                                      {
                                          if(ClientConnectionsObject[3].flag == 0)
                                          {

                                            //Constructing the address for peer
                                            PeerAddress3.sin_family = AF_INET;
                                            inet_pton(AF_INET, IPPeer, &(PeerAddress3.sin_addr));
                                            PeerAddress3.sin_port = htons(PeerPortInt);
                                            bzero(PeerAddress3.sin_zero,8);
                                            //Creating Client Socket
                                            ClientSocketSender3 = socket(AF_INET , SOCK_STREAM , 0);
                                            if(ClientSocketSender3 < 0)
                                            {
                                                puts("Error Creating Client SENDER Socket");
                                            }

                                            //Connecting with the peer
                                            peerConnect3 = connect(ClientSocketSender3, (struct sockaddr *)&PeerAddress3, sizeof(PeerAddress3));
                                            if(peerConnect3 < 0)
                                            {
                                                perror("Error Connecting Peer...");
                                            }
                                            else
                                            {
                                                puts("Peer Connected");
                                                //Sending the port to peer
                                                char ClientMSGPeer3[100];
                                                sprintf(ClientMSGPeer3,"%s",port);
                                                int ClientMSGPeerBytes3;
                                                if((ClientMSGPeerBytes3 = send(ClientSocketSender3,ClientMSGPeer3,sizeof(ClientMSGPeer3),0)) == -1)
                                                {
                                                    printf("Adding to peer failed \n");
                                                }
                                                else {printf("Peer Added \n");}
                                                //Updating the connection information in Client Structure
                                                ClientConnectionsObject[3].ClientCount = 4;
                                                strcpy(ClientConnectionsObject[3].ClientConnIP,IPPeer);
                                                strcpy(ClientConnectionsObject[3].ClientConnPort,PeerPortPointer);
                                                ClientConnectionsObject[3].sd = ClientSocketSender3;
                                                //Obtaining the peer name from IP
                                                struct hostent *he3;
                                                char ClientPeer3[100];
                                                struct in_addr ipv4addr3;
                                                inet_pton(AF_INET, IPPeer, &ipv4addr3);
                                                he3 = gethostbyaddr(&ipv4addr3, sizeof ipv4addr3, AF_INET);
                                                strcpy(ClientPeer3,he3->h_name);
                                                //Finishing obtaining the peer name
                                                strcpy(ClientConnectionsObject[2].ClientConnName,ClientPeer3);
                                                ClientConnectionsObject[3].flag = 1;
                                                ClientSocketDescriptor[5] = ClientSocketSender3;
                                            }
                                          }
                                          else{puts("You can establish only three connections. PLEASE CLOSE EITHER OF 2 OR 3 OR 4");}
                                      }
                                  }
                                }
                                else{puts("No such IP registered on network");}
                           }
                        else{ puts("Error Checking for client");}
                    }
                    }
                    else{puts("Already in you connections list");}
                    }
                    else{puts("See the correct format for CONNECT");}
                }
                else{puts("Need to Register before CONNECT:  TYPE HELP TO SEE ON HOW TO REGISTER");}
                }

                //TERMINATE COMMAND

                TerminatePointer = strSeperate(a,1);
                strcpy(SplitString3,TerminatePointer);
                if(strcmp(SplitString3,"TERMINATE") == 0)
                {
                    int NumberOfWordsTerminate;
                    NumberOfWordsTerminate = 0;
                    NumberOfWordsTerminate = wordCount(a);
                    if(NumberOfWordsTerminate == 2)
                      {

                    char *TerminateIDPointer;
                    char TerminateID[5];
                    int TerminateIDint;
                    TerminateIDPointer = strSeperate(a,2);
                    strcpy(TerminateID,TerminateIDPointer);
                    TerminateIDint = atoi(TerminateID);
                    int TerminateCount;
                    TerminateCount = 0;
                    for(ClientConnectionsObjectLoop = 0;ClientConnectionsObjectLoop<10;ClientConnectionsObjectLoop++)
                    {
                        if(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount == TerminateIDint)
                        {   TerminateCount = 1;
                            if(TerminateIDint == 1)
                            {
                                REGISTER = 0;
                            }
                            for(ClientSocketDescriptorLoop = 2; ClientSocketDescriptorLoop<15; ClientSocketDescriptorLoop++)
                            {
                                if(ClientSocketDescriptor[ClientSocketDescriptorLoop] == ClientConnectionsObject[ClientConnectionsObjectLoop].sd)
                                {
                                    close(ClientSocketDescriptor[ClientSocketDescriptorLoop]);
                                    ClientSocketDescriptor[ClientSocketDescriptorLoop] = 0;
                                    printf("Connection with %s terminated \n",ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnName);
                                    break;
                                }
                            }
                            ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount = 0;
                            ClientConnectionsObject[ClientConnectionsObjectLoop].flag = 0;
                            ClientConnectionsObject[ClientConnectionsObjectLoop].sd = 0;
                            strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnName,NullifyClientConnectionObjectDetails);
                            strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnPort,NullifyClientConnectionObjectDetails);
                            strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnIP,NullifyClientConnectionObjectDetails);
                            break;
                        }
                    }
                    if(TerminateCount == 0){puts("No such Connection listed in your connections");}
                }
                else{puts("See the correct format for TERMINATE: TYPE HELP");}

                }

                 //QUIT COMMAND

                if(strcmp(a,"QUIT") == 0)
                {
                    for(ClientSocketDescriptorLoop = 2;ClientSocketDescriptorLoop < 15;ClientSocketDescriptorLoop++)
                    {
                        if(ClientSocketDescriptor[ClientSocketDescriptorLoop] != 0 )
                        {
                            close(ClientSocketDescriptor[ClientSocketDescriptorLoop]);
                        }
                    }

                    for(ClientSocketDescriptorLoop = 2;ClientSocketDescriptorLoop < 15;ClientSocketDescriptorLoop++)
                    {
                        ClientSocketDescriptor[ClientSocketDescriptorLoop] = 0;
                    }
                    for(ClientConnectionsObjectLoop = 0;ClientConnectionsObjectLoop<10;ClientConnectionsObjectLoop++)
                    {
                        ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount = 0;
                        ClientConnectionsObject[ClientConnectionsObjectLoop].flag = 0;
                        ClientConnectionsObject[ClientConnectionsObjectLoop].sd = 0;
                        strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnName,NullifyClientConnectionObjectDetails);
                        strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnPort,NullifyClientConnectionObjectDetails);
                        strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnIP,NullifyClientConnectionObjectDetails);

                    }
                    REGISTER = 0;
                }

                //GET COMMAND

                GETPointer = strSeperate(a,1);
                strcpy(SplitString4,GETPointer);
                if(strcmp(SplitString4,"GET") == 0)
                {
                    int NumberOfTermsGET;
                    NumberOfTermsGET = 0;
                    NumberOfTermsGET = wordCount(a);
                    if(NumberOfTermsGET == 3)
                    {
                    GETIDPointer = strSeperate(a,2);
                    strcpy(GETID,GETIDPointer);
                    int GETIDint;
                    GETIDint = atoi(GETID);
                    GETFileNamePointer = strSeperate(a,3);
                    strcpy(GETFileName,GETFileNamePointer);
                    //Checking if the request is for Server
                    if(GETIDint == 1)
                    {
                        puts("Cannot transfer files to timberlake<SERVER>");
                    }
                    else
                    {
                        for(ClientConnectionsObjectLoop = 0;ClientConnectionsObjectLoop<10;ClientConnectionsObjectLoop++)
                        {
                            if(GETIDint == ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount)
                            {
                                strcat(SplitString4," ");
                                strcat(SplitString4,GETFileName);
                                char RequestedFileName[2000]= {0};
                                sprintf(RequestedFileName,"%s",SplitString4);
                                int GETFileRequestBytesSent;

                                if((GETFileRequestBytesSent = send(ClientConnectionsObject[ClientConnectionsObjectLoop].sd,RequestedFileName,sizeof(RequestedFileName),0)) == -1)
                                {
                                    puts("file name request failed");
                                }
                                else
                                {
                                    //Newly Added

                                   FILE *GETRecFilePointer;
                                   GETRecFilePointer = fopen(GETFileName,"a");
                                   char GETFileRec[5000];
                                   memset(GETFileRec,0,sizeof(GETFileRec));

                                   GETFileReadVal = 0;

                                   if((GETFileReadVal = recv(ClientConnectionsObject[ClientConnectionsObjectLoop].sd , GETFileRec, sizeof(GETFileRec),0)) != 0)
                                   {
                                       GETFileRec[strlen(GETFileRec)] = '\0';
                                       if((strcmp(GETFileRec,"No") == 0))
                                          {
                                              puts("No Such File");
                                          }
                                       else{
                                       fputs(GETFileRec,GETRecFilePointer);
                                       fclose(GETRecFilePointer);
                                       puts("Successfully Downloaded");
                                       }
                                   }
                                   else{puts("Error Rec File");}


                                }
                            }
                        }
                    }
                } else{puts("See the correct format for GET: TYPE HELP");}
                }


                PUTPointer = strSeperate(a,1);
                strcpy(SplitString5,PUTPointer);
                if(strcmp(SplitString5,"PUT") == 0)
                {
                    int NumberOfTermsPUT;
                    NumberOfTermsPUT = 0;
                    NumberOfTermsPUT = wordCount(a);
                    if(NumberOfTermsPUT == 3)
                    {
                        char tempPUT[100];
                        strcpy(tempPUT,"PUT");
                        strcat(tempPUT," ");
                        PUTIDPointer = strSeperate(a,2);
                        strcpy(PUTID,PUTIDPointer);
                        int PUTIDint;
                        PUTIDint = atoi(PUTID);
                        PUTFileNamePointer = strSeperate(a,3);
                        strcpy(PUTFileName,PUTFileNamePointer);
                        strcat(tempPUT,PUTFileName);
                        strcat(tempPUT," ");

                        if(PUTIDint == 1)
                        {
                            puts("Cannot PUT a file on SERVER");
                        }
                        else
                        {
                            for(ClientConnectionsObjectLoop = 1;ClientConnectionsObjectLoop<10;ClientConnectionsObjectLoop++)
                            {
                                if(PUTIDint == ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount)
                                {

                                    char PUTc[4000];
                                    int PUTfileSize;
                                    PUTfileSize = 0;
                                    FILE *PUTfp;
                                    PUTfp = fopen(PUTFileName,"r");
                                    if(PUTfp == NULL)
                                    {
                                        puts("No such File");
                                    }
                                    else
                                    {
                                        while(!feof(PUTfp))
                                        {
                                                PUTc[PUTfileSize] = fgetc(PUTfp);
                                                PUTfileSize=++PUTfileSize;
                                                if(PUTfileSize == 4000)
                                                {
                                                    break;
                                                }
                                        }
                                        PUTc[PUTfileSize] = '\0';
                                        strcat(tempPUT,PUTc);
                                        puts("FileReadSuccess");
                                        char PUTFileSendBuffer[5000] = {0};
                                        sprintf(PUTFileSendBuffer,"%s",tempPUT);
                                        int PUTFileSentValue;
                                        PUTFileSentValue = 0;
                                        if((PUTFileSentValue = send(ClientConnectionsObject[ClientConnectionsObjectLoop].sd,PUTFileSendBuffer,sizeof(PUTFileSendBuffer),0)) == 0)
                                        {
                                            puts("File upload failed");
                                        }
                                        else{puts("File upload Success");}
                                        fclose(PUTfp);


                                    }

                                }
                            }
                        }

                    }
                    else{puts("See the correct Format For PUT: TYPE HELP");}
                }


                if(strcmp(a,"CREATOR") == 0)
                {
                    puts("CREATOR DETAILS");
                    puts("Anuj Rastogi");
                    puts("anujrast");
                    puts("anujrast@buffalo.edu");
                    puts("50134324");
                }

                else{puts("type<HELP> commands accept upper-case.CASE SENSITIVE");}



            }

            //Checking the listener Socket
            if(FD_ISSET(ClientSocketDescriptor[1],&socketfd))
            {
                NewSocketDes = accept(ClientSocketDescriptor[1],(struct sockaddr *)&PeerAddressAccept,(socklen_t*)&PeerAddressLenAccept);
                if(NewSocketDes<0)
                {
                    puts("Error in connecting..Peer Busy cannot handle more than three connections");
                }
                else
                {
                puts("New Peer Successfully connected");
                for(ClientSocketDescriptorLoop = 6; ClientSocketDescriptorLoop < 15; ClientSocketDescriptorLoop++)
                {
                    if(ClientSocketDescriptor[ClientSocketDescriptorLoop] == 0)
                    {
                        ClientSocketDescriptor[ClientSocketDescriptorLoop] = NewSocketDes;
                        break;
                    }
                }
                //Getting the information about Connection and string in Structure
                char z[20];
                getpeername(NewSocketDes, (struct sockaddr*)&addrAccept, &PeerAddrLengthAccept);
                struct sockaddr_in *sAccept = (struct sockaddr_in *)&addrAccept;
                inet_ntop(AF_INET, &sAccept->sin_addr, PeerIPAccept, sizeof(PeerIPAccept));
                //Getting the Client name
                struct hostent *heAccept;
                char PeerNameAccept[100];
                struct in_addr ipv4addrAccept;
                inet_pton(AF_INET, PeerIPAccept, &ipv4addrAccept);
                heAccept = gethostbyaddr(&ipv4addrAccept, sizeof ipv4addrAccept, AF_INET);
                strcpy(PeerNameAccept,heAccept->h_name);
                //Adding New Connection into Client Structure
                for(ClientConnectionsObjectLoop = 4;ClientConnectionsObjectLoop<10;ClientConnectionsObjectLoop++)
                {
                    if(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount == 0)
                    {
                        strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnName,PeerNameAccept);
                        strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnIP,PeerIPAccept);
                        ClientConnectionsObject[ClientConnectionsObjectLoop].flag =0;
                        ClientConnectionsObject[ClientConnectionsObjectLoop].sd = NewSocketDes;
                        break;
                    }
                }

                }
            }


            //Checking For the Remaining Sockets
            for(ClientSocketDescriptorLoop = 2; ClientSocketDescriptorLoop<15;ClientSocketDescriptorLoop++)
            {
                if(ClientSocketDescriptor[ClientSocketDescriptorLoop] != 0)
                {
                    if(FD_ISSET(ClientSocketDescriptor[ClientSocketDescriptorLoop],&socketfd))
                    {
                        memset(ClientPeerBuffer, 0 , sizeof(ClientPeerBuffer));
                        if((ClientPeerBufferReadVal = recv(ClientSocketDescriptor[ClientSocketDescriptorLoop] , ClientPeerBuffer, sizeof(ClientPeerBuffer),0)) == 0)
                        {
                            for(ClientConnectionsObjectLoop =0;ClientConnectionsObjectLoop<10;ClientConnectionsObjectLoop++)
                            {
                                if(ClientConnectionsObject[ClientConnectionsObjectLoop].sd == ClientSocketDescriptor[ClientSocketDescriptorLoop])
                                {
                                    ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount = 0;
                                    ClientConnectionsObject[ClientConnectionsObjectLoop].flag = 0;
                                    ClientConnectionsObject[ClientConnectionsObjectLoop].sd = 0;
                                    strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnName,NullifyClientConnectionObjectDetails);
                                    strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnPort,NullifyClientConnectionObjectDetails);
                                    strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnIP,NullifyClientConnectionObjectDetails);
                                }
                            }
                            close(ClientSocketDescriptor[ClientSocketDescriptorLoop]);
                            ClientSocketDescriptor[ClientSocketDescriptorLoop] = 0;
                            puts("Peer Disconnected");
                        }
                        else
                        {
                            ClientPeerBuffer[strlen(ClientPeerBuffer)] = '\0';
                            for(ClientConnectionsObjectLoop =0;ClientConnectionsObjectLoop<10;ClientConnectionsObjectLoop++)
                            {
                                ClientConnectionCount = ClientConnectionCount+1;
                                if(ClientConnectionsObject[ClientConnectionsObjectLoop].sd == ClientSocketDescriptor[ClientSocketDescriptorLoop])
                                {
                                    if( strcmp(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnPort,NullifyClientConnectionObjectDetails) == 0)
                                    {
                                        strcpy(ClientConnectionsObject[ClientConnectionsObjectLoop].ClientConnPort,ClientPeerBuffer);
                                        ClientConnectionsObject[ClientConnectionsObjectLoop].ClientCount = ClientConnectionCount;
                                        ClientConnectionCount = 0;
                                        break;
                                    }
                                }
                            }

                            int ValidateMessage;
                            ValidateMessage = validateIpOrName(ClientPeerBuffer);
                            if(ValidateMessage == 2)
                            {
                                if(strlen(ClientPeerBuffer) > 35)
                                {
                                    puts(ClientPeerBuffer);
                                }
                            }

                            if(strlen(ClientPeerBuffer) > 1)
                            {

                            char *PUTReciverPointer1;
                            char PUTReciverPointerFinal[3000];
                            memset(PUTReciverPointerFinal,0,sizeof(PUTReciverPointerFinal));
                            PUTReciverPointer1 = strSeperate(ClientPeerBuffer,1);
                            strcpy(PUTReciverPointerFinal,PUTReciverPointer1);

                            if(strcmp(PUTReciverPointerFinal,"PUT") == 0)
                            {
                                char *PUTFileNamePointer;
                                char PUTFileNameFinal[100];
                                PUTFileNamePointer = strSeperate(ClientPeerBuffer,2);
                                strcpy(PUTFileNameFinal,PUTFileNamePointer);

                                FILE *PutRecfp;
                                PutRecfp = fopen(PUTFileNameFinal,"a");
                                fputs(ClientPeerBuffer,PutRecfp);
                                fclose(PutRecfp);
                                puts("Successfully Downloaded a file");
                                }
                            }




                            if(strlen(ClientPeerBuffer) > 4)
                            {
                            char *RecFileNamePointer;
                            char RecFileName[100];
                            char *RecGETPointer;
                            char RecGET[3000];
                            RecGETPointer = strSeperate(ClientPeerBuffer,1);
                            strcpy(RecGET,RecGETPointer);
                            if(strcmp(RecGET,"GET") == 0)
                            {
                                RecFileNamePointer = strSeperate(ClientPeerBuffer,2);
                                strcpy(RecFileName,RecFileNamePointer);
                                FILE *fp;
                                char c[5000];
                                int fileSize;
                                fileSize = 0;

                                fp = fopen(RecFileName,"r");
                                if(fp == NULL)
                                {
                                   char NoFile[100] = {0};
                                   sprintf(NoFile,"%s","No");
                                   int NoFileInt;
                                   NoFileInt = 0;
                                   if((NoFileInt = send(ClientSocketDescriptor[ClientSocketDescriptorLoop],NoFile,sizeof(NoFile),0)) == 0)
                                   {
                                        puts("File sent Failed on GET");
                                   }
                                   else{puts("error Message sent successfully");}

                                }
                                else
                                {


                                while(!feof(fp))
                                {
                                    c[fileSize] = fgetc(fp);
                                    fileSize=++fileSize;
                                    if(fileSize == 5000)
                                    {
                                        break;
                                    }
                                }
                                c[fileSize] = '\0';
                                printf("%s \n", c);
                                char FileSendBuffer[5000]={0};
                                sprintf(FileSendBuffer,"%s",c);
                                int fileSendingInt;
                                fileSendingInt = 0;
                                    if((fileSendingInt = send(ClientSocketDescriptor[ClientSocketDescriptorLoop],FileSendBuffer,sizeof(FileSendBuffer),0)) == 0)
                                    {
                                        puts("File Send Failed");
                                    }
                                    else
                                    {puts("File Send Success");
                                    int downloadFileLoop;
                                    downloadFileLoop = 0;
                                    for(downloadFileLoop = 0; downloadFileLoop<10; downloadFileLoop++)
                                    {
                                        if(ClientSocketDescriptor[ClientSocketDescriptorLoop] == ClientConnectionsObject[downloadFileLoop].sd)
                                        {
                                            printf(" File Downloaded by %s \n", ClientConnectionsObject[downloadFileLoop].ClientConnName);
                                        }
                                    }
                                    }

                                fclose(fp);

                                }

                            }

                            }

                        }
                    }
                }
            }


        }


}
