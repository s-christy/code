//g++ -lfftw3 -lm inverse.cpp;echo>f1;echo>f2;./a.out;rm a.out;gnuplot plot; rm f1 f2

#include <fftw3.h>
#include <fstream>
#include <iostream>
#include <math.h>

int N=1000;

int main(){
	//Allocate the arrays
	fftw_complex *in=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
	fftw_complex *out=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);

	//create a plan
	fftw_plan p=fftw_plan_dft_1d(N,in,out,FFTW_FORWARD,FFTW_ESTIMATE);

	//put the output of the sin function in the input array
	int index=9*N/10;
	for(int i=index;i<index+1;i++)in[i][0]=2;
	index=8*N/9;
	for(int i=index;i<index+1;i++)in[i][0]=2;

	//save the input
	std::ofstream f1("f1");
	for(int i=0;i<N;i++)f1<<in[i][0]<<'\n';

	//Run the transform
	fftw_execute(p);

	//save the output
	float scale=.1;
	std::ofstream f2("f2");
	for(int i=0;i<N;i++)f2<<out[i][0]*scale<<'\n';

	//free memory
	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);
}
