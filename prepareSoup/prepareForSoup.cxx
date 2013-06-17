#include "TTree.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TSystem.h"
#include <cstdlib>
#include <cmath>



void prepareForSoup() {
	using namespace std;
    TTree *tIn  = (TTree *) gFile->Get("tpTree/fitter_tree");
    Float_t pt, abseta, pair_probeMultiplicity, tag_eta,mass;
    Int_t Glb, TM, PF;
	Int_t Tight2012, tag_Tight2012, tag_Mu8, Mu8, DoubleMu17Mu8_Mu17leg,  DoubleMu17Mu8_Mu8leg, DoubleMu17Mu8_Mu17, DoubleMu17Mu8_Mu8, DoubleMu17TkMu8_Mu17, DoubleMu17TkMu8_TkMu8, DoubleMu17TkMu8_Mu17leg, DoubleMu17TkMu8_TkMu8leg;
    Int_t tag_DoubleMu17Mu8_Mu17leg,  tag_DoubleMu17Mu8_Mu8leg, tag_DoubleMu17Mu8_Mu17, tag_DoubleMu17Mu8_Mu8, tag_DoubleMu17TkMu8_Mu17, tag_DoubleMu17TkMu8_TkMu8, tag_DoubleMu17TkMu8_Mu17leg, tag_DoubleMu17TkMu8_TkMu8leg;
    tIn->SetBranchAddress("pt", &pt);
    tIn->SetBranchAddress("abseta", &abseta);
    tIn->SetBranchAddress("tag_eta", &tag_eta);
    tIn->SetBranchAddress("mass", &mass);
    tIn->SetBranchAddress("pair_probeMultiplicity", &pair_probeMultiplicity);
    tIn->SetBranchAddress("Tight2012", &Tight2012);
    tIn->SetBranchAddress("tag_Tight2012", &tag_Tight2012);
    tIn->SetBranchAddress("tag_Mu8", &tag_Mu8);
    tIn->SetBranchAddress("Mu8", &Mu8);
    tIn->SetBranchAddress("Glb", &Glb);
    tIn->SetBranchAddress("TM", &TM);
    tIn->SetBranchAddress("PF", &PF);
    tIn->SetBranchAddress("DoubleMu17Mu8_Mu17leg", &DoubleMu17Mu8_Mu17leg);
    tIn->SetBranchAddress("DoubleMu17Mu8_Mu17", &DoubleMu17Mu8_Mu17);
    tIn->SetBranchAddress("DoubleMu17Mu8_Mu8leg", &DoubleMu17Mu8_Mu8leg);
    tIn->SetBranchAddress("DoubleMu17Mu8_Mu8", &DoubleMu17Mu8_Mu8);
    tIn->SetBranchAddress("DoubleMu17TkMu8_Mu17", &DoubleMu17TkMu8_Mu17);
    tIn->SetBranchAddress("DoubleMu17TkMu8_TkMu8", &DoubleMu17TkMu8_TkMu8);
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
	

	

    TFile *fOut = new TFile("/tmp/hbrun/tnpZ_withMuIDTop.root", "RECREATE");
    //TFile *fOut = new TFile("/afs/cern.ch/work/h/hbrun/pogTnPr7/TnP_Data_"+NameFile+".root", "RECREATE");
    fOut->mkdir("tpTree")->cd();
    TTree *tOut = tIn->CloneTree(0);
    Float_t tag_abseta;
    Int_t passORdiMu, passORdiMuNodZ, passMu17Mu8, passMu17Mu8NoDz, passMu17TkMu8, passMu17TkMu8NoDz;
//    tOut->Branch("pt", &pt, "pt/F");
   tOut->Branch("tag_abseta", &tag_abseta, "tag_abseta/F");
    tOut->Branch("passORdiMu", &passORdiMu, "passORdiMu/I");
    tOut->Branch("passORdiMuNodZ", &passORdiMuNodZ, "passORdiMuNodZ/I");
    tOut->Branch("passMu17Mu8", &passMu17Mu8, "passMu17Mu8/I");
    tOut->Branch("passMu17Mu8NoDz", &passMu17Mu8NoDz, "passMu17Mu8NoDz/I");
    tOut->Branch("passMu17TkMu8", &passMu17TkMu8, "passMu17TkMu8/I");
    tOut->Branch("passMu17TkMu8NoDz", &passMu17TkMu8NoDz, "passMu17TkMu8NoDz/I");

	
  

    int step = tIn->GetEntries()/1000;
    double evDenom = 100.0/double(tIn->GetEntries());
    TStopwatch timer; timer.Start();
	
    for (int i = 0, n = tIn->GetEntries(); i < n; ++i) {
	//for (int i = 0, n = 100; i < n; ++i) {
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
        //if (!(Tight2012&&tag_Tight2012)) continue;
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
        
        // printf("on va sauver ! \n");
        tOut->Fill();
    }

    tOut->AutoSave(); // according to root tutorial this is the right thing to do
    fOut->Close();
}
