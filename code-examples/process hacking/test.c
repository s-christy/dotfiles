#include <stdio.h>



void change(int *i){
	int d=9;
	*i=9;
}

int main(){
	int i=10;
	printf("%d\n",i);
	change(&i);
	printf("%d\n",i);

	return 0;
}

