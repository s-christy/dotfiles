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
	printf("%d\n",x);
	struct user_regs_struct regs;
	ptrace(PTRACE_GETREGS,pid,NULL, &regs);
	printf("cs: %lx.\n",regs.cs);
	printf("ds: %lx.\n",regs.ds);
	printf("eflags: %lx.\n",regs.eflags);
	printf("es: %lx.\n",regs.es);
	printf("fs: %lx.\n",regs.fs);
	printf("fs_base: %lx.\n",regs.fs_base);
	printf("gs: %lx.\n",regs.gs);
	printf("gs_base: %lx.\n",regs.gs_base);
	printf("orig_rax: %lx.\n",regs.orig_rax);
	printf("r10: %lx.\n",regs.r10);
	printf("r11: %lx.\n",regs.r11);
	printf("r12: %lx.\n",regs.r12);
	printf("r13: %lx.\n",regs.r13);
	printf("r14: %lx.\n",regs.r14);
	printf("r15: %lx.\n",regs.r15);
	printf("r8: %lx.\n",regs.r8);
	printf("r9: %lx.\n",regs.r9);
	printf("rax: %lx.\n",regs.rax);
	printf("rbp: %lx.\n",regs.rbp);
	printf("rbx: %lx.\n", regs.rbx);
	printf("rbx: %lx.\n",regs.rbx);
	printf("rcx: %lx.\n",regs.rcx);
	printf("rdi: %lx.\n",regs.rdi);
	printf("rdx: %lx.\n",regs.rdx);
	printf("rip: %lx.-Instruction Pointer\n",regs.rip);
	printf("rsi: %lx.\n",regs.rsi);
	printf("rsp: %lx.-Stack Pointer\n",regs.rsp);
	printf("ss: %lx.\n",regs.ss);
}

int main(int argc, char **argv){
	printf("begin\n");
	int pid=atoi(argv[1]);//the pid of the process
	int status;
	ptrace(PTRACE_ATTACH,pid);//attach to process
	waitpid(pid,&status,0);

	do{
		x++;
		printf("%d",ptrace(PTRACE_SINGLESTEP,pid,NULL,NULL));
		dumpRegs(pid);
	}while(getchar()!='q');

	printf("%d",ptrace(PTRACE_CONT,pid,NULL,NULL));
	ptrace(PTRACE_DETACH,pid);//attach to process
	printf("end\n");

	return 0;
}

/*NOTES
 * kill(pid,18); sigcont
 * kill(pid,9); sigkill
 */
