void B1a(){

#include "TF1.h"
#include "TMath.h"
#include "TTreeReader.h"

	TCanvas *c1 = new TCanvas("c1","",20,20,1000,2000);
	c1->Divide(1,1);
	c1->cd(1);

	TFile*filename = new TFile("~/opt/basic/B1a/build/B1.root");

	TH1F*h1=(TH1F*)filename->Get("Edep");

	h1->GetXaxis()->SetTitle("x-axis");
	h1->GetYaxis()->SetTitle("y-axis");
	h1->SetFillColor(4);
	h1->Draw();

	
	// code is modeled after Laura's that was sent in teams chat (H100MeVsmear.C
	//FWHM Section
	//Findong halfmaxYValue
	Double_t BinWithMostCounts = h1->GetMaximumBin();
	Double_t MaxYValue = h1->GetBinContent(BinWithMostCounts);
	Double_t HalfMaxYValue =MaxYValue/2;

	//Finding HalfMaxYValue bin on the left-hand side of the peak 
	Double_t FWHMLeftXValue = 0;
	int binA = 0;
	//searches for the bin in the range of bin 0 and BinWithMostCounts
	h1->GetBinWithContent(HalfMaxYValue, binA, 0, BinWithMostCounts, 0);
	//the if condition if no bin was found with content of HalfMaxYValue
	if (binA == 0){
		//Finding the first bin (on the left-hand side of the max peak) that has contents above HalfMaxYValue (Lower2))
		//the second parameter has to be 1 when using the search ability 
		Double_t Lower2 = h1->FindFirstBinAbove(HalfMaxYValue, 1, 0, BinWithMostCounts);
		Double_t Lower2Contents = h1->GetBinContent(Lower2);

		//Finding the bin below HalfMaxYValue on the left-hand side of the max peak (Lower1)
		Double_t Lower1 = Lower2 - 1;
		Double_t Lower1Contents = h1->GetBinContent(Lower1);
		
		//Finding an approximation for the bin x-value with HalfMaxYValue on the left-hand side of the max peak 
		Double_t LowerBinFraction = Lower1Contents/Lower2Contents;
		Double_t CenterLower1 = h1->GetBinCenter(Lower1);
		Double_t CenterLower2 = h1->GetBinCenter(Lower2);
		Double_t LowerBinWidth = CenterLower2 - CenterLower1;
		FWHMLeftXValue = CenterLower1 + (LowerBinWidth)*(LowerBinFraction);
	}

	//the else if condition pertains if there is a bin that was found with contents of HalfMaxYValue
	else if (binA !=0){
		FWHMLeftXValue = h1->GetBinCenter(binA);
	}

	//Finding the HalfMaxYValue bin on the right-hand side of the peak
	Double_t FWHMRightXValue = 0;
	int binB = 0;
	//This searches for the bin in the range of BinWithMostCounts and bin 200, which is the last bin 
	h1->GetBinWithContent(HalfMaxYValue, binB, BinWithMostCounts, 200, 0);
	//the if condition pertains if no bin was found with content of HalfMaxYValue
	if (binB ==0){
		//Finding the last bin (on the rhs of the max peak) that has content above HalfMaxYValue (Upper1)
		//the second parameter has to be one when using the search ability
		Double_t Upper1 =h1->FindLastBinAbove(HalfMaxYValue, 1, BinWithMostCounts, 200);
		Double_t Upper1Contents =h1->GetBinContent(Upper1);
		//finding the bin below HalfMaxYValue on the rhs of the max peak (Upper2)
		Double_t Upper2 = Upper1 +1;
		Double_t Upper2Contents = h1->GetBinContent(Upper2);
		//finding an approx. for the bin x-value with the HalfMaxYValue on the rhs  of the max peak 
		Double_t UpperBinFraction = Upper2Contents/Upper1Contents;
		Double_t CenterUpper1 = h1->GetBinCenter(Upper1);
		Double_t CenterUpper2 = h1->GetBinCenter(Upper2);
		Double_t UpperBinWidth = CenterUpper2 - CenterUpper1;
		FWHMRightXValue = CenterUpper2 + (UpperBinWidth)*(UpperBinFraction);
	}
	//else if pertains if a bin is found with content of the HalfMaxYValue 
	else if (binB !=0){
		FWHMRightXValue = h1->GetBinCenter(binB);
	}
	//finding the FWHM
	Double_t FinalWidth = FWHMRightXValue - FWHMLeftXValue;
	Double_t FWHM = (FinalWidth/100)*100;
	cout << "FWHM:" << endl;
	cout << FWHM << endl;
	
	c1->cd(1);
	TString FWHM_string;
	FWHM_string = Form("FWHM:%lf",FWHM);
	TPaveLabel *a = new TPaveLabel(86, 3000, 90, 3500, FWHM_string);
	a->Draw();

}
