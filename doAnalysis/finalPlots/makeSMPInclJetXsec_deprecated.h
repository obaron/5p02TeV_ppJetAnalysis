void  makeSMPInclJetXsec_PY8unfdata_DebugLaptop_ratios (std::string outdir, TFile* fout=NULL);//FULL RECO PY8 unf, truth v. unf data, ratios
void  makeSMPInclJetXsec_JOHNNLOunfdata (std::string outdir, TFile* fout=NULL);//SMEARED NLO unf, my data v. john's data
void  makeSMPInclJetXsec_JOHNNLOunfdata_ratios (std::string outdir, TFile* fout=NULL);//SMEARED NLO unf, my data v. john's data, ratios
void  makeSMPInclJetXsec_JOAONLOunfdata_ratios (std::string outdir, TFile* fout=NULL);//SMEARED NLO unf, my data v. john's data, ratios
void  makeSMPInclJetXsec_JOHNmeasdata (std::string outdir, TFile* fout=NULL);//RECO data, my data v. john's data
void  makeSMPInclJetXsec_JOHNmeasdata_ratios (std::string outdir, TFile* fout=NULL);//RECOdata, my data v. john's data, ratios

void  makeSMPInclJetXsec_NLOunfdataAcrossy_ratios (std::string outdir, TFile* fout=NULL);//SMEARED NLO unf, truth v. unf data, ratios
void  makeSMPInclJetXsec_PY8unfdataAcrossy_ratios (std::string outdir, TFile* fout=NULL);//SMEARED NLO unf, truth v. unf data, ratios





void  makeSMPInclJetXsec_NLOsyst_ratios (std::string outdir, TFile* fout=NULL, std::string order="");//SMEARED NLO unf, truth v. unf data, ratios
void  makeSMPInclJetXsec_NLOunfdata_ratios (std::string outdir, TFile* fout=NULL, std::string mode="");//SMEARED NLO unf, truth v. unf data, ratios

//move me to top
void  makeSMPInclJetXsec_PY8unfdata_DebugLaptop_ratios (std::string outdir, TFile* fout){

  const int netabins=PY8_UNFDIR_DATA_Nfiles;  
  //if(netabins!=n_etabin_strs){
  //  printetabinerrormessage();
  //  return;
  //}

  TH1D* mcspectra[netabins]={};

  TH1D* spectra[netabins]={};
  //TH1D* spectra_JECup[netabins]={};
  //TH1D* spectra_JECdown[netabins]={};
  //TH1D* spectra_JERup[netabins]={};
  //TH1D* spectra_JERdown[netabins]={};

  TH1D* ratios[netabins]={};
  TH1D* ratios_statunc[netabins]={};
  //TH1D* ratios_JECup[netabins]={};
  //TH1D* ratios_JECdown[netabins]={};
  //TH1D* ratios_JERup[netabins]={};
  //TH1D* ratios_JERdown[netabins]={};
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_unf") 
			   )->Clone( 
				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
				     )
			  );

    mcspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)file->Get("MC_truth") 
			     )->Clone( 
				      ("MC_truth_ybin"+std::to_string(i)).c_str() 
				       )
			    );        

//    spectra_JECup[i] =  (TH1D*)(
//				(
//			   (TH1D*)file->Get("JECsys/Data_unf_JECsysup") 
//			   )->Clone( 
//				    ("Data_unf_JECsysup_ybin"+std::to_string(i)).c_str() 
//				     )
//			  );
//
//    spectra_JECdown[i] =  (TH1D*)(
//				(
//			   (TH1D*)file->Get("JECsys/Data_unf_JECsysdown") 
//			   )->Clone( 
//				    ("Data_unf_JECsysdown_ybin"+std::to_string(i)).c_str() 
//				     )
//			  );
//
//    std::string JERsysfilepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_SYST_file_array[1] +YBIN_TAG_array[i]+ ".root";//also has JEC systematics
//    TFile* JERsysfile=TFile::Open((JERsysfilepath).c_str(),"READ");
//
//
//    spectra_JERup[i] =  (TH1D*)(
//				( //TYPO!!! JEC SHOULD BE JER!!! FIX ME!!!
//			   (TH1D*)JERsysfile->Get("JECsys/Data_unf_JERsysup") 
//			   )->Clone( 
//				    ("Data_unf_JERsysup_ybin"+std::to_string(i)).c_str() 
//				     )
//			  );
//
//    spectra_JERdown[i] =  (TH1D*)(
//				(
//			   (TH1D*)JERsysfile->Get("JECsys/Data_unf_JERsysdown") 
//			   )->Clone( 
//				    ("Data_unf_JERsysdown_ybin"+std::to_string(i)).c_str() 
//				     )
//			  );
    
    
    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(mcspectra[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.4);    ratios[i]->SetMaximum(1.6);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to PYTHIA8");

    //DATA STAT UNC
    ratios_statunc[i]=(TH1D*) spectra[i]->Clone(("Data_MC_StatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_statunc[i]->Divide(mcspectra[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    
    

//    //JEC SYS
//    ratios_JECup[i]=(TH1D*) spectra_JECup[i]->Clone(("Data_unf_JECsysup_MC_ratio_ybin"+std::to_string(i)).c_str());
//    ratios_JECup[i]->Divide(mcspectra[i]);
//    ratios_JECup[i]->SetMarkerSize(0);  ratios_JECup[i]->SetMarkerColor(kBlack);   ratios_JECup[i]->SetMarkerStyle(kFullCircle);
//    ratios_JECup[i]->SetLineColor(kRed);        ratios_JECup[i]->SetLineWidth(1);    
//    
//    ratios_JECdown[i]=(TH1D*) spectra_JECdown[i]->Clone(("Data_unf_JECsysdown_MC_ratio_ybin"+std::to_string(i)).c_str());
//    ratios_JECdown[i]->Divide(mcspectra[i]);
//    ratios_JECdown[i]->SetMarkerSize(0);  ratios_JECdown[i]->SetMarkerColor(kBlack);   ratios_JECdown[i]->SetMarkerStyle(kFullCircle);
//    ratios_JECdown[i]->SetLineColor(kRed);        ratios_JECdown[i]->SetLineWidth(1);    
//
//    //JER SYS
//    ratios_JERup[i]=(TH1D*) spectra_JERup[i]->Clone(("Data_unf_JERsysup_MC_ratio_ybin"+std::to_string(i)).c_str());
//    ratios_JERup[i]->Divide(mcspectra[i]);
//    ratios_JERup[i]->SetMarkerSize(0);  ratios_JERup[i]->SetMarkerColor(kBlack);   ratios_JERup[i]->SetMarkerStyle(kFullCircle);
//    ratios_JERup[i]->SetLineColor(kGreen);        ratios_JERup[i]->SetLineWidth(1);    
//    
//    ratios_JERdown[i]=(TH1D*) spectra_JERdown[i]->Clone(("Data_unf_JERsysdown_MC_ratio_ybin"+std::to_string(i)).c_str());
//    ratios_JERdown[i]->Divide(mcspectra[i]);
//    ratios_JERdown[i]->SetMarkerSize(0);  ratios_JERdown[i]->SetMarkerColor(kBlack);   ratios_JERdown[i]->SetMarkerStyle(kFullCircle);
//    ratios_JERdown[i]->SetLineColor(kGreen);        ratios_JERdown[i]->SetLineWidth(1);    
    
  }
  
  
  
  ////this works fine because first pt bin of all the ratios are the same
  //TH1D* lumisysterr=(TH1D*)ratios[3]->Clone("lumierr");
  //lumisysterr->Reset("ICES");
  //std::cout<<"lumisysterr low edge bin 1="<<lumisysterr->GetBinLowEdge(1)<<std::endl;
  //std::cout<<"lumisysterr width bin 1="<<lumisysterr->GetBinWidth(1)<<std::endl;
  //std::cout<<"lumisysterr nbins="<<lumisysterr->GetNbinsX()<<std::endl;
  //
  //lumisysterr->SetBinContent(1, 1.);
  //lumisysterr->SetBinError(1, .023);
  //styleLumiErrHist(lumisysterr);

  TCanvas* canv=makeSMPRatioCanvas("PY8unfdata_SMPInclJetXsec_ratio");
  
  canv->cd(1);
  ratios[0]->Draw("HIST E ][");
  ratios_statunc[0]->Draw("HIST E ][ SAME");
  canv->cd(2);
  ratios[1]->Draw("HIST E ][");
  ratios_statunc[1]->Draw("HIST E ][ SAME");
  canv->cd(3); 
  ratios[2]->Draw("HIST E ][");
  ratios_statunc[2]->Draw("HIST E ][ SAME");
  canv->cd(4);
  ratios[3]->Draw("HIST E ][");
  ratios_statunc[3]->Draw("HIST E ][ SAME");
  
  
  //TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  //for(int i=0; i<netabins; i++){
    
    //float xlo=ratios[i]->GetBinLowEdge(1);
    //float xhi=
    //  ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
    //  ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    //TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    

    //canv->cd(i+1);
    //ratios[i]->Draw("HIST E ][");
  //mcspectra[i]->Draw("HIST");
    //one     ->Draw();       
    //ratios_statunc[i]->Draw("HIST E ][ SAME");    
    //ratios_JECup[i]->Draw("HIST ][ SAME");    
    //ratios_JECdown[i]->Draw("HIST ][ SAME");    
    //ratios_JERup[i]->Draw("HIST ][ SAME");    
    //ratios_JERdown[i]->Draw("HIST ][ SAME");    
    //lumisysterr->Draw("HIST  E2  ][ SAME");
    //ratios[i]->Draw("HIST E ][ SAME");    
    

    


    //if(i==0){
    //  TLegend* leg=makeLegend(0.61, 0.68, 0.87, 0.87);
    //  leg->AddEntry(ratios[i],"PY8 Unfolded Data","lp");
    //  //leg->AddEntry(ratios_statunc[i],"Data #oplus MC Stat. Unc.","le");
    //  //leg->AddEntry(ratios_JECup[i],"JEC Syst. Unc.","l");
    //  //leg->AddEntry(ratios_JERup[i],"JER Syst. Unc.","l");
    //  //leg->AddEntry(lumisysterr,"Lumi. Unc., #pm 2.3%","lepf");
    //  //leg->Draw();
    //}
    
    //TPaveText* desc=NULL;
    //if(i==0)desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    //else    desc=makePaveText( 0.15, 0.74, 0.45, 0.88);
    //desc->AddText(etabin_strs[i].c_str());
    //std::string ptrange=ptcuts_lo;
    //ptrange+=std::to_string( (int)xhi)+" GeV";
    //desc->AddText(ptrange.c_str());
    //if(i==0)desc->AddText(jettype.c_str());
    //desc->Draw();
    
    
    //SMPtitle->Draw();  
    
  //}
  
  //makeSMPInclJetXsec_PY8unfdata_DebugLaptop_ratios
  //saveCanv_DebugLaptop(outdir, canv);
  saveCanv(outdir, canv, fout);
  //if((bool)fout){
  //  fout->cd();
  //  for(int i=0; i<netabins;i++){
  //    //spectra[i]->Write();
  //    //mcspectra[i]->Write();
  //    ratios[i]->Write();
  //  }
  //}
  for(int i=0; i<netabins;i++){
    mcspectra[i]->Delete();
    
    spectra[i]->Delete();
    
    ratios[i]->Delete();
    ratios_statunc[i]->Delete();
  }  
  //canv->Delete();

  
  return;
}



void  makeSMPInclJetXsec_JOHNNLOunfdata (std::string outdir, TFile* fout){
  
  const int netabins=NLO_UNFDIR_DATA_JOHNS_BINS_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* spectra[netabins]={};
  TH1D* johnsspectra[netabins]={};
  int powten=netabins-1;
  float maxy=-1., miny=100000000.;//global min/maxy
  
  std::string johnsfilepath=NLO_UNFDIR_JOHNS_DATA+NLO_UNF_JOHNS_DATA_SPECTRA;
  TFile* johnsfile=TFile::Open((johnsfilepath).c_str(), "READ");
  
  //first get the plots, scale accordingly, get the min/max y's
  for(int i=0; i<netabins; i++){

    //// OBTAINED BY UNFOLDING IN STANDARD SMP BINS AND REBINNING TO JOHNS BINS
    std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_unf") 
			   )->Clone( 
				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
				     )
			  );
    spectra[i]->Scale(1000.);//nb-->pb
    spectra[i]->Scale(pow(10,(float)powten));   
    multiplyBinWidth(spectra[i]);
    if      (i==0)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_00eta05_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_00eta05);  
    else if (i==1)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_05eta10_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_05eta10);  
    else if (i==2)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_10eta15_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_10eta15);    
    else if (i==3)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_15eta20_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_15eta20);
    divideBinWidth(spectra[i]);

    johnsspectra[i] =  (TH1D*)getSpectraFromJohnsFile(johnsfile, i);
    
    //johnsspectra[i]->Scale(1000.);//nb-->pb
    johnsspectra[i]->Scale(pow(10,(float)powten));   

    
    if(maxy<spectra[i]->GetMaximum())      maxy=spectra[i]->GetMaximum();
    if(miny>spectra[i]->GetMinimum())      miny=spectra[i]->GetMinimum();
    
    powten--;        
  }
  
  // now style hists stuff
  spectra[0]->SetMarkerSize(2);  spectra[0]->SetMarkerColor(kRed);       spectra[0]->SetMarkerStyle(kFullCircle);
  spectra[1]->SetMarkerSize(2);  spectra[1]->SetMarkerColor(kGreen);     spectra[1]->SetMarkerStyle(kFullSquare);
  spectra[2]->SetMarkerSize(2);  spectra[2]->SetMarkerColor(kBlue);      spectra[2]->SetMarkerStyle(kFullTriangleUp);
  spectra[3]->SetMarkerSize(2);  spectra[3]->SetMarkerColor(kMagenta);   spectra[3]->SetMarkerStyle(kFullTriangleDown); 
  spectra[0]->SetLineColor(kRed);      
  spectra[1]->SetLineColor(kGreen);    
  spectra[2]->SetLineColor(kBlue);     
  spectra[3]->SetLineColor(kMagenta);  


  johnsspectra[0]->SetMarkerSize(0);
  johnsspectra[1]->SetMarkerSize(0);
  johnsspectra[2]->SetMarkerSize(0);
  johnsspectra[3]->SetMarkerSize(0);
  johnsspectra[0]->SetLineColor(kBlack);	
  johnsspectra[1]->SetLineColor(kBlack);	
  johnsspectra[2]->SetLineColor(kBlack);	
  johnsspectra[3]->SetLineColor(kBlack);	
  
  //first hist to be drawn, so this gets the max/min/labels/titles set up
  spectra[0]->SetMaximum(maxy*10.);
  spectra[0]->SetMinimum(miny/5.);  
  setHistLabels((TH1D*)spectra[0]);


  TLegend* leg=makeLegend();
  leg->SetHeader( "Ian's RooUnfoldBayes Results","C" );
  
  TLegend* mcleg=makeLegend(0.52, 0.72, 0.88, 0.84);
  //mcleg->SetHeader( jettype.c_str(),"C" );
  mcleg->AddEntry((TObject*)0, ptcuts.c_str(), "");
  mcleg->AddEntry((TObject*)0, jettype.c_str(), "");
  mcleg->AddEntry(johnsspectra[0], "John's TUnfold Results", "l");
  
  TCanvas* canv=makeSMPSpectraCanvas("JOHNNLOunfdata_SMPInclJetXsec");
  canv->cd();

  powten=netabins-1;
  for(int i=0; i<netabins; i++){
    if(i==0)
      spectra[i]->Draw("HIST E ][");
    else 
      spectra[i]->Draw("HIST E ][ SAME");
    std::string legstr=etabin_strs[i] + " ( x 10^{"+std::to_string(powten)+"} )";
    leg->AddEntry( spectra[i], 
		   (legstr).c_str() ,"lp");        
    powten--;
    
    johnsspectra[i]->Draw("HIST E SAME");
    
  }
  
  leg->Draw();
  mcleg->Draw();
  
  TPaveText* SMPtitle=makePrelimPaveTextTitle();
  SMPtitle->Draw();  
  
  //makeSMPInclJetXsec_JOHNNLOunfdata
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();
    johnsspectra[i]->Delete();
  }  
  //canv->Delete();


  
  return;
}


void  makeSMPInclJetXsec_JOHNNLOunfdata_ratios (std::string outdir, TFile* fout){

  const int netabins=NLO_UNFDIR_DATA_JOHNS_BINS_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  //TH1D* toymcspectra[netabins]={};//toy MC version of NNPDF; use for PDF/THY errs
  TH1D* johnsspectra[netabins]={};// Matrix Element Calculation of NNPDF; use for data comparisons    
  TH1D* spectra[netabins]={};									      
  TH1D* ratios[netabins]={};                                                                          

  std::string johnsfilepath=NLO_UNFDIR_JOHNS_DATA+NLO_UNF_JOHNS_DATA_SPECTRA;
  TFile* johnsfile=TFile::Open((johnsfilepath).c_str(), "READ");  


  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){

    ////// OBTAINED BY UNFOLDING IN JOHNS BINS
    //std::string filepath= NLO_UNFDIR_DATA_JOHNS_BINS + NLO_UNFDIR_DATA_JOHNS_BINS_file_array[i] + ".root";
    //TFile* file=TFile::Open(( filepath).c_str(), "READ");    
    ////SPECTRA ONLY, NO SYST
    //spectra[i] =  (TH1D*)(
    //			  (
    //			   (TH1D*)file->Get("Data_unf") 
    //			   )->Clone( 
    //				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
    //				     )
    //			  );
    //spectra[i]->Scale(1000.);//nb-->pb
    
    //// OBTAINED BY UNFOLDING IN STANDARD SMP BINS AND REBINNING TO JOHNS BINS
    std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_unf") 
			   )->Clone( 
				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
				     )
			  );
    spectra[i]->Scale(1000.);//nb-->pb
    multiplyBinWidth(spectra[i]);
    if      (i==0)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_00eta05_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_00eta05);  
    else if (i==1)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_05eta10_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_05eta10);  
    else if (i==2)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_10eta15_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_10eta15);    
    else if (i==3)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_15eta20_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_15eta20);
    divideBinWidth(spectra[i]);

    int nbins=spectra[i]->GetNbinsX();
    Double_t ptbins[nbins+1];
    for(int j=1; j<=nbins;j++){
      ptbins[j-1]=spectra[i]->GetBinLowEdge(j);
      if(j==nbins){
	ptbins[j]=spectra[i]->GetBinLowEdge(j)+spectra[i]->GetBinWidth(j);
      }
    }
    
    

    johnsspectra[i] =  (TH1D*)getSpectraFromJohnsFile(johnsfile, i);
    multiplyBinWidth(johnsspectra[i]);
    johnsspectra[i]=(TH1D*)johnsspectra[i]->TH1::Rebin(nbins, ((std::string)johnsspectra[i]->GetName()+"_rebin").c_str(), (Double_t*)ptbins);
    divideBinWidth(johnsspectra[i]);
    
    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_JohnData_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(johnsspectra[i]);

    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.6);    ratios[i]->SetMaximum(1.7);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to John's TUnfold Result");
    
    
    
  }
  
  
  
  TCanvas* canv=makeSMPRatioCanvas("JOHNNLOunfdata_SMPInclJetXsec_ratio");
  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][ ");    

    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    //TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    one     ->Draw();       

    TLegend* leg=makeLegend(0.59, 0.63, 0.87, 0.87);
    //leg->SetHeader()
    leg->AddEntry(ratios[i],"Ian's RooUnfoldBayes Result","lp");
    leg->Draw();


    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);   
    one     ->Draw();       
    TLine* downline     =makeTLine(xlo, 0.8 , xhi, 0.8);   
    downline     ->Draw();       
    TLine* upline     =makeTLine(xlo, 1.2 , xhi, 1.2);   
    upline     ->Draw();       
    
    TPaveText* desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    desc->AddText(etabin_strs[i].c_str());
    desc->AddText(jettype.c_str());
    std::string ptrange=ptcuts_lo;
    ptrange+=std::to_string( (int)xhi)+" GeV";
    desc->AddText(ptrange.c_str());
    desc->Draw();
        
    SMPtitle->Draw();  
    
  }
  
  
  //makeSMPInclJetXsec_JOHNNLOunfdata_ratios
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    johnsspectra[i]->Delete();
    spectra[i]->Delete();									      
    ratios[i]->Delete();                                                                          
  }


  //canv->Delete();


  
  return;
}


void  makeSMPInclJetXsec_JOAONLOunfdata_ratios (std::string outdir, TFile* fout){

  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  //TH1D* toymcspectra[netabins]={};//toy MC version of NNPDF; use for PDF/THY errs
  TH1D* mcspectra[netabins]={};// Matrix Element Calculation of NNPDF; use for data comparisons
  //TH1D* mcspectra_PDFup[netabins]={};
  //TH1D* mcspectra_PDFdown[netabins]={};

  TH1D* spectra[netabins]={};	      
  TH1D* spectra_JECup[netabins]={};   
  TH1D* spectra_JECdown[netabins]={}; 
  TH1D* spectra_JERup[netabins]={};   
  TH1D* spectra_JERdown[netabins]={}; 
  	                              
  TH1D* ratios[netabins]={};	      
  TH1D* ratios_statunc[netabins]={};  
  TH1D* ratios_JECup[netabins]={};    
  TH1D* ratios_JECdown[netabins]={};  
  TH1D* ratios_JERup[netabins]={};    
  TH1D* ratios_JERdown[netabins]={};  
  //TH1D* ratios_PDFup[netabins]={};
  //TH1D* ratios_PDFdown[netabins]={};
  
  //TFile* joaofile=TFile::Open("/Users/ilaflott/Working/CERNBox/localAnalysis/fastNLO/fromJoao/CMS-5.02TeV-spectra-muPT/fout.root","READ");
  TFile* joaofile=TFile::Open("/Users/ilaflott/Working/CERNBox/localAnalysis/fastNLO/fromJoao/CMS-5.02TeV-spectra-muPT1/fout1.root","READ");
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";//also has JEC systematics
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    //SPECTRA ONLY, NO SYST
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_unf") 
			   )->Clone( 
				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
				     )
			  );
    spectra[i]->Scale(1000.);//nb-->pb
    //readBinContent(spectra[i]);

    mcspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)joaofile->Get(("h0100"+std::to_string(i+1)+"00").c_str()) 
			     )->Clone( 
				      ("MC_truth_ybin"+std::to_string(i)).c_str() 
				       )
			    );            
    multiplyBinWidth(mcspectra[i]);
    //readBinContent(mcspectra[i]);
    if      (i==0)
      mcspectra[i]=(TH1D*)mcspectra[i]->TH1::Rebin(defbins_00eta05_nbins, ((std::string)mcspectra[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_00eta05);  
    else if (i==1)
      mcspectra[i]=(TH1D*)mcspectra[i]->TH1::Rebin(defbins_05eta10_nbins, ((std::string)mcspectra[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_05eta10);  
    else if (i==2)
      mcspectra[i]=(TH1D*)mcspectra[i]->TH1::Rebin(defbins_10eta15_nbins, ((std::string)mcspectra[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_10eta15);    
    else if (i==3)
      mcspectra[i]=(TH1D*)mcspectra[i]->TH1::Rebin(defbins_15eta20_nbins, ((std::string)mcspectra[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_15eta20);
    divideBinWidth(mcspectra[i]);
    //readBinContent(mcspectra[i]);
    
    for(int j=1; j<=mcspectra[i]->GetNbinsX();j++)//errors due to PDF will be illustrated by 6 point scale var error. leave inherent PDF errors out of it.
      mcspectra[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root]
    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_NLO_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(mcspectra[i]);
    //readBinContent(ratios[i]);
    //return;
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.4);    ratios[i]->SetMaximum(1.6);
    //setRatioHistLabels((TH1D*)ratios[i], "Ratio to NNPDF 3.0 #otimes HERWIG EE5C");
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to CT14nnlo (#mu = Jet p_{T}) from Joao");
    //setRatioHistLabels((TH1D*)ratios[i], "Ratio to CT14nnlo (#mu = Jet p_{T}^{Lead}) from Joao");
    
    
    //DATA STAT UNC
    ratios_statunc[i]=(TH1D*) spectra[i]->Clone(("Data_MC_StatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_statunc[i]->Divide(mcspectra[i]);
    setOneBinContent(ratios_statunc[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    
    
    //JEC SYSTEMATICS
    spectra_JECup[i] =  (TH1D*)(
    				(
    			   (TH1D*)file->Get("ppData_BayesUnf_JECsysup_Spectra") 
    			   )->Clone( 
    				    ("Data_unf_JECsysup_ybin"+std::to_string(i)).c_str() 
    				     )
    			  );
    spectra_JECup[i]->Scale(1000.);//nb-->pb    
    
    ratios_JECup[i]=(TH1D*) spectra_JECup[i]->Clone(("Data_JECsysup_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECup[i]->Divide(mcspectra[i]);
    setOneBinContent_errHist(ratios[i], ratios_JECup[i]);
    ratios_JECup[i]->SetMarkerSize(0);  ratios_JECup[i]->SetMarkerColor(kBlack);   ratios_JECup[i]->SetMarkerStyle(kFullCircle);
    ratios_JECup[i]->SetLineColor(kRed);    ratios_JECup[i]->SetLineWidth(1);    
    
    
    spectra_JECdown[i] =  (TH1D*)(
    				  (
    				   (TH1D*)file->Get("ppData_BayesUnf_JECsysdown_Spectra") 
    				   )->Clone( 
    					    ("Data_unf_JECsysdown_ybin"+std::to_string(i)).c_str() 
    					     )
    				  );
    spectra_JECdown[i]->Scale(1000.);//nb-->pb    
    
    ratios_JECdown[i]=(TH1D*) spectra_JECdown[i]->Clone(("Data_JECsysdown_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECdown[i]->Divide(mcspectra[i]);
    setOneBinContent_errHist(ratios[i], ratios_JECdown[i]);
    ratios_JECdown[i]->SetMarkerSize(0);  ratios_JECdown[i]->SetMarkerColor(kBlack);   ratios_JECdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JECdown[i]->SetLineColor(kRed);    ratios_JECdown[i]->SetLineWidth(1);    
    


    ////PDF 6PT SYSTEMATICS, USE THY HIST NOT TOY MC ANYMORE, NO NEED FOR SEP FILE
    //mcspectra_PDFup[i] =  (TH1D*)(
    //				(
    //				 (TH1D*)joaofile->Get(("h0100"+std::to_string(i+1)+"09").c_str()) 
    //				 )->Clone( 
    //					  ("MC_PDFsysup_ybin"+std::to_string(i)).c_str() 
    //					   )
    //				);
    //multiplyBinWidth(mcspectra_PDFup[i]);
    //if      (i==0)
    //  mcspectra_PDFup[i]=(TH1D*)mcspectra_PDFup[i]->TH1::Rebin(defbins_00eta05_nbins, ((std::string)mcspectra_PDFup[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_00eta05);  
    //else if (i==1)
    //  mcspectra_PDFup[i]=(TH1D*)mcspectra_PDFup[i]->TH1::Rebin(defbins_05eta10_nbins, ((std::string)mcspectra_PDFup[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_05eta10);  
    //else if (i==2)
    //  mcspectra_PDFup[i]=(TH1D*)mcspectra_PDFup[i]->TH1::Rebin(defbins_10eta15_nbins, ((std::string)mcspectra_PDFup[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_10eta15);    
    //else if (i==3)
    //  mcspectra_PDFup[i]=(TH1D*)mcspectra_PDFup[i]->TH1::Rebin(defbins_15eta20_nbins, ((std::string)mcspectra_PDFup[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_15eta20);
    //divideBinWidth(mcspectra_PDFup[i]);
    //
    //ratios_PDFup[i]=(TH1D*) mcspectra_PDFup[i]->Clone(("MC_PDFsysup_ratio_ybin"+std::to_string(i)).c_str());
    //ratios_PDFup[i]->Divide(mcspectra[i]);
    //ratios_PDFup[i]->SetMarkerSize(0);  ratios_PDFup[i]->SetMarkerColor(kBlack);   ratios_PDFup[i]->SetMarkerStyle(kFullCircle);
    //ratios_PDFup[i]->SetLineColor(kMagenta);    ratios_PDFup[i]->SetLineWidth(1);    
    //
    //
    //mcspectra_PDFdown[i] =  (TH1D*)(
    //				  (
    //				   (TH1D*)joaofile->Get(("h0100"+std::to_string(i+1)+"08").c_str()) 
    //				   )->Clone( 
    //				    ("MC_PDFsysdown_ybin"+std::to_string(i)).c_str() 
    //					     )
    //				  );
    //multiplyBinWidth(mcspectra_PDFdown[i]);
    //if      (i==0)
    //  mcspectra_PDFdown[i]=(TH1D*)mcspectra_PDFdown[i]->TH1::Rebin(defbins_00eta05_nbins, ((std::string)mcspectra_PDFdown[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_00eta05);  
    //else if (i==1)
    //  mcspectra_PDFdown[i]=(TH1D*)mcspectra_PDFdown[i]->TH1::Rebin(defbins_05eta10_nbins, ((std::string)mcspectra_PDFdown[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_05eta10);  
    //else if (i==2)
    //  mcspectra_PDFdown[i]=(TH1D*)mcspectra_PDFdown[i]->TH1::Rebin(defbins_10eta15_nbins, ((std::string)mcspectra_PDFdown[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_10eta15);    
    //else if (i==3)
    //  mcspectra_PDFdown[i]=(TH1D*)mcspectra_PDFdown[i]->TH1::Rebin(defbins_15eta20_nbins, ((std::string)mcspectra_PDFdown[i]->GetName()+"_rebin").c_str(), (Double_t*)defbins_15eta20);
    //divideBinWidth(mcspectra_PDFdown[i]);
    //
    //
    //ratios_PDFdown[i]=(TH1D*) mcspectra_PDFdown[i]->Clone(("MC_PDFsysdown_ratio_ybin"+std::to_string(i)).c_str());
    //ratios_PDFdown[i]->Divide(mcspectra[i]);
    //ratios_PDFdown[i]->SetMarkerSize(0);  ratios_PDFdown[i]->SetMarkerColor(kBlack);   ratios_PDFdown[i]->SetMarkerStyle(kFullCircle);
    //ratios_PDFdown[i]->SetLineColor(kMagenta);    ratios_PDFdown[i]->SetLineWidth(1);    

    //JER SYSTEMATICS: REQUIRES SEPERATE FILE
    std::string JERsysfilepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_SYST_file_array[1] +ETABIN_TAG_array[i]+ ".root";//also has JEC systematics
    TFile* JERsysfile=TFile::Open(( JERsysfilepath).c_str(), "READ");
    spectra_JERup[i] =  (TH1D*)(
    				(
    				 (TH1D*)JERsysfile->Get("ppData_BayesUnf_JERsysup_Spectra") 
    				 )->Clone( 
    					  ("Data_unf_JERsysup_ybin"+std::to_string(i)).c_str() 
    					   )
    				);
    spectra_JERup[i]->Scale(1000.);//nb-->pb    
    
    ratios_JERup[i]=(TH1D*) spectra_JERup[i]->Clone(("Data_JERsysup_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERup[i]->Divide(mcspectra[i]);
    setOneBinContent_errHist(ratios[i], ratios_JERup[i]);
    ratios_JERup[i]->SetMarkerSize(0);  ratios_JERup[i]->SetMarkerColor(kBlack);   ratios_JERup[i]->SetMarkerStyle(kFullCircle);
    ratios_JERup[i]->SetLineColor(kGreen);    ratios_JERup[i]->SetLineWidth(1);    
    
    
    spectra_JERdown[i] =  (TH1D*)(
    				  (
    				   (TH1D*)JERsysfile->Get("ppData_BayesUnf_JERsysdown_Spectra") 
    				   )->Clone( 
    					    ("Data_unf_JERsysdown_ybin"+std::to_string(i)).c_str() 
    					     )
    				  );
    spectra_JERdown[i]->Scale(1000.);//nb-->pb    
    
    
    ratios_JERdown[i]=(TH1D*) spectra_JERdown[i]->Clone(("Data_JERsysdown_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERdown[i]->Divide(mcspectra[i]);
    setOneBinContent_errHist(ratios[i], ratios_JERdown[i]);
    ratios_JERdown[i]->SetMarkerSize(0);  ratios_JERdown[i]->SetMarkerColor(kBlack);   ratios_JERdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JERdown[i]->SetLineColor(kGreen);    ratios_JERdown[i]->SetLineWidth(1);    
    
    

    
    

  }
  
  
  
  //this works fine because first pt bin of all the ratios are the same
  TH1D* lumisysterr=(TH1D*)ratios[3]->Clone("lumierr");
  lumisysterr->Reset("ICES");
  //  std::cout<<"lumisysterr low edge bin 1="<<lumisysterr->GetBinLowEdge(1)<<std::endl;
  //  std::cout<<"lumisysterr width bin 1="<<lumisysterr->GetBinWidth(1)<<std::endl;
  //  std::cout<<"lumisysterr nbins="<<lumisysterr->GetNbinsX()<<std::endl;
  lumisysterr->SetBinContent(1, 1.);
  lumisysterr->SetBinError(1, .023);
  styleLumiErrHist(lumisysterr);
  TCanvas* canv=makeSMPRatioCanvas("JOAONLOunfdata1_SMPInclJetXsec_ratio");
  //TCanvas* canv=makeSMPRatioCanvas("JOAONLOunfdata_SMPInclJetXsec_ratio");
  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][ ");    
    ratios_statunc[i]->Draw("HIST E ][ SAME");    
    //ratios_PDFup[i]->Draw("HIST ][ SAME");    
    //ratios_PDFdown[i]->Draw("HIST ][ SAME");    
    ratios_JECup[i]->Draw("HIST ][ SAME");    
    ratios_JECdown[i]->Draw("HIST ][ SAME");    
    ratios_JERup[i]->Draw("HIST ][ SAME");    
    ratios_JERdown[i]->Draw("HIST ][ SAME");    
    ratios[i]->Draw("HIST E ][ SAME");    
    lumisysterr->Draw("HIST  E2  ][ SAME");
    

    

    //float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    //TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    one     ->Draw();       

    if(i==0){
      TLegend* leg=makeLegend(0.45, 0.63, 0.90, 0.87);
      //leg->SetHeader()
      leg->AddEntry(ratios[i],"CT14nnlo NLO #otimes HERIWIGEE5C Unfolded Data","lp");
      leg->AddEntry(ratios_statunc[i],"Data Stat. Unc.","le");
      leg->AddEntry(ratios_JECup[i],"JEC Unc.","l");
      leg->AddEntry(ratios_JERup[i],"JER Unc.","l");
      //leg->AddEntry(ratios_PDFup[i],"PDF 6 Pt. Scale Unc..","l");
      leg->AddEntry(lumisysterr,"Lumi. Unc., #pm 2.3%","lepf");//just f--> annoying border on the legend entry , lepf w/ 0 line width, 0 marker color alpha -->no annoying border
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
  
  
  //makeSMPInclJetXsec_JOAONLOunfdata_ratios
  saveCanv(outdir, canv, fout);
  //if((bool)fout){
  //  fout->cd();
  //  for(int i=0; i<netabins;i++){
  //    ratios[i]->Write();
  //  }
  //}

  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();	      
    spectra_JECup[i]->Delete();   
    spectra_JECdown[i]->Delete(); 
    spectra_JERup[i]->Delete();   
    spectra_JERdown[i]->Delete(); 
                                  
    ratios[i]->Delete();	      
    ratios_statunc[i]->Delete();  
    ratios_JECup[i]->Delete();    
    ratios_JECdown[i]->Delete();  
    ratios_JERup[i]->Delete();    
    ratios_JERdown[i]->Delete();  





  }

  //canv->Delete();

  return;
}

void  makeSMPInclJetXsec_JOHNmeasdata (std::string outdir, TFile* fout){
  
  const int netabins=NLO_UNFDIR_DATA_JOHNS_BINS_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* spectra[netabins]={};
  TH1D* johnsspectra[netabins]={};
  int powten=netabins-1;
  float maxy=-1., miny=100000000.;//global min/maxy
  
  std::string johnsfilepath=NLO_UNFDIR_JOHNS_DATA+MEAS_JOHNS_DATA_SPECTRA;
  TFile* johnsfile=TFile::Open((johnsfilepath).c_str(), "READ");
  
  //first get the plots, scale accordingly, get the min/max y's
  for(int i=0; i<netabins; i++){

    //// OBTAINED BY UNFOLDING IN STANDARD SMP BINS AND REBINNING TO JOHNS BINS
    //std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";
    std::string filepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_meas") 
			   )->Clone( 
				    ("Data_meas_ybin"+std::to_string(i)).c_str() 
				     )
			  );
    spectra[i]->Scale(1000.);//nb-->pb
    spectra[i]->Scale(pow(10,(float)powten));   
    multiplyBinWidth(spectra[i]);
    if      (i==0)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_00eta05_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_00eta05);  
    else if (i==1)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_05eta10_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_05eta10);  
    else if (i==2)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_10eta15_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_10eta15);    
    else if (i==3)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_15eta20_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_15eta20);
    divideBinWidth(spectra[i]);
    

    int nbins=spectra[i]->GetNbinsX();
    Double_t ptbins[nbins+1];
    for(int j=1; j<=nbins;j++){
      ptbins[j-1]=spectra[i]->GetBinLowEdge(j);
      if(j==nbins){
    	ptbins[j]=spectra[i]->GetBinLowEdge(j)+spectra[i]->GetBinWidth(j);
      }
    }
    
    
    johnsspectra[i] =  (TH1D*)(
			       (
				(TH1D*)johnsfile->Get(("hpt_eta"+std::to_string(i)).c_str()) 
				)->Clone( 
					 ("hptALL_data_etaBin"+std::to_string(i)+"_clone").c_str() 
					  )
			       );
    multiplyBinWidth(johnsspectra[i]);
    //std::cout<<"john etabin i="<<i<<std::endl;
    johnsspectra[i]=(TH1D*)johnsspectra[i]->TH1::Rebin(nbins, ((std::string)johnsspectra[i]->GetName()+"_rebin").c_str(), (Double_t*)ptbins);
    divideBinWidth(johnsspectra[i]);
    johnsspectra[i]->Scale(pow(10,(float)powten));   
    //johnsspectra[i]->Scale(1000.);//nb-->pb    
    //johnsspectra[i]->Scale(1000000.);//nb-->pb    
    //johnsspectra[i]->Scale(25.8/27.4);
    float spectra_i_min=getnonzeromin((TH1*)spectra[i]);
    if(maxy<spectra[i]->GetMaximum())      maxy=spectra[i]->GetMaximum();
    if(miny>spectra_i_min)      miny=spectra_i_min;
    
    powten--;        
  }
  
  // now style hists stuff
  spectra[0]->SetMarkerSize(2);  spectra[0]->SetMarkerColor(kRed);       spectra[0]->SetMarkerStyle(kFullCircle);
  spectra[1]->SetMarkerSize(2);  spectra[1]->SetMarkerColor(kGreen);     spectra[1]->SetMarkerStyle(kFullSquare);
  spectra[2]->SetMarkerSize(2);  spectra[2]->SetMarkerColor(kBlue);      spectra[2]->SetMarkerStyle(kFullTriangleUp);
  spectra[3]->SetMarkerSize(2);  spectra[3]->SetMarkerColor(kMagenta);   spectra[3]->SetMarkerStyle(kFullTriangleDown); 
  spectra[0]->SetLineColor(kRed);      
  spectra[1]->SetLineColor(kGreen);    
  spectra[2]->SetLineColor(kBlue);     
  spectra[3]->SetLineColor(kMagenta);  


  johnsspectra[0]->SetMarkerSize(0);
  johnsspectra[1]->SetMarkerSize(0);
  johnsspectra[2]->SetMarkerSize(0);
  johnsspectra[3]->SetMarkerSize(0);
  johnsspectra[0]->SetLineColor(kBlack);	
  johnsspectra[1]->SetLineColor(kBlack);	
  johnsspectra[2]->SetLineColor(kBlack);	
  johnsspectra[3]->SetLineColor(kBlack);	
  
  //first hist to be drawn, so this gets the max/min/labels/titles set up
  spectra[0]->SetMaximum(maxy*10.);
  spectra[0]->SetMinimum(miny/5.);  
  setHistLabels((TH1D*)spectra[0]);


  TLegend* leg=makeLegend();
  leg->SetHeader( "Ian's Measured Data","C" );
  
  TLegend* mcleg=makeLegend(0.52, 0.72, 0.88, 0.84);
  //mcleg->SetHeader( jettype.c_str(),"C" );
  mcleg->AddEntry((TObject*)0, ptcuts.c_str(), "");
  mcleg->AddEntry((TObject*)0, jettype.c_str(), "");
  mcleg->AddEntry(johnsspectra[0], "John's Measured Data", "l");
  
  TCanvas* canv=makeSMPSpectraCanvas("JOHNmeasdata_SMPInclJetXsec");
  canv->cd();
  
  powten=netabins-1;
  for(int i=0; i<netabins; i++){
    if(i==0)
      spectra[i]->Draw("HIST E ][");
    else 
      spectra[i]->Draw("HIST E ][ SAME");
    std::string legstr=etabin_strs[i] + " ( x 10^{"+std::to_string(powten)+"} )";
    leg->AddEntry( spectra[i], 
		   (legstr).c_str() ,"lp");        
    powten--;
    
    johnsspectra[i]->Draw("HIST E SAME");
    
  }
  
  leg->Draw();
  mcleg->Draw();
  
  TPaveText* SMPtitle=makePrelimPaveTextTitle();
  SMPtitle->Draw();  
  
  //makeSMPInclJetXsec_JOHNmeasdata
  saveCanv(outdir, canv, fout);
  //if((bool)fout){
  //  fout->cd();
  //  for(int i=0; i<netabins; i++){
  //    spectra[i]->Write();
  //  }
  //  for(int i=0; i<netabins; i++){
  //    johnsspectra[i]->Write();
  //  }
  //}
  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();
    johnsspectra[i]->Delete();
  }    
  //canv->Delete();

  return;
}



void  makeSMPInclJetXsec_JOHNmeasdata_ratios (std::string outdir, TFile* fout){
  
  const int netabins=NLO_UNFDIR_DATA_JOHNS_BINS_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  //TH1D* toymcspectra[netabins]={};//toy MC version of NNPDF; use for PDF/THY errs
  TH1D* johnsspectra[netabins]={};// Matrix Element Calculation of NNPDF; use for data comparisons
  
  TH1D* spectra[netabins]={};
  
  
  
  TH1D* ratios[netabins]={};

  std::string johnsfilepath=NLO_UNFDIR_JOHNS_DATA+MEAS_JOHNS_DATA_SPECTRA;
  TFile* johnsfile=TFile::Open((johnsfilepath).c_str(), "READ");  


  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){

    ////// OBTAINED BY UNFOLDING IN JOHNS BINS
    //std::string filepath= NLO_UNFDIR_DATA_JOHNS_BINS + NLO_UNFDIR_DATA_JOHNS_BINS_file_array[i] + ".root";
    //TFile* file=TFile::Open(( filepath).c_str(), "READ");    
    ////SPECTRA ONLY, NO SYST
    //spectra[i] =  (TH1D*)(
    //			  (
    //			   (TH1D*)file->Get("Data_unf") 
    //			   )->Clone( 
    //				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
    //				     )
    //			  );
    //spectra[i]->Scale(1000.);//nb-->pb
    
    //// OBTAINED BY UNFOLDING IN STANDARD SMP BINS AND REBINNING TO JOHNS BINS
    //std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";
    std::string filepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_meas") 
			   )->Clone( 
				    ("Data_meas_ybin"+std::to_string(i)).c_str() 
				     )
			  );
    spectra[i]->Scale(1000.);//nb-->pb
    multiplyBinWidth(spectra[i]);
    if      (i==0)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_00eta05_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_00eta05);  
    else if (i==1)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_05eta10_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_05eta10);  
    else if (i==2)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_10eta15_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_10eta15);    
    else if (i==3)
      spectra[i]=(TH1D*)spectra[i]->TH1::Rebin(johnsbins_15eta20_nbins, ((std::string)spectra[i]->GetName()+"_rebin").c_str(), (Double_t*)johnsbins_15eta20);
    divideBinWidth(spectra[i]);
    
    int nbins=spectra[i]->GetNbinsX();
    Double_t ptbins[nbins+1];
    for(int j=1; j<=nbins;j++){
      ptbins[j-1]=spectra[i]->GetBinLowEdge(j);
      if(j==nbins){
    	ptbins[j]=spectra[i]->GetBinLowEdge(j)+spectra[i]->GetBinWidth(j);
      }
    }
    
    
    
    //johnsspectra[i] =  (TH1D*)getSpectraFromJohnsFile(johnsfile, i);
    //divideBinWidth(johnsspectra[i]);
    
    johnsspectra[i] =  (TH1D*)(
			       (
				(TH1D*)johnsfile->Get(("hpt_eta"+std::to_string(i)).c_str()) 
				)->Clone( 
					 ("hptALL_data_etaBin"+std::to_string(i)+"_clone").c_str() 
					  )
			       );
    multiplyBinWidth(johnsspectra[i]);    
    johnsspectra[i]=(TH1D*)johnsspectra[i]->TH1::Rebin(nbins, ((std::string)johnsspectra[i]->GetName()+"_rebin").c_str(), (Double_t*)ptbins);
    divideBinWidth(johnsspectra[i]);
    //johnsspectra[i]->Scale(1000000.);//nb-->pb        
    //johnsspectra[i]->Scale(25.8/27.4);
    

    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_JohnData_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(johnsspectra[i]);

    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.6);    ratios[i]->SetMaximum(1.7);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to John's Measured Data");
    
    
    
  }
  
  
  
  TCanvas* canv=makeSMPRatioCanvas("JOHNmeasdata_SMPInclJetXsec_ratio");
  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][ ");    

    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    //TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    one     ->Draw();       

    TLegend* leg=makeLegend(0.59, 0.63, 0.87, 0.87);
    //leg->SetHeader()
    leg->AddEntry(ratios[i],"Ian's Measured Data","lp");
    leg->Draw();


    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);   
    one     ->Draw();       
    TLine* downline     =makeTLine(xlo, 0.8 , xhi, 0.8);   
    downline     ->Draw();       
    TLine* upline     =makeTLine(xlo, 1.2 , xhi, 1.2);   
    upline     ->Draw();       
    
    TPaveText* desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    desc->AddText(etabin_strs[i].c_str());
    desc->AddText(jettype.c_str());
    std::string ptrange=ptcuts_lo;
    ptrange+=std::to_string( (int)xhi)+" GeV";
    desc->AddText(ptrange.c_str());
    desc->Draw();
        
    SMPtitle->Draw();  
    
  }
  
  //makeSMPInclJetXsec_JOHNmeasdata_ratios
  saveCanv(outdir, canv, fout);
  //if((bool)fout){
  //  for(int i=0; i<netabins;i++){
  //    ratios[i]->Write();
  //  }
  //}
  for(int i=0; i<netabins;i++){
    johnsspectra[i]->Delete();
    spectra[i]->Delete();									      
    ratios[i]->Delete();                                                                          
  }
  //canv->Delete();
  
  return;
}



void  makeSMPInclJetXsec_NLOunfdataAcrossy_ratios (std::string outdir, TFile* fout){
  
  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* spectra[netabins]={};		  
  TH1D* spectrabin0_rebin[netabins]={};	  
  TH1D* ratios[netabins]={};		  
	                                  
  TH1D* mcspectra[netabins]={};		  
  TH1D* mcspectrabin0_rebin[netabins]={}; 
  TH1D* mcratios[netabins]={};		  
	                                  
  TH1D* thyspectra[netabins]={};	  
  TH1D* thyspectrabin0_rebin[netabins]={};
  TH1D* thyratios[netabins]={};		  
	                                  
  TF1*  NPCfit[netabins]={};		  
  TH1D* NPCfithist[netabins]={};	  
  TH1D* NPCfithistbin0_rebin[netabins]={};
  TH1D* NPCfitratios[netabins]={};        

  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";//also has JEC systematics
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    //SPECTRA ONLY, NO SYST
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_unf") 
			   )->Clone( 
				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
				     )
			  );
    
    int nbins=spectra[i]->GetNbinsX();
    std::vector<double> ptbinedges;
    for(int j=1;j<=nbins;j++)
      ptbinedges.push_back(spectra[i]->GetBinLowEdge(j));
    ptbinedges.push_back(spectra[i]->GetBinLowEdge(nbins)+spectra[i]->GetBinWidth(nbins));
    
    spectrabin0_rebin[i]=(TH1D*)spectra[0]->Clone(("Data_unf_ybin0_binsOfybin"+std::to_string(i)).c_str());
    multiplyBinWidth(spectrabin0_rebin[i]);
    spectrabin0_rebin[i]=(TH1D*)spectrabin0_rebin[i]->TH1::Rebin( nbins, ((std::string)spectrabin0_rebin[i]->GetName()+"_rebin").c_str() , ((double*)ptbinedges.data()) );
    divideBinWidth(spectrabin0_rebin[i]);
    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_unf_ybin0ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(spectrabin0_rebin[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  
    ratios[i]->SetMarkerColor(kBlack);   
    //ratios[i]->SetMarkerColorAlpha(0.,kBlack);   
    ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    //ratios[i]->SetLineColorAlpha(0.,kBlack);    
    
    ratios[i]->SetMinimum(0.0);    ratios[i]->SetMaximum(2.0);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to Unf. Data (#||{y} < 0.5)");
    
    mcspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)file->Get(thyname.c_str()) 
			     )->Clone( 
				      ("MC_truth_ybin"+std::to_string(i)).c_str() 
				       )
			    );        
    mcspectrabin0_rebin[i]=(TH1D*)mcspectra[0]->Clone(("MC_truth_ybin0_binsOfybin"+std::to_string(i)).c_str());
    multiplyBinWidth(mcspectrabin0_rebin[i]);
    mcspectrabin0_rebin[i]=(TH1D*)mcspectrabin0_rebin[i]->TH1::Rebin( nbins, ((std::string)mcspectrabin0_rebin[i]->GetName()+"_rebin").c_str() , ((double*)ptbinedges.data()) );
    divideBinWidth(mcspectrabin0_rebin[i]);
    
    mcratios[i]=(TH1D*) mcspectra[i]->Clone(("MC_truth_ybin0ratio_ybin"+std::to_string(i)).c_str());
    //mcratios[i]->Divide(mcspectrabin0_rebin[i]);
    mcratios[i]->Divide(spectrabin0_rebin[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      mcratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    mcratios[i]->SetMarkerSize(1.2);  mcratios[i]->SetMarkerColor(kGray);   mcratios[i]->SetMarkerStyle(kOpenCircle);
    mcratios[i]->SetLineColor(kGray);    
    std::cout<<"mcratios["<<i<<"]->GetBinContent(5)="<<    mcratios[i]->GetBinContent(5)<<std::endl;

    
    //FastNLO file from JOAO
    std::string thyfilepath= FNLO_DIR+nlothyfile+".root";
    TFile* thyfile=TFile::Open(( thyfilepath).c_str(), "READ");
    
    thyspectra[i] =  (TH1D*)(
			     (
			      (TH1D*)thyfile->Get(("h1100"+std::to_string(i+1)+"00").c_str()) 
			      )->Clone( 
				       ("thy_ybin"+std::to_string(i)).c_str() 
					)
			     );        
    thyspectra[i]->Scale(.001);//units duh
    
    thyspectrabin0_rebin[i]=(TH1D*)thyspectra[0]->Clone(("thy_ybin0_binsOfybin"+std::to_string(i)).c_str());
    multiplyBinWidth(thyspectrabin0_rebin[i]);
    thyspectrabin0_rebin[i]=(TH1D*)thyspectrabin0_rebin[i]->TH1::Rebin( nbins, ((std::string)thyspectrabin0_rebin[i]->GetName()+"_rebin").c_str() , ((double*)ptbinedges.data()) );
    divideBinWidth(thyspectrabin0_rebin[i]);
    
    thyratios[i]=(TH1D*) thyspectra[i]->Clone(("thy_ybin0ratio_ybin"+std::to_string(i)).c_str());//do this here because thyspectra[0] needs to be unchanged for the rest of the routine to work right and put the NLO in the same binning as the unfolded results
    multiplyBinWidth(thyratios[i]);
    thyratios[i]=(TH1D*)thyratios[i]->TH1::Rebin( nbins, ((std::string)thyratios[i]->GetName()+"_rebin").c_str() , ((double*)ptbinedges.data()) );
    divideBinWidth(thyratios[i]);

    //thyratios[i]->Divide(thyspectrabin0_rebin[i]);
    //thyratios[i]->Divide(mcspectrabin0_rebin[i]);
    thyratios[i]->Divide(spectrabin0_rebin[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      thyratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    thyratios[i]->SetMarkerSize(1.2);  thyratios[i]->SetMarkerColor(kMagenta);   thyratios[i]->SetMarkerStyle(kOpenStar);
    //thyratios[i]->SetLineColorAlpha(0., kGray);    
    thyratios[i]->SetLineColor(kMagenta);    
    std::cout<<"thyratios["<<i<<"]->GetBinContent(5)="<<    thyratios[i]->GetBinContent(5)<<std::endl;  
    
    ptbinedges.clear();    

    std::string NPCfilepath= NPC_DIR + NPC_FILE + ".root";
    std::string NPC_str="HerwigEE5C";
    TFile* NPCfile=TFile::Open(( NPCfilepath).c_str(), "READ");  
    NPCfit[i] =  (TF1*)(
			(
			 (TF1*)NPCfile->Get(("fNPC_"+NPC_str+"_R4_etabin"+std::to_string(i)).c_str()) 
			 )->Clone( 
				  ("fNPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str()) 			 
			);
    
    
    NPCfithist[i]=(TH1D*)thyspectra[i]->Clone(("NPCfit_ybin0_binsOfybin"+std::to_string(i)).c_str());
    NPCfithist[i]->Reset("MICES");
    for(int j=1; j<=NPCfithist[i]->GetNbinsX();j++){
      NPCfithist[i]->SetBinContent(j,NPCfit[i]->Eval(NPCfithist[i]->GetBinCenter(j)));
    }
    
    NPCfithistbin0_rebin[i]=(TH1D*)NPCfithist[0]->Clone(("NPCfithist_ybin0_binsOfybin"+std::to_string(i)).c_str());
    multiplyBinWidth(NPCfithistbin0_rebin[i]);
    NPCfithistbin0_rebin[i]=(TH1D*)NPCfithistbin0_rebin[i]->TH1::Rebin( nbins, ((std::string)NPCfithistbin0_rebin[i]->GetName()+"_rebin").c_str() , ((double*)ptbinedges.data()) );
    divideBinWidth(NPCfithistbin0_rebin[i]);

    NPCfitratios[i]=(TH1D*) NPCfithist[i]->Clone(("NPCfitratio_ybin0ratio_ybin"+std::to_string(i)).c_str());//do this here because thyspectra[0] needs to be unchanged for the rest of the routine to work right and put the NLO in the same binning as the unfolded results
    multiplyBinWidth(NPCfitratios[i]);
    NPCfitratios[i]=(TH1D*)NPCfitratios[i]->TH1::Rebin( nbins, ((std::string)NPCfitratios[i]->GetName()+"_rebin").c_str() , ((double*)ptbinedges.data()) );
    divideBinWidth(NPCfitratios[i]);
    
    NPCfitratios[i]->Divide(NPCfithistbin0_rebin[i]);
    NPCfitratios[i]->SetMarkerSize(1.0);  NPCfitratios[i]->SetMarkerColor(kBlue);   NPCfitratios[i]->SetMarkerStyle(kFullSquare);
    NPCfitratios[i]->SetLineColor(kBlue);    
    

    
  }
  
  TCanvas* canv=makeSMPRatioCanvas("NLOunfdataAcrossy_SMPInclJetXsec_ratio");  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){
    
    
    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    
    TLine* p75     =makeTLine(xlo, 0.60 , xhi, 0.60);    
    TLine* p50     =makeTLine(xlo, 0.20 , xhi, 0.20);    
    TLine* p25     =makeTLine(xlo, 1.40 , xhi, 1.40);    
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][ ");    
    one     ->Draw();       
    p75     ->Draw();       
    p50     ->Draw();       
    p25     ->Draw();       
    mcratios[i]->Draw("HIST E ][ SAME ");    
    thyratios[i]->Draw("HIST E ][ SAME ");    
    //NPCfitratios[i]->Draw("HIST E ][ SAME");
    ratios[i]->Draw("HIST E ][ SAME");    
    
    if(i==0){
      TLegend* leg=makeLegend(0.55, 0.63, 0.87, 0.87);
      leg->AddEntry(ratios[i],"NLO #otimes NP Unf. Data","lp");            
      leg->AddEntry(mcratios[i],"CT14nnlo NLO #otimes Herwig EE5C NPCs","lp");            
      leg->AddEntry(thyratios[i],"CT14nnlo NLO","lp");            
      //leg->AddEntry(NPCfitratios[i],"Herwig EE5C in #||{y} bins > 0.5","lp");
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
  
  
  //makeSMPInclJetXsec_NLOunfdataAcrossy_ratios
  saveCanv(outdir, canv, fout);
  //if((bool)fout){
  //  fout->cd();
  //  for(int i=0; i<netabins;i++){
  //    ratios[i]->Write();
  //  }
  //}

  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();		  
    spectrabin0_rebin[i]->Delete();	  
    ratios[i]->Delete();		  
                                      
    mcspectra[i]->Delete();		  
    mcspectrabin0_rebin[i]->Delete(); 
    mcratios[i]->Delete();		  
                                      
    thyspectra[i]->Delete();	  
    thyspectrabin0_rebin[i]->Delete();
    thyratios[i]->Delete();		  
                                      
    NPCfit[i]->Delete();		  
    //NPCfithist[i]->Delete();	  
    //NPCfithistbin0_rebin[i]->Delete();
    NPCfitratios[i]->Delete();        

  }
  //canv->Delete();
      
  return;
}



void  makeSMPInclJetXsec_PY8unfdataAcrossy_ratios (std::string outdir, TFile* fout){
  
  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* spectra[netabins]={};		 
  TH1D* spectrabin0_rebin[netabins]={};	 
  TH1D* ratios[netabins]={};		 
	                                 
  TH1D* mcspectra[netabins]={};		 
  TH1D* mcspectrabin0_rebin[netabins]={};
  TH1D* mcratios[netabins]={};           
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    //SPECTRA ONLY, NO SYST
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_unf") 
			   )->Clone( 
				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
				     )
			  );
    
    int nbins=spectra[i]->GetNbinsX();
    std::vector<double> ptbinedges;
    for(int j=1;j<=nbins;j++)
      ptbinedges.push_back(spectra[i]->GetBinLowEdge(j));
    ptbinedges.push_back(spectra[i]->GetBinLowEdge(nbins)+spectra[i]->GetBinWidth(nbins));
    
    spectrabin0_rebin[i]=(TH1D*)spectra[0]->Clone(("Data_unf_ybin0_binsOfybin"+std::to_string(i)).c_str());
    multiplyBinWidth(spectrabin0_rebin[i]);
    spectrabin0_rebin[i]=(TH1D*)spectrabin0_rebin[i]->TH1::Rebin( nbins, ((std::string)spectrabin0_rebin[i]->GetName()+"_rebin").c_str() , ((double*)ptbinedges.data()) );
    divideBinWidth(spectrabin0_rebin[i]);
    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_unf_ybin0ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(spectrabin0_rebin[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.0);    ratios[i]->SetMaximum(1.6);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to 0.0 < #||{y} < 0.5");
    
    mcspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)file->Get("MC_truth") 
			     )->Clone( 
				      ("MC_truth_ybin"+std::to_string(i)).c_str() 
				       )
			    );        
    mcspectrabin0_rebin[i]=(TH1D*)mcspectra[0]->Clone(("MC_truth_ybin0_binsOfybin"+std::to_string(i)).c_str());
    multiplyBinWidth(mcspectrabin0_rebin[i]);
    mcspectrabin0_rebin[i]=(TH1D*)mcspectrabin0_rebin[i]->TH1::Rebin( nbins, ((std::string)mcspectrabin0_rebin[i]->GetName()+"_rebin").c_str() , ((double*)ptbinedges.data()) );
    divideBinWidth(mcspectrabin0_rebin[i]);

    mcratios[i]=(TH1D*) mcspectra[i]->Clone(("MC_truth_ybin0ratio_ybin"+std::to_string(i)).c_str());
    mcratios[i]->Divide(mcspectrabin0_rebin[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      mcratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    mcratios[i]->SetMarkerSize(1.2);  mcratios[i]->SetMarkerColor(kGray);   mcratios[i]->SetMarkerStyle(kOpenCircle);
    mcratios[i]->SetLineColor(kGray);    
    
    ptbinedges.clear();    
  }
  
  TCanvas* canv=makeSMPRatioCanvas("PY8unfdataAcrossy_SMPInclJetXsec_ratio");  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){
    
    
    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    
    TLine* p75     =makeTLine(xlo, 0.75 , xhi, 0.75);    
    TLine* p50     =makeTLine(xlo, 0.50 , xhi, 0.50);    
    TLine* p25     =makeTLine(xlo, 0.25 , xhi, 0.25);    
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][ ");    
    one     ->Draw();      
    p75     ->Draw();       
    p50     ->Draw();       
    p25     ->Draw();       
    
    mcratios[i]->Draw("HIST E ][ SAME ");    
    ratios[i]->Draw("HIST E ][ SAME");    
    
    if(i==0){
      TLegend* leg=makeLegend(0.55, 0.63, 0.87, 0.87);
      leg->AddEntry(ratios[i],"PYTHIA8 Unf. Data in #||{y} bins > 0.5","lp");            
      leg->AddEntry(mcratios[i],"GEN PYTHIA8 in #||{y} bins > 0.5","lp");            
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
  
  
  //makeSMPInclJetXsec_PY8unfdataAcrossy_ratios
  saveCanv(outdir, canv, fout);
  //if((bool)fout){
  //  fout->cd();
  //  for(int i=0; i<netabins;i++){
  //    ratios[i]->Write();
  //  }
  //}

  for(int i=0; i<netabins;i++){
    spectra[i]->Delete();		 
    spectrabin0_rebin[i]->Delete();	 
    ratios[i]->Delete();		 
                                     
    mcspectra[i]->Delete();		 
    mcspectrabin0_rebin[i]->Delete();
    mcratios[i]->Delete();           
  }
  //canv->Delete();
  
  return;
}




//void amitakingcrazypills(TH1D* ratio, int bin, std::string outdir);
//
//void amitakingcrazypills(TH1D* ratio, int bin, std::string outdir){
//  
//  TH1D* ratioclone_zero  =(TH1D*)ratio->Clone("crazyclone_zero"  ); // mc/(data)=mc/(counts/lumi)=(mc/counts)*lumi
//  TH1D* ratioclone_up  =(TH1D*)ratio->Clone("crazyclone_up"  ); // mc/(data)=mc/(counts/lumi)=(mc/counts)*lumi
//  TH1D* ratioclone_down=(TH1D*)ratio->Clone("crazyclone_down");
//  //lumi err is +/- 2.3%. up value  =(mc/counts)*lumi*1.023
//  ratioclone_up  ->Scale(1.000+0.023);
//  //lumi err is +/- 2.3%. down value=(mc/counts)*lumi*0.977
//  ratioclone_down->Scale(1.000-0.023);
//  
//  for(int j=1; j<=ratioclone_up->GetNbinsX();j++){
//    std::cout<<"bin j="<<j<<std::endl;
//    std::cout<<"up   diff= "<<  ratioclone_up->GetBinContent(j)-ratio->GetBinContent(j)<<std::endl;
//    std::cout<<"down diff="<<ratioclone_down->GetBinContent(j)-ratio->GetBinContent(j)<<std::endl;
//    ratioclone_zero->SetBinContent(j,0.);
//    ratioclone_up  ->SetBinContent(j,ratioclone_up  ->GetBinContent(j)-ratio->GetBinContent(j));
//    ratioclone_down->SetBinContent(j,ratioclone_down->GetBinContent(j)-ratio->GetBinContent(j));
//  }
//  
//  TCanvas* crazycanvas=new TCanvas(
//				   ("crazycanv_"+std::to_string(bin)).c_str(),
//				   ("crazycanv_"+std::to_string(bin)).c_str(),
//				   CANVX, CANVY);
//  crazycanvas->SetLogx(1);
//  crazycanvas->SetLogy(0);
//  crazycanvas->cd();
//  ratioclone_zero->SetMaximum(0.08);
//  ratioclone_zero->SetMinimum(-0.08);
//  ratioclone_zero->Draw("HIST");
//  ratioclone_up->Draw("HIST SAME");
//  ratioclone_down->Draw("HIST SAME");
//  saveCanv(outdir, crazycanvas);
//  //CONCLUSION, no i am not, but the diff in the diff between bins is very small so i dont have to worry about it, it is about 2.3%, b.c. taylor expansions
//  return;
//}















/*
//deprecated approach... too convoluted. this is saved for backwards compatibility or something. probably still worthless at this point.
void  makeSMPInclJetXsec_NPCs_onePadOneEta(std::string outdir, TFile* fout, std::string NPC_str){
  
  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  
  if(NPC_str=="")
    NPC_str="HerwigEE5C";
  
  const int netabins=NLO_UNFDIR_DATA_Nfiles;
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1F* NPCdata_toClone[netabins]={};
  TH1F* NPCdata[netabins]={};
  TF1*  NPCfit[netabins]={};
  TF1*  NPCfit_sysup[netabins]={};
  TF1*  NPCfit_sysdown[netabins]={};
  double ymax=-1.;
  double ymin=99999999999999999999.;
  double xmin[netabins]={0.};
  double xmax[netabins]={0.};
  
  std::string filepath= NPC_DIR + NPC_FILE + ".root";
  TFile* file=TFile::Open(( filepath).c_str(), "READ");  
  for(int i=0; i<netabins; i++){
    if(filepath.find("fromJohn")==std::string::npos){
      NPCfit[i] =  (TF1*)(
			  (
			   (TF1*)file->Get( ("fNPC_"+NPC_str+"_R4_etabin"+std::to_string(i)).c_str())
			   )->Clone(        ("fNPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str()
					    )
			  );
      NPCdata_toClone[i] =  (TH1F*)(
				    (
				     (TH1F*)file->Get( ("NPC_"+NPC_str+"_R4_etabin"+std::to_string(i)).c_str())
				     )->Clone( 
					      ("toClone_NPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str()
					       )
				    );
    }
    else {
      NPCfit[i] =  (TF1*)(
			  (
			   (TF1*)file->Get( ("fNPC_"+NPC_str+"_R4_etabin"+std::to_string(i)).c_str())
			   )->Clone(        ("fNPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str()
					    )
			  );
      if(NPC_str!="AVG"){
	NPCdata_toClone[i] =  (TH1F*)(
				      (
				       (TH1F*)file->Get( ("hNPC_"+NPC_str+"_R4_etabin"+std::to_string(i)).c_str())
				       )->Clone( 
						("toClone_NPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str()
						 )
				      );
      }
      
    }
    
    if(NPC_str!="AVG"){
      //have to do this bit because something about the NPC hists from raghav is weird for POWPY8 and HerwigEE4C NPs
      const int nptbins=NPCdata_toClone[i]->GetNbinsX();
      std::vector<Double_t> bins;
      for(int j=1; j<=nptbins;j++){
	bins.push_back(NPCdata_toClone[i]->GetBinLowEdge(j));
	if(j==(nptbins)){
	  bins.push_back(NPCdata_toClone[i]->GetBinLowEdge(j) + NPCdata_toClone[i]->GetBinWidth(j));
	}
      }
      const double* binsforhist=(double*)bins.data();
      
      NPCdata[i]=new TH1F(
			  ("NPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str(),
			  ("NPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str(),
			  nptbins, binsforhist);
      for(int j=1; j<=nptbins;j++){
	NPCdata[i]->SetBinContent(j, NPCdata_toClone[i]->GetBinContent(j));
	NPCdata[i]->SetBinError(j, NPCdata_toClone[i]->GetBinError(    j));
      }
    }
    //end weird thing
    
    if(filepath.find("fromJohn")==std::string::npos){
      NPCfit_sysup[i]=(TF1*)NPCfit[i]->Clone(
					     ("fNPC_"+NPC_str+"_R4_sysup_ybin"+std::to_string(i)).c_str()
					     );
      NPCfit_sysup[i]->SetParameter(0, NPCfit[i]->GetParameter(0)+NPCfit[i]->GetParError(0));
      NPCfit_sysup[i]->SetParameter(1, NPCfit[i]->GetParameter(1)+NPCfit[i]->GetParError(1));
      NPCfit_sysup[i]->SetParameter(2, NPCfit[i]->GetParameter(2)-NPCfit[i]->GetParError(2));
      
      NPCfit_sysdown[i]=(TF1*)NPCfit[i]->Clone(
					       ("fNPC_"+NPC_str+"_R4_sysdown_ybin"+std::to_string(i)).c_str()
					       );
      NPCfit_sysdown[i]->SetParameter(0, NPCfit[i]->GetParameter(0)-NPCfit[i]->GetParError(0));
      NPCfit_sysdown[i]->SetParameter(1, NPCfit[i]->GetParameter(1)-NPCfit[i]->GetParError(1));
      NPCfit_sysdown[i]->SetParameter(2, NPCfit[i]->GetParameter(2)+NPCfit[i]->GetParError(2));
    }
    else {
      NPCfit_sysup[i] =  (TF1*)(
				(
				 (TF1*)file->Get( ("fNPC_"+NPC_str+"_R4_etabin"+std::to_string(i)+"_up").c_str())
				 )->Clone(        ("fNPC_"+NPC_str+"_sysup_R4_ybin"+std::to_string(i)).c_str()
						  )
				);
      NPCfit_sysdown[i] =  (TF1*)(
				  (
				   (TF1*)file->Get( ("fNPC_"+NPC_str+"_R4_etabin"+std::to_string(i)+"_down").c_str())
				   )->Clone(        ("fNPC_"+NPC_str+"_sysdown_R4_ybin"+std::to_string(i)).c_str()
						    )
				  );
    }
    
    


    
    float th1max;
    float th1min;
    if(NPC_str!="AVG"){
      th1max=NPCdata[i]->GetMaximum();
      th1min=getnonzeromin((TH1*)NPCdata[i]);
      if(th1max>ymax)ymax=th1max;
      if(th1min<ymin)ymin=th1min;    
      xmin[i]=NPCdata[i]->GetBinLowEdge(1);
      xmax[i]=NPCdata[i]->GetBinLowEdge(NPCdata[i]->GetNbinsX())+NPCdata[i]->GetBinWidth(NPCdata[i]->GetNbinsX());
    }
    else{
      th1max=1.05;
      th1min=0.95;
      ymax=th1max;
      ymin=th1min;
      NPCfit[i]->GetRange(xmin[i],xmax[i]);      
    }
    
  }
  
  if(NPC_str!="AVG"){
    NPCdata[0]->SetLineColor(kRed);     NPCdata[0]->SetMarkerColor(kBlack); NPCdata[0]->SetMarkerStyle(kFullCircle); NPCdata[0]->SetMarkerSize(.6);
    NPCdata[1]->SetLineColor(kGreen);   NPCdata[1]->SetMarkerColor(kBlack); NPCdata[1]->SetMarkerStyle(kFullCircle); NPCdata[1]->SetMarkerSize(.6);
    NPCdata[2]->SetLineColor(kBlue);    NPCdata[2]->SetMarkerColor(kBlack); NPCdata[2]->SetMarkerStyle(kFullCircle); NPCdata[2]->SetMarkerSize(.6);
    NPCdata[3]->SetLineColor(kMagenta); NPCdata[3]->SetMarkerColor(kBlack); NPCdata[3]->SetMarkerStyle(kFullCircle); NPCdata[3]->SetMarkerSize(.6);
  }

  NPCfit[0]->SetLineColor(kRed);     
  NPCfit[1]->SetLineColor(kGreen);   
  NPCfit[2]->SetLineColor(kBlue);    
  NPCfit[3]->SetLineColor(kMagenta); 
  
  NPCfit_sysup[0]->SetLineColorAlpha( 3+kRed    ,0.7 );         NPCfit_sysdown[0]->SetLineColorAlpha( 3+kRed    ,0.7 ); 
  NPCfit_sysup[1]->SetLineColorAlpha( 3+kGreen  ,0.7 ); 	NPCfit_sysdown[1]->SetLineColorAlpha( 3+kGreen  ,0.7 ); 
  NPCfit_sysup[2]->SetLineColorAlpha( 3+kBlue   ,0.7 ); 	NPCfit_sysdown[2]->SetLineColorAlpha( 3+kBlue   ,0.7 ); 
  NPCfit_sysup[3]->SetLineColorAlpha( 3+kMagenta,0.7 ); 	NPCfit_sysdown[3]->SetLineColorAlpha( 3+kMagenta,0.7 ); 


  TCanvas* canv=makeSMPRatioCanvas(NPC_str+"_NPCs_onePadOneEta");
  
  TPaveText* SMPtitle=makeSimPaveTextTitleRatio();
  bool dologx=true, dology=false;
  for(int i=0; i<netabins; i++){

    TLegend* leg=makeLegend(.15,.65,.6,.9);
    leg->SetHeader( (NPC_str+" NPCs (R=0.4)").c_str(),"" );    
    if(NPC_str!="AVG")leg->AddEntry(NPCdata[i],"Data Points", "lpe");
    leg->AddEntry(NPCfit[i],"Fit", "l");
    //leg->AddEntry(NPCfit_sysup[i],"Fit Unc.", "l");
    canv->cd(i+1)->SetLogx(dologx);//maybe set to 1?
    canv->cd(i+1)->SetLogy(dology);//maybe set to 1?
    canv->cd(i+1);
    
    setRatioHistLabels((TH1*)NPCdata[i], "Correction Factor");
    NPCdata[i]->GetXaxis()->SetTitle("Jet p_{T} [GeV]");

    if(dologx)NPCdata[i]->GetXaxis()->SetNoExponent(true);
    if(dologx)NPCdata[i]->GetXaxis()->SetMoreLogLabels(true);
    //NPCdata[i]->SetAxisRange(ymin*.3,ymax*1.7, "Z");
    //NPCdata[i]->SetAxisRange(ymin*.95,ymax*1.1, "Y");
    NPCdata[i]->SetAxisRange(.95,1.05, "Y");
    NPCdata[i]->SetAxisRange(xmin[i],xmax[i], "X");

    NPCdata[i]->Draw("");    
    //TLine* one     =makeTLine(xmin[i], 1. , xmax[i], 1.);    
    TLine* one     =makeTLine(xmin[i], 1. , xmax[i], 1.);    
    one     ->Draw();      
    NPCdata[i]->Draw("HIST E ][ SAME");    
    NPCfit[i]->Draw("SAME");
    NPCfit_sysup[i]->Draw("SAME");
    NPCfit_sysdown[i]->Draw("SAME");

    TPaveText* desc=makePaveText( 0.4, .9, 0.6, .98);
    //desc->AddText(const_etabin_strs[i].c_str());
    desc->AddText(const_ybin_strs[i].c_str());
    //desc->AddText(jettype.c_str());
    desc->Draw();
    SMPtitle->Draw();
    leg->Draw();
    
  }
  
  //makeSMPInclJetXsec_NPCs_onePadOneEta
  saveCanv(outdir, canv, fout);
  if((bool)fout){
    fout->cd();
    if(NPC_str!="AVG")
      for(int i=0; i<netabins;i++){
	NPCdata[i]->Write();
      }
    for(int i=0; i<netabins;i++){
      NPCfit[i]->Write();
    }
    for(int i=0; i<netabins;i++){
      NPCfit_sysup[i]->Write();
    }
    for(int i=0; i<netabins;i++){
      NPCfit_sysdown[i]->Write();
    }
  }

  
  return;
}
*/















//--------------------------------------------------------------------------------------------------------------------------------
//this is just to make systematic error bands on the theory itself, by itself. show as a deviation from 1.
void  makeSMPInclJetXsec_NLOsyst_ratios (std::string outdir, TFile* fout, std::string order){
  std::cout<<"running makeSMPInclJetXsec_NLOsyst_ratios for "<<order<<std::endl;
  

  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  
  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }

  
  //FastNLO file from JOAO
  std::string thyfilepath= FNLO_DIR+nlothyfile+".root";
  TFile* thyfile=TFile::Open(( thyfilepath).c_str(), "READ");
  
  TH1D* mcspectra[netabins]={};// Matrix Element Calculation of NNPDF; use for data comparisons
  TH1D* mcspectra_statunc[netabins]={};
  TH1D* mcspectra_PDFup[netabins]={};
  TH1D* mcspectra_PDFdown[netabins]={};
  TH1D* mcspectra_NPup[netabins]={};
  TH1D* mcspectra_NPdown[netabins]={};
  
  TH1D* ratios[netabins]={};
  TH1D* ratios_statunc[netabins]={};
  TH1D* ratios_PDFup[netabins]={};
  TH1D* ratios_PDFdown[netabins]={};
  TH1D* ratios_NPup[netabins]={};
  TH1D* ratios_NPdown[netabins]={};
  TH1D* ratios_totaluncUP[netabins]={};
  TH1D* ratios_totaluncDOWN[netabins]={};


  std::string thyname="CT14nnlo "+order;
  
  for(int i=0; i<netabins; i++){
    int orderint=-1;
    if(order=="NNLO")orderint=0;
    else if(order=="NLO")orderint=1;
    else if(order=="LO")orderint=2;
    else return;
    
    std::string thyhistname="h"+std::to_string(orderint)+"100"+std::to_string(i+1)+"0";
    std::cout<<"thyhistname="<<thyhistname<<std::endl;
    mcspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)thyfile->Get((thyhistname+"0").c_str()) 
			     )->Clone( 
				      ("thy_"+order+"_ybin"+std::to_string(i)).c_str() 
				       )
			    );       
    applyNPCorrs(mcspectra[i],i);    

    //because the way i did the histogram binning in the files is they all have the same # of bins (kinda stupid, but oh well...)
    int nbins=mcspectra[i]->GetNbinsX();
    std::vector<double> ptbinedges;
    for(int j=1;j<=nbins;j++){
      
      if(mcspectra[i]->GetBinContent(j)>0.)
	ptbinedges.push_back(mcspectra[i]->GetBinLowEdge(j));
      
      //check for last bin, kill loop if it is to avoid next if statement
      if(j==nbins){
	ptbinedges.push_back(mcspectra[i]->GetBinLowEdge(j)+mcspectra[i]->GetBinWidth(j));
	std::cout<<"etabin == "<<i<<" , number of bins before rebinning = "<< nbins << ", after rebinning = "<<ptbinedges.size()-1<<std::endl;
	break;
      }
      //check for zero bin content, kill loop if 
      if(!(mcspectra[i]->GetBinContent(j)>0.)){
	ptbinedges.push_back(mcspectra[i]->GetBinLowEdge(j)+mcspectra[i]->GetBinWidth(j));
	std::cout<<"etabin == "<<i<<" , number of bins before rebinning = "<< nbins << ", after rebinning = "<<ptbinedges.size()-1<<std::endl;
	break;
      }
    }
    int nbins_nonzero=(ptbinedges.size()-1);
    mcspectra[i]       =(TH1D*)       mcspectra[i]->TH1::Rebin(nbins_nonzero,((std::string)mcspectra[i]->GetName()+"_rebin").c_str(),((double*)ptbinedges.data()));
    
    
    //so the stat unc isn't inflated by sqrt(2) in the ratio at 1
    for(int j=1; j<=mcspectra[i]->GetNbinsX();j++)//errors due to PDF will be illustrated by 6 point scale var error. leave inherent PDF errors out of it.
      mcspectra[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root]
    
    ratios[i]=(TH1D*) mcspectra[i]->Clone(("thy_"+order+"_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(mcspectra[i]);//should just be at 1
    ratios[i]->SetMarkerSize(0);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.4);    ratios[i]->SetMaximum(1.6);
    setRatioHistLabels((TH1D*)ratios[i], thyname+" #otimes NPC Relative Error");
    
    //stat unc
    mcspectra_statunc[i] =  (TH1D*)(
				    (
				     (TH1D*)thyfile->Get((thyhistname+"0").c_str()) 
				     )->Clone( 
					      ("thy_statunc_"+order+"_ybin"+std::to_string(i)).c_str() 
					       )
				    );   
    //for(int j=1; j<=mcspectra_statunc[i]->GetNbinsX();j++)mcspectra_statunc[i]->SetBinError(j,1.e-30);
    applyNPCorrs(mcspectra_statunc[i],i);

    mcspectra_statunc[i]=(TH1D*)mcspectra_statunc[i]->TH1::Rebin(nbins_nonzero,((std::string)mcspectra_statunc[i]->GetName()+"_rebin").c_str(),((double*)ptbinedges.data()));
    ratios_statunc[i]=(TH1D*)mcspectra_statunc[i]->Clone(
							 ("thy_statunc_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
							 );
    ratios_statunc[i]->Divide(mcspectra[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    

    
    //PDF 6PT SYSTEMATICS, USE THY HIST NOT TOY MC ANYMORE, NO NEED FOR SEP FILE
    mcspectra_PDFup[i] =  (TH1D*)(
				  (
				   (TH1D*)thyfile->Get((thyhistname+"9_spectra").c_str()) 
				   )->Clone( 
					    ("thy_"+order+"_PDFsysup_ybin"+std::to_string(i)).c_str() 
					     )
				  );
    applyNPCorrs(mcspectra_PDFup[i],i);
    mcspectra_PDFup[i]=(TH1D*)mcspectra_PDFup[i]->TH1::Rebin(nbins_nonzero,((std::string)mcspectra_PDFup[i]->GetName()+"_rebin").c_str(),((double*)ptbinedges.data()));
    ratios_PDFup[i]=(TH1D*)mcspectra_PDFup[i]->Clone(
						     ("thy_PDFsysup_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
						     );
    ratios_PDFup[i]->Divide(mcspectra[i]);
    ratios_PDFup[i]->SetMarkerSize(0);  ratios_PDFup[i]->SetMarkerColor(kBlack);   ratios_PDFup[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFup[i]->SetLineColor(kMagenta);    ratios_PDFup[i]->SetLineWidth(1);    
    
    
    
    
    mcspectra_PDFdown[i] =  (TH1D*)(
				    (
				     (TH1D*)thyfile->Get((thyhistname+"8_spectra").c_str()) 
				     )->Clone( 
					      ("thy_"+order+"_PDFsysdown_ybin"+std::to_string(i)).c_str() 
					       )
				    );
    applyNPCorrs(mcspectra_PDFdown[i],i);
    mcspectra_PDFdown[i]=(TH1D*)mcspectra_PDFdown[i]->TH1::Rebin(nbins_nonzero,((std::string)mcspectra_PDFdown[i]->GetName()+"_rebin").c_str(),((double*)ptbinedges.data()));
    ratios_PDFdown[i]=(TH1D*)mcspectra_PDFdown[i]->Clone(
							 ("thy_PDFsysdown_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
							 );
    ratios_PDFdown[i]->Divide(mcspectra[i]);
    ratios_PDFdown[i]->SetMarkerSize(0);  ratios_PDFdown[i]->SetMarkerColor(kBlack);   ratios_PDFdown[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFdown[i]->SetLineColor(kMagenta);    ratios_PDFdown[i]->SetLineWidth(1);    
    
    
    //NP SYSTEMATICS, CURRENTLY BASED JUST ON FIT PARAMETER UNCERTAINTIES
    mcspectra_NPup[i] =  (TH1D*)(
				 (
				  (TH1D*)thyfile->Get((thyhistname+"0").c_str()) 
				  )->Clone( 
					   ("thy_"+order+"_NPsysup_ybin"+std::to_string(i)).c_str() 
					    )
				 );        
    applyNPCorrs(mcspectra_NPup[i],i,"up");
    mcspectra_NPup[i]  =(TH1D*)  mcspectra_NPup[i]->TH1::Rebin(nbins_nonzero,((std::string)mcspectra_NPup[i]->GetName()+"_rebin").c_str(),((double*)ptbinedges.data()));
    
    ratios_NPup[i]=(TH1D*)mcspectra_NPup[i]->Clone(
						   ("thy_NPsysup_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
						   );
    ratios_NPup[i]->Divide(mcspectra[i]);
    ratios_NPup[i]->SetMarkerSize(0);  ratios_NPup[i]->SetMarkerColor(kBlack);   ratios_NPup[i]->SetMarkerStyle(kFullCircle);
    ratios_NPup[i]->SetLineColor(kCyan);    ratios_NPup[i]->SetLineWidth(1);    
    
    mcspectra_NPdown[i] =  (TH1D*)(
				   (
				    (TH1D*)thyfile->Get((thyhistname+"0").c_str()) 
				    )->Clone( 
					     ("thy_"+order+"_NPsysdown_ybin"+std::to_string(i)).c_str() 
					      )
				   );        
    applyNPCorrs(mcspectra_NPdown[i],i,"down");
    mcspectra_NPdown[i]=(TH1D*)mcspectra_NPdown[i]->TH1::Rebin(nbins_nonzero,((std::string)mcspectra_NPdown[i]->GetName()+"_rebin").c_str(),((double*)ptbinedges.data()));
    
    ratios_NPdown[i]=(TH1D*)mcspectra_NPdown[i]->Clone(
						       ("thy_NPsysdown_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
						       );
    ratios_NPdown[i]->Divide(mcspectra[i]);
    ratios_NPdown[i]->SetMarkerSize(0);  ratios_NPdown[i]->SetMarkerColor(kBlack);   ratios_NPdown[i]->SetMarkerStyle(kFullCircle);
    ratios_NPdown[i]->SetLineColor(kCyan);    ratios_NPdown[i]->SetLineWidth(1);    
    
    ////TOTAL UNC (STAT + SYST)
    ratios_totaluncUP[i]=(TH1D*) ratios_statunc[i]->Clone(("MC_totalUncUP_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncUP[i]->Reset("MICES");
    ratios_totaluncUP[i]->SetMarkerSize(0);  ratios_totaluncUP[i]->SetMarkerColor(kBlack);   ratios_totaluncUP[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncUP[i]->SetLineColor(kBlack);    ratios_totaluncUP[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("up",
			   ratios_statunc[i],
		       ((std::vector<TH1*>){ratios_PDFup[i],ratios_NPup[i]}) ,
		       ratios_totaluncUP[i]);

    ratios_totaluncDOWN[i]=(TH1D*) ratios_statunc[i]->Clone(("MC_totalUncDOWN_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncDOWN[i]->Reset("MICES");
    ratios_totaluncDOWN[i]->SetMarkerSize(0);  ratios_totaluncDOWN[i]->SetMarkerColor(kBlack);   ratios_totaluncDOWN[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncDOWN[i]->SetLineColor(kBlack);    ratios_totaluncDOWN[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("down",
		       ratios_statunc[i],
		       ((std::vector<TH1*>){ratios_PDFdown[i],ratios_NPdown[i]}) ,
		       ratios_totaluncDOWN[i]);
  
  }  

  
  TCanvas* canv=makeSMPRatioCanvas("CT14nnlo_"+order+"_syst_SMPInclJetXsec_ratio");
  TPaveText* SMPtitle=makeSimPaveTextTitleRatio();
  
  for(int i=0; i<netabins; i++){

    ratios[i]->GetXaxis()->SetNoExponent(true);
    ratios[i]->GetXaxis()->SetMoreLogLabels(true);

    
    
    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);      

    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][ ");    
    one     ->Draw();       
    ratios_statunc[i]->Draw("HIST E ][ SAME");    
    ratios_PDFup[i]->Draw("HIST ][ SAME");    
    ratios_PDFdown[i]->Draw("HIST ][ SAME");  
    ratios_NPup[i]->Draw("HIST ][ SAME");    
    ratios_NPdown[i]->Draw("HIST ][ SAME");  
    ratios_totaluncUP[i]->Draw("HIST ][ SAME");    
    ratios_totaluncDOWN[i]->Draw("HIST ][ SAME");  
    ratios[i]->Draw("HIST E ][ SAME");
    
    if(i==1){
      TLegend* leg=makeLegend(0.55, 0.63, 0.88, 0.87);
      leg->SetHeader(("CT14nnlo "+order).c_str(),"");
      leg->AddEntry(ratios_statunc[i],"Stat Unc.","le");
      leg->AddEntry(ratios_PDFup[i]  ,"6P Scale Unc.","l");
      leg->AddEntry(ratios_NPup[i]   ,"NPC Unc.","l");
      leg->AddEntry(ratios_totaluncUP[i]   ,"Stat. #oplus Syst. Unc.","l");
      leg->Draw();}  
    
    
    TPaveText* desc=NULL;
    if     (i==0)desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    else if(i==1)desc=makePaveText( 0.15, 0.63, 0.45, 0.88);
    else    desc=makePaveText( 0.15, 0.74, 0.45, 0.88);
    //desc->AddText(etabin_strs[i].c_str());
    desc->AddText(const_ybin_strs[i].c_str());
    std::string ptrange=ptcuts_lo;
    ptrange+=std::to_string( (int)xhi)+" GeV";
    desc->AddText(ptrange.c_str());
    if(i==0)desc->AddText(jettype.c_str());
    else if(i==1){
      if(      nlothyfile.find("murmufHTp")!=std::string::npos)
	desc->AddText(scalechoice_murmufHTp.c_str());
      else if( nlothyfile.find("murmufpt1")!=std::string::npos)
	desc->AddText(scalechoice_murmufpt1.c_str());
      else if( nlothyfile.find("murmufpt" )!=std::string::npos)
	desc->AddText(scalechoice_murmufpt .c_str());      
    }
    desc->Draw();
    
    SMPtitle->Draw();  
    
  }
  
  //makeSMPInclJetXsec_NLOsyst_ratios
  saveCanv(outdir, canv, fout);

  for(int i=0; i<netabins;i++){
    
    mcspectra[i]->Delete();
    mcspectra_statunc[i]->Delete();
    mcspectra_PDFup[i]->Delete();
    mcspectra_PDFdown[i]->Delete();
    mcspectra_NPup[i]->Delete();
    mcspectra_NPdown[i]->Delete();

    ratios[i]->Delete();
    ratios_statunc[i]->Delete();
    ratios_PDFup[i]->Delete();
    ratios_PDFdown[i]->Delete();
    ratios_NPup[i]->Delete();
    ratios_NPdown[i]->Delete();
    ratios_totaluncUP[i]->Delete();
    ratios_totaluncDOWN[i]->Delete();
  }  


  return;
}



//--------------------------------------------------------------------------------------------------------------------------------
//i can deprecate this, targPDF version does this better and is more flexible
void  makeSMPInclJetXsec_NLOunfdata_ratios (std::string outdir, TFile* fout, std::string mode){
  std::cout<<"running makeSMPInclJetXsec_NLOunfdata_ratios, mode="<<mode<<std::endl;


  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  if(mode=="" ||
     mode=="totUnc" ||
     mode=="datatotUnc" ||
     mode=="NLOtotUnc")
    std::cout<<"ratio plot unc mode="<<mode<<std::endl;
  else {
    std::cout<<"ratio plot unc mode="<<mode<<" is not recognized. return."<<std::endl;
  }
  
  //TH1D* toymcspectra[netabins]={};//toy MC version of NNPDF; use for PDF/THY errs
  TH1D* mcspectra[netabins]={};// Matrix Element Calculation of NNPDF; use for data comparisons
  TH1D* mcspectra_PDFup[netabins]={};
  TH1D* mcspectra_PDFdown[netabins]={};
  TH1D* mcspectra_NPup[netabins]={};//gonna need to make these by opening up the usual NLO file + applying the NP + rebinning
  TH1D* mcspectra_NPdown[netabins]={};

  TH1D* spectra[netabins]={};
  TH1D* spectra_JECup[netabins]={};
  TH1D* spectra_JECdown[netabins]={};
  TH1D* spectra_JERup[netabins]={};
  TH1D* spectra_JERdown[netabins]={};  
  
  TH1D* ratios[netabins]={};		     
  TH1D* ratios_statunc[netabins]={};	     
  TH1D* ratios_JECup[netabins]={};	     
  TH1D* ratios_JECdown[netabins]={};	     
  TH1D* ratios_JERup[netabins]={};	     
  TH1D* ratios_JERdown[netabins]={};	     
  TH1D* ratios_PDFup[netabins]={};	     
  TH1D* ratios_PDFdown[netabins]={};	     
  TH1D* ratios_NPup[netabins]={};	     
  TH1D* ratios_NPdown[netabins]={};	     
	                                     
  TH1D* ratios_totaluncup[netabins]={};	     
  TH1D* ratios_totaluncdown[netabins]={};    
  TH1D* ratios_MCstatunc[netabins]={};	     
  TH1D* ratios_totalMCuncup[netabins]={};    
  TH1D* ratios_totalMCuncdown[netabins]={};  
  TH1D* ratios_datastatunc[netabins]={};     
  TH1D* ratios_totaldatauncup[netabins]={};  
  TH1D* ratios_totaldatauncdown[netabins]={};
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";//also has JEC systematics
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    //SPECTRA ONLY, NO SYST
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_unf") 
			   )->Clone( 
				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
				     )
			  );

    std::cout<<"grabbing theory hist from unf file: thyname=="<<thyname<<std::endl;
    mcspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)file->Get(thyname.c_str()) 
			     )->Clone( 
				      ("MC_truth_ybin"+std::to_string(i)).c_str() 
				       )
			    );        
    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_NLO_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(mcspectra[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.55);    ratios[i]->SetMaximum(1.6);
    //ratios[i]->SetMinimum(0.7);    ratios[i]->SetMaximum(1.0);
    //setRatioHistLabels((TH1D*)ratios[i], "Ratio to CT14nnlo NLO #otimes HERWIG EE5C");
    //setRatioHistLabels((TH1D*)ratios[i], "Ratio to CT14nnlo NLO #otimes PY8 NPCs");
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to CT14nnlo NLO #otimes NPCs");
    
    
    //DATA #OPLUS MC STAT UNC
    ratios_statunc[i]=(TH1D*) spectra[i]->Clone(("Data_MC_StatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_statunc[i]->Divide(mcspectra[i]);
    //setOneBinContent(ratios_statunc[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    

    // MC STAT UNC ONLY (acheived by setting data clone stat unc to 0, then dividing by mc w/ stat unc)
    ratios_MCstatunc[i]=(TH1D*) spectra[i]->Clone(("Data_MC_MCOnlyStatUnc_ratio_ybin"+std::to_string(i)).c_str());
    for(int j=1; j<=ratios_MCstatunc[i]->GetNbinsX();j++){
      ratios_MCstatunc[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc    
    }
    ratios_MCstatunc[i]->Divide(mcspectra[i]);
    //for(int j=1; j<=ratios_MCstatunc[i]->GetNbinsX();j++){//the NLO stat unc should be small, but it shouldn't be 0. This checks to make sure it isn't 0
    //  std::cout<<std::endl;
    //  std::cout<<"mcspectra       ["<<i<<"]->GetBinContent("<<j<<")="<< mcspectra[i]->GetBinContent(j)<< std::endl;
    //  std::cout<<"mcspectra       ["<<i<<"]->GetBinError  ("<<j<<")="<< mcspectra[i]->GetBinError(j)<< std::endl;
    //  std::cout<<"ratios_MCstatunc["<<i<<"]->GetBinContent("<<j<<")="<< ratios_MCstatunc[i]->GetBinContent(j)<< std::endl;
    //  std::cout<<"ratios_MCstatunc["<<i<<"]->GetBinError  ("<<j<<")="<< ratios_MCstatunc[i]->GetBinError(j)<< std::endl;
    //}
    //return;   
    ratios_MCstatunc[i]->SetMarkerSize(0);  ratios_MCstatunc[i]->SetMarkerColor(kBlack);   ratios_MCstatunc[i]->SetMarkerStyle(kFullCircle);
    ratios_MCstatunc[i]->SetLineColor(kGray+2);    

    for(int j=1; j<=mcspectra[i]->GetNbinsX();j++)//set mc stat unc to 0
      mcspectra[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root]

    // DATA STAT UNC ONLY (acheived by dividing cloned data hist w/ stat unc by mc w/o stat unc)
    ratios_datastatunc[i]=(TH1D*) spectra[i]->Clone(("Data_MC_DataOnlyStatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_datastatunc[i]->Divide(mcspectra[i]);
    ratios_datastatunc[i]->SetMarkerSize(0);  ratios_MCstatunc[i]->SetMarkerColor(kBlack);   ratios_MCstatunc[i]->SetMarkerStyle(kFullCircle);
    ratios_datastatunc[i]->SetLineColor(kGray+2);    

    for(int j=1; j<=spectra[i]->GetNbinsX();j++)
      spectra[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root]

    
    //JEC SYSTEMATICS
    spectra_JECup[i] =  (TH1D*)(
				(
			   (TH1D*)file->Get("ppData_BayesUnf_JECsysup_Spectra") 
			   )->Clone( 
				    ("Data_unf_JECsysup_ybin"+std::to_string(i)).c_str() 
				     )
			  );

    ratios_JECup[i]=(TH1D*) spectra_JECup[i]->Clone(("Data_JECsysup_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECup[i]->Divide(mcspectra[i]);
    //setOneBinContent_errHist(ratios[i], ratios_JECup[i]);
    ratios_JECup[i]->SetMarkerSize(0);  ratios_JECup[i]->SetMarkerColor(kBlack);   ratios_JECup[i]->SetMarkerStyle(kFullCircle);
    ratios_JECup[i]->SetLineColor(kRed);    ratios_JECup[i]->SetLineWidth(1);    
    
    
    spectra_JECdown[i] =  (TH1D*)(
				  (
				   (TH1D*)file->Get("ppData_BayesUnf_JECsysdown_Spectra") 
				   )->Clone( 
					    ("Data_unf_JECsysdown_ybin"+std::to_string(i)).c_str() 
					     )
				  );
    
    ratios_JECdown[i]=(TH1D*) spectra_JECdown[i]->Clone(("Data_JECsysdown_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECdown[i]->Divide(mcspectra[i]);
    //setOneBinContent_errHist(ratios[i], ratios_JECdown[i]);
    ratios_JECdown[i]->SetMarkerSize(0);  ratios_JECdown[i]->SetMarkerColor(kBlack);   ratios_JECdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JECdown[i]->SetLineColor(kRed);    ratios_JECdown[i]->SetLineWidth(1);    
    


    //PDF 6PT SYSTEMATICS, USE THY HIST NOT TOY MC ANYMORE
    std::string PDFsysfilepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_SYST_file_array[2] +ETABIN_TAG_array[i]+ ".root";//also has JEC systematics
    TFile* PDFsysfile=TFile::Open(( PDFsysfilepath).c_str(), "READ");

    mcspectra_PDFup[i] =  (TH1D*)(
				(
				 //(TH1D*)PDFsysfile->Get("CT14nlo_np_scale6_up") 
				 (TH1D*)PDFsysfile->Get("CT14nlo_np_scale6_up_rebin") 
				 )->Clone( 
					  ("MC_PDFsysup_ybin"+std::to_string(i)).c_str() 
					   )
				);

    ratios_PDFup[i]=(TH1D*) spectra[i]->Clone(("MC_PDFsysup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_PDFup[i]->Divide(mcspectra_PDFup[i]);
    ratios_PDFup[i]->SetMarkerSize(0);  ratios_PDFup[i]->SetMarkerColor(kBlack);   ratios_PDFup[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFup[i]->SetLineColor(kMagenta);    ratios_PDFup[i]->SetLineWidth(1);    
    
    
    mcspectra_PDFdown[i] =  (TH1D*)(
				  (
				   //(TH1D*)PDFsysfile->Get("CT14nlo_np_scale6_down") 
				   (TH1D*)PDFsysfile->Get("CT14nlo_np_scale6_down_rebin") 
				   )->Clone( 
				    ("MC_PDFsysdown_ybin"+std::to_string(i)).c_str() 
					     )
				  );
    
    ratios_PDFdown[i]=(TH1D*) spectra[i]->Clone(("MC_PDFsysdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_PDFdown[i]->Divide(mcspectra_PDFdown[i]);
    ratios_PDFdown[i]->SetMarkerSize(0);  ratios_PDFdown[i]->SetMarkerColor(kBlack);   ratios_PDFdown[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFdown[i]->SetLineColor(kMagenta);    ratios_PDFdown[i]->SetLineWidth(1);    

    //NP SYSTEMATICS, USE THY HIST NOT TOY MC ANYMORE
    std::string NPsysfilepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_SYST_file_array[3] +ETABIN_TAG_array[i]+ ".root";//also has JEC systematics
    TFile* NPsysfile=TFile::Open(( NPsysfilepath).c_str(), "READ");

    mcspectra_NPup[i] =  (TH1D*)(
				(
				 (TH1D*)NPsysfile->Get("NLO_CT14_NLO_NPsysup_R04_jtpt") 
				 )->Clone( 
					  ("MC_NPsysup_ybin"+std::to_string(i)).c_str() 
					   )
				 );
    //mcspectra_NPup[i]->Scale(1./1000.);//!!!TEMPORARY -- scaling for units reasons only -- TEMPORARY!!!//
    
    ratios_NPup[i]=(TH1D*) spectra[i]->Clone(("MC_NPsysup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_NPup[i]->Divide(mcspectra_NPup[i]);
    ratios_NPup[i]->SetMarkerSize(0);  ratios_NPup[i]->SetMarkerColor(kBlack);   ratios_NPup[i]->SetMarkerStyle(kFullCircle);
    ratios_NPup[i]->SetLineColor(kCyan);    ratios_NPup[i]->SetLineWidth(1);    

    mcspectra_NPdown[i] =  (TH1D*)(
				(
				 (TH1D*)NPsysfile->Get("NLO_CT14_NLO_NPsysdown_R04_jtpt") 
				 )->Clone( 
					  ("MC_NPsysdown_ybin"+std::to_string(i)).c_str() 
					   )
				 );
    //mcspectra_NPdown[i]->Scale(1./1000.);//!!!TEMPORARY -- scaling for units reasons only -- TEMPORARY!!!//
    
    ratios_NPdown[i]=(TH1D*) spectra[i]->Clone(("MC_NPsysdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_NPdown[i]->Divide(mcspectra_NPdown[i]);
    ratios_NPdown[i]->SetMarkerSize(0);  ratios_NPdown[i]->SetMarkerColor(kBlack);   ratios_NPdown[i]->SetMarkerStyle(kFullCircle);
    ratios_NPdown[i]->SetLineColor(kCyan);    ratios_NPdown[i]->SetLineWidth(1);    


    //JER SYSTEMATICS: REQUIRES SEPERATE FILE
    std::string JERsysfilepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_SYST_file_array[1] +ETABIN_TAG_array[i]+ ".root";//also has JEC systematics
    TFile* JERsysfile=TFile::Open(( JERsysfilepath).c_str(), "READ");
    spectra_JERup[i] =  (TH1D*)(
				(
				 (TH1D*)JERsysfile->Get("ppData_BayesUnf_JERsysup_Spectra") 
				 )->Clone( 
					  ("Data_unf_JERsysup_ybin"+std::to_string(i)).c_str() 
					   )
				);
    
    ratios_JERup[i]=(TH1D*) spectra_JERup[i]->Clone(("Data_JERsysup_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERup[i]->Divide(mcspectra[i]);
    ratios_JERup[i]->SetMarkerSize(0);  ratios_JERup[i]->SetMarkerColor(kBlack);   ratios_JERup[i]->SetMarkerStyle(kFullCircle);
    ratios_JERup[i]->SetLineColor(kGreen);    ratios_JERup[i]->SetLineWidth(1);    


    spectra_JERdown[i] =  (TH1D*)(
				  (
				   (TH1D*)JERsysfile->Get("ppData_BayesUnf_JERsysdown_Spectra") 
				   )->Clone( 
					    ("Data_unf_JERsysdown_ybin"+std::to_string(i)).c_str() 
					     )
				  );
    
    
    ratios_JERdown[i]=(TH1D*) spectra_JERdown[i]->Clone(("Data_JERsysdown_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERdown[i]->Divide(mcspectra[i]);
    ratios_JERdown[i]->SetMarkerSize(0);  ratios_JERdown[i]->SetMarkerColor(kBlack);   ratios_JERdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JERdown[i]->SetLineColor(kGreen);    ratios_JERdown[i]->SetLineWidth(1);    
    
    
    //TOTAL UNC, ALL UNC
    ratios_totaluncup[i]=(TH1D*)ratios[i]->Clone(("Data_MC_totaluncup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncup[i]->Reset("MICES");
    std::cout<<"making data/MC total upper uncertainty for all sources"<<std::endl;
    makeTotSystUncRatio("up", ratios[i] , ratios_statunc[i],
			( (std::vector<TH1*>)
			{ ratios_JERdown[i], ratios_JECup[i],
			    ratios_PDFdown[i],  ratios_NPdown[i] }),
			ratios_totaluncup[i]);
    //return;
    ratios_totaluncup[i]->SetMarkerSize(0);  ratios_totaluncup[i]->SetMarkerColor(kBlack);   ratios_totaluncup[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncup[i]->SetLineColor(kBlack);    ratios_totaluncup[i]->SetLineWidth(1);    
    
    
    ratios_totaluncdown[i]=(TH1D*)ratios[i]->Clone(("Data_MC_totaluncdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncdown[i]->Reset("MICES");
    std::cout<<"making data/MC total lower uncertainty for all sources"<<std::endl;
    makeTotSystUncRatio("down", ratios[i] , ratios_statunc[i],
			( (std::vector<TH1*>)
			{ ratios_JERup[i], ratios_JECdown[i],
			    ratios_PDFup[i],  ratios_NPup[i] }),
			ratios_totaluncdown[i]);
    ratios_totaluncdown[i]->SetMarkerSize(0);  ratios_totaluncdown[i]->SetMarkerColor(kBlack);   ratios_totaluncdown[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncdown[i]->SetLineColor(kBlack);    ratios_totaluncdown[i]->SetLineWidth(1);    
    

    
    //TOTAL DATA UNC
    ratios_totaldatauncup[i]=(TH1D*)ratios[i]->Clone(("Data_MC_totalDataOnlyuncup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaldatauncup[i]->Reset("MICES");
    std::cout<<"making data/MC total upper uncertainty for data sources"<<std::endl;
    makeTotSystUncRatio("up", ratios[i] , ratios_datastatunc[i],
			( (std::vector<TH1*>)
			{ ratios_JERdown[i], ratios_JECup[i]}),
			ratios_totaldatauncup[i]);
    ratios_totaldatauncup[i]->SetMarkerSize(0);  ratios_totaldatauncup[i]->SetMarkerColor(kBlack);   ratios_totaldatauncup[i]->SetMarkerStyle(kFullCircle);
    ratios_totaldatauncup[i]->SetLineColor(kRed);    ratios_totaldatauncup[i]->SetLineWidth(1);    
    
    
    ratios_totaldatauncdown[i]=(TH1D*)ratios[i]->Clone(("Data_MC_totalDataOnlyuncdown_ratio_ybin"+std::to_string(i)).c_str());
    std::cout<<"making data/MC total lower uncertainty for data sources"<<std::endl;
    ratios_totaldatauncdown[i]->Reset("MICES");
    makeTotSystUncRatio("down", ratios[i] , ratios_datastatunc[i],
			( (std::vector<TH1*>)
			{ ratios_JERup[i], ratios_JECdown[i]}),
			ratios_totaldatauncdown[i]);
    ratios_totaldatauncdown[i]->SetMarkerSize(0);  ratios_totaldatauncdown[i]->SetMarkerColor(kBlack);   ratios_totaldatauncdown[i]->SetMarkerStyle(kFullCircle);
    ratios_totaldatauncdown[i]->SetLineColor(kRed);    ratios_totaldatauncdown[i]->SetLineWidth(1);    

    //TOTAL MC UNC
    ratios_totalMCuncup[i]=(TH1D*)ratios[i]->Clone(("Data_MC_totalMCOnlyuncup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totalMCuncup[i]->Reset("MICES");
    std::cout<<"making data/MC total upper uncertainty for MC sources"<<std::endl;
    makeTotSystUncRatio("up", ratios[i] , ratios_MCstatunc[i],
			( (std::vector<TH1*>)
			{ ratios_PDFdown[i], ratios_NPdown[i]}),
			ratios_totalMCuncup[i]);
    ratios_totalMCuncup[i]->SetMarkerSize(0);  ratios_totalMCuncup[i]->SetMarkerColor(kBlack);   ratios_totalMCuncup[i]->SetMarkerStyle(kFullCircle);
    ratios_totalMCuncup[i]->SetLineColor(kMagenta);    ratios_totalMCuncup[i]->SetLineWidth(1);    
    
    
    ratios_totalMCuncdown[i]=(TH1D*)ratios[i]->Clone(("Data_MC_totalMCOnlyuncdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totalMCuncdown[i]->Reset("MICES");
    std::cout<<"making data/MC total lower uncertainty for MC sources"<<std::endl;
    makeTotSystUncRatio("down", ratios[i] , ratios_MCstatunc[i],
			( (std::vector<TH1*>)
			{ ratios_PDFup[i], ratios_NPup[i]}),
			ratios_totalMCuncdown[i]);
    ratios_totalMCuncdown[i]->SetMarkerSize(0);  ratios_totalMCuncdown[i]->SetMarkerColor(kBlack);   ratios_totalMCuncdown[i]->SetMarkerStyle(kFullCircle);
    ratios_totalMCuncdown[i]->SetLineColor(kMagenta);    ratios_totalMCuncdown[i]->SetLineWidth(1);    

    
  }
  
  
  
  //this works fine because first pt bin of all the ratios are the same
  TH1D* lumisysterr=(TH1D*)ratios[3]->Clone("lumierr");
  lumisysterr->Reset("ICES");
  //  std::cout<<"lumisysterr low edge bin 1="<<lumisysterr->GetBinLowEdge(1)<<std::endl;
  //  std::cout<<"lumisysterr width bin 1="<<lumisysterr->GetBinWidth(1)<<std::endl;
  //  std::cout<<"lumisysterr nbins="<<lumisysterr->GetNbinsX()<<std::endl;
  lumisysterr->SetBinContent(1, 1.);
  lumisysterr->SetBinError(1, .023);
  styleLumiErrHist(lumisysterr);
  std::string name="";
  if(mode=="")
    name ="NLOunfdata_SMPInclJetXsec_ratio";
  else
    name ="NLOunfdata_SMPInclJetXsec_"+mode+"_ratio";
  TCanvas* canv=makeSMPRatioCanvas(name);
  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){


    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][ ");    

    one     ->Draw();       
    
    if(mode=="totUnc"){
      
      ratios_totaldatauncup[i]->Draw("HIST ][ SAME");    
      ratios_totaldatauncdown[i]->Draw("HIST ][ SAME");    

      ratios_totalMCuncup[i]->Draw("HIST ][ SAME");    
      ratios_totalMCuncdown[i]->Draw("HIST ][ SAME");    
      
      ratios_totaluncup[i]->Draw("HIST ][ SAME");    
      ratios_totaluncdown[i]->Draw("HIST ][ SAME");    
    }
    else if(mode=="datatotUnc"){
      ratios_totaldatauncup[i]  ->SetLineColor(kBlack);
      ratios_totaldatauncdown[i]->SetLineColor(kBlack);

      ratios_totaldatauncup[i]->Draw("HIST ][ SAME");    
      ratios_totaldatauncdown[i]->Draw("HIST ][ SAME");    

      ratios_datastatunc[i]->Draw("HIST E ][ SAME");

      ratios_JERdown[i]->Draw("HIST ][ SAME");
      ratios_JERup[i]->Draw("HIST ][ SAME");
      ratios_JECdown[i]->Draw("HIST ][ SAME");
      ratios_JECup[i]->Draw("HIST ][ SAME");

    }
    else if(mode=="NLOtotUnc"){

      ratios_totalMCuncup[i]  ->SetLineColor(kBlack);
      ratios_totalMCuncdown[i]->SetLineColor(kBlack);

      ratios_totalMCuncup[i]->Draw("HIST ][ SAME");    
      ratios_totalMCuncdown[i]->Draw("HIST ][ SAME");    

      ratios_MCstatunc[i]->Draw("HIST E ][ SAME");

      ratios_NPdown[i]->Draw("HIST ][ SAME");
      ratios_NPup[i]->Draw("HIST ][ SAME");
      ratios_PDFdown[i]->Draw("HIST ][ SAME");
      ratios_PDFup[i]->Draw("HIST ][ SAME");

    }
    else{
      ratios_statunc[i]->Draw("HIST E ][ SAME");    
      ratios_PDFup[i]->Draw("HIST ][ SAME");    
      ratios_PDFdown[i]->Draw("HIST ][ SAME");    
      ratios_NPup[i]->Draw("HIST ][ SAME");    
      ratios_NPdown[i]->Draw("HIST ][ SAME");    
      ratios_JECup[i]->Draw("HIST ][ SAME");    
      ratios_JECdown[i]->Draw("HIST ][ SAME");    
      ratios_JERup[i]->Draw("HIST ][ SAME");    
      ratios_JERdown[i]->Draw("HIST ][ SAME");         
    }
    
    lumisysterr->Draw("HIST  E2  ][ SAME");
    ratios[i]->Draw("HIST E ][ SAME");    
    
    
    
    
    if(i==0){
      TLegend* leg0=makeLegend( 0.51, 0.72, 0.89, 0.89);
      leg0->AddEntry(ratios[i],"NLO #otimes NP Unfolded Data","lp");
      leg0->AddEntry(lumisysterr,"Lumi. Unc., #pm 2.3%","lepf");//just f--> annoying border on the legend entry , lepf w/ 0 line width, 0 marker color alpha -->no annoying border
      leg0->Draw();
    }
    else if(i==1){
      TLegend* leg=NULL;
      if(     mode=="totUnc"    )leg=makeLegend(0.54, 0.71, 0.89, 0.88);//good dimensions for 3 in a legend
      else if(mode=="datatotUnc")leg=makeLegend(0.54, 0.65, 0.89, 0.88);
      else if(mode=="NLOtotUnc" )leg=makeLegend(0.54, 0.65, 0.89, 0.88);
      else                       leg=makeLegend(0.54, 0.60, 0.89, 0.88);
      if(mode=="totUnc"){
	leg->AddEntry(ratios_totaldatauncup[i],"Data Stat. #oplus Sys. Unc.","l");
	leg->AddEntry(ratios_totalMCuncup[i],"Thy. Stat. #oplus Sys. Unc.","l");
	leg->AddEntry(ratios_totaluncup[i],"Data #oplus Thy. Unc.","l");	
      }
      else if(mode=="datatotUnc"){
	leg->AddEntry(ratios_JECup[i],"JEC Unc.","l");
	leg->AddEntry(ratios_JERup[i],"JER Unc.","l");
	leg->AddEntry(ratios_datastatunc[i],"Data Stat. Unc.","le");
	leg->AddEntry(ratios_totaldatauncup[i],"Data Stat. #oplus Sys. Unc.","l");
      }
      else if(mode=="NLOtotUnc"){
	leg->AddEntry(ratios_PDFup[i],"6P Scale Unc.","l");
	leg->AddEntry(ratios_NPup[i],"NPC Unc.","l");
	leg->AddEntry(ratios_MCstatunc[i],"Thy Stat. Unc.","le");
	leg->AddEntry(ratios_totalMCuncup[i],"Thy Stat. #oplus Sys. Unc.","l");
      }
      else{      
	leg->AddEntry(ratios_JECup[i],"JEC Unc.","l");
	leg->AddEntry(ratios_JERup[i],"JER Unc.","l");
	leg->AddEntry(ratios_PDFup[i],"6P Scale Unc.","l");
	leg->AddEntry(ratios_NPup[i],"NPC Unc.","l");
	leg->AddEntry(ratios_statunc[i],"Data #oplus Thy Stat. Unc.","le");
      }
      leg->Draw();
    }
    
    TPaveText* desc=NULL;
    if     (i==0)desc=makePaveText( 0.15, 0.67, 0.45, 0.88);
    else if(i==1)desc=makePaveText( 0.15, 0.63, 0.45, 0.88);
    else    desc=makePaveText( 0.15, 0.74, 0.45, 0.88);
    desc->AddText(etabin_strs[i].c_str());
    std::string ptrange=ptcuts_lo;
    ptrange+=std::to_string( (int)xhi)+" GeV";
    desc->AddText(ptrange.c_str());
    if(i==0)desc->AddText(jettype.c_str());
    else if(i==1){
      if(      nlothyfile.find("murmufHTp")!=std::string::npos)
	desc->AddText(scalechoice_murmufHTp.c_str());
      else if( nlothyfile.find("murmufpt1")!=std::string::npos)
	desc->AddText(scalechoice_murmufpt1.c_str());
      else if( nlothyfile.find("murmufpt" )!=std::string::npos)
	desc->AddText(scalechoice_murmufpt .c_str());
    }
    desc->Draw();
        
    SMPtitle->Draw();  
    
  }
  
  
  //makeSMPInclJetXsec_NLOunfdata_ratios
  saveCanv(outdir, canv, fout);

  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();
    spectra_JERup[i]->Delete();
    spectra_JERdown[i]->Delete();
    spectra_JECup[i]->Delete();
    spectra_JECdown[i]->Delete();
    
    mcspectra[i]->Delete();
    mcspectra_PDFup[i]->Delete();
    mcspectra_PDFdown[i]->Delete();
    mcspectra_NPup[i]->Delete();
    mcspectra_NPdown[i]->Delete();

    ratios[i]->Delete();		     
    ratios_statunc[i]->Delete();	     
    ratios_JECup[i]->Delete();	     
    ratios_JECdown[i]->Delete();	     
    ratios_JERup[i]->Delete();	     
    ratios_JERdown[i]->Delete();	     
    ratios_PDFup[i]->Delete();	     
    ratios_PDFdown[i]->Delete();	     
    ratios_NPup[i]->Delete();	     
    ratios_NPdown[i]->Delete();	     
                                         
    ratios_totaluncup[i]->Delete();	     
    ratios_totaluncdown[i]->Delete();    
    ratios_MCstatunc[i]->Delete();	     
    ratios_totalMCuncup[i]->Delete();    
    ratios_totalMCuncdown[i]->Delete();  
    ratios_datastatunc[i]->Delete();     
    ratios_totaldatauncup[i]->Delete();  
    ratios_totaldatauncdown[i]->Delete();

  }
  //canv->Delete();
  
  return;
}
