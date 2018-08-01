#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <string.h>

int step=0;
#define MEMSIZE 100000000
long memory[MEMSIZE];


void dumpRegs(int pid){
	printf("------------------------\n");
	printf("Step: %d\n",step);
	struct user_regs_struct regs;
	ptrace(PTRACE_GETREGS,pid,NULL, &regs);
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

void steps(int pid,int steps){
	int status;
	for(int i=0;i<steps;i++){
		ptrace(PTRACE_SINGLESTEP,pid,NULL,NULL);
		waitpid(pid,&status,0);
		step++;
	}
	dumpRegs(pid);
}

//For reference
void loadMemory(int pid,long regions[17][2]){
	int counter=0;
	for(int j=0;j<17;j++){
		for(int i=0;i<4096;i++){
			long data=ptrace(PTRACE_PEEKDATA,pid,regions[j][0]+i,NULL);
			memory[counter]=data;
			counter++;
			//printf("%016lx\t",data);
		}
	}
	for(int i=0;i<MEMSIZE;i++){
		if(memory[i]!=0 && memory[i]!=-1){
			printf("%016lx\n",memory[i] & 0xFFFF);
		}
	}
	printf("DONE\n");
	for(int i=0;i<MEMSIZE;i++){
		if((memory[i] & 0xFFFF) == 0x1234){
			printf("%016lx\n",memory[i]);
		}
	}
	printf("DONE\n");
}



void findHeap(int pid,long *heapStart, long *heapEnd){
	long addr=-1;
	//get file from pid
	char pids[255];
	char fName[255]="/proc/";
	sprintf(pids,"%d",pid);
	strcat(fName,pids);
	strcat(fName,"/maps");
	FILE* f=fopen(fName,"r");
	//printf("%s\n",fName);
	for(int i=0;i<17;i++){
		//get line
		char buf[255];
		fgets(buf,255,f);
		//printf("%s\n",buf);
		if(strstr(buf,"[stack]")!=NULL){
			printf("%s\n",buf);
			*heapStart=strtol(buf,NULL,16);
			char * next=strstr(buf,"-");
			*heapEnd=strtol(next+1,NULL,16);
		}
	}
	fclose(f);
}

void find(int pid,long start,long end){
	getchar();
	char input[255];
	fgets(input,255,stdin);
	long counter=0;
	for(long i=start;i<end;i++){
		long data=ptrace(PTRACE_PEEKDATA,pid,i,NULL);
		memory[counter]=data;
		counter++;
	}
	for(int i=0;i<MEMSIZE;i++){
		if(memory[i]!=0 && memory[i]!=-1){
			if((memory[i] & 0xFFFF) == strtol(input,NULL,16)){
				printf("DATA: %016lx-ADDRESS: %016lx\n",memory[i],i);
			//printf("%016lx\n",memory[i] & 0xFFFF);
			}
		}
	}
	printf("DONE-%s\n",input);
}

int main(int argc, char **argv){
	for(int i=0;i<MEMSIZE;i++)memory[i]=0;
	int pid=atoi(argv[1]);//the pid of the process
	ptrace(PTRACE_ATTACH,pid);//attach to process
	waitpid(pid,NULL,0);
	printf("PID IS %d\n",pid);

	//Get memory regions
	long heapStart=0;
	long heapEnd=0;
	findHeap(pid,&heapStart,&heapEnd);
	printf("HEAP LOCATED AT %lx\n",heapStart);
	printf("GOES UNTIL %lx\n",heapEnd);

	//Mainloop
	char c='s';
	int num=1;
	int running=1;
	while(running==1){
		char tmp=getchar();
		if(tmp!='\n')c=tmp;
		if(c=='q')running=0;
		if(c=='k')kill(pid,9);
		if(c=='s')steps(pid,num);
		if(c=='f')find(pid,heapStart, heapEnd);
		if(c=='n'){
			char buf[255];
			fgets(buf,255,stdin);
			num=atoi(buf);
		}
	}

	//Detach
	printf("%d",ptrace(PTRACE_CONT,pid,NULL,NULL));
	ptrace(PTRACE_DETACH,pid);//attach to process
	return 0;
}

