

//// PY8 UNFOLDING RESULTS
//DATA
const std::string PY8_UNFDIR_DATA   ="PY8_unfolding/data/";
const std::string PY8_UNFDIR_DATA_file_array[]={
  "ak3PFJets_wjtID_anabins_Bayes_PY8_FullRECO_07.11.19_SMPbins_etabin_3_LOMC_00eta05",
  "ak3PFJets_wjtID_anabins_Bayes_PY8_FullRECO_07.11.19_SMPbins_etabin_3_LOMC_05eta10",
  "ak3PFJets_wjtID_anabins_Bayes_PY8_FullRECO_07.11.19_SMPbins_etabin_3_LOMC_10eta15",
  "ak3PFJets_wjtID_anabins_Bayes_PY8_FullRECO_07.11.19_SMPbins_etabin_3_LOMC_15eta20"
};
const int PY8_UNFDIR_DATA_Nfiles=sizeof( PY8_UNFDIR_DATA_file_array )/sizeof(std::string);
//CLOSURE
const std::string PY8_UNFDIR_CLOSURE="PY8_unfolding/closure/";
const std::string PY8_UNFDIR_CLOSURE_file_array[]={
  "ak3PFJets_wjtID_anabins_Bayes_Closure_PY8_FullRECO_09.30.20_SMPbins_LOMC_00eta05",
  "ak3PFJets_wjtID_anabins_Bayes_Closure_PY8_FullRECO_09.30.20_SMPbins_LOMC_05eta10",
  "ak3PFJets_wjtID_anabins_Bayes_Closure_PY8_FullRECO_09.30.20_SMPbins_LOMC_10eta15",
  "ak3PFJets_wjtID_anabins_Bayes_Closure_PY8_FullRECO_09.30.20_SMPbins_LOMC_15eta20"
};
const int PY8_UNFDIR_CLOSURE_Nfiles=sizeof( PY8_UNFDIR_CLOSURE_file_array )/sizeof(std::string);



//// SMEARED NLO UNFOLDING RESULTS
//DATA
const std::string NLO_UNFDIR_DATA   ="smearNLO_unfolding/data/";
const std::string NLO_UNFDIR_DATA_file_array[]={ 
  "ak4PFJets_wjtID_anabins_06.25.19_Bayes_NNPDF_NLO_sigmu_noJERscales_semifinal_JECsys_NLOMC_wNP_00eta05",
  "ak4PFJets_wjtID_anabins_06.25.19_Bayes_NNPDF_NLO_sigmu_noJERscales_semifinal_JECsys_NLOMC_wNP_05eta10",
  "ak4PFJets_wjtID_anabins_06.25.19_Bayes_NNPDF_NLO_sigmu_noJERscales_semifinal_JECsys_NLOMC_wNP_10eta15",
  "ak4PFJets_wjtID_anabins_06.25.19_Bayes_NNPDF_NLO_sigmu_noJERscales_semifinal_JECsys_NLOMC_wNP_15eta20"
};
const int   NLO_UNFDIR_DATA_Nfiles=sizeof(   NLO_UNFDIR_DATA_file_array )/sizeof(std::string);
//CLOSURE
const std::string NLO_UNFDIR_CLOSURE="smearNLO_unfolding/closure/";
const std::string NLO_UNFDIR_CLOSURE_file_array[]={ 
  "ak4PFJets_wjtID_anabins_06.25.19_Bayes_Closure_NNPDF_NLO_sigmu_noJERscales_semifinal_NLOMC_wNP_00eta05",
  "ak4PFJets_wjtID_anabins_06.25.19_Bayes_Closure_NNPDF_NLO_sigmu_noJERscales_semifinal_NLOMC_wNP_05eta10",
  "ak4PFJets_wjtID_anabins_06.25.19_Bayes_Closure_NNPDF_NLO_sigmu_noJERscales_semifinal_NLOMC_wNP_10eta15",
  "ak4PFJets_wjtID_anabins_06.25.19_Bayes_Closure_NNPDF_NLO_sigmu_noJERscales_semifinal_NLOMC_wNP_15eta20"
};
const int   NLO_UNFDIR_CLOSURE_Nfiles=sizeof(   NLO_UNFDIR_CLOSURE_file_array )/sizeof(std::string);


//// MC JERS
const std::string JERDIR_MC  ="printPlots_JERS/";
const std::string JERDIR_MC_file_array[]={ 
  "ak4PF_PY8JER_00eta05_06.25.19_sigmu_semifinal",
  "ak4PF_PY8JER_05eta10_06.25.19_sigmu_semifinal",
  "ak4PF_PY8JER_10eta15_06.25.19_sigmu_semifinal",
  "ak4PF_PY8JER_15eta20_06.25.19_sigmu_semifinal"
};
const int   JERDIR_MC_Nfiles=sizeof(   JERDIR_MC_file_array )/sizeof(std::string);

/// /MC VTX WGTS
const std::string VTXWDIR_MC  ="MC_vtxvzwgts/";
const std::string VTXWDIR_MC_file_array[]={ 
  "Py8_vzEvtWeights_baryshift_neg"
};
const int  VTXWDIR_MC_Nfiles=sizeof(  VTXWDIR_MC_file_array )/sizeof(std::string);

//// JET PLOTS QA
const std::string JETQA  ="printPlots_jetPlots/";
const std::string JETQA_file_array[]={ 
"ak4PF_HPtJetTrig_semiOffPy8_00eta20_06.25.19_noMB_SMPbins_semifinal_jetPlots"
};
const int       JETQA_Nfiles=sizeof(       JETQA_file_array )/sizeof(std::string);

//// JET ID QA
const std::string JETIDQA  ="printPlots_jetIDPlots_HIN/";
const std::string JETIDQA_file_array[]={ 
  "ak4PF_HPtJetTrig_00eta20_06.25.19_noMB_SMPbins_semifinal_jetIDPlots",
  "ak4PF_Py8_CUETP8M1_00eta20_06.25.19_SMPbins_semifinal_jetIDPlots"
};
const int     JETIDQA_Nfiles=sizeof(     JETIDQA_file_array )/sizeof(std::string);

//// JET TRIG QA
const std::string JETTRIGQA  ="printPlots_jetTrig/";
const std::string JETTRIGQA_file_array[]={ 
  "ak4PF_HPtJetTrig_00eta20_06.25.19_noMB_SMPbins_semifinal_jetTrig"
};
const int   JETTRIGQA_Nfiles=sizeof(   JETTRIGQA_file_array )/sizeof(std::string);
//const int Nfiles=sizeof(file_array)/sizeof(std::string);
