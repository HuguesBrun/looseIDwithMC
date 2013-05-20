


TFile *myOutFile = new TFile("Mu17refPlot.root","RECREATE");
float ptBins[3] = {10,20,100};
float etaBins[5] = {0,1.2,2.4};
//float ptBins[3] = {10,20,100};
TString runPeriod[5] = {"runA","runB","runC","runD","all"};
TString type[2] = {"data","mc"};

doTheRefPlot(){
    for (int m=0 ; m<2 ; m++){
        for (int k=0 ; k<5 ; k++){
            TFile *myInFile = new TFile("theEfficiencyPlots_"+type[m]+"_"+runPeriod[k]+".root");
            TGraphAsymmErrors *theEffPlot0 = (TGraphAsymmErrors*) myInFile->Get("Mu8_ptEta_abseta_PLOT_pt_bin0");
            //if (m==1) theEffPlot0 = (TGraphAsymmErrors*) myInFile->Get("Mu17_ptEta_abseta_PLOT_pt_bin0");
            TGraphAsymmErrors *theEffPlot1 = (TGraphAsymmErrors*) myInFile->Get("Mu8_ptEta_abseta_PLOT_pt_bin1");
            //if (m==1) theEffPlot1 = (TGraphAsymmErrors*) myInFile->Get("Mu17_ptEta_abseta_PLOT_pt_bin1");

            cout << "m=" << m << " k=" << k << endl;
            TH2F *eff2D = new TH2F("eff2D_ptbin0_"+runPeriod[k]+"_"+type[m],"",2,etaBins,2,etaBins);
            int points = theEffPlot0->GetN();
            double x,y;
            double x2,y2;
            double theError, theError2, theErrorTot;
            for (int i=0 ; i<points; i++){
                theEffPlot0->GetPoint(i, x, y);
                theError = theEffPlot0->GetErrorY(i);
                for (int j=0 ; j<points ; j++){
                    theEffPlot1->GetPoint(j, x2, y2);
                    theError2 = theEffPlot1->GetErrorY(j);
                    cout << "i=" << i << ", x=" << x << ", y=" << y << endl;
                    cout << "j=" << j << ", x=" << x2 << ", y=" << y2 << endl;
                    double theRealEff = (double) 1.0-(1.-y2)*(1.-y);
                    theErrorTot = sqrt(theError*theError+theError2*theError2);
                    eff2D->SetBinContent(i+1,j+1,theRealEff);
                    eff2D->SetBinError(i+1,j+1,theErrorTot);
                }
            }
            myOutFile->cd();
            eff2D->Write();
            delete eff2D;
            
            TH2F *eff2D = new TH2F("eff2D_ptbin1_"+runPeriod[k]+"_"+type[m],"",2,etaBins,2,etaBins);
            int points = theEffPlot0->GetN();
            double x,y;
            double x2,y2;
            double theError, theError2, theErrorTot;
            for (int i=0 ; i<points; i++){
                theEffPlot1->GetPoint(i, x, y);
                theError = theEffPlot1->GetErrorY(i);
                for (int j=0 ; j<points ; j++){
                    theEffPlot1->GetPoint(j, x2, y2);
                    theError2 = theEffPlot1->GetErrorY(j);
                    cout << "i=" << i << ", x=" << x << ", y=" << y << endl;
                    cout << "j=" << j << ", x=" << x2 << ", y=" << y2 << endl;
                    double theRealEff = (double) 1.0-(1.-y2)*(1.-y);
                    theErrorTot = sqrt(theError*theError+theError2*theError2);
                    eff2D->SetBinContent(i+1,j+1,theRealEff);
                    eff2D->SetBinError(i+1,j+1,theErrorTot);
                }
            }
            myOutFile->cd();
            eff2D->Write();
        }
    }
}
