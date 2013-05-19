
TString runPeriod[5] = {"runA","runB","runC","runD","all"};
TString theTypeName[3] = {"passORdiMu","passMu17Mu8","passMu17TkMu8"};
TString theType[2] = {"data","mc"};

giveFinalNumbers(){
    
    TFile *weightStat = new TFile("theWeightFile.root");
    TFile *effFile = new TFile("FinalEfficiencies.root");
    for (int n=0 ; n<2 ; n++){
    for (int m=0 ; m < 3 ; m++){
        for (int k=0; k<5 ; k++){
                float theEff = 0;
                float theError = 0;
                TH2F *effsBin0 = (TH2F*) effFile->Get("effTrigger_"+runPeriod[k]+"_"+theTypeName[m]+"_"+theType[n]);
                TH1F *weightHistoBin0 = (TH1F*) weightStat->Get("PtWeights");
                for (int  i = 0 ; i < 2 ; i++){
                        theEff += weightHistoBin0->GetBinContent(i+1)*effsBin0->GetBinContent(2,i+1);
                        theError += (weightHistoBin0->GetBinContent(i+1)*effsBin0->GetBinError(2,i+1)*weightHistoBin0->GetBinContent(i+1)*effsBin0->GetBinError(2,i+1));
                
                }
                cout << theType[n] << " & " <<  theTypeName[m] << " & " << runPeriod[k] << " & " << theEff <<  " & " << sqrt(theError) <<  endl;
            
            }
        }
    }
    
    
}