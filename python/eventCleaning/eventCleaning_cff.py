import FWCore.ParameterSet.Config as cms

#Scraping event filter
from TopBrussels.TopTreeProducer.eventCleaning.scrapingFilter_cfi import *

#good primary vertex filter
from TopBrussels.TopTreeProducer.eventCleaning.primaryVertexFilter_cfi import *
 
# CSC Beam Halo Filter
#from RecoMET.METAnalyzers.CSCTightHalo2015Filter_cfi import *
from RecoMET.METAnalyzers.globalTightHalo2016Filter_cfi import * #27/10/2016 update to 80

# HB + HE noise filter
from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import *

# HCAL laser events filter
from RecoMET.METFilters.hcalLaserEventFilter_cfi import *
hcalLaserEventFilter.vetoByRunEventNumber=cms.untracked.bool(False)
hcalLaserEventFilter.vetoByHBHEOccupancy=cms.untracked.bool(True)

# ECAL dead cell filter
from RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi import *
#EcalDeadCellTriggerPrimitiveFilter.tpDigiCollection = cms.InputTag("ecalTPSkimNA")

# Tracking failure filter
from RecoMET.METFilters.trackingFailureFilter_cfi import *
trackingFailureFilter.VertexSource = cms.InputTag("goodOfflinePrimaryVertices", "", "")

# The EE bad SuperCrystal filter
from RecoMET.METFilters.eeBadScFilter_cfi import *

eventCleaning = cms.Sequence(
#    CSCTightHalo2015Filter* #29/2/2016
    globalTightHalo2016Filter* #27/10/2016
    HBHENoiseFilter*
    scrapingFilter*
    hcalLaserEventFilter*
    EcalDeadCellTriggerPrimitiveFilter*
#    primaryVertexFilter * # this will be applied before this sequence. do we need to apply this only for data? --> applied in the analysis
    trackingFailureFilter*
    eeBadScFilter
)
