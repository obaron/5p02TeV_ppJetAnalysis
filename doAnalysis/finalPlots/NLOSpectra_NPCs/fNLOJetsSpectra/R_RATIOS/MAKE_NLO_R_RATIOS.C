#include <cstdlib>
#include <iostream>
#include <string>

#include "TColor.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TLine.h"

const std::string _CT10_str="CT10nlo_HS";
const std::string _CT14_str="CT14nlo_HS";
const std::string _HERA_str="HERAPDF15NLO_ALPHAS_HS";
const std::string _MMHT_str="MMHT2014nlo68cl_HS";
const std::string NNPDF_str="NNPDF30_nnlo_as_0121_MC";

std::string etabin_str_arr[]={
  "0.0 < #||{y} < 0.5",
  "0.5 < #||{y} < 1.0",
  "1.0 < #||{y} < 1.5",
  "1.5 < #||{y} < 2.0"//,
  //"2.0 < #||{y} < 2.5",
  //"2.5 < #||{y} < 3.0"
};
const int netabins=4;

Color_t etabin_color_arr[]={
  632,//"kRed",
  600,//"kBlue",
  416,//"kGreen",
  616//,//"kMagenta"//,
  //880,////"kViolet",
  //840////"kTeal"
};

void MAKE_NLO_R_RATIOS( std::string targnlo, int numR, int denR, int order){
  
  std::string nlostr;
  if(targnlo=="CT10")       nlostr=_CT10_str;
  else if(targnlo=="CT14")  nlostr=_CT14_str;
  else if(targnlo=="HERA")  nlostr=_HERA_str;
  else if(targnlo=="MMHT")  nlostr=_MMHT_str;
  else if(targnlo=="NNPDF") nlostr=NNPDF_str;
  else return;
  if(numR != 4 &&
     numR != 3 &&
     numR != 7 
     )return;
  if(denR != 4 &&
     denR != 3 &&
     denR != 7 
     )return;
  if(denR==numR)return;
  if(order != 0 &&
     order != 1)    return;
  
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gROOT->ForceStyle();
  
  std::string numR_dir_str="R0"+std::to_string(numR)+"/fnl5020_LO2_R0"+std::to_string(numR)+"Jets_modify_"+nlostr;
  std::string denR_dir_str="R0"+std::to_string(denR)+"/fnl5020_LO2_R0"+std::to_string(denR)+"Jets_modify_"+nlostr;
  
  std::cout<<"opening file "<<denR_dir_str<<std::endl;
  TFile* denR_NLO_file=TFile::Open( (denR_dir_str+".root").c_str(),"READ");
  std::cout<<"opening file "<<numR_dir_str<<std::endl;
  TFile* numR_NLO_file=TFile::Open( (numR_dir_str+".root").c_str(),"READ");
  
  TH1D *denR_NLO_jtpt[netabins]={};
  TH1D *numR_NLO_jtpt[netabins]={};
  TH1D *numR_ov_denR_NLO_jtpt[netabins]={};
  TLegend* leg=new TLegend(0.6,0.6,0.9,0.9, "");
  leg->SetBorderSize(0.);
  leg->SetFillStyle(0);
  float ymin=1000., ymax=-1.;
  for(int i=0; i<netabins;i++){
    std::string histname="h"+std::to_string(order)+"100"+std::to_string(i+1)+"00";
    std::cout<<"getting denominator hist, etabin="<<i<<", denR="<<denR<<std::endl;
    denR_NLO_jtpt[i]=(TH1D*)denR_NLO_file->Get(histname.c_str());
    std::cout<<"getting numerator hist,   etabin="<<i<<", numR="<<numR<<std::endl;
    numR_NLO_jtpt[i]=(TH1D*)numR_NLO_file->Get(histname.c_str());
    
    numR_ov_denR_NLO_jtpt[i]=(TH1D*)numR_NLO_jtpt[i]->Clone(("RO"+std::to_string(numR)+"_ov_RO"+std::to_string(denR)+"_jtpt_etabin"+std::to_string(i)).c_str());
    
    
    numR_ov_denR_NLO_jtpt[i]->Divide(denR_NLO_jtpt[i]);
    //numR_ov_denR_NLO_jtpt[i]->SetLineColor((Color_t)(etabin_color_arr[i].c_str()));
    numR_ov_denR_NLO_jtpt[i]->SetLineColor((Color_t)(etabin_color_arr[i]));
    leg->AddEntry(numR_ov_denR_NLO_jtpt[i], etabin_str_arr[i].c_str(), "lp");  
    float maxval=    numR_ov_denR_NLO_jtpt[i]->GetMaximum();
    if(maxval>ymax)ymax=maxval;
    float minval=    numR_ov_denR_NLO_jtpt[i]->GetMinimum();
    if(minval<ymin)ymin=minval;
  }
  
  float xmin=numR_ov_denR_NLO_jtpt[0]->GetBinLowEdge(1);
  float xmax=
    numR_ov_denR_NLO_jtpt[0]->GetBinLowEdge(numR_ov_denR_NLO_jtpt[0]->GetNbinsX()) + 
    numR_ov_denR_NLO_jtpt[0]->GetBinWidth(  numR_ov_denR_NLO_jtpt[0]->GetNbinsX());
  
  TLine* one=new TLine(xmin, 1., xmax, 1.);
  one->SetLineColor(kBlack);
  one->SetLineWidth(1);
  one->SetLineStyle(9);
  
  std::string htitle="Ratios of "+nlostr+" Spectra, ";
  if(order==0)htitle+="LO, ";
  else if(order==1)htitle+="NLO, ";  
  htitle+="R=0."+std::to_string(numR)+" / R=0."+std::to_string(denR);

  TH1D* stylehist=(TH1D*)numR_ov_denR_NLO_jtpt[0]->Clone("stylehistonly");
  stylehist->Reset("MICES");  
  stylehist->SetTitle(htitle.c_str()		      );
  stylehist->GetXaxis()->SetTitle("Jet p_{T}");
  stylehist->GetXaxis()->SetMoreLogLabels(true);
  stylehist->GetXaxis()->SetNoExponent(true);
  stylehist->GetYaxis()->SetTitle(("Ratio to R=0."+std::to_string(denR)).c_str());
  stylehist->GetYaxis()->CenterTitle(true);
  stylehist->GetYaxis()->SetTitleOffset(1.3);
  std::cout<<"ymin, ymax = "<<ymin <<", "<<ymax<<std::endl;
  //stylehist->SetMaximum(1.005);
  //stylehist->SetMinimum(0.995);
  if(order==1){
    stylehist->SetMaximum(1.005);
    stylehist->SetMinimum(0.995);}
  else if(order==0){
    stylehist->SetMaximum(ymax*1.05);
    stylehist->SetMinimum(ymin*0.95);}

  
  
  TCanvas* NLO_ratio_canv=new TCanvas("NLO_ratio_canv","NLO_ratio_canv",1600,1400);
  NLO_ratio_canv->SetLogx(1);
  NLO_ratio_canv->SetLogy(0);
  NLO_ratio_canv->cd();
  
  stylehist->Draw();
  one->Draw();
  
  for(int i=0; i<netabins;i++)
    numR_ov_denR_NLO_jtpt[i]->Draw("SAME");
  
  leg->Draw();
  
  std::string outputname="RO"+std::to_string(numR)+"_ov_RO"+std::to_string(denR)+"_"+nlostr+"_";
  if(order==0)outputname+="LO_alletabins";
  else if(order==1)outputname+="NLO_alletabins";

  NLO_ratio_canv->SaveAs((outputname+".pdf").c_str());
  NLO_ratio_canv->SaveAs((outputname+".png").c_str());

  return;
}
