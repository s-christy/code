//g++ -lfftw3 -lm main.cpp;./a.out;rm a.out

//TODO
//vectorize all of these arrays

#include <fftw3.h>
#include <iostream>
#include <math.h>

int N=100;

int main(){
	//Allocate the arrays
	fftw_complex *in=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);
	fftw_complex *out=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*N);

	//create a plan
	fftw_plan p=fftw_plan_dft_1d(N,in,out,FFTW_FORWARD,FFTW_ESTIMATE);

	//put the output of the sin function in the input array
	for(int i=0;i<N;i++)in[i][0]=sin(i);

	//print the input
	for(int i=0;i<N;i++)std::cout<<in[i][0]<<' ';
	std::cout<<"\n\n";

	//Run the transform
	fftw_execute(p);

	//print the output
	for(int i=0;i<N;i++)std::cout<<out[i][0]<<' ';
	std::cout<<"\n\n";

	//free memory
	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);
}
