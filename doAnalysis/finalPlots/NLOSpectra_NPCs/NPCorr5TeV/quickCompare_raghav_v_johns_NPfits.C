#include <cstdlib>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TKey.h"
#include "TClass.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLine.h"
#include "TAttLine.h"
#include "TAxis.h"
#include "TF1.h"


const std::string etabin_str[]={
"0.0 < #||{y} < 0.5",  
  "0.5 < #||{y} < 1.0",
  "1.0 < #||{y} < 1.5",
  "1.5 < #||{y} < 2.0"//,
  //  "2.0 < #||{y} < 2.5",
  //  "2.5 < #||{y} < 3.0",
  //  "3.2 < #||{y} < 4.7"
  };
const int Netabins=sizeof(etabin_str)/sizeof(std::string);
const int MAXetabin=sizeof(etabin_str)/sizeof(std::string)-1;

const std::string john_NPC="PYTHIA8";
//const std::string raghav_NPC="HerwigEE5C";
//const std::string raghav_NPC="HerwigEE4C";
//const std::string raghav_NPC="POWPY8";
//const std::string raghav_NPC="POWPY8CTEQ";
//const std::string raghav_NPC="PYTHIA8";


void quickCompare_raghav_v_johns_NPfits_plot(std::string raghav_NPC_to_use){


  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  TFile* johnsFile=TFile::Open("NPfits_fromJohn.root","READ");  
  TCanvas* john_canv=(TCanvas*)johnsFile->Get("c1");
  
  TFile* raghavsFile=TFile::Open("NLOpNP_InclusiveJets5TeV.root","READ");
  
  
  std::string nucanv_name="NPC_john"+john_NPC+"_raghav"+raghav_NPC_to_use+"_comp_etabin0to"+std::to_string(MAXetabin);
  TCanvas* nucanv=new TCanvas(nucanv_name.c_str(),
			      nucanv_name.c_str(),
			      1600,1600);
  nucanv->cd();
  nucanv->TPad::Divide(2,2,0.005,0.005);//nxpads, nypads, xmargin, ymargin);
  
  std::string rationucanv_name="NPC_john"+john_NPC+"_raghav"+raghav_NPC_to_use+"_ratio_etabin0to"+std::to_string(MAXetabin);
  TCanvas* rationucanv=new TCanvas(rationucanv_name.c_str(),
				   rationucanv_name.c_str(),
				   1600,1600);  
  rationucanv->cd();
  rationucanv->TPad::Divide(2,2,0.005,0.005);
  
  std::string raghavnucanv_name="NPC_raghav"+raghav_NPC_to_use+"_wdatapoints_etabin0to"+std::to_string(MAXetabin);
  TCanvas* raghavnucanv=new TCanvas(raghavnucanv_name.c_str(),
				    raghavnucanv_name.c_str(),
				    1600,1600);  
  raghavnucanv->cd();
  raghavnucanv->TPad::Divide(2,2,0.005,0.005);
  
  //for(int etabin=0;etabin<7; etabin++){
  for(int etabin=0;etabin<=MAXetabin; etabin++){
    std::cout<<"etabin="<<etabin<<std::endl;
    TPad* john_canv_1=(TPad*)john_canv->FindObject(("c1_"+std::to_string(etabin+1)).c_str()
						   );
    TF1* john_fPY8=(TF1*)
      (john_canv_1->FindObject("f"))->Clone(
					    ("johns_fit_etabin"+std::to_string(etabin)).c_str()
					    )
      ;
    std::cout<<"John's parameter0    ="<<john_fPY8->GetParameter(0)<<std::endl;
    std::cout<<"John's parameter0 err="<<john_fPY8-> GetParError(0)<<std::endl;
    std::cout<<"John's parameter1    ="<<john_fPY8->GetParameter(1)<<std::endl;
    std::cout<<"John's parameter1 err="<<john_fPY8-> GetParError(1)<<std::endl;
    std::cout<<"John's parameter2    ="<<john_fPY8->GetParameter(2)<<std::endl;
    std::cout<<"John's parameter2 err="<<john_fPY8-> GetParError(2)<<std::endl;
    
    TH1* john_PY8 =(TH1*)
      (john_fPY8->GetHistogram()) -> Clone(("johns_fit_hist_etabin"+std::to_string(etabin)).c_str());
    john_PY8->SetLineColor(kBlue);
    
    TF1* raghav_fNPC=(TF1*)
      //(raghavsFile->Get(("fNPC_PYTHIA8_R4_etabin"+std::to_string(etabin)).c_str()))->Clone(
      (raghavsFile->Get(("fNPC_"+raghav_NPC_to_use+"_R4_etabin"+std::to_string(etabin)).c_str()))->Clone(
											   ("raghavs_fit_etabin"+std::to_string(etabin)).c_str()
											   );

    TH1* raghav_fNPC_datapoints_toClone=(TH1*)
      //(raghavsFile->Get(("fNPC_PYTHIA8_R4_etabin"+std::to_string(etabin)).c_str()))->Clone(
      (raghavsFile->Get(("NPC_"+raghav_NPC_to_use+"_R4_etabin"+std::to_string(etabin)).c_str()))->Clone(
											   ("toClone_raghavs_NPC_datapoints_etabin"+std::to_string(etabin)).c_str()
													);
    const int nptbins=raghav_fNPC_datapoints_toClone->GetNbinsX();
    std::vector<Double_t> bins;
    for(int i=1; i<=nptbins;i++){
      bins.push_back(raghav_fNPC_datapoints_toClone->GetBinLowEdge(i));
      if(i==(nptbins)){
	bins.push_back(raghav_fNPC_datapoints_toClone->GetBinLowEdge(i) + raghav_fNPC_datapoints_toClone->GetBinWidth(i));
      }
    }
    const double* binsforhist=(double*)bins.data();
    TH1D* raghav_fNPC_datapoints=new TH1D(("raghavs_NPC_datapoints_etabin"+std::to_string(etabin)).c_str(),"",nptbins,binsforhist);
    for(int i=1; i<=nptbins;i++){
      raghav_fNPC_datapoints->SetBinContent(i, raghav_fNPC_datapoints_toClone->GetBinContent(i));
      raghav_fNPC_datapoints->SetBinError(  i, raghav_fNPC_datapoints_toClone->GetBinError(  i));
    }
    
    std::cout<<"Raghav's parameter0    ="<<raghav_fNPC->GetParameter(0)<<std::endl;
    std::cout<<"Raghav's parameter0 err="<<raghav_fNPC-> GetParError(0)<<std::endl;
    std::cout<<"Raghav's parameter1    ="<<raghav_fNPC->GetParameter(1)<<std::endl;
    std::cout<<"Raghav's parameter1 err="<<raghav_fNPC-> GetParError(1)<<std::endl;
    std::cout<<"Raghav's parameter2    ="<<raghav_fNPC->GetParameter(2)<<std::endl;
    std::cout<<"Raghav's parameter2 err="<<raghav_fNPC-> GetParError(2)<<std::endl;

    TH1* raghav_hNPC=(TH1*)
      (raghav_fNPC->GetHistogram()) -> Clone(("raghavs_fit_hist_etabin"+std::to_string(etabin)).c_str());
    raghav_hNPC->SetLineColor(kRed);
    //raghav_hNPC->SetTitle(("PY8 R4 NPCs, "+etabin_str[etabin]).c_str());
    raghav_hNPC->SetTitle(("John v. Raghav R4 NPCs, "+etabin_str[etabin]).c_str());
    raghav_hNPC->GetYaxis()->SetTitle("Correction Factor");
    raghav_hNPC->GetYaxis()->CenterTitle(true);
    raghav_hNPC->GetXaxis()->SetTitle("Jet p_{T} [GeV]");





    float max=raghav_hNPC->GetMaximum();
    if(john_PY8->GetMaximum()>max)
      max=john_PY8->GetMaximum();
    max*=1.01;
    
    float min=raghav_hNPC->GetMinimum();
    if(john_PY8->GetMinimum()<min)
      min=john_PY8->GetMinimum();
    min*=0.98;
    
    
    raghav_hNPC->SetMaximum(max);
    raghav_hNPC->SetMinimum(min);        

    

    nucanv->cd(etabin+1)->SetLogx(1);
    nucanv->cd(etabin+1)->SetLogy(1);
    nucanv->cd(etabin+1);
    raghav_hNPC->GetYaxis()->SetMoreLogLabels(true);
    raghav_hNPC->GetYaxis()->SetNoExponent(true);
    raghav_hNPC->GetXaxis()->SetMoreLogLabels(true);
    raghav_hNPC->GetXaxis()->SetNoExponent(true);

    raghav_hNPC->Draw();
    john_PY8->Draw("SAME");
    
    TLegend* leg=new TLegend(.4,.15,.70,.35);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(raghav_hNPC,(raghav_NPC_to_use+" (Raghav) NPC").c_str(),"l");
    leg->AddEntry(john_PY8,(john_NPC+" (John) NPC").c_str(),"l");
    
    leg->Draw();
    
    
    



    //TF1 ratio
    //([0]+[1]*pow(x,[2]))/([3]+[4]*pow(x,[5]))
    TF1* raghav_john_ratio=new TF1(("raghav_ov_john_rat_ybin"+std::to_string(etabin)).c_str(), 
				   "([0]+[1]*pow(x,[2]))/([3]+[4]*pow(x,[5]))", 
				   raghav_hNPC->GetXaxis()->GetXmin(), 
				   raghav_hNPC->GetXaxis()->GetXmax());
    raghav_john_ratio->SetParameter(0, raghav_fNPC->GetParameter(0));
    raghav_john_ratio->SetParameter(1, raghav_fNPC->GetParameter(1));
    raghav_john_ratio->SetParameter(2, raghav_fNPC->GetParameter(2));
    raghav_john_ratio->SetParameter(3, john_fPY8->GetParameter(0));
    raghav_john_ratio->SetParameter(4, john_fPY8->GetParameter(1));
    raghav_john_ratio->SetParameter(5, john_fPY8->GetParameter(2));

    //  std::string hragjon_rat_name="h_raghav_ov_john_rat_ybin"+std::to_string(etabin);
    TH1* h_raghav_john_ratio=(TH1*)(
    				    ((TH1*)raghav_john_ratio->GetHistogram())
    				    ->Clone(("hNPC_john_raghav_ratio_etabin"+std::to_string(etabin)).c_str())			    );
    float rat_maxy=h_raghav_john_ratio->GetMaximum();
    float rat_miny=h_raghav_john_ratio->GetMinimum();
    rat_maxy*=1.05;
    rat_miny*=0.95;

    h_raghav_john_ratio->Reset("MICES");
    h_raghav_john_ratio->SetMaximum(rat_maxy);
    h_raghav_john_ratio->SetMinimum(rat_miny);
    h_raghav_john_ratio->SetTitle(("Ratio of Fits, "+etabin_str[etabin]).c_str());
    h_raghav_john_ratio->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    h_raghav_john_ratio->GetYaxis()->SetTitle("Raghav NP/John NP");
    h_raghav_john_ratio->GetYaxis()->CenterTitle(true);
    
    
    rationucanv->cd(etabin+1)->SetLogx(1);
    //rationucanv->cd(etabin+1)->SetLogy(1);
    rationucanv->cd(etabin+1);
    
    h_raghav_john_ratio->GetXaxis()->SetMoreLogLabels(true);
    h_raghav_john_ratio->GetXaxis()->SetNoExponent(true);
    //h_raghav_john_ratio->GetYaxis()->SetNoExponent(true);
    //h_raghav_john_ratio->GetYaxis()->SetMoreLogLabels(true);
    h_raghav_john_ratio->Draw();
    raghav_john_ratio->Draw("SAME");
    
    float dpmin=99999., dpmax=-1.;
    for(int k=1; k<=raghav_fNPC_datapoints->GetNbinsX();k++){
      float content=raghav_fNPC_datapoints->GetBinContent(k);
      if(content>dpmax)dpmax=content;
      if( !(content>0.) && !(content<0.))continue;
      else if(content <dpmin)dpmin=content;
    }

    if(raghav_NPC_to_use=="POWPY8"){
      raghav_fNPC_datapoints->SetMarkerColor(kMagenta);
      raghav_fNPC->SetLineColor(kMagenta);
    }
    else if (raghav_NPC_to_use=="PYTHIA8"){
      raghav_fNPC_datapoints->SetMarkerColor(kBlack);
      if(etabin==0)dpmax*=1.50;
    }


    raghav_fNPC_datapoints->SetMaximum(dpmax*1.10);
    raghav_fNPC_datapoints->SetMinimum(dpmin*0.90);
    raghav_fNPC_datapoints->SetTitle((etabin_str[etabin]).c_str());
    raghav_fNPC_datapoints->GetYaxis()->CenterTitle(true);
    raghav_fNPC_datapoints->GetYaxis()->SetTitle("NP Corr. Factor");
    raghav_fNPC_datapoints->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    raghav_fNPC_datapoints->GetXaxis()->SetMoreLogLabels(true);
    raghav_fNPC_datapoints->GetXaxis()->SetNoExponent(true);
    raghav_fNPC_datapoints->GetYaxis()->SetMoreLogLabels(true);
    raghav_fNPC_datapoints->GetYaxis()->SetNoExponent(true);

    TLegend* leg2=new TLegend(.15,.6,.4,.85);
    leg2->SetBorderSize(0);
    leg2->SetFillStyle(0);
    leg2->AddEntry(raghav_fNPC,           (raghav_NPC_to_use+" fit").c_str(), "l");
    leg2->AddEntry(raghav_fNPC_datapoints,"data points used"         , "lpe");
    
    
    raghavnucanv->cd(etabin+1)->SetLogx(true);
    raghavnucanv->cd(etabin+1)->SetLogy(true);
    raghavnucanv->cd(etabin+1);
    raghav_fNPC_datapoints->Draw();
    raghav_fNPC->Draw("SAME");
    leg2->Draw();

  }
  
  
  
  
  
  
  nucanv->cd();
  nucanv->SaveAs(
		 ((std::string)nucanv->GetName()+".png").c_str()
		 );
  rationucanv->cd();
  rationucanv->SaveAs(			
		      ((std::string)rationucanv->GetName()+".png").c_str()
		      );
  raghavnucanv->cd();
  raghavnucanv->SaveAs(			
		      ((std::string)raghavnucanv->GetName()+".png").c_str()
		      );
  
  
  
  return;
}

void quickCompare_raghav_v_johns_NPfits(){
  quickCompare_raghav_v_johns_NPfits_plot("HerwigEE5C");
  quickCompare_raghav_v_johns_NPfits_plot("HerwigEE4C");
  quickCompare_raghav_v_johns_NPfits_plot("POWPY8");
  quickCompare_raghav_v_johns_NPfits_plot("POWPY8CTEQ");
  quickCompare_raghav_v_johns_NPfits_plot("PYTHIA8");
  return;
}
