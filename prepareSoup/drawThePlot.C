TFile *myFile = new TFile("OrSoupPlot.root");

drawMyPlot(TString nom, TString title){
	UInt_t Number = 2;
	Double_t Red[2]    = { 1.00, 0.00};
	Double_t Green[2]  = { 1.00, 0.00};
	Double_t Blue[2]   = { 1.00, 1.00};
	Double_t Length[2] = { 0.00, 1.0};
	Int_t nb=50;
	TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
    
	TH2F *theHisto = (TH2F*) myFile->Get(nom);
	
	TCanvas *c0 = new TCanvas("c0","coucou",600,600);
	c0->SetFillColor(0);
    theHisto->SetTitle(title);
	theHisto->GetXaxis()->SetTitle("#mu Tag p_{T} (GeV/c)");
	theHisto->GetXaxis()->SetNoExponent();
	theHisto->GetXaxis()->SetMoreLogLabels();
    theHisto->GetYaxis()->SetNoExponent();
	theHisto->GetYaxis()->SetMoreLogLabels();
	theHisto->GetYaxis()->SetTitle("#mu Probe p_{T} (GeV/c)");
	theHisto->GetZaxis()->SetTitle("");
	theHisto->GetZaxis()->SetLabelSize(0.01);
	theHisto->SetAxisRange(0.,1.,"Z");
	theHisto->SetMarkerSize(1.7);
	theHisto->SetMarkerColor(kRed-9);
	theHisto->Draw("COLZTEXTE");
    
    /*TLatex t;
    t.SetNDC();
    t.SetTextSize(0.04);
    t.DrawLatex(0.3,0.93,title);*/
	
	c0->Print("effPlots/"+nom+".pdf");
	
	c0->SetLogy();
	c0->SetLogx();
    c0->Print("effPlots/"+nom+"_log.pdf");
    
	
}



drawThePlot(){
    gStyle->SetOptStat(0);
    drawMyPlot("eff2D_all_passMu17Mu8_data","Mu17_Mu8 after Mu17, data all 2012");
    drawMyPlot("eff2D_all_passMu17TkMu8_data","Mu17_TkMu8 after Mu17, data all 2012");
    drawMyPlot("eff2D_all_passORdiMu_data","Mu17_Mu8 OR Mu17_TkMu8 after Mu17, data all 2012");
   
    drawMyPlot("eff2D_runA_passMu17Mu8_data","Mu17_Mu8 after Mu17, data run A");
    drawMyPlot("eff2D_runA_passMu17TkMu8_data","Mu17_TkMu8 after Mu17, data run A");
    drawMyPlot("eff2D_runA_passORdiMu_data","Mu17_Mu8 OR Mu17_TkMu8 after Mu17, data run A");

    drawMyPlot("eff2D_runB_passMu17Mu8_data","Mu17_Mu8 after Mu17, data run B");
    drawMyPlot("eff2D_runB_passMu17TkMu8_data","Mu17_TkMu8 after Mu17, data run B");
    drawMyPlot("eff2D_runB_passORdiMu_data","Mu17_Mu8 OR Mu17_TkMu8 after Mu17, data run B");
    
    drawMyPlot("eff2D_runC_passMu17Mu8_data","Mu17_Mu8 after Mu17, data run C");
    drawMyPlot("eff2D_runC_passMu17TkMu8_data","Mu17_TkMu8 after Mu17, data run C");
    drawMyPlot("eff2D_runC_passORdiMu_data","Mu17_Mu8 OR Mu17_TkMu8 after Mu17, data run C");
    
    drawMyPlot("eff2D_runD_passMu17Mu8_data","Mu17_Mu8 after Mu17, data run D");
    drawMyPlot("eff2D_runD_passMu17TkMu8_data","Mu17_TkMu8 after Mu17, data run D");
    drawMyPlot("eff2D_runD_passORdiMu_data","Mu17_Mu8 OR Mu17_TkMu8 after Mu17, data run D");

}
