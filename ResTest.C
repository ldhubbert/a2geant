{
#include "TAxis.h"
#include "THistPainter.h"

#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
  
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
	
	// Open file filled by Geant4 simulation 
  TFile *f1 = TFile::Open("out/CATS.root");//was out/CATS.root
  TH1D *h1 = (TH1D*)f1->Get("h12");
  h1->Draw("eCATS*1000>>CATS(100,280,301)");
  h1->SetLineWidth(3);
  h1->SetLineColor(2);
  c1->Update();
  
  
   // h1->SetTitle("new CATS sim;Energy (MeV);Counts");
   int bin1 = h1->FindFirstBinAbove(h1->GetMaximum()/2);
   int bin2 = h1->FindLastBinAbove(h1->GetMaximum()/2);
   double fwhm = h1->GetBinCenter(bin2) - h1->GetBinCenter(bin1);
  


   //int binmax = h1->GetMaximumBin();
   //double x = h1->GetXaxis()->GetBinCenter(binmax);
   cout << fwhm << endl;
   //cout << x << endl;

  //TLegend *tl = new TLegend(0.2,0.65,0.58,0.83);//.57
  //tl->SetTextFont( 132);
  //tl->SetFillStyle(0);
  //tl->SetBorderSize(0);
  //tl->SetTextSize(0.04);
  //tl->AddEntry(((TObject*)0), TString::Format("fwhm = %g", fwhm), "");

  //tl->AddEntry(h4, "Elastic","l");

  //TTree* t1 = (TTree*) f1.Get("h12");
  //TH1F *h1 = new TH1F("h1","nhits",100,0,600);
  //t1->Draw("eCATS*1000>>CATS(100,480,501)");
  //h1->SetDirectory(0);
  //f1.Close();
  
  //TFile *f2 = TFile::Open("out/CATSA2copy1.root");
  //TH1D *h2 = (TH1D*)f2->Get("h12");
  //h2->SetLineWidth(2);
  //h2->SetLineColor(4);
  //h2->Draw("eCATS*1000>>CATS(100,480,501)");
  //c1->cd(1);
  //c1->Update(); 
  //h2->Draw("same");
  //c1->Update();
  //TTree* t2 = (TTree*) f2.Get("h12");
  //TH1F *h2 = new TH1F("h2","nhits",100,0,600);
  //t2->Draw("eCATS*1000>>CATS(100,480,501)");
  //h2->SetDirectory(0);
  //f2.Close();

  
  // Create a canvas and divide it into 2x2 pads
  //TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  //h1->Draw();
  //h2->Draw("same"); 
  //TTree *eCATS = (TTree*)f.Get("h12");//these pointers are likely the issue
  //TTree *eCATS1 = (TTree*)m.Get("h12");//these pointers are likely the issue
  
  //eCATS->Draw("eCATS*1000>>CATS(100,480,501)");
  
  //eCATS1->Draw("eCATS*1000>>CATS(1000,480,501)");
  //h12->Draw("eCATS*1000>>eCATS(50,450,505)");
  //TH1F *h1 = gPad->GetPrimitive("htemp");

  
  //CATS->GetXaxis()->SetTitle("Energy (MeV)");
  //CATS->GetYaxis()->SetTitle("Counts");
  //CATS->SetTitle("Energy Recorded by A2G4 CATS sim");
  //gPad->SetLogy();
  //eCATS->SetTitle("Energy Recorded by A2G4 CATS sim;a;a");
}

