TopTreeProducer
===============

Repository for code to produce TopTrees

For 2017 data: check out the master branch (CMSSW_9_2_X)

~~~
cmsrel CMSSW_8_0_26_patch1
cd CMSSW_8_0_26_patch1/src
cmsenv

git cms-init

git cms-merge-topic cms-egamma:EGM_gain_v1
cd EgammaAnalysis/ElectronTools/data
git clone -b Moriond17_gainSwitch_unc https://github.com/ECALELFS/ScalesSmearings.git
cd $CMSSW_BASE/src

git cms-merge-topic ikrav:egm_id_80X_v2 #https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2#User_recipes_general_remarks
git cms-merge-topic -u cms-met:fromCMSSW_8_0_20_postICHEPfilter #https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#How_to_run_the_Bad_Charged_Hadro
git cms-merge-topic rafaellopesdesa:RegressionCheckNegEnergy
git cms-merge-topic gpetruc:badMuonFilters_80X
git cms-merge-topic cms-met:METRecipe_8020 -u
git cms-merge-topic cms-met:METRecipe_80X_part2 -u

git cms-merge-topic -u intrepid42:pseudotoprivet_80x
cd TopQuarkAnalysis
git clone https://gitlab.cern.ch/CMS-TOPPAG/BFragmentationAnalyzer.git
cd -


scram b -j8

# Add the area containing the MVA weights (from cms-data, to appear in "external").
# Note: the "external" area appears after "scram build" is run at least once, as above
#
cd $CMSSW_BASE/external
# below, you may have a different architecture, this is just one example from lxplus
cd slc6_amd64_gcc530/
git clone https://github.com/ikrav/RecoEgamma-ElectronIdentification.git data/RecoEgamma/ElectronIdentification/data
cd data/RecoEgamma/ElectronIdentification/data
git checkout egm_id_80X_v1
# Go back to the src/
cd $CMSSW_BASE/src

git clone -b CMSSW_80X https://github.com/TopBrussels/TopTreeProducer TopBrussels/TopTreeProducer

~~~

To compile TRoot* objects
~~~
cd TopBrussels/TopTreeProducer/src/
make
~~~

To compile analysers
~~~
scram b
~~~

