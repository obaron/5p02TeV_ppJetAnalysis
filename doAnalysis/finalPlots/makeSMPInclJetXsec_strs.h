//const std::string etaORy_str="y";
//const bool etaORy_str="#eta";
const std::string etaORy_str="#eta";

//// ETA OR YBIN STRINGS FOR FINAL PLOTTING MACRO --> STILL CALLED 'etabin_strs' CAUSE IM LAZY
const std::string etabin_strs[]={
  "0.0 < #||{"+etaORy_str+"} < 0.5",  
  "0.5 < #||{"+etaORy_str+"} < 1.0",
  "1.0 < #||{"+etaORy_str+"} < 1.5",
  "1.5 < #||{"+etaORy_str+"} < 2.0"
};
const int n_etabin_strs=sizeof(etabin_strs)/sizeof(std::string);

//this array always ybin strs
const std::string const_ybin_strs[]={
  "0.0 < #||{y} < 0.5",  
  "0.5 < #||{y} < 1.0",
  "1.0 < #||{y} < 1.5",
  "1.5 < #||{y} < 2.0"
};
const int n_const_ybin_strs=sizeof(const_ybin_strs)/sizeof(std::string);

//this array always eta strs
const std::string const_etabin_strs[]={
  "0.0 < #||{#eta} < 0.5",  
  "0.5 < #||{#eta} < 1.0",
  "1.0 < #||{#eta} < 1.5",
  "1.5 < #||{#eta} < 2.0"
};
const int n_const_etabin_strs=sizeof(const_etabin_strs)/sizeof(std::string);


const std::string simpavetitle="#bf{CMS} #it{Simulation}                                                                                           (5.02 TeV)";
const std::string prelimpavetitle="#bf{CMS} #it{Preliminary}                                                                              27.4 pb^{-1} (5.02 TeV)";
const std::string simratpavetitle="#bf{CMS} #it{Simulation}                                                              (5.02 TeV)";
const std::string prelimratpavetitle="#bf{CMS} #it{Preliminary}                                                 27.4 pb^{-1} (5.02 TeV)";

const std::string yaxtitle="#frac{d^{2}#sigma}{d"+etaORy_str+" dp_{T}} [#frac{pb}{GeV}]";
const std::string xaxtitle="Jet p_{T} [GeV]";

const std::string sqrts="#sqrt{s} = 5.02 TeV";
const std::string jettype="anti-k_{T} PF Jets (R = 0.3)";
const std::string ptcuts="56 GeV < Jet p_{T} < 967 GeV";
const std::string ptcuts_lo="56 GeV < Jet p_{T} < ";
const std::string intlumi="L_{int} = 27.4 pb^{-1}";

const std::string scalechoice_murmufpt ="#mu_{r} = #mu_{f} = p_{T}^{Jet}";
const std::string scalechoice_murmufpt1="#mu_{r} = #mu_{f} = p_{T}^{Lead Jet}";
const std::string scalechoice_murmufHTp="#mu_{r} = #mu_{f} = #Sigma p_{T}^{parton}";
