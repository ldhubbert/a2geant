void CFF()
{
	UInt_t bins, cut_bin;
	Int_t counts, c_el, c_in;
	Double_t x, eg, sigma, res, mean, lo, hi;
	Double_t elastic, inelastic, amp_in, Elastic, Inelastic;
	Double_t eff, cont, max, cut;
	TString name;

	TCanvas *c1 = new TCanvas( "c1", "Functions", 20, 20, 1000, 500);
	c1->Divide( 2, 1);
	
	counts = 1e6;

	cut = 295;

	lo = 270;
	hi = 370;
	bins = 1000;

	elastic = 300;
	inelastic = elastic - 4.4;
	amp_in = 0.15;

	res = 0.02;
	sigma = res*elastic/2.534;
	cout << "sigma = " << sigma << endl;

// Elastic peak
	TF1 *g1 = new TF1( "g1", "gaus", lo, hi);
	g1->SetParameter( 0, 1);		// Amplitude
	g1->SetParameter( 1, elastic);		// Mean
	g1->SetParameter( 2, sigma);		// Sigma

// Inelastic peak
	TF1 *g2 = new TF1( "g2", "gaus", lo, hi);
	g2->SetParameter( 0, amp_in);		// Amplitude
	g2->SetParameter( 1, inelastic);		// Mean
	g2->SetParameter( 2, sigma);		// Sigma

	c1->cd( 1);
	g1->SetLineWidth( 4);
	g1->SetLineColor( 2);
	g1->SetMaximum( 1.1);
	g1->Draw();
	g1->GetXaxis()->SetTitle( "E_{#gamma'} (MeV)");
	g1->SetTitle();
	g2->SetLineWidth( 4);
	g2->SetLineColor( 4);
	g2->Draw( "same");

	//TLine *l = new TLine( cut, 0, cut, 1.1);
	//l->SetLineWidth( 2);
	//l->SetLineStyle( 2);
	//l->Draw();

	//TPaveText *pt1 = new TPaveText( 0.5, 0.6, 0.7, 0.8, "NDC");
	//pt1->SetTextAlign( 11);
	//name = Form( "E_{#gamma'}^{elastic} = %4.1f MeV", elastic);
	//pt1->AddText( name);
	//name = Form( "E_{#gamma'}^{inelastic} = %4.1f MeV", inelastic);
	//pt1->AddText( name);
	//name = Form( "cut = %3.0f MeV", cut);
	//pt1->AddText( name);
	//pt1->SetBorderSize( 0);
	//pt1->SetFillStyle( 0);
	//pt1->SetTextFont( 23);
	//pt1->SetTextSize( 20);
	//pt1->Draw();

	Elastic = g1->Integral(1,100);
	Inelastic = g2 ->Integral(1,100);
	cout <<" El" << Elastic << " ";
	cout << "In" << Inelastic << " ";
	
	c1->cd( 2);

// Now the histogram filled with the functions
	TH1F *h1 = new TH1F( "h1", "", bins, lo, hi);
	cut_bin = h1->GetXaxis()->FindBin( cut);
	cout << cut << " ";
	cout << cut_bin << " ";
	h1->FillRandom( "g1", counts);
	c_el = h1->Integral( cut_bin, bins);
	cout << c_el << " ";
	h1->FillRandom( "g2", counts*amp_in);
	h1->Draw();
	max = h1->GetMaximum();
	h1->SetMaximum( 1.1*max);
	h1->SetStats( 0);
	h1->SetLineWidth( 4);
	h1->GetXaxis()->SetTitle( "E_{#gamma'} (MeV)");

	//TLine *l1 = new TLine( cut, 0, cut, 1.1*max);
	//l1->SetLineWidth( 2);
	//l1->SetLineStyle( 2);
	//l1->Draw();

	TH1F *h2 = new TH1F( "h2", "Inelastic", bins, lo, hi);
	h2->FillRandom( "g2", counts*amp_in);
	c_in = h2->Integral( cut_bin, bins);
	cout << c_in << " ";
	cout << endl;

//	mean = h1->GetMean();
//	cout << mean << endl;

	eff = (float) c_el/counts;
	cont = c_in/(1+amp_in)/counts;

	//TPaveText *pt = new TPaveText( 0.5, 0.65, 0.7, 0.8, "NDC");
	//pt->SetTextAlign( 11);
	//name = Form( "efficiency = %4.1f%%", eff*100);
	//pt->AddText( name);
	//name = Form( "contamination = %4.1f%%", cont*100);
	//pt->AddText( name);
	//pt->SetBorderSize( 0);
	//pt->SetFillStyle( 0);
	//pt->SetTextFont( 23);
	//pt->SetTextSize( 20);
	//pt->Draw();

	c1->Print( "output.pdf");

}
