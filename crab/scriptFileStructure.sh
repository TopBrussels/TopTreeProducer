#!/bin/bash
# macro intended to set up the bookkeeping for the analysis structure

rm -rf endprintout.txt
#rm -rf auto-cmsswconfig
#rm -rf mkdir auto-crabconfig

    
    echo "usage:" 
    echo ". scriptFileStructure.sh <txtfile> "
    echo "where text file is space separated list of format:"
    echo "DATASETNAME TOPTREEPRODUCERTAG GLOBALTAGFORTTP"
    echo "OTHERDATASETNAME TOPTREEPRODUCERTAG GLOBALTAGFORTTP"
    echo "DIFFERENTSETNAME TOPTREEPRODUCERTAG GLOBALTAGFORTTP"
    echo " example:"
    echo "/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM CMSSW_74X_v2 MCRUN2_74_V9::All
/MuonEG/Run2015B-PromptReco-v1/MINIAOD CMSSW_74X_v2 GR_P_V56::All"


inputfile=$1
mkdir auto-cmsswconfig
mkdir auto-crabconfig
while IFS=" "  read samplename version globaltag jsonfile ; do
#    echo $samplename "  --- " $version " --- " $globaltag --- $jsonfile
    if [ -z `echo $samplename | grep AOD `  ] ; then 
	continue
    fi
    cleanedsamplename=`echo $samplename | awk -F"/" '{print $2"-"$3}'`
    totalworkname=$samplename"--"$version"--"$globaltag
    worknamerequest=$cleanedsamplename"-"$version"-"$globaltag
    cleanedtotalworkname=`echo $totalworkname | sed -e s%"/"%"-"%g -e s%"::"%"-"%g `
    cleanedrequestname=`echo $worknamerequest | sed -e s%"/"%"-"%g -e s%"::All"%""%g `
    dummyname=`echo $cleanedrequestname | sed -e s%"--"%"-"%g `
    cleanedrequestname=$dummyname
    reqlength=${#cleanedrequestname}

    # the following code strips the start of the requestname if it is longer than 140 characters. There is a maximum size of request names so this is done to protect against strings that are too long
    if [ $reqlength -ge 140 ]; then
	echo "!!!!!!!!!!!!!! requestname larger than 140: "  $reqlength " "$cleanedrequestname " so shortening by stripping start of name as already present in directory structure! "
	dummyname=${cleanedrequestname:$reclength-140}
	cleanedrequestname=$dummyname
	echo "!!!!!!!!!!!!!! new name: "$cleanedrequestname
    fi

#    echo $cleanedtotalworkname " ---- " $cleanedrequestname

    cmsswfilename="auto-cmsswconfig/TOPTREE_fromminiAOD-"$cleanedtotalworkname".py"
    crabfilename="auto-crabconfig/crabConfigTOPTREE-"$cleanedtotalworkname".py"

#   create crab config file:
#   some file manipulations, replace the request name by new name, change datasets, first for the crab config:
    grep -v "config.General.requestName" crabConfigTOPTREE.py > bla
    echo "config.General.requestName = '"$cleanedrequestname"'" >> bla
    grep -v "config.JobType.psetName" bla > bla2; mv bla2 bla
    echo "config.JobType.psetName = '"$cmsswfilename"'" >> bla
    echo "config.section_(\"User\")" >> bla
    echo "config.User.voGroup = 'becms'" >> bla
    grep -v "config.Data.inputDataset" bla > bla2; mv bla2 bla
    echo "config.Data.inputDataset = '"$samplename"'" >> bla 
    echo "config.Data.outLFNDirBase = '/store/user/"`whoami`"/TopTree/"$version"'" >> bla
    if [[ $samplename == *"Run2015"* ]] 
    then
	grep -v "config.Data.splitting = 'FileBased'" bla > bla2; mv bla2 bla
	echo "config.Data.splitting = 'LumiBased'" >> bla
	echo "config.Data.unitsPerJob = 20" >> bla
	if [[ $jsonfile == *"13TeV"* ]]
	then
	    echo "config.Data.lumiMask = '"$jsonfile"'">> bla
#	echo "config.Data.lumiMask = 'myJSONFILE.txt" >> bla
	fi

    fi


    echo $samplename >> endprintout.txt  #" config files "$cmsswfilename" "$crabfilename >> endprintout.txt

#    move the resulting file to the right location
    mv bla $crabfilename
#    cat $crabfilename

# now, start working on the cmssw config file:
    grep -v "process.GlobalTag.globaltag" ../prod/TOPTREE_fromminiAOD.py > bla
    echo "process.GlobalTag.globaltag = cms.string('"$globaltag"')" >> bla
# move the resulting file to the right location
    mv bla $cmsswfilename

    #cat $cmsswfilename


   # print some info to file for the summary at the end of the job
    echo $samplename  >> endprintout.txt  #" config files "$cmsswfilename" "$crabfilename >> endprintout.txt

done < $inputfile

echo "SUMMARY: CREATED CONFIGS FOR THE FOLLOWING SAMPLES: "
cat endprintout.txt



