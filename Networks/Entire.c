------multicast receiver------
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 512
int main()
{
	struct sockaddr_in local_add;
	int sock;
	int addr_len,size;
	struct ip_mreq grp_add;
	char buff[SIZE];
	memset( &buff, 0, sizeof(buff));
	if ((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0) {
		printf("Socket Creation Error\n");
		exit(1);
	} else
		printf("Socket instance creation successful\n");
	/*
	   int reuse = 1;
	   if ((setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse)))<0) {
	   printf("Socket not available for reuse\n");
	   close(sock);
	   exit(1);
	   } else
	   printf("Socket available for reuse\n");
	   */
	// construct the bind sturcture
	memset(&local_add,0,sizeof(local_add));		// Zero out the structure
	local_add.sin_family=AF_INET;			// Internet Addr. family
	local_add.sin_addr.s_addr=htonl(INADDR_ANY);	// Any incoming interface
	local_add.sin_port=htons(8080);			// Multicast port

	if ((bind(sock,(struct sockaddr *)&local_add,sizeof(local_add))) < 0) {
		printf("bind() failure\n");
		close(sock);
		exit(1);
	} else
		printf("bind() success\n");

	/* Specify the multicast group */
	grp_add.imr_multiaddr.s_addr=inet_addr("224.0.0.1");
	/* Accept multicast from any interface */
	grp_add.imr_interface.s_addr=inet_addr("127.0.0.1");

	/* Join the multicast group */
	if ((setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&grp_add,sizeof(grp_add)))<0) {
		printf("setsocketopt() failed\n");
		close(sock);
		exit(1);
	} else
		printf("setsockopt() success\n");

	int recvStrLen = 0;
	while(1) {
		addr_len=sizeof(buff);
		//if ((read(sock,buff,addr_len)) < 0) {
		if ((recvStrLen = recvfrom(sock,buff,addr_len, 0, NULL, 0)) < 0) {
			printf("Error in receiving message\n");
			close(sock);
			exit(1);
		} else {
			buff[recvStrLen] = '\0';
			printf("Received: %s",buff);
		}
	}
	close(sock);
	return 0;
}
------multicast sender------
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 512

int main() {
	struct sockaddr_in grp_add;
	struct in_addr local_add;
	int sock;
	char buff[512];

	/* create the socket for sending/receiving datagrams */
	if ((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0) {
		printf("Socket creation error\n");
		close(sock);
		exit(1);
	} else
		printf("Socket instance creation successful\n");

	memset(&grp_add,0,sizeof(grp_add));
	grp_add.sin_family=AF_INET;
	grp_add.sin_addr.s_addr=inet_addr("224.0.0.1");
	grp_add.sin_port=htons(8080);

	/* interface for the given socket */
	local_add.s_addr=inet_addr("127.0.0.1");

	/* 
	 * IP_MULTICAST_IF:
	 * we have choosen a concrete out going interface for a given socket with this option
	 */
	if ((setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF,&local_add, sizeof(local_add))) < 0) {
		printf("setsockopt() failed\n");
		close(sock);
		exit(1);
	} else
		printf("setsockopt() success\n");

	while (1) {
		memset(&buff,0,sizeof(buff));
		printf("Enter Multicasting Text(\"exit\" to end): ");
		fgets(buff, SIZE, stdin);
		if(strlen(buff)<=1) {
			close(sock);
			exit(1);
		}

		/* end if exited */
		if(strcmp(buff, "exit\n") == 0){
			close(sock);
			return 0;
		}

		if ((sendto(sock,buff,strlen(buff),0,(struct sockaddr *)&grp_add,sizeof(grp_add))) < 0) {
			printf("sendto() error\n");
			close(sock);
			exit(1);
		} else
			printf("sendto() successful\n") ;
	}

	return 0;
}
--------CRC----------
#include<stdio.h>
int  main()
{
	printf("enter the no of bits in the data\n");
	int size_data;
	scanf("%d",&size_data);
	
	int rem[16],data[32],div[16],j;
	int i,data_copy[32];
	
	printf("enter the data,seperate each bit by a space\n");
	for(i=0;i<size_data;i++) {
		scanf("%d",&data[i]);
		data_copy[i]=data[i];
	}

	printf("enter the no of bits in the divisor\n");
	int size_divisor;
	scanf("%d",&size_divisor);
	
	printf("enter the divisor\n");
	for(i=0;i<size_divisor;i++) {
		scanf("%d",&div[i]);
	}

	for(i=size_data;i<(size_data+size_divisor);i++) {
		data[i]=0;
		data_copy[i]=0;
	}

	int x;
	for( i = 0; i < size_data; i++) {
		x = i;
		if(data[i] == 1) {
			for (j=0;j < size_divisor;j++) {
				if (data[x] == div[j]) {
					data[x] = 0;
					rem[j] = 0;
				} else {
					data[x] = 1;
					rem[j] = 1;
				}
				x++;
			}
		}
	}

	printf("the remainder is : ");
	for(j=0;j<size_divisor;j++)
		printf("%d",rem[j]);
	printf("\n");

	FILE *f;
	f=fopen("crc_generator.txt","w"); //write the generated codeword to the file

	printf("the  generated codeword(data+remainder) sent is : ");
	for(j=0;j<(size_data);j++) {
		printf("%d",data_copy[j]);
		fprintf(f,"%d ",data_copy[j]);
	}
	for(j=1;j<size_divisor;j++) { //first bit of remainder not padded 
		printf("%d",rem[j]);
		fprintf(f,"%d ",rem[j]);
	}
	printf("\ncodeword and other details is stored in a file crc_generator.txt\n");
	fclose(f);
	return 0;
}
---------tcp chat client-----------
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in echo_client, echo_server;

    memset( &echo_client, 0, sizeof(echo_client)); /* Zero out structure */
    echo_client.sin_addr.s_addr = inet_addr("192.168.16.72"); /* set Internet Address (32 bits) */
    echo_client.sin_family = AF_INET; /* Internet Protocol */
    echo_client.sin_port = htons(8080); /* Address port (16 bits) */

    /* Create an instance of socket abstraction */
    int sock = socket( AF_INET /* IPV4 */, SOCK_STREAM /* type=TCP */, 0 /* protocol */);
    if (sock == -1) {
        printf("Error creating an instance of socket.\n");
        return 0;
    }

    /* Estb. a connection to the server */
    int status_connect = connect(sock, (struct sockaddr*) &echo_client, sizeof(echo_client));
    if (status_connect == -1) {
        printf("Error creating a connection.\n");
        return 0;
    } else if (status_connect == 0) {
        printf("Connection created.\n");
    }

    printf("Started chat...\n");
    printf("To close the chat type: \"BYE\"\n");
    char send_buffr[128], recv_buffr[128];

    // start the client
    for( ; ; ) {
        /* take user input the msg */
        printf("Client: ");
        fgets(send_buffr, 128, stdin);
        int StringLen = strlen(send_buffr);

        /* send the msg */
        int sent_bytes = send(sock, send_buffr, StringLen, 0 /* flags */);
        if (sent_bytes == -1) {
            printf("Error sending msg.\nClosing chat...\n");
            break;
        }

        // terminate chat if client says BYE
        if (strcmp( send_buffr, "BYE\n") == 0) {
            printf("Chat closed by client.\n");
            if (close(sock) == 0)
                // close the socket
                printf("Bye\n");
            return 0;
        }

        printf("Server: ");

        /* recieve the msg */
        int recv_bytes = recv(sock, recv_buffr, 128, 0 /* flags */);
        if (recv_bytes == -1) {
            printf("Error recieving msg.\nClosing chat...\n");
            return 0;
        }

        recv_buffr[recv_bytes] = '\0';

        // terminate chat
        if (strcmp( recv_buffr, "BYE\n") == 0) {
            printf("Chat closed by server.\n");
            if (close(sock) == 0)
                // close the socket
                printf("Bye\n");
            return 0;
        }

        printf("%s", recv_buffr);
    }

    if (close(sock) == 0)
        // close the socket
        printf("Bye\n");

    return 0;
}
--------------tcp server--------------
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
	struct sockaddr_in echo_client /* Client Address */,
			   echo_server /* Local Address */;

	/* Construct local address structure */
	memset( &echo_server, 0, sizeof(echo_server)); /* Zero out structure */
	echo_server.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
	echo_server.sin_family = AF_INET; /* Internet address family */
	echo_server.sin_port = htons(8080); /* Local port (16 bits) */

	/* Create an instance of socket abstraction */
	int servSock = socket( AF_INET /* IPV4 */, SOCK_STREAM /* type=TCP */, 0 /* protocol */);
	if (servSock == -1) {
		printf("Error creating an instance of socket.\n");
		return 0;
	}

	/* Bind to the local address */
	if(bind(servSock, (struct sockaddr *) &echo_server, sizeof(echo_server)) < 0) {
		printf("Error in bind().\n");
		close(servSock);
		return 0;
	}

	/* Mark the socket so it will listen for incoming connections */
	if(listen(servSock, 5) < 0) {
		printf("Error in listen().\n");
		close(servSock);
		return 0;
	} else {
		printf("Listening...\n");
	}

	/* Wait for client to connect */
	int clintLen = sizeof(echo_client);
	int clientSock = accept(servSock, (struct sockaddr *) &echo_client, &clintLen);
	if (clientSock < 0) {
		printf("accept() failed.\n");
		close(servSock);
		close(clientSock); // close the socket
		return 0;
	} else {
		printf("accept() success.\n");
	}

	char send_buffr[128], recv_buffr[128];

	printf("Started chat...\n");
	printf("To close chat type: \"BYE\"\n");

	/* start the chat server */
	for( ; ; ) {
		printf("Client: ");
		/* recieve the msg */
		int recv_bytes = recv(clientSock, recv_buffr, 128, 0 /* flags */);
		if (recv_bytes == -1) {
			printf("Error recieving msg.\nClosing chat...\n");
			break;
		}

		recv_buffr[recv_bytes] = '\0'; /* terminate the string */


		// Close chat.
		if (strcmp(recv_buffr, "BYE\n") == 0) {
			printf("Chat closed by client.\n");
			close(clientSock); // close the socket
			close(servSock);
			printf("Bye\n");
			return 0;
		}

		printf("%s", recv_buffr);

		/* get server msg */
		printf("Server: ");
		fgets(send_buffr, 128, stdin);
		int StrSendLen = strlen(send_buffr);

		/* send the msg */
		int sent_bytes = send(clientSock, send_buffr, StrSendLen, 0 /* flags */);
		if (sent_bytes == -1) {
			printf("Error sending msg.\nClosing chat...\n");
			break;
		}

		// Close chat if sever says BYE
		if (strcmp(send_buffr, "BYE\n") == 0) {
			printf("Chat closed by server.\n");
			close(clientSock); // close the socket
			close(servSock);
			printf("Bye\n");
			send(clientSock, send_buffr, StrSendLen, 0 /* flags */);
			return 0;
		}

	}

	close(clientSock); // close the socket
	close(servSock);
	printf("Bye\n");
	return 0;
}
---------------------udp chat client--------------------------
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
	struct sockaddr_in echoServAddr /* Echo server address */,
			   fromAddr /* Source address of echo */;

	/* Create a UDP socket */
	int sock = socket(AF_INET /* IPV4 */, SOCK_DGRAM /* type=UDP */, 0 /* protocol */);
	if (sock < 0) {
		printf("Error creating socket.\n");
		close(sock);
		return 0;
	} else {
		printf("socket created.\n");
	}

	/* Construct the server address structure */
	memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
	echoServAddr.sin_family = AF_INET; /* Internet addr family */
	echoServAddr.sin_addr.s_addr = inet_addr("127.0.0.1" /* serv IP */); /* set internet addr (32 bits) */
	echoServAddr.sin_port = htons(8080); /* Address port(16 bits) */

	printf("Started chat...\n");
	printf("To close the chat type: \"BYE\"\n");
	char send_buffr[128], recv_buffr[128];

	for( ; ; ) {
		/* get user input of the msg */
		printf("Client: ");
		fgets(send_buffr, 128, stdin);
		int sendStrLen = strlen(send_buffr);

		/* Send the string to the server */
		int sent_bytes = sendto(sock, send_buffr, sendStrLen, 0 /* flags */, 
				(struct sockaddr *) &echoServAddr /* destination addr */, sizeof(echoServAddr));
		if (sent_bytes == -1) {
			printf("Error sending msg.\n");
			close(sock);
			return 0;
		} else if (sent_bytes != sendStrLen) {
			printf("sendto() sent a different number of bytes than expected.\n");
		}

		// terminate chat if client says BYE
		if (strcmp( send_buffr, "BYE\n") == 0) {
			printf("Chat closed by client.\n");
			if (close(sock) == 0)
				// close the socket
				printf("Bye\n");
			return 0;
		}

		printf("Server: ");
		/* Recieve response */
		int fromSize = sizeof(fromAddr);
		int recv_bytes = recvfrom(sock, recv_buffr, 128, 0 /* flags */, (struct sockaddr *)
				&fromAddr /* src addr */, &fromSize);
		if (recv_bytes != sendStrLen) {
			printf("recvfrom() failed.\n");
			close(echoServAddr);
			return 0;
		}

		/* null terminate the recieved data */
		recv_buffr[recv_bytes] = '\0';

		// terminate chat
		if (strcmp( recv_buffr, "BYE\n") == 0) {
			printf("Chat closed by server.\n");
			if (close(sock) == 0)
				// close the socket
				printf("Bye\n");
			return 0;
		}


		printf("%s", recv_buffr);
	}
	close(sock);
	return 0;
}
-----------------udp server----------------
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
	struct sockaddr_in echoServAddr /* Local address */,
			   echoClientAddr /* Client address */;

	/* Create a UDP socket */
	int sock = socket(AF_INET /* IPV4 */, SOCK_DGRAM /* type=UDP */, 0 /* protocol */);
	if (sock < 0) {
		printf("Error creating socket.\n");
		close(sock);
		return 0;
	} else {
		printf("socket created.\n");
	}

	/* Construct the local address structure */
	memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
	echoServAddr.sin_family = AF_INET; /* Internet addr family */
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
	echoServAddr.sin_port = htons(8080); /* Local port(16 bits) */

	/* Bind to the local addr */
	if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0) {
		printf("Error in bind().\n");
		close(sock);
		return 0;
	} else {
		printf("bind() success.\n");
	}

	char send_buffr[128], recv_buffr[128];
	int sendStrLen;
	printf("Started chat...\n");
	printf("To close the chat type: \"BYE\"\n");
	for( ; ; ) {
		print("Client: ");
		/* Recieve response from client */
		int clientAddrLen = sizeof(echoClientAddr); // lenght of the client addr
		int recv_bytes = recvfrom(sock, recv_buffr, 128, 0 /* flags */, (struct sockaddr *)
				&echoClientAddr /* src addr */, &clientAddrLen);
		if (recv_bytes < 0) {
			printf("recvfrom() failed.\nClosing chat...\n");
			close(echoServAddr);
			return 0;
		}

		/* null terminate the recieved data */
		recv_buffr[recv_bytes] = '\0';

		// Close chat
		if (strcmp(recv_buffr, "BYE\n") == 0) {
			printf("Chat closed by client.\n");
			close(sock); // close the socket
			printf("Bye\n");
			return 0;
		}


		printf("%s", recv_buffr);

		/* get user input of the msg */
		printf("Server: ");
		fgets(send_buffr, 128, stdin);
		int sendStrLen = strlen(send_buffr);

		/* Send the string to the server */
		int sent_bytes = sendto(sock, send_buffr, recv_bytes, 0 /* flags */, (struct sockaddr *)
				&echoClientAddr /* destination addr */, sizeof(echoClientAddr));
		if (sent_bytes == -1) {
			printf("Error sending msg.\nClosing chat...\n");
			close(sock);
			return 0;
		} else if (sent_bytes != recv_bytes) {
			printf("sendto() sent a different number of bytes than expected.\n");
		}

		// Close chat if sever says BYE
		if (strcmp(send_buffr, "BYE\n") == 0) {
			printf("Chat closed by server.\n");
			close(sock); // close the socket
			printf("Bye\n");
			send(sock, send_buffr, StrSendLen, 0 /* flags */);
			return 0;
		}

	}

	close(sock);
	return 0;
}
------------------concurrent serv------------
#include <stdio.h>
#include <sys/wait.h> /* for waitpid() */
#include <sys/socket.h> /* for socket(), bind() and connect() */
#include <arpa/inet.h> /* for sockaddr_in */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#include <stdlib.h> /* for exit() */

int main() {
    int servSock, clntSock; /* socket descriptors for client and server */
    struct sockaddr_in echoServAddr /* local address */,
                       echoClntAddr /* client address */;

    pid_t processID; /* Process ID from fork() */
    unsigned int childProcCount = 0; /* Number of child processes */

    /* create socket for incoming connections */
    if ((servSock = socket(AF_INET /* IPV4 */, SOCK_STREAM /* type = TCP */, 0 /* protocol */)) < 0) {
        printf("Error creating instance of socket.\n");
        return 0;
    }

    /* constuct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out the structure */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_family = AF_INET; /* Internet Addr family */
    echoServAddr.sin_port = htons(8080); /* Local port (16 bits) */

    /* bind to the local addr */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0) {
        printf("Error in bind().\n");
        close(servSock);
        return 0;
    } else {
        printf("bind() success.\n");
    }

    /* mark the socket so it will listen for incoming connections */
    if (listen(servSock, 5) < 0) {
        printf("Error in listen().\n");
        close(servSock);
        return 0;
    } else
        printf("listen() success.\n");

    int clntLen;
    char sendBuffr[128], recvBuffr[128];
    for( ; ; ) {
        clntLen = sizeof(echoClntAddr);
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0) {
            printf("accept() failed.\n");
            close(servSock);
            close(clntSock);
            return 0;
        } else
            printf("accept() success.\n");

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

        /* Fork child processes and report any error */
        if ((processID = fork()) < 0) {
            printf("fork() failed.\n");
            close(servSock);
            close(clntSock);
            return 0;
        } else if (processID == 0) /* this is a child process */ {
            close(servSock); /* child closes the listening socket */

            /* recieve the msg */
            int recv_bytes = recv(clntSock, recvBuffr, 128, 0 /* flags */);
            if (recv_bytes == -1) {
                printf("Error recieving msg.\n");
                close(servSock);
                close(clntSock); // close the socket
                return 0;
            }

            recvBuffr[recv_bytes] = '\0'; /* terminate the string */
            printf("Message recieved: %s\n", recvBuffr);
            strcpy(sendBuffr, recvBuffr); // ready the send_buffr with the message

            /* send the msg */
            int sent_bytes = send(clntSock, sendBuffr, recv_bytes, 0 /* flags */);
            if (sent_bytes == -1) {
                printf("Error sending msg.\n");
                close(servSock);
                close(clntSock); // close the socket
                return 0;
            } else if (sent_bytes != recv_bytes) {
                printf("send() sent a different number of bytes than expected.\n");
                close(servSock);
                close(clntSock); // close the socket
                return 0;
            } else {
                printf("Message sent.\n");
            }

            exit(0); /* child process terminates */
        }

        printf("with child process' %d\n", (int) processID);
        close(clntSock);
        /* Parent closes child socket descriptor */
        childProcCount++;
        /* Increment number of outstanding child processes */
        while (childProcCount) /* Clean up all zombies */
        {
            processID = waitpid((pid_t) -1, NULL, WNOHANG); /* Nonblocking wait */
            if (processID < 0) /* waitpid() error? */
                printf("waitpid() failed.\n");
            else if (processID == 0) /* No zombie to wait on */
                break;
            else
                childProcCount--; /* Cleaned up after a child */
        }
    }
}
-----------------concurrent client---------------------
#include<arpa/inet.h>
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>

int main() {
    struct sockaddr_in echo_client, echo_server;

    memset( &echo_client, 0, sizeof(echo_client)); /* Zero out structure */
    echo_client.sin_addr.s_addr = inet_addr("127.0.0.1"); /*set Internet Address (32 bits) */
    echo_client.sin_family = AF_INET; /* Internet Protocol */
    echo_client.sin_port = htons(8080); /* Address port (16bits) */

    /* Create an instance of socket abstraction */
    int sock = socket( AF_INET /* IPV4 */, SOCK_STREAM /*type=TCP */, 0 /* protocol */);
    if (sock == -1) {
        printf("Error creating an instance of socket.\n");
        return 0;
    }

    /* Estb. a connection to the server */
    int status_connect = connect(sock, (struct sockaddr*) &echo_client, sizeof(echo_client));
    if (status_connect == -1) {
        printf("Error creating a connection.\n");
        return 0;
    } else if (status_connect == 0) {
        printf("Connection created.\n");
    }
    char send_buffr[128], recv_buffr[128];
    /* take user input the msg */
    printf("Enter the message: ");
    scanf("%s", send_buffr);
    int StringLen = strlen(send_buffr);
    /* send the msg */
    int sent_bytes = send(sock, send_buffr, StringLen, 0 /* flags */);if (sent_bytes == -1) {
        printf("Error sending msg.\n");
        return 0;
    } else if (sent_bytes != StringLen) {
        printf("send() sent a different number of bytes than expected.\n");
        return 0;
    } else {
        printf("Message sent.\n");
    }

    /* recieve the msg */
    int recv_bytes = recv(sock, recv_buffr, 128, 0 /* flags */);
    if (recv_bytes == -1) {
        printf("Error recieving msg.\n");
        return 0;
    }

    recv_buffr[recv_bytes] = '\0';
    printf("Recieved message: %s\n", recv_buffr);
    close(sock); // close the socket
    return 0;
}
----------------time-----------------------
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    time_t t;
    struct sockaddr_in echo_server, client_name;
    memset(&echo_server, 0, sizeof(echo_server));
    echo_server.sin_addr.s_addr = inet_addr("127.0.0.1"); /** assign the localIP **/
    echo_server.sin_family = AF_INET;
    echo_server.sin_port = htons(8888);

    // Create the socket: socket descriptor
    int s = socket(AF_INET /* family: IPV4 */, SOCK_STREAM /* type: TCP */, 0 /* PROTOCOL */);

    // If socket creation failed
    if(s == -1) {
        printf("Error creating socket.\n");
        int status = close(s);
        if (status == 0)
            printf("Socket closed!\n");
        return 0;
    }

    int status = bind(s, (struct sockaddr *) &echo_server, sizeof(echo_server));
    if(status == -1) {
        printf("Bind unsuccessful.\n");
    } else {
        printf("Bind successful.\n");
    }

    status = listen(s, 3 /* queuelen */);
    printf("Server is listening...\n");

    int client_size = sizeof(client_name);
    int status_accept = accept(s, (struct sockaddr *) &client_name, &client_size);

    if(status_accept == -1) {
        // message not recieve
        printf("Connection failed.\n");
    } else {
        printf("Connection successful.\n");
    }

    // recieve the message from the client
    char buf_recv[128];
    int count = recv(status_accept, buf_recv, sizeof(buf_recv), 0 /* flags */);
    buf_recv[count] = '\0';

    if (count == -1) {
        printf("Message not recieved!\n");
    } else {
        printf("Message recieved: ");
        printf("%s", buf_recv);
    }

    // send the message back to the client
    char *buf_send;
    t = time(NULL); // get the time
    buf_send = ctime(&t);
    int send_str_len = strlen(buf_send);
    count = send(status_accept, buf_send, send_str_len, 0 /* flags */);

    if (count != -1) {
        printf("Message sent!\n");
    } else if (count == -1) {
        // If message not sent
        printf("Message not sent!\n");
    }

    status = close(s);
    if (status == 0)
        printf("Socket closed!\n");

    return 0;
}
----------------file trnsfer clnt----------------
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct sockaddr_in echoServer;

int main() {
    memset(&echoServer, 0, sizeof(echoServer));
    echoServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    echoServer.sin_family = AF_INET;
    echoServer.sin_port = htons(8888);


    // Create the socket: socket descriptor
    int s = socket(AF_INET /* family: IPV4 */, SOCK_STREAM /* type: TCP */, 0 /* PROCTOCOL */);

    // If socket creation failed
    if(s == -1) {
        printf("Error creating socket.\n");
        int status = close(s);
        if (status == 0)
            printf("Socket closed!\n");
        return 0;
    }

    // create the connection
    int status = connect(s /* socket descriptor */, (struct sockaddr *) &echoServer, sizeof(echoServer));
    if(status == -1) {
        printf("Connection failed.\n");
    } else {
        printf("Connection successful.\n");
    }

    // get the data from the user
    char buf_send[128], ch;
    int c = 0;
    
    /* copy from the file */
    printf("Client: ");
    FILE *f;
    f = fopen("main_file.txt","r");

    while( (ch=fgetc(f)) != EOF) {
        buf_send[c++]=ch;
    }

    int StringLen = strlen(buf_send);

    /* send the msg */
    int sent_bytes = send(s, buf_send, StringLen, 0);
    if (sent_bytes == -1) {
        printf("Error sending msg.\nClosing chat...\n");
    }

    printf("File transfer success: main_file.txt\n");
    fclose(f);

    status = close(s);
    if (status == 0)
        printf("Socket closed!\n");

    return 0;
}
--------------------file trnsfr serv---------------------
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    time_t t;
    struct sockaddr_in echo_server, client_name;
    memset(&echo_server, 0, sizeof(echo_server));
    echo_server.sin_addr.s_addr = inet_addr("127.0.0.1"); /** assign the localIP **/
    echo_server.sin_family = AF_INET;
    echo_server.sin_port = htons(8888);

    // Create the socket: socket descriptor
    int s = socket(AF_INET /* family: IPV4 */, SOCK_STREAM /* type: TCP */, 0 /* PROTOCOL */);

    // If socket creation failed
    if(s == -1) {
        printf("Error creating socket.\n");
        int status = close(s);
        if (status == 0)
            printf("Socket closed!\n");
        return 0;
    }

    int status = bind(s, (struct sockaddr *) &echo_server, sizeof(echo_server));
    if(status == -1) {
        printf("Bind unsuccessful.\n");
    } else {
        printf("Bind successful.\n");
    }

    status = listen(s, 3 /* queuelen */);
    printf("Server is listening...\n");

    int client_size = sizeof(client_name);
    int status_accept = accept(s, (struct sockaddr *) &client_name, &client_size);

    if(status_accept == -1) {
        // message not recieve
        printf("Connection failed.\n");
    } else {
        printf("Connection successful.\n");
    }

    // recieve the message from the client
    char buf_recv[128];
    int count = recv(status_accept, buf_recv, sizeof(buf_recv), 0 /* flags */);
    buf_recv[count] = '\0';

    // copy the file in new file
    FILE *f;
    f = fopen("copy_file.txt","w");
    fprintf(f, "%s", buf_recv);
    if (count == -1) {
        printf("Error recieving msg.\nClosing chat...\n");
    }

    printf("Server: File recieved: main_file.txt\n");
    printf("New file created: copy_main.txt\n");

    fclose(f); // close the file

    status = close(s);
    if (status == 0)
        printf("Socket closed!\n");

    return 0;
}
----------------brdcast sender-------------
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

int main(int argc, char *argv[])
{
    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    char sendString[20];                 /* String to broadcast */
    int broadcastPermission;          /* Socket opt to set permission to broadcast */
    unsigned int sendStringLen;       /* Length of string to broadcast */

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        printf("socket() failed\n");
	return 0;
    }

    /* Set socket to allow broadcast */
    broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission)) < 0) {
        printf("setsockopt() failed\n");
	close(sock);
	return 0;
    }

    /* Construct local address structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = inet_addr("10.0.2.255");/* Broadcast IP address */
    broadcastAddr.sin_port = htons(8800);         /* Broadcast port */

    /* Take the message to send from the user */
    printf("Enter the message: ");
    fgets( sendString, 20, stdin);
    sendStringLen = strlen(sendString);  /* Find length of sendString */
    for (;;) /* Run forever */ {
         /* Broadcast sendString in datagram to clients every 3 seconds*/
         if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen) {
             printf("sendto() sent a different number of bytes than expected\n");
	     return 0;
	 }

        sleep(3);   /* Avoids flooding the network */
    }
}
----------------brdcst receivr-------------------
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXRECVSTRING 255  /* Longest string to receive */

void DieWithError(char *errorMessage);  /* External error handling function */

int main(int argc, char *argv[])
{
    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast Address */
    char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
    int recvStringLen;                /* Length of received string */

    /* Create a best-effort datagram socket using UDP */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        printf("socket() failed\n");
	return 0;
    }

    /* Construct bind structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* Any incoming interface */
    broadcastAddr.sin_port = htons(8800);      /* Broadcast port */

    /* Bind to the broadcast port */
    if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0) {
        printf("bind() failed\n");
	return 0;
    }

    /* Receive a single datagram from the server */
    if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0) {
        printf("recvfrom() failed\n");
	return 0;
    }

    recvString[recvStringLen] = '\0';
    printf("Received: %s\n", recvString);    /* Print the received string */
    
    close(sock);
    exit(0);
}
--------------------Stop and wait ARQ--------------------------
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#define size 200
int main() {	
int i,j;
int noframes,x,x1=10,x2;
printf("Enter the number of frames:");
scanf("%d",&noframes);
for(i=0;i<size;i++)
rand();	
//noframes=rand()/200;	
i=1;	
j=1;	
noframes = noframes / 8;
printf("\n number of frames is %d",noframes);
	while(noframes>0) {
		printf("\nsending frame %d",i);
		srand(x1++);
		x = rand()%10;
		if(x%2 == 0) {
			for (x2=1; x2<2; x2++) {
				printf("\nwaiting for %d seconds\n", x2);
				sleep(x2);
			}
			printf("\nsending frame %d",i);
			srand(x1++);
			x = rand()%10;
		}
		printf("\nack for frame %d",j);
		noframes-=1;
		i++;
		j++;
	}
	printf("\n end of stop and wait protocol \n");
	exit(0);
	return 0;
}
