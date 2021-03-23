#!/bin/bash

echo ""
echo "rename/hadd'ing..."
echo ""

#localDir=/Users/ilaflott/Working/Dropbox/localAnalysis/src/5p02TeV_ppJetAnalysis-master/doAnalysis/printPlots/outputCondor

MM="03"
DD="22"
YY="21"


#source renameNhadd.sh 3 "${MM}-${DD}-${YY}" "${MM}.${DD}.${YY}" "jetPlots_0.0eta2.0" "ppMC" "semifinal_doublecheck"
#source renameNhadd.sh 3 "${MM}-${DD}-${YY}" "${MM}.${DD}.${YY}" "JERS_0.0eta2.0" "ppMC" "JERSplots"
#source renameNhadd.sh 3 "${MM}-${DD}-${YY}" "${MM}.${DD}.${YY}" "jetPlots_0.0eta2.0" "ppMC"
source renameNhadd.sh 3 "${MM}-${DD}-${YY}" "${MM}.${DD}.${YY}" "unf_0.0eta2.0"      "ppMC" "unfold"


####source renameNhadd.sh 3 "${MM}-${DD}-${YY}" "${MM}.${DD}.${YY}" "jetPlots_0.0eta2.0" "ppData" "JohnSbins"
####source renameNhadd.sh 3 "${MM}-${DD}-${YY}" "${MM}.${DD}.${YY}" "jetPlots_0.0eta2.0" "ppData" "Chrisbins"
#source renameNhadd.sh 3 "${MM}-${DD}-${YY}" "${MM}.${DD}.${YY}" "jetPlots_0.0eta2.0" "ppData" "SMPbins"

###mv ppMC_Py8_CUETP8M1_QCDjetAllPtBins_ak3PFJets_06-26-19_unf_0.0eta2.0 ppMC_Py8_CUETP8M1_QCDjetAllPtBins_ak3PFJets_06-25-19_unf_0.0eta2.0
###source renameNhadd.sh 3 "${MM}-${DD}-${YY}" "${MM}.${DD}.${YY}" "unf_0.0eta2.0"      "ppMC" "unfold"

#
##mv ppMC_Py8_CUETP8M1_QCDjetAllPtBins_ak4PFJets_06-26-19_MCEff_0.0eta2.0 ppMC_Py8_CUETP8M1_QCDjetAllPtBins_ak4PFJets_06-25-19_MCEff_0.0eta2.0
##source renameNhadd.sh 3 "${MM}-${DD}-${YY}" "${MM}.${DD}.${YY}" "MCEff_0.0eta2.0"    "ppMC" "semifinal_doublecheck"










echo ""
echo "done rename/hadd'ing."
echo ""

return
