#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct face{
	int w,x,y,z;
};

struct vector{
	double x,y,z;
};

void printFace(struct face f){
	printf("%d,%d,%d,%d\n",f.w,f.x,f.y,f.z);
}

void printVector(struct vector v){
	printf("%f,%f,%f\n",v.x,v.y,v.z);
}

double extractDouble(char buff[]){
	int i=0;
	int neg=0;
	int start=0;
	int dec=0;
	int end=0;
	while(buff[i]=='v' || buff[i]=='f' || buff[i]==' ')i++;
	if(buff[i]=='-'){
		i++;
		neg=1;
	}
	start=i;
	while(buff[i]!='.'){
		i++;
	}
	dec=i;
	while(buff[i]!=' '){
		i++;
	}
	end=i;
	double sum=0;
	for(int j=start;j<dec;j++){
		printf("%c\n",buff[i]);
		//sum*=10;
		//sum+=buff[i]-48;
	}
	return sum;


//	int i=0;
//	double sum=0;
//	int dec=0;
//	int neg=0;
//	int start=0;
//	while(buff[i]=='v' || buff[i]=='f' || buff[i]==' ')i++;
//	if(buff[i]=='-'){
//		neg=1;
//		i++;
//	}
//	start=i;
//	while(buff[i]!=' ' && buff[i]!='/'){
//		//printf("%c", buff[i]);
//		if(buff[i]!='.'){
//			sum*=10;
//			sum+=buff[i]-48;
//		}else{
//			dec=i;
//		}
//		i++;
//	}
//	for(int j=0;j<dec+start;j++)sum/=10.0;
//	if(neg)sum*=-10.;
//	return sum;
}

void process(char buff[]){
	printf("%s",buff);
	//char b[]="12 ";
	//printf("%f\n",extractDouble(b));
	printf("%f\n",extractDouble(buff));
//	int i=0;
//	struct face f={0,0,0,0};
//	if(buff[i]=='f'){
//		i+=2;
//		while(buff[i]!=0){
//			while(buff[i]!='/'){
//				f.x*=10;
//
//				f.x+=buff[i]-97;
//				i++;
//			}
//			//if(buff[i]=='/')while(buff[i]!=' '&&buff[i]!='\n')i++;
//			//putchar(buff[i]);
//			printFace(f);
//			i++;
//		}
//	}
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
