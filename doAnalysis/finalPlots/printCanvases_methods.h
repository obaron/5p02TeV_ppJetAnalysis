#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>


bool direxists(std::string name){
  struct stat statbuf;
  int isDir=0;
  if(stat(name.c_str(),&statbuf) !=-1){
    if(S_ISDIR(statbuf.st_mode))
      isDir=1;
  }
  else
    isDir=0;
  return (bool)isDir;
}

bool makedirectory(std::string name){ 
  bool success=false;  
  if(mkdir(name.c_str(), 0777)==-1){
    std::cout<<"dir "<<name<<" not created!"<<std::endl;
    if(!direxists(name)){
      std::cout<<"... but dir does not exists?! check manually!"<<std::endl;
      success=false;    }
    else {
      std::cout<<"... because dir already exists!"<<std::endl;    
      success=true;    }  }
  else{
    std::cout<<"dir "<<name<<" created"<<std::endl;  
    success=true;  }  
  return success;
}

float getnonzeromin(TH2D* th2){
  float nonzeromin=999999999999999.;
  int nbinsx=th2->GetNbinsX();
  int nbinsy=th2->GetNbinsY();
  for(int i=1;i<=nbinsx;i++)
    for(int j=1;j<=nbinsy;j++){
      float content=th2->GetBinContent(i,j);
      if(!(content>0.)&&!(content<0.))
	continue;
      else if(content < nonzeromin)
	nonzeromin=content;
      else continue;
    }
  return nonzeromin;
    
}
