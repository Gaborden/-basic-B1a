
//root[0] .x plotHisto.C
{
 gROOT->Reset();
 gROOT->SetStyle("Plain");

 TFile f("B1.root");
 TCanvas*c1 = new TCanvas ("c1","",20,20,100,1000);

 c1->Divide(1,1);
 c1->cd(1);
 TH1D* hist1 =(TH1D*)f.Get("Edep");
 hist1->Draw("Hist");
}
