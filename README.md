TopTreeProducer
===============

Repository for code to produce TopTrees

For developers: check out the CMSSW_80X branch

~~~
git cms-init

git remote add -f -t ecal_smear_fix_80X emanueledimarco https://github.com/emanueledimarco/cmssw.git
git cms-addpkg EgammaAnalysis/ElectronTools
git checkout -b from-52f192a 52f192a
cd EgammaAnalysis/ElectronTools/data
git clone -b ICHEP2016_v2 https://github.com/ECALELFS/ScalesSmearings.git
cd -

git cms-merge-topic -u cms-met:CMSSW_8_0_X-METFilterUpdate
git cms-merge-topic ikrav:egm_id_80X_v1

scram b -j10

git clone -b CMSSW_76X https://github.com/TopBrussels/TopTreeProducer TopBrussels/TopTreeProducer/
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

