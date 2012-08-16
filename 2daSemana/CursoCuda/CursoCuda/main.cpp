#include <iostream>
#include <fstream>
#include <cmath>
#include <functional>
#include <ctime>
#include <tbb\tbb.h>
#include <tbb\parallel_for.h>

using namespace tbb;
using namespace std;

void procesoSerial(double* arr,int size)
{
	for(int i=0; i<size ;i++)
	{
		arr[i]=pow(sin(arr[i])+cos(arr[i]) +tan(arr[i]) +1/tan(arr[i])+1/cos(arr[i])+1/sin(arr[i]),2);
		arr[i]=pow(sin(arr[i])+cos(arr[i]) +tan(arr[i]) +1/tan(arr[i])+1/cos(arr[i])+1/sin(arr[i]),3);
	}
}

void procesoParalelo(double* arr,int size)
{
	parallel_for( blocked_range<int>(0,size),[arr](const blocked_range<int>& range)
	{
		for(int i=range.begin(); i<range.end() ;i++)
		{
			arr[i]=pow(sin(arr[i])+cos(arr[i]) +tan(arr[i]) +1/tan(arr[i])+1/cos(arr[i])+1/sin(arr[i]),2);
			arr[i]=pow(sin(arr[i])+cos(arr[i]) +tan(arr[i]) +1/tan(arr[i])+1/cos(arr[i])+1/sin(arr[i]),3);
		}
	});
	
	
}
/*
void funcionReutilizable(double * arr, int size, function<void(int&)> doSomeWork)
{
	for( int  i=0; i<size ;i++ )
	{
		doSomeWork( arr[i] );
	}

}*/

void main()
{
	fstream fs("archivo.txt",ios::out|ios::app);
	time_t begin, end;
	int size = 10000;
	
	size = 50000;
	size = 100000;
	size = 200000;
	size = 500000;

	size = 1000000;
	size = 2000000;
	size = 5000000;
	size = 10000000;
	size = 100000000;


	double* arr = new double[size];

	/*funcionReutilizable(arr,size,[](int & n){ 
			n = rand()%100; 
		}
	);*/
	cout<<size<<endl;
	fs<<size<<endl;
	begin = clock();
	procesoSerial(arr,size);
	end = clock();
	cout<<(end-begin)*1.0f/CLOCKS_PER_SEC<<endl;
	fs<<(end-begin)*1.0f/CLOCKS_PER_SEC<<endl;

	begin = clock();
	procesoParalelo(arr,size);
	end = clock();	
	cout<<(end-begin)*1.0f/CLOCKS_PER_SEC<<endl;
	fs<<(end-begin)*1.0f/CLOCKS_PER_SEC;

	delete[] arr;

	cin.get();
}

