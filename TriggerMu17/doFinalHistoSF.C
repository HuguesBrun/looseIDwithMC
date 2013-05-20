TFile *myFileOut = new TFile("SFdataMC.root","RECREATE");

TString runPeriod[5] = {"runA","runB","runC","runD","all"};

doFinalHistoSF(){
    TFile *theFile = new TFile("Mu17refPlot.root");

    for (int k=0; k<5 ; k++){
        for (int j = 0 ; j<2 ; j++){
            TH2F *thePlotData = (TH2F*) theFile->Get(Form("eff2D_ptbin%i_",j)+runPeriod[k]+"_data");
            TH2F *thePlotMC = (TH2F*) theFile->Get(Form("eff2D_ptbin%i_",j)+runPeriod[k]+"_mc");
    
    
            TH2F *finalPlot = (TH2F*) thePlotData->Clone();
            finalPlot->Divide(thePlotData, thePlotMC,1,1);
            

            myFileOut->cd();
            finalPlot->Write(Form("SF_ptbin%i_",j)+runPeriod[k]);
        }
    }
    
}
