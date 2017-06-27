TopTreeProducer
===============

Repository for code to produce TopTrees

For developers: check out the CMSSW_80X branch - this is the working development for CMSSW_9_2_X for the 2017 data

~~~
cmsrel CMSSW_9_2_4
cd CMSSW_9_2_4/src
cmsenv

git cms-init

git clone https://github.com/TopBrussels/TopTreeProducer TopBrussels/TopTreeProducer

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

