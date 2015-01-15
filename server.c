#include<stdio.h> 			/* perror */
#include<stdlib.h>			/* exit	*/
#include<sys/types.h>		/* WNOHANG */
#include<sys/wait.h>		/* waitpid */
#include<string.h>			/* memset */
#include<time.h>
#include "common.h" 	/* socket layer wrapper */

#define	true		1
#define false		0

#define MYPORT 		9876                /* listen port */ 
#define BACKLOG 	10                 	/* length of listen recv quene */
#define MAXDATASIZE     1000

int main() 
{
	int sockfd, new_fd;            /* listen port£¬data port */
	struct sockaddr_in sa;         /* server address */ 
	struct sockaddr_in their_addr; /* client address */ 
	int sin_size;
	char buf[MAXDATASIZE];
	int nread;
        time_t t_start,t_end;
	
	if ((sockfd = Socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket"); 
		exit(1); 
	}
	else
        {
            printf("serverfd create succeed!\n");
        }
	sa.sin_family = AF_INET;
	sa.sin_port = Htons(MYPORT);     
	sa.sin_addr.s_addr = INADDR_ANY;  
	memset(&(sa.sin_zero),0, 8); 
	
	if (Bind(sockfd, (struct sockaddr *)&sa, sizeof(sa)) == -1) 
	{
		perror("bind");
		exit(1);
	}
	else
        {
            printf("bind succeed!\n");
        }
	if (Listen(sockfd, BACKLOG) == -1) 
	{
		perror("listen");
		exit(1);
	}
        else
        {
            printf("begin listening......\n");
        }
        	
	sin_size = sizeof(struct sockaddr_in);
	new_fd = Accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
	if (new_fd == -1) 
	{
		perror("accept");
	}
	else
        {
            printf("connect succeed!\n");
        }	
	printf("Got connection from %s\n", Inet_ntoa(their_addr.sin_addr));

	FILE *fp;

    if((fp=fopen(Inputpath,"r"))==NULL)
    {
        perror("fopen");
        return false;
    }
        printf("begin timing......\n");
        t_start=time(NULL);
        printf("recving......\n");
	do{
		nread=fread(buf,1,MAXDATASIZE,fp);
		send(new_fd,buf,nread,0);
	}while(nread>0);
	fclose(fp);
        printf("receving succeed!\n");
        printf("timing end!\n");
        t_end=time(NULL);
        printf("time of transmission:%.0fs\n",difftime(t_end,t_start));
	close(new_fd);
	close(sockfd);
	return true;
}
