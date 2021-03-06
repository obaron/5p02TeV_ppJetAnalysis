const std::string SCRATCH_BASE ="/cms/heavyion/obaron/5p02TeV_ppJetAnalysis/outputCondor/";

const std::string _PY8_FILESTR="06.25.19_outputCondor/ppMC_Py8_CUETP8M1_QCDjetAllPtBins_ak3PFJets_06-25-19_unf_0.0eta2.0_unfold/Py8_CUETP8M1_QCDjetAllPtBins_ak3PF-allFiles.root";
const std::string _PY8_DESCTXT="GEN PY8 CUETP8M1";

//PDF file strings + descriptive text
const std::string _CT10FILESTR="fnl5020_LO2_R03Jets_modify_CT10nlo_HS";
const std::string _CT14FILESTR="fnl5020_LO2_R03Jets_modify_CT14nlo_HS";
const std::string _HERAFILESTR="fnl5020_LO2_R03Jets_modify_HERAPDF15NLO_ALPHAS_HS";
const std::string _MMHTFILESTR="fnl5020_LO2_R03Jets_modify_MMHT2014nlo68cl_HS";
const std::string NNPDFFILESTR="fnl5020_LO2_R03Jets_modify_NNPDF30_nnlo_as_0121_MC";


const std::string _CT10DESCTXT="CT10";
const std::string _CT14DESCTXT="CT14";
const std::string _HERADESCTXT="HERAPDF15";
const std::string _MMHTDESCTXT="MMHT14";
const std::string NNPDFDESCTXT="NNPDF30";


//NP corr fits strings + descriptive text
const std::string HERWGEE4_NPS = "NPC_HerwigEE4C_R3";  //LO
const std::string HERWGEE5_NPS = "NPC_HerwigEE5C_R3";  //LO
const std::string _PYTHIA8_NPS = "NPC_PYTHIA8_R3";      //LO
const std::string _POW_PY8_NPS = "NPC_POWPY8_R3";  //NLO
const std::string POWPY8CT_NPS = "NPC_POWPY8CTEQ_R3";  //NLO

const std::string HERWGEE4_NPS_TXT = "Herwig EE4C R3";  //LO
const std::string HERWGEE5_NPS_TXT = "Herwig EE5C R3";  //LO
const std::string _PYTHIA8_NPS_TXT = "PYTHIA8 R3";      //LO
const std::string _POW_PY8_NPS_TXT = "POW+PY8 R3";  //NLO
const std::string POWPY8CT_NPS_TXT = "POW+PY8 CTEQ R3";  //NLO


//descriptive text
std::string ddxsec_yax="#frac{d^{2}#sigma}{dp_{T}dy} [nb/GeV]";


//default file strings
const std::string in_JERFile_default="/home/ilaflott/5p02TeV_ppJetAnalysis/CMSSW_7_5_8/src/doAnalysis/printPlots_JERS/output/ak4PF_MCJEC_00eta05.root";
const std::string NPCorrFile="/home/ilaflott/5p02TeV_ppJetAnalysis/CMSSW_7_5_8/src/doAnalysis/doUnfolding/smearTheory/NPCorr5TeV/NLOpNP_InclusiveJets5TeV.root";

const std::string in_NLOFile_default=NNPDFFILESTR;
const std::string in_PY8File_default=_PY8_FILESTR;

