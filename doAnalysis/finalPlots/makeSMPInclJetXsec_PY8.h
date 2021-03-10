void  makeSMPInclJetXsec_PY8JERmu_onePadOneEta (std::string outdir, TFile* fout=NULL);
void  makeSMPInclJetXsec_PY8JERsigma_onePadOneEta (std::string outdir, TFile* fout=NULL);

void  makeSMPInclJetXsec_NLOSmearingFits_onePadAllEta (std::string outdir, TFile* fout=NULL);
void  makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadAllEta (std::string outdir, TFile* fout=NULL);
void  makeSMPInclJetXsec_NLOSmearingFits_onePadOneEta (std::string outdir, TFile* fout=NULL);
void  makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadOneEta (std::string outdir, TFile* fout=NULL);







//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_PY8JERsigma_onePadOneEta (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_PY8JERsigma_onePadOneEta"<<std::endl;

  
  const int netabins=JERDIR_MC_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* sigma_datapoints[netabins]={};
  float lineptmax[netabins]={0.};
  float ptmax[netabins]={0.};
  float lineptmin[netabins]={0.};
  float ptmin[netabins]={0.};
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= JERDIR_MC + JERDIR_MC_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    sigma_datapoints[i] =  (TH1D*)(
				(
				 (TH1D*)file->Get("hSigma_fit") 
				    )->Clone( 
					     ("hSigma_datapoints_ybin"+std::to_string(i)).c_str() 
					      )
				);        
    
    //std::cout<<"hello bin #"<<i<<std::endl;
    sigma_datapoints[i]->GetYaxis()->SetTitle("Gaussian Core Fit #sigma");
    sigma_datapoints[i]->GetYaxis()->SetTitleOffset(0.95);
    sigma_datapoints[i]->GetYaxis()->SetTitleSize(0.05);
    sigma_datapoints[i]->GetYaxis()->SetLabelOffset(0.005);
    sigma_datapoints[i]->GetYaxis()->SetLabelSize(0.045);
    sigma_datapoints[i]->GetYaxis()->CenterTitle(true);

    sigma_datapoints[i]->GetXaxis()->SetTitle("Jet p_{T} [GeV]");    
    //sigma_datapoints[i]->GetXaxis()->SetTitleOffset(1.0);
    sigma_datapoints[i]->GetXaxis()->SetTitleSize(0.045);
    sigma_datapoints[i]->GetXaxis()->SetLabelOffset(0.005);
    sigma_datapoints[i]->GetXaxis()->SetLabelSize(0.045);

    bool minimumset=false;
    for(int j=1; j<=sigma_datapoints[i]->GetNbinsX();j++){
      //std::cout<<"hello pt bin #"<<i<<std::endl;
      float lowedge  =sigma_datapoints[i]->GetBinLowEdge(j);          //std::cout<<"lowedge ="<<lowedge <<std::endl;
      float highedge =sigma_datapoints[i]->GetBinWidth(j)+lowedge;    //std::cout<<"highedge="<<highedge<<std::endl;
      float sigma       =sigma_datapoints[i]->GetBinContent(j);	      //std::cout<<"mu      ="<<mu      <<std::endl;
      float sigmaerr    =sigma_datapoints[i]->GetBinError(j);      	      //std::cout<<"muerr   ="<<muerr   <<std::endl;
      if(!(sigma>0.))continue;
      if(!minimumset){
	ptmin[i]=lowedge;
	lineptmin[i]=lowedge-(highedge-lowedge);//...why do i do this again? guess we will see...
	std::cout<<"MINIMUM SET: ptmin[i]="<<ptmin[i]<<std::endl;
	minimumset=true;
      }
      if(ptmax[i]<highedge){
	ptmax[i]=highedge;
	lineptmax[i]=highedge+sigma_datapoints[i]->GetBinWidth(j+1);//...why do i do this again? guess we will see...	  
      }
    }
  }
  
  
  
  TCanvas* canv=makeSMPRatioCanvas("PY8JERsigma_onePadOneEta");
  
  TPaveText* SMPtitle=makeSimPaveTextTitleRatio();
  bool dologx=true;
  for(int i=0; i<netabins; i++){
    
    canv->cd(i+1)->SetLogx(dologx);//maybe set to 1?
    canv->cd(i+1)->SetLogy(0);
    canv->cd(i+1);
    
    float xlo=ptmin[i];
    float xhi=ptmax[i];    
    float linexlo=lineptmin[i];    
    float linexhi=lineptmax[i];    
    
    sigma_datapoints[i]->SetTitle("");
    if(dologx)sigma_datapoints[i]->GetXaxis()->SetNoExponent(true);
    if(dologx)sigma_datapoints[i]->GetXaxis()->SetMoreLogLabels(true);
    sigma_datapoints[i]->SetAxisRange(linexlo, xhi, "X");
    sigma_datapoints[i]->SetAxisRange(0.03,0.24, "Y");
    //if(i==0)sigma_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==1)sigma_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==2)sigma_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==3)sigma_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    sigma_datapoints[i]->Draw("HIST E ][");    
    
    
    TLine* line1        =makeTLine( linexlo, 0.05 ,linexhi , 0.05);    line1    ->Draw();       
    TLine* line2        =makeTLine( linexlo, 0.15 ,linexhi , 0.15);    line2    ->Draw();       

    sigma_datapoints[i]->Draw("HIST E ][ SAME");    
    

    if(i==1){
      TLegend* leg=makeLegend(0.65, 0.75, 0.90, 0.85);
      leg->AddEntry(sigma_datapoints[i],"PYTHIA8","lpe");
      leg->Draw();
    }
    
    TPaveText* desc=NULL;
    if(i==0)desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    else    desc=makePaveText( 0.15, 0.74, 0.45, 0.88);
    desc->AddText(etabin_strs[i].c_str());
    std::string ptrange=std::to_string( (int)xlo) +
                            " GeV < Jet p_{T} < " +
                        std::to_string( (int)xhi) + " GeV";
    desc->AddText(ptrange.c_str());
    if(i==0)desc->AddText(jettype.c_str());
    desc->Draw();
    
    SMPtitle->Draw();  
  }
  
  //makeSMPInclJetXsec_PY8JERsigma_onePadOneEta
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    sigma_datapoints[i]->Delete();
  }

  return;
}


//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_PY8JERmu_onePadOneEta (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_PY8JERmu_onePadOneEta"<<std::endl;  
  const int netabins=JERDIR_MC_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* mu_datapoints[netabins]={};
  float lineptmax[netabins]={0.};
  float ptmax[netabins]={0.};
  float lineptmin[netabins]={0.};
  float ptmin[netabins]={0.};
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= JERDIR_MC + JERDIR_MC_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    mu_datapoints[i] =  (TH1D*)(
				(
				 (TH1D*)file->Get("hMean_fit") 
				    )->Clone( 
					     ("hMean_datapoints_ybin"+std::to_string(i)).c_str() 
					      )
				);        
    
    //std::cout<<"hello bin #"<<i<<std::endl;
    mu_datapoints[i]->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    mu_datapoints[i]->GetYaxis()->SetTitle("Gaussian Core Fit #mu");
    mu_datapoints[i]->GetYaxis()->SetTitleOffset(0.95);
    //    std::cout<<"mu_datapoints["<<i<<"]->GetYaxis()->GetTitleOffset()="<<mu_datapoints[i]->GetYaxis()->GetTitleOffset()<<std::endl;   
    //    std::cout<<"mu_datapoints["<<i<<"]->GetYaxis()->GetTitleSize()  ="<<mu_datapoints[i]->GetYaxis()->GetTitleSize()<<std::endl;
    std::cout<<"mu_datapoints["<<i<<"]->GetYaxis()->GetLabelOffset()="<<mu_datapoints[i]->GetYaxis()->GetLabelOffset()<<std::endl;
    std::cout<<"mu_datapoints["<<i<<"]->GetYaxis()->GetLabelSize()  ="<<mu_datapoints[i]->GetYaxis()->GetLabelSize()<<std::endl;    
    std::cout<<"mu_datapoints["<<i<<"]->GetXaxis()->GetTitleOffset()="<<mu_datapoints[i]->GetXaxis()->GetTitleOffset()<<std::endl;
    std::cout<<"mu_datapoints["<<i<<"]->GetXaxis()->GetTitleSize()  ="<<mu_datapoints[i]->GetXaxis()->GetTitleSize()<<std::endl;
    std::cout<<"mu_datapoints["<<i<<"]->GetXaxis()->GetLabelOffset()="<<mu_datapoints[i]->GetXaxis()->GetLabelOffset()<<std::endl;
    std::cout<<"mu_datapoints["<<i<<"]->GetXaxis()->GetLabelSize()  ="<<mu_datapoints[i]->GetXaxis()->GetLabelSize()<<std::endl;
    mu_datapoints[i]->GetYaxis()->CenterTitle(true);
    bool minimumset=false;
    for(int j=1; j<=mu_datapoints[i]->GetNbinsX();j++){
      //std::cout<<"hello pt bin #"<<i<<std::endl;
      float lowedge  =mu_datapoints[i]->GetBinLowEdge(j);          //std::cout<<"lowedge ="<<lowedge <<std::endl;
      float highedge =mu_datapoints[i]->GetBinWidth(j)+lowedge;    //std::cout<<"highedge="<<highedge<<std::endl;
      float mu       =mu_datapoints[i]->GetBinContent(j);	      //std::cout<<"mu      ="<<mu      <<std::endl;
      float muerr    =mu_datapoints[i]->GetBinError(j);      	      //std::cout<<"muerr   ="<<muerr   <<std::endl;
      if(!(mu>0.))continue;
      if(!minimumset){
	ptmin[i]=lowedge;
	lineptmin[i]=lowedge-(highedge-lowedge);//...why do i do this again? guess we will see...
	std::cout<<"MINIMUM SET: ptmin[i]="<<ptmin[i]<<std::endl;
	minimumset=true;
      }
      if(ptmax[i]<highedge){
	ptmax[i]=highedge;
	lineptmax[i]=highedge+mu_datapoints[i]->GetBinWidth(j+1);//...why do i do this again? guess we will see...	  
      }
    }
  }
  
  
  
  TCanvas* canv=makeSMPRatioCanvas("PY8JERmu_onePadOneEta");
  
  TPaveText* SMPtitle=makeSimPaveTextTitleRatio();
  bool dologx=true;
  for(int i=0; i<netabins; i++){
    
    canv->cd(i+1)->SetLogx(dologx);//maybe set to 1?
    canv->cd(i+1)->SetLogy(0);
    canv->cd(i+1);
    
    float xlo=ptmin[i];
    float xhi=ptmax[i];    
    float linexlo=lineptmin[i];    
    float linexhi=lineptmax[i];    
    
    mu_datapoints[i]->SetTitle("");
    if(dologx)mu_datapoints[i]->GetXaxis()->SetNoExponent(true);
    if(dologx)mu_datapoints[i]->GetXaxis()->SetMoreLogLabels(true);
    mu_datapoints[i]->SetAxisRange(linexlo, xhi, "X");
    mu_datapoints[i]->SetAxisRange(0.98,1.04, "Y");
    //if(i==0)mu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==1)mu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==2)mu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==3)mu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    mu_datapoints[i]->Draw("HIST E ][");    

    
    TLine* onep01     =makeTLine( linexlo, 1.01 ,linexhi , 1.01);    onep01     ->Draw();       
    TLine* one        =makeTLine( linexlo, 1.00 ,linexhi , 1.00);    one     ->Draw();       
    TLine* p99        =makeTLine( linexlo, 0.99 ,linexhi , 0.99);    p99     ->Draw();       

    mu_datapoints[i]->Draw("HIST E ][ SAME");    
    

    if(i==1){
      TLegend* leg=makeLegend(0.65, 0.75, 0.90, 0.85);
      leg->AddEntry(mu_datapoints[i],"PYTHIA8","lpe");
      leg->Draw();
    }
    
    TPaveText* desc=NULL;
    if(i==0)desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    else    desc=makePaveText( 0.15, 0.74, 0.45, 0.88);
    desc->AddText(etabin_strs[i].c_str());
    std::string ptrange=std::to_string( (int)xlo) +
                            " GeV < Jet p_{T} < " +
                        std::to_string( (int)xhi) + " GeV";
    desc->AddText(ptrange.c_str());
    if(i==0)desc->AddText(jettype.c_str());
    desc->Draw();
    
    SMPtitle->Draw();  
  }
  
  //makeSMPInclJetXsec_PY8JERmu_onePadOneEta
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    mu_datapoints[i]->Delete();
  }
  //canv->Delete();

  return;
}



//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOSmearingFits_onePadAllEta (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_NLOSmearingFits_onePadAllEta"<<std::endl;
  
  const int netabins=JERDIR_MC_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }

  TF1* JERfit[netabins]={};
  TH1D* JERfithist[netabins]={};//to make it easier to draw stuff
  float maxy=-1., miny=100000000.;//global min/maxy
  
  //first get the plots, scale accordingly, get the min/max y's
  for(int i=0; i<netabins; i++){
    std::string filepath= JERDIR_MC + JERDIR_MC_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    JERfit[i] =  (TF1*)(
			 (
			  (TF1*)file->Get("SigmaFit_f") 
			  )->Clone( 
				   ("SigmaFit_f_ybin"+std::to_string(i)).c_str() 
				    )
			 );
    
    JERfithist[i]=(TH1D*)(
			  JERfit[i]->GetHistogram() 
			  );
    JERfithist[i]->SetName(("SigmaFit_f_hist_ybin"+std::to_string(i)).c_str());
    if(maxy<JERfithist[i]->GetMaximum())      maxy=JERfithist[i]->GetMaximum();
    if(miny>JERfithist[i]->GetMinimum())      miny=JERfithist[i]->GetMinimum();
    
    
  }
  
  // now style hists stuff
  JERfit[0]->SetLineColor(kRed);      
  JERfit[1]->SetLineColor(kGreen);    
  JERfit[2]->SetLineColor(kBlue);     
  JERfit[3]->SetLineColor(kMagenta);  
  
  JERfithist[0]=(TH1D*)JERfithist[0]->Clone("forDrawingOnly_JERfithist");
  JERfithist[0]->Reset("MICES");
  JERfithist[0]->SetLineColorAlpha(kBlack, 1.);
  JERfithist[0]->SetMarkerColorAlpha(kBlack, 1.);
  JERfithist[0]->SetMaximum(maxy*1.2);
  JERfithist[0]->SetMinimum(miny/1.4);
  JERfithist[0]->SetTitle("");  
  JERfithist[0]->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
  JERfithist[0]->GetXaxis()->SetNoExponent(true);
  JERfithist[0]->GetXaxis()->SetMoreLogLabels(true);  
  JERfithist[0]->GetYaxis()->SetTitle("#sigma / #mu");
    

  //first hist to be drawn, so this gets the max/min/labels/titles set up
  TLegend* leg=makeLegend(0.55, 0.60, 0.90, 0.85);
  //leg->SetHeader( "PYTHIA8 Gaussian Core Resolution            ","C" );
  leg->SetHeader( "PYTHIA8 Gaussian Core Resolution" );
  leg->AddEntry((TObject*)0,  jettype.c_str(), "");
  
  TCanvas* canv=makeSMPSpectraCanvas("NLOSmearingFits_onePadAllEta");
  canv->SetLogy(0);
  canv->SetLogx(0);
  canv->cd();
  
  JERfithist[0]->Draw("");
  
  for(int i=0; i<netabins; i++){
    JERfit[i]->Draw("SAME");
    std::string legstr=etabin_strs[i] ;
    leg->AddEntry( JERfit[i], 
		   (legstr).c_str() ,"lp");        
    
    
  }
  
  leg->Draw();
  
  TPaveText* SMPtitle=makeSimPaveTextTitle();
  SMPtitle->Draw();  
  
  //makeSMPInclJetXsec_NLOSmearingFits_onePadAllEta
  saveCanv(outdir, canv, fout);

  for(int i=0; i<netabins;i++){
    JERfit[i]->Delete();
  }
  
  return;
}



//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadAllEta (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadAllEta"<<std::endl;
  
  const int netabins=JERDIR_MC_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }

  TF1* JERfit[netabins]={};
  TH1D* JERfithist[netabins]={};//to make it easier to draw stuff
  float maxy=-1., miny=100000000.;//global min/maxy
  
  //first get the plots, scale accordingly, get the min/max y's
  for(int i=0; i<netabins; i++){
    std::string filepath= JERDIR_MC + JERDIR_MC_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    JERfit[i] =  (TF1*)(
			 (
			  (TF1*)file->Get("SigmaFit_f") 
			  )->Clone( 
				   ("SigmaFit_f_ybin"+std::to_string(i)).c_str() 
				    )
			);
    JERfit[i]->SetParameter(0,
			    JERfit[i]->GetParameter(0)*1.1);
    JERfit[i]->SetParameter(1,
			    JERfit[i]->GetParameter(1)*1.1);
    
    JERfithist[i]=(TH1D*)(
			  JERfit[i]->GetHistogram() 
			  );
    JERfithist[i]->SetName(("SigmaFit_f_hist_ybin"+std::to_string(i)).c_str());
    if(maxy<JERfithist[i]->GetMaximum())      maxy=JERfithist[i]->GetMaximum();
    if(miny>JERfithist[i]->GetMinimum())      miny=JERfithist[i]->GetMinimum();
    
    
  }
  
  // now style hists stuff
  JERfit[0]->SetLineColor(kRed);      
  JERfit[1]->SetLineColor(kGreen);    
  JERfit[2]->SetLineColor(kBlue);     
  JERfit[3]->SetLineColor(kMagenta);  
  
  JERfithist[0]=(TH1D*)JERfithist[0]->Clone("forDrawingOnly_JERfithistwSFs");
  JERfithist[0]->Reset("MICES");
  JERfithist[0]->SetLineColorAlpha(kBlack, 1.);
  JERfithist[0]->SetMarkerColorAlpha(kBlack, 1.);
  JERfithist[0]->SetMaximum(maxy*1.2);
  JERfithist[0]->SetMinimum(miny/1.4);
  JERfithist[0]->SetTitle("");  
  JERfithist[0]->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
  JERfithist[0]->GetXaxis()->SetNoExponent(true);
  JERfithist[0]->GetXaxis()->SetMoreLogLabels(true);  
  JERfithist[0]->GetYaxis()->SetTitle("#sigma / #mu");
    

  //first hist to be drawn, so this gets the max/min/labels/titles set up
  TLegend* leg=makeLegend(0.55, 0.60, 0.90, 0.85);
  //leg->SetHeader( "PYTHIA8 Gaussian Core Resolution            ","C" );
  leg->SetHeader( "PYTHIA8 JER Smearing Fits" );
  leg->AddEntry((TObject*)0,  "w/ Scale Factor = 1.1 +/- 0.1", "");
  leg->AddEntry((TObject*)0,  jettype.c_str(), "");
  
  TCanvas* canv=makeSMPSpectraCanvas("NLOSmearingFitswSFs_onePadAllEta");
  canv->SetLogy(0);
  canv->SetLogx(0);
  canv->cd();
  
  JERfithist[0]->Draw("");
  
  for(int i=0; i<netabins; i++){
    JERfit[i]->Draw("SAME");
    std::string legstr=etabin_strs[i] ;
    leg->AddEntry( JERfit[i], 
		   (legstr).c_str() ,"lp");        
    
    
  }
  
  leg->Draw();
  
  TPaveText* SMPtitle=makeSimPaveTextTitle();
  SMPtitle->Draw();  
  
  //makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadAllEta
  saveCanv(outdir, canv, fout);

  for(int i=0; i<netabins;i++){
    JERfit[i]->Delete();
  }    
  
  return;
}

//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOSmearingFits_onePadOneEta (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_NLOSmearingFits_onePadOneEta"<<std::endl;
  
  const int netabins=JERDIR_MC_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TF1* JERfit[netabins]={};	       
  TF1* JERfit_sysup[netabins]={};      
  TF1* JERfit_sysdown[netabins]={};    
                                       
  TH1D* sigmu_datapoints[netabins]={}; 
  TH1D* sigma_datapoints[netabins]={}; 
  TH1D* mu_datapoints[netabins]={};    
  float lineptmax[netabins]={0.};
  float ptmax[netabins]={0.};
  float lineptmin[netabins]={0.};
  float ptmin[netabins]={0.};             
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= JERDIR_MC + JERDIR_MC_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    JERfit[i] =  (TF1*)(
			(
			 (TF1*)file->Get("SigmaFit_f") 
			 )->Clone( 
				  ("SigmaFit_f_ybin"+std::to_string(i)).c_str() 
				   )
			);
    
    JERfit_sysup[i] =  (TF1*)(
			      (
			       (TF1*)file->Get("SigmaFit_sysup_f") 
			       )->Clone( 
					("SigmaFit_sysup_f_ybin"+std::to_string(i)).c_str() 
					 )

			      );
    
    JERfit_sysdown[i] =  (TF1*)(
				(
			 (TF1*)file->Get("SigmaFit_sysdown_f") 
			 )->Clone( 
				  ("SigmaFit_sysdown_f_ybin"+std::to_string(i)).c_str() 
				   )
				
				);
    
    sigma_datapoints[i] =  (TH1D*)(
				   (
				    (TH1D*)file->Get("hSigma_fit") 
				    )->Clone( 
					     ("hSigma_datapoints_ybin"+std::to_string(i)).c_str() 
					      )
				   );        

    mu_datapoints[i] =  (TH1D*)(
				(
				 (TH1D*)file->Get("hMean_fit") 
				    )->Clone( 
					     ("hMean_datapoints_ybin"+std::to_string(i)).c_str() 
					      )
				);        
    
    sigmu_datapoints[i]=(TH1D*) sigma_datapoints[i]->Clone(
							   ("hSigmu_datapoints_ybin"+std::to_string(i)).c_str()
							   );
    //std::cout<<"hello bin #"<<i<<std::endl;
    sigmu_datapoints[i]->Reset("MICES");
    sigmu_datapoints[i]->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    sigmu_datapoints[i]->GetYaxis()->SetTitle("#sigma / #mu");
    bool minimumset=false;
    for(int j=1; j<=sigma_datapoints[i]->GetNbinsX();j++){
      //std::cout<<"hello pt bin #"<<i<<std::endl;
      float lowedge  =sigma_datapoints[i]->GetBinLowEdge(j);          //std::cout<<"lowedge ="<<lowedge <<std::endl;
      float highedge =sigma_datapoints[i]->GetBinWidth(j)+lowedge;    //std::cout<<"highedge="<<highedge<<std::endl;
      float sigma    =sigma_datapoints[i]->GetBinContent(j);	      //std::cout<<"sigma   ="<<sigma   <<std::endl;
      float sigmaerr =sigma_datapoints[i]->GetBinError(j);	      //std::cout<<"sigmaerr="<<sigmaerr<<std::endl;
      float mu       =mu_datapoints[i]->GetBinContent(j);	      //std::cout<<"mu      ="<<mu      <<std::endl;
      float muerr    =mu_datapoints[i]->GetBinError(j);      	      //std::cout<<"muerr   ="<<muerr   <<std::endl;
      if(!(mu>0.))continue;
      float sigmu=sigma/mu;
      float sigmuerr=(sigma/mu)*sqrt(
				     pow(sigmaerr/sigma, 2)+
				     pow(muerr/mu, 2)
				     );
      
      sigmu_datapoints[i]->SetBinContent(j,sigmu);
      sigmu_datapoints[i]->SetBinError(j,sigmuerr);            
      if(!minimumset){
	ptmin[i]=lowedge;
	lineptmin[i]=lowedge-(highedge-lowedge);
	std::cout<<"MINIMUM SET: ptmin[i]="<<ptmin[i]<<std::endl;
	minimumset=true;
      }
      if(ptmax[i]<highedge){
	ptmax[i]=highedge;
	lineptmax[i]=highedge+sigma_datapoints[i]->GetBinWidth(j+1);
	  
      }
    }
    
    

  }
  
  
  
  TCanvas* canv=makeSMPRatioCanvas("NLOSmearingFits_onePadOneEta");

  TPaveText* SMPtitle=makeSimPaveTextTitleRatio();
  bool dologx=true;
  for(int i=0; i<netabins; i++){

    canv->cd(i+1)->SetLogx(dologx);//maybe set to 1?
    canv->cd(i+1)->SetLogy(0);
    canv->cd(i+1);

    float xlo=ptmin[i];
    float xhi=ptmax[i];    
    float linexlo=lineptmin[i];    
    float linexhi=lineptmax[i];    
    
    sigmu_datapoints[i]->SetTitle("");
    if(dologx)sigmu_datapoints[i]->GetXaxis()->SetNoExponent(true);
    if(dologx)sigmu_datapoints[i]->GetXaxis()->SetMoreLogLabels(true);
    sigmu_datapoints[i]->SetAxisRange(linexlo, xhi, "X");
    sigmu_datapoints[i]->SetAxisRange(0.03,0.24, "Y");
    //if(i==0)sigmu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==1)sigmu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==2)sigmu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==3)sigmu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    sigmu_datapoints[i]->Draw("HIST E ][");    

    
    TLine* p05     =makeTLine( linexlo,.05 ,linexhi , .05);    p05     ->Draw();       
    //TLine* p10     =makeTLine( linexlo,.10 ,linexhi , .10);    p10     ->Draw();       
    TLine* p15     =makeTLine( linexlo,.15 ,linexhi , .15);    p15     ->Draw();       
    sigmu_datapoints[i]->Draw("HIST E ][ SAME");    
    JERfit[i]        ->Draw("SAME");    
    JERfit_sysup[i]  ->Draw("SAME");    
    JERfit_sysdown[i]->Draw("SAME");    
    

    
    
    TPaveText* desc=NULL;
    if(i==0)desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    else    desc=makePaveText( 0.15, 0.74, 0.45, 0.88);
    desc->AddText(etabin_strs[i].c_str());
    std::string ptrange=std::to_string( (int)xlo)+
      " GeV < Jet p_{T} < "+
      std::to_string( (int)xhi)+" GeV";
    desc->AddText(ptrange.c_str());
    if(i==0)desc->AddText(jettype.c_str());
    desc->Draw();

    
    if(i==1){
      TLegend* leg=makeLegend(0.56, 0.68, 0.87, 0.87);
      leg->AddEntry(sigmu_datapoints[i],"PYTHIA8 Resolution","lpe");
      leg->AddEntry(JERfit[i],"Gauss Core Fit Resolution","lp");
      leg->AddEntry(JERfit_sysdown[i],"Upper/Lower Fit Unc.","l");
      leg->Draw();
    }
    
    
    
    SMPtitle->Draw();  
  }
  
  //makeSMPInclJetXsec_NLOSmearingFits_onePadOneEta
  saveCanv(outdir, canv, fout);

  for(int i=0; i<netabins;i++){
    JERfit[i]->Delete();	           
    JERfit_sysup[i]->Delete();      
    JERfit_sysdown[i]->Delete();    
    
    sigmu_datapoints[i]->Delete(); 
    sigma_datapoints[i]->Delete(); 
    mu_datapoints[i]->Delete();    
  }


  return;
}


//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadOneEta (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadOneEta"<<std::endl;
  
  const int netabins=JERDIR_MC_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TF1* JERfit[netabins]={};
  TF1* JERfit_sysup[netabins]={};
  TF1* JERfit_sysdown[netabins]={};
  
  TH1D* sigmu_datapoints[netabins]={};
  TH1D* sigma_datapoints[netabins]={};
  TH1D* mu_datapoints[netabins]={};
  float lineptmax[netabins]={0.};
  float ptmax[netabins]={0.};
  float lineptmin[netabins]={0.};
  float ptmin[netabins]={0.};
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= JERDIR_MC + JERDIR_MC_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    JERfit[i] =  (TF1*)(
			(
			 (TF1*)file->Get("SigmaFit_f") 
			 )->Clone( 
				  ("SigmaFit_f_ybin"+std::to_string(i)).c_str() 
				   )
			);    
    
    JERfit_sysup[i] =  (TF1*)( JERfit[i]->Clone( 
						("SigmaFit_sysup_f_ybin"+std::to_string(i)).c_str() 
						 )			       
			       );
    
    JERfit_sysdown[i] =  (TF1*)( JERfit[i]->Clone( 
						  ("SigmaFit_sysdown_f_ybin"+std::to_string(i)).c_str() 
						   )				 
				 );
    
    JERfit[i]->SetParameter(0,
			    JERfit[i]->GetParameter(0)*(1.1));
    JERfit[i]->SetParameter(1,
			    JERfit[i]->GetParameter(1)*(1.1));

    JERfit_sysup[i]->SetParameter(0,
				  JERfit_sysup[i]->GetParameter(0)*(1.2));
    JERfit_sysup[i]->SetParameter(1,
				  JERfit_sysup[i]->GetParameter(1)*(1.2));
    JERfit_sysup[i]->SetLineColor(kRed);

    JERfit_sysdown[i]->SetParameter(0,
				  JERfit_sysdown[i]->GetParameter(0)*(1.0));
    JERfit_sysdown[i]->SetParameter(1,
				  JERfit_sysdown[i]->GetParameter(1)*(1.0));
    JERfit_sysdown[i]->SetLineColor(kRed);
    
    
    sigma_datapoints[i] =  (TH1D*)(
				   (
				    (TH1D*)file->Get("hSigma_fit") 
				    )->Clone( 
					     ("hSigma_datapoints_ybin"+std::to_string(i)).c_str() 
					      )
				   );        

    mu_datapoints[i] =  (TH1D*)(
				(
				 (TH1D*)file->Get("hMean_fit") 
				    )->Clone( 
					     ("hMean_datapoints_ybin"+std::to_string(i)).c_str() 
					      )
				);        
    
    sigmu_datapoints[i]=(TH1D*) sigma_datapoints[i]->Clone(
							   ("hSigmu_datapoints_ybin"+std::to_string(i)).c_str()
							   );
    //std::cout<<"hello bin #"<<i<<std::endl;
    sigmu_datapoints[i]->Reset("MICES");
    sigmu_datapoints[i]->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    sigmu_datapoints[i]->GetYaxis()->SetTitle("#sigma / #mu");
    sigmu_datapoints[i]->SetMarkerColorAlpha(kBlack, 0.);
    sigmu_datapoints[i]->SetLineColorAlpha(kBlack, 0.);
    
    bool minimumset=false;
    for(int j=1; j<=sigma_datapoints[i]->GetNbinsX();j++){
      //std::cout<<"hello pt bin #"<<i<<std::endl;
      float lowedge  =sigma_datapoints[i]->GetBinLowEdge(j);          //std::cout<<"lowedge ="<<lowedge <<std::endl;
      float highedge =sigma_datapoints[i]->GetBinWidth(j)+lowedge;    //std::cout<<"highedge="<<highedge<<std::endl;
      float sigma    =sigma_datapoints[i]->GetBinContent(j);	      //std::cout<<"sigma   ="<<sigma   <<std::endl;
      float sigmaerr =sigma_datapoints[i]->GetBinError(j);	      //std::cout<<"sigmaerr="<<sigmaerr<<std::endl;
      float mu       =mu_datapoints[i]->GetBinContent(j);	      //std::cout<<"mu      ="<<mu      <<std::endl;
      float muerr    =mu_datapoints[i]->GetBinError(j);      	      //std::cout<<"muerr   ="<<muerr   <<std::endl;
      if(!(mu>0.))continue;
      float sigmu=sigma/mu;
      float sigmuerr=(sigma/mu)*sqrt(
				     pow(sigmaerr/sigma, 2)+
				     pow(muerr/mu, 2)
				     );
      
      sigmu_datapoints[i]->SetBinContent(j,sigmu);
      sigmu_datapoints[i]->SetBinError(j,sigmuerr);            
      if(!minimumset){
	ptmin[i]=lowedge;
	lineptmin[i]=lowedge-(highedge-lowedge);
	std::cout<<"MINIMUM SET: ptmin[i]="<<ptmin[i]<<std::endl;
	minimumset=true;
      }
      if(ptmax[i]<highedge){
	ptmax[i]=highedge;
	lineptmax[i]=highedge+sigma_datapoints[i]->GetBinWidth(j+1);
	  
      }
    }
    
    

  }
  
  
  
  TCanvas* canv=makeSMPRatioCanvas("NLOSmearingFitswSFs_onePadOneEta");

  TPaveText* SMPtitle=makeSimPaveTextTitleRatio();
  bool dologx=true;
  for(int i=0; i<netabins; i++){

    canv->cd(i+1)->SetLogx(dologx);//maybe set to 1?
    canv->cd(i+1)->SetLogy(0);
    canv->cd(i+1);

    float xlo=ptmin[i];
    float xhi=ptmax[i];    
    float linexlo=lineptmin[i];    
    float linexhi=lineptmax[i];    
    
    sigmu_datapoints[i]->SetTitle("");
    if(dologx)sigmu_datapoints[i]->GetXaxis()->SetNoExponent(true);
    if(dologx)sigmu_datapoints[i]->GetXaxis()->SetMoreLogLabels(true);
    sigmu_datapoints[i]->SetAxisRange(linexlo, xhi, "X");
    sigmu_datapoints[i]->SetAxisRange(0.03,0.24, "Y");
    //if(i==0)sigmu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==1)sigmu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==2)sigmu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    //if(i==3)sigmu_datapoints[i]->SetAxisRange(0.04,0.20, "Y");
    sigmu_datapoints[i]->Draw("HIST E ][");    

    
    TLine* p05     =makeTLine( linexlo,.05 ,linexhi , .05);    p05     ->Draw();       
    //TLine* p10     =makeTLine( linexlo,.10 ,linexhi , .10);    p10     ->Draw();       
    TLine* p15     =makeTLine( linexlo,.15 ,linexhi , .15);    p15     ->Draw();       
    sigmu_datapoints[i]->Draw("HIST E ][ SAME");    
    JERfit[i]        ->Draw("SAME");    
    JERfit_sysup[i]  ->Draw("SAME");    
    JERfit_sysdown[i]->Draw("SAME");    
    

    
    
    
    TPaveText* desc=NULL;
    if(i==0)desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    else    desc=makePaveText( 0.15, 0.74, 0.45, 0.88);
    desc->AddText(etabin_strs[i].c_str());
    std::string ptrange=std::to_string( (int)xlo)+
      " GeV < Jet p_{T} < "+
      std::to_string( (int)xhi)+" GeV";
    desc->AddText(ptrange.c_str());
    if(i==0)desc->AddText(jettype.c_str());
    desc->Draw();
    
    if(i==1){
      TLegend* leg=makeLegend(0.56, 0.68, 0.87, 0.87);
      leg->AddEntry((TObject*)0,"PYTHIA8 JER Smearing Fits","");
      leg->AddEntry((TObject*)0,"w/ Scale Factor = 1.1 +/- 0.1","");
      leg->AddEntry(JERfit[i],"Fit","lp");
      leg->AddEntry(JERfit_sysdown[i],"Upper/Lower Unc.","l");
      leg->Draw();
      
    }
    
    
    SMPtitle->Draw();  
  }
  
  //makeSMPInclJetXsec_NLOSmearingFitswSFs_onePadOneEta
  saveCanv(outdir, canv, fout);

  for(int i=0; i<netabins;i++){
    JERfit[i]->Delete();	           
    JERfit_sysup[i]->Delete();      
    JERfit_sysdown[i]->Delete();    
    
    sigmu_datapoints[i]->Delete(); 
    sigma_datapoints[i]->Delete(); 
    mu_datapoints[i]->Delete();    
  }

  
  return;
}
