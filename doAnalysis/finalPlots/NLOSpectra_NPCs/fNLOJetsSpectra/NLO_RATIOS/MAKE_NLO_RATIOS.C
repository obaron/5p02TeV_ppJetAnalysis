#include <cstdlib>
#include <iostream>
#include <string>

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
  "1.5 < #||{y} < 2.0",
  "2.0 < #||{y} < 2.5",
  "2.5 < #||{y} < 3.0"
};


void MAKE_NLO_RATIOS(int radius, int etabin, int order){
  if(etabin>5){
    std::cout<<"error, etabin cannot be > 5"<<std::endl;
    return;
  }
  if(radius!=3 && radius!=4 && radius!=7){
    std::cout<<"error, radius must be 3, 4 or 7"<<std::endl;
    return;
  }
  if(order != 0 && order != 1)
    return;
  
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gROOT->ForceStyle();
  
  std::string dir_str="R0"+std::to_string(radius)+"/fnl5020_LO2_R0"+std::to_string(radius)+"Jets_modify_";
  
  TFile* _CT10_file=TFile::Open( (dir_str+_CT10_str+".root").c_str(),"READ");
  TFile* _CT14_file=TFile::Open( (dir_str+_CT14_str+".root").c_str(),"READ");
  TFile* _HERA_file=TFile::Open( (dir_str+_HERA_str+".root").c_str(),"READ");
  TFile* _MMHT_file=TFile::Open( (dir_str+_MMHT_str+".root").c_str(),"READ");
  TFile* NNPDF_file=TFile::Open( (dir_str+NNPDF_str+".root").c_str(),"READ");
  
  std::string histname="h"+std::to_string(order)+"100"+std::to_string(etabin+1)+"00";
  TH1D* _CT10_jtpt=(TH1D*)_CT10_file->Get(histname.c_str());
  TH1D* _CT14_jtpt=(TH1D*)_CT14_file->Get(histname.c_str());
  TH1D* _HERA_jtpt=(TH1D*)_HERA_file->Get(histname.c_str());
  TH1D* _MMHT_jtpt=(TH1D*)_MMHT_file->Get(histname.c_str());
  TH1D* NNPDF_jtpt=(TH1D*)NNPDF_file->Get(histname.c_str());
  
  TH1D* _CT10_ov_NNPDF_jtpt=(TH1D*)_CT10_jtpt->Clone("_CT10_ov_NNPDF_jtpt");
  TH1D* _CT14_ov_NNPDF_jtpt=(TH1D*)_CT14_jtpt->Clone("_CT14_ov_NNPDF_jtpt");
  TH1D* _HERA_ov_NNPDF_jtpt=(TH1D*)_HERA_jtpt->Clone("_HERA_ov_NNPDF_jtpt");
  TH1D* _MMHT_ov_NNPDF_jtpt=(TH1D*)_MMHT_jtpt->Clone("_MMHT_ov_NNPDF_jtpt");

  
  _CT10_ov_NNPDF_jtpt->Divide(NNPDF_jtpt);
  _CT14_ov_NNPDF_jtpt->Divide(NNPDF_jtpt);
  _HERA_ov_NNPDF_jtpt->Divide(NNPDF_jtpt);
  _MMHT_ov_NNPDF_jtpt->Divide(NNPDF_jtpt);

  _CT10_ov_NNPDF_jtpt->SetLineColor(kRed    );
  _CT14_ov_NNPDF_jtpt->SetLineColor(kBlue   );
  _HERA_ov_NNPDF_jtpt->SetLineColor(kGreen  );
  _MMHT_ov_NNPDF_jtpt->SetLineColor(kMagenta);
  

  float xmin=_CT10_ov_NNPDF_jtpt->GetBinLowEdge(1);
  float xmax=
    _CT10_ov_NNPDF_jtpt->GetBinLowEdge(_CT10_ov_NNPDF_jtpt->GetNbinsX()) + 
    _CT10_ov_NNPDF_jtpt->GetBinWidth(  _CT10_ov_NNPDF_jtpt->GetNbinsX());
  TLine* one=new TLine(xmin, 1., xmax, 1.);
  one->SetLineColor(kBlack);
  one->SetLineWidth(1);
  one->SetLineStyle(9);

  std::string orderstr;
  if(order==0)orderstr="LO";
  else if(order==1 )orderstr="NLO";
		

  TH1D* stylehist=(TH1D*)_CT10_ov_NNPDF_jtpt->Clone("stylehistonly");
  stylehist->Reset("ICES");
  
  stylehist->SetTitle(("Ratios of "+orderstr+" Spectra, R=0."+std::to_string(radius)+", "+etabin_str_arr[etabin]).c_str());
  stylehist->GetXaxis()->SetTitle("Jet p_{T}");
  stylehist->GetXaxis()->SetMoreLogLabels(true);
  stylehist->GetXaxis()->SetNoExponent(true);
  stylehist->GetYaxis()->SetTitle("Ratio to NNPDF NLO");
  stylehist->GetYaxis()->CenterTitle(true);
  stylehist->SetMinimum(0.7);
  stylehist->SetMaximum(1.3);
  
  TLegend* leg=new TLegend(0.6,0.6,0.9,0.9, "");
  leg->SetBorderSize(0.);
  leg->SetFillStyle(0);
  leg->AddEntry(_CT10_ov_NNPDF_jtpt, ("CT10 "+orderstr).c_str(), "lp");
  leg->AddEntry(_CT14_ov_NNPDF_jtpt, ("CT14 "+orderstr).c_str(), "lp");
  leg->AddEntry(_HERA_ov_NNPDF_jtpt, ("HERA "+orderstr).c_str(), "lp");
  leg->AddEntry(_MMHT_ov_NNPDF_jtpt, ("MMHT "+orderstr).c_str(), "lp");
  
  TCanvas* NLO_ratio_canv=new TCanvas("NLO_ratio_canv","NLO_ratio_canv",1600,1400);
  NLO_ratio_canv->SetLogx(1);
  NLO_ratio_canv->SetLogy(0);
  NLO_ratio_canv->cd();
  
  stylehist->Draw();
  one->Draw();
  
  _CT10_ov_NNPDF_jtpt->Draw("SAME");
  _CT14_ov_NNPDF_jtpt->Draw("SAME");
  _HERA_ov_NNPDF_jtpt->Draw("SAME");
  _MMHT_ov_NNPDF_jtpt->Draw("SAME");
  
  leg->Draw();
  
  NLO_ratio_canv->SaveAs(("R0"+std::to_string(radius)+"_"+orderstr+"_ratios_to_NNPDF_etabin"+std::to_string(etabin)+".pdf").c_str());
  NLO_ratio_canv->SaveAs(("R0"+std::to_string(radius)+"_"+orderstr+"_ratios_to_NNPDF_etabin"+std::to_string(etabin)+".png").c_str());

  return;
}
