//for i in {1..10}; do echo "#"; done;g++ ptrace.cpp -o b.out;./b.out;rm b.out

#include <algorithm>
#include <iostream>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <vector>
#include <unistd.h>

#include "printRegs.hpp"
#include "queryProc.hpp"

void sendsig(std::string s,int signal){
	int pid=queryProc(s);
	std::cout<<pid<<' ';
	if(pid!=-1)kill(pid,signal);
}

std::vector<std::pair<unsigned long,unsigned long>> readProc(int pid){
	std::vector<std::pair<unsigned long,unsigned long>> ret;
	std::string fname="/proc/"+std::to_string(pid)+"/maps";
	std::string s;
	std::ifstream f(fname);
	while(f>>s){
		if(s.length()==25){
			int dash=s.find("-")+1;
			unsigned long a,b;
			a=strtol(s.c_str(),0,16);
			b=strtol(s.c_str()+dash,0,16);
			ret.push_back(std::pair<unsigned long, unsigned long>(a,b));
			std::cout<<std::hex<<a<<'-'<<b<<'\n';
		}
	}
	return ret;
}

std::vector<unsigned long> getHits(
		int target,
		std::vector<std::pair<unsigned long,unsigned long>> addresses,
		int pid
	){
	std::vector<unsigned long> hits;
	long data=0;
	for(int j=0;j<addresses.size();j++){
		std::cout<<std::dec<<j<<":\t";
		int n=0;
		for(unsigned long i=addresses[j].first;i<addresses[j].second;i++){
			data=ptrace(PTRACE_PEEKDATA,pid,i,NULL);
			if(data!=0xffffffffffffffff and data!=0){
				int intdata=data;
				if(intdata==target){
					hits.push_back(i);
					n++;
				}
			}
		}
		std::cout<<std::dec<<n<<'\n';
	}
	return hits;
}

void detach(int pid){
	int status;
	waitpid(pid,&status,0);
	if(ptrace(PTRACE_DETACH,pid,0,SIGCONT)==-1)perror("DETACH ERROR");
	else printf("DETACHED\n");
}

void attach(int pid){
	int status;
	waitpid(pid,&status,0);
	if(ptrace(PTRACE_ATTACH,pid)==-1)perror("ATTACH ERROR");
	else printf("ATTACHED\n");
}

std::vector<unsigned long> vectorUnion(
		std::vector<unsigned long> a,
		std::vector<unsigned long> b
	){

	std::vector<unsigned long> both;

	std::sort(a.begin(),a.end());
	std::sort(b.begin(),b.end());

	std::set_intersection(
		a.begin(),a.end(),
		b.begin(),b.end(),
		std::back_inserter(both)
	);
	//std::cout<<"Union is:\n";
	//for(int i=0;i<both.size();i++){
	//	std::cout<<both[i]<<'\n';
	//}
	//std::cout<<"End union.\n";
	return both;
}

int main(){
	int pid=queryProc("a.out");
	if(pid==-1)return -1;

	sendsig("a.out",SIGCONT);



	attach(pid);

	std::vector<std::pair<unsigned long,unsigned long>> addresses=readProc(pid);

	std::vector<unsigned long> total;
	while(1){
		char option;
		std::cout<<"Enter option: ";
		std::cin>>std::dec>>option;
		if(option=='q'){
			break;
		}else if(option=='d'){
			detach(pid);
		}else if(option=='k'){
			kill(pid,SIGKILL);
			exit(0);
		}else if(option=='a'){
			attach(pid);
		}else if(option=='p'){
			unsigned long addr=0;
			std::cout<<"Enter address: ";
			std::cin>>std::hex>>addr;
			unsigned long nval=0;
			std::cout<<"Enter new value: ";
			std::cin>>std::dec>>nval;
			ptrace(PTRACE_POKEDATA,pid,addr,nval);
		}else if(option=='t'){
			int target;
			std::cout<<"Enter target: ";
			std::cin>>std::dec>>target;
			std::vector<unsigned long> hits=getHits(target,addresses,pid);
			if(total.size()>0){
				total=vectorUnion(total,hits);
			}else{
				total=hits;
			}

			for(int i=0;i<total.size();i++){
				std::cout<<std::hex<<total[i]<<'\n';
			}
		}
	}


	//std::vector <unsigned long> both;
	//for(int i=0;i<a.size();i++){
	//	for(int j=0;j<b.size();j++){

	//	}
	//}

	//struct user_regs_struct regs;
	//printRegs(regs);
	//if(ptrace(PTRACE_SINGLESTEP,pid,NULL,NULL)==-1)perror("STEP ERROR");

	detach(pid);

	//sendsig("a.out",SIGKILL);

}

