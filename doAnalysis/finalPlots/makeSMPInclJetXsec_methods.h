void saveCanv(std::string, TCanvas*, TFile*);
TCanvas* makeSMPSpectraCanvas(           std::string);
TCanvas* makeSMPRatioCanvas(           std::string);
TCanvas* makeSMPRatioCanvas_allO(           std::string);


TLegend* makeLegend();
TLegend* makeLegend(float, float, float, float);
TPaveText* makeSimPaveTextTitle();
TPaveText* makePrelimPaveTextTitle();
TPaveText* makeSimPaveTextTitleRatio();
TPaveText* makePrelimPaveTextTitleRatio();
TPaveText* makePaveText(float, float, float, float);
TPaveText* makePaveText(float, float, float, float, std::string);
TLine* makeTLine(float, float, float, float);

void  setHistLabels( TH1*);
void  setHistLabels( TH1*,std::string,std::string);
void  setHistLabels( TH2*,std::string,std::string);
void  setRatioHistLabels( TH1*, std::string);
void styleLumiHist(TH1*);
void applyNPCorrs(TF1*, TH1*);
void applyNPCorrs(TH1*, int, std::string);

void printetabinerrormessage();
void setOneBinContent(TH1*);
void printBinContent(TH1*);
void multiplyBinWidth(TH1*);
void divideBinWidth(TH1*);


float getnonzeromin(TH1*);
float getnonzeromin(TH2*);
void calculateCorrRatioErrs(TH1*, TH1*, TH1*, float);
double* setBinning_etabin(int , int*    );
void makeTotRelSystUncRatio(std::string ,TH1*, std::vector<TH1*> , TH1*);
void makeTotSystUncRatio(std::string ,TH1*, TH1*, std::vector<TH1*> , TH1*);

TH1D* make_fNLOSpectra( 
		       std::string, std::string, std::string, 
		       int, int,
		       bool, std::vector<double>, 
		       bool, std::string);

std::string replace_underscores(std::string);



// global canvas size
const int CANVX=2400, CANVY=CANVX*0.75;
//const int CANVX=1400, CANVY=CANVX*0.75;


//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------


void saveCanv(std::string outdir,TCanvas* canv, TFile* fout=NULL){
  
  canv->SaveAs((
		outdir+
		((std::string)canv->GetName())+
		".pdf"
		).c_str()
	       );

  canv->SaveAs((
		outdir+
		((std::string)canv->GetName())+
		".png"
		).c_str()
	       );
  if((bool)fout){
    fout->cd();
    canv->Write();
  }
  return;
}






//makes canvas for SMP-style incl jet spectra, returns TCanvas object
TCanvas* makeSMPSpectraCanvas( std::string name="defname"){
  bool funcDebug=true;
  if(funcDebug)std::cout<<"in makeSMPSpectraCanvas"<<std::endl;
  
  if(funcDebug)std::cout<<"creating new TCanvas"<<std::endl;
  TCanvas* c =new TCanvas((name).c_str(), (name).c_str(), CANVX, CANVY);
  //if(funcDebug)std::cout<<"c->Dump() prints..."<<std::endl;
  //if(funcDebug)c->Dump();
  c->SetLogx(1);    
  c->SetLogy(1);
  c->cd();
  
  if(funcDebug)std::cout<<"about to return TCanvas pointer"<<std::endl;
  return (TCanvas*)c;
}



//pad1, spectra pad, dim and margin, axis log settings
//const float pad1x1=0.0, pad1y1=0.3, pad1x2=1.0, pad1y2=1.0;
//const float pad1_bottom_mar=0.;
//const bool pad1_logx=true, pad1_logy=true;
//pad2, ratio pad, dim and margin, axis log settings
//const float pad2x1=0.0, pad2y1=0.0, pad2x2=1.0, pad2y2=pad1y1;
//const float pad2_top_mar=0., pad2_bottom_mar=0.25;
const int nxpads=2, nypads=2;
const float xmargin=0.005, ymargin=0.005;//def is 0.01 for TPad::Divide
const bool pad_logx=true, pad_logy=false;
const bool pad_gridx=false, pad_gridy=false;
TCanvas* makeSMPRatioCanvas( std::string name="defname"){
  bool funcDebug=true;
  if(funcDebug)std::cout<<"in makeSMPRatioCanvas"<<std::endl;
  
  if(funcDebug)std::cout<<"creating new TCanvas"<<std::endl;
  TCanvas* c =new TCanvas((name).c_str(), (name).c_str(), CANVX, CANVY);
  //if(funcDebug)std::cout<<"c->Dump() prints..."<<std::endl;
  //if(funcDebug)c->Dump();
  c->cd();
  //TPad::Divide(nx, ny, xmargin=0.01, ymargin=0.01);
  c->TPad::Divide(nxpads, nypads, xmargin, ymargin);
  const int npads=nxpads*nypads;
  for(int i=1; i<=npads; i++){
    c->cd(i)->SetLogx(pad_logx);
    c->cd(i)->SetLogy(pad_logy);
    c->cd(i)->SetGridx(pad_gridx);
    c->cd(i)->SetGridy(pad_gridy);
  }
  
  //  //setup pads + draw on canvases
  //  if(funcDebug)std::cout<<"creating pad1"<<std::endl;
  //  TPad *pad1 = new TPad(("pad1"+name).c_str(), ("pad1"+name).c_str(), pad1x1, pad1y1, pad1x2, pad1y2);
  //  pad1->SetLogx(pad1_logx);    pad1->SetLogy(pad1_logy);
  //  pad1->SetBottomMargin(pad1_bottom_mar); // Upper and lower plot are joined  
  //  pad1->Draw();             // Draw the upper pad: pad1
  //  pad1->cd();
  //  pad1->SetNumber(1);
  //  
  //  c->cd();
  //  if(funcDebug)std::cout<<"creating pad2"<<std::endl;
  //  TPad *pad2 = new TPad(("pad2"+name).c_str(), ("pad2"+name).c_str(), pad2x1, pad2y1, pad2x2, pad2y2);
  //  pad2->SetLogx(pad2_logx);    pad2->SetLogy(pad2_logy);    
  //  pad2->SetTopMargin(pad2_top_mar);  pad2->SetBottomMargin(pad2_bottom_mar);
  //  pad2->Draw();
  //  pad2->cd();
  //  pad2->SetNumber(2);
  
  //if(funcDebug)std::cout<<"c->Dump() prints..."<<std::endl;
  //if(funcDebug)c->Dump();
  if(funcDebug)std::cout<<"about to return TCanvas pointer"<<std::endl;
  return (TCanvas*)c;
}




TCanvas* makeSMPRatioCanvas_allO( std::string name="defname"){
  bool funcDebug=true;
  if(funcDebug)std::cout<<"in makeSMPRatioCanvas_allO"<<std::endl;
  
  if(funcDebug)std::cout<<"creating new TCanvas"<<std::endl;
  //TCanvas* c =new TCanvas((name).c_str(), (name).c_str(), CANVX, (3.*CANVY));
  //TCanvas* c =new TCanvas((name).c_str(), (name).c_str(), (3*CANVX), (9*CANVY));
  TCanvas* c =new TCanvas((name).c_str(), (name).c_str(), 3600,1800 );
  //if(funcDebug)std::cout<<"c->Dump() prints..."<<std::endl;
  //if(funcDebug)c->Dump();
  c->cd();
  c->cd()->SetLogx(pad_logx);
  c->cd()->SetLogy(pad_logy);
  c->cd()->SetGridx(pad_gridx);
  c->cd()->SetGridy(pad_gridy);
    
  //if(funcDebug)std::cout<<"c->Dump() prints..."<<std::endl;
  //if(funcDebug)c->Dump();
  if(funcDebug)std::cout<<"about to return TCanvas pointer"<<std::endl;
  return (TCanvas*)c;
}



const float legbordersize=0.;
const float legx1=0.13, legy1=0.15, legx2=0.43, legy2=0.35;
TLegend* makeLegend(){
  TLegend* l=new TLegend(legx1, legy1, legx2, legy2);
  l->SetBorderSize(legbordersize);
  l->SetFillStyle(0);
  return (TLegend*)l;
}
TLegend* makeLegend(float x1, float y1, float x2, float y2){
  TLegend* l=new TLegend(x1, y1, x2, y2);
  l->SetBorderSize(legbordersize);
  l->SetFillStyle(0);
  return (TLegend*)l;
}



const float pavex1=.05, pavey1=.90, pavex2=.95, pavey2=0.95;
TPaveText* makeSimPaveTextTitle(){
  TPaveText* title=new TPaveText(pavex1, pavey1,
				 pavex2, pavey2
				 ,"NDC");
  title->SetFillStyle(0);
  title->SetBorderSize(0.);
  title->AddText(simpavetitle.c_str());
  return (TPaveText*)title;
}
TPaveText* makePrelimPaveTextTitle(){
  TPaveText* title=new TPaveText(pavex1, pavey1,
				 pavex2, pavey2
				 ,"NDC");
  title->SetFillStyle(0);
  title->SetBorderSize(0.);
  title->AddText(prelimpavetitle.c_str());
  return (TPaveText*)title;
}


const float   ratpavex1=.05,   ratpavey1=.91,   ratpavex2=.95,   ratpavey2=0.97;
TPaveText* makeSimPaveTextTitleRatio(){
  TPaveText* title=new TPaveText(ratpavex1, ratpavey1,
				 ratpavex2, ratpavey2
				 ,"NDC");
  title->SetFillStyle(0);
  title->SetBorderSize(0.);
  title->AddText(simratpavetitle.c_str());
  return (TPaveText*)title;
}
TPaveText* makePrelimPaveTextTitleRatio(){
  TPaveText* title=new TPaveText(ratpavex1, ratpavey1,
				 ratpavex2, ratpavey2
				 ,"NDC");
  title->SetFillStyle(0);
  title->SetBorderSize(0.);
  title->AddText(prelimratpavetitle.c_str());
  return (TPaveText*)title;
}


TPaveText* makePaveText(float x1, float y1, float x2, float y2){
  TPaveText* pavetxt=new TPaveText(x1, y1,
				   x2, y2
				   ,"NDC");
  pavetxt->SetFillStyle(0);
  pavetxt->SetBorderSize(0.);
  return (TPaveText*)pavetxt;
}
TPaveText* makePaveText(float x1, float y1, float x2, float y2, std::string text){
  TPaveText* pavetxt=new TPaveText(x1, y1,
				   x2, y2
				   ,"NDC");
  pavetxt->SetFillStyle(0);
  pavetxt->SetBorderSize(0.);
  pavetxt->AddText(text.c_str());
  return (TPaveText*)pavetxt;
}


TLine* makeTLine(float x1, float y1, float x2, float y2){
  TLine* theline=new TLine(x1,y1,x2,y2);
  theline->SetLineStyle(7);  
  theline->SetLineWidth(1); 
  theline->SetLineColor(kBlack);
  return (TLine*)theline;
}

const float ytitlesize=0.035, xtitlesize=0.035;
const float ytitleoffset=1.1, xtitleoffset=1.05;
const float ylabelsize=0.03, xlabelsize=0.03;
//const float titlesize=, titleoffset=; 
void setHistLabels( TH1* spectra) {
  spectra->GetYaxis()->SetTitle(yaxtitle.c_str());
  spectra->GetYaxis()->SetTitleSize(ytitlesize);
  spectra->GetYaxis()->SetTitleOffset(ytitleoffset);
  spectra->GetYaxis()->SetLabelSize(ylabelsize);
  
  spectra->GetXaxis()->SetTitle(xaxtitle.c_str());
  spectra->GetXaxis()->SetTitleSize(xtitlesize);
  spectra->GetXaxis()->SetLabelSize(xlabelsize);

  spectra->SetTitle("");
  
  return;
}

void setHistLabels( TH1* spectra,std::string xtitle, std::string ytitle) {
  spectra->GetYaxis()->SetTitle(ytitle.c_str());
  spectra->GetYaxis()->SetTitleSize(ytitlesize+.005);
  spectra->GetYaxis()->SetTitleOffset(ytitleoffset);
  spectra->GetYaxis()->SetLabelSize(ylabelsize+.005);
  
  spectra->GetXaxis()->SetTitle(xtitle.c_str());
  spectra->GetXaxis()->SetTitleSize(xtitlesize+.005);
  spectra->GetXaxis()->SetLabelSize(xlabelsize+.005);

  spectra->SetTitle("");
  
  return;
}
const float matztitlesize=0.045, matytitlesize=0.045, matxtitlesize=0.045;
const float matztitleoffset=1.1, matytitleoffset=.98, matxtitleoffset=1.10;
const float matzlabelsize=0.045,  matylabelsize=0.04,  matxlabelsize=0.04;
const float matzlabeloffset=0.99;
void setHistLabels( TH2* matrix, std::string matyaxtitle="", std::string matxaxtitle=""){//, std::string matzaxtitle="") {
  //std::cout<<"asserting false"<<std::endl;assert(false);
  matrix->GetYaxis()->SetTitle(matyaxtitle.c_str());
  matrix->GetYaxis()->SetTitleSize(matytitlesize);
  matrix->GetYaxis()->SetTitleOffset(matytitleoffset);
  matrix->GetYaxis()->SetLabelSize(matylabelsize);
  
  matrix->GetXaxis()->SetTitle(matxaxtitle.c_str());
  matrix->GetXaxis()->SetTitleSize(matxtitlesize);
  matrix->GetXaxis()->SetLabelSize(matxlabelsize);

  //matrix->GetZaxis()->SetTitle(matzaxtitle.c_str());
  matrix->GetZaxis()->SetTitleSize(matztitlesize);
  matrix->GetZaxis()->SetLabelSize(matzlabelsize);
  //matrix->GetZaxis()->SetLabelOffset(matzlabeloffset);

  matrix->SetTitle("");
  
  return;
}


const float rat_ytitlesize=0.05, rat_xtitlesize=0.045;
const float rat_ytitleoffset=.90, rat_xtitleoffset=1.0;
const float rat_ylabelsize=0.05,  rat_xlabelsize=0.045;
void setRatioHistLabels( TH1* ratio, std::string yaxratiotitle) {
  ratio->GetYaxis()->SetTitle(yaxratiotitle.c_str());  ratio->GetYaxis()->CenterTitle(true);
  ratio->GetYaxis()->SetTitleSize  (rat_ytitlesize);
  ratio->GetYaxis()->SetTitleOffset(rat_ytitleoffset);
  ratio->GetYaxis()->SetLabelSize  (rat_ylabelsize);
  
  ratio->GetXaxis()->SetTitle    (xaxtitle.c_str());
  ratio->GetXaxis()->SetTitleSize(rat_xtitlesize);
  ratio->GetXaxis()->SetTitleOffset(rat_xtitleoffset);
  ratio->GetXaxis()->SetLabelSize(rat_xlabelsize);

  ratio->SetTitle("");
  
  return;
}

void styleLumiErrHist(TH1* hlumierr){
  hlumierr->SetMarkerColorAlpha(hlumierr->GetMarkerColor(),0.0);
  hlumierr->SetLineWidth(0);
  hlumierr->SetFillColor(kAzure);
  hlumierr->SetFillStyle(3354);
  return;
}

void applyNPCorrs(TF1* f, TH1* h){
  int nbins=h->GetNbinsX();
  for(int i=1; i<=nbins;i++){
    float nuval=f->Eval(h->GetBinCenter(i))*h->GetBinContent(i);
    float nuerr=f->Eval(h->GetBinCenter(i))*h->GetBinError(i);
    h->SetBinContent(i,nuval);
    h->SetBinError(i,nuerr);    
  }
  return;
}


// this func should call the only NP file that's relevant and apply either the normal ones, or the sysup/down version
void applyNPCorrs(TH1* h, int etabin, std::string sysdir=""){
  TFile* fNPCorr=TFile::Open( (NPC_DIR+NPC_FILE+".root").c_str() , "READ");
  std::string NPname="fNPC_AVG_R4_etabin"+std::to_string(etabin);
  if(sysdir=="up") NPname+="_up";
  else if(sysdir=="down")NPname+="_down";    
  TF1* f=(TF1*)fNPCorr->Get(NPname.c_str());
  
  int nbins=h->GetNbinsX();
  for(int i=1; i<=nbins;i++){
    float nuval=f->Eval(h->GetBinCenter(i))*h->GetBinContent(i);
    float nuerr=f->Eval(h->GetBinCenter(i))*h->GetBinError(i);
    h->SetBinContent(i,nuval);
    h->SetBinError(i,nuerr);    
  }
  return;
}





void printetabinerrormessage(){
  
  std::cout<<"----------------------------- ERROR ---------------------------"<<std::endl;
  std::cout<<"----------------------------- ERROR ---------------------------"<<std::endl;
  std::cout<<"----------------------------- ERROR ---------------------------"<<std::endl;
  std::cout<<"----------------------------- ERROR ---------------------------"<<std::endl;
  std::cout<<"----------------------------- ERROR ---------------------------"<<std::endl;
  std::cout<<"wrong # of etabin strings, code me better or add/subtract more."<<std::endl;
  std::cout<<"----------------------------- ERROR ---------------------------"<<std::endl;
  std::cout<<"----------------------------- ERROR ---------------------------"<<std::endl;
  std::cout<<"----------------------------- ERROR ---------------------------"<<std::endl;
  std::cout<<"----------------------------- ERROR ---------------------------"<<std::endl;
  
  return;
}



//take in hist w/ error bars, set bin content to 1 so error bars are from that value
void setOneBinContent(TH1* hrat){  
  for(int i=1; i<=hrat->GetNbinsX();i++)
    hrat->SetBinContent(i,1.);
  return;
}

void readBinContent(TH1* hrat){  
  std::cout<<std::endl;
  std::cout<<"reading bin content of "<<hrat->GetName()<<std::endl;  
  for(int i=1; i<=hrat->GetNbinsX();i++){
    std::cout<<"bin #"<<i<<", "<<hrat->GetBinLowEdge(i)<<" GeV < jtpt < "<<hrat->GetBinLowEdge(i)+hrat->GetBinWidth(i)<<std::endl;
    std::cout<<"bin content is ="<<hrat->GetBinContent(i)<<std::endl;
  }
  return;
}


//takes in ratio hist, + systematics ratio hist, sets bin content s.t. the drawing make it look like the error is from 1
//errors on bin contents don't matter for hists made in this way
void setOneBinContent_errHist(TH1* hrat, TH1* syshrat){  
  for(int i=1; i<=hrat->GetNbinsX();i++){
    float diff=hrat->GetBinContent(i)-syshrat->GetBinContent(i);
    float newval=1.+diff;
    syshrat->SetBinContent(i,newval);
  }
  return;
}



void multiplyBinWidth(TH1* h){
  for(int i=1; i<=h->GetNbinsX();i++){
    float val=h->GetBinContent(i);
    float valerr=h->GetBinError(i);
    val*=h->GetBinWidth(i);
    valerr*=h->GetBinWidth(i);
    h->SetBinContent(i,val);
    h->SetBinError(i,valerr);
  }
  return;
}
void divideBinWidth(TH1* h){
  for(int i=1; i<=h->GetNbinsX();i++){
    float val=h->GetBinContent(i);
    float valerr=h->GetBinError(i);
    val/=h->GetBinWidth(i);
    valerr/=h->GetBinWidth(i);
    h->SetBinContent(i,val);
    h->SetBinError(i,valerr);
  }
  return;
}





float getnonzeromin(TH1* th1){
  float nonzeromin=1.e+40;
  int nbinsx=th1->GetNbinsX();
  for(int i=1;i<=nbinsx;i++){
    float content=th1->GetBinContent(i);
    if(!(content>0.)&&!(content<0.))//check for zero
      continue;
    else if(content < nonzeromin)//check that new content is less than current minium
      nonzeromin=content;
    else continue;//if the content is greater than current minimum
  }
  return nonzeromin;
    
}


float getnonzeromin(TH2* th2){
  float nonzeromin=1.e+40;
  int nbinsx=th2->GetNbinsX();
  int nbinsy=th2->GetNbinsY();
  for(int i=1;i<=nbinsx;i++)
    for(int j=1;j<=nbinsy;j++){
      float content=th2->GetBinContent(i,j);
      if(!(content>0.)&&!(content<0.))
	continue;
      else if(content < nonzeromin)
	nonzeromin=content;
      else continue;
    }
  return nonzeromin;
    
}

void calculateCorrRatioErrs(TH1* hrat, TH1* hnum, TH1* hden, float corrCoeff=0.5){
  bool funcDebug=false;
  if(hrat->GetNbinsX()!=hnum->GetNbinsX()){
    std::cout<<"in calculateCorrRatioErrs, ratio hist and numerator hist don't have same bins. exit."<<std::endl;
    return;
  }
  else if(hnum->GetNbinsX()!=hden->GetNbinsX()){
    std::cout<<"in calculateCorrRatioErrs, denominator hist and numerator hist don't have same bins. exit."<<std::endl;
    return;
  }
  
  for(int j=1; j<=hrat->GetNbinsX();j++){
    float val=hrat->GetBinContent(j);
    if(funcDebug)std::cout<<std::endl;
    float varA=hnum->GetBinError(j)/hnum->GetBinContent(j);
    varA*=varA;
    if(funcDebug)std::cout <<"varA="<<varA<<std::endl;
    float varB=hden->GetBinError(j)/hden->GetBinContent(j);
    varB*=varB;
    if(funcDebug)std::cout <<"varB="<<varB<<std::endl;
    float varAB=-2.*(hnum->GetBinError(j)/hnum->GetBinContent(j))*(hden->GetBinError(j)/hden->GetBinContent(j))*corrCoeff;
    if(funcDebug)std::cout <<"varAB="<<varAB<<std::endl;
    float valerr=varA+varB+varAB;
    if(funcDebug)std::cout <<"varA+varB+varAB="<<valerr<<std::endl;
    if(valerr<0.)std::cout<<"warning corr err is negative before sqrt"<<std::endl;
    valerr=sqrt(valerr);
    if(funcDebug)std::cout <<"sqrt(valerr)="<<valerr<<std::endl;
    valerr*=val;
    if(funcDebug)std::cout <<"val*sqrt(valerr)="<<valerr<<std::endl;
    if(funcDebug)std::cout<<"final stat unc(maybe?) on ratio bin j="<<j<<" is ="<<valerr<<std::endl;      
    if(funcDebug)std::cout<<"original stat unc on ratio bin j="<<j<<" = "<< hrat->GetBinError(j)/sqrt(2.)<<std::endl;
    //if(valerr==valerr && valerr!=valerr){
    if(!(hrat->GetBinContent(j)>0.) && !(hrat->GetBinContent(j)<0.)){
      std::cout<<"zero bin content for bin j="<<j<<". bin error is set to 0."<<std::endl;
      hrat->SetBinError(j,0.);
    }
    else hrat->SetBinError(j,valerr);            
  }
  
  return;
}





//returns binning array, puts # of bins in nbins
double* setBinning_etabin(int etabinint=0, int* nbins=NULL    ){
  bool funcDebug=true;
  if(funcDebug)std::cout<<std::endl<<"in setBinning_etabin"<<std::endl<<std::endl;
  
  double* binarray=NULL;
  binarray=(double*)(merged_SMP_ptbins[etabinint].data());
  *(nbins)=(int)(merged_SMP_ptbins[etabinint].size()-1);
  
  if(funcDebug)std::cout<<std::endl<<"setBinning_etabin done, exiting."<<std::endl<<std::endl;
  return binarray;
  
}


void makeTotRelSystUncRatio(std::string dir="up",TH1* statunc=NULL, std::vector<TH1*> systhists={0}, TH1* targ=NULL){
  bool funcDebug=true;
  if(funcDebug)std::cout<<std::endl<<"in makeTotRelSystUncRatio"<<std::endl<<std::endl;
  int nsysthists=systhists.size();
  int nbins=statunc->GetNbinsX();
  float updownwgt=0.;

  if(dir=="up")updownwgt=1.;
  else if(dir=="down")updownwgt=-1.;
  else {
    std::cout<<"error, string dir should equal \"up\" or \"down\". exit makeTotRelSystUncRatio."<<std::endl;
    return;
  }

  for(int j=1; j<=nbins; j++){
    for(int i=0; i<= nsysthists; i++){
      if(i==nsysthists){
	targ->AddBinContent(j,pow(statunc->GetBinError(j),2));
      }
      else{
	targ->AddBinContent(j,pow(systhists[i]->GetBinContent(j)-1.,2));
      }
    }//end loop over syst hists
    targ->SetBinContent(j,updownwgt*sqrt(targ->GetBinContent(j)) + 1.);
  }//end loop over bins
  return;
}


//NOTE: BECAREFUL WITH ME
// for a ratio, A/B, where A has several, indep., asymmetric sources of unc. and so does B
// to calculate the given error in e.g. the "up" direction for A/B, one must give it the (A/B)_Asys1up, (A/B)_Asys2up ... ratios,
// and give it the (A/B)_Bsys1down, (A/B)_Bsys2down ... ratios. 
// this is b.c. (A/B)_Bsys1down represents the quantity B *decreasing* by Bsys1down, and so (A/B) naturally *increases* because Bsys1down.
void makeTotSystUncRatio(std::string dir="up", TH1* ratio=NULL, TH1* statunc=NULL, std::vector<TH1*> systhists={0}, TH1* targ=NULL){
  bool funcDebug=false;
  std::cout<<std::endl<<"in makeTotSystUncRatio"<<std::endl<<std::endl;
  int nsysthists=systhists.size();
  int nbins=statunc->GetNbinsX();
  float updownwgt=0.;
  
  if(dir=="up")updownwgt=1.;
  else if(dir=="down")updownwgt=-1.;
  else {
    std::cout<<"error, string dir should equal \"up\" or \"down\". exit makeTotSystUncRatio."<<std::endl;
    return;
  }

  for(int j=1; j<=nbins; j++){
    if(funcDebug)std::cout<<std::endl<<"BEFORE: targ->GetBinContent("<<j<<")="<<targ->GetBinContent(j)<<std::endl;
    for(int i=0; i<= nsysthists; i++){
      if(i==nsysthists){
	targ->AddBinContent(j,pow(statunc->GetBinError(j),2));
      }
      else{

	if(funcDebug){
	  float diff=(systhists[i]->GetBinContent(j)-ratio->GetBinContent(j));		
	  if(dir=="up"){
	    if(diff<0.){
	      std::cout<<"WARNING!"<<std::endl;	    
	      systhists[i]->Print("base");
	      std::cout<<"systhists[i]->GetBinContent("<<j<<")="<<systhists[i]->GetBinContent(j)<<std::endl;
	      std::cout<<"       ratio->GetBinContent("<<j<<")="<<ratio->GetBinContent(j)<<std::endl;
	      std::cout<<"diff="<<diff<<std::endl;
	    }
	  }
	  
	  if(dir=="down"){
	    if(diff>0.){
	      std::cout<<"WARNING!"<<std::endl;	    
	      systhists[i]->Print("base");
	      std::cout<<"systhists[i]->GetBinContent("<<j<<")="<<systhists[i]->GetBinContent(j)<<std::endl;
	      std::cout<<"       ratio->GetBinContent("<<j<<")="<<ratio->GetBinContent(j)<<std::endl;
	      std::cout<<"diff="<<diff<<std::endl;
	      std::cout<<"WARNING!"<<std::endl;
	    }
	  }
	}
	
	targ->AddBinContent(j,pow(
				  (systhists[i]->GetBinContent(j)-ratio->GetBinContent(j))
				  ,2)
			    );
      }
    }//end loop over syst hists
    if(funcDebug)std::cout<<"SUM UNC SQ: targ->GetBinContent("<<j<<")="<<targ->GetBinContent(j)<<std::endl;    
    if(funcDebug)std::cout<<"SQRT(SUM UNC SQ): targ->GetBinContent("<<j<<")="<<sqrt(targ->GetBinContent(j))<<std::endl;    
    targ->SetBinContent(j,updownwgt*sqrt(targ->GetBinContent(j)) + ratio->GetBinContent(j));
    if(funcDebug)std::cout<<"AFTER:  targ->GetBinContent("<<j<<")="<<targ->GetBinContent(j)<<std::endl;
  }//end loop over bins
  return;
}




TH1D* make_fNLOSpectra(  std::string targPDF, std::string scalechoice, std::string orderint, 
		         int etabin, int spectratype ,
			 bool rebin, std::vector<double> bins, 
			 bool applyNPCs , std::string NPsysdir ){
  bool funcDebug=true;
  if(funcDebug)
    std::cout<<"running make_fNLOSpectra!"<<std::endl;   
  
  std::string thyfilename=FNLO_DIR+"R04/fout_"+targPDF+"_"+scalechoice+".root";
  if(funcDebug)std::cout<<"grabbing theory hist(s) from thyfilename =="<<thyfilename<<std::endl;
  
  TFile* thyfile=TFile::Open(thyfilename.c_str(),"READ");
  std::string hname="h"+orderint+"100"+std::to_string(etabin+1)+"0"+std::to_string(spectratype);
  if(spectratype==8 || spectratype==9)   hname+="_spectra";//scale error spectra name
  if(spectratype==1 || spectratype==2)   hname+="_spectra";//pdf error spectra name

  std::string newhname=targPDF;
  if(     spectratype==8)newhname+="_MUsysdown";
  else if(spectratype==9)newhname+="_MUsysup";  
  else if(spectratype==1)newhname+="_PDFsysdown";  
  else if(spectratype==2)newhname+="_PDFsysup";  
  if(NPsysdir!="")newhname+="_NPsys"+NPsysdir;  
  newhname+="_ybin"+std::to_string(etabin);

  TH1D* mcspectra=(TH1D*)(
			  (
			   (TH1D*)thyfile->Get(hname.c_str()) 
			   )->Clone( newhname.c_str()) 
			  );  


//  for(int i=1; i<=mcspectra->GetNbinsX();i++){//zero the stat error on the hist. 1) the errs are sqrt(content) because that's what root does, and these are way too big and 2) the computation time / NEvents is so high that it's basically negligible. 
//    mcspectra->SetBinError(i, 1.e-30);
//  }
  mcspectra->Scale(1./1000.);
  multiplyBinWidth(mcspectra);    
  if(applyNPCs) applyNPCorrs(mcspectra,etabin, NPsysdir);
  if(rebin)
    mcspectra=(TH1D*)mcspectra->TH1::Rebin( (bins.size()-1), ((std::string)mcspectra->GetName()+"_rebin").c_str() , (double*)bins.data());
  divideBinWidth(mcspectra);    
  if(funcDebug)mcspectra->Print("base");
  
  return (TH1D*)mcspectra;
}

std::string replace_underscores(std::string targstr){
  bool funcDebug=true;
  std::string changethis=targstr;
  if(funcDebug)std::cout<<"removing underscores from string="<<changethis<<std::endl;
  while(changethis.find("_")!=std::string::npos){
    size_t us_pos=changethis.find("_");
    if(funcDebug)std::cout<<"underscore found at position us_pos="<<us_pos<<std::endl;
    changethis.replace(us_pos,1," ");
    if(funcDebug)std::cout<<"replacement made; now string="<<changethis<<std::endl;
  }
  
  return changethis;
}
