#include <iostream>
#include <random>
#include <vector>
#include "quickSort.cpp"

#define MODULO 200
#define SIZE 1500

int main(){
	std::vector<float> data;
	for(int i=0;i<SIZE;i++)
		data.push_back(rand()%MODULO);

	data=quickSort(data);

	for(int i=0;i<data.size();i++){
		std::cout<<data[i]<<',';
	}
	std::cout<<'\n';
	return 0;
}
