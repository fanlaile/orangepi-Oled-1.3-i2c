/***************************************************************
Copyright  2024-2029. All rights reserved.
文件名     : test_18_oled.c
作者       : tangmingfei2013@126.com
版本       : V1.0
描述       : 验证dev_oled.c 
其他       : 无
日志       : 初版V1.0 2024/02/23
***************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/fs.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "drv_oled.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <unistd.h>

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_LINE_LEN 32

double temp = 0;
char buf[MAX_LINE_LEN];
char ip_buf[2][40]={};

void get_ip(void)
{    
    char i=0;
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char ip_address[INET_ADDRSTRLEN];
    
    if(*ip_buf[1]!=NULL)
    {
        //printf("%s\n", ip_buf[1]);
        return;
    }

    if (getifaddrs(&ifap) == -1) {
        perror("getifaddrs() error");
        return -1;
    }

    for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            inet_ntop(AF_INET, &sa->sin_addr, ip_address, sizeof(ip_address));
            //printf("%s: %s\n", ifa->ifa_name, ip_address);
           
            sprintf(ip_buf[i++],"%s",ip_address);
              
        }
    }

    freeifaddrs(ifap);
}



void test_oled( void )
{
    int fd;
    char str[7];
    
    fd = open(TEMP_PATH, O_RDONLY);
    if (fd < 0)
    {
        printf("open error!\n");
        return 0;
    }

    if(read(fd, buf, MAX_LINE_LEN) < 0)
    {
        printf("read error!\n");
        return 0;
    }
    get_ip();
    temp = ((double)atoi(buf))/1000;
    sprintf(str, "%.2f", temp);
    //printf("CPU temperature: %.2f\n", temp);
    
    oled_setCharSize( FONT_16 );  
    oled_printfString(1,0,(unsigned char *)"1.3' Orangepi ");  
    
    oled_setCharSize( FONT_12 );
    oled_printfString(0,3,(unsigned char*)"IP");
    oled_printfString(18,3,(unsigned char*)ip_buf[1]);
    oled_printfString(1,5,(unsigned char*)"CPU Temp:");  
    oled_printfString(75,5,(unsigned char*)str);
}
 
int main(void)
{
    int set;
    set = oled_init();
        if( set < 0){
            printf("initial oled failure.\n");
            return -1;
        }
    
   //get_ip();
    while(1)
    {
    
       
        
        
        
        
        test_oled();
        //oled_release();
        sleep(1);
    }
 
    return 0;
}
