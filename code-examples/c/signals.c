#include <stdio.h>
#include <signal.h>
#include <sys/ptrace.h>

//kill -L lists all the signals you can use
//gcc stopProcess.c; ./a.out `pidof TARGET`

int main(int argc, char *argv[]){
	int i;
	sscanf(argv[1], "%d", &i);
	printf("%d\n", i);
	char c=getchar();
	if (c=='c'){
		kill(i, SIGCONT);
	}else if (c=='s'){
		kill(i, SIGSTOP);
	}else if (c=='k'){
		kill(i, SIGKILL);
	}else if (c=='a'){
		ptrace(PTRACE_ATTACH, i,0,0);
	}else if (c=='d'){
		ptrace(PTRACE_DETACH, i,0,0);
	}
	return 0;
}
