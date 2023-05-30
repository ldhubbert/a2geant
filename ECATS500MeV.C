
{
  //NOTE: ALL OF VINCENT'S ORIGINAL CODE FOR THIS HISTOGRAM  IS HERE. LINES NOT IN USE ARE COMMENTED OUT.
  //ECATS100MeV.C to ECATS400MeV.C WERE INCOMPLETE. I (LAURA) FINISHED CODING EACH OF THEM. THE SAME CODING STRATEGY IS USED FOR ECATS100MEV.C TO ECATS500MEV.C.
  //THE ONLY DIFFERENCES BETWEEN THE HISTOGRAM CODES ARE WHICH "out" FILES ARE ACCESSED, THE X-AXES, AND THE TITLES. 
  //I KEPT VINCENT'S OLD CODE IN THIS FILE FOR REFERENCE PURPOSES, BUT COMMENTED THEM OUT. NOTE THAT SOME LINES IN VINCENT'S ORIGINAL CODE WERE ALREADY COMMENTED OUT.
  //ALTHOUGH HIS CODE WORKED, I IMPLEMENTED ANOTHER WAY THAT WOULD WORK ALL OF THE TIME.

  #include "TAxis.h"
  //gROOT->Reset();
  //gROOT->SetStyle("Plain");

  // Draw histos filled by Geant4 simulation 
  //   
  // Open file filled by Geant4 simulation 
  TFile f("out/CATS_500MeV.root");//was out/CATS.root

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);

  // Draw Eabs histogram in the pad 1
  c1->cd(1);

  TTree *eCATS = (TTree*)f.Get("h12");//these pointers are likely the issue
  //eCATS->Draw("eCATS*1000>>CATS(200,450,505)");
  //h12->Draw("eCATS*1000>>eCATS(50,450,505)");
  //TH1F *h1 = gPad->GetPrimitive("htemp");
  
  //I (Laura) added the following line
  TH1F* CATS = new TH1F("CATS", "Energy Recorded by A2G4 CATS sim -- 500MeV Photon Beam", 200, 450, 510);

  //I (Laura) added the following line
  eCATS->Draw("eCATS*1000>>CATS");

  CATS->GetXaxis()->SetTitle("Energy (MeV)");
  CATS->GetYaxis()->SetTitle("Counts");

  //I (Laura) added the following line
  CATS->Draw();

  //CATS->SetTitle("Energy Recorded by A2G4 CATS sim -- 500MeV Photon Beam");
  //gPad->SetLogy();
  //eCATS->SetTitle("Energy Recorded by A2G4 CATS sim;a;a");
  //gPad->Update();
  //TPaveText *title = (TPaveText*)gPad->GetPrimitive("Energy Recorded by A2G4 CATS sim");
  //title->SetBorderSize(0);
}                                            
