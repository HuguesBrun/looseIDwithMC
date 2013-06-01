
all: SFplots/SF_all_log.pdf effPlots/eff2D_all_data_log.pdf

SFplots/SF_all_log.pdf: SFfile.root drawTheSFPlot.C
	root -b -q -l drawTheSFPlot.C

effPlots/eff2D_all_data_log.pdf: FinalEfficiencies.root drawThePlot.C
	root -b -q -l drawThePlot.C

SFfile.root: FinalEfficiencies.root doFinalHistoSF.C
	root -b -q -l doFinalHistoSF.C
	
FinalEfficiencies.root: Mu17refPlot.root OrSoupPlot.root doFinalHisto.C
	root -b -q -l doFinalHisto.C 

Mu17refPlot.root: ../TriggerMu17/Mu17refPlot.root 
	cp ../TriggerMu17/Mu17refPlot.root . 

OrSoupPlot.root: ../prepareSoup/OrSoupPlot.root
	cp ../prepareSoup/OrSoupPlot.root .
