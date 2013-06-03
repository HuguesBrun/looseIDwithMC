

recupTheNumbers(){
    TString theRuns[5] = {"runA","runB","runC","runD","all"};
    TString nomTrigger[3] = {"passMu17Mu8","passMu17TkMu8","passORdiMu"};
    
    TFile *myFile = new TFile("TriggerMu17/Mu17refPlot.root");
    for (int i = 0 ; i < 5 ; i++){
        TH2F *data = (TH2F*) myFile->Get("eff2D_"+theRuns[i]+"_data");
        TH2F *mc = (TH2F*) myFile->Get("eff2D_"+theRuns[i]+"_mc");
        TH2F *ratio = (TH2F*) data->Clone("ratio");
        ratio->Divide(data,mc,1,1);
        cout << theRuns[i] << " " << data->GetBinContent(2,2) << " " << data->GetBinError(2,2);
        cout << " " <<  mc->GetBinContent(2,2) << " " << mc->GetBinError(2,2);
        cout << " " << ratio->GetBinContent(2,2) << " " << ratio->GetBinError(2,2) << endl;
        delete data;
        delete mc;
        delete ratio;
    }
    myFile->Close();
    delete myFile;
    
    TFile *myFile = new TFile("prepareSoup/OrSoupPlot.root");
    for (int j=0 ; j < 2 ; j++){
        for (int i = 0 ; i < 5 ; i++){
           // cout << "eff2D_"+theRuns[i]+"_"+nomTrigger[j]+"_data" << endl;
            TH2F *data = (TH2F*) myFile->Get("eff2D_"+theRuns[i]+"_"+nomTrigger[j]+"_data");
            TH2F *mc = (TH2F*) myFile->Get("eff2D_"+theRuns[i]+"_"+nomTrigger[j]+"_mc");
            TH2F *ratio = (TH2F*) data->Clone("ratio");
            ratio->Divide(data,mc,1,1);
            cout << theRuns[i] << " " << data->GetBinContent(2,2) << " " << data->GetBinError(2,2);
            cout << " " <<  mc->GetBinContent(2,2) << " " << mc->GetBinError(2,2);
            cout << " " << ratio->GetBinContent(2,2) << " " << ratio->GetBinError(2,2) << endl;
            delete data;
            delete mc;
            delete ratio;
        }
    }
    myFile->Close();
    delete myFile;
    
    TFile *myFile = new TFile("combination/FinalEfficiencies.root");
    for (int j=0 ; j < 2 ; j++){
        for (int i = 0 ; i < 5 ; i++){
            // cout << "eff2D_"+theRuns[i]+"_"+nomTrigger[j]+"_data" << endl;
            TH2F *data = (TH2F*) myFile->Get("effTrigger_"+theRuns[i]+"_"+nomTrigger[j]+"_data");
            TH2F *mc = (TH2F*) myFile->Get("effTrigger_"+theRuns[i]+"_"+nomTrigger[j]+"_mc");
            TH2F *ratio = (TH2F*) data->Clone("ratio");
            ratio->Divide(data,mc,1,1);
            cout << theRuns[i] << " " << data->GetBinContent(2,2) << " " << data->GetBinError(2,2);
            cout << " " <<  mc->GetBinContent(2,2) << " " << mc->GetBinError(2,2);
            cout << " " << ratio->GetBinContent(2,2) << " " << ratio->GetBinError(2,2) << endl;
            delete data;
            delete mc;
            delete ratio;
        }
    }
    myFile->Close();
    delete myFile;

}
