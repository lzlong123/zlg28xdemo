#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <asm/ioctls.h>

#define SERVPORT (80)
char *findValueByName(char *source, char *name);
int   streamProcess(char *recebuffer);
void Buzzer(char *s);
void Led(char *s);
int main(int argc, char *argv[])
{
	int i,j, sockfd,recebytes;
	struct hostent *h;
	struct sockaddr_in serv_addr;
	char hostname[] = "refenweb.chinacloudsites.cn";
	char httprequest[] = "GET http://refenweb.chinacloudsites.cn/api/devices/3 HTTP/1.1\r\nHost:refenweb.chinacloudsites.cn\r\n\r\n";
	char recebuffer[1024];
	printf("Your domain :%s\n",hostname);
	printf("Your httpRequest:\n%s",httprequest);
	if((h=gethostbyname(hostname))==NULL)
	{
		printf("can't get IP\n");
		exit(1);
	}
	printf("HostName  :%s\n",h->h_name);
	serv_addr.sin_addr = *((struct in_addr *)h->h_addr_list[0]);
	const char *ip = inet_ntoa(serv_addr.sin_addr);
	//printf("IP Address:%s   %x\n", ip, serv_addr.sin_addr);
	printf("IP Address:%s   \n", ip);
	if(-1 == (sockfd = socket(AF_INET, SOCK_STREAM,0)))
	{
		printf("socket error\n");
		exit(0);
	}
	//bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERVPORT);
	serv_addr.sin_addr = *((struct in_addr *)h->h_addr_list[0]);

	i = j = 0;
	while(1)
	{
		i++;
		if(i>1)
			close(sockfd);
			//close(sockfd);
		if(-1 == (sockfd = socket(AF_INET, SOCK_STREAM,0)))
		{
			printf("socket error\n");
			exit(0);
		}
		usleep(500000);
		//printf("Connecting to :%s ", ip);
		if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
		{
			printf("connect error\n");
			continue;
		}


		if(-1 == write(sockfd,httprequest,strlen(httprequest)))
		{
			printf("send error\n");
			continue;
		}
		//printf("HTTP Request sent\n");

		memset(recebuffer,0,1024);
		if(-1 == (recebytes = read(sockfd, recebuffer, 1024)))
		{
			printf("received error\n");
			continue;
		}
		//printf("Received data:\r\n%s\n",recebuffer);
		if(-1 ==streamProcess(recebuffer))
			printf("find nothing");
		/*
		if(NULL == (p=findValueByName(recebuffer,"Name")))
			printf("find nothing\n");
		else
			printf("Name : %s\n",p);
		*/
		j++;
		printf("sk:%d  total %d success %d \n",sockfd, i , j);
	}

	return 0;
}

char nbuzzer[] = {"Buzzer"};
char nled[] = {"Led"};
//const char nmotor[] = {"Motor"};
int streamProcess(char *recebuffer)
{
	char *p;
	if(NULL == (p=findValueByName(recebuffer,nbuzzer)))
		return -1;
	printf("Buzzer:%s\n",p);
	Buzzer(p);
	if(NULL == (p=findValueByName(recebuffer,nled)))
		return -1;
	printf("Led:%s\n",p);
	Led(p);
	return 1;
}

char buffer[100];
char *findValueByName(char *source, char *name)
{
    char *p,*p2;
    int i,j,k;
    memset(buffer,0,100);
    if((p = strstr(source,name)) == NULL)
        return NULL;
    if((p = strchr(p,':')) == NULL)
        return NULL;
    p++;
    if((p2 = strchr(p, '}')) == NULL)
        return NULL;
    j = (int)(p2) - (int)(p);
    memset(buffer,0,100);
    k=0;
    for(i=0;i<j;i++)
    {
        if(*(p+i)=='\"')
            continue;
        buffer[k] = *(p+i);
        k++;
    }
    buffer[k] = '\0';
    return buffer;
}

void Buzzer(char *s)
{
	if(strcmp("ON",s))
		system("echo 0 > /sys/class/leds/beep/brightness");
	else
		system("echo 1 > /sys/class/leds/beep/brightness");
}

void Led(char *s)
{
	if(strcmp("ON",s))
		system("echo 0 > /sys/class/leds/led-err/brightness");
	else
		system("echo 1 > /sys/class/leds/led-err/brightness");
}
