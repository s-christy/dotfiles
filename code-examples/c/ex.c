#include <stdio.h>

void func(){
	printf("asdf\n");
}

int main(){
	printf("outside\n");
	func();
	return 0;
}
