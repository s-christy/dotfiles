#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

int pid;
int status;
int step=0;
struct user_regs_struct regs;

void memoryRegions();
void printRegs();
void child();
void stepn(int n);
long regions[100][2];

void lookForValue(int val){
	int c=0;
	while(regions[c][0]!=0){
		printf("%lx\n",regions[c][0]);
		c++;
	}
}

void parent(){
	memoryRegions();
	if(ptrace(PTRACE_ATTACH,pid,NULL,NULL)==-1)printf("ATTACH ERROR\n");
	else printf("ATTACHED\n");

	int n=1;
	char c='_';
	while(c!='q'){
		if(c=='r'){
			if(ptrace(PTRACE_GETREGS,pid,NULL,&regs)==-1)printf("GETREGS ERROR\n");
			else printRegs(regs);
		}else if(c=='s'){
			stepn(n);
		}else if(c=='n'){
			char buf[255];
			fgets(buf,255,stdin);
			n=atoi(buf);
			puts(buf);
		}
		char tmp=getchar();
		if(tmp!='\n')c=tmp;
	}

	if(ptrace(PTRACE_DETACH,pid,NULL,NULL)==-1)printf("DETACH ERROR\n");
	else printf("DETACHED\n");
}

int main(int argc, char *argv[]){
	pid=fork();			//fork the process
	if(pid==0)child();	//start the child
	usleep(5000);		//wait before starting the parent
	if(pid!=0)parent();	//start the parent
	kill(pid,9);		//kill child
	exit(EXIT_SUCCESS);	//exit safely
}

void printRegs(){
	printf("------------------------\n");
	printf("Step: %d\n",step);
	printf("cs       | %016lx-Should be unused in x86-64\n",regs.cs);
	printf("ds       | %016lx\n",regs.ds);
	printf("eflags   | %016lx\n",regs.eflags);
	printf("es       | %016lx\n",regs.es);
	printf("fs       | %016lx\n",regs.fs);
	printf("fs_base  | %016lx\n",regs.fs_base);
	printf("gs       | %016lx\n",regs.gs);
	printf("gs_base  | %016lx\n",regs.gs_base);
	printf("orig_rax | %016lx\n",regs.orig_rax);
	printf("ss       | %016lx-Should be unused in x86-64\n",regs.ss);
	printf("\n");
	printf("r8       | %016lx\n",regs.r8);
	printf("r9       | %016lx\n",regs.r9);
	printf("r10      | %016lx\n",regs.r10);
	printf("r11      | %016lx\n",regs.r11);
	printf("r12      | %016lx\n",regs.r12);
	printf("r13      | %016lx\n",regs.r13);
	printf("r14      | %016lx\n",regs.r14);
	printf("r15      | %016lx\n",regs.r15);
	printf("\n");
	printf("rax      | %016lx\n",regs.rax);
	printf("rbp      | %016lx\n",regs.rbp);
	printf("rbx      | %016lx\n", regs.rbx);
	printf("rbx      | %016lx\n",regs.rbx);
	printf("rcx      | %016lx\n",regs.rcx);
	printf("rdi      | %016lx-Destination Index\n",regs.rdi);
	printf("rdx      | %016lx\n",regs.rdx);
	printf("rip      | %016lx-Instruction Pointer\n",regs.rip);
	printf("rsi      | %016lx-Source Index\n",regs.rsi);
	printf("rsp      | %016lx-Stack Pointer\n",regs.rsp);
}

void child(){
	int x=0;
	while(1){
		//printf("%x\n",x);
		x=0x55;
		usleep(5);
		x=0x85;
		usleep(5);
		x=0xa5;
		usleep(5);
		x=0x50;
		usleep(5);
	}
}

void stepn(int n){
	int i=0;
	for(i=0;i<n;i++){
		if(ptrace(PTRACE_SINGLESTEP,pid,NULL,NULL)==-1)printf("STEP ERROR\n");
		waitpid(pid,&status,0);
		step++;
	}
	if(ptrace(PTRACE_GETREGS,pid,NULL,&regs)==-1)printf("GETREGS ERROR\n");
	else printRegs(regs);
}

void memoryRegions(){
	for(int i=0;i<100;i++){regions[i][0]=0;regions[i][1]=0;}
	char pids[255];
	char fName[255]="/proc/";
	sprintf(pids,"%d",pid);
	strcat(fName,pids);
	strcat(fName,"/maps");
	FILE* f=fopen(fName,"r");
	char buf[255];
	int count=0;
	while(!feof(f)){
		fgets(buf,255,f);
		long a=strtol(buf,NULL,16);
		char *next=strstr(buf,"-");
		long b=strtol(next+1,NULL,16);
		regions[count][0]=a;
		regions[count][1]=b;
		count++;
		//printf("%s",&buf);
		//printf("%lx-",a);
		//printf("%lx\n",b);
	}
	fclose(f);
}

