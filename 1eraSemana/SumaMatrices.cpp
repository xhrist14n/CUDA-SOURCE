// cudaejemplo02.cpp: define el punto de entrada de la aplicación de consola.
// se tiene q copiar system 32 las dlls d bin

#include <tbb/parallel_for.h> // esta libreria funciona en parelelo
#include <tbb/tbb.h>
#include <ctime>
#include <iostream>

using namespace tbb;
using namespace std;
class ProcesarSuma
{
private:
	int *A;
	int *B;
	int *C;
	int n;

public:
	ProcesarSuma(int *_A,int*_B,int *_C,int n):A(_A),B(_B),C(_C),n(_n)
	{
		
	}
	void operator()(blocked_range<int>& block) const
	{
		
		for(int i=block.begin();i<block.end();i++)
			{
				C[i]=A[i]+B[i];
				
				
			}

	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	time_t begin,end;
	int size=1000000;
	int *A=new int[size];
	int *B=new int[size];
	int *C=new int[size];

	for(int i=0;i<size;i++)
	{	
		A[i]=rand()%1000;
		B[i]=rand()%1000;
		C[i]=0;
	
	}

	ProcesarSuma sum(A,B,C,size);
	begin=clock();
	parallel_for(blocked_range<int>(0,size),sum);	
	end=clock();
	cout<<(end-begin)*1.0f/CLOCKS_PER_SEC<<"\n";
	
	delete []A;
	delete []B;
	delete []C;
	
	std::cin.get();
	return 0;
}

