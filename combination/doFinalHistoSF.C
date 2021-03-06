TFile *myFileOut = new TFile("SFfile.root","RECREATE");

TString runPeriod[5] = {"runA","runB","runC","runD","all"};
TString theTypeName[3] = {"passORdiMu","passMu17Mu8","passMu17TkMu8"};

doFinalHistoSF(){
    TFile *theFile = new TFile("FinalEfficiencies.root");

    for (int k=0; k<5 ; k++){
        for (int m=0 ; m<3 ; m++){
            TH2F *thePlotData = (TH2F*) theFile->Get("effTrigger_"+runPeriod[k]+"_"+theTypeName[m]+"_data");
            TH2F *thePlotMC = (TH2F*) theFile->Get("effTrigger_"+runPeriod[k]+"_"+theTypeName[m]+"_mc");
    
    
            TH2F *finalPlot = (TH2F*) thePlotData->Clone();
            finalPlot->Divide(thePlotData, thePlotMC,1,1);
            

            myFileOut->cd();
            finalPlot->Write("SF_"+runPeriod[k]+"_"+theTypeName[m]);
        }
    }
    
}
