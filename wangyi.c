//命令格式: ./可执行文件 输入.uc! 输出.mp3
//./可执行文件 输入.uc!

//在android gcc/manjaro linux gcc 编译通过
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
int main(int argc,char* arg[]){
    char temp_bytes[1024];
    unsigned int read_count,wrote_size=0;
    if(argc<2){
        return 1;
    }
    FILE* i=fopen(arg[1],"r");
    FILE* o=fopen(arg[2],"w");
    if(!i){
        printf("Cannot open file!\r\n");
        return 1;
    }
    printf("InputFile:%s\r\n",arg[1]);
    if(!o){
    	const char *add=".mp3\0";
    	char len=strlen(arg[1]);
		char *n=(char *)malloc(len+4+1);
		memcpy(n,arg[1],len);
		memcpy(n+len,add,5);
		printf("OutputFile:%s\r\n",n);
    	o=fopen(n,"w");
    	free(n);
    }else
    	printf("OutputFile:%s\r\n",arg[2]);
    
    while((read_count=fread(temp_bytes,sizeof(char),1024,i))>0){
        unsigned int p;
        wrote_size+=read_count;
        //printf("Cracking position:%u\r\n",wrote_size);
        for(p=0;p<read_count;p++){
            temp_bytes[p]^=0xa3;
        }

        fwrite(temp_bytes,sizeof(char),read_count,o);
        fflush(o);
        if(read_count!=1024){
            printf("This file has been cracked!\r\n");
            break;
        }
    }
    printf("Done!\r\n");
    fclose(i);
    fclose(o);
} 

