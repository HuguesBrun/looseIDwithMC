
all: SFplots/SF_all_log.pdf effPlots/eff2D_all_data_log.pdf

SFplots/SF_all_log.pdf: SFdataMC.root drawTheSFPlot.C
	root -b -q -l drawTheSFPlot.C

effPlots/eff2D_all_data_log.pdf: Mu17refPlot.root drawThePlot.C
	root -b -q -l drawThePlot.C

SFdataMC.root: Mu17refPlot.root doFinalHistoSF.C
	root -b -q -l doFinalHistoSF.C
	
Mu17refPlot.root: theEfficiencyPlots_data_all.root theEfficiencyPlots_data_runA.root theEfficiencyPlots_data_runB.root theEfficiencyPlots_data_runC.root theEfficiencyPlots_data_runD.root theEfficiencyPlots_mc_all.root theEfficiencyPlots_mc_runA.root theEfficiencyPlots_mc_runB.root theEfficiencyPlots_mc_runC.root theEfficiencyPlots_mc_runD.root doTheRefPlot.C
	root -b -q -l doTheRefPlot.C
