#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>

int x=0;

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

void singleStep(int pid){
	x++;
	int status;
	ptrace(PTRACE_SINGLESTEP,pid,NULL,NULL);
	waitpid(pid,&status,0);
	dumpRegs(pid);
}

int main(int argc, char **argv){
	printf("begin\n");
	int pid=atoi(argv[1]);//the pid of the process
	char c='_';
	ptrace(PTRACE_ATTACH,pid);//attach to process
	int status;
	waitpid(pid,&status,0);

	do{
		singleStep(pid);
		c=getchar();
		if(c=='k')kill(pid,9);
	}while(c!='q');

	printf("%d",ptrace(PTRACE_CONT,pid,NULL,NULL));
	ptrace(PTRACE_DETACH,pid);//attach to process
	printf("end\n");

	return 0;
}

/*NOTES
 * kill(pid,18); sigcont
 * kill(pid,9); sigkill
 */
