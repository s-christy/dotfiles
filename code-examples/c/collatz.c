#include <stdio.h>

int main(){
	for(long i=1;i<5000000;i++){
		n=i;
		long num=0;
		while(n!=1){
			num++;
			//printf("%ld\n",n);
			if(n%2==0){
				n/=2;
			}else{
				n*=3;
				n++;
			}
		}
		printf("%d %d\n",i,num);
	}
	return 0;
}
