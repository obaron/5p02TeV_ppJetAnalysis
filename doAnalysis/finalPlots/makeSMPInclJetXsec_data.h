void printEvtCountTable(std::string outdir);
void  makeSMPInclJetXsec_fracstaterrData_ratios(std::string outdir, TFile* fout=NULL);
void  makeSMPInclJetXsec_covmatData_onePadOneEta (std::string outdir, TFile* fout=NULL);
void  makeSMPInclJetXsec_PY8vNLOunfdata_ratios (std::string outdir, TFile* fout=NULL);//SMEARED NLO v PY8 unf data, ratios











//--------------------------------------------------------------------------------------------------------------------------------

void printEvtCountTable(std::string outdir){
  std::cout<<"running printEvtCountTable"<<std::endl;

  bool funcDebug=true;
  if(funcDebug)std::cout<<"in printEvtCountTable"<<std::endl;
  if(funcDebug)std::cout<<"outdir is"<<outdir <<std::endl;
  
  TFile* fin=TFile::Open((EVTCOUNTS+EVTCOUNTS_file+".root").c_str(),"READ");
  
  std::cout<<"Opening Data File"<<std::endl;
  TFile* fdata=TFile::Open("/cms/heavyion/obaron/5p02TeV_ppJetAnalysis/outputCondor/06.25.19_outputCondor/ppData_HighPtJetTrig_ak3PFJets_06-25-19_jetPlots_0.0eta2.0_SMPbins/HighPtJetTrig_noMB_ak3PF-allFiles.root","READ");
  TFile* fMC=TFile::Open("/cms/heavyion/obaron/5p02TeV_ppJetAnalysis/outputCondor/09.30.20_outputCondor/ppMC_Py8_CUETP8M1_QCDjetAllPtBins_ak3PFJets_09-30-20_jetPlots_0.0eta2.0/Py8_CUETP8M1_QCDjetAllPtBins_ak3PF-allFiles.root","READ");
  
  TH1D* h_NEvents_Jet80_read   =(TH1D*)fin->Get("NEvents_Jet80_read"   );
  TH1D* h_NEvents_Jet80_skimCut=(TH1D*)fin->Get("NEvents_Jet80_skimCut");
  TH1D* h_NEvents_Jet80_vzCut  =(TH1D*)fin->Get("NEvents_Jet80_vzCut"  );
  //TH1D* h_NEvents_Jet80_PFMETfracCut=(TH1D*)fin->Get("NEvents_Jet80_PFMETfracCut"  );
  TH1D* h_NEvents_Jet80_is80   =(TH1D*)fin->Get("NEvents_Jet80_is80"   );
  
  TH1D* h_NEvents_read   =(TH1D*)fdata->Get("NEvents_read"   );
  TH1D* h_NEvents_vzCut=(TH1D*)fdata->Get("NEvents_vzCut");
  TH1D* h_NEvents_skimCut  =(TH1D*)fdata->Get("NEvents_skimCut"  );

  TH1D* h_NEvents_MCread   =(TH1D*)fMC->Get("NEvents_read"   );
  TH1D* h_NEvents_MCvzCut=(TH1D*)fMC->Get("NEvents_vzCut");
  TH1D* h_NEvents_MCskimCut  =(TH1D*)fMC->Get("NEvents_skimCut"  );
  
  double NEvents_read		= h_NEvents_read		->GetBinContent(1);
  double NEvents_vzCut		= h_NEvents_vzCut		->GetBinContent(1);
  double NEvents_skimCut	= h_NEvents_skimCut		->GetBinContent(1);

  double NEvents_MCread		= h_NEvents_MCread		->GetBinContent(1);
  double NEvents_MCvzCut	= h_NEvents_MCvzCut		->GetBinContent(1);
  double NEvents_MCskimCut	= h_NEvents_MCskimCut		->GetBinContent(1);


  double Nevts_jet80_read   = h_NEvents_Jet80_read   ->GetBinContent(1);
  double Nevts_jet80_skimcut= h_NEvents_Jet80_skimCut->GetBinContent(1);
  double Nevts_jet80_vzcut  = h_NEvents_Jet80_vzCut  ->GetBinContent(1);
  //double Nevts_jet80_PFMETfracCut  = h_NEvents_Jet80_PFMETfracCut  ->GetBinContent(1);
  double Nevts_jet80_is80   = h_NEvents_Jet80_is80   ->GetBinContent(1);

  double perc_Nevts_jet80_read   =100.*(Nevts_jet80_read/Nevts_jet80_read); 
  double perc_Nevts_jet80_skimcut=100.*(Nevts_jet80_skimcut/Nevts_jet80_read); 
  double perc_Nevts_jet80_vzcut  =100.*(Nevts_jet80_vzcut/Nevts_jet80_read); 
  //double perc_Nevts_jet80_PFMETfracCut  =100.*(Nevts_jet80_PFMETfracCut/Nevts_jet80_read); 
  double perc_Nevts_jet80_is80   =100.*(Nevts_jet80_is80/Nevts_jet80_read); 
  
  double perc_NEvents_read		= 100*(NEvents_read/NEvents_read);
  double perc_NEvents_vzCut		= 100*(NEvents_vzCut/NEvents_read);
  double perc_NEvents_skimCut	= 100*(NEvents_skimCut/NEvents_read);

  double perc_NEvents_MCread		= 100*(NEvents_MCread/NEvents_MCread);
  double perc_NEvents_MCvzCut		= 100*(NEvents_MCvzCut/NEvents_MCread);
  double perc_NEvents_MCskimCut		= 100*(NEvents_MCskimCut/NEvents_MCread);

  
  std::cout<<std::endl;
  std::cout<<" ----- FinalPlots Data Event Count Report ----- "<<std::endl;
  std::cout<<"# Events ............................................ in Dataset: "<<  NEvents_read   <<", Fraction of total: "		<< perc_NEvents_read   <<std::endl;
  std::cout<<"# Events after HBHENoise, BeamScraping, and PV  quality  filters: "<<  NEvents_skimCut<<", Fraction of total: "		<< perc_NEvents_skimCut <<std::endl;
  std::cout<<"# Events after ................................. |vz|< 24 cm cut: "<<  NEvents_vzCut  <<", Fraction of total: "		<< perc_NEvents_vzCut <<std::endl;  
  
  std::cout<<std::endl;
  std::cout<<" ----- FinalPlots MC Event Count Report ----- "<<std::endl;
  std::cout<<"# Events ............................................ in Dataset: "<<  NEvents_MCread   <<", Fraction of total: "		<< perc_NEvents_MCread   <<std::endl;
  std::cout<<"# Events after HBHENoise, BeamScraping, and PV  quality  filters: "<<  NEvents_MCskimCut<<", Fraction of total: "		<< perc_NEvents_MCskimCut <<std::endl;
  std::cout<<"# Events after ................................. |vz|< 24 cm cut: "<<  NEvents_MCvzCut  <<", Fraction of total: "		<< perc_NEvents_MCvzCut <<std::endl;  
    
  
  
  
  std::cout<<std::endl;
  std::cout<<" ----- Jet80 PD Event Count Report ----- "<<std::endl;
  std::cout<<"# Events ............................................ in Dataset: "<<  Nevts_jet80_read   <<", Fraction of total: "<< perc_Nevts_jet80_read   <<std::endl;
  std::cout<<"# Events after HBHENoise, BeamScraping, and PV  quality  filters: "<<  Nevts_jet80_skimcut<<", Fraction of total: "<< perc_Nevts_jet80_skimcut<<std::endl;
  std::cout<<"# Events after ................................. |vz|< 24 cm cut: "<<  Nevts_jet80_vzcut  <<", Fraction of total: "<< perc_Nevts_jet80_vzcut  <<std::endl;
  //std::cout<<"# Events after ............................. PFMETFrac < 0.3 cut: "<<  Nevts_jet80_PFMETfracCut  <<", Fraction of total: "<< perc_Nevts_jet80_PFMETfracCut  <<std::endl;
  std::cout<<"# Events after ............... passing trigger jet req for HLT80: "<<  Nevts_jet80_is80   <<", Fraction of total: "<< perc_Nevts_jet80_is80   <<std::endl;
  
  TH1D* h_NEvents_LowJets_read   =(TH1D*)fin->Get("NEvents_LowJets_read"   );
  TH1D* h_NEvents_LowJets_skimCut=(TH1D*)fin->Get("NEvents_LowJets_skimCut");
  TH1D* h_NEvents_LowJets_vzCut  =(TH1D*)fin->Get("NEvents_LowJets_vzCut"  );
  //TH1D* h_NEvents_LowJets_PFMETfracCut=(TH1D*)fin->Get("NEvents_LowJets_PFMETfracCut"  );
  TH1D* h_NEvents_LowJets_is40   =(TH1D*)fin->Get("NEvents_LowJets_is40"   );
  TH1D* h_NEvents_LowJets_is60   =(TH1D*)fin->Get("NEvents_LowJets_is60"   );

  double Nevts_lowjets_read   = h_NEvents_LowJets_read   ->GetBinContent(1);
  double Nevts_lowjets_skimcut= h_NEvents_LowJets_skimCut->GetBinContent(1);
  double Nevts_lowjets_vzcut  = h_NEvents_LowJets_vzCut  ->GetBinContent(1);
  //double Nevts_lowjets_PFMETfracCut  = h_NEvents_LowJets_PFMETfracCut  ->GetBinContent(1);
  double Nevts_lowjets_is60   = h_NEvents_LowJets_is60   ->GetBinContent(1);
  double Nevts_lowjets_is40   = h_NEvents_LowJets_is40   ->GetBinContent(1);
  double Nevts_lowjets_is60or40   = Nevts_lowjets_is60+Nevts_lowjets_is40;
 
  double perc_Nevts_lowjets_read   =100.*(Nevts_lowjets_read/Nevts_lowjets_read); 
  double perc_Nevts_lowjets_skimcut=100.*(Nevts_lowjets_skimcut/Nevts_lowjets_read); 
  double perc_Nevts_lowjets_vzcut  =100.*(Nevts_lowjets_vzcut/Nevts_lowjets_read);
  //double perc_Nevts_lowjets_PFMETfracCut  =100.*(Nevts_lowjets_PFMETfracCut/Nevts_lowjets_read); 
  double perc_Nevts_lowjets_is60   =100.*(Nevts_lowjets_is60/Nevts_lowjets_read); 
  double perc_Nevts_lowjets_is40   =100.*(Nevts_lowjets_is40/Nevts_lowjets_read); 
  double perc_Nevts_lowjets_is60or40   =100.*(Nevts_lowjets_is60or40/Nevts_lowjets_read);  

  std::cout<<std::endl;
  std::cout<<" ----- LowerJets PD Event Count Report ----- "<<std::endl;
  std::cout<<"# Events ............................................ in Dataset: "<< Nevts_lowjets_read     <<", Fraction of total: "<< perc_Nevts_lowjets_read     <<std::endl;
  std::cout<<"# Events after HBHENoise, BeamScraping, and PV  quality  filters: "<< Nevts_lowjets_skimcut  <<", Fraction of total: "<< perc_Nevts_lowjets_skimcut  <<std::endl;
  std::cout<<"# Events after ..................................|vz|< 24 cm cut: "<< Nevts_lowjets_vzcut    <<", Fraction of total: "<< perc_Nevts_lowjets_vzcut    <<std::endl;
  //std::cout<<"# Events after ............................. PFMETFrac < 0.3 cut: "<<  Nevts_lowjets_PFMETfracCut  <<", Fraction of total: "<< perc_Nevts_lowjets_PFMETfracCut  <<std::endl;
  std::cout<<"# Events after ...... passing trigger jet req for HLT60 or HLT40: "<< Nevts_lowjets_is60or40 <<", Fraction of total: "<< perc_Nevts_lowjets_is60or40 <<std::endl;
  std::cout<<"# Events ......................... passing trigger jet req for HLT40 only: "<<Nevts_lowjets_is40 <<", Fraction of total: "<< perc_Nevts_lowjets_is40 <<std::endl;
  std::cout<<"# Events ......................... passing trigger jet req for HLT60 only: "<<Nevts_lowjets_is60 <<", Fraction of total: "<< perc_Nevts_lowjets_is60 <<std::endl;
  
  TH1D* h_NEvents_MC_read   =(TH1D*)fin->Get("NEvents_MC_read"   );
  TH1D* h_NEvents_MC_skimCut=(TH1D*)fin->Get("NEvents_MC_skimCut");
  TH1D* h_NEvents_MC_vzCut  =(TH1D*)fin->Get("NEvents_MC_vzCut"  );
  //TH1D* h_NEvents_MC_PFMETfracCut  =(TH1D*)fin->Get("NEvents_MC_PFMETfracCut"  );
  
  double Nevts_mc_read   = h_NEvents_MC_read   ->GetBinContent(1);
  double Nevts_mc_skimcut= h_NEvents_MC_skimCut->GetBinContent(1);
  double Nevts_mc_vzcut  = h_NEvents_MC_vzCut  ->GetBinContent(1);
  //double Nevts_mc_PFMETfracCut  = h_NEvents_MC_PFMETfracCut  ->GetBinContent(1);

  double perc_Nevts_mc_read   = 100.*(Nevts_mc_read/Nevts_mc_read);
  double perc_Nevts_mc_skimcut= 100.*(Nevts_mc_skimcut/Nevts_mc_read);
  double perc_Nevts_mc_vzcut  = 100.*(Nevts_mc_vzcut/Nevts_mc_read);
  //double perc_Nevts_mc_PFMETfracCut  = 100.*(Nevts_mc_PFMETfracCut/Nevts_mc_read);

  std::cout<<std::endl;
  std::cout<<" ----- PYTHIA8 PD Event Count Report ----- "<<std::endl;
  std::cout<<"# Events ............................................ in Dataset: "<< Nevts_mc_read     <<", Fraction of total: "<< perc_Nevts_mc_read     <<std::endl;
  std::cout<<"# Events after HBHENoise, BeamScraping, and PV  quality  filters: "<< Nevts_mc_skimcut  <<", Fraction of total: "<< perc_Nevts_mc_skimcut  <<std::endl;
  std::cout<<"# Events after ................................. |vz|< 24 cm cut: "<< Nevts_mc_vzcut    <<", Fraction of total: "<< perc_Nevts_mc_vzcut    <<std::endl;
  //std::cout<<"# Events after ............................. PFMETFrac < 0.3 cut: "<< Nevts_mc_PFMETfracCut    <<", Fraction of total: "<< perc_Nevts_mc_PFMETfracCut    <<std::endl;


  h_NEvents_Jet80_read    ->Delete();
  h_NEvents_Jet80_skimCut ->Delete();
  h_NEvents_Jet80_vzCut	  ->Delete();
  //h_NEvents_Jet80_PFMETfracCut	  ->Delete();
  h_NEvents_Jet80_is80    ->Delete();

  h_NEvents_LowJets_read   ->Delete();
  h_NEvents_LowJets_skimCut->Delete();
  h_NEvents_LowJets_vzCut  ->Delete();
  //h_NEvents_LowJets_PFMETfracCut	  ->Delete();
  h_NEvents_LowJets_is40   ->Delete();
  h_NEvents_LowJets_is60   ->Delete();

  h_NEvents_MC_read      ->Delete();
  h_NEvents_MC_skimCut	 ->Delete();
  h_NEvents_MC_vzCut     ->Delete();
  //h_NEvents_MC_PFMETfracCut     ->Delete();
  
  

  //// ============================================================================================ //
  //// ======================================= Jet Counts ========================================= //
  //// ============================================================================================ //
  //std::cout<<std::endl;
  //std::cout<<" ----- Jet80 PD Event Count Report ----- "<<std::endl;
  //std::cout<<"# Events ............................................ in Dataset: "<<  Nevts_jet80_read   <<", Fraction of total: "<< perc_Nevts_jet80_read   <<std::endl;
  //std::cout<<"# Events after HBHENoise, BeamScraping, and PV  quality  filters: "<<  Nevts_jet80_skimcut<<", Fraction of total: "<< perc_Nevts_jet80_skimcut<<std::endl;
  //std::cout<<"# Events after ..................................|vz|< 24 cm cut: "<<  Nevts_jet80_vzcut  <<", Fraction of total: "<< perc_Nevts_jet80_vzcut  <<std::endl;
  //std::cout<<"# Events after ............... passing trigger jet req for HLT80: "<<  Nevts_jet80_is80   <<", Fraction of total: "<< perc_Nevts_jet80_is80   <<std::endl;
  //
  //std::cout<<std::endl;
  //std::cout<<" ----- LowerJets PD Event Count Report ----- "<<std::endl;
  //std::cout<<"# Events ............................................ in Dataset: "<< Nevts_lowjets_read     <<", Fraction of total: "<< perc_Nevts_lowjets_read     <<std::endl;
  //std::cout<<"# Events after HBHENoise, BeamScraping, and PV  quality  filters: "<< Nevts_lowjets_skimcut  <<", Fraction of total: "<< perc_Nevts_lowjets_skimcut  <<std::endl;
  //std::cout<<"# Events after ..................................|vz|< 24 cm cut: "<< Nevts_lowjets_vzcut    <<", Fraction of total: "<< perc_Nevts_lowjets_vzcut    <<std::endl;
  //std::cout<<"# Events after ...... passing trigger jet req for HLT60 or HLT40: "<< Nevts_lowjets_is60or40 <<", Fraction of total: "<< perc_Nevts_lowjets_is60or40 <<std::endl;
  //std::cout<<"# Events ......................... passing trigger jet req for HLT40 only: "<<Nevts_lowjets_is40 <<", Fraction of total: "<< perc_Nevts_lowjets_is40 <<std::endl;
  //std::cout<<"# Events ......................... passing trigger jet req for HLT60 only: "<<Nevts_lowjets_is60 <<", Fraction of total: "<< perc_Nevts_lowjets_is60 <<std::endl;
  //
  //
  //std::cout<<std::endl;
  //
  //std::cout<<" ----- PYTHIA8 PD Event Count Report ----- "<<std::endl;
  //std::cout<<"# Events ............................................ in Dataset: "<< Nevts_mc_read     <<", Fraction of total: "<< perc_Nevts_mc_read     <<std::endl;
  //std::cout<<"# Events after HBHENoise, BeamScraping, and PV  quality  filters: "<< Nevts_mc_skimcut  <<", Fraction of total: "<< perc_Nevts_mc_skimcut  <<std::endl;
  //std::cout<<"# Events after ..................................|vz|< 24 cm cut: "<< Nevts_mc_vzcut    <<", Fraction of total: "<< perc_Nevts_mc_vzcut    <<std::endl;

  return;
}














//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_fracstaterrData_ratios (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_fracstaterrData_ratios"<<std::endl;
  
  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }

  TH1D* spectra[netabins]={};		
	                                
  TH1D* measspectra[netabins]={};	
  TH1D* ratios_fracstatunc[netabins]={};
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";//also has JEC systematics
    //std::cout<<"filepath="<<filepath<<std::endl;
    TFile* file=TFile::Open(( filepath).c_str(), "READ");




    measspectra[i] =  (TH1D*)(
			      (
			       (TH1D*)file->Get("Data_meas_1GeVbins") 
			       )->Clone( 
					("Data_meas_1GeVbins_ybin"+std::to_string(i)).c_str() 
				     )
			      );


    
    ////USE BINNING IN HEADER
    //int nbins=-1;
    //double* ptbins=setBinning_etabin(i, &nbins);
    //measspectra[i]=(TH1D*)measspectra[i]->TH1::Rebin(nbins, ((std::string)measspectra[i]->GetName()+"_rebin").c_str(), ptbins );
    ////END USE BINNING IN HEADER

    //USE BINNING IN UNF DATA HIST
    spectra[i] =  (TH1D*)(
    			     (
    			      (TH1D*)file->Get("Data_unf") 
    			      )->Clone( 
    				       ("Data_unf_ybin"+std::to_string(i)).c_str() 
    					)
    			     );    
    //gonna have to get the binning here and rebin the stuff from the fastnlo files respectively
    int nbins=spectra[i]->GetNbinsX();
    std::vector<double> ptbins;
    for(int j=1;j<=nbins;j++)
      ptbins.push_back(spectra[i]->GetBinLowEdge(j));
    ptbins.push_back(spectra[i]->GetBinLowEdge(nbins)+spectra[i]->GetBinWidth(nbins));
    measspectra[i]=(TH1D*)measspectra[i]->TH1::Rebin(nbins, ((std::string)measspectra[i]->GetName()+"_rebin").c_str(), ((double*)ptbins.data()) );
    //END USE BINNING IN UNF DATA HIST

    //DATA STAT UNC
    ratios_fracstatunc[i]=(TH1D*) measspectra[i]->Clone(("Data_FracStatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_fracstatunc[i]->Reset("MICES");
    for(int bin=1;bin<=nbins;bin++){
      ratios_fracstatunc[i]->SetBinContent(bin, measspectra[i]->GetBinError(bin));
      ratios_fracstatunc[i]->SetBinError(bin, 1.e-30);
      measspectra[i]->SetBinError(bin,1.e-30);
    }
    ratios_fracstatunc[i]->Divide(measspectra[i]);
    ratios_fracstatunc[i]->SetMarkerSize(0.);  ratios_fracstatunc[i]->SetMarkerColor(kBlack);   ratios_fracstatunc[i]->SetMarkerStyle(kFullCircle);
    ratios_fracstatunc[i]->SetLineColor(kBlack);    
    
    ptbins.clear();
  }
  
  
  


  //TCanvas* canv=makeSMPRatioCanvas("fracstaterrData_SMPInclJetXsec_ratios");  
  TCanvas* canv=makeSMPRatioCanvas("fracstaterrData_SMPInclJetXsec_currentunfbinning_ratios");  
  //TCanvas* canv=makeSMPRatioCanvas("fracstaterrData_SMPInclJetXsec_lt50perc_nogaps_ratios");  
  //TCanvas* canv=makeSMPRatioCanvas("fracstaterrData_covmatErrors_SMPInclJetXsec_ratios");  

  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();


  for(int i=0; i<netabins; i++){
    
    canv->cd(i+1)->SetLogy(1);
    canv->cd(i+1)->SetLogx(1);
    canv->cd(i+1);

    ratios_fracstatunc[i]->SetTitle("");    
    ratios_fracstatunc[i]->SetMaximum(6.);
    ratios_fracstatunc[i]->GetYaxis()->CenterTitle(true);
    ratios_fracstatunc[i]->GetXaxis()->SetNoExponent(true);
    ratios_fracstatunc[i]->GetXaxis()->SetMoreLogLabels(true);
    setHistLabels(ratios_fracstatunc[i],"RECO Jet p_{T} [GeV]","Fractional Stat. Uncertainty");

    ratios_fracstatunc[i]->Draw("HIST");    
    
    float xlo=ratios_fracstatunc[i]->GetBinLowEdge(1);
    float xhi=
      ratios_fracstatunc[i]->GetBinLowEdge(ratios_fracstatunc[i]->GetNbinsX()) +   
      ratios_fracstatunc[i]->GetBinWidth(  ratios_fracstatunc[i]->GetNbinsX() );
    TLine* one     =makeTLine(xlo, 0.5 , xhi, 0.5);    
    one     ->Draw();       
   
    if(i==0){
      TLegend* leg=makeLegend(0.56, 0.68, 0.87, 0.87);
      leg->SetHeader("Merged SMP Inclusive Jet Bins");
      leg->AddEntry(ratios_fracstatunc[i],"Fractional Stat. Unc.","l");
      leg->AddEntry(one, "50% Unc.","l");
      leg->Draw();
    }
    
    TPaveText* desc=NULL;
    if(i==0)desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    else    desc=makePaveText( 0.15, 0.74, 0.45, 0.88);
    desc->AddText(etabin_strs[i].c_str());
    std::string ptrange=ptcuts_lo;
    ptrange+=std::to_string( (int)xhi)+" GeV";
    desc->AddText(ptrange.c_str());
    if(i==0)desc->AddText(jettype.c_str());
    desc->Draw();
    
    SMPtitle->Draw();  
    
  }

  //makeSMPInclJetXsec_fracstaterrData_ratios
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    spectra[i]->Delete();		
    measspectra[i]->Delete();	
    ratios_fracstatunc[i]->Delete();
  }

  return;
}






//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_covmatData_onePadOneEta (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_covmatData_onePadOneEta"<<std::endl;
  
  const int netabins=PY8_UNFDIR_DATA_Nfiles;
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH2D* covmatrix[netabins]={};
  float zmax=-1.;
  float zmin=99999999999999999999.;
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    covmatrix[i] =  (TH2D*)(
			(
			 (TH2D*)file->Get("Data_covmat_rebin") 
			 )->Clone( 
				  ("Data_covmat_ybin"+std::to_string(i)).c_str() 
				   )
			    );
    float th2max=covmatrix[i]->GetMaximum();
    float th2min=getnonzeromin((TH2*)covmatrix[i]);
    if(th2max>zmax)zmax=th2max;
    if(th2min<zmin)zmin=th2min;
    
  }
  
  TCanvas* canv=makeSMPRatioCanvas("covmatData_onePadOneEta");

  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  bool dologx=true, dology=true, dologz=true;
  for(int i=0; i<netabins; i++){
      
    canv->cd(i+1)->SetLogx(dologx);//maybe set to 1?
    canv->cd(i+1)->SetLogy(dology);//maybe set to 1?
    canv->cd(i+1)->SetLogz(dologz);//maybe set to 1?
    canv->cd(i+1);
    
    setHistLabels((TH2D*)covmatrix[i], "RECO Jet p_{T} [GeV]","RECO Jet p_{T} [GeV]");//,"Covariance [pb^{-2}]");
    
    if(dologx)covmatrix[i]->GetXaxis()->SetNoExponent(true);
    if(dologx)covmatrix[i]->GetXaxis()->SetMoreLogLabels(true);
    if(dology)covmatrix[i]->GetYaxis()->SetNoExponent(true);
    if(dology)covmatrix[i]->GetYaxis()->SetMoreLogLabels(true);
    covmatrix[i]->SetAxisRange(zmin*.9,zmax*1.1, "Z");
    covmatrix[i]->Draw("COLZ");    

    TPaveText* desc=makePaveText( 0.38, 0.90, 0.62, 1.00);
    desc->AddText(etabin_strs[i].c_str());
    desc->AddText(jettype.c_str());
    desc->Draw();
    SMPtitle->Draw();
    
  }
  
  //makeSMPInclJetXsec_covmatData_onePadOneEta
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    covmatrix[i]->Delete();
  }
  
  return;
}













//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_PY8vNLOunfdata_ratios (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_PY8vNLOunfdata_ratio"<<std::endl;

  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* NLOunfspectra[netabins]={};
  TH1D* PY8unfspectra[netabins]={};
  //TH1D* smrPY8unfspectra[netabins]={};

  TH1D* ratios[netabins]={};
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string NLOunffilepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";//also has JEC systematics
    TFile* NLOunffile=TFile::Open(( NLOunffilepath).c_str(), "READ");
    
    //NLOSPECTRA ONLY, NO SYST
    NLOunfspectra[i] =  (TH1D*)(
			     (
			      (TH1D*)NLOunffile->Get("Data_unf") 
			      )->Clone( 
				       ("Data_unf_ybin"+std::to_string(i)).c_str() 
					)
			     );
    

    std::string PY8unffilepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_file_array[i] + ".root";
    TFile* PY8unffile=TFile::Open(( PY8unffilepath).c_str(), "READ");
    
    PY8unfspectra[i] =  (TH1D*)(
			     (
			      (TH1D*)PY8unffile->Get("Data_unf") 
			      )->Clone( 
				       ("Data_unf_ybin"+std::to_string(i)).c_str() 
					)
			     );

    ratios[i]=(TH1D*) PY8unfspectra[i]->Clone(("Data_NLO_PY8_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(NLOunfspectra[i]);
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.6);    ratios[i]->SetMaximum(1.4);
    //setRatioHistLabels((TH1D*)ratios[i], "PY8 Unf. / NLO #otimes NP Unf.");
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to NLO #otimes NP Unf. Data");


    //std::string smrPY8unffilepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_file_array[i] + ".root";
    //TFile* smrPY8unffile=TFile::Open(( smrPY8unffilepath).c_str(), "READ");
    //
    //smrPY8unfspectra[i] =  (TH1D*)(
    //				   (
    //				    (TH1D*)smrPY8unffile->Get("Data_unf") 
    //				    )->Clone( 
    //					     ("Data_unf_ybin"+std::to_string(i)).c_str() 
    //					      )
    //				   );
    //
    //ratios[i]=(TH1D*) PY8unfspectra[i]->Clone(("Data_NLO_PY8_ratio_ybin"+std::to_string(i)).c_str());
    //ratios[i]->Divide(NLOunfspectra[i]);
    //ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    //ratios[i]->SetLineColor(kBlack);    
    //ratios[i]->SetMinimum(0.6);    ratios[i]->SetMaximum(1.4);
    ////setRatioHistLabels((TH1D*)ratios[i], "PY8 Unf. / NLO #otimes NP Unf.");
    //setRatioHistLabels((TH1D*)ratios[i], "Ratio to NLO #otimes NP Unf. Data");
    

  }
  
  
 
  TCanvas* canv=makeSMPRatioCanvas("PY8vNLOunfdata_SMPInclJetXsec_ratio");
  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){


    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST ][ ");    
    one     ->Draw();       
    ratios[i]->Draw("HIST ][ SAME");    
    

    


    if(i==0){
      TLegend* leg=makeLegend(0.59, 0.63, 0.87, 0.87);
      leg->AddEntry(ratios[i],"Full SIM PY8 unf.","lp");
      //leg->AddEntry(ratios2[i],"Smeared PY8 unf.","lp");
      leg->Draw();}
    
    TPaveText* desc=NULL;
    if(i==0)desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    else    desc=makePaveText( 0.15, 0.74, 0.45, 0.88);
    desc->AddText(etabin_strs[i].c_str());
    std::string ptrange=ptcuts_lo;
    ptrange+=std::to_string( (int)xhi)+" GeV";
    desc->AddText(ptrange.c_str());
    if(i==0)desc->AddText(jettype.c_str());
    desc->Draw();
        
    SMPtitle->Draw();  
    
  }
  
  
  //makeSMPInclJetXsec_PY8vNLOunfdata_ratios
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    NLOunfspectra[i]->Delete();
    PY8unfspectra[i]->Delete()  ;
    ratios[i]->Delete();
  }
  
  return;
}


