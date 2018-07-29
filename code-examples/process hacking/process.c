#include <stdio.h>

int x=0;
int y=0;
int flag=0x1234;

int main(){
	while(flag==0x1234){
		x++;
		printf("%d\n",x);
		y++;
		y++;
	}
	printf("Left loop\n");
	return 0;
}
