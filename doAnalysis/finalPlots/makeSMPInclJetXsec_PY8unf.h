void  makeSMPInclJetXsec_PY8unfdata (std::string outdir, TFile* fout=NULL);//FULL RECO PY8 unf, truth v. unf data
void  makeSMPInclJetXsec_PY8unfdata_ratios (std::string outdir, TFile* fout=NULL);//FULL RECO PY8 unf, truth v. unf data, ratios
void  makeSMPInclJetXsec_PY8unfdatasysterr_ratios (std::string outdir, TFile* fout=NULL);//FULL RECO PY8 unf, sys errs only
void  makeSMPInclJetXsec_PY8unfdata_wdatameas (std::string outdir, TFile* fout=NULL);//RECO data v. unf data
void  makeSMPInclJetXsec_PY8unfdata_wdatameas_ratios (std::string outdir, TFile* fout=NULL);//RECO data v. unf data, ratios
void  makeSMPInclJetXsec_PY8unfrespmat_onePadOneEta (std::string outdir, TFile* fout=NULL);



//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_PY8unfdata (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_PY8unfdata"<<std::endl;  

  const int netabins=PY8_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }

  TH1D* spectra[netabins]={};
  TH1D* mcspectra[netabins]={};
  int powten=netabins-1;
  float maxy=-1., miny=100000000.;//global min/maxy
  
  //first get the plots, scale accordingly, get the min/max y's
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
    spectra[i]->Scale(1000.);//nb-->pb
    spectra[i]->Scale(pow(10,(float)powten));   

    mcspectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("MC_truth") 
			   )->Clone( 
				    ("MC_truth_ybin"+std::to_string(i)).c_str() 
				     )
			  );        //have to clone or else memory leak risk
    mcspectra[i]->Scale(1000.);//nb-->pb
    mcspectra[i]->Scale(pow(10,(float)powten));   

    
    if(maxy<spectra[i]->GetMaximum())      maxy=spectra[i]->GetMaximum();
    //if(miny>spectra[i]->GetMinimum())      miny=spectra[i]->GetMinimum();
    float spectra_i_min=getnonzeromin((TH1*)spectra[i]);
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


  mcspectra[0]->SetMarkerSize(0);
  mcspectra[1]->SetMarkerSize(0);
  mcspectra[2]->SetMarkerSize(0);
  mcspectra[3]->SetMarkerSize(0);
  mcspectra[0]->SetLineColor(kBlack);	
  mcspectra[1]->SetLineColor(kBlack);	
  mcspectra[2]->SetLineColor(kBlack);	
  mcspectra[3]->SetLineColor(kBlack);	
  
  //first hist to be drawn, so this gets the max/min/labels/titles set up
  spectra[0]->SetMaximum(maxy*10.);
  spectra[0]->SetMinimum(miny/5.);  
  setHistLabels((TH1D*)spectra[0]);

  float xhi=spectra[0]->GetBinLowEdge(spectra[0]->GetNbinsX())+spectra[0]->GetBinWidth(spectra[0]->GetNbinsX());
  std::string ptrange=ptcuts_lo+std::to_string( (int)xhi)+" GeV";


  TLegend* leg=makeLegend();
  leg->SetHeader( "RECO PY8 Unfolded Data   ");
  
  TLegend* mcleg=makeLegend(0.52, 0.72, 0.88, 0.84);
  //mcleg->SetHeader( jettype.c_str(),"C" );
  mcleg->AddEntry((TObject*)0, ptrange.c_str(), "");
  mcleg->AddEntry((TObject*)0, jettype.c_str(), "");
  mcleg->AddEntry(mcspectra[0], "PYTHIA8 CUETP8M1", "l");
  
  TCanvas* canv=makeSMPSpectraCanvas("PY8unfdata_SMPInclJetXsec");
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
    
    mcspectra[i]->Draw("HIST E SAME");
    
  }
  
  leg->Draw();
  mcleg->Draw();
  
  TPaveText* SMPtitle=makePrelimPaveTextTitle();
  SMPtitle->Draw();  

  //makeSMPInclJetXsec_PY8unfdata
  saveCanv(outdir, canv, fout);
  
  for(int i=0; i<netabins;i++){
    spectra[i]->Delete();
    mcspectra[i]->Delete();
  }

  
  return;
}













//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_PY8unfdata_ratios (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_PY8unfdata_ratios"<<std::endl;
  
  const int netabins=PY8_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }

  TH1D* mcspectra[netabins]={};

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

  TH1D* ratios_totaluncup[netabins]={};	     
  TH1D* ratios_totaluncdown[netabins]={};    

  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
cout<<"0"<<endl;	  
    std::string filepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_unf") 
			   )->Clone( 
				    ("Data_unf_ybin"+std::to_string(i)).c_str() 
				     )
			  );
cout<<"1"<<endl;
    mcspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)file->Get("MC_truth") 
			     )->Clone( 
				      ("MC_truth_ybin"+std::to_string(i)).c_str() 
				       )
			    );        
cout<<"2"<<endl;
    spectra_JECup[i] =  (TH1D*)(
				(
			   (TH1D*)file->Get("Data_unf_JECsysup") 
			   )->Clone( 
				    ("Data_unf_JECsysup_ybin"+std::to_string(i)).c_str() 
				     )
			  );
cout<<"3"<<endl;
    spectra_JECdown[i] =  (TH1D*)(
				(
				 (TH1D*)file->Get("Data_unf_JECsysdown") 
			   )->Clone( 
				    ("Data_unf_JECsysdown_ybin"+std::to_string(i)).c_str() 
				     )
			  );
cout<<"4"<<endl;

if(doJERsys){
    std::string JERsysfilepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_SYST_file_array[1] +ETABIN_TAG_array[i]+ ".root";//also has JEC systematics
    TFile* JERsysfile=TFile::Open((JERsysfilepath).c_str(),"READ");
	cout<<"JERsysfile = "<<JERsysfilepath<<endl;
    spectra_JERup[i] =  (TH1D*)(
				( //TYPO!!! JEC SHOULD BE JER!!! FIX ME!!!
				 (TH1D*)JERsysfile->Get("Data_unf_JERsysup") 
			   )->Clone( 
				    ("Data_unf_JERsysup_ybin"+std::to_string(i)).c_str() 
				     )
			  );
cout<<"5"<<endl;
    spectra_JERdown[i] =  (TH1D*)(
				(
			   (TH1D*)JERsysfile->Get("Data_unf_JERsysdown") 
			   )->Clone( 
				    ("Data_unf_JERsysdown_ybin"+std::to_string(i)).c_str() 
				     )
			  );
			  cout<<"JERsys Run"<<endl;
}

    
    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(mcspectra[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.4);    ratios[i]->SetMaximum(1.6);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to PYTHIA8");
cout<<"DATA STAT"<<endl;
    //DATA STAT UNC
    ratios_statunc[i]=(TH1D*) spectra[i]->Clone(("Data_MC_StatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_statunc[i]->Divide(mcspectra[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    
    
cout<<"JEC SYS"<<endl;
    //JEC SYS
    ratios_JECup[i]=(TH1D*) spectra_JECup[i]->Clone(("Data_unf_JECsysup_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECup[i]->Divide(mcspectra[i]);
    ratios_JECup[i]->SetMarkerSize(0);  ratios_JECup[i]->SetMarkerColor(kBlack);   ratios_JECup[i]->SetMarkerStyle(kFullCircle);
    ratios_JECup[i]->SetLineColor(kRed);        ratios_JECup[i]->SetLineWidth(1);    
    
    ratios_JECdown[i]=(TH1D*) spectra_JECdown[i]->Clone(("Data_unf_JECsysdown_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECdown[i]->Divide(mcspectra[i]);
    ratios_JECdown[i]->SetMarkerSize(0);  ratios_JECdown[i]->SetMarkerColor(kBlack);   ratios_JECdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JECdown[i]->SetLineColor(kRed);        ratios_JECdown[i]->SetLineWidth(1);    

if(doJERsys){
cout<<"JER SYS"<<endl;
    //JER SYS
    ratios_JERup[i]=(TH1D*) spectra_JERup[i]->Clone(("Data_unf_JERsysup_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERup[i]->Divide(mcspectra[i]);
    ratios_JERup[i]->SetMarkerSize(0);  ratios_JERup[i]->SetMarkerColor(kBlack);   ratios_JERup[i]->SetMarkerStyle(kFullCircle);
    ratios_JERup[i]->SetLineColor(kGreen);        ratios_JERup[i]->SetLineWidth(1);    
    
    ratios_JERdown[i]=(TH1D*) spectra_JERdown[i]->Clone(("Data_unf_JERsysdown_MC_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERdown[i]->Divide(mcspectra[i]);
    ratios_JERdown[i]->SetMarkerSize(0);  ratios_JERdown[i]->SetMarkerColor(kBlack);   ratios_JERdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JERdown[i]->SetLineColor(kGreen);        ratios_JERdown[i]->SetLineWidth(1);    
}

cout<<"TOTAL UNC"<<endl;
    //TOTAL UNC, ALL UNC
    ratios_totaluncup[i]=(TH1D*)ratios[i]->Clone(("Data_MC_totaluncup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncup[i]->Reset("MICES");
    std::cout<<"making data/MC total upper uncertainty for all sources"<<std::endl;
    makeTotSystUncRatio("up", ratios[i] , ratios_statunc[i],
			( (std::vector<TH1*>)
	//		{ ratios_JERdown[i], 
			ratios_JECup[i]
	//		    }
			  ),
			ratios_totaluncup[i]);
    //return;
    ratios_totaluncup[i]->SetMarkerSize(0);  ratios_totaluncup[i]->SetMarkerColor(kBlack);   ratios_totaluncup[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncup[i]->SetLineColor(kBlack);    ratios_totaluncup[i]->SetLineWidth(1);    
    
    
    ratios_totaluncdown[i]=(TH1D*)ratios[i]->Clone(("Data_MC_totaluncdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncdown[i]->Reset("MICES");
    std::cout<<"making data/MC total lower uncertainty for all sources"<<std::endl;
    makeTotSystUncRatio("down", ratios[i] , ratios_statunc[i],
			( (std::vector<TH1*>)
	//		{ ratios_JERup[i],
			ratios_JECdown[i]
	//		    }
			  ),
			ratios_totaluncdown[i]);
    ratios_totaluncdown[i]->SetMarkerSize(0);  ratios_totaluncdown[i]->SetMarkerColor(kBlack);   ratios_totaluncdown[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncdown[i]->SetLineColor(kBlack);    ratios_totaluncdown[i]->SetLineWidth(1);    
    
  }
  
  
  
  //this works fine because first pt bin of all the ratios are the same
  TH1D* lumisysterr=(TH1D*)ratios[3]->Clone("lumierr");
  lumisysterr->Reset("ICES");
  std::cout<<"lumisysterr low edge bin 1="<<lumisysterr->GetBinLowEdge(1)<<std::endl;
  std::cout<<"lumisysterr width bin 1="<<lumisysterr->GetBinWidth(1)<<std::endl;
  std::cout<<"lumisysterr nbins="<<lumisysterr->GetNbinsX()<<std::endl;

  lumisysterr->SetBinContent(1, 1.);
  lumisysterr->SetBinError(1, .023);
  styleLumiErrHist(lumisysterr);
  TCanvas* canv=makeSMPRatioCanvas("PY8unfdata_SMPInclJetXsec_ratio");

  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){

    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    

    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][");    
    one     ->Draw();       
    ratios_statunc[i]->Draw("HIST E ][ SAME");    
    ratios_JECup[i]->Draw("HIST ][ SAME");    
    ratios_JECdown[i]->Draw("HIST ][ SAME");    

if(doJERsys){ 
	ratios_JERup[i]->Draw("HIST ][ SAME");    
    ratios_JERdown[i]->Draw("HIST ][ SAME");    
	}
	
    ratios_totaluncup[i]->Draw("HIST ][ SAME");
    ratios_totaluncdown[i]->Draw("HIST ][ SAME");
    lumisysterr->Draw("HIST  E2  ][ SAME");
    ratios[i]->Draw("HIST E ][ SAME");    
    
    
    
    
    
    if(i==0){
      TLegend* leg=makeLegend(0.61, 0.66, 0.87, 0.88);
      leg->AddEntry(ratios[i],"PY8 Unfolded Data","lp");
      leg->AddEntry(ratios_statunc[i],"Data #oplus MC Stat. Unc.","le");
      leg->AddEntry(ratios_JECup[i],"JEC Syst. Unc.","l");
	  
if(doJERsys){     
	 leg->AddEntry(ratios_JERup[i],"JER Syst. Unc.","l");
}

      leg->AddEntry(ratios_totaluncup[i],"Stat #oplus Syst. Unc.","l");
      leg->AddEntry(lumisysterr,"Lumi. Unc., #pm 2.3%","lepf");
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
  
  //makeSMPInclJetXsec_PY8unfdata_ratios
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    mcspectra[i]->Delete();
    
    spectra[i]->Delete();
    spectra_JERup[i]  ->Delete();
    spectra_JERdown[i]->Delete();
    spectra_JECup[i]  ->Delete();
    spectra_JECdown[i]->Delete();
    
    ratios[i]->Delete();
    ratios_statunc[i]->Delete();
if(doJERsys){    
	ratios_JERup[i]  ->Delete();
    ratios_JERdown[i]->Delete();
}
	ratios_JECup[i]  ->Delete();
    ratios_JECdown[i]->Delete();
    ratios_totaluncup[i]  ->Delete();
    ratios_totaluncdown[i]->Delete();
  }  

  return;
}












//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_PY8unfdatasysterr_ratios (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_PY8unfdatasysterr_ratios"<<std::endl;
const bool doJERsys=false;
  const int netabins=PY8_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }

  TH1D* spectra[netabins]={};
  TH1D* spectra_JECup[netabins]={};
  TH1D* spectra_JECdown[netabins]={};

if(doJERsys){  
	cout<<"I'm being naughty and doing JERsys"<<endl;
  TH1D* spectra_JERup[netabins]={};
  TH1D* spectra_JERdown[netabins]={};
  TH1D* ratios_JERup[netabins]={};
  TH1D* ratios_JERdown[netabins]={};
}

  TH1D* ratios[netabins]={};
  TH1D* ratios_statunc[netabins]={};
  TH1D* ratios_JECup[netabins]={};
  TH1D* ratios_JECdown[netabins]={};
  
  
  
  TH1D* ratios_totaluncUP[netabins]={};
  TH1D* ratios_totaluncDOWN[netabins]={};
  
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
    
    spectra_JECup[i] =  (TH1D*)(
				(
				 (TH1D*)file->Get("Data_unf_JECsysup") 
				 )->Clone( 
					  ("Data_unf_JECsysup_ybin"+std::to_string(i)).c_str() 
					   )
				);
    
    spectra_JECdown[i] =  (TH1D*)(
				  (
				   (TH1D*)file->Get("Data_unf_JECsysdown") 
				   )->Clone( 
					    ("Data_unf_JECsysdown_ybin"+std::to_string(i)).c_str() 
					     )
				  );
if(doJERsys){
    std::string JERsysfilepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_SYST_file_array[1] +ETABIN_TAG_array[i]+ ".root";//also has JEC systematics
    TFile* JERsysfile=TFile::Open((JERsysfilepath).c_str(),"READ");
    
    
    spectra_JERup[i] =  (TH1D*)(
				( //TYPO!!! JEC SHOULD BE JER!!! FIX ME!!!
				 (TH1D*)JERsysfile->Get("JERsys/Data_unf_JERsysup") 
				  )->Clone( 
				    ("Data_unf_JERsysup_ybin"+std::to_string(i)).c_str() 
					    )
				);
    
    spectra_JERdown[i] =  (TH1D*)(
				  (
				   (TH1D*)JERsysfile->Get("JERsys/Data_unf_JERsysdown") 
				   )->Clone( 
					    ("Data_unf_JERsysdown_ybin"+std::to_string(i)).c_str() 
					     )
				  );
}

    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(spectra[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(0);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColorAlpha(kBlack,0);    
    ratios[i]->SetMinimum(0.6);    ratios[i]->SetMaximum(1.4);
    setRatioHistLabels((TH1D*)ratios[i], "PYTHIA8 Unf. Data Unc.");

    //DATA STAT UNC
    ratios_statunc[i]=(TH1D*) spectra[i]->Clone(("Data_StatUnc_ratio_ybin"+std::to_string(i)).c_str());
    for(int j=1; j<=spectra[i]->GetNbinsX();j++)
      spectra[i]->SetBinError(j,0.0000000000000000000000000000001);
    ratios_statunc[i]->Divide(spectra[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    
    
    
    ratios_JECup[i]=(TH1D*) spectra_JECup[i]->Clone(("Data_unf_JECsysup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECup[i]->Divide(spectra[i]);
    ratios_JECup[i]->SetMarkerSize(0);  ratios_JECup[i]->SetMarkerColor(kBlack);   ratios_JECup[i]->SetMarkerStyle(kFullCircle);
    ratios_JECup[i]->SetLineColor(kRed);        ratios_JECup[i]->SetLineWidth(1);    
    
    ratios_JECdown[i]=(TH1D*) spectra_JECdown[i]->Clone(("Data_unf_JECsysdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECdown[i]->Divide(spectra[i]);
    ratios_JECdown[i]->SetMarkerSize(0);  ratios_JECdown[i]->SetMarkerColor(kBlack);   ratios_JECdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JECdown[i]->SetLineColor(kRed);        ratios_JECdown[i]->SetLineWidth(1);    

if(doJERsys){
    ratios_JERup[i]=(TH1D*) spectra_JERup[i]->Clone(("Data_unf_JERsysup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERup[i]->Divide(spectra[i]);
    ratios_JERup[i]->SetMarkerSize(0);  ratios_JERup[i]->SetMarkerColor(kBlack);   ratios_JERup[i]->SetMarkerStyle(kFullCircle);
    ratios_JERup[i]->SetLineColor(kGreen);        ratios_JERup[i]->SetLineWidth(1);    
    
    ratios_JERdown[i]=(TH1D*) spectra_JERdown[i]->Clone(("Data_unf_JERsysdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERdown[i]->Divide(spectra[i]);
    ratios_JERdown[i]->SetMarkerSize(0);  ratios_JERdown[i]->SetMarkerColor(kBlack);   ratios_JERdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JERdown[i]->SetLineColor(kGreen);        ratios_JERdown[i]->SetLineWidth(1);    


    ////TOTAL UNC (STAT + SYST)
    ratios_totaluncUP[i]=(TH1D*) ratios_statunc[i]->Clone(("Data_totalUncUP_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncUP[i]->Reset("MICES");
    ratios_totaluncUP[i]->SetMarkerSize(0);  ratios_totaluncUP[i]->SetMarkerColor(kBlack);   ratios_totaluncUP[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncUP[i]->SetLineColor(kBlack);    ratios_totaluncUP[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("up",
		       ratios_statunc[i],
		       ((std::vector<TH1*>){ratios_JERup[i],ratios_JECup[i],ratios_statunc[i]}) ,
		       ratios_totaluncUP[i]);

    ratios_totaluncDOWN[i]=(TH1D*) ratios_statunc[i]->Clone(("Data_totalUncDOWN_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncDOWN[i]->Reset("MICES");
    ratios_totaluncDOWN[i]->SetMarkerSize(0);  ratios_totaluncDOWN[i]->SetMarkerColor(kBlack);   ratios_totaluncDOWN[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncDOWN[i]->SetLineColor(kBlack);    ratios_totaluncDOWN[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("down",
		       ratios_statunc[i],
		       ((std::vector<TH1*>){ratios_JERdown[i],ratios_JECdown[i],ratios_statunc[i]}) ,
		       ratios_totaluncDOWN[i]);
  }
  
 else( 
  
      ////TOTAL UNC (STAT + SYST)
    ratios_totaluncUP[i]=(TH1D*) ratios_statunc[i]->Clone(("Data_totalUncUP_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncUP[i]->Reset("MICES");
    ratios_totaluncUP[i]->SetMarkerSize(0);  ratios_totaluncUP[i]->SetMarkerColor(kBlack);   ratios_totaluncUP[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncUP[i]->SetLineColor(kBlack);    ratios_totaluncUP[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("up",
		       ratios_statunc[i],
		       ((std::vector<TH1*>){ratios_JECup[i],ratios_statunc[i]}) ,
		       ratios_totaluncUP[i]);

    ratios_totaluncDOWN[i]=(TH1D*) ratios_statunc[i]->Clone(("Data_totalUncDOWN_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncDOWN[i]->Reset("MICES");
    ratios_totaluncDOWN[i]->SetMarkerSize(0);  ratios_totaluncDOWN[i]->SetMarkerColor(kBlack);   ratios_totaluncDOWN[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncDOWN[i]->SetLineColor(kBlack);    ratios_totaluncDOWN[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("down",
		       ratios_statunc[i],
		       ((std::vector<TH1*>){ratios_JECdown[i],ratios_statunc[i]}) ,
		       ratios_totaluncDOWN[i]);
  }
  
  
}
  
  
  //this works fine because first pt bin of all the ratios are the same
  TH1D* lumisysterr=(TH1D*)ratios[3]->Clone("lumierr");
  lumisysterr->Reset("ICES");
  std::cout<<"lumisysterr low edge bin 1="<<lumisysterr->GetBinLowEdge(1)<<std::endl;
  std::cout<<"lumisysterr width bin 1="<<lumisysterr->GetBinWidth(1)<<std::endl;
  std::cout<<"lumisysterr nbins="<<lumisysterr->GetNbinsX()<<std::endl;

  lumisysterr->SetBinContent(1, 1.);
  lumisysterr->SetBinError(1, .023);
  styleLumiErrHist(lumisysterr);
  TCanvas* canv=makeSMPRatioCanvas("PY8unfdatasysterr_SMPInclJetXsec_ratio");

  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){

    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    

    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][");    
    one     ->Draw();       
    ratios_statunc[i]->Draw("HIST E ][ SAME");    
    ratios_JECup[i]->Draw("HIST ][ SAME");    
    ratios_JECdown[i]->Draw("HIST ][ SAME");    
if(doJERsys){    
	ratios_JERup[i]->Draw("HIST ][ SAME");    
    ratios_JERdown[i]->Draw("HIST ][ SAME");    
}
	ratios_totaluncUP[i]->Draw("HIST ][ SAME");    
    ratios_totaluncDOWN[i]->Draw("HIST ][ SAME");    
    lumisysterr->Draw("HIST  E2  ][ SAME");
    ratios[i]->Draw("HIST E ][ SAME");    
    

    


    if(i==0){
      TLegend* leg=makeLegend(0.61, 0.68, 0.87, 0.87);
      //leg->AddEntry(ratios[i],"PY8 Unfolded Data","lp");
      leg->AddEntry(ratios_statunc[i],"Data Stat. Unc.","le");
      leg->AddEntry(ratios_JECup[i],"JEC Syst. Unc.","l");
if(doJERsys){      leg->AddEntry(ratios_JERup[i],"JER Syst. Unc.","l"); }
      leg->AddEntry(ratios_totaluncUP[i],"Stat. #oplus Syst. Unc.","l");
      leg->AddEntry(lumisysterr,"Lumi. Unc., #pm 2.3%","lepf");
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
  
  //makeSMPInclJetXsec_PY8unfdatasysterr_ratios
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();
if(doJERsys){
    spectra_JERup[i]  ->Delete();
    spectra_JERdown[i]->Delete();
}	
    spectra_JECup[i]  ->Delete();
    spectra_JECdown[i]->Delete();
    
    ratios[i]->Delete();
    ratios_statunc[i]->Delete();
if(doJERsys){    
	ratios_JERup[i]  ->Delete();
    ratios_JERdown[i]->Delete();
}
	ratios_JECup[i]  ->Delete();
    ratios_JECdown[i]->Delete();
    ratios_totaluncUP[i]->Delete();
    ratios_totaluncDOWN[i]->Delete();

  }  
  
  return;
}







//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_PY8unfdata_wdatameas (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_PY8unfdata_wdatameas"<<std::endl;

  
  const int netabins=PY8_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* spectra[netabins]={};
  TH1D* measspectra[netabins]={};
  int powten=netabins-1;
  float maxy=-1., miny=100000000.;//global min/maxy
  
  //first get the plots, scale accordingly, get the min/max y's
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
    spectra[i]->Scale(1000.);//nb-->pb
    spectra[i]->Scale(pow(10,(float)powten));   

    measspectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_meas") 
			   )->Clone( 
				    ("Data_meas_ybin"+std::to_string(i)).c_str() 
				     )
			      );        //have to clone or else memory leak risk
    measspectra[i]->Scale(1000.);//nb-->pb
    measspectra[i]->Scale(pow(10,(float)powten));   
    
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


  measspectra[0]->SetMarkerSize(2);  measspectra[0]->SetMarkerColor(kRed    -1);       measspectra[0]->SetMarkerStyle(kOpenCircle);
  measspectra[1]->SetMarkerSize(2);  measspectra[1]->SetMarkerColor(kGreen  -1);     measspectra[1]->SetMarkerStyle(kOpenSquare);
  measspectra[2]->SetMarkerSize(2);  measspectra[2]->SetMarkerColor(kBlue   -1);      measspectra[2]->SetMarkerStyle(kOpenTriangleUp);
  measspectra[3]->SetMarkerSize(2);  measspectra[3]->SetMarkerColor(kMagenta-1);   measspectra[3]->SetMarkerStyle(kOpenTriangleDown); 
  measspectra[0]->SetLineColor(kRed    -1);      
  measspectra[1]->SetLineColor(kGreen  -1);    
  measspectra[2]->SetLineColor(kBlue   -1);     
  measspectra[3]->SetLineColor(kMagenta-1);  



  
  //first hist to be drawn, so this gets the max/min/labels/titles set up
  spectra[0]->SetMaximum(maxy*10.);
  spectra[0]->SetMinimum(miny/5.);  
  setHistLabels((TH1D*)spectra[0]);

  float xhi=spectra[0]->GetBinLowEdge(spectra[0]->GetNbinsX())+spectra[0]->GetBinWidth(spectra[0]->GetNbinsX());
  std::string ptrange=ptcuts_lo+std::to_string( (int)xhi)+" GeV";


  TLegend* leg=makeLegend();
  leg->SetHeader( "RECO PY8 Unfolded Data   ");
  
  TPaveText* jetdesc=makePaveText(.64,.81,.87,.88);
  jetdesc->AddText(ptrange.c_str());
  jetdesc->AddText(jettype.c_str());
  
  TLegend* dataleg=makeLegend(0.64, 0.60, 0.90, 0.80);
  dataleg->SetHeader("Measured Data         ");
  
  
  TCanvas* canv=makeSMPSpectraCanvas("PY8unfdata_SMPInclJetXsec_wdatameas");
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

    dataleg->AddEntry( measspectra[i], 
		       (legstr).c_str() ,"lp");        
    powten--;
    
    measspectra[i]->Draw("HIST E SAME");
    
  }
  
  leg->Draw();
  dataleg->Draw();
  jetdesc->Draw();
  
  TPaveText* SMPtitle=makePrelimPaveTextTitle();
  SMPtitle->Draw();  

  //makeSMPInclJetXsec_PY8unfdata_wdatameas
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    spectra[i]->Delete();
    measspectra[i]->Delete();
  }

  
  return;
}


//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_PY8unfdata_wdatameas_ratios (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_PY8unfdata_wdatameas_ratios"<<std::endl;

  
  const int netabins=PY8_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* measspectra[netabins]={};

  TH1D* spectra[netabins]={};
if(doJERsys){ 
 TH1D* spectra_JERup[netabins]={};
  TH1D* spectra_JERdown[netabins]={};  
}
  TH1D* ratios[netabins]={};
  TH1D* ratios_statunc[netabins]={};
  if(doJERsys){
  TH1D* ratios_JERup[netabins]={};
  TH1D* ratios_JERdown[netabins]={};
}
  
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

    measspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)file->Get("Data_meas") 
			     )->Clone( 
				      ("Data_meas_ybin"+std::to_string(i)).c_str() 
				       )
			    );        

if(doJERsys){
    std::string JERsysfilepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_SYST_file_array[1] +ETABIN_TAG_array[i]+ ".root";//also has JEC systematics
    TFile* JERsysfile=TFile::Open((JERsysfilepath).c_str(),"READ");


    spectra_JERup[i] =  (TH1D*)(
				( //TYPO!!! JEC SHOULD BE JER!!! FIX ME!!!
			   (TH1D*)JERsysfile->Get("JERsys/Data_unf_JERsysup") 
			   )->Clone( 
				    ("Data_unf_JERsysup_ybin"+std::to_string(i)).c_str() 
				     )
			  );

    spectra_JERdown[i] =  (TH1D*)(
				(
			   (TH1D*)JERsysfile->Get("JERsys/Data_unf_JERsysdown") 
			   )->Clone( 
				    ("Data_unf_JERsysdown_ybin"+std::to_string(i)).c_str() 
				     )
			  );
}
    //for(int j=1; j<=measspectra[i]->GetNbinsX();j++)//errors due to PDF will be illustrated by 6 point scale var error. leave inherent PDF errors out of it.
    //measspectra[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root]
    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_Meas_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(measspectra[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.4);    ratios[i]->SetMaximum(1.6);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to Measured Data");
    
    //DATA STAT UNC
    ratios_statunc[i]=(TH1D*) spectra[i]->Clone(("Data_Meas_StatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_statunc[i]->Divide(measspectra[i]);    
    calculateCorrRatioErrs((TH1*)ratios_statunc[i],(TH1*)spectra[i],(TH1*)measspectra[i],0.5);//still unsure if this is what i should do, or if i should just scale stat err down by sqrt(2)
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    

if(doJERsys){
    //DATA JER UNC
    ratios_JERup[i]=(TH1D*) spectra_JERup[i]->Clone(("Data_Meas_JERsysupUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERup[i]->Divide(measspectra[i]);    
    ratios_JERup[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_JERup[i]->SetLineColor(kGreen);    
    
    ratios_JERdown[i]=(TH1D*) spectra_JERdown[i]->Clone(("Data_Meas_JERsysdownUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERdown[i]->Divide(measspectra[i]);    
    ratios_JERdown[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_JERdown[i]->SetLineColor(kGreen);    
}
	
  }
  
  
if(doJERsys){
  TCanvas* canv=makeSMPRatioCanvas("PY8unfdata_SMPInclJetXsec_wdatameas_ratio");
  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][");    
    ratios_JERup[i]->Draw("HIST ][ SAME");    
    ratios_JERdown[i]->Draw("HIST ][ SAME");    
    ratios_statunc[i]->Draw("HIST E ][ SAME");    
    
    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    TLine* one     =makeTLine(xlo, 1. , xhi, 1.);   
    one     ->Draw();       
    //TLine* downline     =makeTLine(xlo, 0.7 , xhi, 0.7);   
    //downline     ->Draw();       
    //TLine* upline     =makeTLine(xlo, 1.3 , xhi, 1.3);   
    //upline     ->Draw();       
    
    if(i==0){
      TLegend* leg=makeLegend(0.61, 0.68, 0.87, 0.87);
      //leg->SetHeader()
      leg->AddEntry(ratios[i],"PY8 Unfolded Data","lp");
      leg->AddEntry(ratios_statunc[i],"Stat. Unc.","le");
      leg->AddEntry(ratios_JERup[i],"JER Unc.","le");
      leg->Draw(); }
    
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

  
  //makeSMPInclJetXsec_PY8unfdata_wdatameas_ratios
  saveCanv(outdir, canv, fout);
      
  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();
    spectra_JERup[i]  ->Delete();
    spectra_JERdown[i]->Delete();
    
    ratios[i]->Delete();
    ratios_statunc[i]->Delete();
    ratios_JERup[i]  ->Delete();
    ratios_JERdown[i]->Delete();

  }  

}
  
  return;
}







//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_PY8unfrespmat_onePadOneEta (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_PY8unfrespmat_onePadOneEta"<<std::endl;
  
  const int netabins=PY8_UNFDIR_DATA_Nfiles;
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH2D* respmatrix[netabins]={};
  float zmax=-1.;
  float zmin=99999999999999999999.;
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= PY8_UNFDIR_DATA + PY8_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    respmatrix[i] =  (TH2D*)(
			(
			 (TH2D*)file->Get("MC_mat_rebin") 
			 )->Clone( 
				  ("MC_respmat_rebin_ybin"+std::to_string(i)).c_str() 
				   )
			    );
    float th2max=respmatrix[i]->GetMaximum();
    float th2min=getnonzeromin((TH2*)respmatrix[i]);
    if(th2max>zmax)zmax=th2max;
    if(th2min<zmin)zmin=th2min;
    
  }
  
  TCanvas* canv=makeSMPRatioCanvas("PY8unfrespmat_onePadOneEta");

  TPaveText* SMPtitle=makeSimPaveTextTitleRatio();
  bool dologx=true, dology=true, dologz=true;
  for(int i=0; i<netabins; i++){
      
    canv->cd(i+1)->SetLogx(dologx);//maybe set to 1?
    canv->cd(i+1)->SetLogy(dology);//maybe set to 1?
    canv->cd(i+1)->SetLogz(dologz);//maybe set to 1?
    canv->cd(i+1);
    
    setHistLabels((TH2D*)respmatrix[i], "GEN Jet p_{T} [GeV]","RECO Jet p_{T} [GeV]");//,"Covariance [pb^{-2}]");
    
    if(dologx)respmatrix[i]->GetXaxis()->SetNoExponent(true);
    if(dologx)respmatrix[i]->GetXaxis()->SetMoreLogLabels(true);
    if(dology)respmatrix[i]->GetYaxis()->SetNoExponent(true);
    if(dology)respmatrix[i]->GetYaxis()->SetMoreLogLabels(true);
    respmatrix[i]->SetAxisRange(zmin*.9,zmax*1.1, "Z");
    respmatrix[i]->Draw("COLZ");    

    TPaveText* desc=makePaveText( 0.38, 0.90, 0.62, 1.00);
    desc->AddText(etabin_strs[i].c_str());
    desc->AddText(jettype.c_str());
    desc->Draw();
    SMPtitle->Draw();
    
  }
  
  //makeSMPInclJetXsec_PY8unfrespmat_onePadOneEta
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    respmatrix[i]->Delete();
  }
  
  
  return;
}



