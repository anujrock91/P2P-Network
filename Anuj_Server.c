#include "network.h"

struct AddressInformation
{
    int count;
    char details[1000];
    char port[100];
    int discriptorVar;
};

char *ListGenerator(struct AddressInformation *s);
void MainServerFunction(char *port)
{
    struct AddressInformation addInfo[10];
    int ServerListnerSocket;
    struct sockaddr_in ServerAddress;
    int BindVar;
    int portNumber;
    fd_set socketfd;
    int SocketDescriptor[10];
    int MaxSocketDescriptor;
    int SocketDescriptorLoop;
    int SocketActivity;
    int NewSocketDescriptor;
    struct sockaddr_in ClientAddress;
    int ClientAddressLength;
    char buffer[100];
    int AddressInformationLoop;
    int AddressInformationCount;
    char a[100];
    AddressInformationCount = 1;
    char ClientReadBuffer[2000];
    int ClientReadValue;
    char NullifyAddInfoDetails[] = " ";
    //Server List sending variables
    char *ServerList;
    char ServerListFinal[3000];
    int ServerSentList;
    char *QuitServerList;
    char QuitServerListFinal[3000];
    int QuitServerSentList;
    char *ServerListClientConnect;
    char ServerListClientConnectFinal[3000];
    int ServerListClientConnectSent;
    //Validating IP for PEER
        struct sockaddr_storage validateIPPeer;
        char ValidatePeerIP[INET6_ADDRSTRLEN];
        socklen_t ValidatePeerIPLength;
        ValidatePeerIPLength = sizeof(ValidatePeerIP);

    //newly added
        struct sockaddr_storage addr;
        char ClientIP[INET6_ADDRSTRLEN];
        int Clientport;
        socklen_t ClientAddrLength;
        ClientAddrLength = sizeof(addr);
        //Newly Added Finish

    //Getting the IP of Server
    char getIpTimberlake[]="timberlake.cse.buffalo.edu";
    char *ReceiveIP;
    ReceiveIP = GetIP(getIpTimberlake);
    //Getting the port number
    portNumber = atoi(port);

    //Getting the server address
    ServerAddress.sin_family = AF_INET;
    inet_pton(AF_INET, ReceiveIP, &(ServerAddress.sin_addr));
    ServerAddress.sin_port = htons(portNumber);
    bzero(ServerAddress.sin_zero,8);

    //Creating a server socket
    ServerListnerSocket = socket(AF_INET , SOCK_STREAM , 0);
    if(ServerListnerSocket < 0)
    {
        puts("Error creating Socket...");
    }

    //Binding the Server socket
    BindVar = bind(ServerListnerSocket, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress));
    if(BindVar < 0)
    {
        puts("Error Binding...");
    }

    //Server Listener
    if((listen(ServerListnerSocket, 5)) < 0)
    {
        puts("Error in Listening Method...");
    }

    for(SocketDescriptorLoop = 2; SocketDescriptorLoop <10; SocketDescriptorLoop++)
    {
        SocketDescriptor[SocketDescriptorLoop] = 0;
    }
    SocketDescriptor[0] = stdin;
    SocketDescriptor[1] = ServerListnerSocket;

    //working with Address Information structure
    char *StringAddressGenVar;
    addInfo[0].count = 1;
    StringAddressGenVar = TwoStringCombine(getIpTimberlake,ReceiveIP);
    strcpy(addInfo[0].details,StringAddressGenVar);
    strcpy(addInfo[0].port,port);
    addInfo[0].discriptorVar = ServerListnerSocket;

    for(AddressInformationLoop=1; AddressInformationLoop<10; AddressInformationLoop++)
    {
        addInfo[AddressInformationLoop].discriptorVar = 0;
        addInfo[AddressInformationLoop].count = 0;
        strcpy(addInfo[AddressInformationLoop].details,NullifyAddInfoDetails);
        strcpy(addInfo[AddressInformationLoop].port,NullifyAddInfoDetails);
    }

    puts("Welcome Server");

    //Initiating While Loop
    while(1)
    {
        memset(ClientReadBuffer, 0 , sizeof(ClientReadBuffer));
        //Making the SocketDescriptors in the Set Zero
        AddressInformationCount = 1;
        FD_ZERO(&socketfd);
        FD_SET(0,&socketfd);
        FD_SET(SocketDescriptor[1],&socketfd);

        if(0>SocketDescriptor[1])
        {
            MaxSocketDescriptor = 0;
        }
        else
        {
            MaxSocketDescriptor = SocketDescriptor[1];
        }

        //Adding All The established Sockets To The Set Of Sockets To Be Analyzed For Activity
        for(SocketDescriptorLoop = 2; SocketDescriptorLoop<10; SocketDescriptorLoop++)
        {
            if(SocketDescriptor[SocketDescriptorLoop] != 0)
            {
                FD_SET(SocketDescriptor[SocketDescriptorLoop],&socketfd);
                    if(SocketDescriptor[SocketDescriptorLoop]>MaxSocketDescriptor)
                    {
                        MaxSocketDescriptor = SocketDescriptor[SocketDescriptorLoop];
                    }
            }
        }

        //Checking The Activity At Every Socket In The Set Of Sockets To Be Analyzed
        SocketActivity = select( MaxSocketDescriptor + 1 , &socketfd , NULL , NULL , NULL);
        if ((SocketActivity < 0) && (errno!=EINTR))
            {
                puts("select Error...");
            }
        //Checking Which All Sockets In The Select Showed Activity
        if(FD_ISSET(0,&socketfd))
            {
                gets(buffer);
                strcpy(a,buffer);
                if(strcmp(a,"HELP") == 0)
                {
                    int i;
                    i=Help();
                }

                if(strcmp(a,"DISPLAY") == 0)
                {
                    printf("ProcessIP:  %s \n",ReceiveIP);
                    printf("ListeningPortNumber:  %d \n",portNumber);
                }

                if(strcmp(a,"LIST") == 0)
                {
                    for(AddressInformationLoop=0; AddressInformationLoop <10;AddressInformationLoop++)
                    {
                        if(addInfo[AddressInformationLoop].count != 0)
                        {
                            printf("%d  %s  %s \n",addInfo[AddressInformationLoop].count,addInfo[AddressInformationLoop].details, addInfo[AddressInformationLoop].port);
                        }
                    }
                }

                if(strcasecmp(a,"CREATOR") == 0)
                {
                    puts("CREATOR DETAILS");
                    puts("Anuj Rastogi");
                    puts("anujrast");
                    puts("anujrast@buffalo.edu");
                    puts("50134324");
                }

                else{puts("TYPE HELP..commands are <UPPERCASE> and CASE-SENSITIVE");}

            }

        if(FD_ISSET(SocketDescriptor[1],&socketfd))
            {
                NewSocketDescriptor = accept(SocketDescriptor[1], (struct sockaddr *)&ClientAddress, (socklen_t*)&ClientAddressLength);
                if(NewSocketDescriptor<0)
                {
                    puts("Error In Connecting...");
                }
                else
                {

                //Removing else scope from here and adding later
                for(SocketDescriptorLoop = 2; SocketDescriptorLoop<10 ; SocketDescriptorLoop++)
                {
                    if(SocketDescriptor[SocketDescriptorLoop] == 0)
                    {
                        SocketDescriptor[SocketDescriptorLoop]= NewSocketDescriptor;
                        break;
                    }
                }
                //Getting Client IP and Port
                char z[20];
                getpeername(NewSocketDescriptor, (struct sockaddr*)&addr, &ClientAddrLength);
                struct sockaddr_in *s = (struct sockaddr_in *)&addr;
                Clientport = ntohs(s->sin_port);
                inet_ntop(AF_INET, &s->sin_addr, ClientIP, sizeof(ClientIP));
                char *ClientportStringPointer;
                char ClientportString[20];
                ClientportStringPointer = IntToString(Clientport);
                strcpy(ClientportString,ClientportStringPointer);
                //Getting the Client name
                struct hostent *he;
                char ClientName[100];
                struct in_addr ipv4addr;
                inet_pton(AF_INET, ClientIP, &ipv4addr);
                he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
                strcpy(ClientName,he->h_name);
                //Creating the String for Client Address
                char *ClientAddressGenPointer;
                char ClientAddressGen[100];
                ClientAddressGenPointer = TwoStringCombine(ClientName,ClientIP);
                strcpy(ClientAddressGen,ClientAddressGenPointer);

               //Adding the newly connected client details to structure
                for(AddressInformationLoop=1; AddressInformationLoop<10;AddressInformationLoop++)
                {
                    if(addInfo[AddressInformationLoop].count == 0)
                    {
                        addInfo[AddressInformationLoop].discriptorVar = NewSocketDescriptor;
                        strcpy(addInfo[AddressInformationLoop].details,ClientAddressGen);
                        break;
                    }
                }
            }
            }



        for(SocketDescriptorLoop = 2; SocketDescriptorLoop<10 ; SocketDescriptorLoop++)
            {
                if(SocketDescriptor[SocketDescriptorLoop] != 0)
                {

                    if(FD_ISSET(SocketDescriptor[SocketDescriptorLoop],&socketfd))
                    {
                        memset(ClientReadBuffer, 0 , sizeof(ClientReadBuffer));
                        if ((ClientReadValue = recv(SocketDescriptor[SocketDescriptorLoop] , ClientReadBuffer, sizeof(ClientReadBuffer),0)) == 0)
                        {
                            for(AddressInformationLoop = 1; AddressInformationLoop<10; AddressInformationLoop++)
                            {
                                if(addInfo[AddressInformationLoop].discriptorVar == SocketDescriptor[SocketDescriptorLoop])
                                {
                                    addInfo[AddressInformationLoop].count = 0;
                                    addInfo[AddressInformationLoop].discriptorVar = 0;
                                    strcpy(addInfo[AddressInformationLoop].details,NullifyAddInfoDetails);
                                    strcpy(addInfo[AddressInformationLoop].port,NullifyAddInfoDetails);
                                }
                            }
                            close(SocketDescriptor[SocketDescriptorLoop]);
                            SocketDescriptor[SocketDescriptorLoop] = 0;
                            puts("Client Disconnected");
                            //Sending the list to all the clients
                            int QuitList;
                            QuitServerList = ListGenerator(addInfo);
                            strcpy(QuitServerListFinal,QuitServerList);
                            char QuitBytesSending[3000] = {0};
                            sprintf(QuitBytesSending,"%s",QuitServerListFinal);
                            for(QuitList = 2;QuitList<10;QuitList++)
                            {
                                if(SocketDescriptor[QuitList] != 0)
                                {
                                    QuitServerSentList = 0;
                                    if((QuitServerSentList = send(SocketDescriptor[QuitList],QuitBytesSending,sizeof(QuitBytesSending),0)) == 0)
                                    {
                                        puts("Quit List failed");
                                    }
                                    else{puts("Quit List Sent Success");}
                                }
                            }
                        }
                        else
                        {

                            ClientReadBuffer[strlen(ClientReadBuffer)] = '\0';
                            if(strcmp(ClientReadBuffer,"LIST") == 0)
                            {
                                ServerList = ListGenerator(addInfo);
                                strcpy(ServerListFinal,ServerList);
                                char ServerBytesSendingRequest[2000] = {0};
                                sprintf(ServerBytesSendingRequest,"%s",ServerListFinal);

                                ServerSentList = 0;
                                if((ServerSentList = send(SocketDescriptor[SocketDescriptorLoop],ServerBytesSendingRequest,sizeof(ServerBytesSendingRequest),0)) == -1)
                                {
                                    puts("List Sending Failed on request");
                                }
                                else{puts("List Sent successfully on request");}
                            }
                            else
                            {
                                for(AddressInformationLoop = 1; AddressInformationLoop<10; AddressInformationLoop++)
                                {
                                    AddressInformationCount = AddressInformationCount+1;
                                    if(addInfo[AddressInformationLoop].discriptorVar == SocketDescriptor[SocketDescriptorLoop])
                                    {
                                        if(strcmp(addInfo[AddressInformationLoop].port,NullifyAddInfoDetails) == 0)
                                        {
                                            addInfo[AddressInformationLoop].count = AddressInformationCount;
                                            strcpy(addInfo[AddressInformationLoop].port,ClientReadBuffer);
                                            AddressInformationCount = 1;
                                            //Sending the updated list to clients
                                            int SendingUpdatedList;
                                            ServerListClientConnect = ListGenerator(addInfo);
                                            strcpy(ServerListClientConnectFinal,ServerListClientConnect);
                                            for(SendingUpdatedList = 2;SendingUpdatedList<10;SendingUpdatedList++)
                                            {
                                                if(SocketDescriptor[SendingUpdatedList] != 0)
                                                {
                                                    ServerListClientConnectSent = 0;
                                                    if((ServerListClientConnectSent = send(SocketDescriptor[SendingUpdatedList],ServerListClientConnectFinal,sizeof(ServerListClientConnectFinal),0)) == -1)
                                                    {
                                                        puts("Sending Updated Client list Failed");
                                                    }
                                                    else
                                                    {
                                                        puts("Sending Updated client list success");
                                                    }
                                                }
                                            }

                                            break;
                                        }
                                    }
                                }

                                if( strlen(ClientReadBuffer) > 5)
                                {
                                    puts("in validation");
                                    int IPValidateCount = 0;
                                    int x;
                                    for(x = 2;x<10;x++)
                                    {
                                        if(SocketDescriptor[x] != 0)
                                        {
                                        getpeername(SocketDescriptor[x], (struct sockaddr*)&validateIPPeer, &ValidatePeerIPLength);
                                        struct sockaddr_in *ValidateIP = (struct sockaddr_in *)&validateIPPeer;
                                        inet_ntop(AF_INET, &ValidateIP->sin_addr, ValidatePeerIP, sizeof(ValidatePeerIP));
                                        if(strcmp(ClientReadBuffer,ValidatePeerIP) == 0){ IPValidateCount = 1;}
                                        }
                                    }
                                    if(IPValidateCount == 1)
                                    {
                                        puts("IP exists");
                                        char ValidateIPResult[2000]= {0};
                                        sprintf(ValidateIPResult,"%s","True");
                                        int ValidateIPResultBytesRead;
                                        if((ValidateIPResultBytesRead = send(SocketDescriptor[SocketDescriptorLoop],ValidateIPResult,sizeof(ValidateIPResult),0)) == -1)
                                        {
                                            puts("Sending for ValidateIP Request Failed");
                                        }
                                        else
                                        {
                                            puts("IP result send successfully");
                                        }
                                    }
                                    else
                                    {
                                        puts("IP Does Not Exists");
                                        char ValidateIPResult2[2000]= {0};
                                        sprintf(ValidateIPResult2,"%s","False");
                                        int ValidateIPResultBytesRead2;
                                        if((ValidateIPResultBytesRead2 = send(SocketDescriptor[SocketDescriptorLoop],ValidateIPResult2,sizeof(ValidateIPResult2),0)) == -1)
                                        {
                                            puts("Sending for ValidateIP Request Failed");
                                        }
                                        else
                                        {
                                            puts("IP result send successfully");
                                        }
                                    }

                                }




                            }

                        }

                    }
                }
            }


    }


}

char *ListGenerator(struct AddressInformation *s)
{
    char *countStr;
    char countStrFinal[100];
    countStr = IntToString(s[0].count);
    strcpy(countStrFinal,countStr);
    char *StringAddressGenOutput;
    static char SAGOutput[2000];
    StringAddressGenOutput = StringAddressGen(countStrFinal,s[0].details,s[0].port);
    strcpy(SAGOutput,StringAddressGenOutput);
    int i;
    for(i=1; i<10;i++)
    {
        if(s[i].count != 0)
        {
            memset(countStr,0,sizeof(countStr));
            memset(countStrFinal,0,sizeof(countStrFinal));
            countStr = IntToString(s[i].count);
            strcpy(countStrFinal,countStr);
            memset(StringAddressGenOutput,0,sizeof(StringAddressGenOutput));
            StringAddressGenOutput = StringAddressGen(countStrFinal,s[i].details,s[i].port);
            strcat(SAGOutput,",");
            strcat(SAGOutput,"\n");
            strcat(SAGOutput,StringAddressGenOutput);
        }
    }
    return SAGOutput;
}

