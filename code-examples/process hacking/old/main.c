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

int x=0;
#define MEMSIZE 10000000
long memory[MEMSIZE];

void dumpRegs(int pid){
	printf("------------------------\n");
	printf("Step: %d\n",x);
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

void singleStep(int pid,int steps){
	int status;
	for(int i=0;i<steps;i++){
		ptrace(PTRACE_SINGLESTEP,pid,NULL,NULL);
		waitpid(pid,&status,0);
		x++;
	}
	dumpRegs(pid);
}

void getMemoryRegions(int pid,long regions[17][2]){
	//get file from pid
	char pids[255];
	char fName[255]="/proc/";
	sprintf(pids,"%d",pid);
	strcat(fName,pids);
	strcat(fName,"/maps");
	FILE* f=fopen(fName,"r");
	//printf("%s\n",fName);

	int length=0;

	for(int i=0;i<17;i++){
		//get line
		char buf[255];
		fgets(buf,255,f);

		//get addresses
		long a=strtol(buf,NULL,16);
		long b=strtol(buf+13,NULL,16);
		//printf("%lx-%lx\n",a,b);
		regions[i][0]=a;
		regions[i][1]=b;
		//printf("%d\n",b-a);
		length+=b-a;
	}

	printf("%d\n",length);
	fclose(f);

}

int peekMemory(int pid,long regions[17][2]){
	long start=regions[0][0];
	long end=regions[0][1];
	//for(int i=0;i<end-start;i++){
	for(int i=0;i<10;i++){
		long data=ptrace(PTRACE_PEEKDATA,pid,start+i,NULL);
		printf("%016lx\n",data);
	}
}

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

int main(int argc, char **argv){
	//char s[255];
	//fgets(s,255,stdin);
	for(int i=0;i<MEMSIZE;i++)memory[i]=0;
	//Attach
	int pid=atoi(argv[1]);//the pid of the process
	ptrace(PTRACE_ATTACH,pid);//attach to process
	waitpid(pid,NULL,0);

	//Get memory regions
	long regions[17][2];
	getMemoryRegions(pid,regions);
	//loadMemory(pid,regions);

	//Mainloop
	char c='s';
	int running=1;
	while(running==1){
		printf("(s)ingle step\tpeek (m)emory\t(l)oad memory region\t(k)ill process\t(q)uit\n");
		char tmp=getchar();
		if(tmp!='\n')c=tmp;
		if(c=='k')kill(pid,9);
		if(c=='l')loadMemory(pid,regions);
		if(c=='m')peekMemory(pid,regions);
		if(c=='q')running=0;
		if(c=='s')singleStep(pid,100);
	}

	//Detach
	printf("%d",ptrace(PTRACE_CONT,pid,NULL,NULL));
	ptrace(PTRACE_DETACH,pid);//attach to process
	return 0;
}

