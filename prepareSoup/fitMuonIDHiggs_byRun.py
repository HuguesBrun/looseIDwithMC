import FWCore.ParameterSet.Config as cms
import re, os

### USAGE:
###    cmsRun fitMuonID.py <scenario> [ <id> [ <binning1> ... <binningN> ] ]
###
### scenarios:
###   - data_all (default)  
###   - signal_mc

import sys
args = sys.argv[1:]
if (sys.argv[0] == "cmsRun"): args =sys.argv[2:]
scenario = "data_all"
if len(args) > 0: scenario = args[0]
print "Will run scenario ", scenario 

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

Template = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(False),

    Variables = cms.PSet(
        mass = cms.vstring("Tag-muon Mass", "70", "120", "GeV/c^{2}"),
        pt = cms.vstring("muon p_{T}", "0", "1000", "GeV/c"),
        abseta = cms.vstring("muon |#eta|", "0", "2.5", ""),
        tag_pt = cms.vstring("muon Tag Pt","20","500","GeV/c^2"),
        tag_abseta = cms.vstring("muon |#eta|", "0", "2.5", ""),
        pair_probeMultiplicity = cms.vstring("multiplicity","0","999",""),
        weight = cms.vstring("weight", "0.0", "30.0", ""),
                         weight_runA = cms.vstring("weight_runA", "0.0", "30.0", ""),
                         weight_runB = cms.vstring("weight_runB", "0.0", "30.0", ""),
                         weight_runC = cms.vstring("weight_runC", "0.0", "30.0", ""),
                         weight_runD = cms.vstring("weight_runD", "0.0", "30.0", ""),


    ),

    Categories = cms.PSet(
                          passORdiMu = cms.vstring("passORdiMu","dummy[pass=1,fail=0]"),
                          passMu17Mu8 = cms.vstring("passMu17TkMu8","dummy[pass=1,fail=0]"),
                          passMu17TkMu8 = cms.vstring("passMu17TkMu8","dummy[pass=1,fail=0]"),
                          passORdiMuNodZ = cms.vstring("passORdiMuNodZ","dummy[pass=1,fail=0]"),
                          passMu17Mu8NoDz = cms.vstring("passMu17Mu8NoDz","dummy[pass=1,fail=0]"),
                          passMu17TkMu8NoDz = cms.vstring("passMu17TkMu8NoDz","dummy[pass=1,fail=0]"),
                          passORMuCocktail = cms.vstring("passORMuCocktail","dummy[pass=1,fail=0]"),
                          passORMuCocktailNoDz = cms.vstring("passORMuCocktailNoDz","dummy[pass=1,fail=0]")
    ),
    PDFs = cms.PSet(
        voigtPlusExpo = cms.vstring(
            "Voigtian::signal(mass, mean[90,80,100], width[2.495], sigma[3,1,20])",
            "Exponential::backgroundPass(mass, lp[0,-5,5])",
            "Exponential::backgroundFail(mass, lf[0,-5,5])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpo = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,2,10])",
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpoMin70 = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,3,10])",
            "SUM::signal(vFrac[0.8,0.5,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0.7,1]",
            "signalFractionInPassing[0.9]"
        )
    ),

    binnedFit = cms.bool(False),
    binsForFit = cms.uint32(40),

    Efficiencies = cms.PSet(
    ), # will be filled later
)

if "mc" in scenario: Template.binnedFit=cms.bool(True)


TRIGGER = cms.PSet(tag_Mu24 = cms.vstring("pass"))
if "mc" in scenario or "39X" in scenario or "38X" in scenario:
    TRIGGER = cms.PSet(tag_Mu15 = cms.vstring("pass"), tag_pt = cms.vdouble(24.,9999.))



PT_ETA_BINS_TRIGGER = cms.PSet(
                               pt   = cms.vdouble(10, 20, 100),
                               tag_pt   = cms.vdouble(10, 20, 100),
                               abseta = cms.vdouble(0,2.4),
                               tag_abseta = cms.vdouble(0,2.4),
                               #  abseta = cms.vdouble(0,1.,2.1,2.4),
                               #tag_abseta = cms.vdouble(0,1,2.1,2.4),

)




#PREFIX="/data/gpetrucc/7TeV/tnp/2011.02.17/"
PREFIX="file:/afs/cern.ch/work/h/hbrun/pogTnPr8SoupWithTight/"
#PREFIX="root://eoscms//eos/cms/store/caf/user/gpetrucc/TnP/V4/"
#PREFIX="file:/tmp/hbrun/"
process.TnP_MuonID = Template.clone(
    InputFileNames = cms.vstring(PREFIX+"tnpZ_withMVAIsoNew.root"),
    InputTreeName = cms.string("fitter_tree"),
    InputDirectoryName = cms.string("tpTree"),
    OutputFileName = cms.string("TnP_MuonID_%s.root" % scenario),
    Efficiencies = cms.PSet(),
)

weightName="weight"
if "mc" in scenario:
    process.TnP_MuonID.WeightVariable = cms.string("weight")
    if "runA" in scenario: process.TnP_MuonID.WeightVariable = cms.string("weight_runA")
    elif "runB" in scenario: process.TnP_MuonID.WeightVariable = cms.string("weight_runB")
    elif "runC" in scenario: process.TnP_MuonID.WeightVariable = cms.string("weight_runC")
    elif "runD" in scenario: process.TnP_MuonID.WeightVariable = cms.string("weight_runD")
    
    if "runA" in scenario: weightName="weight_runA"
    elif "runB" in scenario: weightName="weight_runB"
    elif "runC" in scenario: weightName="weight_runC"
    elif "runD" in scenario: weightName="weight_runD"


if "data" in scenario:
    if   "v1" in scenario: process.TnP_MuonID.InputFileNames = [ PREFIX+"tnpZ_HWWid2012.root" ]
    elif "v2" in scenario: process.TnP_MuonID.InputFileNames = [ PREFIX+"tnpZ_2011A_v2_GOLDEN.root" ]
    # elif "huguesTest" in scenario: process.TnP_MuonID.InputFileNames = [ PREFIX + "TnP_Data_runA.root",PREFIX + "TnP_Data_runB.root",PREFIX + "TnP_Data_runCv1.root",PREFIX + "TnP_Data_runCv2_forTrigger.root",PREFIX + "TnP_Data_runDp1.root",PREFIX + "TnP_Data_runDp2.root"]
    # elif "huguesTest" in scenario: process.TnP_MuonID.InputFileNames = [ PREFIX + "TnP_Data_runDp1_dipho.root",PREFIX + "TnP_Data_runDp2_dipho.root"]
    elif "huguesTest" in scenario:
        if "runA" in scenario: process.TnP_MuonID.InputFileNames = [ PREFIX + "tnpZ_DoubleMu_Run2012A.root"]
        elif "runB" in scenario: process.TnP_MuonID.InputFileNames = [ PREFIX + "tnpZ_DoubleMu_Run2012B.root"]
        elif "runC" in scenario: process.TnP_MuonID.InputFileNames = [ PREFIX + "tnpZ_DoubleMu_Run2012C.root"]
        elif "runD" in scenario: process.TnP_MuonID.InputFileNames = [ PREFIX + "tnpZ_DoubleMu_Run2012D.root"]
        elif "all" in scenario: process.TnP_MuonID.InputFileNames = [ PREFIX + "tnpZ_DoubleMu_Run2012A.root",PREFIX + "tnpZ_DoubleMu_Run2012B.root", PREFIX + "tnpZ_DoubleMu_Run2012C.root", PREFIX + "tnpZ_DoubleMu_Run2012D.root"]

if "mc" in scenario:
    process.TnP_MuonID.InputFileNames = [PREFIX + "tnpZ_MC53X_DYJets.root"]
#TnP_DY.root"]

if "tag35" in scenario:
    process.TnP_MuonID.Variables.tag_pt[1]='35'

print "les fichiers que l'on va utiliser = ", process.TnP_MuonID.InputFileNames

IDS = ["passORdiMuNodZ","passMu17Mu8NoDz","passMu17TkMu8NoDz", "passORMuCocktailNoDz"]


ALLBINS = [("ptEta",PT_ETA_BINS_TRIGGER)]



#TemplateSignal_AllBin = cms.vstring(
                                    #"scalePass[1,0.9,1.1]",
                                    #"scaleFail[1,0.9,1.1]",
                                    #"largerResPass[1,0.9,1.1]",
                                    #"largerResFail[1,0.9,1.1]",
                                    #"expr::NewMean1p('mean1p*scalePass',mean1p,scalePass)",
                                    #"expr::NewMean2p('mean2p*scalePass',mean2p,scalePass)",
                                    #"expr::NewMean1f('mean1f*scalePass',mean1f,scalePass)",
                                    #"expr::NewMean2f('mean2f*scalePass',mean2f,scalePass)",
                                    #"expr::NewWidth1p('width1p*largerResPass',width1p[2.495],largerResPass)",
                                    #"expr::NewWidth2p('width2p*largerResPass',width2p[2.495],largerResPass)",
                                    #"expr::NewWidth1f('width1f*largerResFail',width1f,largerResFail)",
                                    #"expr::NewWidth2f('width2f*largerResFail',width2f,largerResFail)",
                                    #"Voigtian::theSig1p(mass, NewMean1p, NewWidth1p, sigma1p)",
                                    #"Voigtian::theSig2p(mass, NewMean2p, NewWidth2p, sigma2p)",
                                    #"SUM::sVoigP(vPropp*theSig1p,theSig2p)",
                                    #"Voigtian::theSig1f(mass, NewMean1f, NewWidth1f, sigma1f)",
                                    #"Voigtian::theSig2f(mass, NewMean2f, NewWidth2f, sigma2f)",
                                    #"SUM::sVoigF(vPropf*theSig1f,theSig2f)",
                                    #"Exponential::expP(mass, lsp)",
                                    #"Exponential::expF(mass, lsf)",
                                    #"ArgusBG::argF(mass, ap0, ap1)",
                                    #"SUM::shapeF(vFrac*argF, expF)",
                                    #"SUM::signalPass(vPropTotp*sVoigP,expP)",
                                    #"SUM::signalFail( vPropTotf*sVoigF,shapeF)",
                                    #"Exponential::backgroundPass(mass, lp[0,-5,5])",
                                    #"Exponential::backgroundFail(mass, lf[0,-5,5])",
                                    #"efficiency[0.9,0,1]",
                                    #"signalFractionInPassing[0.9]"
                                    #                                    )
TemplateSignal_AllBin = cms.vstring(
                                    "scale[1,0.9,1.1]",
                                    "largerResPass[1,0.,2.]",
                                    "largerResFail[1,0.,2.]",
                                    "expr::NewMean1p('mean1p*scale',mean1p,scale)",
                                    "expr::NewMean2p('mean2p*scale',mean2p,scale)",
                                    "expr::NewMean1f('mean1f*scale',mean1f,scale)",
                                    "expr::NewMean2f('mean2f*scale',mean2f,scale)",
                                    "expr::NewSigma1p('sigma1p*largerResPass',sigma1p,largerResPass)",
                                    "expr::NewSigma2p('sigma2p*largerResPass',sigma2p,largerResPass)",
                                    "expr::NewSigma1f('sigma1f*largerResFail',sigma1f,largerResFail)",
                                    "expr::NewSigma2f('sigma2f*largerResFail',sigma2f,largerResFail)",
                                    "Voigtian::theSig1p(mass, NewMean1p, width1p[2.495], NewSigma1p)",
                                    "Voigtian::theSig2p(mass, NewMean2p, width2p[2.495], NewSigma2p)",
                                    "SUM::sVoigP(vPropp*theSig1p,theSig2p)",
                                    "Voigtian::theSig1f(mass, NewMean1f, width1f, NewSigma1f)",
                                    "Voigtian::theSig2f(mass, NewMean2f, width2f, NewSigma2f)",
                                    "SUM::sVoigF(vPropf*theSig1f,theSig2f)",
                                    "Exponential::expP(mass, lsp)",
                                    "Exponential::expF(mass, lsf)",
                                    "ArgusBG::argF(mass, ap0, ap1)",
                                    "SUM::shapeF(vFrac*argF, expF)",
                                    "SUM::signalPass(vPropTotp*sVoigP,expP)",
                                    "SUM::signalFail( vPropTotf*sVoigF,shapeF)",
                                    #"Exponential::backgroundPass(mass, lp[0,-5,5])",
                                    #"Exponential::backgroundFail(mass, lf[0,-5,5])",
                                    "RooBernstein::backgroundPass(mass,{a0[10,0,50],a1[1,0,50],a2[1,0,50],a3[1,0,50],a4[1,0,50]})",
                                    "RooBernstein::backgroundFail(mass,{a0[10,0,50],a1[1,0,50],a2[1,0,50],a3[1,0,50],a4[1,0,50]})",
                                    "efficiency[0.9,0,1]",
                                    "signalFractionInPassing[0.9]"
                                    )

TemplateSignal_HighestEtaBin = cms.vstring(
                                           "scale[1,0.9,1.1]",
                                           "largerResPass[1,0.,2.]",
                                           "largerResFail[1,0.,2.]",
                                           "expr::NewMean1p('mean1p*scale',mean1p,scale)",
                                           "expr::NewMean2p('mean2p*scale',mean2p,scale)",
                                           "expr::NewMean1f('mean1f*scale',mean1f,scale)",
                                           "expr::NewMean2f('mean2f*scale',mean2f,scale)",
                                           "expr::NewSigma1p('sigma1p*largerResPass',sigma1p,largerResPass)",
                                           "expr::NewSigma2p('sigma2p*largerResPass',sigma2p,largerResPass)",
                                           "expr::NewSigma1f('sigma1f*largerResFail',sigma1f,largerResFail)",
                                           "expr::NewSigma2f('sigma2f*largerResFail',sigma2f,largerResFail)",
                                           "Voigtian::theSig1p(mass, NewMean1p, width1p[2.495], NewSigma1p)",
                                           "Voigtian::theSig2p(mass, NewMean2p, width2p[2.495], NewSigma2p)",
                                           "SUM::sVoigP(vPropp*theSig1p,theSig2p)",
                                           "Voigtian::theSig1f(mass, NewMean1f, width1f, NewSigma1f)",
                                           "Voigtian::theSig2f(mass, NewMean2f, width2f, NewSigma2f)",
                                           "SUM::sVoigF(vPropf*theSig1f,theSig2f)",
                                           "Exponential::expP(mass, lsp)",
                                           "Exponential::expF(mass, lsf)",
                                           "ArgusBG::argF(mass, ap0, ap1)",
                                           "SUM::shapeF(vFrac*argF, expF)",
                                           "SUM::signalPass(vPropTotp*sVoigP,expP)",
                                           "SUM::signalFail( vPropTotf*sVoigF,shapeF)",
                                           "RooBernstein::backgroundPass(mass,{a0[10,0,50],a1[1,0,50],a2[1,0,50],a3[1,0,50],a4[1,0,50]})",
                                           "RooBernstein::backgroundFail(mass,{a0[10,0,50],a1[1,0,50],a2[1,0,50],a3[1,0,50],a4[1,0,50]})",
                                           "efficiency[0.9,0,1]",
                                           "signalFractionInPassing[0.9]"
                                    )

TemplateSignal_HighBin = cms.vstring(
                                     "scale[1,0.9,1.1]",
                                     "largerResPass[1,0.,2.]",
                                     "expr::NewMean('mean*scale',mean,scale)",
                                     "expr::NewSigma('sigma*largerResPass',sigma,largerResPass)",
                                     "CBShape::crystal(mass, NewMean, NewSigma,alpha, n)",
                                     "RooLandau::pLandau(mass, Lmp,wp)",
                                     "ArgusBG::fArg(mass, ap0, ap1)",
                                     "RooLandau::fLandau(mass, Lmf,wf)",
                                     "SUM::argLand(vFrac*fLandau, fArg)",
                                     "SUM::signalPass(vProp*crystal,pLandau)",
                                     "SUM::signalFail(vProp*crystal,argLand)",
                                     #"Exponential::backgroundPass(mass, lp[0,-5,5])",
                                     #"Exponential::backgroundFail(mass, lf[0,-5,5])",
                                     "RooBernstein::backgroundPass(mass,{a0[10,0,50],a1[1,0,50],a2[1,0,50],a3[1,0,50],a4[1,0,50]})",
                                     "RooBernstein::backgroundFail(mass,{a0[10,0,50],a1[1,0,50],a2[1,0,50],a3[1,0,50],a4[1,0,50]})",
                                     "efficiency[0.9,0,1]",
                                     "signalFractionInPassing[0.9]"
                                     )




if len(args) > 1 and args[1] not in IDS: IDS += [ args[1] ]
for ID in IDS:
    if len(args) > 1 and ID != args[1]: continue
    
    for X,B in ALLBINS:
        if len(args) > 2 and X not in args[2:]: continue
        module = process.TnP_MuonID.clone(OutputFileName = cms.string("TnP_MuonID_%s_%s_%s.root" % (scenario, ID, X)))
        shape = cms.vstring("vpvPlusExpo")                   

        
        DEN = B.clone(); num = ID;
        if "_from_" in ID:
            parts = ID.split("_from_")
            num = parts[0]
            setattr(DEN, parts[1], cms.vstring("pass"))
        print shape

        setattr(module.Efficiencies, ID+"_"+X, cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(num,"pass"),
            UnbinnedVariables = cms.vstring("mass",weightName),
            BinnedVariables = DEN,
            BinToPDFmap = shape #cms.vstring(shape)
        ))

        setattr(process, "TnP_MuonID_"+ID+"_"+X, module)        
        setattr(process, "run_"+ID+"_"+X, cms.Path(module))

