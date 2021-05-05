//ETABIN TAGS, RELEVANT TO SYSTEMATICS STUFF
const std::string ETABIN_TAG_array[]={
  "00eta05",
  "05eta10",
  "10eta15",
  "15eta20"
};
const int ETABIN_TAG_Nstrs=sizeof(ETABIN_TAG_array)/sizeof(std::string);

const std::string YBIN_TAG_array[]={
  "00y05",
  "05y10",
  "10y15",
  "15y20"
};
const int YBIN_TAG_Nstrs=sizeof(YBIN_TAG_array)/sizeof(std::string);



// ------------------------------------------------------------------------------- //
// ----------------------  //// PY8 UNFOLDING RESULTS //// ----------------------- // 
// ------------------------------------------------------------------------------- //

//DATA, NOTE: JEC/KITER SYSTEMATICS IN THESE FILES
//ak3PFJets_wjtID_anabins_Bayes_PY8_FullRECO_07.11.19_SMPbins_etabin_3_LOMC_00eta05.pdf
const std::string PY8_UNFDIR_DATA   ="PY8unf/data/"; 
const std::string PY8_UNF_DATA_file_base="ak3PFJets_wjtID_anabins_Bayes_PY8_FullRECO_07.11.19_SMPbins_withJECsys_LOMC_";
const std::string PY8_UNFDIR_DATA_file_array[]={
  PY8_UNF_DATA_file_base+"00eta05",
  PY8_UNF_DATA_file_base+"05eta10",
  PY8_UNF_DATA_file_base+"10eta15",
  PY8_UNF_DATA_file_base+"15eta20" 
};
const std::string PY8_UNFDIR_DATA_shortdir_array[]={
  "YBIN0",
  "YBIN1",
  "YBIN2",
  "YBIN3"
};
const int PY8_UNFDIR_DATA_Nfiles=sizeof( PY8_UNFDIR_DATA_file_array )/sizeof(std::string);

//CLOSURE
const std::string PY8_UNFDIR_CLOSURE="PY8unf/closure/";

//ak3PFJets_wjtID_anabins_Bayes_Closure_PY8_FullRECO_09.30.20_SMPbins_LOMC_05eta10.root
const std::string PY8_UNF_CLOSURE_file_base="ak3PFJets_wjtID_anabins_Bayes_Closure_PY8_FullRECO_03.22.21_SMPbins_LOMC_";
const std::string PY8_UNFDIR_CLOSURE_file_array[]={
  PY8_UNF_CLOSURE_file_base+"00eta05",
  PY8_UNF_CLOSURE_file_base+"05eta10",
  PY8_UNF_CLOSURE_file_base+"10eta15",
  PY8_UNF_CLOSURE_file_base+"15eta20" 
};
const std::string PY8_UNFDIR_CLOSURE_shortdir_array[]={
  "YBIN0",
  "YBIN1",
  "YBIN2",
  "YBIN3"
};
const int PY8_UNFDIR_CLOSURE_Nfiles=sizeof( PY8_UNFDIR_CLOSURE_file_array )/sizeof(std::string);

//SYSTEMATICS
const std::string PY8_UNF_DATA_SYST_file_base=PY8_UNF_DATA_file_base;	//This should be OK
const std::string PY8_UNFDIR_DATA_SYST_file_array[]={ 
  PY8_UNF_DATA_SYST_file_base,
  PY8_UNF_DATA_SYST_file_base
};
const int   PY8_UNFDIR_DATA_SYST_Nfiles=(sizeof(   PY8_UNFDIR_DATA_SYST_file_array )/sizeof(std::string))*(ETABIN_TAG_Nstrs);//MULTIPLY BY # OF ETABINS



// ------------------------------------------------------------------------------- //
// ------------------- //// SMEARED NLO UNFOLDING RESULTS //// ------------------- // 
// ------------------------------------------------------------------------------- //

//DATA, NOTE: FILES w/ JEC/KITER SYSTEMATICS ARE USED HERE
const std::string NLO_UNFDIR_DATA   ="NLOunf/data/";
const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_01.05.21_Bayes_CT14NNLO_NLO_sigmu_murmufpt_SMPbins_withgenjety_wJERSFs_SMPbins_wPFMET0p3_semifinalv4_";
//"ak4PFJets_wjtID_anabins_01.05.21_Bayes_CT14NNLO_NLO_sigmu_murmufHTp_SMPbins_withgenjety_wJERSFs_SMPbins_wPFMET0p3_semifinalv4_";
const std::string NLO_UNFDIR_DATA_file_array[]={ 
  NLO_UNF_DATA_file_base+"JECsys_NLOMC_wNP_00eta05",
  NLO_UNF_DATA_file_base+"JECsys_NLOMC_wNP_05eta10",
  NLO_UNF_DATA_file_base+"JECsys_NLOMC_wNP_10eta15",
  NLO_UNF_DATA_file_base+"JECsys_NLOMC_wNP_15eta20"
};
const std::string NLO_UNFDIR_DATA_shortdir_array[]={ 
  "YBIN0",
  "YBIN1",
  "YBIN2",
  "YBIN3"
};
const int   NLO_UNFDIR_DATA_Nfiles=sizeof(   NLO_UNFDIR_DATA_file_array )/sizeof(std::string);

//CLOSURE
const std::string NLO_UNFDIR_CLOSURE="NLOunf/closure/";

const std::string NLO_UNF_CLOSURE_file_base="ak4PFJets_wjtID_anabins_01.05.21_Bayes_Closure_CT14NNLO_NLO_v4_sigmu_SMPbins_withjety_semifinalv4_REBIN_NODATACOVMAT_murmufHTp_NLOMC_wNP_";
const std::string NLO_UNFDIR_CLOSURE_file_array[]={ 
  NLO_UNF_CLOSURE_file_base+"00eta05",
  NLO_UNF_CLOSURE_file_base+"05eta10",
  NLO_UNF_CLOSURE_file_base+"10eta15",
  NLO_UNF_CLOSURE_file_base+"15eta20"
};
const std::string NLO_UNFDIR_CLOSURE_shortdir_array[]={ 
  "YBIN0",
  "YBIN1",
  "YBIN2",
  "YBIN3"
};
const int   NLO_UNFDIR_CLOSURE_Nfiles=sizeof(   NLO_UNFDIR_CLOSURE_file_array )/sizeof(std::string);

//DATA SYST, NOTE: FILES HAVE ETA STRING AT END REMOVED SO ETABIN MUST BE SPECIFIED IN SCRIPTS
const std::string NLO_UNF_DATA_SYST_file_base=NLO_UNF_DATA_file_base;
const std::string NLO_UNFDIR_DATA_SYST_file_array[]={ 
  NLO_UNF_DATA_SYST_file_base+"JECsys_NLOMC_wNP_",
  NLO_UNF_DATA_SYST_file_base+"JERsys_NLOMC_wNP_",
  NLO_UNF_DATA_SYST_file_base+"PDFsysupdown_NLOMC_wNP_",//,
  //NLO_UNF_DATA_SYST_file_base+"PDF12_NLOMC_wNP_",//REMAKE THESE 3? IS THIS NEEDED?
  NLO_UNF_DATA_SYST_file_base+"NPsysupdown_NLOMC_wNP_"
  //NLO_UNF_DATA_SYST_file_base+"NPsys12_NLOMC_wNP_"
};
const int   NLO_UNFDIR_DATA_SYST_Nfiles=(sizeof(   NLO_UNFDIR_DATA_SYST_file_array )/sizeof(std::string))*(ETABIN_TAG_Nstrs);//MULTIPLY BY # OF ETABINS



// ------------------------------------------------------------------------------- //
// ---------------------------  //// JERS W PY8 //// ----------------------------- // 
// ------------------------------------------------------------------------------- //
const std::string JERDIR_MC  ="JER/";
const std::string JERDIR_MC_file_array[]={ 
  "ak3PF_PY8JER_00eta05_03.22.21_sigmu",
  "ak3PF_PY8JER_05eta10_03.22.21_sigmu",
  "ak3PF_PY8JER_10eta15_03.22.21_sigmu",
  "ak3PF_PY8JER_15eta20_03.22.21_sigmu"
};
const std::string JERDIR_MC_shortdir_array[]={ 
  "YBIN0",
  "YBIN1",
  "YBIN2",
  "YBIN3"
};
const int   JERDIR_MC_Nfiles=sizeof(   JERDIR_MC_file_array )/sizeof(std::string);



// ------------------------------------------------------------------------------- //
// -------------------------  //// OTHER MISC FILES ////  ------------------------ // 
// ------------------------------------------------------------------------------- //
/// /MC VTX WGTS
const std::string VTXWDIR_MC  ="PY8vzwgts/";
const std::string VTXWDIR_MC_file_array[]={ 
  "Py8_vzEvtWeights_baryshift_neg"
};
const std::string VTXWDIR_MC_shortdir_array[]={ 
  ""
};
const int  VTXWDIR_MC_Nfiles=sizeof(  VTXWDIR_MC_file_array )/sizeof(std::string);



//// JET PLOTS QA
const std::string JETQA  ="jetPlots/";
const std::string JETQA_file_array[]={ 
  "ak3PF_HPtJetTrig_semiOffPy8_00eta20_noMB_wJetID_jetPlots"
  //"ak4PF_HPtJetTrig_semiOffPy8_00eta20_03.18.20_semifinalv3_jetPlots"
};
const std::string JETQA_shortdir_array[]={ 
  ""
};
const int       JETQA_Nfiles=sizeof(       JETQA_file_array )/sizeof(std::string);

//// JET ID QA
const std::string JETIDQA  ="JetIDHIN/";
const std::string JETIDQA_file_array[]={ 
  "ak4PF_HPtJetTrig_00eta20_01.05.21_semifinalv4_jetIDPlots",
  "ak4PF_Py8_CUETP8M1_00eta20_01.05.21_semifinalv4_jetIDPlots"
  //"ak4PF_HPtJetTrig_00eta20_03.18.20_semifinalv3_jetIDPlots",
  //"ak4PF_Py8_CUETP8M1_00eta20_03.18.20_semifinalv3_jetIDPlots"
};
const std::string JETIDQA_shortdir_array[]={ 
  "DATA",
  "PY8"
};
const int     JETIDQA_Nfiles=sizeof(     JETIDQA_file_array )/sizeof(std::string);

//// JET TRIG QA
const std::string JETTRIGQA  ="jetTrigEff/";
const std::string JETTRIGQA_file_array[]={ 
  "ak4PF_HPtJetTrig_00eta51_01.05.21_HLT60Eff_useHLT40Ref_semifinalv4_jetTrigEff",
  "ak4PF_HPtJetTrig_00eta51_01.05.21_HLT80Eff_useHLT60Ref_semifinalv4_jetTrigEff"
//  "ak4PF_HPtJetTrig_00eta51_11.26.19_HLT60Eff_useHLT40Ref_semifinalv2_LowHLT40Thresh_jetTrigEff",//TIME TO REMAKE THIS FILE?
//  "ak4PF_HPtJetTrig_00eta51_11.26.19_HLT80Eff_useHLT60Ref_semifinalv2_LowHLT40Thresh_jetTrigEff"//TIME TO REMAKE THIS FILE?
};
const std::string JETTRIGQA_shortdir_array[]={ 
  "HLT60",
  "HLT80"
};
const int   JETTRIGQA_Nfiles=sizeof(   JETTRIGQA_file_array )/sizeof(std::string);


//// EVENT COUNTS
const std::string EVTCOUNTS="evtCounts/";
const std::string EVTCOUNTS_file="ak4PF_HPtJetTrig_semiOffPy8_00eta20_01.05.21_semifinalv4_Jet80_LowJets_PY8_evtCounts";

//// NON PERTURBATIVE CORRECTIONS
const std::string NPC_DIR="NLOSpectra_NPCs/NPCorr5TeV/";
const std::string NPC_FILE="NLOpNP_InclusiveJets5TeV_fromJohn_refit";//PYTHIA8, tune ??? WRONG FILE?!?! DOUBLE CHECK

//// FASTNLO FILES
const std::string FNLO_DIR="NLOSpectra_NPCs/fNLOJetsSpectra/";

const std::string CT14nnlo_muEQpt ="R04/fout_CT14nnlo_murmufpt_v4"; //where fact/renorm scale is: the jet pt for every jet
const std::string CT14nnlo_muEQpt1="R04/fout_CT14nnlo_murmufpt1_v4"; //where fact/renorm scale is: the pt from the lead jet of the event, for each jet in the event
const std::string CT14nnlo_muEQHTp="R04/fout_CT14nnlo_murmufHTp_v4"; //where fact/renorm scale is: the scalar sum of pt of all partons in the event, for each jet in the event

//const std::string CT14nnlo_muEQpt ="R04/fout_CT14nnlo_murmufpt_v4"; //where fact/renorm scale is: the jet pt for every jet
//const std::string CT14nnlo_muEQpt1="R04/fout_CT14nnlo_murmufpt1_v4"; //where fact/renorm scale is: the pt from the lead jet of the event, for each jet in the event
//const std::string CT14nnlo_muEQHTp="R04/fout_CT14nnlo_murmufHTp_v4"; //where fact/renorm scale is: the scalar sum of pt of all partons in the event, for each jet in the event

//const std::string CT14nnlo=CT14nnlo_muEQpt;
//const std::string CT14nnlo=CT14nnlo_muEQpt1;
const std::string CT14nnlo=CT14nnlo_muEQHTp;



const std::string NNPDFnnlo30_as121_muEQpt ="R04/fout_NNPDFnnlo30_as121_murmufpt_v4"; 
const std::string NNPDFnnlo30_as121_muEQHTp="R04/fout_NNPDFnnlo30_as121_murmufHTp_v4";
const std::string NNPDFnnlo31_as120_muEQpt ="R04/fout_NNPDFnnlo31_as120_murmufpt_v4";
const std::string NNPDFnnlo31_as120_muEQHTp="R04/fout_NNPDFnnlo31_as120_murmufHTp_v4";
const std::string NNPDFnnlo31_as122_muEQpt ="R04/fout_NNPDFnnlo31_as122_murmufpt_v4"; 
const std::string NNPDFnnlo31_as122_muEQHTp="R04/fout_NNPDFnnlo31_as122_murmufHTp_v4";


//const std::string NNPDFnnlo=NNPDFnnlo_muEQpt;
//const std::string NNPDFnnlo=NNPDFnnlo_muEQpt1;
//const std::string NNPDFnnlo=NNPDFnnlo_muEQHTp;















//// ------------------------------------------------------------------------------- //
//// ------------------  //// STUFF FOR RUNNING COMPARISONS //// ------------------- // 
//// ------------------------------------------------------------------------------- //
//const std::string NLO_UNFDIR_DATA_JOHNS_BINS   ="NLOunf/MY_RESULTS_JOHNS_BINS/";
//const std::string NLO_UNF_DATA_JOHNS_BINS_file_base="ak4PFJets_wjtID_anabins_08.06.19_Bayes_NNPDF_NLO_sigmu_noJERscales_withLumiCorr_JOHNbins_semifinal_JECsys_NLOMC_wNP_";
//const std::string NLO_UNFDIR_DATA_JOHNS_BINS_file_array[]={ 
//  NLO_UNF_DATA_JOHNS_BINS_file_base+"00eta05",
//  NLO_UNF_DATA_JOHNS_BINS_file_base+"05eta10",
//  NLO_UNF_DATA_JOHNS_BINS_file_base+"10eta15",
//  NLO_UNF_DATA_JOHNS_BINS_file_base+"15eta20"
//};
//const int   NLO_UNFDIR_DATA_JOHNS_BINS_Nfiles=sizeof(   NLO_UNFDIR_DATA_JOHNS_BINS_file_array )/sizeof(std::string);
//
////COMPARISON W JOHNS RESULTS
////const std::string NLO_UNFDIR_JOHNS_DATA="smearNLO_unfolding/comparison/JOHNS_DATA_OLDJEC/";//tail discrepency
////const std::string MEAS_JOHNS_DATA_SPECTRA="mergeHistos.root";
//const std::string NLO_UNF_JOHNS_DATA_SPECTRA="allUnfoldedPlots.root";
//const std::string NLO_UNF_JOHNS_DATA_RATIOS="allUnfoldedRatios.root";
////const std::string NLO_UNFDIR_JOHNS_DATA="smearNLO_unfolding/comparison/JOHNS_DATA_1/";//spike in me/john ratio at low pt
////const std::string MEAS_JOHNS_DATA_SPECTRA="mergeHistos_newJEC.root";
//const std::string NLO_UNFDIR_JOHNS_DATA="NLOunf/comparison/JOHNS_DATA_2/";
//const std::string MEAS_JOHNS_DATA_SPECTRA="makeSpectra.root";//latest, lets see









// ------------------------------------------------------------------------------- //
// -------------------------------  //// OLD //// -------------------------------- //
// ------------------------------------------------------------------------------- //
//const std::string NLO_UNF_CLOSURE_file_base="ak4PFJets_wjtID_anabins_06.25.19_Bayes_Closure_NNPDF_NLO_sigmu_noJERscales_semifinal_NLOMC_wNP_";//REMAKE THESE FILES

  ////"ak4PFJets_wjtID_anabins_Bayes_PY8_FullRECO_11.26.19_SMPbins_withJECsysv2_SMPbins_ptLo56_withLumiCorr_semifinalv2_LowHLT40Thresh_LOMC_";
//const std::string PY8_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_Bayes_PY8_FullRECO_03.18.20_SMPbins_withJECsysv2_SMPbins_ptLo56_withLumiCorr_semifinalv3_LOMC_";
//const std::string PY8_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_PY8_FullRECO_SMPbins_withJECsysv2_withjety_SMPbins_semifinalv3_LOMC_";

////ak4PFJets_wjtID_anabins_11.26.19_Bayes_NNPDF_NLO_sigmu_noJERscales_withLumiCorr_SMPbins_withJECsysv2_ptLo56_semifinalv2_LowHLT40Thresh_JECsysv2_NLOMC_wNP_";
//ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v2_sigmu_noJERscales_SMPbins_withjety_ptLo56_semifinalv3_TEST_JECsys_NLOMC_wNP_00eta05
//const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v2_sigmu_noJERscales_SMPbins_withjety_ptLo56_semifinalv3_TEST_JECsys_NLOMC_wNP_"; 
//const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v2_sigmu_noJERscales_SMPbins_withjety_ptLo56_semifinalv3_TEST_"; 
//const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v2_sigmu_noJERscales_SMPbins_withjety_ptLo56_semifinalv3_TEST_"; 
//const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v2_sigmu_noJERscales_SMPbins_withjety_ptLo56_semifinalv3_JOHNSBINS_NODATACOVMAT_TEST_"; 
//const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v2_sigmu_noJERscales_SMPbins_withjety_ptLo56_semifinalv3_REBIN_NODATACOVMAT_TEST_"; 
//const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v3_sigmu_noJERscales_SMPbins_withjety_ptLo56_semifinalv3_REBIN_NODATACOVMAT_murmufpt1_TEST_";//where fact/renorm scale is the lead jet pt for jets of entire event
//const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v3_sigmu_noJERscales_SMPbins_withjety_ptLo56_semifinalv3_REBIN_NODATACOVMAT_murmufpt_TEST_"; //where fact/renorm scale is the jet pt for every jet
//const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v3_sigmu_SMPbins_withjety_semifinalv3_REBIN_NODATACOVMAT_murmufpt_"; //where fact/renorm scale is the jet pt for every jet
//const std::string NLO_UNF_DATA_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v3_sigmu_SMPbins_withjety_semifinalv3_REBIN_NODATACOVMAT_murmufpt1_"; //where fact/renorm scale is the lead jet pt for every jet

////"ak4PFJets_wjtID_anabins_11.26.19_Bayes_NNPDF_NLO_sigmu_noJERscales_withLumiCorr_SMPbins_withJECsysv2_ptLo56_semifinalv2_LowHLT40Thresh_";
//const std::string NLO_UNF_DATA_SYST_file_base="ak4PFJets_wjtID_anabins_03.18.20_Bayes_CT14NNLO_NLO_v2_sigmu_noJERscales_SMPbins_withjety_ptLo56_semifinalv3_TEST_REBIN_NODATACOVMAT_";

  //"ak4PF_HPtJetTrig_semiOffPy8_00eta20_11.26.19_SMPbins_wJECsysv2_withLumiCorr_semifinalv2_jetPlots"
  //"ak4PF_HPtJetTrig_semiOffPy8_00eta20_11.26.19_SMPbins_wJECsysv2_withLumiCorr_semifinalv2_LowHLT40Thresh_jetPlots"//TIME TO REMAKE THIS FILE
  //"ak4PF_HPtJetTrig_00eta20_11.26.19_SMPbins_wJECsysv2_withLumiCorr_semifinalv2_jetIDPlots",
  //  "ak4PF_HPtJetTrig_00eta20_11.26.19_SMPbins_wJECsysv2_withLumiCorr_semifinalv2_LowHLT40Thresh_jetIDPlots",//TIME TO REMAKE THIS FILE
  //  "ak4PF_Py8_CUETP8M1_00eta20_06.25.19_SMPbins_semifinal_jetIDPlots"//TIME TO REMAKE THIS FILE



//const std::string NPC_FILE="NLOpNP_InclusiveJets5TeV";
//const std::string NPC_FILE="NLOpNP_InclusiveJets5TeV_fromJohn";
//const std::string NPC_FILE="";//HERWIG7, tune CH2 [see GEN-19-001 PAS]


//const int Nfiles=sizeof(file_array)/sizeof(std::string);
  //"ak4PF_HPtJetTrig_semiOffPy8_00eta20_11.26.19_SMPbins_wJECsysv2_withLumiCorr_semifinalv2_jetPlots"
