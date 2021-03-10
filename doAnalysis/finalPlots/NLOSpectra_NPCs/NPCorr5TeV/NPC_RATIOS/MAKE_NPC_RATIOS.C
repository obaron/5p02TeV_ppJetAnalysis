#include <cstdlib>
#include <iostream>
#include <string>

#include "TROOT.h"
#include "TStyle.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TLine.h"

const std::string __HWG5C_str="HerwigEE5C";
const std::string __HWG4C_str="HerwigEE4C";
const std::string _PYTHIA_str="PYTHIA8";
const std::string _POWPY8_str="POWPY8";
const std::string POWPY8C_str="POWPY8CTEQ";

std::string etabin_str_arr[]={
  "0.0 < #||{y} < 0.5",
  "0.5 < #||{y} < 1.0",
  "1.0 < #||{y} < 1.5",
  "1.5 < #||{y} < 2.0",
  "2.0 < #||{y} < 2.5",
  "2.5 < #||{y} < 3.0"
};


void MAKE_NPC_RATIOS(int radius, int etabin){
  if(etabin>5){
    std::cout<<"error, etabin cannot be > 5"<<std::endl;
    return;
  }
  if( radius < 2 || radius > 8){
    std::cout<<"error, radius must be between 2 and 8"<<std::endl;
    return;
  }
  
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gROOT->ForceStyle();
  
  TFile* NPC_file=TFile::Open( "NLOpNP_InclusiveJets5TeV.root","READ");

  //DATA POINTS
  TH1D* __HWG5C_NPCs=(TH1D*)NPC_file->Get(("NPC_"+__HWG5C_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());
  TH1D* __HWG4C_NPCs=(TH1D*)NPC_file->Get(("NPC_"+__HWG4C_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());
  TH1D* _PYTHIA_NPCs=(TH1D*)NPC_file->Get(("NPC_"+_PYTHIA_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());
  TH1D* _POWPY8_NPCs=(TH1D*)NPC_file->Get(("NPC_"+_POWPY8_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());
  TH1D* POWPY8C_NPCs=(TH1D*)NPC_file->Get(("NPC_"+POWPY8C_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());

  //FITS TO DATA POINTS
  //TF1* f__HWG5C_NPCs=(TF1*)NPC_file->Get(("fNPC_"+__HWG5C_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());
  //TF1* f__HWG4C_NPCs=(TF1*)NPC_file->Get(("fNPC_"+__HWG4C_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());
  //TF1* f_PYTHIA_NPCs=(TF1*)NPC_file->Get(("fNPC_"+_PYTHIA_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());
  //TF1* f_POWPY8_NPCs=(TF1*)NPC_file->Get(("fNPC_"+_POWPY8_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());
  //TF1* fPOWPY8C_NPCs=(TF1*)NPC_file->Get(("fNPC_"+POWPY8C_str+"_R"+std::to_string(radius)+"_etabin"+std::to_string(etabin)).c_str());
  //
  //TH1D* __HWG5C_NPCs=(TH1D*)(f__HWG5C_NPCs->GetHistogram());
  //TH1D* __HWG4C_NPCs=(TH1D*)(f__HWG4C_NPCs->GetHistogram());
  //TH1D* _PYTHIA_NPCs=(TH1D*)(f_PYTHIA_NPCs->GetHistogram());
  //TH1D* _POWPY8_NPCs=(TH1D*)(f_POWPY8_NPCs->GetHistogram());
  //TH1D* POWPY8C_NPCs=(TH1D*)(fPOWPY8C_NPCs->GetHistogram());

  TH1D* __HWG4C_ov_HWG5C_NPCs=(TH1D*)__HWG4C_NPCs->Clone("__HWG4C_ov_HWG5C_NPCs");
  TH1D* _PYTHIA_ov_HWG5C_NPCs=(TH1D*)_PYTHIA_NPCs->Clone("_PYTHIA_ov_HWG5C_NPCs");
  TH1D* _POWPY8_ov_HWG5C_NPCs=(TH1D*)_POWPY8_NPCs->Clone("_POWPY8_ov_HWG5C_NPCs");
  TH1D* POWPY8C_ov_HWG5C_NPCs=(TH1D*)POWPY8C_NPCs->Clone("POWPY8C_ov_HWG5C_NPCs");
  
  
  __HWG4C_ov_HWG5C_NPCs->Divide(__HWG5C_NPCs);
  _PYTHIA_ov_HWG5C_NPCs->Divide(__HWG5C_NPCs);
  _POWPY8_ov_HWG5C_NPCs->Divide(__HWG5C_NPCs);
  POWPY8C_ov_HWG5C_NPCs->Divide(__HWG5C_NPCs);
  
  __HWG4C_ov_HWG5C_NPCs->SetLineColor(kRed    );
  _PYTHIA_ov_HWG5C_NPCs->SetLineColor(kBlue   );
  _POWPY8_ov_HWG5C_NPCs->SetLineColor(kGreen  );
  POWPY8C_ov_HWG5C_NPCs->SetLineColor(kMagenta);
  
  
  float xmin=__HWG4C_ov_HWG5C_NPCs->GetBinLowEdge(1);
  float xmax=
    __HWG4C_ov_HWG5C_NPCs->GetBinLowEdge(__HWG4C_ov_HWG5C_NPCs->GetNbinsX()) + 
    __HWG4C_ov_HWG5C_NPCs->GetBinWidth(  __HWG4C_ov_HWG5C_NPCs->GetNbinsX());
  TLine* one=new TLine(xmin, 1., xmax, 1.);
  one->SetLineColor(kBlack);
  one->SetLineWidth(1);
  one->SetLineStyle(9);
  
  TH1D* stylehist=(TH1D*)__HWG4C_ov_HWG5C_NPCs->Clone("stylehistonly");
  stylehist->Reset("ICES");
  
  //stylehist->SetTitle(("Ratios of NPCs (fit-->hist), R=0."+std::to_string(radius)+", "+etabin_str_arr[etabin]).c_str());
  stylehist->SetTitle(("Ratios of NPCs (data points for fits), R=0."+std::to_string(radius)+", "+etabin_str_arr[etabin]).c_str());
  stylehist->GetXaxis()->SetTitle("Jet p_{T}");
  stylehist->GetXaxis()->SetMoreLogLabels(true);
  stylehist->GetXaxis()->SetNoExponent(true);
  stylehist->GetYaxis()->SetTitle("Ratio to HERWIG EE5C NPCs");
  stylehist->GetYaxis()->CenterTitle(true);
  stylehist->SetMinimum(0.5);
  stylehist->SetMaximum(1.7);
  
  TLegend* leg=new TLegend(0.6,0.6,0.9,0.9, "");
  leg->SetBorderSize(0.);
  leg->SetFillStyle(0);
  leg->AddEntry(__HWG4C_ov_HWG5C_NPCs, "HERWIG EE4C NPCs", "lp");
  leg->AddEntry(_PYTHIA_ov_HWG5C_NPCs,   "PYTHIA8 NPCs", "lp");
  leg->AddEntry(_POWPY8_ov_HWG5C_NPCs,   "POW+PY8 NPCs", "lp");
  leg->AddEntry(POWPY8C_ov_HWG5C_NPCs,   "POW+PY8 CTEQ NPCs", "lp");
  
  TCanvas* NPC_ratio_canv=new TCanvas("NPC_ratio_canv","NPC_ratio_canv",1600,1400);
  NPC_ratio_canv->SetLogx(1);
  NPC_ratio_canv->SetLogy(0);
  NPC_ratio_canv->cd();
  
  stylehist->Draw();
  one->Draw();
  
  __HWG4C_ov_HWG5C_NPCs->Draw("HIST ][ SAME");
  _PYTHIA_ov_HWG5C_NPCs->Draw("HIST ][ SAME");
  _POWPY8_ov_HWG5C_NPCs->Draw("HIST ][ SAME");
  POWPY8C_ov_HWG5C_NPCs->Draw("HIST ][ SAME");
  
  leg->Draw();
  
  //  NPC_ratio_canv->SaveAs(("R0"+std::to_string(radius)+"_NPC_ratios_to_HERWIGEE5C_etabin"+std::to_string(etabin)+".pdf").c_str());
  NPC_ratio_canv->SaveAs(("R0"+std::to_string(radius)+"_DATAPOINTS_NPC_ratios_to_HERWIGEE5C_etabin"+std::to_string(etabin)+".pdf").c_str());

  return;
}
