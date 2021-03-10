




void  makeSMPInclJetXsec_OnlyNLO (std::string outdir, TFile* fout=NULL);//SMEARED NLO unf, truth v. unf data

void  makeSMPInclJetXsec_NLOsyst_targPDF_ratios (std::string outdir, TFile* fout=NULL, 
						std::string targPDF="", std::string scalechoice="", std::string order="");//SMEARED NLO unf, truth v. unf data, ratios
//(std::string outdir, TFile* fout=NULL, std::string order="");//SMEARED NLO unf, truth v. unf data, ratios


void  makeSMPInclJetXsec_NPCs_onePadAllEta (std::string outdir, TFile* fout=NULL, std::string NPC_str="");
void  makeSMPInclJetXsec_NPCs_onePadOneEta (std::string outdir, TFile* fout=NULL, std::string NPC_str="");






//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_OnlyNLO (std::string outdir, TFile* fout){
  std::cout<<"running makeSMPInclJetXsec_OnlyNLO"<<std::endl;
  
  
  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  
  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  TH1D* spectra[netabins]={};
  TH1D* mcspectra[netabins]={};
  int powten=netabins-1;
  float maxy=-1., miny=100000000.;//global min/maxy
  
  std::string thyfilepath= FNLO_DIR+nlothyfile+".root";
  TFile* thyfile=TFile::Open(( thyfilepath).c_str(), "READ");
  
  
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
    
    
    mcspectra[i] =  (TH1D*)(
			    (
			     (TH1D*)thyfile->Get(("h1100"+std::to_string(i+1)+"00").c_str()) 
			     )->Clone( 
				      ("NLO_truth_ybin"+std::to_string(i)).c_str() 
				       )
			    );        //have to clone or else memory leak risk
    mcspectra[i]->Scale(1000.);//nb-->pb
    mcspectra[i]->Scale(pow(10,(float)powten));   
    
    //need to get rid of bins w/ 0 bin content for log scaling.
    //get all bin edges corresponding to bins w/ nonzero content.
    std::vector<double> bins;
    for(int j=1; j<=mcspectra[i]->GetNbinsX();j++){
      if(mcspectra[i]->GetBinContent(j)>0.){
	bins.push_back(mcspectra[i]->GetBinLowEdge(j));
	if(j==mcspectra[i]->GetNbinsX()){//case where every bin is filled; we'll miss the highest bin edge if this isn't here.
	  bins.push_back(mcspectra[i]->GetBinLowEdge(j)+
			 mcspectra[i]->GetBinWidth(j) );
	}
      }
      else {//if 0 bin content, we're at the end of the spectra
	bins.push_back(mcspectra[i]->GetBinLowEdge(j));
	break;
      }
    }
    mcspectra[i]=(TH1D*)mcspectra[i]->TH1::Rebin( (bins.size()-1), ((std::string)mcspectra[i]->GetName()+"_rebinclone").c_str() , (double*)bins.data());
    bins.clear();
    
    
    if(maxy<mcspectra[i]->GetMaximum())      maxy=mcspectra[i]->GetMaximum();
    if(miny>mcspectra[i]->GetMinimum())      miny=mcspectra[i]->GetMinimum();
    
    powten--;        
  }
  
  // now style hists stuff
  spectra[0]->SetMarkerSize(2);  spectra[0]->SetMarkerColor(kRed);       spectra[0]->SetMarkerStyle(kFullCircle);
  spectra[1]->SetMarkerSize(2);  spectra[1]->SetMarkerColor(kGreen);     spectra[1]->SetMarkerStyle(kFullSquare);
  spectra[2]->SetMarkerSize(2);  spectra[2]->SetMarkerColor(kBlue);      spectra[2]->SetMarkerStyle(kFullTriangleUp);
  spectra[3]->SetMarkerSize(2);  spectra[3]->SetMarkerColor(kMagenta);   spectra[3]->SetMarkerStyle(kFullTriangleDown); 
  spectra[0]->SetLineColor(kRed    );      
  spectra[1]->SetLineColor(kGreen  );    
  spectra[2]->SetLineColor(kBlue   );     
  spectra[3]->SetLineColor(kMagenta);  


  mcspectra[0]->SetMarkerSize(0);
  mcspectra[1]->SetMarkerSize(0);
  mcspectra[2]->SetMarkerSize(0);
  mcspectra[3]->SetMarkerSize(0);
  mcspectra[0]->SetLineColor(kRed    );	
  mcspectra[1]->SetLineColor(kGreen  );	
  mcspectra[2]->SetLineColor(kBlue   );	
  mcspectra[3]->SetLineColor(kMagenta);	
  
  //first hist to be drawn, so this gets the max/min/labels/titles set up
  mcspectra[0]->SetMaximum(maxy*10.);
  mcspectra[0]->SetMinimum(miny/5.);  
  mcspectra[0]->GetXaxis()->SetNoExponent(true);
  mcspectra[0]->GetXaxis()->SetMoreLogLabels(true);
  setHistLabels((TH1D*)mcspectra[0]);

  float xlo=mcspectra[0]->GetBinLowEdge(1);
  float xhi=mcspectra[0]->GetBinLowEdge(mcspectra[0]->GetNbinsX())+mcspectra[0]->GetBinWidth(mcspectra[0]->GetNbinsX());
  std::string ptrange=std::to_string((int)xlo) + " GeV < Jet p_{T} < "+std::to_string( (int)xhi)+" GeV";
  //std::string ptrange=ptcuts_lo+std::to_string( (int)xhi)+" GeV";


  TLegend* leg=makeLegend();
  //leg->SetHeader( "NLO #otimes NP Unfolded Data   ","C" );
  
  TLegend* mcleg=makeLegend(0.52, 0.72, 0.88, 0.84);
  //mcleg->SetHeader( jettype.c_str(),"C" );
  mcleg->AddEntry((TObject*)0, ptrange.c_str(), "");
  mcleg->AddEntry((TObject*)0, jettype.c_str(), "");
  //mcleg->AddEntry(mcspectra[0], "CT14nnlo NLO #otimes HERWIG EE5C NPCs", "l");
  mcleg->AddEntry((TObject*)0, "CT14nnlo NLO", "");
  
  TCanvas* canv=makeSMPSpectraCanvas("OnlyNLO_SMPInclJetXsec");
  //canv->cd()->SetLogy(0);//debug
  canv->cd();
  
  powten=netabins-1;
  for(int i=0; i<netabins; i++){
    
    //if(i==0)
    //  spectra[i]->Draw("HIST E ][");
    //else 
    //  spectra[i]->Draw("HIST E ][ SAME");
    
    std::string legstr=etabin_strs[i] + " ( x 10^{"+std::to_string(powten)+"} )";
    leg->AddEntry( mcspectra[i], 
		   (legstr).c_str() ,"lp");        
    powten--;
    
    if(i==0)
      mcspectra[i]->Draw("HIST E ][");    
    else 
      mcspectra[i]->Draw("HIST E ][ SAME");    
    
  }
  
  leg->Draw();
  mcleg->Draw();
  
  //TPaveText* SMPtitle=makePrelimPaveTextTitle();
  TPaveText* SMPtitle=makeSimPaveTextTitleRatio();
  //TPaveText* SMPtitle=makeSimPaveTextTitle();
  SMPtitle->Draw();  
  
  //makeSMPInclJetXsec_OnlyNLO
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    spectra[i]->Delete();
    mcspectra[i]->Delete();
  }  

  return;
}























//--------------------------------------------------------------------------------------------------------------------------------
//this is just to make systematic error bands on the theory itself, by itself. show as a deviation from 1.
void  makeSMPInclJetXsec_NLOsyst_targPDF_ratios (std::string outdir, TFile* fout, std::string targPDF, std::string scalechoice, std::string order){
  std::cout<<"running makeSMPInclJetXsec_NLOsyst_targPDF_ratios for "<<targPDF<<", "<<order<<", "<<scalechoice<<std::endl;    
  
  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  
  const int netabins=NLO_UNFDIR_DATA_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }

  
  //FastNLO file from JOAO
  //std::string thyfilepath= FNLO_DIR+nlothyfile+".root";
  //TFile* thyfile=TFile::Open(( thyfilepath).c_str(), "READ");
  
  TH1D* mcspectra[netabins]={};// Matrix Element Calculation of NNPDF; use for data comparisons
  TH1D* mcspectra_statunc[netabins]={};
  TH1D* mcspectra_PDFup[netabins]={};
  TH1D* mcspectra_PDFdown[netabins]={};
  TH1D* mcspectra_MUup[netabins]={};
  TH1D* mcspectra_MUdown[netabins]={};
  TH1D* mcspectra_NPup[netabins]={};
  TH1D* mcspectra_NPdown[netabins]={};
  
  TH1D* ratios[netabins]={};
  TH1D* ratios_statunc[netabins]={};
  TH1D* ratios_PDFup[netabins]={};
  TH1D* ratios_PDFdown[netabins]={};
  TH1D* ratios_MUup[netabins]={};
  TH1D* ratios_MUdown[netabins]={};
  TH1D* ratios_NPup[netabins]={};
  TH1D* ratios_NPdown[netabins]={};
  TH1D* ratios_totaluncUP[netabins]={};
  TH1D* ratios_totaluncDOWN[netabins]={};
  
  
  int orderint=-1;
  if(order=="NNLO")orderint=0;
  else if(order=="NLO")orderint=1;
  else if(order=="LO")orderint=2;
  else return;

  std::vector<double> bins={0.};//place holder for now. might not bother adding rebinning functionality.
  std::string targPDF_nous=replace_underscores(targPDF);  
  for(int i=0; i<netabins; i++){
    
    mcspectra[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) std::to_string(orderint),
					  (int) i, (int) 0,
					  (bool) false, (std::vector<double>) bins, 
					  (bool) true, "");        
    //mcspectra_statunc[i]=(TH1D*)mcspectra[i]->Clone( ((std::string)mcspectra[i]->GetName()+"_statunc_clone").c_str() );
    
    //so the stat unc isn't inflated by sqrt(2) in the ratio at 1
    for(int j=1; j<=mcspectra[i]->GetNbinsX();j++)//errors due to PDF will be illustrated by 6 point scale var error. leave inherent PDF errors out of it.
      mcspectra[i]->SetBinError(j,1.e-30);//set this to *almost* 0[else the marker doesnt draw... stupid root]
    
    ratios[i]=(TH1D*) mcspectra[i]->Clone((targPDF+"_"+order+"_"+scalechoice+"_ratio_ybin"+std::to_string(i)).c_str());
    ratios[i]->Divide(mcspectra[i]);//should just be at 1
    ratios[i]->SetMarkerSize(0);  ratios[i]->SetMarkerColor(kBlack);   ratios[i]->SetMarkerStyle(kFullCircle);
    ratios[i]->SetLineColor(kBlack);    
    //    ratios[i]->SetMinimum(0.4);    ratios[i]->SetMaximum(1.6);
    ratios[i]->SetMinimum(0.75);    ratios[i]->SetMaximum(1.35);
    
    setRatioHistLabels((TH1D*)ratios[i], targPDF_nous+" #otimes NPC Relative Unc.");
    
    //stat unc
    mcspectra_statunc[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) std::to_string(orderint),
    						  (int) i, (int) 0,
    						  (bool) false, (std::vector<double>) bins, 
    						  (bool) true, "");        
    
    ratios_statunc[i]=(TH1D*)mcspectra_statunc[i]->Clone(
							 ("thy_statunc_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
							 );
    ratios_statunc[i]->Divide(mcspectra[i]);
    ratios_statunc[i]->SetMarkerSize(0);  ratios_statunc[i]->SetMarkerColor(kBlack);   ratios_statunc[i]->SetMarkerStyle(kFullCircle);
    ratios_statunc[i]->SetLineColor(kGray+2);    
    
    
    //6PT SCALE SYSTEMATICS
    mcspectra_MUup[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) std::to_string(orderint),
						(int) i, (int) 9,
						(bool) false, (std::vector<double>) bins, 
						(bool) true, "");       
    ratios_MUup[i]=(TH1D*)mcspectra_MUup[i]->Clone(
						     ("thy_MUsysup_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
						     );
    ratios_MUup[i]->Divide(mcspectra[i]);
    ratios_MUup[i]->SetMarkerSize(0);  ratios_MUup[i]->SetMarkerColor(kBlack);   ratios_MUup[i]->SetMarkerStyle(kFullCircle);
    ratios_MUup[i]->SetLineColor(kMagenta);    ratios_MUup[i]->SetLineWidth(1);    
    
    
    
    
    mcspectra_MUdown[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) std::to_string(orderint),
						  (int) i, (int) 8,
						  (bool) false, (std::vector<double>) bins, 
						  (bool) true, "");           
    ratios_MUdown[i]=(TH1D*)mcspectra_MUdown[i]->Clone(
							 ("thy_MUsysdown_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
							 );
    ratios_MUdown[i]->Divide(mcspectra[i]);
    ratios_MUdown[i]->SetMarkerSize(0);  ratios_MUdown[i]->SetMarkerColor(kBlack);   ratios_MUdown[i]->SetMarkerStyle(kFullCircle);
    ratios_MUdown[i]->SetLineColor(kMagenta);    ratios_MUdown[i]->SetLineWidth(1);    

    //PDF SYSTEMATICS
    mcspectra_PDFup[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) std::to_string(orderint),
						(int) i, (int) 2,
						(bool) false, (std::vector<double>) bins, 
						(bool) true, "");       
    ratios_PDFup[i]=(TH1D*)mcspectra_PDFup[i]->Clone(
						     ("thy_PDFsysup_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
						     );
    ratios_PDFup[i]->Divide(mcspectra[i]);
    ratios_PDFup[i]->SetMarkerSize(0);  ratios_PDFup[i]->SetMarkerColor(kBlack);   ratios_PDFup[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFup[i]->SetLineColor(kYellow+2);    ratios_PDFup[i]->SetLineWidth(1);    
    
    
    
    
    mcspectra_PDFdown[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) std::to_string(orderint),
						  (int) i, (int) 1,
						  (bool) false, (std::vector<double>) bins, 
						  (bool) true, "");           
    ratios_PDFdown[i]=(TH1D*)mcspectra_PDFdown[i]->Clone(
							 ("thy_PDFsysdown_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
							 );
    ratios_PDFdown[i]->Divide(mcspectra[i]);
    ratios_PDFdown[i]->SetMarkerSize(0);  ratios_PDFdown[i]->SetMarkerColor(kBlack);   ratios_PDFdown[i]->SetMarkerStyle(kFullCircle);
    ratios_PDFdown[i]->SetLineColor(kYellow+2);    ratios_PDFdown[i]->SetLineWidth(1);    
    
    
    //NP SYSTEMATICS
    mcspectra_NPup[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) std::to_string(orderint),
					       (int) i, (int) 0,
					       (bool) false, (std::vector<double>) bins, 
					       (bool) true, "up");
    ratios_NPup[i]=(TH1D*)mcspectra_NPup[i]->Clone(
						   ("thy_NPsysup_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
						   );
    ratios_NPup[i]->Divide(mcspectra[i]);
    ratios_NPup[i]->SetMarkerSize(0);  ratios_NPup[i]->SetMarkerColor(kBlack);   ratios_NPup[i]->SetMarkerStyle(kFullCircle);
    ratios_NPup[i]->SetLineColor(kCyan+2);    ratios_NPup[i]->SetLineWidth(1);    
    
    
    mcspectra_NPdown[i]=(TH1D*)make_fNLOSpectra( (std::string) targPDF, (std::string) scalechoice, (std::string) std::to_string(orderint),
						 (int) i, (int) 0,
						 (bool) false, (std::vector<double>) bins, 
						 (bool) true, "down");
    ratios_NPdown[i]=(TH1D*)mcspectra_NPdown[i]->Clone(
						       ("thy_NPsysdown_"+order+"_ratio_ybin"+std::to_string(i)).c_str()
						       );    
    ratios_NPdown[i]->Divide(mcspectra[i]);
    ratios_NPdown[i]->SetMarkerSize(0);  ratios_NPdown[i]->SetMarkerColor(kBlack);   ratios_NPdown[i]->SetMarkerStyle(kFullCircle);
    ratios_NPdown[i]->SetLineColor(kCyan+2);    ratios_NPdown[i]->SetLineWidth(1);    
    
    ////TOTAL UNC (STAT + SYST)
    ratios_totaluncUP[i]=(TH1D*) ratios_statunc[i]->Clone(("MC_totalUncUP_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncUP[i]->Reset("MICES");
    ratios_totaluncUP[i]->SetMarkerSize(0);  ratios_totaluncUP[i]->SetMarkerColor(kBlack);   ratios_totaluncUP[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncUP[i]->SetLineColor(kBlack);    ratios_totaluncUP[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("up",
			   ratios_statunc[i],
			   ((std::vector<TH1*>){ratios_MUup[i],ratios_NPup[i], ratios_PDFup[i]}) ,
			   ratios_totaluncUP[i]);
    
    ratios_totaluncDOWN[i]=(TH1D*) ratios_statunc[i]->Clone(("MC_totalUncDOWN_ratio_ybin"+std::to_string(i)).c_str());
    ratios_totaluncDOWN[i]->Reset("MICES");
    ratios_totaluncDOWN[i]->SetMarkerSize(0);  ratios_totaluncDOWN[i]->SetMarkerColor(kBlack);   ratios_totaluncDOWN[i]->SetMarkerStyle(kFullCircle);
    ratios_totaluncDOWN[i]->SetLineColor(kBlack);    ratios_totaluncDOWN[i]->SetLineWidth(1);    
    makeTotRelSystUncRatio("down",
			   ratios_statunc[i],
			   ((std::vector<TH1*>){ratios_MUdown[i],ratios_NPdown[i], ratios_PDFdown[i]}) ,
			   ratios_totaluncDOWN[i]);
    
  }  
  
  
  std::string name=targPDF+"_"+order+"_"+scalechoice+"_syst_SMPInclJetXsec_ratio";
  TCanvas* canv=makeSMPRatioCanvas(name);
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
    ratios_MUup[i]->Draw("HIST ][ SAME");    
    ratios_MUdown[i]->Draw("HIST ][ SAME");  
    ratios_PDFup[i]->Draw("HIST ][ SAME");    
    ratios_PDFdown[i]->Draw("HIST ][ SAME");  
    ratios_NPup[i]->Draw("HIST ][ SAME");    
    ratios_NPdown[i]->Draw("HIST ][ SAME");  
    ratios_totaluncUP[i]->Draw("HIST ][ SAME");    
    ratios_totaluncDOWN[i]->Draw("HIST ][ SAME");  
    ratios[i]->Draw("HIST E ][ SAME");
    
    if(i==1){
      TLegend* leg=makeLegend(0.55, 0.63, 0.88, 0.87);
      leg->SetHeader((targPDF_nous+" "+order).c_str(),"");
      leg->AddEntry(ratios_statunc[i],"Stat Unc.","le");
      leg->AddEntry(ratios_PDFup[i]  ,"PDF Unc.","l");
      leg->AddEntry(ratios_MUup[i]  ,"6P Scale Unc.","l");
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
  
  //makeSMPInclJetXsec_NLOsyst_targPDF_ratios
  saveCanv(outdir, canv, fout);

  for(int i=0; i<netabins;i++){
    
    mcspectra[i]->Delete();
    mcspectra_statunc[i]->Delete();
    mcspectra_MUup[i]->Delete();
    mcspectra_MUdown[i]->Delete();
    mcspectra_PDFup[i]->Delete();
    mcspectra_PDFdown[i]->Delete();
    mcspectra_NPup[i]->Delete();
    mcspectra_NPdown[i]->Delete();

    ratios[i]->Delete();
    ratios_statunc[i]->Delete();
    ratios_MUup[i]->Delete();
    ratios_MUdown[i]->Delete();
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
void  makeSMPInclJetXsec_NPCs_onePadAllEta (std::string outdir, TFile* fout, std::string NPC_str){
  std::cout<<"running makeSMPInclJetXsec_NPCS_onePadAllEta for "<< NPC_str<<" NPCs"<<std::endl;  
  if(NPC_str=="")
    return;
  
  
  const int netabins=JERDIR_MC_Nfiles;  
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }

  TF1* NPCfit[netabins]={};
  TH1D* NPCfithist[netabins]={};//to make it easier to draw stuff
  float maxy=-1., miny=100000000.;//global min/maxy
  std::string filepath= NPC_DIR + NPC_FILE + ".root";
  TFile* file=TFile::Open(( filepath).c_str(), "READ");  

  //first get the plots, scale accordingly, get the min/max y's
  for(int i=0; i<netabins; i++){
    
    NPCfit[i] =  (TF1*)(
			(
			 (TF1*)file->Get(("fNPC_"+NPC_str+"_R4_etabin"+std::to_string(i)).c_str()) 
			 )->Clone( 
				  ("fNPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str()) 			 
			);
    
    NPCfithist[i]=(TH1D*)(
			  NPCfit[i]->GetHistogram() 
			  );
    NPCfithist[i]->SetName(("hNPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str());
    if(maxy<NPCfithist[i]->GetMaximum())      maxy=NPCfithist[i]->GetMaximum();
    if(miny>NPCfithist[i]->GetMinimum())      miny=NPCfithist[i]->GetMinimum();
    
    
  }
  
  // now style hists stuff
  NPCfit[0]->SetLineColor(kRed);      
  NPCfit[1]->SetLineColor(kGreen);    
  NPCfit[2]->SetLineColor(kBlue);     
  NPCfit[3]->SetLineColor(kMagenta);  
  
  NPCfithist[0]->Reset("ICES");
  NPCfithist[0]->SetMaximum(maxy*1.02);
  NPCfithist[0]->SetMinimum(miny*.99);
  NPCfithist[0]->SetTitle("");  
  NPCfithist[0]->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
  NPCfithist[0]->GetXaxis()->SetNoExponent(true);
  NPCfithist[0]->GetXaxis()->SetMoreLogLabels(true);  
  NPCfithist[0]->GetYaxis()->SetTitle("Correction Factor");
  NPCfithist[0]->GetYaxis()->CenterTitle(true);
    

  //first hist to be drawn, so this gets the max/min/labels/titles set up
  TLegend* leg=makeLegend(0.12, 0.63, 0.4, 0.88);
  leg->SetHeader( (NPC_str+" NPC Fits (R=0.4)").c_str(),"" );
  
  TCanvas* canv=makeSMPSpectraCanvas(NPC_str+"_NPCs_onePadAllEta");
  canv->SetLogy(0);
  canv->SetLogx(1);
  canv->cd();
  
  NPCfithist[0]->Draw("");
  
  for(int i=0; i<netabins; i++){
    NPCfit[i]->Draw("SAME");
    std::string legstr=const_ybin_strs[i] ;
    leg->AddEntry( NPCfit[i], 
		   (legstr).c_str() ,"lp");        
    
    
  }
  
  leg->Draw();
  
  TPaveText* SMPtitle=makeSimPaveTextTitle();
  SMPtitle->Draw();  
  
  //makeSMPInclJetXsec_NPCs_onePadAllEta
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    NPCfit[i]->Delete();
  }
  return;
}









//--------------------------------------------------------------------------------------------------------------------------------
void  makeSMPInclJetXsec_NPCs_onePadOneEta (std::string outdir, TFile* fout, std::string NPC_str){
  std::cout<<"running makeSMPInclJetXsec_NPCS_onePadOneEta for "<< NPC_str<< " NPCs"<<std::endl;
  
  gStyle->SetOptStat(0);
  gROOT->ForceStyle();
  
  if(NPC_str=="")
    return;
  
  const int netabins=NLO_UNFDIR_DATA_Nfiles;
  if(netabins!=n_etabin_strs){
    printetabinerrormessage();
    return;
  }
  
  //TH1F* NPCdata_toClone[netabins]={};	  
  TH1F* NPCdata[netabins]={};		  
  TH1F* NPCdata_forDraw[netabins]={};		  //b.c. the fit is a primitive in the hist. and so gets drawn. copy bin contents only. leave everything else
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
    
    NPCfit[i] =  (TF1*)(
			(
			 (TF1*)file->Get( ("fNPC_"+NPC_str+"_R4_etabin"+std::to_string(i)).c_str())
			 )->Clone(        ("fNPC_"+NPC_str+"_R4_ybin"+std::to_string(i)).c_str()
					  )
			);
    if(NPC_str!="AVG"){
      NPCdata[i] =  (TH1F*)(
			    (
			     (TH1F*)file->Get( ("hNPC_"+NPC_str+"_R4_etabin"+std::to_string(i)).c_str())
			     )->Clone( 
				      ("NPC_"+NPC_str+"_R4_ybin"+std::to_string(i)+"_clone").c_str()
				       )
			    );      
      NPCdata[i]->TH1::ClearUnderflowAndOverflow();

      
    }
    else if(NPC_str=="AVG"){
      NPCdata[i] =  (TH1F*)(
			    (
			     (TH1F*)file->Get( ("hNPC_HERWIG_R4_etabin"+std::to_string(i)).c_str())
			     )->Clone( 
				      ("NPC_HERWIG_R4_ybin"+std::to_string(i)+"_clone").c_str()
				       )
			    );      
      NPCdata[i]->TH1::ClearUnderflowAndOverflow();
      //NPCdata[i]->SetLineColorAlpha(kBlack, 0.);
      //NPCdata[i]->SetMarkerColorAlpha(kBlack, 0.);
      NPCdata[i]->Reset("MICES");
      
    }
    




    //// weird thing; the hist has the fit *inside* of it, and is drawn automatically with the hist. this sucks!
    
    int nbins=NPCdata[i]->GetNbinsX();
    Double_t ptbins[nbins+1];
    for(int j=1; j<=nbins;j++){
      ptbins[j-1]=NPCdata[i]->GetBinLowEdge(j);
      if(j==nbins){
	ptbins[j]=NPCdata[i]->GetBinLowEdge(j)+NPCdata[i]->GetBinWidth(j);
      }
    }
    


    
    NPCdata_forDraw[i]=new TH1F(   ("NPC_"+NPC_str+"_R4_ybin"+std::to_string(i)+"_clone_forDraw").c_str(),
				   ("NPC_"+NPC_str+"_R4_ybin"+std::to_string(i)+"_clone_forDraw").c_str(), nbins, (double*)ptbins);      
    
    for(int k=1; k<=(nbins);k++){
      NPCdata_forDraw[i]->SetBinContent(k,
					NPCdata[i]->GetBinContent(k));
      NPCdata_forDraw[i]->SetBinError(k,
				      NPCdata[i]->GetBinError(k));	
    }
    
    
    ////end weird thing
    
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

    double xmintemp,xmaxtemp;//i have to do this this way for some reason.
    NPCfit[i]->GetRange(xmintemp,xmaxtemp);
    xmin[i]=xmintemp;
    xmax[i]=xmaxtemp;
    
  }
  
  if(NPC_str!="AVG"){
    NPCdata_forDraw[0]->SetLineColor(kRed);     NPCdata_forDraw[0]->SetMarkerColor(kBlack); NPCdata_forDraw[0]->SetMarkerStyle(kFullCircle); NPCdata_forDraw[0]->SetMarkerSize(.6);
    NPCdata_forDraw[1]->SetLineColor(kGreen);   NPCdata_forDraw[1]->SetMarkerColor(kBlack); NPCdata_forDraw[1]->SetMarkerStyle(kFullCircle); NPCdata_forDraw[1]->SetMarkerSize(.6);
    NPCdata_forDraw[2]->SetLineColor(kBlue);    NPCdata_forDraw[2]->SetMarkerColor(kBlack); NPCdata_forDraw[2]->SetMarkerStyle(kFullCircle); NPCdata_forDraw[2]->SetMarkerSize(.6);
    NPCdata_forDraw[3]->SetLineColor(kMagenta); NPCdata_forDraw[3]->SetMarkerColor(kBlack); NPCdata_forDraw[3]->SetMarkerStyle(kFullCircle); NPCdata_forDraw[3]->SetMarkerSize(.6);
  }
  else{
    NPCdata_forDraw[0]->SetLineColorAlpha(kRed    , 0.);    NPCdata_forDraw[0]->SetMarkerColorAlpha(kBlack, 0.); 
    NPCdata_forDraw[1]->SetLineColorAlpha(kGreen  , 0.);    NPCdata_forDraw[1]->SetMarkerColorAlpha(kBlack, 0.); 
    NPCdata_forDraw[2]->SetLineColorAlpha(kBlue   , 0.);    NPCdata_forDraw[2]->SetMarkerColorAlpha(kBlack, 0.); 
    NPCdata_forDraw[3]->SetLineColorAlpha(kMagenta, 0.);    NPCdata_forDraw[3]->SetMarkerColorAlpha(kBlack, 0.); 
    
    NPCdata_forDraw[0]->SetMarkerStyle(kFullCircle); NPCdata_forDraw[0]->SetMarkerSize(.6);
    NPCdata_forDraw[1]->SetMarkerStyle(kFullCircle); NPCdata_forDraw[1]->SetMarkerSize(.6);
    NPCdata_forDraw[2]->SetMarkerStyle(kFullCircle); NPCdata_forDraw[2]->SetMarkerSize(.6);
    NPCdata_forDraw[3]->SetMarkerStyle(kFullCircle); NPCdata_forDraw[3]->SetMarkerSize(.6);
    
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
    if(NPC_str!="AVG")leg->AddEntry(NPCdata_forDraw[i],"Data Points", "lpe");
    leg->AddEntry(NPCfit[i],"Fit", "l");
    leg->AddEntry(NPCfit_sysup[i],"Fit Unc.", "l");
    
    
    setRatioHistLabels((TH1*)NPCdata_forDraw[i], "Correction Factor");
    NPCdata_forDraw[i]->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
    
    if(dologx)NPCdata_forDraw[i]->GetXaxis()->SetNoExponent(true);
    if(dologx)NPCdata_forDraw[i]->GetXaxis()->SetMoreLogLabels(true);
    //std::cout<<"xmin["<<i<<"]="<<xmin[i]<<std::endl;
    //std::cout<<"xmax["<<i<<"]="<<xmax[i]<<std::endl;
    //std::cout<<"(underflow) NPCdata_forDraw["<<i<<"]->GetBinContent(0)="<<NPCdata_forDraw[i]->GetBinContent(0)<<std::endl;
    //std::cout<<"(overflow)  NPCdata_forDraw["<<i<<"]->GetBinContent("<<NPCdata_forDraw[i]->GetNbinsX()+1<<")="<<NPCdata_forDraw[i]->GetBinContent(NPCdata_forDraw[i]->GetNbinsX()+1)<<std::endl;
    
    if(NPC_str=="PYTHIA8"){
      NPCdata_forDraw[i]->SetMinimum(0.90);      NPCdata_forDraw[i]->SetMaximum(1.05);            }
    else if((NPC_str=="HERWIG")||
	    (NPC_str=="AVG")){
      NPCdata_forDraw[i]->SetMinimum(0.83);      NPCdata_forDraw[i]->SetMaximum(1.08);            }
    
    NPCdata_forDraw[i]->SetAxisRange(xmin[i],xmax[i], "X");
    
    TLine* one     =makeTLine(xmin[i], 1. , xmax[i], 1.);          
    
    TPaveText* desc=makePaveText( 0.4, .9, 0.6, .98);
    desc->AddText(const_ybin_strs[i].c_str());
    
    canv->cd(i+1)->SetLogx(dologx);
    canv->cd(i+1)->SetLogy(dology);
    canv->cd(i+1);
    
    NPCdata_forDraw[i]->Draw("");    
    one     ->Draw();      
    NPCdata_forDraw[i]->Draw("HIST E ][ SAME");    

    NPCfit[i]->Draw("SAME");
    NPCfit_sysup[i]->Draw("SAME");
    NPCfit_sysdown[i]->Draw("SAME");
    
    desc->Draw();
    SMPtitle->Draw();
    leg->Draw();
  }

  
  //makeSMPInclJetXsec_NPCs_onePadOneEta
  saveCanv(outdir, canv, fout);
  for(int i=0; i<netabins;i++){
    NPCdata[i]->Delete();		  
    NPCdata_forDraw[i]->Delete();		  
    NPCfit[i]->Delete();		  
    NPCfit_sysup[i]->Delete();	  
    NPCfit_sysdown[i]->Delete();      

  }

  return;
}














