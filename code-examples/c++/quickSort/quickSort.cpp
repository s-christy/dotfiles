#include <vector>

template<typename T>

std::vector<T> quickSort(std::vector<T> data){

	if(data.size()==0)return data;
	int pivot=data[data.size()/2];

	std::vector<T> a;
	std::vector<T> b;
	std::vector<T> c;
	std::vector<T> ret;

	for(int i=0;i<data.size();i++){
		if(data[i]<pivot)a.push_back(data[i]);
		if(data[i]==pivot)b.push_back(data[i]);
		if(data[i]>pivot)c.push_back(data[i]);
	}

	a=quickSort(a);
	c=quickSort(c);

	for(int i=0;i<a.size();i++)ret.push_back(a[i]);
	for(int i=0;i<b.size();i++)ret.push_back(b[i]);
	for(int i=0;i<c.size();i++)ret.push_back(c[i]);

	return ret;
}

