TFile *myFile = new TFile("Mu17refPlot.root");

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
    theHisto->SetTitle("Mu17, "+title);
	theHisto->GetXaxis()->SetTitle("#mu_{1} |#eta|");
    theHisto->GetXaxis()->SetNoExponent();
	theHisto->GetXaxis()->SetMoreLogLabels();
    theHisto->GetYaxis()->SetNoExponent();
	theHisto->GetYaxis()->SetMoreLogLabels();
	theHisto->GetYaxis()->SetTitle("#mu_{2} |#eta|");
	theHisto->GetZaxis()->SetLabelSize(0.02);
	theHisto->SetAxisRange(0.5,1.,"Z");
    theHisto->SetMarkerSize(1.7);
	theHisto->SetMarkerColor(kRed-9);

	theHisto->Draw("COLZTEXTE");
    
    /*TLatex t;
    t.SetNDC();
    t.SetTextSize(0.04);
    t.DrawLatex(0.3,0.93,title);*/
	
	c0->Print("effPlots/"+nom+".pdf");
	
	/*c0->SetLogy();
	c0->SetLogx();
    c0->Print("effPlots/"+nom+"_log.pdf");*/
    
	
}



drawThePlot(){
    gStyle->SetOptStat(0);
   /* drawMyPlot("eff2D_all_data","all 2012, data ");
    drawMyPlot("eff2D_runA_data","run A, data ");
    drawMyPlot("eff2D_runB_data","run B, data");
    drawMyPlot("eff2D_runC_data","run C, data");
    drawMyPlot("eff2D_runD_data","run D, data");

    drawMyPlot("eff2D_all_mc","all 2012, mc ");
    drawMyPlot("eff2D_runA_mc","run A, mc ");
    drawMyPlot("eff2D_runB_mc","run B, mc");
    drawMyPlot("eff2D_runC_mc","run C, mc");
    drawMyPlot("eff2D_runD_mc","run D, mc");*/
    
    TString runPeriod[5] = {"runA","runB","runC","runD","all"};
    TString type[2] = {"data","mc"};
    for (int i = 0; i < 2 ; i++){
        for (int j = 0 ; j<5 ; j++){
            for (int k = 0 ; k<2 ; k++){
                drawMyPlot(Form("eff2D_ptbin%i_",k)+runPeriod[j]+"_"+type[i],runPeriod[j]+", "+type[i]+Form(", P_{T}bin_%i",k));
            }
        }
    }
    
    

}
