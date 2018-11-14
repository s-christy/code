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
