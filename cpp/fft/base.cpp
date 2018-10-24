//g++ -lfftw3 -lm base.cpp;echo>f1;echo>f2;./a.out;rm a.out;gnuplot plot; rm f1 f2

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
	for(int i=0;i<N;i++)in[i][0]=sin(i);

	//save the input
	std::ofstream f1("f1");
	for(int i=0;i<N;i++)f1<<in[i][0]<<'\n';

	//Run the transform
	fftw_execute(p);

	//save the output
	std::ofstream f2("f2");
	for(int i=0;i<N;i++)f2<<out[i][0]<<'\n';

	//free memory
	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);
}
