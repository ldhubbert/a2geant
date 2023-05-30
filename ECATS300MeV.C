{
  //Draw histos filled by Geant4 simulation    

  //Open file filled by Geant4 simulation 
  TFile f("out/CATS_300MeV.root");

  //Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);

  //Draw Eabs histogram in the pad 1
  c1->cd(1);

  TTree *eCATS = (TTree*)f.Get("h12");//these pointers are likely the issue

  //I (Laura) added the following
  TH1F* CATS = new TH1F("CATS", "Energy Recorded by A2G4 CATS sim -- 300MeV Photon Beam", 200, 265, 305);

  eCATS->Draw("eCATS*1000>>CATS");

  CATS->GetXaxis()->SetTitle("Energy (MeV)");
  CATS->GetYaxis()->SetTitle("Counts");

  CATS->Draw();
}
