#include "TTree.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TSystem.h"
#include <cstdlib>
#include <cmath>

void easyPrinter(){
    using namespace std;
    TTree *tIn  = (TTree *) gFile->Get("tpTree/fitter_tree");
    Float_t pt, abseta, tag_pt, tag_eta;
    UInt_t event;
    
    tIn->SetBranchAddress("pt", &pt);
    tIn->SetBranchAddress("abseta", &abseta);
    tIn->SetBranchAddress("tag_pt", &tag_pt);
    tIn->SetBranchAddress("tag_eta", &tag_eta);
    tIn->SetBranchAddress("event", &event);

    for (int i = 0, n = tIn->GetEntries(); i < n; ++i) {
    //for (int i = 0, n = 100; i < n; ++i) {
        tIn->GetEntry(i);
        printf("event=%i, pt=%f, abseta=%f, tag_pt=%f, tag_eta=%f \n", event, pt, abseta, tag_pt, tag_eta);
        
    
    }
    
}
