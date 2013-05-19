TFile *myFileOut = new TFile("SFdataMC.root","RECREATE");

TString runPeriod[5] = {"runA","runB","runC","runD","all"};

doFinalHistoSF(){
    TFile *theFile = new TFile("Mu17refPlot.root");

    for (int k=0; k<5 ; k++){
            TH2F *thePlotData = (TH2F*) theFile->Get("eff2D_"+runPeriod[k]+"_data");
            TH2F *thePlotMC = (TH2F*) theFile->Get("eff2D_"+runPeriod[k]+"_mc");
    
    
            TH2F *finalPlot = (TH2F*) thePlotData->Clone();
            finalPlot->Divide(thePlotData, thePlotMC,1,1);
            

            myFileOut->cd();
            finalPlot->Write("SF_"+runPeriod[k]);
    }
    
}
