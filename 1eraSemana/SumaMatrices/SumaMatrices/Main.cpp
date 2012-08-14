// SumaMatrices.cpp: define el punto de entrada de la aplicación de consola.
//
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>

using namespace std;
using namespace tbb;

class ProcesarSuma{
private: 
	int *A,*B,*C,n;
public:
	ProcesarSuma(int *_A,int*_B,int *_C,int _n):A(_A),B(_B),C(_C),n(_n){
		
	}
	void operator()(const blocked_range<int> &block) const{
		for(int i=block.begin();i<block.end();i++){
			C[i] = A[i]+B[i];
			//std::cout<<C[i]<<std::endl;
		}
	}
	void procesar()const{
		for(int i =0;i<n;i++){
			C[i] = A[i]+B[i];
		}
	}
};
/*
Traer como trabajo para el lunes :

traer el valor de clocks per sec de su maquina
CLOCKS_PER_SEC cuanto vale para su maquina

traer cuanto demora en 10000 elementos
traer cuanto demora en 100000 elementos
traer cuanto demora en 1000000 elementos
traer cuanto demora en 10000000 elementos

y probar en modo serial

*/

int main(int argc, char* argv[])
{
	//std::cout<<": "<<CLOCKS_PER_SEC<<endl;
	std::fstream fs("salidas",ios::out|ios::app);
	time_t begin=NULL,end=NULL;
	std::cout<<"Iniciando programa"<<std::endl;
	srand((unsigned int)time(NULL));
	int size = 10000000;
	int *A = new int[size];
	int *B = new int[size];
	int *C = new int[size];
	for(int i=0;i<size;i++){
		A[i]=rand()%1000;
		B[i]=rand()%1000;
		C[i]=0;
	}
	ProcesarSuma* sum=new ProcesarSuma(A,B,C,size);
	begin=(int)clock();
	parallel_for(blocked_range<int>(0,size),*sum);
	//sum->procesar();
	end=(int)clock();
	float tiempo=((float)((end-begin)*1.0f))/(float)(CLOCKS_PER_SEC);
	std::cout<<"Longitud de array: "<<size<<endl;
	std::cout<<"El tiempo de ejecucion es: "<<tiempo<<std::endl;
	fs<<"Longitud de array: "<<size<<endl;
	fs<<"El tiempo de ejecucion es: "<<tiempo<<std::endl;
	delete[]A;
	delete[]B;
	delete[]C;
	std::cout<<"Terminando programa"<<std::endl;
	std::cin.get();
	return 0;
}