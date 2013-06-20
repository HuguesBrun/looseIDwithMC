
TFile *myOutFile = new TFile("OrSoupPlot.root","RECREATE");
TString runPeriod[5] = {"runA","runB","runC","runD","all"};
TString theTypeName[4] = {"passORdiMuNodZ","passMu17Mu8NoDz","passMu17TkMu8NoDz","passORMuCocktailNoDz"};
TString theType[2] = {"data","mc"};

doTheSoupPlot(){
    for(int i =0 ; i< 2 ; i++){
    for (int k=0 ; k<5 ; k++){
        for (int m=0; m<4 ; m++){
            TFile *myInFile = new TFile("theEfficiencyPlots_"+theType[i]+"_"+runPeriod[k]+"_"+theTypeName[m]+".root");
            TH2F *theEffPlot = (TH2F*) myInFile->Get(theTypeName[m]+"_ptEta_tag_pt_pt_PLOT_abseta_bin0_&_tag_abseta_bin0");
            myOutFile->cd();
            theEffPlot->Write("eff2D_"+runPeriod[k]+"_"+theTypeName[m]+"_"+theType[i]);
        }
    }
    }
        
}
