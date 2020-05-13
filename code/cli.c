#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

char p,q,n,t,flag,e[100],d[100],j,m[100],i;

char temp[100],en[100];

char msg[100];

int prime(long int);

void ce();

long int cd(long int);

void encrypt();

void decrypt();

int main()
{
	
    int sd,con,port,i,Res;
    char content[30];
    struct sockaddr_in cli;

    if((sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
    {
        printf("\nSocket problem");
        return 0;
    }

    bzero((char*)&cli,sizeof(cli));
    cli.sin_family = AF_INET;
    printf("ENTER PORT NO:\n");
    scanf("%d",&port);
    cli.sin_port=htons(port);
    cli.sin_addr.s_addr=htonl(INADDR_ANY);

    con=connect(sd,(struct sockaddr*)&cli,sizeof(cli));

    if(con==-1)
    {
        printf("\nConnection error");
        return 0;
    }
   //  if(fork())
   //    {
   //      printf("enter msg");
   //      scanf("%s",content);
   //        while(strcmp(content,"exit")!=0)
   //            {
   //             send(sd,content,30,0);
   //              scanf("%s",content);
   //            }
   //   }
   // else
   //     {
   //        i=recv(sd,content,30,0);
   //     while(strcmp(content,"exit")!=0)
   //      {
   //          printf("\nServer: %s\n",content);
   //          i=recv(sd,content,30,0);
   //      }
   //
   //
   // }
   i=recv(sd,d,100,0);
   if(i==0){
     printf("No d array value received");
     return 1;
   }
   i=recv(sd,temp,100,0);
   if(i==0){
     printf("No temp array value received");
     return 1;
   }
   i=recv(sd,en,100,0);
   if(i==0){
     printf("No en array value received");
     return 1;
   }

   decrypt();
    close(sd);
      return 0;

}
int prime(long int pr) {

	int i;

	j=sqrt(pr);

	for (i=2;i<=j;i++) {

		if(pr%i==0)

		    return 0;

	}

	return 1;

}

void ce() {

	int k;

	k=0;

	for (i=2;i<t;i++) {

		if(t%i==0)

		    continue;

		flag=prime(i);

		if(flag==1&&i!=p&&i!=q) {

			e[k]=i;

			flag=cd(e[k]);

			if(flag>0) {

				d[k]=flag;

				k++;

			}

			if(k==99)

			        break;

		}

	}

}

long int cd(long int x) {

	long int k=1;

	while(1) {

		k=k+t;

		if(k%x==0)

		    return(k/x);

	}

}

void encrypt() {

	long int pt,ct,key=e[0],k,len;

	i=0;

	len=strlen(msg);

	while(i!=len) {

		pt=m[i];

		pt=pt-96;

		k=1;

		for (j=0;j<key;j++) {

			k=k*pt;

			k=k%n;

		}

		temp[i]=k;

		ct=k+96;

		en[i]=ct;

		i++;

	}

	en[i]=-1;

	printf("\nTHE ENCRYPTED MESSAGE IS\n");

	for (i=0;en[i]!=-1;i++)

	printf("%c",en[i]);

}

void decrypt() {

	char ct,pt,key=d[0],k;

	i=0;

	while(en[i]!='/0') {

		ct=temp[i];

		k=1;

		for (j=0;j<key;j++) {

			k=k*ct;

			k=k%n;

		}

		pt=k+96;

		m[i]=pt;

		i++;

	}

	m[i]=-1;

	printf("\nTHE DECRYPTED MESSAGE IS\n");

	for (i=0;m[i]!=-1;i++)

	printf("%c",m[i]);

}
