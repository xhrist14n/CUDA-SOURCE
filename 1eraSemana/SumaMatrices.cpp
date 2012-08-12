// SumaMatrices.cpp: define el punto de entrada de la aplicación de consola.
// se tiene q copiar system 32 las dlls d bin

#include <tbb/parallel_for.h> // esta libreria funciona en paralelo
#include <tbb/tbb.h>		  // libreria TBB
#include <ctime>
#include <iostream>

using namespace tbb;
using namespace std;
class ProcesarSuma
{
private: int *A;
private: int *B;
private: int *C;
private: int n;

public: ProcesarSuma(int *_A,int*_B,int *_C,int n):A(_A),B(_B),C(_C),n(_n)
		{
			
		}
public: void operator()(blocked_range<int>& block) const
	{
		
		for(int i=block.begin();i<block.end();i++)
			{
				C[i]=A[i]+B[i];
				
				
			}

	}
};

int main(int argc, char* argv[])
{
	srand(time(NULL));
	time_t begin,end;
	const int size=1000000;
	int *A=new int[size];
	int *B=new int[size];
	int *C=new int[size];

	for(int i=0;i<size;i++)
	{	
		A[i]=(rand()*1000)%1000;
		B[i]=(rand()*1000)%1000;
		C[i]=0;
	
	}

	ProcesarSuma *sum=new ProcesarSuma(A,B,C,size);
	begin=clock();
	parallel_for(blocked_range<int>(0,size),*sum);	
	end=clock();
	cout<<(end-begin)*1.0f/CLOCKS_PER_SEC<<"\n";
	
	delete []A;
	delete []B;
	delete []C;
	
	std::cin.get();
	return 0;
}

