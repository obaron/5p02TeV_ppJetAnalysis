//what this code is supposed to do, is take in the final root files, and make additional plots/canvases/etc. 
// .png --> for quick reference + adding things to ANs/Theses/slides/etc...
// .C --> for quick/last minute editing figure etc.

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <string>

#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TKey.h"
#include "TClass.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLine.h"
#include "TAttLine.h"
#include "TAxis.h"
#include "TF1.h"
#include "TObject.h"
#include "TMemStatShow.h"

#include "printCanvases_methods.h"
//#include "file_strings_03.18.20.h"//Y RESULTS W NLO FROM JOAO
#include "file_strings_01.05.21.h"//Y RESULTS W FULL-STAT NLO FROM KLAUS
#include "makeSMPInclJetXsec.h"

const std::string uncopts[4]={"",
			      "datatotUnc",
			      "NLOtotUnc",
			      "totUnc"};
const std::string targpdfs[4]={ "CT14nnlo",
				"NNPDF30_nnlo_as_0121",
				"NNPDF31_nnlo_as_0120",
				"NNPDF31_nnlo_as_0122"};
const std::string scaleopts[2]={"murmufHTp_v4",
				"murmufpt_v4"};
const std::string orders[2]={"NLO","NNLO"};

const std::string outdir="final_plots/";
const bool writeToFile=false;
const bool printFileBaseToScreen=false;

const bool doDataPlots=false;
const bool doPY8Plots=false;
const bool doPY8unfPlots=true;
const bool doThyPlots=false;
const bool doNLOunfPlots=false;

void makeFinalPlots(){
  
  
  TFile* fout=NULL;
  if(writeToFile)
    fout=new TFile("final_plots/final_plots.root","RECREATE");

  
  if(printFileBaseToScreen){
    std::cout<<"NLO_UNF_DATA_file_base="<< NLO_UNF_DATA_file_base<<std::endl;
    std::cout<<"FNLO_DIR="<<FNLO_DIR<<std::endl;
    std::cout<<"file for CT14nnlo="<<CT14nnlo<<std::endl;
    
    if(      (NLO_UNF_DATA_file_base.find("murmufHTp")!=std::string::npos) &&
	     (CT14nnlo.find("murmufHTp")!=std::string::npos) ){
      std::cout<<"scale choice is mur = muf = sum(parton pt in evt)"<<std::endl;}
    else if( (NLO_UNF_DATA_file_base.find("murmufpt1")!=std::string::npos) &&
	     (CT14nnlo.find("murmufpt1")!=std::string::npos) ){
      std::cout<<"scale choice is mur = muf = lead jet pt in evt"<<std::endl;}
    else if( (NLO_UNF_DATA_file_base.find("murmufpt")!=std::string::npos) &&
	     (CT14nnlo.find("murmufpt")!=std::string::npos) ){
      std::cout<<"scale choice is mur = muf = jet pt"<<std::endl;}
    else{
      std::cout<<"ERROR! Scale choice(s) of NLO_UNF_DATA_file_base and CT14nnlo file are incompatable! Check file_strings header!!!!"<<std::endl;
      //return;
    }
    
  }
  
  //////makeSMPInclJetXsec_data.h //good, only issue is that the PY8 file doesn't have the PFMETFracCut event count
  if(doDataPlots){
    //Data/PY8 event counts
    //printEvtCountTable(outdir);
    
    //Data Stat Errors
    makeSMPInclJetXsec_fracstaterrData_ratios(outdir,fout);
    //Data Covariance Matrix
    //makeSMPInclJetXsec_covmatData_onePadOneEta(outdir,fout);
    //NLO v PY8 unfolding comparison, MY unfolded results
    //makeSMPInclJetXsec_PY8vNLOunfdata_ratios(outdir,fout);    

    //TO DO?////Data Trigger Spectra 
    ////makeSMPInclJetXsec_triggerData_spectra(outdir,fout);
    //TO DO?////Data Trigger Turn Ons
    ////makeSMPInclJetXsec_triggerEffData_spectra(outdir,fout);
  }

  
  //////makeSMPInclJetXsec_PY8.h  //good
  if(doPY8Plots){
    //PY8 JER sigma
    makeSMPInclJetXsec_PY8JERsigma_onePadOneEta(outdir, fout);
    //PY8 JER mu
    makeSMPInclJetXsec_PY8JERmu_onePadOneEta(outdir, fout);
    //PY8 JER sigmu fit, one pad, all eta
    makeSMPInclJetXsec_NLOSmearingFits_onePadAllEta(outdir,fout);
    makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadAllEta(outdir,fout);
    //PY8 JER sigmu fit, one pad, one eta
    makeSMPInclJetXsec_NLOSmearingFits_onePadOneEta(outdir,fout);
    makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadOneEta(outdir,fout);
  }
  
  
  
  
  //////makeSMPInclJetXsec_PY8unf.h //good
  if(doPY8unfPlots){
    //comparisons with thy/GEN/truth distributions
    makeSMPInclJetXsec_PY8unfdata(outdir,fout);
    makeSMPInclJetXsec_PY8unfdata_ratios(outdir,fout);
    makeSMPInclJetXsec_PY8unfdatasysterr_ratios(outdir,fout);
    //comparisons with measured data distributions
    makeSMPInclJetXsec_PY8unfdata_wdatameas(outdir,fout);
    makeSMPInclJetXsec_PY8unfdata_wdatameas_ratios(outdir,fout);
    //response matrices for this unfolding
    makeSMPInclJetXsec_PY8unfrespmat_onePadOneEta(outdir,fout);
  }
  
  
  //////makeSMPInclJetXsec_NLOandNPCs.h 
  if(doThyPlots){
    ////NLO spectra
    //makeSMPInclJetXsec_OnlyNLO(outdir,fout);//give me targ pdf functionality?
    //NLOsyst targPDF v order
    for(int l=0; l<2;l++){	//loop over orders
      for(int k=0; k<2;k++){//loop over scale opts
	for(int j=0; j<4;j++){	    //loop over targ pdfs
	  makeSMPInclJetXsec_NLOsyst_targPDF_ratios(outdir,fout, targpdfs[j], scaleopts[k], orders[l]);
	}}}
    ////PY8 NPCs
    //makeSMPInclJetXsec_NPCs_onePadAllEta(outdir,fout, "PYTHIA8");
    //makeSMPInclJetXsec_NPCs_onePadOneEta(outdir,fout, "PYTHIA8");
    ////HERWIG NPCs
    //makeSMPInclJetXsec_NPCs_onePadAllEta(outdir,fout, "HERWIG");
    //makeSMPInclJetXsec_NPCs_onePadOneEta(outdir,fout, "HERWIG");
    ////AVG NPCs
    //makeSMPInclJetXsec_NPCs_onePadAllEta(outdir,fout, "AVG");
    //makeSMPInclJetXsec_NPCs_onePadOneEta(outdir,fout, "AVG");
  }
  
  
  //////////makeSMPInclJetXsec_NLOunf.h //targPDF works great! some discrepency between NLOunfdata_ratios and NLOunfdata_targPDF_ratios... dig into it when you can
  //TO DO: ADD PDF UNC (actual PDF errors, not the scale errors [also named PDFsys...]
  if(doNLOunfPlots){
    //////spectra comparisons with thy/GEN/truth distributions, give me targ pdf functionality
    //makeSMPInclJetXsec_NLOunfdata(outdir,fout);

    ////syst err sources on unf data only //fine 
    //makeSMPInclJetXsec_NLOunfdatasysterr_ratios(outdir,fout);  
    ////comparisons with measured data distributions //fine
    //makeSMPInclJetXsec_NLOunfdata_wdatameas(outdir,fout);
    //makeSMPInclJetXsec_NLOunfdata_wdatameas_ratios(outdir,fout);
    ////Response Matrices  //fine
    //makeSMPInclJetXsec_NLOunfrespmat_onePadOneEta(outdir,fout);
    
    ////ratio comparisons with target PDF spectra // these look fine as far as i can tell
    //for(int i=0; i<4;i++){//loop over unc opts
    // for(int l=0; l<2;l++){	//loop over orders
    //	for(int k=0; k<2;k++){ //loop over scale opts
    //	 for(int j=0; j<4;j++){	     //loop over targ pdfs
    //	    makeSMPInclJetXsec_NLOunfdata_targPDF_ratios(outdir,fout, uncopts[i], targpdfs[j], scaleopts[k], orders[l]);
    //	  }}}}    
    
    
    for(int etabin=0; etabin<4; etabin++){//loop over etabins
      for(int k=0; k<2;k++){ //loop over scale opts
	for(int j=0; j<4;j++){	     //loop over targ pdfs
	  makeSMPInclJetXsec_allOunfdata_ratios(outdir,fout,  targpdfs[j], scaleopts[k], etabin);
	}      }    }
      
    ////ratio comparisons w/ thy for LO, NLO, and NNLO spectra on one panel, by etabin, issue with stat error bars
    //makeSMPInclJetXsec_allOunfdata_ratios(outdir,fout,  0); 
    //makeSMPInclJetXsec_allOunfdata_ratios(outdir,fout,  1); 
    //makeSMPInclJetXsec_allOunfdata_ratios(outdir,fout,  2); 
    //makeSMPInclJetXsec_allOunfdata_ratios(outdir,fout,  3); 


  }
  
  
  


  

 
  
  if(writeToFile){
    fout->Write();
    fout->Close();
  }
  return;
}










//deprecrated below here



  
  ////////////QUICK COMPARISONS SECTION
  //spectra ratios to |y|<0.5, for NLO+NP theory, GEN PY8, and unf data
  //std::cout<<"running makeSMPInclJetXsec_NLOunfdataAcrossy_ratios"<<std::endl;
  //makeSMPInclJetXsec_NLOunfdataAcrossy_ratios(outdir,fout);
  //std::cout<<"running makeSMPInclJetXsec_PY8unfdataAcrossy_ratios"<<std::endl;
  //makeSMPInclJetXsec_PY8unfdataAcrossy_ratios(outdir,fout);


  //////comparisons with JOHNS unfolded results
  ////std::cout<<"running makeSMPInclJetXsec_JOHNNLOunfdata"<<std::endl;
  ////makeSMPInclJetXsec_JOHNNLOunfdata(outdir,fout);
  ////std::cout<<"running makeSMPInclJetXsec_JOHNNLOunfdata_ratios"<<std::endl;
  ////makeSMPInclJetXsec_JOHNNLOunfdata_ratios(outdir,fout);
  ////////comparisons with JOHNS measured data results
  ////std::cout<<"running makeSMPInclJetXsec_JOHNmeasdata"<<std::endl;
  ////makeSMPInclJetXsec_JOHNmeasdata(outdir,fout);
  ////std::cout<<"running makeSMPInclJetXsec_JOHNmeasdata_ratios"<<std::endl;
  ////makeSMPInclJetXsec_JOHNmeasdata_ratios(outdir,fout);  
  //////comparisons with JOHNS unfolded results
  ////std::cout<<"running makeSMPInclJetXsec_JOAONLOunfdata"<<std::endl;
  ////makeSMPInclJetXsec_JOAONLOunfdata(outdir,fout);
  ////std::cout<<"running makeSMPInclJetXsec_JOAONLOunfdata_ratios"<<std::endl;
  ////makeSMPInclJetXsec_JOAONLOunfdata_ratios(outdir,fout); 


  ////std::cout<<"running makeSMPInclJetXsec_PY8unfdata_DebugLaptop_ratios"<<std::endl;
  //makeSMPInclJetXsec_PY8unfdata_DebugLaptop_ratios(outdir,fout);
  //makeSMPInclJetXsec_PY8unfdata_DebugLaptop_ratios(outdir);


    //////ratio comparisons with thy/GEN/truth distributions used to unfold // error bands look slightly different than the ones produced by targPDF_ratios using equivalent inputs... look into
    //makeSMPInclJetXsec_NLOunfdata_ratios(outdir,fout,"");             //deprecate me
    //makeSMPInclJetXsec_NLOunfdata_ratios(outdir,fout,"totUnc");       //deprecate me
    //makeSMPInclJetXsec_NLOunfdata_ratios(outdir,fout,"datatotUnc");   //deprecate me
    //makeSMPInclJetXsec_NLOunfdata_ratios(outdir,fout,"NLOtotUnc");    //deprecate me
    //return;




    //NLOsyst v order
    //makeSMPInclJetXsec_NLOsyst_ratios(outdir,fout,"LO");   //deprecate me
    //makeSMPInclJetXsec_NLOsyst_ratios(outdir,fout,"NLO");  //deprecate me
    //makeSMPInclJetXsec_NLOsyst_ratios(outdir,fout,"NNLO"); //deprecate me
