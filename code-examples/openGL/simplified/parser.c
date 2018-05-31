#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct face{
	int w;
	int x;
	int y;
	int z;
};

struct vector{
	int x;
	int y;
	int z;
};

void printFace(struct face f){
	printf("%d,%d,%d,%d\n",f.w,f.x,f.y,f.z);
}

void printVector(struct vector v){
	printf("%d,%d,%d\n",v.x,v.y,v.z);
}

void process(char buff[]){
	printf("%s",buff);
	int i=0;
	struct face f={0,0,0,0};
	if(buff[i]=='f'){
		i+=2;
		while(buff[i]!=0){
			while(buff[i]!='/'){
				f.x*=10;
				
				f.x+=buff[i]-97;
				i++;
			}
			//if(buff[i]=='/')while(buff[i]!=' '&&buff[i]!='\n')i++;
			//putchar(buff[i]);
			printFace(f);
			i++;
		}
	}
}

int main(int argc,char *argv[]){
	FILE *f=fopen("sample2.obj","r");
	char buf[100];
	char c;
	//while(c!='#')c=fgetc(f);
	while(fgets(buf,100,f)!=NULL){
		if(buf[0]=='v'||buf[0]=='f'){
			if(buf[1]!='n'){
				process(buf);
			}
		}
	}
	return 0;
}
