#include <iostream>
#include <fstream>
#include <dirent.h>

int queryProc(std::string search,bool silent=true){
	int pid=-1;
	DIR* procDir=opendir("/proc");
	dirent* d=readdir(procDir);
	while((d=readdir(procDir))!=NULL){
		if(atoi(d->d_name)>0){
			std::string fname="/proc/"+std::string(d->d_name)+"/cmdline";
			std::string s;
			std::ifstream f(fname);
			f>>s;
			if(s.find(search)!=std::string::npos){
				pid=atoi(d->d_name);
				if(!silent)std::cout<<pid<<"\t"<<s<<'\n';
			}
		}
	}
	return pid;
}

std::vector<std::pair<unsigned long,unsigned long>> readProc(int pid){
	std::vector<std::pair<unsigned long,unsigned long>> ret;
	std::string fname="/proc/"+std::to_string(pid)+"/maps";
	std::string s;
	std::ifstream f(fname);
	while(std::getline(f,s)){
		if(
			s.find("heap")!=std::string::npos or
			s.find("stack")!=std::string::npos){

			int dash=s.find("-")+1;
			unsigned long a,b;
			a=strtol(s.c_str(),0,16);
			b=strtol(s.c_str()+dash,0,16);
			ret.push_back(std::pair<unsigned long, unsigned long>(a,b));
			std::cout<<s<<'\n';
		}
	}
	return ret;
}
