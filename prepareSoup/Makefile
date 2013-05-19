
all: SFplots/SF_all_log.pdf effPlots/eff2D_all_data_log.pdf

SFplots/SF_all_log.pdf: SFfile.root
	root -b -q -l drawTheSFPlot.C

effPlots/eff2D_all_data_log.pdf: OrSoupPlot.root
	root -b -q -l drawThePlot.C

SFfile.root: OrSoupPlot.root
	root -b -q -l doFinalHistoSF.C
	
OrSoupPlot.root: theEfficiencyPlots_data_*.root theEfficiencyPlots_mc_*.root
	root -b -q -l doTheSoupPlot.C