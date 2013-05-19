TFile *myFile = new TFile("SFfile.root");

drawMyPlot(TString nom, TString title){
	/*UInt_t Number = 2;
	Double_t Red[2]    = { 1.00, 0.00};
	Double_t Green[2]  = { 1.00, 0.00};
	Double_t Blue[2]   = { 1.00, 1.00};
	Double_t Length[2] = { 0.00, 1.0};
	Int_t nb=50;
	TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);*/
    
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
	theHisto->SetAxisRange(0.5,1.5,"Z");
	theHisto->SetMarkerSize(1.7);
	theHisto->SetMarkerColor(kBlack);
	theHisto->Draw("COLZTEXTE");
    
    /*TLatex t;
    t.SetNDC();
    t.SetTextSize(0.04);
    t.DrawLatex(0.3,0.93,title);*/
	
	//c0->Print("effPlots/"+nom+".pdf");
	
	c0->SetLogy();
	c0->SetLogx();
    c0->Print("SFplots/"+nom+"_log.pdf");
    
	
}



drawTheSFPlot(){
    gStyle->SetOptStat(0);
    drawMyPlot("SF_all_passMu17Mu8","Mu17_Mu8, all 2012");
    drawMyPlot("SF_all_passMu17TkMu8","Mu17_TkMu8, all 2012");
    drawMyPlot("SF_all_passORdiMu","Mu17_Mu8 OR Mu17_TkMu8, all 201");
   
    drawMyPlot("SF_runA_passMu17Mu8","Mu17_Mu8, run A");
    drawMyPlot("SF_runA_passMu17TkMu8","Mu17_TkMu8, run A");
    drawMyPlot("SF_runA_passORdiMu","Mu17_Mu8 OR Mu17_TkMu8, run A");
    
    drawMyPlot("SF_runB_passMu17Mu8","Mu17_Mu8, run B");
    drawMyPlot("SF_runB_passMu17TkMu8","Mu17_TkMu8, run B");
    drawMyPlot("SF_runB_passORdiMu","Mu17_Mu8 OR Mu17_TkMu8, run B");
    
    drawMyPlot("SF_runC_passMu17Mu8","Mu17_Mu8, run C");
    drawMyPlot("SF_runC_passMu17TkMu8","Mu17_TkMu8, run C");
    drawMyPlot("SF_runC_passORdiMu","Mu17_Mu8 OR Mu17_TkMu8, run C");
    
    drawMyPlot("SF_runD_passMu17Mu8","Mu17_Mu8, run D");
    drawMyPlot("SF_runD_passMu17TkMu8","Mu17_TkMu8, run D");
    drawMyPlot("SF_runD_passORdiMu","Mu17_Mu8 OR Mu17_TkMu8, run D");

    
  

}
