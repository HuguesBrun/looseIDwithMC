#include "TTree.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TSystem.h"
#include "TH1F.h"
#include <cstdlib>
#include <cmath>



void prepareForSoupMC() {
	using namespace std;
    TTree *tIn  = (TTree *) gFile->Get("tpTree/fitter_tree");
    Float_t pt, abseta, pair_probeMultiplicity, tag_eta, tag_nVertices, mass;
    Int_t Glb, TM, PF;
	Int_t Tight2012, tag_Mu8, Mu8, DoubleMu17Mu8_Mu17leg,  DoubleMu17Mu8_Mu8leg, DoubleMu17Mu8_Mu17, DoubleMu17Mu8_Mu8, DoubleMu17TkMu8_Mu17, DoubleMu17TkMu8_TkMu8, DoubleMu17TkMu8_Mu17leg, DoubleMu17TkMu8_TkMu8leg, tag_Mu17, Mu17;
    Int_t tag_DoubleMu17Mu8_Mu17leg,  tag_DoubleMu17Mu8_Mu8leg, tag_DoubleMu17Mu8_Mu17, tag_DoubleMu17Mu8_Mu8, tag_DoubleMu17TkMu8_Mu17, tag_DoubleMu17TkMu8_TkMu8, tag_DoubleMu17TkMu8_Mu17leg, tag_DoubleMu17TkMu8_TkMu8leg;
    tIn->SetBranchAddress("pt", &pt);
    tIn->SetBranchAddress("abseta", &abseta);
    tIn->SetBranchAddress("tag_eta", &tag_eta);
    tIn->SetBranchAddress("mass", &mass);
    tIn->SetBranchAddress("pair_probeMultiplicity", &pair_probeMultiplicity);
    tIn->SetBranchAddress("Tight2012", &Tight2012);
    tIn->SetBranchAddress("tag_Mu8", &tag_Mu8);
    tIn->SetBranchAddress("Mu8", &Mu8);
    tIn->SetBranchAddress("tag_Mu17", &tag_Mu17);
    tIn->SetBranchAddress("Mu17", &Mu17);
    tIn->SetBranchAddress("Glb", &Glb);
    tIn->SetBranchAddress("TM", &TM);
    tIn->SetBranchAddress("PF", &PF);
    tIn->SetBranchAddress("tag_nVertices", &tag_nVertices);
    tIn->SetBranchAddress("DoubleMu17Mu8_Mu17leg", &DoubleMu17Mu8_Mu17leg);
    tIn->SetBranchAddress("DoubleMu17Mu8_Mu17", &DoubleMu17Mu8_Mu17);
    tIn->SetBranchAddress("DoubleMu17Mu8_Mu8leg", &DoubleMu17Mu8_Mu8leg);
  //  tIn->SetBranchAddress("DoubleMu17Mu8_Mu8", &DoubleMu17Mu8_Mu8);
    tIn->SetBranchAddress("DoubleMu17TkMu8_Mu17", &DoubleMu17TkMu8_Mu17);
  //  tIn->SetBranchAddress("DoubleMu17TkMu8_TkMu8", &DoubleMu17TkMu8_TkMu8);
    tIn->SetBranchAddress("DoubleMu17TkMu8_Mu17leg", &DoubleMu17TkMu8_Mu17leg);
    tIn->SetBranchAddress("DoubleMu17TkMu8_TkMu8leg", &DoubleMu17TkMu8_TkMu8leg);
    tIn->SetBranchAddress("tag_DoubleMu17Mu8_Mu17leg", &tag_DoubleMu17Mu8_Mu17leg);
    tIn->SetBranchAddress("tag_DoubleMu17Mu8_Mu17", &tag_DoubleMu17Mu8_Mu17);
    tIn->SetBranchAddress("tag_DoubleMu17Mu8_Mu8leg", &tag_DoubleMu17Mu8_Mu8leg);
    tIn->SetBranchAddress("tag_DoubleMu17Mu8_Mu8", &tag_DoubleMu17Mu8_Mu8);
    tIn->SetBranchAddress("tag_DoubleMu17TkMu8_Mu17", &tag_DoubleMu17TkMu8_Mu17);
    tIn->SetBranchAddress("tag_DoubleMu17TkMu8_TkMu8", &tag_DoubleMu17TkMu8_TkMu8);
    tIn->SetBranchAddress("tag_DoubleMu17TkMu8_Mu17leg", &tag_DoubleMu17TkMu8_Mu17leg);
    tIn->SetBranchAddress("tag_DoubleMu17TkMu8_TkMu8leg", &tag_DoubleMu17TkMu8_TkMu8leg);
	
    TFile *myFile = new TFile("nVtxHistoByRun.root");
    TH1F *mcPU = (TH1F*) myFile->Get("MC");
    mcPU->Scale(1.0/mcPU->Integral());
    
    TH1F *runAPU = (TH1F*) myFile->Get("runA");
    runAPU->Scale(1.0/runAPU->Integral());
    TH1F *runBPU = (TH1F*) myFile->Get("runB");
    runBPU->Scale(1.0/runBPU->Integral());
    TH1F *runCPU = (TH1F*) myFile->Get("runC");
    runCPU->Scale(1.0/runCPU->Integral());
    TH1F *runDPU = (TH1F*) myFile->Get("runD");
    runDPU->Scale(1.0/runDPU->Integral());
    
    TH1F *dataPU = (TH1F*) myFile->Get("allData");
    dataPU->Scale(1.0/dataPU->Integral());
    
    std::vector<double> weights_runA(runAPU->GetNbinsX()+1, 1.0);
    for (int i = 1, n = weights_runA.size(); i < n; ++i) {
        double nMC = mcPU->GetBinContent(i), nData = runAPU->GetBinContent(i);
        weights_runA[i-1] = (nMC > 0 ? nData/nMC : 1.0);
    }
    std::vector<double> weights_runB(runBPU->GetNbinsX()+1, 1.0);
    for (int i = 1, n = weights_runB.size(); i < n; ++i) {
        double nMC = mcPU->GetBinContent(i), nData = runBPU->GetBinContent(i);
        weights_runB[i-1] = (nMC > 0 ? nData/nMC : 1.0);
    }
    std::vector<double> weights_runC(runCPU->GetNbinsX()+1, 1.0);
    for (int i = 1, n = weights_runC.size(); i < n; ++i) {
        double nMC = mcPU->GetBinContent(i), nData = runCPU->GetBinContent(i);
        weights_runC[i-1] = (nMC > 0 ? nData/nMC : 1.0);
    }
    std::vector<double> weights_runD(runDPU->GetNbinsX()+1, 1.0);
    for (int i = 1, n = weights_runD.size(); i < n; ++i) {
        double nMC = mcPU->GetBinContent(i), nData = runDPU->GetBinContent(i);
        weights_runD[i-1] = (nMC > 0 ? nData/nMC : 1.0);
    }
    std::vector<double> weights(dataPU->GetNbinsX()+1, 1.0);
    for (int i = 1, n = weights.size(); i < n; ++i) {
        double nMC = mcPU->GetBinContent(i), nData = dataPU->GetBinContent(i);
        weights[i-1] = (nMC > 0 ? nData/nMC : 1.0);
    }
	

    TFile *fOut = new TFile("/tmp/hbrun/tnpZ_withMuIDTop.root", "RECREATE");
    //TFile *fOut = new TFile("/afs/cern.ch/work/h/hbrun/pogTnPr7/TnP_Data_"+NameFile+".root", "RECREATE");
    fOut->mkdir("tpTree")->cd();
    TTree *tOut = tIn->CloneTree(0);
    Float_t tag_abseta, weight, weight_runA, weight_runB, weight_runC, weight_runD;
    Int_t passORdiMu, passORdiMuNodZ, passMu17Mu8, passMu17Mu8NoDz, passMu17TkMu8, passMu17TkMu8NoDz;
//    tOut->Branch("pt", &pt, "pt/F");
   tOut->Branch("tag_abseta", &tag_abseta, "tag_abseta/F");
    tOut->Branch("passORdiMu", &passORdiMu, "passORdiMu/I");
    tOut->Branch("passORdiMuNodZ", &passORdiMuNodZ, "passORdiMuNodZ/I");
    tOut->Branch("passMu17Mu8", &passMu17Mu8, "passMu17Mu8/I");
    tOut->Branch("passMu17Mu8NoDz", &passMu17Mu8NoDz, "passMu17Mu8NoDz/I");
    tOut->Branch("passMu17TkMu8", &passMu17TkMu8, "passMu17TkMu8/I");
    tOut->Branch("passMu17TkMu8NoDz", &passMu17TkMu8NoDz, "passMu17TkMu8NoDz/I");
    tOut->Branch("weight", &weight, "weight/F");
    tOut->Branch("weight_runA", &weight_runA, "weight_runA/F");
    tOut->Branch("weight_runB", &weight_runB, "weight_runB/F");
    tOut->Branch("weight_runC", &weight_runC, "weight_runC/F");
    tOut->Branch("weight_runD", &weight_runD, "weight_runD/F");
	
  

    int step = tIn->GetEntries()/1000;
    double evDenom = 100.0/double(tIn->GetEntries());
    TStopwatch timer; timer.Start();
	
    //for (int i = 0, n = tIn->GetEntries(); i < n; ++i) {
	for (int i = 0, n = 500000; i < n; ++i) {
        tIn->GetEntry(i);
        //if (i > 20000) break;
        if ((i+1) % step == 0) { 
            double totalTime = timer.RealTime()/60.; timer.Continue();
            double fraction = double(i+1)/double(n+1), remaining = totalTime*(1-fraction)/fraction;
            printf("Done %9d/%9d   %5.1f%%   (elapsed %5.1f min, remaining %5.1f min)\n", i, n, i*evDenom, totalTime, remaining); 
            fflush(stdout);
        }
        if (pair_probeMultiplicity>1) {
            //  printf("ref=%i, event=%i, multi=%f, diffToZ=%f\n",i,event,pair_probeMultiplicity,fabs(mass-91.2));
            
            int multi = (int) pair_probeMultiplicity;
            int theBest = i;
            float bestProvi = fabs(mass-91.2);
            for (int j=i+1 ; j<(i+multi) ; j++){
                tIn->GetEntry(j);
                if (bestProvi>fabs(mass-91.2)) {
                    //printf("on est dans le boucle, j-i=%i\n",j);
                    bestProvi=fabs(mass-91.2);
                    theBest = j;
                }
            }
            tIn->GetEntry(theBest);
            i=i+multi-1;
            //  printf("save ref=%i, event=%i, multi=%f, diffToZ=%f\n",i,event,pair_probeMultiplicity,fabs(mass-91.2));
            
        }
        //if (!((pair_probeMultiplicity>0)&&(pair_probeMultiplicity<2.0))) continue;
        //if (!(Tight2012)) continue;
        bool passLoose = ((Glb||TM)&&PF);
        if (!(passLoose)) continue;
        if (!((Mu17)||(tag_Mu17))) continue;
      //  passORdiMu = ((DoubleMu17Mu8_Mu17&&DoubleMu17Mu8_Mu8)||(DoubleMu17TkMu8_Mu17&&DoubleMu17TkMu8_TkMu8));
        passMu17Mu8 = ((DoubleMu17Mu8_Mu17&&tag_DoubleMu17Mu8_Mu8leg)||(tag_DoubleMu17Mu8_Mu17&&DoubleMu17Mu8_Mu8leg));
        passMu17TkMu8 = ((DoubleMu17TkMu8_Mu17&&tag_DoubleMu17TkMu8_TkMu8leg)||(tag_DoubleMu17TkMu8_Mu17&&DoubleMu17TkMu8_TkMu8leg));
        passORdiMu = passMu17Mu8 || passMu17TkMu8;
        
        passMu17Mu8NoDz = ((DoubleMu17Mu8_Mu17leg&&tag_DoubleMu17Mu8_Mu8leg)||(tag_DoubleMu17Mu8_Mu17leg&&DoubleMu17Mu8_Mu8leg));
        passMu17TkMu8NoDz = ((DoubleMu17TkMu8_Mu17leg&&tag_DoubleMu17TkMu8_TkMu8leg)||(tag_DoubleMu17TkMu8_Mu17leg&&DoubleMu17TkMu8_TkMu8leg));
        passORdiMuNodZ = passMu17Mu8NoDz || passMu17TkMu8NoDz;
        tag_abseta = fabs(tag_eta);
        
        weight = weights[int(tag_nVertices)];
        weight_runA = weights_runA[int(tag_nVertices)];
        weight_runB = weights_runB[int(tag_nVertices)];
        weight_runC = weights_runC[int(tag_nVertices)];
        weight_runD = weights_runD[int(tag_nVertices)];
        // printf("on va sauver ! \n");
        tOut->Fill();
    }

    tOut->AutoSave(); // according to root tutorial this is the right thing to do
    fOut->Close();
}
