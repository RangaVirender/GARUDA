TH1D* spec2gauss(const TH1D* hist, Double_t resolution)
{
    
    //FWHM = 2.3548*sigma
    Double_t count = 0;
	Double_t binCenter = 0;
    
    Int_t nBinsGauss = hist->GetNbinsX();
    Double_t xMinGauss = hist->GetXaxis()->GetBinLowEdge(1);
    Double_t xMaxGauss = hist->GetXaxis()->GetBinUpEdge(nBinsGauss);
    //cout << "nBins" <<"\t"<< nBins << endl;
    //cout << "xMin" <<"\t"<< xMin << endl;
    //cout << "xMax" <<"\t"<< xMax << endl;
    
    TH1D* hist_gaus = new TH1D("hist_gaus","",nBinsGauss, xMinGauss, xMaxGauss);
	
	for(Int_t i = 1; i <= nBinsGauss ; ++i)
	{
		count = hist->GetBinContent(i);
		binCenter = hist->GetXaxis()->GetBinCenter(i);
		
		for(Int_t j = 1; j <= nBinsGauss ; ++j)
    	{
            Double_t binContent = hist_gaus->GetBinContent(j);
            Double_t x = hist_gaus->GetXaxis()->GetBinCenter(j);
            
            //resolution = resolution/sqrt(binCenter)+0.01;
            
            //binContent = binContent + count*TMath::Gaus(x,binCenter,resolution,kTRUE);
            binContent = binContent + count*TMath::Gaus(j,i,resolution,kTRUE);
            Double_t area = count*resolution*sqrt(2.0*M_PI);
            //cout<<"Area: \t"<<area<<endl;
            hist_gaus->SetBinContent(j,binContent);
            binContent=0;
    	}
    }    
	return hist_gaus;
}

Double_t fpeaks(Double_t *x, Double_t *par)
	{   Int_t npeaks = 10;
   		Double_t result = par[0] + par[1]*x[0];
   		for (Int_t p=0;p<npeaks;p++)
   		{
      		Double_t norm  = par[3*p+2]; // "height" or "area"
      		Double_t mean  = par[3*p+3];
      		Double_t sigma = par[3*p+4];
			#if defined(__PEAKS_C_FIT_AREAS__)
      			norm /= sigma * (TMath::Sqrt(TMath::TwoPi())); // "area"
			#endif /* defined(__PEAKS_C_FIT_AREAS__) */
      		result += norm*TMath::Gaus(x[0],mean,sigma);
   		}
   		return result;
	}


  

int rootAnalysis()
{   
	//gSystem->RedirectOutput("mylog.txt");

    
     Int_t includeResolutionFlag = false;
   //gSystem->Exec("(cd .. && ./mergeRootFiles.sh)");
   
   TFile* f1 = new TFile("output.root","READ");
	TTree* t2 = (TTree*)f1->Get("simulationInfo");
    t2->GetEntry(0);
       Int_t Events = (int)t2->GetLeaf("fnoOfEvents")->GetValue();
    Double_t detDistance = (double)t2->GetLeaf("fdetDistance")->GetValue();
    Double_t detHalfLengthZ = (double)t2->GetLeaf("fdetHalfLengthZ")->GetValue();
	Double_t detDiameterCm = (double)t2->GetLeaf("fdetDiameterCm")->GetValue();
	Double_t particleEnergy = (double)t2->GetLeaf("fparticleEnergy")->GetValue();
    
    
    
    Double_t solidAngle = 2.0*M_PI*(1.0 - detDistance/sqrt(pow(detDiameterCm/2.0,2.0) + pow(detDistance, 2.0) ) );
    Double_t solidAngleFrac = solidAngle/(4.0*M_PI);
    
    //Int_t gammaEnergy = 10800; // keV // to set xrange of spectrum 
	                                  // and retrieve no of counts in full energy peak  
	particleEnergy = particleEnergy*1000;//convert into keV
	Int_t negBins = 250;
	Int_t gammaEnergyBin = particleEnergy + negBins ;
	Int_t nBinsH1 = 1.1*particleEnergy + negBins; // to have some bins on negative side to accomodate broadening
	Double_t xMinH1 = -1*negBins/1000.0; //            
	Double_t xMaxH1 = 1.1*particleEnergy/1000.0;
	
	cout <<nBinsH1<<"\t"<<xMinH1<<"\t"<<xMaxH1<<endl;

	TCanvas* c1 = new TCanvas("c1");
	
	TTree* t1 = (TTree*)f1->Get("Scoring");
	TH1D* h1 = new TH1D("h1", "", nBinsH1, xMinH1, xMaxH1);
	t1->Draw("fEdep>>h1","","");
	
    //f1->ls();


    
	gPad->SetLogy(1);
	
	h1->GetYaxis()->SetRangeUser(1,h1->GetMaximum()*1.1);
	//h1->Draw();
	c1->SaveAs("h1.pdf");
    
    cout << "Total counts in  h1: " << h1->Integral() << endl;
	
	Double_t gammaCounts = 0 ;

	gammaEnergyBin = gammaEnergyBin - 1 ;
	cout << "Counts at energyBin " << gammaEnergyBin << ": " << h1->GetBinContent(gammaEnergyBin) << endl;
	gammaCounts = h1->GetBinContent(gammaEnergyBin);
	
	gammaEnergyBin = gammaEnergyBin + 1 ;
	cout << "Counts at energyBin " << gammaEnergyBin << ": " << h1->GetBinContent(gammaEnergyBin) << endl;
	gammaCounts = gammaCounts + h1->GetBinContent(gammaEnergyBin);
	
	gammaEnergyBin = gammaEnergyBin + 1 ;
	cout << "Counts at energyBin " << gammaEnergyBin << ": " << h1->GetBinContent(gammaEnergyBin) << endl;
	gammaCounts = gammaCounts + h1->GetBinContent(gammaEnergyBin);
	
	gammaEnergyBin = gammaEnergyBin - 1 ;
	cout << "Total Counts at energy " << particleEnergy << ": " << gammaCounts << endl;
    

    Double_t intFEPEff = gammaCounts/(Events*solidAngleFrac);

    cout << "No of Events " << Events << endl;
    cout << "detDistance " << detDistance << " cm" << endl;
    cout << "detHalfLengthZ " << detHalfLengthZ << " cm" << endl;
    cout << "detDiameter " << detDiameterCm << " cm " << endl;
    cout << "particleEnergy " << particleEnergy << " keV" << endl; 
    cout << "solidAngle " << solidAngle << " Steradian" << endl;
    cout << "Fraction of 4pi " << solidAngleFrac << endl;
    cout << "Intrinsic FEP Eff " << intFEPEff*100.0 << " %" << endl;

    TH1D* hist_gaussian;
    if(includeResolutionFlag)
    {
		hist_gaussian = spec2gauss(h1,25);
	
		hist_gaussian->Draw("SAME");

		hist_gaussian->GetYaxis()->SetRangeUser(0.1, hist_gaussian->GetMaximum()*1.1);
	
		hist_gaussian->SetLineColor(kGreen);
	
		c1->SaveAs("h1_gaussian.pdf");
    
    	cout << "Total counts in  h1_gaussian: " <<
        		hist_gaussian->Integral() << endl;
    }
	//gSystem->RedirectOutput(0);

	TLegend* legend1 = new TLegend(0.6,0.8,0.97,0.97);//x1 y1 x2 y2
   //legend1->SetNColumns (1);
   legend1->AddEntry(h1,"Hitogram","l");
   //legend1->AddEntry(g2,"Target at 45 deg ","l");
 	legend1->Draw();

 	//write histograms and results to another root file

   TFile* f2 = new TFile("results.root","RECREATE");
   
   f2->cd();
   t1->Write();
   t2->Write();
   h1->Write();
   if(includeResolutionFlag) hist_gaussian->Write();
   c1->Write();
   f2->Close();

	return 0;
}