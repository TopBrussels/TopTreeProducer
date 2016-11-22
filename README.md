TopTreeProducer
===============

Repository for code to produce TopTrees

For developers: check out the CMSSW_80X branch

~~~
cmsrel CMSSW_8_0_22
cd CMSSW_8_0_22/src
cmsenv

git cms-init

git cms-merge-topic emanueledimarco:ecal_smear_fix_80X
cd EgammaAnalysis/ElectronTools/data
git clone -b ICHEP2016_v2 https://github.com/ECALELFS/ScalesSmearings.git
cd -

git cms-merge-topic ikrav:egm_id_80X_v1
git cms-merge-topic -u cms-met:CMSSW_8_0_X-METFilterUpdate

scram b -j6

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

