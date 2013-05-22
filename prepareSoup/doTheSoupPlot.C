
TFile *myOutFile = new TFile("OrSoupPlot.root","RECREATE");
TString runPeriod[6] = {"runA","runB","runC","runD","all","3first"};
TString theTypeName[3] = {"passORdiMu","passMu17Mu8","passMu17TkMu8"};
TString theType[2] = {"data","mc"};

float theEta[4] = {0,1, 2.1,2.4};


doTheSoupPlot(){
    for(int i =0 ; i< 2 ; i++){
    for (int k=0 ; k<6 ; k++){
        for (int m=0; m<3 ; m++){
            double x;
            double y;
            TFile *myInFile = new TFile("theEfficiencyPlots_"+theType[i]+"_"+runPeriod[k]+"_"+theTypeName[m]+".root");

            TH2F *theEffPlot = new TH2F("theEffPlot","the Eff plot",3, theEta, 3, theEta);
            TGraphAsymmErrors *theGraph0 = (TGraphAsymmErrors*) myInFile->Get(theTypeName[m]+"_ptEta_abseta_PLOT_pt_bin0_&_tag_abseta_bin0_&_tag_pt_bin1");
            TGraphAsymmErrors *theGraph1 = (TGraphAsymmErrors*) myInFile->Get(theTypeName[m]+"_ptEta_abseta_PLOT_pt_bin0_&_tag_abseta_bin1_&_tag_pt_bin1");
 			theGraph0->GetPoint(0, x, y);
			theEffPlot->SetBinContent(1, 1, y);
			theEffPlot->SetBinError(1, 1, theGraph0->GetErrorY(0));
            theGraph0->GetPoint(1, x, y);
			theEffPlot->SetBinContent(1,2, y);
			theEffPlot->SetBinError(1, 2, theGraph0->GetErrorY(1));
            
            theGraph1->GetPoint(0, x, y);
			theEffPlot->SetBinContent(2, 1, y);
			theEffPlot->SetBinError(2, 1, theGraph0->GetErrorY(0));
            theGraph1->GetPoint(1, x, y);
			theEffPlot->SetBinContent(2,2, y);
			theEffPlot->SetBinError(2, 2, theGraph0->GetErrorY(1));
            
            myOutFile->cd();
            if (k==5) theEffPlot->Write("eff2D_ptbin0_runABC_"+theTypeName[m]+"_"+theType[i]);
            else theEffPlot->Write("eff2D_ptbin0_"+runPeriod[k]+"_"+theTypeName[m]+"_"+theType[i]);
            delete theEffPlot;
        
            TH2F *theEffPlot = new TH2F("theEffPlot","the Eff plot",3, theEta, 3, theEta);
            TGraphAsymmErrors *theGraph0 = (TGraphAsymmErrors*) myInFile->Get(theTypeName[m]+"_ptEta_abseta_PLOT_pt_bin1_&_tag_abseta_bin0_&_tag_pt_bin1");
            TGraphAsymmErrors *theGraph1 = (TGraphAsymmErrors*) myInFile->Get(theTypeName[m]+"_ptEta_abseta_PLOT_pt_bin1_&_tag_abseta_bin1_&_tag_pt_bin1");
 			theGraph0->GetPoint(0, x, y);
			theEffPlot->SetBinContent(1, 1, y);
			theEffPlot->SetBinError(1, 1, theGraph0->GetErrorY(0));
            theGraph0->GetPoint(1, x, y);
			theEffPlot->SetBinContent(1,2, y);
			theEffPlot->SetBinError(1, 2, theGraph0->GetErrorY(1));
            
            theGraph1->GetPoint(0, x, y);
			theEffPlot->SetBinContent(2, 1, y);
			theEffPlot->SetBinError(2, 1, theGraph0->GetErrorY(0));
            theGraph1->GetPoint(1, x, y);
			theEffPlot->SetBinContent(2,2, y);
			theEffPlot->SetBinError(2, 2, theGraph0->GetErrorY(1));
            
            myOutFile->cd();
            if (k==5) theEffPlot->Write("eff2D_ptbin1_runABC_"+theTypeName[m]+"_"+theType[i]);
            else theEffPlot->Write("eff2D_ptbin1_"+runPeriod[k]+"_"+theTypeName[m]+"_"+theType[i]);

        
        }
    }
    }
        
}
