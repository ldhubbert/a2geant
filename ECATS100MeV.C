{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  // Draw histos filled by Geant4 simulation 
  //   

  // Open file filled by Geant4 simulation 
  TFile f("out/CATS.root");//was out/CATS.root

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);

  // Draw Eabs histogram in the pad 1
  c1->cd(1);

  TTree *CATS = (TTree*)f.Get("h12");//these pointers are likely the issue
  h12->Draw("eCATS>>eCATS(500,0.09,0.105)");//was 90,105
}
