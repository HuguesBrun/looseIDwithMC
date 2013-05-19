
TFile *myOutFile = new TFile("OrSoupPlot.root","RECREATE");
TString runPeriod[5] = {"runA","runB","runC","runD","all"};
TString theTypeName[3] = {"passORdiMu","passMu17Mu8","passMu17TkMu8"};
TString theType[2] = {"data","mc"};

doTheSoupPlot(){
    for(int i =0 ; i< 2 ; i++){
    for (int k=0 ; k<5 ; k++){
        for (int m=0; m<3 ; m++){
            cout << "i=" << i << " k=" << k << " m=" << m << endl;
            TFile *myInFile = new TFile("theEfficiencyPlots_"+theType[i]+"_"+runPeriod[k]+"_"+theTypeName[m]+".root");
            cout << theTypeName[m]+"NodZ_ptEta_tag_pt_pt_PLOT_abseta_bin0_&_tag_abseta_bin0" << endl;
            if (m==0) TH2F *theEffPlot = (TH2F*) myInFile->Get(theTypeName[m]+"NodZ_ptEta_tag_pt_pt_PLOT_abseta_bin0_&_tag_abseta_bin0");
            else TH2F *theEffPlot = (TH2F*) myInFile->Get(theTypeName[m]+"NoDz_ptEta_tag_pt_pt_PLOT_abseta_bin0_&_tag_abseta_bin0");
            myOutFile->cd();
            theEffPlot->Write("eff2D_"+runPeriod[k]+"_"+theTypeName[m]+"_"+theType[i]);
        }
    }
    }
        
}
//passORdiMuNodZ_ptEta_pt_tag_pt_PLOT_abseta_bin0_&_tag_abseta_bin0
//passORdiMuNodZ_ptEta_tag_pt_pt_PLOT_abseta_bin0_&_tag_abseta_bin0
//passORdiMuNodZ_ptEta_tag_pt_pt_PLOT_abseta_bin0_&_tag_abseta_bin0
//passORdiMuNoDz_ptEta_tag_pt_pt_PLOT_abseta_bin0_&_tag_abseta_bin0