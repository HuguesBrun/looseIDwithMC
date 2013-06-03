


TFile *myOutFile = new TFile("Mu17refPlot.root","RECREATE");
float ptBins[3] = {10,20,100};
//float ptBins[3] = {10,20,100};
TString runPeriod[5] = {"runA","runB","runC","runD","all"};
TString type[2] = {"data","mc"};

doTheRefPlot(){
    for (int m=0 ; m<2 ; m++){
        for (int k=0 ; k<5 ; k++){
            TFile *myInFile = new TFile("theEfficiencyPlots_"+type[m]+"_"+runPeriod[k]+".root");
            TGraphAsymmErrors *theEffPlot = (TGraphAsymmErrors*) myInFile->Get("Mu8_ptEta_pt_PLOT");
           // if (m==1) theEffPlot = (TGraphAsymmErrors*) myInFile->Get("Mu17_ptEta_pt_PLOT");

            TH2F *eff2D = new TH2F("eff2D_"+runPeriod[k]+"_"+type[m],"",2,ptBins,2,ptBins);
            int points = theEffPlot->GetN();
            double x,y;
            double x2,y2;
            double theError, theError2, theErrorTot;
            for (int i=0 ; i<points; i++){
                theEffPlot->GetPoint(i, x, y);
                theError = theEffPlot->GetErrorY(i)/y;
                for (int j=0 ; j<points ; j++){
                    theEffPlot->GetPoint(j, x2, y2);
                    theError2 = theEffPlot->GetErrorY(j)/y;
                    cout << "i=" << i << ", x=" << x << ", y=" << y << endl;
                    cout << "j=" << j << ", x=" << x2 << ", y=" << y2 << endl;
                    double theRealEff = (double) 1.0-(1.-y2)*(1.-y);
                    theErrorTot = theRealEff*sqrt(theError*theError+theError2*theError2);
                    if (i==j) theErrorTot=2*theError;
                    eff2D->SetBinContent(i+1,j+1,theRealEff);
                    eff2D->SetBinError(i+1,j+1,theErrorTot);
                }
            }
            myOutFile->cd();
            eff2D->Write();
        }
    }
}
