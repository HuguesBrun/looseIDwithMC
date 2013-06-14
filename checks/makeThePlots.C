TFile *myFile = new TFile("theOutFile.root");

drawFinalyThePlot(TH2F *histo, TString title, TString nomToSave){
    TCanvas *c0 = new TCanvas("c0","coucou",600,600);
    c0->SetFillColor(0);
    histo->SetTitle(title);
	histo->GetXaxis()->SetTitle("#mu_{1} #eta");
	histo->GetXaxis()->SetNoExponent();
	histo->GetXaxis()->SetMoreLogLabels();
	histo->GetXaxis()->SetLabelOffset(0.1);
    histo->GetYaxis()->SetNoExponent();
	histo->GetYaxis()->SetMoreLogLabels();
	histo->GetYaxis()->SetTitle("#mu_{2} #eta");
    histo->GetYaxis()->SetLabelOffset(0.1);
	histo->GetZaxis()->SetTitle("");
	histo->GetZaxis()->SetLabelSize(0.01);
	//histo->SetAxisRange(0.5,1.5,"Z");
	histo->SetMarkerSize(1.7);
	histo->SetMarkerColor(kBlack);
	histo->Draw("COLZTEXTE");
    
    c0->Print("plots/"+nomToSave+".png");
    
}


makeThePlots(){
    gStyle->SetOptStat(0);
    
    
    /// zone to do the Ref histos
    TH2F *TrueHistoHigh = (TH2F*) myFile->Get("effHighPt");
    drawFinalyThePlot(TrueHistoHigh, "Eff true, P_{T} > 20 GeV/c", "effHighPt");
    
    TH2F *TrueHistoLow = (TH2F*) myFile->Get("effLowPt");
    drawFinalyThePlot(TrueHistoLow, "Eff true, 10 < P_{T} < 20 GeV/c", "effLowPt");

    
    // compute the Ref efficiencies from 1D
    TH2F *eff2Dcomputed_High = (TH2F*) myFile->Get("eff2Dcomputed_High");
    drawFinalyThePlot(eff2Dcomputed_High, "Ref trigger, P_{T} > 20 GeV/c", "eff2Dcomputed_High");
    
    TH2F *eff2Dcomputed_Low = (TH2F*) myFile->Get("eff2Dcomputed_Low");
    drawFinalyThePlot(eff2Dcomputed_Low, "Ref trigger, 10 < P_{T} < 20 GeV/c", "eff2Dcomputed_Low");

    
    // true values of Ref efficiencies
    TH2F *effHighPtRef = (TH2F*) myFile->Get("effHighPtRef");
    drawFinalyThePlot(effHighPtRef, "Ref trigger true, P_{T} > 20 GeV/c", "effHighPtRef");
    
    TH2F *effLowPtRef = (TH2F*) myFile->Get("effLowPtRef");
    drawFinalyThePlot(effLowPtRef, "Ref trigger, 10 < P_{T} < 20 GeV/c", "effLowPtRef");
    
    // diff between Ref true and computed
    TH2F *diffRefHigh = (TH2F*) eff2Dcomputed_High->Clone("diffRefHigh");
    diffRefHigh->Add(effHighPtRef, -1);
    drawFinalyThePlot(diffRefHigh, "Ref trigger diff, P_{T} > 20 GeV/c", "effHighPtRef_diff");

    TH2F *diffRefLow = (TH2F*) eff2Dcomputed_High->Clone("diffRefLow");
    diffRefLow->Add(effLowPtRef, -1);
    drawFinalyThePlot(diffRefLow, "Ref trigger diff, 10 < P_{T} < 20 GeV/c", "effLowPtRef_diff");

    // recup the sou
    TH2F *effSoupHigh = (TH2F*) myFile->Get("effHighPt_Soup");
    TH2F *effSoupLow = (TH2F*) myFile->Get("effLowPt_Soup");
    // integration method !
    TH2F *statHigh = (TH2F*) myFile->Get("hStat_High");
    statHigh->Sumw2();
    statHigh->Scale(1.0/statHigh->Integral());
    
    TH2F *statLow = (TH2F*) myFile->Get("hStat_Low");
    statLow->Sumw2();
    statLow->Scale(1.0/statLow->Integral());
    
    // integrate true eff
    TH2F *forIntegrationHigh = (TH2F*) TrueHistoHigh->Clone("forIntegrationHigh");
    forIntegrationHigh->Sumw2();
    forIntegrationHigh->Multiply(TrueHistoHigh, statHigh,1,1);
    double errorHigh;
    float valueIntegratedHigh = forIntegrationHigh->IntegralAndError(1,4,1,4,errorHigh);
    cout << "valueTrueHigh=" << valueIntegratedHigh << " +/- " << errorHigh << endl;
    delete forIntegrationHigh;
    
    TH2F *forIntegrationLow = (TH2F*) TrueHistoLow->Clone("forIntegrationLow");
    forIntegrationLow->Sumw2();
    forIntegrationLow->Multiply(TrueHistoLow, statLow,1,1);
    double errorLow;
    float valueIntegratedLow = forIntegrationLow->IntegralAndError(1,4,1,4,errorLow);
    cout << "valueTrueLow=" << valueIntegratedLow << " +/- " << errorLow << endl;
    delete forIntegrationLow;
    
    // final efficiency from computed ref
    TH2F *finalFromComputedHigh = (TH2F*) effSoupHigh->Clone("finalFromComputedHigh");
    finalFromComputedHigh->Sumw2();
    finalFromComputedHigh->Multiply(effSoupHigh,eff2Dcomputed_High,1,1);
    drawFinalyThePlot(finalFromComputedHigh, "Final Eff, P_{T} > 20 GeV/c", "finalFromComputedHigh");

    TH2F *finalFromComputedLow = (TH2F*) effSoupHigh->Clone("finalFromComputedLow");
    finalFromComputedLow->Sumw2();
    finalFromComputedLow->Multiply(effSoupLow,eff2Dcomputed_Low,1,1);
    drawFinalyThePlot(finalFromComputedLow, "Final Eff, 10 < P_{T} < 20 GeV/c", "finalFromComputedLow");

    TH2F *forIntegrationHigh = (TH2F*) TrueHistoHigh->Clone("forIntegrationHigh");
    forIntegrationHigh->Sumw2();
    forIntegrationHigh->Multiply(finalFromComputedHigh, statHigh,1,1);
    double errorHigh;
    float valueIntegratedHigh = forIntegrationHigh->IntegralAndError(1,4,1,4,errorHigh);
    cout << "valueTrueHigh=" << valueIntegratedHigh << " +/- " << errorHigh << endl;
    delete forIntegrationHigh;
    
    TH2F *forIntegrationLow = (TH2F*) TrueHistoLow->Clone("forIntegrationLow");
    forIntegrationLow->Sumw2();
    forIntegrationLow->Multiply(finalFromComputedLow, statLow,1,1);
    double errorLow;
    float valueIntegratedLow = forIntegrationLow->IntegralAndError(1,4,1,4,errorLow);
    cout << "valueTrueLow=" << valueIntegratedLow << " +/- " << errorLow << endl;
    delete forIntegrationLow;
    
    
    finalFromComputedHigh->Add(TrueHistoHigh,-1);
    drawFinalyThePlot(finalFromComputedHigh, "Final Eff Diff, P_{T} > 20 GeV/c", "finalFromComputedHighDiff");

    finalFromComputedLow->Add(TrueHistoLow,-1);
    drawFinalyThePlot(finalFromComputedLow, "Final Eff Diff, 10 < P_{T} < 20 GeV/c", "finalFromComputedLowDiff");

    
    
    
    // final efficiency from true ref
    TH2F *finalFromTrueHigh = (TH2F*) effSoupHigh->Clone("finalFromTrueHigh");
    finalFromTrueHigh->Sumw2();
    finalFromTrueHigh->Multiply(effSoupHigh,effHighPtRef,1,1);
    drawFinalyThePlot(finalFromTrueHigh, "Final Eff, P_{T} > 20 GeV/c", "finalFromTrueHigh");
    
    TH2F *finalFromTrueLow = (TH2F*) effSoupHigh->Clone("finalFromTrueLow");
    finalFromTrueLow->Sumw2();
    finalFromTrueLow->Multiply(effSoupLow,effLowPtRef,1,1);
    drawFinalyThePlot(finalFromTrueLow, "Final Eff, 10 < P_{T} < 20 GeV/c", "finalFromTrueLow");
    
    TH2F *forIntegrationHigh = (TH2F*) TrueHistoHigh->Clone("forIntegrationHigh");
    forIntegrationHigh->Sumw2();
    forIntegrationHigh->Multiply(finalFromTrueHigh, statHigh,1,1);
    double errorHigh;
    float valueIntegratedHigh = forIntegrationHigh->IntegralAndError(1,4,1,4,errorHigh);
    cout << "valueTrueHigh=" << valueIntegratedHigh << " +/- " << errorHigh << endl;
    delete forIntegrationHigh;
    
    TH2F *forIntegrationLow = (TH2F*) TrueHistoLow->Clone("forIntegrationLow");
    forIntegrationLow->Sumw2();
    forIntegrationLow->Multiply(finalFromTrueLow, statLow,1,1);
    double errorLow;
    float valueIntegratedLow = forIntegrationLow->IntegralAndError(1,4,1,4,errorLow);
    cout << "valueTrueLow=" << valueIntegratedLow << " +/- " << errorLow << endl;
    delete forIntegrationLow;
    
    finalFromTrueHigh->Add(TrueHistoHigh,-1);
    drawFinalyThePlot(finalFromTrueHigh, "Final Eff Diff, P_{T} > 20 GeV/c", "finalFromTrueHighDiff");
    
    finalFromTrueLow->Add(TrueHistoLow,-1);
    drawFinalyThePlot(finalFromTrueLow, "Final Eff Diff, 10 < P_{T} < 20 GeV/c", "finalFromTrueLowDiff");

    
}
