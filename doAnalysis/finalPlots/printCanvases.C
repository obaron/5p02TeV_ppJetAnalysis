
//what this code is supposed to do, is take in a root file, look at all the TCanvases in the file, and print them all as .png's and .C's.
// .png --> for quick reference + adding things to ANs/Theses/slides/etc...
// .C --> for quick/last minute editing figure etc.

#include <cstdlib>
#include <iostream>
#include <cassert>

#include "TROOT.h"
#include "TFile.h"
#include "TKey.h"
#include "TClass.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"

#include "printCanvases_methods.h"
//#include "file_strings.h"
//#include "file_strings_03.18.20.h"
#include "file_strings_01.05.21.h"

const bool debugMode=false;

const bool DO_PNG=true, DO_PDF=true, DO_EPS=false, DO_C=false;

//const std::string BASEDIR="/Users/ilaflott/Working/CERNBox/5p02TeV_ppJetAnalysis_Results/5p02TeV_ppJetAnalysis_Results/";



//usage; root -l -b printCanvases.C++
//note; -b flag is not optional for saveas to work properly (unclear why)
//void printCanvases(std::string INPUTSTRING=""){//TO DO
void printCanvases(int jobnum=-1){
  std::cout<<"input jobnum="<<jobnum<<std::endl;
  //std::string file_array[]={};
  std::string* file_array=NULL;
  std::string *shortdir_array=NULL;//b.c. TEX hates me and won't compile if the image string is too long due to filenames being large...
  std::string targdir;
  int Nfiles=-1;
  switch (jobnum)
    {
    case 0:  std::cout<<"you chose PY8_UNF_DATA"<<std::endl   ; file_array=(std::string*)PY8_UNFDIR_DATA_file_array   ;shortdir_array=(std::string*)   PY8_UNFDIR_DATA_shortdir_array;  targdir=PY8_UNFDIR_DATA   ; Nfiles=PY8_UNFDIR_DATA_Nfiles   ;break;
    case 1:  std::cout<<"you chose PY8_UNF_CLOSURE"<<std::endl; file_array=(std::string*)PY8_UNFDIR_CLOSURE_file_array;shortdir_array=(std::string*)PY8_UNFDIR_CLOSURE_shortdir_array;  targdir=PY8_UNFDIR_CLOSURE; Nfiles=PY8_UNFDIR_CLOSURE_Nfiles;break;
    case 2:  std::cout<<"you chose NLO_UNF_DATA"<<std::endl   ; file_array=(std::string*)NLO_UNFDIR_DATA_file_array   ;shortdir_array=(std::string*)   NLO_UNFDIR_DATA_shortdir_array;  targdir=NLO_UNFDIR_DATA   ; Nfiles=NLO_UNFDIR_DATA_Nfiles   ;break;
    case 3:  std::cout<<"you chose NLO_UNF_CLOSURE"<<std::endl; file_array=(std::string*)NLO_UNFDIR_CLOSURE_file_array;shortdir_array=(std::string*)NLO_UNFDIR_CLOSURE_shortdir_array;  targdir=NLO_UNFDIR_CLOSURE; Nfiles=NLO_UNFDIR_CLOSURE_Nfiles;break;
    case 4:  std::cout<<"you chose JERDIR_MC  "<<std::endl    ; file_array=(std::string*)  JERDIR_MC_file_array       ;shortdir_array=(std::string*)         JERDIR_MC_shortdir_array;  targdir=JERDIR_MC         ; Nfiles=  JERDIR_MC_Nfiles       ;break;
    case 5:  std::cout<<"you chose VTXWDIR_MC "<<std::endl    ; file_array=(std::string*) VTXWDIR_MC_file_array       ;shortdir_array=(std::string*)        VTXWDIR_MC_shortdir_array;  targdir=VTXWDIR_MC        ; Nfiles= VTXWDIR_MC_Nfiles       ;break;
    case 6:  std::cout<<"you chose JETQA      "<<std::endl    ; file_array=(std::string*)      JETQA_file_array       ;shortdir_array=(std::string*)             JETQA_shortdir_array;  targdir=JETQA             ; Nfiles=      JETQA_Nfiles       ;break;
    case 7:  std::cout<<"you chose JETIDQA    "<<std::endl    ; file_array=(std::string*)    JETIDQA_file_array       ;shortdir_array=(std::string*)           JETIDQA_shortdir_array;  targdir=JETIDQA           ; Nfiles=    JETIDQA_Nfiles       ;break;
    case 8:  std::cout<<"you chose JETTRIGQA  "<<std::endl    ; file_array=(std::string*)  JETTRIGQA_file_array       ;shortdir_array=(std::string*)         JETTRIGQA_shortdir_array;  targdir=JETTRIGQA         ; Nfiles=  JETTRIGQA_Nfiles       ;break;
    default: std::cout<<"case not found; exit"<<std::endl; return; break;
    }
  std::cout<<"Nfiles="<<Nfiles<<std::endl;  
  
  if(Nfiles<1) {std::cout<<"err something wrong"<<std::endl; return;}
  
  std::cout<<"beginning loop over "<<Nfiles<<" files"<<std::endl;
  for(int i=0; i<Nfiles;i++){  
    
    std::string filename=file_array[i];    //input files
    std::string dirname=shortdir_array[i]; //for output images/root macro files
    
    filename=targdir+filename+".root";
    dirname =targdir+dirname;
    
    std::cout<<std::endl;
    std::cout<<"dirname="<<dirname<<std::endl;
    std::cout<<"opening file:"<<filename<<std::endl;    
    std::cout<<std::endl;
    
    //continue;
    
    TFile *f = TFile::Open(filename.c_str());       
    if(!((bool)f)){std::cout<<"file not open! skip!"<<std::endl;continue;}
    
    TIter next(f->GetListOfKeys());
    TKey *key;  
    bool dir_created=false;
    while ( (key = (TKey*)next()) ) {//loop over all objects in the root file
      
      if(debugMode)std::cout<<"found key! TKey->GetName()="<<key->GetName()<<std::endl;//debug
      
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("TCanvas")) continue;//if its not a canvas forget it
      
      TCanvas* canv = (TCanvas*)key->ReadObj();      
      if((bool)canv){if(debugMode)std::cout<<"found TCanvas! name is "<<key->GetName()<<std::endl;    }
      else {std::cout<<"canvas not opening for some reason. skip."<<std::endl;continue;}
      
      if(!dir_created){
	dir_created=makedirectory(dirname);
	if(!dir_created){ //make sure i dont fuck up the I/O; it could be bad.
	  std::cout<<"issue w/ directory, not created for some reason. exiting!"<<std::endl;
	  assert(false);	}      }
      
      canv->Draw();      
      
      if(DO_PNG){
	std::cout<<"saving .png of "<< key->GetName()<<std::endl;
	std::string png_name=dirname+"/"+((std::string)key->GetName())+".png";
	std::cout<<"png_name="<<png_name<<std::endl;
	canv->SaveAs( png_name.c_str() );}
      if(DO_EPS){
	std::cout<<"saving .eps of "<< key->GetName()<<std::endl;
	std::string eps_name=dirname+"/"+((std::string)key->GetName())+".eps";
	canv->SaveAs( eps_name.c_str() );}
      if(DO_PDF){
	std::cout<<"saving .pdf of "<< key->GetName()<<std::endl;
	std::string pdf_name=dirname+"/"+((std::string)key->GetName())+".pdf";
	canv->SaveAs( pdf_name.c_str() );}
      if(DO_C){
	std::cout<<"saving .C of   "<< key->GetName()<<std::endl; 
	std::string C_name  =dirname+"/"+((std::string)key->GetName())+".C";
	canv->SaveAs( C_name.c_str() );}

      //return; //use for DEBUG if running by root -l <name>.C
      //assert(false);//use for DEBUG if running by ./<name>.exe           
      
    }
    if(debugMode)std::cout<<"done w/ key loop"<<std::endl;
  }
  if(debugMode)std::cout<<"done w/ file loop"<<std::endl;
  
  return;
}

//// comment out for running by root -l <name>.C RECOMMENDED (graphics aren't right w/ g++/.exe)
//// uncomment for running by ./<name>.exe
//int main(int argc, char* argv[]){
//  
//
//  
//  printCanvases();
//  
//  return 0;
//  
//}


// NOTE when compiling w/ g++ into an executable, saving out as .png and/or .C does not work right. The canvas dimensions get really weird. 
// NOTE a diff between the .C saved out via g++ compiled executable, and the .C saved out via running w/ ROOT's C interpreter shows the problem:
//// diff canv_spectra_wg++.C canv_spectra_wROOT.C
////   4,5c4,5
////   < //=========  (Wed Oct 17 12:53:04 2018) by ROOT version6.08/02
////   <    TCanvas *c1 = new TCanvas("c1", "I/O Spectra Canvas",1,1,4,4);
////   ---
////   > //=========  (Wed Oct 17 12:51:04 2018) by ROOT version6.08/02
////   >    TCanvas *c1 = new TCanvas("c1", "I/O Spectra Canvas",0,45,1396,972); 

