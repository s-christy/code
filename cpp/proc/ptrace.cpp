//for i in {1..10}; do echo "#"; done;g++ ptrace.cpp -o b.out;./b.out;rm b.out

#include <algorithm>
#include <iostream>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <vector>

#include "printRegs.hpp"
#include "queryProc.hpp"

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
	return both;
}

std::vector<unsigned int> snapshot(int pid,std::vector<std::pair<unsigned long,unsigned long>> addresses){
	std::vector<unsigned int> ret;
	int len=0;
	for(int i=0;i<addresses.size();i++){
		len+=addresses[0].second-addresses[0].first;
	}
	int limit=len/100;
	len=limit;
	ret=std::vector<unsigned int>(len);
	unsigned long index=0;
	for(int j=0;j<addresses.size();j++){
		for(unsigned long i=addresses[j].first;i<addresses[j].second;i++){
			ret[index]=ptrace(PTRACE_PEEKDATA,pid,i,NULL);
			index++;
			if(index%10000==0)std::cout<<(float)index/(float)len<<"\t\t\r";
			if(index==limit){
				std::cout<<'\n';
				return ret;
			}
		}
	}
	std::cout<<'\n';
	return ret;
}

void different(std::vector<unsigned int>& snap,int pid,std::vector<std::pair<unsigned long,unsigned long>>& addresses){
	std::vector<unsigned int> snap2=snapshot(pid,addresses);

	for(int i=0;i<snap.size();i++){
		if(snap[i]==snap2[i] or snap[i]==0){
			snap[i]=0;
		}else{
			snap[i]=snap2[i];
		}
	}
}

void same(std::vector<unsigned int>& snap,int pid,std::vector<std::pair<unsigned long,unsigned long>>& addresses){
	std::vector<unsigned int> snap2=snapshot(pid,addresses);

	for(int i=0;i<snap.size();i++){
		if(snap[i]!=snap2[i]){
			snap[i]=0;
		}
	}
}

int main(){
	//std::string procName="Risk_of_Rain";
	//std::string procName="a.out";
	std::string procName="deadcells";
	int pid=queryProc(procName);
	if(pid==-1)return -1;

	kill(pid,SIGCONT);
	//exit(0);



	attach(pid);

	std::vector<std::pair<unsigned long,unsigned long>> addresses=readProc(pid);
	std::vector<unsigned int> snap=snapshot(pid,addresses);

	std::vector<unsigned long> total;
	while(1){
		char option;
		std::cout<<"[s]ame\td[i]fferent\t[a]ttach\t[d]etach\t[p]oke\n";
		std::cin>>std::dec>>option;
		if(option=='q'){//quit
			break;
		}else if(option=='k'){//kill process
			kill(pid,SIGKILL);
			exit(0);
		}else if(option=='s'){//same
			same(snap,pid,addresses);
		}else if(option=='i'){//different
			different(snap,pid,addresses);
		}else if(option=='a'){//attach
			attach(pid);
		}else if(option=='d'){//detach
			detach(pid);
		}else if(option=='p'){//poke
			unsigned long addr=0;
			std::cout<<"Enter address: ";
			std::cin>>std::hex>>addr;
			unsigned long nval=0;
			std::cout<<"Enter new value: ";
			std::cin>>std::dec>>nval;
			if(addr==0){
				for(int i=0;i<total.size();i++)
					ptrace(PTRACE_POKEDATA,pid,total[i],nval);
			}else{
				ptrace(PTRACE_POKEDATA,pid,addr,nval);
			}
		}else if(option=='t'){//find target
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
			std::cout<<total.size()<<'\n';


		}
		else if(option=='v'){//view
			for(int i=0;i<snap.size();i++){
				if(snap[i]!=0){
					std::cout<<snap[i]<<'\n';
				}
			}
		}
		int count=0;
		for(int i=0;i<snap.size();i++)
			if(snap[i]!=0)
				count++;
		std::cout<<count<<'\n';
	}



	detach(pid);


}

