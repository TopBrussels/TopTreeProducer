TopTreeProducer
===============

Repository for code to produce TopTrees

For developers: check out the CMSSW_80X branch

~~~
cmsrel CMSSW 8_0_26_patch1
cd CMSSW 8_0_26_patch1/src 
cmsenv

git cms-init

#add the repository with the updated Egamma package
git cms-merge-topic shervin86:Moriond2017_JEC_energyScales

cd EgammaAnalysis/ElectronTools/data
# download the txt files with the corrections
git clone git@github.com:ECALELFS/ScalesSmearings.git
cd -

git cms-merge-topic ikrav:egm_id_80X_v2
git cms-merge-topic -u cms-met:CMSSW_8_0_X-METFilterUpdate
git cms-merge-topic rafaellopesdesa:Regression80XEgammaAnalysis_v2
git cms-merge-topic gpetruc:badMuonFilters_80X

# Replace the following line in CMSSW_8_0_26/src/RecoMET/METFilters/python/badGlobalMuonTaggersMiniAOD_cff.py
`cloneGlobalMuonTaggerMAOD = badGlobalMuonTagger.clone(`
by
`cloneGlobalMuonTaggerMAOD = badGlobalMuonTaggerMAOD.clone(`

scram b -j8


# Add the area containing the MVA weights (from cms-data, to appear in “external”).
# Note: the “external” area appears after “scram build” is run at least once, as above
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

