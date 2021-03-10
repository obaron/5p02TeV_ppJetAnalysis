void  makeSMPInclJetXsec_NLOunfdata (std::string outdir, TFile* fout=NULL);//SMEARED NLO unf, truth v. unf data

void  makeSMPInclJetXsec_NLOunfdata_targPDF_ratios (std::string outdir, TFile* fout=NULL, std::string mode="", 
						    std::string targPDF="", std::string scalechoice="", std::string order="");//SMEARED NLO unf, truth v. unf data, ratios

//void  makeSMPInclJetXsec_allOunfdata_ratios (std::string outdir, TFile* fout=NULL,  int etabin=0);//SMEARED NLO unf, truth v. unf data, ratios
void  makeSMPInclJetXsec_allOunfdata_ratios (std::string outdir, TFile* fout=NULL,  std::string targPDF="", std::string scalechoice="", int etabin=0);//SMEARED NLO unf, truth v. unf data, ratios
void  makeSMPInclJetXsec_NLOunfdatasysterr_ratios (std::string outdir, TFile* fout=NULL);//SMEARED NLO unf, syst errs only

void  makeSMPInclJetXsec_NLOunfdata_wdatameas (std::string outdir, TFile* fout=NULL);//RECO data v. unf data
void  makeSMPInclJetXsec_NLOunfdata_wdatameas_ratios (std::string outdir, TFile* fout=NULL);//RECO data v. unf data, ratios

void  makeSMPInclJetXsec_NLOunfrespmat_onePadOneEta (std::string outdir, TFile* fout=NULL);




//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOunfdata (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_NLOunfdata"<<std::endl;

  
  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
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
    std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    spectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_unf") 
			   )->Clone( 
				    ("Data_NLOunf_ybin"+std::to_string(i)).c_str() 
				     )
			  );
    spectra[i]->Scale(1000.);//nb-->pb
    spectra[i]->Scale(pow(10,(float)powten));   
    
        //i want to grab fnlo spectra from the fnlo files. i will need to rebin them to the unf data binning.
    std::vector<double> bins;
    for(int j=1; j<=spectra[i]->GetNbinsX();j++){
      bins.push_back(spectra[i]->GetBinLowEdge(j));
      if(j==spectra[i]->GetNbinsX()){//case where every bin is filled; we'll miss the highest bin edge if this isn't here.
	bins.push_back(spectra[i]->GetBinLowEdge(j)+
		       spectra[i]->GetBinWidth(j) );	}
    }    
    
    mcspectra[i]=  (TH1D*)make_fNLOSpectra( (std::string) "CT14nnlo", (std::string) "murmufHTp_v4", (std::string) "1",
					    (int) i, (int) 0,
					    (bool) true, (std::vector<double>) bins, 
					    (bool) true, "");
    mcspectra[i]->Scale(1000.);//for cosmetic scaling to work out right
    mcspectra[i]->Scale(pow(10,(float)powten));   
    

    
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
  leg->SetHeader( "NLO #otimes NP Unfolded Data   ","C" );
  
  TLegend* mcleg=makeLegend(0.52, 0.72, 0.88, 0.84);
  //mcleg->SetHeader( jettype.c_str(),"C" );
  mcleg->AddEntry((TObject*)0, ptrange.c_str(), "");
  mcleg->AddEntry((TObject*)0, jettype.c_str(), "");
  //mcleg->AddEntry(mcspectra[0], "CT14nnlo NLO #otimes HERWIG EE5C NPCs", "l");
  mcleg->AddEntry(mcspectra[0], "CT14nnlo NLO #otimes NPCs", "l");
  
  TCanvas* canv=makeSMPSpectraCanvas("NLOunfdata_SMPInclJetXsec");
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
  
  //makeSMPInclJetXsec_NLOunfdata
  saveCanv(outdir, canv, fout);

  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();
    mcspectra[i]->Delete();
  }  


  return;
}









//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOunfdata_targPDF_ratios (std::string outdir, TFile* fout, std::string mode, std::string targPDF, std::string scalechoice, std::string order){
  std::cout<<"running makeSMPInclJetXsec_NLOunfdata_targPDF_ratios!"<<std::endl;
  std::cout<<"mode="<<mode<<", targPDF="<<targPDF<<", scalechoice="<<scalechoice<<", order="<<order<<std::endl;
  
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
  TH1D* mcspectra_MUup[netabins]={};
  TH1D* mcspectra_MUdown[netabins]={};
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
  TH1D* ratios_MUup[netabins]={};	     
  TH1D* ratios_MUdown[netabins]={};	     
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

  std::string orderint="";
  if(     order=="LO"  )orderint="2";
  else if(order=="NLO" )orderint="1";
  else if(order=="NNLO")orderint="0";
  
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
    //spectra[i]->Print("base");
    
    //i want to grab fnlo spectra from the fnlo files. i will need to rebin them to the unf data binning.
    std::vector<double> bins;
    for(int j=1; j<=spectra[i]->GetNbinsX();j++){
      bins.push_back(spectra[i]->GetBinLowEdge(j));
      if(j==spectra[i]->GetNbinsX()){//case where every bin is filled; we'll miss the highest bin edge if this isn't here.
	bins.push_back(spectra[i]->GetBinLowEdge(j)+
		       spectra[i]->GetBinWidth(j) );	}
    }    
   
     mcspectra[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) orderint,
					  (int) i, (int) 0,
					  (bool) true, (std::vector<double>) bins, 
					  (bool) true, "");

    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_"+order+"_"+targPDF+"_"+scalechoice+"_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(mcspectra[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.55);    ratios[i]->SetMaximum(1.6);
    std::string targPDF_nous=replace_underscores(targPDF);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to "+targPDF_nous+" "+order+" #otimes NPCs");
    
    
    //DATA #OPLUS MC STAT UNC
    ratios_statunc[i]=(TH1D*) spectra[i]->Clone(("Data_MC_StatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_statunc[i]->Divide(mcspectra[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    

    // MC STAT UNC ONLY (acheived by setting data clone stat unc to 0, then dividing by mc w/ stat unc)
    ratios_MCstatunc[i]=(TH1D*) spectra[i]->Clone(("Data_MC_MCOnlyStatUnc_ratio_ybin"+std::to_string(i)).c_str());
    for(int j=1; j<=ratios_MCstatunc[i]->GetNbinsX();j++)
      ratios_MCstatunc[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc        
    ratios_MCstatunc[i]->Divide(mcspectra[i]);
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
    ratios_JECdown[i]->SetMarkerSize(0);  ratios_JECdown[i]->SetMarkerColor(kBlack);   ratios_JECdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JECdown[i]->SetLineColor(kRed);    ratios_JECdown[i]->SetLineWidth(1);    
    
    // SCALE SYSTEMATICS
    mcspectra_MUup[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) orderint,
						(int) i, (int) 9,
						(bool) true, (std::vector<double>) bins, 
						(bool) true, "");       
    ratios_MUup[i]=(TH1D*) spectra[i]->Clone((targPDF+"_MUsysup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_MUup[i]->Divide(mcspectra_MUup[i]);
    ratios_MUup[i]->SetMarkerSize(0);  ratios_MUup[i]->SetMarkerColor(kBlack);   ratios_MUup[i]->SetMarkerStyle(kFullCircle);
    ratios_MUup[i]->SetLineColor(kMagenta);    ratios_MUup[i]->SetLineWidth(1);    
    
    
    mcspectra_MUdown[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) orderint,
						  (int) i, (int) 8,
						  (bool) true, (std::vector<double>) bins, 
						  (bool) true, "");
    ratios_MUdown[i]=(TH1D*) spectra[i]->Clone((targPDF+"_MUsysdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_MUdown[i]->Divide(mcspectra_MUdown[i]);
    ratios_MUdown[i]->SetMarkerSize(0);  ratios_MUdown[i]->SetMarkerColor(kBlack);   ratios_MUdown[i]->SetMarkerStyle(kFullCircle);
    ratios_MUdown[i]->SetLineColor(kMagenta);    ratios_MUdown[i]->SetLineWidth(1);    


    // PDF SYSTEMATICS
    mcspectra_PDFup[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) orderint,
						(int) i, (int) 2,
						(bool) true, (std::vector<double>) bins, 
						(bool) true, "");       
    ratios_PDFup[i]=(TH1D*) spectra[i]->Clone((targPDF+"_PDFsysup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_PDFup[i]->Divide(mcspectra_PDFup[i]);
    ratios_PDFup[i]->SetMarkerSize(0);  ratios_PDFup[i]->SetMarkerColor(kBlack);   ratios_PDFup[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFup[i]->SetLineColor(kYellow+2);    ratios_PDFup[i]->SetLineWidth(1);    
    
    
    mcspectra_PDFdown[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) orderint,
						  (int) i, (int) 1,
						  (bool) true, (std::vector<double>) bins, 
						  (bool) true, "");
    ratios_PDFdown[i]=(TH1D*) spectra[i]->Clone((targPDF+"_PDFsysdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_PDFdown[i]->Divide(mcspectra_PDFdown[i]);
    ratios_PDFdown[i]->SetMarkerSize(0);  ratios_PDFdown[i]->SetMarkerColor(kBlack);   ratios_PDFdown[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFdown[i]->SetLineColor(kYellow+2);    ratios_PDFdown[i]->SetLineWidth(1);    
    
    ////NP SYSTEMATICS, USE THY HIST NOT TOY MC ANYMORE
    mcspectra_NPup[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) orderint,
					       (int) i, (int) 0,
					       (bool) true, (std::vector<double>) bins, 
					       (bool) true, "up");
    ratios_NPup[i]=(TH1D*) spectra[i]->Clone(("MC_NPsysup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_NPup[i]->Divide(mcspectra_NPup[i]);
    ratios_NPup[i]->SetMarkerSize(0);  ratios_NPup[i]->SetMarkerColor(kBlack);   ratios_NPup[i]->SetMarkerStyle(kFullCircle);
    ratios_NPup[i]->SetLineColor(kCyan+2);    ratios_NPup[i]->SetLineWidth(1);    
    
    mcspectra_NPdown[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) orderint,
					       (int) i, (int) 0,
					       (bool) true, (std::vector<double>) bins, 
					       (bool) true, "down");
    
    ratios_NPdown[i]=(TH1D*) spectra[i]->Clone(("MC_NPsysdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_NPdown[i]->Divide(mcspectra_NPdown[i]);
    ratios_NPdown[i]->SetMarkerSize(0);  ratios_NPdown[i]->SetMarkerColor(kBlack);   ratios_NPdown[i]->SetMarkerStyle(kFullCircle);
    ratios_NPdown[i]->SetLineColor(kCyan+2);    ratios_NPdown[i]->SetLineWidth(1);    


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
			    ratios_MUdown[i],  ratios_NPdown[i], ratios_PDFdown[i] }),
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
			    ratios_MUup[i],  ratios_NPup[i], ratios_PDFup[i] }),
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
			{ ratios_MUdown[i], ratios_NPdown[i], ratios_PDFdown[i]}),
			ratios_totalMCuncup[i]);
    ratios_totalMCuncup[i]->SetMarkerSize(0);  ratios_totalMCuncup[i]->SetMarkerColor(kBlack);   ratios_totalMCuncup[i]->SetMarkerStyle(kFullCircle);
    ratios_totalMCuncup[i]->SetLineColor(kMagenta);    ratios_totalMCuncup[i]->SetLineWidth(1);    
    
    
    ratios_totalMCuncdown[i]=(TH1D*)ratios[i]->Clone(("Data_MC_totalMCOnlyuncdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totalMCuncdown[i]->Reset("MICES");
    std::cout<<"making data/MC total lower uncertainty for MC sources"<<std::endl;
    makeTotSystUncRatio("down", ratios[i] , ratios_MCstatunc[i],
			( (std::vector<TH1*>)
			{ ratios_MUup[i], ratios_NPup[i], ratios_PDFup[i]}),
			ratios_totalMCuncdown[i]);
    ratios_totalMCuncdown[i]->SetMarkerSize(0);  ratios_totalMCuncdown[i]->SetMarkerColor(kBlack);   ratios_totalMCuncdown[i]->SetMarkerStyle(kFullCircle);
    ratios_totalMCuncdown[i]->SetLineColor(kMagenta);    ratios_totalMCuncdown[i]->SetLineWidth(1);    
    
    
  }
  
  
  
  //this works fine because first pt bin of all the ratios are the same
  TH1D* lumisysterr=(TH1D*)ratios[3]->Clone("lumierr");
  lumisysterr->Reset("ICES");
  lumisysterr->SetBinContent(1, 1.);
  lumisysterr->SetBinError(1, .023);
  styleLumiErrHist(lumisysterr);
  std::string name="NLOunfdata_SMPInclJetXsec_"+targPDF+"_"+order+"_"+scalechoice;//+"_"+mode+"_ratio";
  if(mode=="")name+="_ratio";
  else name+="_"+mode+"_ratio";

 


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
      ratios_MUdown[i]->Draw("HIST ][ SAME");
      ratios_MUup[i]->Draw("HIST ][ SAME");
      ratios_PDFdown[i]->Draw("HIST ][ SAME");
      ratios_PDFup[i]->Draw("HIST ][ SAME");

    }
    else{
      ratios_statunc[i]->Draw("HIST E ][ SAME");    
      ratios_MUup[i]->Draw("HIST ][ SAME");    
      ratios_MUdown[i]->Draw("HIST ][ SAME");    
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
	leg->AddEntry(ratios_PDFup[i],"PDF Unc.","l");
	leg->AddEntry(ratios_MUup[i],"6P Scale Unc.","l");
	leg->AddEntry(ratios_NPup[i],"NPC Unc.","l");
	leg->AddEntry(ratios_MCstatunc[i],"Thy Stat. Unc.","le");
	leg->AddEntry(ratios_totalMCuncup[i],"Thy Stat. #oplus Sys. Unc.","l");
      }
      else{      
	leg->AddEntry(ratios_JECup[i],"JEC Unc.","l");
	leg->AddEntry(ratios_JERup[i],"JER Unc.","l");
	leg->AddEntry(ratios_PDFup[i],"PDF Unc.","l");
	leg->AddEntry(ratios_MUup[i],"6P Scale Unc.","l");
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
      if(      scalechoice.find("murmufHTp")!=std::string::npos)
	desc->AddText(scalechoice_murmufHTp.c_str());
      else if( scalechoice.find("murmufpt1")!=std::string::npos)
	desc->AddText(scalechoice_murmufpt1.c_str());
      else if( scalechoice.find("murmufpt" )!=std::string::npos)
	desc->AddText(scalechoice_murmufpt .c_str());
    }
    desc->Draw();
        
    SMPtitle->Draw();  
    
  }
  
  
  //makeSMPInclJetXsec_NLOunfdata_targPDF_ratios
  saveCanv(outdir, canv, fout);

  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();
    spectra_JERup[i]->Delete();
    spectra_JERdown[i]->Delete();
    spectra_JECup[i]->Delete();
    spectra_JECdown[i]->Delete();
    
    mcspectra[i]->Delete();
    mcspectra_MUup[i]->Delete();
    mcspectra_MUdown[i]->Delete();
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
    ratios_MUup[i]->Delete();	     
    ratios_MUdown[i]->Delete();	     
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


//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOunfdatasysterr_ratios (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_NLOunfdatasysterr_ratios"<<std::endl;

  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  

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
  TH1D* ratios_totaluncUP[netabins]={};	 
  TH1D* ratios_totaluncDOWN[netabins]={};
  
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


    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(spectra[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(0);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColorAlpha(kBlack, 0.);    
    setRatioHistLabels((TH1D*)ratios[i], "NLO #otimes NP Unfolded Data Unc.");
    ratios[i]->SetMinimum(0.6);    ratios[i]->SetMaximum(1.4);
    //ratios[i]->SetMinimum(0.5);    ratios[i]->SetMaximum(1.4);
    //ratios[i]->SetMinimum(-0.6);    ratios[i]->SetMaximum(0.6);
    //    ratios[i]->Scale(100.)
    //    ratios[i]->SetMinimum(-60.);    ratios[i]->SetMaximum(60.);
   

    //DATA STAT UNC
    ratios_statunc[i]=(TH1D*) spectra[i]->Clone(("Data_StatUnc_ratio_ybin"+std::to_string(i)).c_str());
    for(int j=1; j<=spectra[i]->GetNbinsX();j++)
      spectra[i]->SetBinError(j,1.e-30);//set this to *almost* zero or the marker wont draw, also so the errs are correctly calculated
    ratios_statunc[i]->Divide(spectra[i]);
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
    ratios_JECup[i]=(TH1D*) spectra_JECup[i]->Clone(("Data_JECsysup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECup[i]->Divide(spectra[i]);
    ratios_JECup[i]->SetMarkerSize(0);  ratios_JECup[i]->SetMarkerColor(kBlack);   ratios_JECup[i]->SetMarkerStyle(kFullCircle);
    ratios_JECup[i]->SetLineColor(kRed);    ratios_JECup[i]->SetLineWidth(1);    
    
    
    spectra_JECdown[i] =  (TH1D*)(
				  (
				   (TH1D*)file->Get("ppData_BayesUnf_JECsysdown_Spectra") 
				   )->Clone( 
					    ("Data_unf_JECsysdown_ybin"+std::to_string(i)).c_str() 
					     )
				  );
    ratios_JECdown[i]=(TH1D*) spectra_JECdown[i]->Clone(("Data_JECsysdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JECdown[i]->Divide(spectra[i]);
    ratios_JECdown[i]->SetMarkerSize(0);  ratios_JECdown[i]->SetMarkerColor(kBlack);   ratios_JECdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JECdown[i]->SetLineColor(kRed);    ratios_JECdown[i]->SetLineWidth(1);    
    


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
    
    ratios_JERup[i]=(TH1D*) spectra_JERup[i]->Clone(("Data_JERsysup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERup[i]->Divide(spectra[i]);
    ratios_JERup[i]->SetMarkerSize(0);  ratios_JERup[i]->SetMarkerColor(kBlack);   ratios_JERup[i]->SetMarkerStyle(kFullCircle);
    ratios_JERup[i]->SetLineColor(kGreen);    ratios_JERup[i]->SetLineWidth(1);    


    spectra_JERdown[i] =  (TH1D*)(
				  (
				   (TH1D*)JERsysfile->Get("ppData_BayesUnf_JERsysdown_Spectra") 
				   )->Clone( 
					    ("Data_unf_JERsysdown_ybin"+std::to_string(i)).c_str() 
					     )
				  );
    
    
    ratios_JERdown[i]=(TH1D*) spectra_JERdown[i]->Clone(("Data_JERsysdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_JERdown[i]->Divide(spectra[i]);
    ratios_JERdown[i]->SetMarkerSize(0);  ratios_JERdown[i]->SetMarkerColor(kBlack);   ratios_JERdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JERdown[i]->SetLineColor(kGreen);    ratios_JERdown[i]->SetLineWidth(1);    
    
    ////TOTAL UNC (STAT + SYST)
    ratios_totaluncUP[i]=(TH1D*) ratios_statunc[i]->Clone(("Data_totalUncUP_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncUP[i]->Reset("MICES");
    ratios_totaluncUP[i]->SetMarkerSize(0);  ratios_totaluncUP[i]->SetMarkerColor(kBlack);   ratios_totaluncUP[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncUP[i]->SetLineColor(kBlack);    ratios_totaluncUP[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("up",
			   ratios_statunc[i],
			   ((std::vector<TH1*>){ratios_JERdown[i],ratios_JECup[i]}) ,
			   ratios_totaluncUP[i]);

    ratios_totaluncDOWN[i]=(TH1D*) ratios_statunc[i]->Clone(("Data_totalUncDOWN_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncDOWN[i]->Reset("MICES");
    ratios_totaluncDOWN[i]->SetMarkerSize(0);  ratios_totaluncDOWN[i]->SetMarkerColor(kBlack);   ratios_totaluncDOWN[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncDOWN[i]->SetLineColor(kBlack);    ratios_totaluncDOWN[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("down",
		       ratios_statunc[i],
		       ((std::vector<TH1*>){ratios_JERup[i],ratios_JECdown[i]}) ,
		       ratios_totaluncDOWN[i]);
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
  TCanvas* canv=makeSMPRatioCanvas("NLOunfdatasysterr_SMPInclJetXsec_ratio");
  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){


    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    //TLine* one     =makeTLine(xlo, 1. , xhi, 1.);    
    TLine* one     =makeTLine(xlo, 0. , xhi, 0.);    
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][ ");    
    one     ->Draw();       
    ratios_statunc[i]->Draw("HIST E ][ SAME");    
    ratios_JECup[i]->Draw("HIST ][ SAME");    
    ratios_JECdown[i]->Draw("HIST ][ SAME");    
    ratios_JERup[i]->Draw("HIST ][ SAME");    
    ratios_JERdown[i]->Draw("HIST ][ SAME");    
    ratios_totaluncUP[i]->Draw("HIST ][ SAME");
    ratios_totaluncDOWN[i]->Draw("HIST ][ SAME");
    lumisysterr->Draw("HIST  E2  ][ SAME");
    ratios[i]->Draw("HIST E ][ SAME");    
    

    


    if(i==1){
      TLegend* leg=makeLegend(0.55, 0.65, 0.82, 0.88);
      //leg->SetHeader()
      //leg->AddEntry(ratios[i],"NLO #otimes NP Unfolded Data","lp");
      leg->AddEntry(ratios_JECup[i],"JEC Syst. Unc.","l");
      leg->AddEntry(ratios_JERup[i],"JER Syst. Unc.","l");
      leg->AddEntry(ratios_statunc[i],"Data Stat. Unc.","le");
      leg->AddEntry(ratios_totaluncUP[i],"Stat. #oplus Syst. Unc.","l");
      //leg->AddEntry(lumisysterr,"Lumi. Unc., #pm 2.3%","lepf");//just f--> annoying border on the legend entry , lepf w/ 0 line width, 0 marker color alpha -->no annoying border
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
  
  
  //makeSMPInclJetXsec_NLOunfdatasysterr_ratios
  saveCanv(outdir, canv, fout);

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
    ratios_totaluncUP[i]->Delete();	 
    ratios_totaluncDOWN[i]->Delete();
  }

  
  return;
}









//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_allOunfdata_ratios (std::string outdir, TFile* fout,  std::string targPDF, std::string scalechoice, int etabin){
  std::cout<<"running makeSMPInclJetXsec_allOunfdata_ratios for etabin="<<etabin<<std::endl;
  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(etabin>=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  std::string datafilepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[etabin] + ".root";//also has JEC systematics
  TFile* file=TFile::Open(( datafilepath).c_str(), "READ");

  //SPECTRA ONLY, NO SYST
  TH1D* spectra =  (TH1D*)(
			   (
			    (TH1D*)file->Get("Data_unf") 
			    )->Clone( 
				     ("Data_unf_ybin"+std::to_string(etabin)).c_str() 
				      )
			   );

  //gonna have to get the binning here and rebin the stuff from the fastnlo files respectively
  int nbins=spectra->GetNbinsX();
  std::vector<double> ptbinedges;
  for(int i=1;i<=nbins;i++)
    ptbinedges.push_back(spectra->GetBinLowEdge(i));
  ptbinedges.push_back(spectra->GetBinLowEdge(nbins)+spectra->GetBinWidth(nbins));
  
  //JEC SYSTEMATICS
  TH1D* spectra_JECup =  (TH1D*)( 
				 (
			       (TH1D*)file->Get("ppData_BayesUnf_JECsysup_Spectra") 
			       )->Clone( 
					("Data_unf_JECsysup_ybin"+std::to_string(etabin)).c_str() 
					 )
			      );
  
  TH1D* spectra_JECdown =  (TH1D*)(
				(
				 (TH1D*)file->Get("ppData_BayesUnf_JECsysdown_Spectra") 
				 )->Clone( 
					  ("Data_unf_JECsysdown_ybin"+std::to_string(etabin)).c_str() 
					   )
				);
  
  //JER SYSTEMATICS: REQUIRES SEPERATE FILE
  std::string JERsysfilepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_SYST_file_array[1] +ETABIN_TAG_array[etabin]+ ".root";//also has JEC systematics
  TFile* JERsysfile=TFile::Open(( JERsysfilepath).c_str(), "READ");
  
  //JER SYSTEMATICS
  TH1D* spectra_JERup =  (TH1D*)(
				 (
				  (TH1D*)JERsysfile->Get("ppData_BayesUnf_JERsysup_Spectra") 
				  )->Clone( 
					   ("Data_unf_JERsysup_ybin"+std::to_string(etabin)).c_str() 
					    )
				 );
  
  TH1D* spectra_JERdown =  (TH1D*)(
				   (
				    (TH1D*)JERsysfile->Get("ppData_BayesUnf_JERsysdown_Spectra") 
				    )->Clone( 
					     ("Data_unf_JERsysdown_ybin"+std::to_string(etabin)).c_str() 
					      )
				   );
  
  

  //FastNLO file from JOAO
  std::string thyfilepath= FNLO_DIR+nlothyfile+".root";
  TFile* thyfile=TFile::Open(( thyfilepath).c_str(), "READ");
  
  //3 for NNLO, NLO, and LO  
  TH1D* mcspectra[2]={};// Matrix Element Calculation of NNPDF; use for data comparisons   
  TH1D* mcspectra_MUup[2]={};								   
  TH1D* mcspectra_MUdown[2]={};							   
  TH1D* mcspectra_PDFup[2]={};								   
  TH1D* mcspectra_PDFdown[2]={};							   
  TH1D* mcspectra_NPup[2]={};								   
  TH1D* mcspectra_NPdown[2]={};								   
  	                                                                                   
  TH1D* ratios[2]={};									   
  TH1D* ratios_statunc[2]={};								   
  TH1D* ratios_JECup[2]={};								   
  TH1D* ratios_JECdown[2]={};								   
  TH1D* ratios_JERup[2]={};								   
  TH1D* ratios_JERdown[2]={};								   
  TH1D* ratios_MUup[2]={};								   
  TH1D* ratios_MUdown[2]={};								   
  TH1D* ratios_PDFup[2]={};								   
  TH1D* ratios_PDFdown[2]={};								   
  TH1D* ratios_NPup[2]={};								   
  TH1D* ratios_NPdown[2]={};                                                               


  TH1D* ratios_MCstatunc[2]={};	     
  TH1D* ratios_totalMCuncup[2]={};    
  TH1D* ratios_totalMCuncdown[2]={};  
  TH1D* ratios_datastatunc[2]={};     
  TH1D* ratios_totaldatauncup[2]={};  
  TH1D* ratios_totaldatauncdown[2]={};
  TH1D* ratios_totaluncup[2]={};	     
  TH1D* ratios_totaluncdown[2]={};    

  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  //  for(int i=0; i<3; i++){
  for(int i=0; i<2; i++){
    
    std::string Ostr;
    if(i==0)      Ostr="NNLO";
    else if(i==1) Ostr="NLO";
    else if(i==2) Ostr="LO";
    
    
    mcspectra[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, std::to_string(i),
					  (int) etabin, (int) 0,
					  (bool) true, (std::vector<double>) ptbinedges, 
					  (bool) true, "");
  
    //    //gonna leave this here, just in case, but LO isn't on this plot anymore. 
    //    if(i==2)   //want the LO stat unc set to 0 without setting the unf data stat unc to zero
    //      for(int j=1; j<=mcspectra[i]->GetNbinsX();j++)
    //	mcspectra[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root]
    
    //DATA+MC STAT UNC
    ratios_statunc[i]=(TH1D*) spectra->Clone(("Data_MC_StatUnc_"+Ostr+"_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_statunc[i]->Divide(mcspectra[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    

    // MC STAT UNC ONLY (acheived by setting data clone stat unc to 0, then dividing by mc w/ stat unc)
    ratios_MCstatunc[i]=(TH1D*) spectra->Clone(("Data_MC_"+Ostr+"MCOnlyStatUnc_ratio_ybin"+std::to_string(i)).c_str());
    for(int j=1; j<=ratios_MCstatunc[i]->GetNbinsX();j++)
      ratios_MCstatunc[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc        
    ratios_MCstatunc[i]->Divide(mcspectra[i]);
    ratios_MCstatunc[i]->SetMarkerSize(0);  ratios_MCstatunc[i]->SetMarkerColor(kBlack);   ratios_MCstatunc[i]->SetMarkerStyle(kFullCircle);
    ratios_MCstatunc[i]->SetLineColor(kGray+2);    
    
    
    for(int j=1; j<=mcspectra[i]->GetNbinsX();j++)//i dont want stat unc on anything else
      mcspectra[i]->SetBinError(j,1.e-30);
    
    // DATA STAT UNC ONLY (acheived by dividing cloned data hist w/ stat unc by mc w/o stat unc)
    ratios_datastatunc[i]=(TH1D*) spectra->Clone(("Data_MC_"+Ostr+"DataOnlyStatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_datastatunc[i]->Divide(mcspectra[i]);
    ratios_datastatunc[i]->SetMarkerSize(0);  ratios_MCstatunc[i]->SetMarkerColor(kBlack);   ratios_MCstatunc[i]->SetMarkerStyle(kFullCircle);
    ratios_datastatunc[i]->SetLineColor(kGray+2);    
    
    //RATIO VALUES
    ratios[i]=(TH1D*) spectra->Clone(("Data_"+Ostr+"_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios[i]->Divide(mcspectra[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.4);    ratios[i]->SetMaximum(1.6);

    std::string targPDF_nous=replace_underscores(targPDF);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to "+targPDF_nous+" #otimes NPCs");
    //setRatioHistLabels((TH1D*)ratios[i], "Ratio to CT14nnlo #otimes HERWIG EE5C");
    //setRatioHistLabels((TH1D*)ratios[i], "Ratio to CT14nnlo #otimes NPC");
    
    
    

    //JEC SYS UNC
    ratios_JECup[i]=(TH1D*) spectra_JECup->Clone(("Data_JECsysup_MC_"+Ostr+"_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_JECup[i]->Divide(mcspectra[i]);
    ratios_JECup[i]->SetMarkerSize(0);  ratios_JECup[i]->SetMarkerColor(kBlack);   ratios_JECup[i]->SetMarkerStyle(kFullCircle);
    ratios_JECup[i]->SetLineColor(kRed);    ratios_JECup[i]->SetLineWidth(1);    
    
    ratios_JECdown[i]=(TH1D*) spectra_JECdown->Clone(("Data_JECsysdown_MC_"+Ostr+"_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_JECdown[i]->Divide(mcspectra[i]);
    ratios_JECdown[i]->SetMarkerSize(0);  ratios_JECdown[i]->SetMarkerColor(kBlack);   ratios_JECdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JECdown[i]->SetLineColor(kRed);    ratios_JECdown[i]->SetLineWidth(1);    
    
    
    
    //6P SCALE UNC
    mcspectra_MUup[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, std::to_string(i),
					       (int) etabin, (int) 9,
					       (bool) true, (std::vector<double>) ptbinedges, 
					       (bool) true, "");       
    
    ratios_MUup[i]=(TH1D*) spectra->Clone(("MC_"+Ostr+"_MUsysup_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_MUup[i]->Divide(mcspectra_MUup[i]);
    ratios_MUup[i]->SetMarkerSize(0);          ratios_MUup[i]->SetMarkerColor(kBlack);   ratios_MUup[i]->SetMarkerStyle(kFullCircle);
    ratios_MUup[i]->SetLineColor(kMagenta);    ratios_MUup[i]->SetLineWidth(1);    
    
    
    mcspectra_MUdown[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, std::to_string(i),
						 (int) etabin, (int) 8,
						 (bool) true, (std::vector<double>) ptbinedges, 
						 (bool) true, "");       
    
    ratios_MUdown[i]=(TH1D*) spectra->Clone(("MC_"+Ostr+"_MUsysdown_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_MUdown[i]->Divide(mcspectra_MUdown[i]);
    ratios_MUdown[i]->SetMarkerSize(0);          ratios_MUdown[i]->SetMarkerColor(kBlack);   ratios_MUdown[i]->SetMarkerStyle(kFullCircle);
    ratios_MUdown[i]->SetLineColor(kMagenta);    ratios_MUdown[i]->SetLineWidth(1);    


    
    //JER SYS UNC
    ratios_JERup[i]=(TH1D*) spectra_JERup->Clone(("Data_JERsysup_MC_"+Ostr+"_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_JERup[i]->Divide(mcspectra[i]);
    ratios_JERup[i]->SetMarkerSize(0);  ratios_JERup[i]->SetMarkerColor(kBlack);   ratios_JERup[i]->SetMarkerStyle(kFullCircle);
    ratios_JERup[i]->SetLineColor(kGreen);    ratios_JERup[i]->SetLineWidth(1);    

    ratios_JERdown[i]=(TH1D*) spectra_JERdown->Clone(("Data_JERsysdown_MC_"+Ostr+"_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_JERdown[i]->Divide(mcspectra[i]);
    ratios_JERdown[i]->SetMarkerSize(0);  ratios_JERdown[i]->SetMarkerColor(kBlack);   ratios_JERdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JERdown[i]->SetLineColor(kGreen);    ratios_JERdown[i]->SetLineWidth(1);    
    
    //NP SYS UNC
    mcspectra_NPup[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, std::to_string(i),
					       (int) etabin, (int) 0,
					       (bool) true, (std::vector<double>) ptbinedges, 
					       (bool) true, "up");    
    ratios_NPup[i]=(TH1D*) spectra->Clone(("MC_"+Ostr+"_NPsysup_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_NPup[i]->Divide(mcspectra_NPup[i]);
    ratios_NPup[i]->SetMarkerSize(0);  ratios_NPup[i]->SetMarkerColor(kBlack);   ratios_NPup[i]->SetMarkerStyle(kFullCircle);
    ratios_NPup[i]->SetLineColor(kCyan);    ratios_NPup[i]->SetLineWidth(1);    
    
    
    mcspectra_NPdown[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, std::to_string(i),
						 (int) etabin, (int) 0,
						 (bool) true, (std::vector<double>) ptbinedges, 
						 (bool) true, "down");    
    ratios_NPdown[i]=(TH1D*) spectra->Clone(("MC_"+Ostr+"_NPsysdown_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_NPdown[i]->Divide(mcspectra_NPdown[i]);
    ratios_NPdown[i]->SetMarkerSize(0);  ratios_NPdown[i]->SetMarkerColor(kBlack);   ratios_NPdown[i]->SetMarkerStyle(kFullCircle);
    ratios_NPdown[i]->SetLineColor(kCyan);    ratios_NPdown[i]->SetLineWidth(1);    

    //PDF SYS UNC
    mcspectra_PDFup[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, std::to_string(i),
						(int) etabin, (int) 2,
						(bool) true, (std::vector<double>) ptbinedges, 
						(bool) true, "");           
    ratios_PDFup[i]=(TH1D*) spectra->Clone(("MC_"+Ostr+"_PDFsysup_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_PDFup[i]->Divide(mcspectra_PDFup[i]);
    ratios_PDFup[i]->SetMarkerSize(0);       ratios_PDFup[i]->SetMarkerColor(kBlack);   ratios_PDFup[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFup[i]->SetLineColor(kYellow+2);    ratios_PDFup[i]->SetLineWidth(1);    
    
    
    mcspectra_PDFdown[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, std::to_string(i),
						  (int) etabin, (int) 1,
						  (bool) true, (std::vector<double>) ptbinedges, 
						  (bool) true, "");           
    ratios_PDFdown[i]=(TH1D*) spectra->Clone(("MC_"+Ostr+"_PDFsysdown_ratio_ybin"+std::to_string(etabin)).c_str());
    ratios_PDFdown[i]->Divide(mcspectra_PDFdown[i]);
    ratios_PDFdown[i]->SetMarkerSize(0);  ratios_PDFdown[i]->SetMarkerColor(kBlack);   ratios_PDFdown[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFdown[i]->SetLineColor(kYellow+2);    ratios_PDFdown[i]->SetLineWidth(1);    


    //TOTAL MC UNC
    ratios_totalMCuncup[i]=(TH1D*)ratios[i]->Clone(("Data_MC_"+Ostr+"_totalMCOnlyuncup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totalMCuncup[i]->Reset("MICES");
    std::cout<<"making data/MC total upper uncertainty for "<<Ostr<<" MC sources"<<std::endl;
    makeTotSystUncRatio("up", ratios[i] , ratios_MCstatunc[i],
			( (std::vector<TH1*>)
			{ ratios_MUdown[i], ratios_NPdown[i], ratios_PDFdown[i]}),
			ratios_totalMCuncup[i]);
    ratios_totalMCuncup[i]->SetMarkerSize(0);  ratios_totalMCuncup[i]->SetMarkerColor(kBlack);   ratios_totalMCuncup[i]->SetMarkerStyle(kFullCircle);
    ratios_totalMCuncup[i]->SetLineColor(kMagenta);    ratios_totalMCuncup[i]->SetLineWidth(1);    
    
    
    ratios_totalMCuncdown[i]=(TH1D*)ratios[i]->Clone(("Data_MC_"+Ostr+"_totalMCOnlyuncdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totalMCuncdown[i]->Reset("MICES");
    std::cout<<"making data/MC total lower uncertainty for "<<Ostr<<" MC sources"<<std::endl;
    makeTotSystUncRatio("down", ratios[i] , ratios_MCstatunc[i],
			( (std::vector<TH1*>)
			{ ratios_MUup[i], ratios_NPup[i], ratios_PDFup[i]}),
			ratios_totalMCuncdown[i]);
    ratios_totalMCuncdown[i]->SetMarkerSize(0);  ratios_totalMCuncdown[i]->SetMarkerColor(kBlack);   ratios_totalMCuncdown[i]->SetMarkerStyle(kFullCircle);
    ratios_totalMCuncdown[i]->SetLineColor(kMagenta);    ratios_totalMCuncdown[i]->SetLineWidth(1);    

    //TOTAL DATA UNC
    ratios_totaldatauncup[i]=(TH1D*)ratios[i]->Clone(("Data_MC_"+Ostr+"_totalDataOnlyuncup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaldatauncup[i]->Reset("MICES");
    std::cout<<"making data/MC total upper uncertainty for data sources"<<std::endl;
    makeTotSystUncRatio("up", ratios[i] , ratios_datastatunc[i],
			( (std::vector<TH1*>)
			{ ratios_JERdown[i], ratios_JECup[i]}),
			ratios_totaldatauncup[i]);
    ratios_totaldatauncup[i]->SetMarkerSize(0);  ratios_totaldatauncup[i]->SetMarkerColor(kBlack);   ratios_totaldatauncup[i]->SetMarkerStyle(kFullCircle);
    ratios_totaldatauncup[i]->SetLineColor(kRed);    ratios_totaldatauncup[i]->SetLineWidth(1);    
    
    
    ratios_totaldatauncdown[i]=(TH1D*)ratios[i]->Clone(("Data_MC_"+Ostr+"_totalDataOnlyuncdown_ratio_ybin"+std::to_string(i)).c_str());
    std::cout<<"making data/MC total lower uncertainty for data sources"<<std::endl;
    ratios_totaldatauncdown[i]->Reset("MICES");
    makeTotSystUncRatio("down", ratios[i] , ratios_datastatunc[i],
			( (std::vector<TH1*>)
			{ ratios_JERup[i], ratios_JECdown[i]}),
			ratios_totaldatauncdown[i]);
    ratios_totaldatauncdown[i]->SetMarkerSize(0);  ratios_totaldatauncdown[i]->SetMarkerColor(kBlack);   ratios_totaldatauncdown[i]->SetMarkerStyle(kFullCircle);
    ratios_totaldatauncdown[i]->SetLineColor(kRed);    ratios_totaldatauncdown[i]->SetLineWidth(1);    
    
    
    //TOTAL UNC, ALL UNC
    ratios_totaluncup[i]=(TH1D*)ratios[i]->Clone(("Data_MC_"+Ostr+"_totaluncup_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncup[i]->Reset("MICES");
    std::cout<<"making data/MC total upper uncertainty for all sources"<<std::endl;
    makeTotSystUncRatio("up", ratios[i] , ratios_statunc[i],
			( (std::vector<TH1*>)
			{ ratios_JERdown[i], ratios_JECup[i],
			    ratios_MUdown[i],  ratios_NPdown[i], ratios_PDFdown[i] }),
			ratios_totaluncup[i]);
    //return;
    ratios_totaluncup[i]->SetMarkerSize(0);  ratios_totaluncup[i]->SetMarkerColor(kBlack);   ratios_totaluncup[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncup[i]->SetLineColor(kBlack);    ratios_totaluncup[i]->SetLineWidth(1);    
    
    
    ratios_totaluncdown[i]=(TH1D*)ratios[i]->Clone(("Data_MC_"+Ostr+"_totaluncdown_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncdown[i]->Reset("MICES");
    std::cout<<"making data/MC total lower uncertainty for all sources"<<std::endl;
    makeTotSystUncRatio("down", ratios[i] , ratios_statunc[i],
			( (std::vector<TH1*>)
			{ ratios_JERup[i], ratios_JECdown[i],
			    ratios_MUup[i],  ratios_NPup[i], ratios_PDFup[i] }),
			ratios_totaluncdown[i]);
    ratios_totaluncdown[i]->SetMarkerSize(0);  ratios_totaluncdown[i]->SetMarkerColor(kBlack);   ratios_totaluncdown[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncdown[i]->SetLineColor(kBlack);    ratios_totaluncdown[i]->SetLineWidth(1);        
    
  }
  
  
  
  //this works fine because first pt bin of all the ratios are the same
  TH1D* lumisysterr=(TH1D*)ratios[0]->Clone("lumierr");
  lumisysterr->Reset("ICES");
  //  std::cout<<"lumisysterr low edge bin 1="<<lumisysterr->GetBinLowEdge(1)<<std::endl;
  //  std::cout<<"lumisysterr width bin 1="<<lumisysterr->GetBinWidth(1)<<std::endl;
  //  std::cout<<"lumisysterr nbins="<<lumisysterr->GetNbinsX()<<std::endl;
  lumisysterr->SetBinContent(1, 1.);
  lumisysterr->SetBinError(1, .023);
  styleLumiErrHist(lumisysterr);

  ratios[0]->SetMinimum(0.3);
  ratios[0]->SetMaximum(3.3);
  
  
  
  TCanvas* canv=makeSMPRatioCanvas_allO("allOunfdata_SMPInclJetXsec_"+targPDF+"_"+scalechoice+"_ratio_ybin"+std::to_string(etabin));
  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<2; i++){
    
    //canv->cd(i+1);
    canv->cd();
    float vertshift=((float)(1-i));
    for(int bin=1; bin<=ratios[i]->GetNbinsX();bin++){
      ratios[i]        ->SetBinContent(bin,ratios[i]        ->GetBinContent(bin)+vertshift);
      ratios_statunc[i]->SetBinContent(bin,ratios_statunc[i]->GetBinContent(bin)+vertshift);//this looks this way so that LO is about 1, NLO is about 2, and NNLO is about 3
      ratios_PDFup[i]  ->SetBinContent(bin,ratios_PDFup[i]  ->GetBinContent(bin)+vertshift);
      ratios_PDFdown[i]->SetBinContent(bin,ratios_PDFdown[i]->GetBinContent(bin)+vertshift);
      ratios_MUup[i]  ->SetBinContent(bin,ratios_MUup[i]  ->GetBinContent(bin)+vertshift);
      ratios_MUdown[i]->SetBinContent(bin,ratios_MUdown[i]->GetBinContent(bin)+vertshift);
      ratios_NPup[i]   ->SetBinContent(bin,ratios_NPup[i]  ->GetBinContent(bin)+vertshift);
      ratios_NPdown[i] ->SetBinContent(bin,ratios_NPdown[i]->GetBinContent(bin)+vertshift);
      ratios_totalMCuncup[i]->SetBinContent(bin,ratios_totalMCuncup[i]->GetBinContent(bin)+vertshift);
      ratios_totalMCuncdown[i]->SetBinContent(bin,ratios_totalMCuncdown[i]->GetBinContent(bin)+vertshift);
      ratios_JECup[i]  ->SetBinContent(bin,ratios_JECup[i]  ->GetBinContent(bin)+vertshift);
      ratios_JECdown[i]->SetBinContent(bin,ratios_JECdown[i]->GetBinContent(bin)+vertshift);
      ratios_JERup[i]  ->SetBinContent(bin,ratios_JERup[i]  ->GetBinContent(bin)+vertshift);
      ratios_JERdown[i]->SetBinContent(bin,ratios_JERdown[i]->GetBinContent(bin)+vertshift);
      ratios_totaldatauncup[i]  ->SetBinContent(bin,ratios_totaldatauncup[i]->GetBinContent(bin)+vertshift);
      ratios_totaldatauncdown[i]->SetBinContent(bin,ratios_totaldatauncdown[i]->GetBinContent(bin)+vertshift);

      ratios_totaluncup[i]  ->SetBinContent(bin,ratios_totaluncup[i]->GetBinContent(bin)+vertshift);
      ratios_totaluncdown[i]->SetBinContent(bin,ratios_totaluncdown[i]->GetBinContent(bin)+vertshift);
      
      //std::cout<<"bincontent ratios = "<<ratios[i]->GetBinContent(bin)<<std::endl;//debug
      if(i==0)lumisysterr      ->SetBinContent(bin,lumisysterr      ->GetBinContent(bin)+vertshift);
    }
    
    if(i==0)ratios[i]->Draw("HIST E ][ ");     
    //ratios_statunc[i]->Draw("HIST E ][ SAME");    
    //ratios_JECup[i]->Draw("HIST ][ SAME");    
    //ratios_JECdown[i]->Draw("HIST ][ SAME");    
    //ratios_JERup[i]->Draw("HIST ][ SAME");    
    //ratios_JERdown[i]->Draw("HIST ][ SAME");    
    ratios_totaldatauncup[i]->Draw("HIST ][ SAME");
    ratios_totaldatauncdown[i]->Draw("HIST ][ SAME");
    
    
    //ratios_PDFup[i]->Draw("HIST ][ SAME");    
    //ratios_PDFdown[i]->Draw("HIST ][ SAME");    
    //ratios_MUup[i]->Draw("HIST ][ SAME");    
    //ratios_MUdown[i]->Draw("HIST ][ SAME");    
    //ratios_NPup[i]->Draw("HIST ][ SAME");    
    //ratios_NPdown[i]->Draw("HIST ][ SAME");    
    ratios_totalMCuncup[i]  ->Draw("HIST ][ SAME");
    ratios_totalMCuncdown[i]->Draw("HIST ][ SAME");

    ratios_totaluncup[i] ->Draw("HIST ][ SAME");
    ratios_totaluncdown[i] ->Draw("HIST ][ SAME");
    
    if(i==0)lumisysterr->Draw("HIST  E2  ][ SAME");
    ratios[i]->Draw("HIST E ][ SAME");    
    
    
    
    float xlo=ratios[i]->GetBinLowEdge(1);
    float xhi=
      ratios[i]->GetBinLowEdge(ratios[i]->GetNbinsX()) +   
      ratios[i]->GetBinWidth(  ratios[i]->GetNbinsX() );
    
    TLine* one     =makeTLine(xlo, (1.+vertshift) , xhi, (1.+vertshift));    
    one     ->Draw();       
    
    if(i==0){//DEBUG
      //if(i==2){//DEBUG
      TLegend* leg1=makeLegend(0.18, 0.76, 0.38, 0.89);
      //leg->SetHeader()
      leg1->AddEntry(ratios[i],"Unfolded Data","lp");
      //leg1->AddEntry(ratios_statunc[i],"Data #oplus Theory Stat. Unc.","le");
      leg1->AddEntry(lumisysterr,"Lumi. Unc., #pm 2.3%","lepf");//just f--> annoying border on the legend entry
                                                                //lepf w/ 0 line width, 0 marker color alpha -->no annoying border 
      leg1->Draw();    
      TLegend* leg2=makeLegend(0.41, 0.72, 0.61, 0.89);
      //leg2->AddEntry(ratios_JECup[i],"JEC Unc.","l");
      //leg2->AddEntry(ratios_JERup[i],"JER Unc.","l");
      leg2->AddEntry(ratios_totaldatauncup[i],"Data Stat. #oplus Syst. Unc.","l");
      //leg2->AddEntry(ratios_PDFup[i],"PDF Unc.","l");
      //leg2->AddEntry(ratios_MUup[i],"6P Scale Unc.","l");
      //leg2->AddEntry(ratios_NPup[i],"NPC Unc.","l");
      leg2->AddEntry(ratios_totalMCuncup[i],"Thy. Stat. #oplus Syst. Unc.","l");
      leg2->AddEntry(ratios_totaluncup[i],"Data #oplus Thy. Unc.","l");
      leg2->Draw();
      
      TPaveText* desc=NULL;
      desc=makePaveText( 0.63, 0.70, 0.86, 0.87);
      desc->AddText(etabin_strs[etabin].c_str());
      std::string ptrange=ptcuts_lo;
      ptrange+=std::to_string( (int)xhi)+" GeV";
      desc->AddText(ptrange.c_str());
      desc->AddText(jettype.c_str());
      if(      scalechoice.find("murmufHTp")!=std::string::npos)
	desc->AddText(scalechoice_murmufHTp.c_str());
      else if( scalechoice.find("murmufpt1")!=std::string::npos)
	desc->AddText(scalechoice_murmufpt1.c_str());
      else if( scalechoice.find("murmufpt" )!=std::string::npos)
	desc->AddText(scalechoice_murmufpt .c_str());      
      desc->Draw();
      
      TPaveText* NNLOstr=NULL;
      NNLOstr=makePaveText(.15,.61,.30,.66);
      NNLOstr->AddText("Data/NNLO + 1");
      NNLOstr->Draw();
      
      TPaveText* NLOstr=NULL;
      NLOstr=makePaveText(.15,.34,.25,.39);
      NLOstr->AddText("Data/NLO");
      NLOstr->Draw();
      
      //TPaveText* LOstr=NULL;
      //LOstr=makePaveText(.15,.25,.21,.30);
      //LOstr->AddText("Data/LO");
      //LOstr->Draw();
      
      SMPtitle->Draw();  
    }
    
  }
  
  
  //makeSMPInclJetXsec_allOunfdata_ratios
  saveCanv(outdir, canv, fout);
  spectra->Delete();
  spectra_JECup->Delete();
  spectra_JECdown->Delete();
  spectra_JERup->Delete();
  spectra_JERdown->Delete();

  for(int i=0; i<2; i++){
    mcspectra[i]->Delete();
    mcspectra_PDFup[i]->Delete();								   
    mcspectra_PDFdown[i]->Delete();							   
    mcspectra_MUup[i]->Delete();								   
    mcspectra_MUdown[i]->Delete();							   
    mcspectra_NPup[i]->Delete();								   
    mcspectra_NPdown[i]->Delete();								   
    
    ratios[i]->Delete();									   
    ratios_statunc[i]->Delete();	

    ratios_datastatunc[i]->Delete();	
    ratios_totaldatauncup[i]->Delete();								   
    ratios_totaldatauncdown[i]->Delete();								   
						       
    ratios_JECup[i]->Delete();								   
    ratios_JECdown[i]->Delete();								   
    ratios_JERup[i]->Delete();								   
    ratios_JERdown[i]->Delete();								   
    
    ratios_MCstatunc[i]->Delete();
    ratios_totalMCuncup[i]->Delete();								   
    ratios_totalMCuncdown[i]->Delete();								   

    ratios_MUup[i]->Delete();								   
    ratios_MUdown[i]->Delete();								   
    ratios_PDFup[i]->Delete();								   
    ratios_PDFdown[i]->Delete();								   
    ratios_NPup[i]->Delete();								   
    ratios_NPdown[i]->Delete();
    
    ratios_totaluncup[i]->Delete();
    ratios_totaluncdown[i]->Delete();
  }
  
  return;
}












//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOunfdata_wdatameas (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_NLOunfdata_wdatameas"<<std::endl;

  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
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

    measspectra[i] =  (TH1D*)(
			  (
			   (TH1D*)file->Get("Data_meas")
			   )->Clone( 
				    ("Data_meas_NLObins_ybin"+std::to_string(i)).c_str() 
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
  leg->SetHeader( "NLO #otimes NP Unfolded Data   ","C" );
  
  TPaveText* jetdesc=makePaveText(.64,.81,.87,.88);
  jetdesc->AddText(ptrange.c_str());
  jetdesc->AddText(jettype.c_str());
  
  TLegend* dataleg=makeLegend(0.64, 0.60, 0.90, 0.80);
  dataleg->SetHeader("Measured Data         ", "C");
  
  TCanvas* canv=makeSMPSpectraCanvas("NLOunfdata_SMPInclJetXsec_wdatameas");
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
    dataleg->AddEntry( measspectra[i], 
		       (legstr).c_str() ,"lp");        
    
    
    measspectra[i]->Draw("HIST E SAME");
    
  }
  
  leg->Draw();
  dataleg->Draw();
  jetdesc->Draw();
  
  TPaveText* SMPtitle=makePrelimPaveTextTitle();
  SMPtitle->Draw();  

  //makeSMPInclJetXsec_NLOunfdata_wdatameas
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    
    spectra[i]->Delete();
    measspectra[i]->Delete();
  }    

  return;
}


//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOunfdata_wdatameas_ratios (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_NLOunfdata_wdatameas_ratios"<<std::endl;

  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* measspectra[netabins]={};// Matrix Element Calculation of NNPDF; use for data comparisons
	                              
  TH1D* spectra[netabins]={};	      
  TH1D* spectra_JERup[netabins]={};   
  TH1D* spectra_JERdown[netabins]={}; 
  	                              
  	                              
  TH1D* ratios[netabins]={};	      
  TH1D* ratios_statunc[netabins]={};  
  TH1D* ratios_JERup[netabins]={};    
  TH1D* ratios_JERdown[netabins]={};  
  
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


    measspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)file->Get("Data_meas") 
			     )->Clone( 
				      ("Data_meas_ybin"+std::to_string(i)).c_str() 
				       )
			      );        
    
    ratios[i]=(TH1D*) spectra[i]->Clone(("Data_Meas_ratio_NLOunf_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(measspectra[i]);
    for(int j=1; j<=ratios[i]->GetNbinsX();j++)
      ratios[i]->SetBinError(j,0.0000000000000000000000000000001);//set this to *almost* 0[else the marker doesnt draw... stupid root], we'll see the rel stat error via ratios_statunc
    ratios[i]->SetMarkerSize(1.2);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    ratios[i]->SetMinimum(0.4);    ratios[i]->SetMaximum(1.6);
    setRatioHistLabels((TH1D*)ratios[i], "Ratio to Measured Data");
    
    
    //DATA STAT UNC
    ratios_statunc[i]=(TH1D*) spectra[i]->Clone(("Data_MC_StatUnc_ratio_ybin"+std::to_string(i)).c_str());
    ratios_statunc[i]->Divide(measspectra[i]);
    calculateCorrRatioErrs((TH1*)ratios_statunc[i],(TH1*)spectra[i],(TH1*)measspectra[i],0.5);
    //setOneBinContent(ratios_statunc[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    
    
    //for(int j=1; j<=measspectra[i]->GetNbinsX();j++)
    //  measspectra[i]->SetBinError(j,1.e-30);
    
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
    ratios_JERup[i]->Divide(measspectra[i]);
    //setOneBinContent_errHist(ratios[i], ratios_JERup[i]);
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
    ratios_JERdown[i]->Divide(measspectra[i]);
    //setOneBinContent_errHist(ratios[i], ratios_JERdown[i]);
    ratios_JERdown[i]->SetMarkerSize(0);  ratios_JERdown[i]->SetMarkerColor(kBlack);   ratios_JERdown[i]->SetMarkerStyle(kFullCircle);
    ratios_JERdown[i]->SetLineColor(kGreen);    ratios_JERdown[i]->SetLineWidth(1);    
    
    

    
    

  }
  
  
  

  TCanvas* canv=makeSMPRatioCanvas("NLOunfdata_SMPInclJetXsec_wdatameas_ratio");
  
  TPaveText* SMPtitle=makePrelimPaveTextTitleRatio();
  for(int i=0; i<netabins; i++){
    
    canv->cd(i+1);
    ratios[i]->Draw("HIST E ][ ");    
    ratios_statunc[i]->Draw("HIST E ][ SAME");    
    ratios_JERup[i]->Draw("HIST ][ SAME");    
    ratios_JERdown[i]->Draw("HIST ][ SAME");    
    ratios[i]->Draw("HIST E ][ SAME");    
    

    

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
      TLegend* leg=makeLegend(0.59, 0.63, 0.87, 0.87);
      //leg->SetHeader()
      leg->AddEntry(ratios[i],"NLO #otimes NP Unfolded Data","lp");
      leg->AddEntry(ratios_statunc[i],"Stat. Unc.","le");
      leg->AddEntry(ratios_JERup[i],"JER Unc.","l");
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
  
  //makeSMPInclJetXsec_NLOunfdata_wdatameas_ratios
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins; i++){

    measspectra[i]->Delete();
    
    spectra[i]->Delete();	      
    spectra_JERup[i]->Delete();   
    spectra_JERdown[i]->Delete(); 
    
    
    ratios[i]->Delete();	      
    ratios_statunc[i]->Delete();  
    ratios_JERup[i]->Delete();    
    ratios_JERdown[i]->Delete();  
  }
  return;
}







//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NLOunfrespmat_onePadOneEta (std::string outdir, TFile* fout){
    std::cout<<"running makeSMPInclJetXsec_NLOunfrespmat_onePadOneEta"<<std::endl;

  const int netabins=NLO_UNFDIR_DATA_Nfiles;
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH2D* respmatrix[netabins]={};
  float zmax=-1.;
  float zmin=99999999999999999999.;
  
  //first get the plots, clone + divide accordingly. binning should be set for me already, essentially
  for(int i=0; i<netabins; i++){
    std::string filepath= NLO_UNFDIR_DATA + NLO_UNFDIR_DATA_file_array[i] + ".root";
    TFile* file=TFile::Open(( filepath).c_str(), "READ");
    
    respmatrix[i] =  (TH2D*)(
			(
			 (TH2D*)file->Get("MC_mat_rebin") 
			 )->Clone( 
				  ("NLO_respmat_rebin_ybin"+std::to_string(i)).c_str() 
				   )
			    );
    float th2max=respmatrix[i]->GetMaximum();
    float th2min=getnonzeromin((TH2*)respmatrix[i]);
    if(th2max>zmax)zmax=th2max;
    if(th2min<zmin)zmin=th2min;
    
  }
  
  TCanvas* canv=makeSMPRatioCanvas("NLOunfrespmat_onePadOneEta");

  TPaveText* SMPtitle=makeSimPaveTextTitleRatio();
  bool dologx=true, dology=true, dologz=true;
  for(int i=0; i<netabins; i++){
      
    canv->cd(i+1)->SetLogx(dologx);//maybe set to 1?
    canv->cd(i+1)->SetLogy(dology);//maybe set to 1?
    canv->cd(i+1)->SetLogz(dologz);//maybe set to 1?
    canv->cd(i+1);
    
    setHistLabels((TH2D*)respmatrix[i], "True Jet p_{T} [GeV]","Smeared Jet p_{T} [GeV]");//,"Covariance [pb^{-2}]");
    
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
  
  //makeSMPInclJetXsec_NLOunfrespmat_onePadOneEta
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    respmatrix[i]->Delete();
  }  

  return;
}



