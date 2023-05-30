{//gROOT->Reset();
  //gROOT->SetStyle("Plain");

  gStyle->SetOptStat(0);
  // Draw histos filled by Geant4 simulation 
  //   
  int y = 20;
  // Open file filled by Geant4 simulation 
  TFile f1("Out/");
  //LAURA COMMENT: NOTE: the file filled by the Geant4 simulation needs to be inserted here, depending on which energy you wanted run through the sim (i.e., the B4_100MeV.root file, etc.)

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(1,1);

  // Draw Eabs histogram in the pad 1
  c1->cd(1);

  //gStyle->SetOptFit(1111);
  TTree *t1 = (TTree*)f1.Get("h12");
  TF1 f2("f2","[0] * TMath::Landau([1]-x, 0., [2])", 296., 1);//301
  f2.SetParameters(50000,296,1);
  //h12->Draw("eCATS*1000>>h1(100,275,310)");
  
  
  TH1F* h1 = new TH1F("h1", "eCATS", y, 280, 301);
  t1->Draw("eCATS*1000>>h1","","goff");

  
  //B4->Draw("Ecore>>h1(100,450.,505)","Ecore<500");
  h1->Fit("f2");
  h1->SetFillStyle( 3001);
  h1->SetFillColor(7);

  //gPad->SetLogy();
   int bin1 = h1->FindFirstBinAbove(h1->GetMaximum()/2);
   int bin2 = h1->FindLastBinAbove(h1->GetMaximum()/2);
   double fwhm = h1->GetBinCenter(bin2) - h1->GetBinCenter(bin1);

   double res = 100 * fwhm / 300; 
  //h1->Integral();
  //Double_t x = h1->Integral();
  //cout << x << endl;
  cout << fwhm << endl;

  h1->Draw( "hist same");
  h1->SetTitle("A2G4 CATS;Energy (MeV);Counts");

  TLegend *tl = new TLegend(0.2,0.65,0.58,0.73);//.57
  tl->SetTextFont( 132);
  tl->SetFillStyle(0);
  tl->SetBorderSize(0);
  tl->AddEntry(((TObject*)0), TString::Format("FWHM = %g", fwhm)", "");
  tl->AddEntry(((TObject*)0), TString::Format("Energy Resolution = %g%%", res), "");
  tl->Draw( "same");
}

