TFile *myFileOut = new TFile("FinalEfficiencies.root","RECREATE");
TString runPeriod[5] = {"runA","runB","runC","runD","all"};
TString theTypeName[3] = {"passORdiMu","passMu17Mu8","passMu17TkMu8"};
TString theType[2] = {"data","mc"};

doFinalHisto(){
    TFile *refFile = new TFile("Mu17refPlot.root");
    TFile *soupFile = new TFile("OrSoupPlot.root");

    for (int n=0 ; n<2 ; n++){
    for (int k=0; k<5 ; k++){
        TH2F *refPlot = (TH2F*) refFile->Get("eff2D_ptbin0_"+runPeriod[k]+"_"+theType[n]);
        for (int m=0 ; m<3 ; m++){
        TH2F *soupPlot = (TH2F*) soupFile->Get("eff2D_ptbin0_"+runPeriod[k]+"_"+theTypeName[m]+"_"+theType[n]);
    
        int nBinX = refPlot->GetXaxis()->GetNbins();
        int nBinY = refPlot->GetYaxis()->GetNbins();
    
        //  cout << "nBinX="<< nBinX << " nBinY=" << nBinY << endl;
        TH2F *finalPlot = (TH2F*) refPlot->Clone();

        for (int i = 0 ; i < nBinX; i++){
            for (int j=0 ; j < nBinY ; j++){
                // cout << "i=" << i << " j=" << j << endl;
                //cout << "ref=" << refPlot->GetBinContent(i+1, j+1) << endl;
                //cout << "soup=" << soupPlot->GetBinContent(i+1, j+1) << endl;
                float theValue = refPlot->GetBinContent(i+1, j+1)*soupPlot->GetBinContent(i+1, j+1);
                // cout << "theValue=" << theValue << endl;
                float theError = sqrt(refPlot->GetBinError(i+1, j+1)*refPlot->GetBinError(i+1, j+1)+soupPlot->GetBinError(i+1, j+1)*soupPlot->GetBinError(i+1, j+1));
                finalPlot->SetBinContent(i+1, j+1, theValue);
                finalPlot->SetBinError(i+1, j+1, theError);
            }
        
        }
        myFileOut->cd();
        finalPlot->Write("effTrigger_ptbin0_"+runPeriod[k]+"_"+theTypeName[m]+"_"+theType[n]);
        }
        
        TH2F *refPlot = (TH2F*) refFile->Get("eff2D_ptbin1_"+runPeriod[k]+"_"+theType[n]);
        for (int m=0 ; m<3 ; m++){
            TH2F *soupPlot = (TH2F*) soupFile->Get("eff2D_ptbin1_"+runPeriod[k]+"_"+theTypeName[m]+"_"+theType[n]);
            
            int nBinX = refPlot->GetXaxis()->GetNbins();
            int nBinY = refPlot->GetYaxis()->GetNbins();
            
            //  cout << "nBinX="<< nBinX << " nBinY=" << nBinY << endl;
            TH2F *finalPlot = (TH2F*) refPlot->Clone();
            
            for (int i = 0 ; i < nBinX; i++){
                for (int j=0 ; j < nBinY ; j++){
                    // cout << "i=" << i << " j=" << j << endl;
                    //cout << "ref=" << refPlot->GetBinContent(i+1, j+1) << endl;
                    //cout << "soup=" << soupPlot->GetBinContent(i+1, j+1) << endl;
                    float theValue = refPlot->GetBinContent(i+1, j+1)*soupPlot->GetBinContent(i+1, j+1);
                    // cout << "theValue=" << theValue << endl;
                    float theError = sqrt(refPlot->GetBinError(i+1, j+1)*refPlot->GetBinError(i+1, j+1)+soupPlot->GetBinError(i+1, j+1)*soupPlot->GetBinError(i+1, j+1));
                    finalPlot->SetBinContent(i+1, j+1, theValue);
                    finalPlot->SetBinError(i+1, j+1, theError);
                }
                
            }
            myFileOut->cd();
            finalPlot->Write("effTrigger_ptbin1_"+runPeriod[k]+"_"+theTypeName[m]+"_"+theType[n]);
        }
    }
    }
}
