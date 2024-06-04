{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("B1.root");

  TCanvas*c1 = new TCanvas ("c1","",20,20,1000,1000);
  c1->Divide(1,1);

  TNtuple* ntuple = (TNtuple*)f.Get("B1");

  c1->cd(1);
  ntuple->Draw("Edep");
