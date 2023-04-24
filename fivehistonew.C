void fivehistonew(){

gStyle->SetOptStat("0");

int x = 500;
int El_Counts = 61000;
Double_t Elastic, Inelastic, sum;//made double to prevent division error
Double_t eff, contamination;
Double_t lower = 390;
Double_t upper = 401;
Double_t lowerdraw = 380;
Double_t upperdraw = 401;


TFile f1("out/CATS.root");
TTree* t1 = (TTree*) f1.Get("h12");
TH1F* h1 = new TH1F("h1", "eCATS", x, lower, upper);
t1->Draw("eCATS*1000>>h1","","goff");
h1->SetDirectory(0);
f1.Close();

TFile f2("out/CATSA2copy1.root");
TTree* t2 = (TTree*) f2.Get("h12");
TH1F* h2 = new TH1F("h2", "eCATS", x, lower, upper);
t2->Draw("eCATS*1000>>h2","","goff");
h2->SetDirectory(0);
f2.Close();

Elastic = h1->Integral();
Inelastic = h2 ->Integral();
sum = Elastic + Inelastic;

eff = Elastic / El_Counts;
contamination = Inelastic / (Elastic + Inelastic);
cout << "Lower cut: " << lower << endl;
cout << "Upper cut: " << upper << endl;
cout << "Elastic: " << Elastic << endl;
cout << "Inelastic: " << Inelastic << endl;
cout << "sum: " << sum << endl;
cout << "Efficiency: " << eff << endl;
cout << "Contamination: " << contamination << endl;

TFile f4("out/CATS.root");
TTree* t4 = (TTree*) f4.Get("h12");
TH1F* h4 = new TH1F("h4", "eCATS", x, lowerdraw, upperdraw);
t4->Draw("eCATS*1000>>h4","","goff");
h4->SetDirectory(0);
f4.Close();

TFile f5("out/CATSA2copy1.root");
TTree* t5 = (TTree*) f5.Get("h12");
TH1F* h5 = new TH1F("h5", "eCATS", x, lowerdraw, upperdraw);
t5->Draw("eCATS*1000>>h5","","goff");
h5->SetDirectory(0);
//h5->Draw("PFC");//new
f5.Close();

TCanvas* c = new TCanvas();
h4->SetLineColor(kBlue+1);
//h4->SetFillColor(kMagenta);
//h4->Draw();

h5->SetLineColor(kGreen+3);
//h5->SetFillColor(kRed);
//h5->Draw("same");

TH1F* h3 = new TH1F("h3", "eCATS", x, lowerdraw, upperdraw);
h3->Add(h4,1.);
h3->Add(h5,1.);
h3->SetLineColor(kMagenta+2);
//h3->SetFillColor(kMagenta+2);

h3->SetLineWidth(4);
h4->SetLineWidth(4);
h5->SetLineWidth(4);

h3->GetXaxis()->SetTitle("Energy (MeV)");
h3->GetYaxis()->SetTitle("Counts");
//h3->Draw();

//h4->SetFillStyle (3001);
//h4->Draw("same");

//h5->SetFillColor(kGreen+3);


h5->SetFillColor(kGreen+3);
h5->SetFillStyle (3001);


h5->GetYaxis()->SetTitle("Counts");
h5->GetXaxis()->SetTitle("Energy (MeV)");
h5->Draw();

h4->SetFillColor(kBlue+1);
h4->SetFillStyle (3001);
h4->Draw("hist same");
//h4->SetFillStyle (3001);

h3->Draw("hist same");

auto line = new TLine(lower, 0, lower, 8000);//200000
line->SetLineColor(kRed-9);
line->SetLineWidth(2);
line->SetLineWidth(2);
line->Draw();

//gPad->SetLogy();

TLegend *tl = new TLegend(0.2,0.65,0.58,0.83);//.57
tl->SetTextFont( 132);
tl->SetFillStyle(0);
tl->SetBorderSize(0);

//tl->AddEntry(((TObject*)0), TString::Format("Efficiency = %g", eff), "");
//tl->AddEntry(((TObject*)0), TString::Format("Contamination = %g", contamination), "");
tl->SetTextSize(0.04);
//tl->AddEntry(((TObject*)0), TString::Format("Green: inlastic"), "");
//tl->AddEntry(((TObject*)0), TString::Format("Blue: elastic"), "");
//tl->AddEntry(((TObject*)0), TString::Format("Violet: elastic and inelastic"), "");
//tl->AddEntry(h3, "Elastic and inelastic","l");
tl->AddEntry(h4, "Elastic","l");
tl->AddEntry(h5, "Inelastic","l");
tl->AddEntry(h3, "Sum","l");

//tl->AddEntry(line, "Cut","l");
//tl->AddEntry(((TObject*)0), TString::Format("Pink: cut"), "");

tl->Draw("Same");

TLegend *tl1 = new TLegend(0.2,0.5,0.58,0.6);
tl1->SetTextFont( 132);
tl1->SetFillStyle(0);
tl1->SetBorderSize(0);

tl1->AddEntry(((TObject*)0), TString::Format("Efficiency = %g", eff), "");
tl1->AddEntry(((TObject*)0), TString::Format("Contamination = %g", contamination), "");
tl1->SetTextSize(0.04);
tl1->Draw("same");

//auto leg = new TLegend(0.2,0.57,0.58,0.83);
//leg->SetFillColor(0);
//leg->SetBorderSize(0);
//leg->AddEntry((TObject*)0, "efficiency: " str, "");
//leg->AddEntry(((TObject*)0), TString::Format("Efficiency = %g", eff), "");
//leg->AddEntry(((TObject*)0), TString::Format("Contamination = %g", contamination), "");
//leg->SetTextSize(0.04);

//leg->AddEntry(((TObject*)0), TString::Format("Green: inlastic"), "");
//leg->AddEntry(((TObject*)0), TString::Format("Blue: elastic"), "");
//leg->AddEntry(((TObject*)0), TString::Format("Violet: elastic and inelastic"), "");
//leg->AddEntry(((TObject*)0), TString::Format("Pink: cut"), "");

//leg->Draw("same");
}


