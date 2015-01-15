#include<stdio.h> 			/* perror */
#include<stdlib.h>			/* exit	*/
#include<sys/types.h>		/* WNOHANG */
#include<sys/wait.h>		/* waitpid */
#include<string.h>			/* memset */
#include "common.h" 	/* socket layer wrapper */
#include<time.h>

#define	true		1
#define false		0

#define PORT 		9876 	/* connect server port */
#define MAXDATASIZE 1000

int main(int argc, char *argv[])
{
	int sockfd;
	char buf[MAXDATASIZE];
	struct hostent *he; /* own message */
	struct sockaddr_in their_addr; /* server address */
	int nrecv;
        time_t t_start,t_end;
        t_start=time(NULL);
	/*if (argc != 2) 
	{
		fprintf(stderr,"usage: client hostname\n");
		exit(1);
	}*/
	
	/* get the host info */
	if ((he=Gethostbyname(argv[1])) == NULL) 
	{
		perror("gethostbyname");
		exit(1);
	}
	
	if ((sockfd=Socket(AF_INET,SOCK_STREAM,0))==-1) 
	{
		perror("socket");
		exit(1);
	}
	else
        {
            printf("clientfd create succeed!\n");
        }
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = Htons(PORT); /* short, NBO */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr_list[0]);
	memset(&(their_addr.sin_zero),0,8);

        printf("begin timing......\n");
	
	if (Connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) 
	{
		perror("connect");
		exit(1);
	}
        else
        {
            printf("connect succeed!\n");
        }
	FILE *fp;
    if((fp=fopen(Outputpath,"w"))==NULL)
    {
        perror("fopen");
        return false;
    }
        printf("sending......\n");
	while((nrecv=recv(sockfd,buf,MAXDATASIZE,0))>0)
	{
		fwrite(buf,1,nrecv,fp);
	}
	fclose(fp);
	printf("sending succeed!\n");

	close(sockfd);
	t_end=time(NULL);
        printf("timing end!\n");
        printf("common time:%.0fs\n",difftime(t_end,t_start));
	return true;

}
