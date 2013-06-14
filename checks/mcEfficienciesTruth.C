TFile *myFile = new TFile("theOutFile.root","RECREATE");

TChain *chain = new TChain("tpTree/fitter_tree");


void the2Defficiencies(float *etaBins, int theNbOfBins){
    TH2F *hDenom = new TH2F("hDenom","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hDenom","pt<20&&pt>10&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1");
  //  hDenom->Write();
    
    TH2F *hNum = new TH2F("hNum","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hNum","pt<20&&pt>10&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1&&passMu17Mu8==1");
  //  hNum->Write();
    
    TH2F *hEffi = (TH2F*) hNum->Clone("hEffi");
    hEffi->Sumw2();
    hEffi->Divide(hNum, hDenom, 1, 1);
    hEffi->Write("effLowPt");
    
    delete hDenom;
    delete hNum;
    delete hEffi;
    
    TH2F *hDenom = new TH2F("hDenom","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hDenom","pt>20&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1");
  //  hDenom->Write();
    
    TH2F *hNum = new TH2F("hNum","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hNum","pt>20&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1&&passMu17Mu8==1");
 //   hNum->Write();
    
    TH2F *hEffi = (TH2F*) hNum->Clone("hEffi");
    hEffi->Sumw2();
    hEffi->Divide(hNum, hDenom, 1, 1);
    hEffi->Write("effHighPt");
    
    delete hDenom;
    delete hNum;
    delete hEffi;
}

TH2F *doThePlot2DHigh(float *etaBins, int theNbOfBins, TH1F *histo1D){
    TH2F *result = new TH2F("result","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    
    for (int i = 0 ; i<theNbOfBins; i++){
        float effI = histo1D->GetBinContent(i+1);
        float relatErrI = histo1D->GetBinError(i+1)/histo1D->GetBinContent(i+1);
        for (int j = 0 ; j < theNbOfBins ; j++){
            float effJ = histo1D->GetBinContent(j+1);
            float relatErrJ = histo1D->GetBinError(j+1)/histo1D->GetBinContent(j+1);
            float value = 1-(1-effI)*(1-effJ);
            float erreur = (i==j)? 2*effJ*relatErrJ : value*sqrt(relatErrI*relatErrI+relatErrJ*relatErrJ);
            //cout << "i=" << i << " j=" << j << " " << value << " +/- " << erreur << endl;
            result->SetBinContent(i+1, j+1, value);
            result->SetBinError(i+1, j+1, erreur);
        }
        
    }
    
    return result;
}


TH2F *doThePlot2DLow(float *etaBins, int theNbOfBins, TH1F *histo1DHigh, TH1F *histo1DLow){
    TH2F *result = new TH2F("result","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    
    for (int i = 0 ; i<theNbOfBins; i++){
        float effI = histo1DHigh->GetBinContent(i+1);
        float relatErrI = histo1DHigh->GetBinError(i+1)/histo1DHigh->GetBinContent(i+1);
        for (int j = 0 ; j < theNbOfBins ; j++){
            float effJ = histo1DLow->GetBinContent(j+1);
            float relatErrJ = histo1DLow->GetBinError(j+1)/histo1DLow->GetBinContent(j+1);
            float value = 1-(1-effI)*(1-effJ);
            float erreur = value*sqrt(relatErrI*relatErrI+relatErrJ*relatErrJ);
            //cout << "i=" << i << " j=" << j << " " << value << " +/- " << erreur << endl;
            result->SetBinContent(i+1, j+1, value);
            result->SetBinError(i+1, j+1, erreur);
        }
        
    }
    
    return result;
}

void the1Defficiencies(float *etaBins, int theNbOfBins){
    TH1F *hNum = new TH1F("hNum1D_High","",theNbOfBins, etaBins);
    chain->Draw("abseta>>hNum1D_High","pt>20&&tag_pt>25&&tag_Tight2012&&mass>80&&mass<100&&mcTrue==1&&tag_Mu17==1&&Mu17==1");
  //  hNum->Write();
    
    TH1F *hDenom = new TH1F("hDenom1D_High","",theNbOfBins, etaBins);
    chain->Draw("abseta>>hDenom1D_High","pt>20&&tag_pt>25&&tag_Tight2012&&mass>80&&mass<100&&mcTrue==1&&tag_Mu17==1");
  //  hNum->Write();
    
    TH1F *heffi = (TH1F*) hNum->Clone("hEffi1D_High");
    heffi->Sumw2();
    heffi->Divide(hNum, hDenom, 1, 1);
    heffi->Write("eff1D_High");
    
    TH2F *h2Dcomputed = (TH2F*) doThePlot2DHigh(etaBins, theNbOfBins, heffi);
    h2Dcomputed->Write("eff2Dcomputed_High");
    delete h2Dcomputed;
    
    
    delete hNum;
    delete hDenom;
    
    TH1F *hNum = new TH1F("hNum1D_Low","",theNbOfBins, etaBins);
    chain->Draw("abseta>>hNum1D_Low","pt>10&&pt<20&&tag_pt>25&&tag_Tight2012&&mass>80&&mass<100&&mcTrue==1&&tag_Mu17==1&&Mu17==1");
  //  hNum->Write();
    
    TH1F *hDenom = new TH1F("hDenom1D_Low","",theNbOfBins, etaBins);
    chain->Draw("abseta>>hDenom1D_Low","pt>10&&pt<20&&tag_pt>25&&tag_Tight2012&&mass>80&&mass<100&&mcTrue==1&&tag_Mu17==1");
  //  hNum->Write();
    
    TH1F *heffiL = (TH1F*) hNum->Clone("hEffi1DL");
    heffiL->Sumw2();
    heffiL->Divide(hNum, hDenom, 1, 1);
    heffiL->Write("eff1D_Low");
    
    TH2F *h2Dcomputed = (TH2F*) doThePlot2DLow(etaBins, theNbOfBins, heffi, heffiL);
    h2Dcomputed->Write("eff2Dcomputed_Low");
    delete h2Dcomputed;
    
    delete hNum;
    delete hDenom;
    delete heffiL;
    delete heffi;

}

void the2DefficienciesRef(float *etaBins, int theNbOfBins){
    TH2F *hDenom = new TH2F("hDenom","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hDenom","pt<20&&pt>10&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1");
  //  hDenom->Write();
    
    TH2F *hNum = new TH2F("hNum","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hNum","pt<20&&pt>10&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1&&(Mu17||tag_Mu17)");
  //  hNum->Write();
    
    TH2F *hEffi = (TH2F*) hNum->Clone("hEffi");
    hEffi->Sumw2();
    hEffi->Divide(hNum, hDenom, 1, 1);
    hEffi->Write("effLowPtRef");
    
    delete hDenom;
    delete hNum;
    delete hEffi;
    
    TH2F *hDenom = new TH2F("hDenom","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hDenom","pt>20&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1");
  //  hDenom->Write();
    
    TH2F *hNum = new TH2F("hNum","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hNum","pt>20&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1&&(Mu17||tag_Mu17)");
 //   hNum->Write();
    
    TH2F *hEffi = (TH2F*) hNum->Clone("hEffi");
    hEffi->Sumw2();
    hEffi->Divide(hNum, hDenom, 1, 1);
    hEffi->Write("effHighPtRef");
    
    delete hDenom;
    delete hNum;
    delete hEffi;
}
void the2DefficienciesSoup(float *etaBins, int theNbOfBins){
    TH2F *hDenom = new TH2F("hDenom","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hDenom","pt<20&&pt>10&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1&&(Mu17||tag_Mu17)");
    //hDenom->Write("hStat_High");
    
    TH2F *hNum = new TH2F("hNum","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hNum","pt<20&&pt>10&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1&&(Mu17||tag_Mu17)&&passMu17Mu8==1");
    //hNum->Write();
    
    TH2F *hEffi = (TH2F*) hNum->Clone("hEffi");
    hEffi->Sumw2();
    hEffi->Divide(hNum, hDenom, 1, 1);
    hEffi->Write("effLowPt_Soup");
    
    delete hDenom;
    delete hNum;
    delete hEffi;
    
    TH2F *hDenom = new TH2F("hDenom","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hDenom","pt>20&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1&&(Mu17||tag_Mu17)");
//    hDenom->Write("hStat_Low");
    
    TH2F *hNum = new TH2F("hNum","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hNum","pt>20&&tag_pt>20&&mass>80&&mass<100&&mcTrue==1&&(Mu17||tag_Mu17)&&passMu17Mu8==1");
 //   hNum->Write();
    
    TH2F *hEffi = (TH2F*) hNum->Clone("hEffi");
    hEffi->Sumw2();
    hEffi->Divide(hNum, hDenom, 1, 1);
    hEffi->Write("effHighPt_Soup");
    
    delete hDenom;
    delete hNum;
    delete hEffi;
}
void the2DStat(float *etaBins, int theNbOfBins){
    TH2F *hDenom = new TH2F("hDenom","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hDenom","pt<20&&pt>10&&tag_pt>20&&mass>50&&mcTrue==1");
    hDenom->Write("hStat_Low");
    delete hDenom;

    
    TH2F *hDenom = new TH2F("hDenom","",theNbOfBins, etaBins, theNbOfBins, etaBins);
    chain->Draw("abseta:tag_abseta>>hDenom","pt>20&&tag_pt>20&&mass>50&&mcTrue==1");
    hDenom->Write("hStat_High");
    delete hDenom;

}

mcEfficienciesTruth(){
   // float etaBins[9] = {0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4};
  //  int nbOfBins =  8;
    
    float etaBins[5] = {0,  0.6,  1.2, 1.8,  2.4};
    int nbOfBins =  4;
    
    //chain->Add("/afs/cern.ch/work/h/hbrun/pogTnPr7SoupWithLooseBestZOnePairBiasNoRef/tnpZ_MC53X_DYJetsUnbiasedBigStat.root");
    chain->Add("/tmp/hbrun/tnpZ_withMuIDTop.root");
    
    
    // fill the histo of soup efficiency without ref trigger
    the2Defficiencies(etaBins, nbOfBins);
    the1Defficiencies(etaBins, nbOfBins);
    the2DefficienciesRef(etaBins, nbOfBins);
    the2DefficienciesSoup(etaBins, nbOfBins);
    the2DStat(etaBins, nbOfBins);
    


    
    myFile->Close();
    delete myFile;
}