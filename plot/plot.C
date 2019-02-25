#define nTrk_max 50000

void SetPlotStyle(TH1D* hist, int marker_style, int marker_color, int line_style, int line_color);
void SetAxesTitle(TH2D* hist, TString xname, TString yname);
void SetAxesTitle(TH1D* hist, TString xname, TString yname);

int plot(){
  gStyle->SetOptStat(0);
  TFile* f = new TFile("../test.root", "READ");
  TTree* pfcand_t = (TTree*) f->Get("pfcand_update_t");
  TTree* track_t = (TTree*) f->Get("track_update_t");
  TTree* pseudojet_t = (TTree*) f->Get("pseudojet_t");

  int nEvents = pfcand_t->GetEntries();

  pfcand_t->Draw("pfPhi:pfEta>>pfcand_n_h2(50, -2,2, 50, -3.2, 3.2)", "", "colz");
  TH2D* pfcand_n_h2 = (TH2D*)gDirectory->Get("pfcand_n_h2");
  pfcand_n_h2->Scale(1./nEvents);
  // pfcand_n_h2->SetMinimum(0.);
  // pfcand_n_h2->SetMaximum(1.1);
  SetAxesTitle(pfcand_n_h2, "pfEta", "pfPhi");

  pfcand_t->Draw("pfPhi:pfEta>>pfcand_n_pass_h2(50, -2,2, 50, -3.2, 3.2)", "pfPass", "colz");
  TH2D* pfcand_n_pass_h2 = (TH2D*)gDirectory->Get("pfcand_n_pass_h2");
  pfcand_n_pass_h2->Scale(1./nEvents);
  // pfcand_n_pass_h2->SetMinimum(0.);
  // pfcand_n_pass_h2->SetMaximum(1.1);
  SetAxesTitle(pfcand_n_pass_h2, "pfEta", "pfPhi");

  pfcand_t->Draw("pfPhi:pfEta>>pfcand_n_nopass_h2(50, -2,2, 50, -3.2, 3.2)", "!pfPass", "colz");
  TH2D* pfcand_n_nopass_h2 = (TH2D*)gDirectory->Get("pfcand_n_nopass_h2");
  pfcand_n_nopass_h2->Scale(1./nEvents);
  // pfcand_n_nopass_h2->SetMinimum(0.);
  // pfcand_n_nopass_h2->SetMaximum(0.6);
  SetAxesTitle(pfcand_n_nopass_h2, "pfEta", "pfPhi");

  pfcand_t->Draw("pfPhi:pfEta>>pfcand_pt_h2(50, -2,2, 50, -3.2, 3.2)", "(1)*pfPt", "colz");
  TH2D* pfcand_pt_h2 = (TH2D*)gDirectory->Get("pfcand_pt_h2");
  pfcand_pt_h2->Scale(1./nEvents);
  // pfcand_pt_h2->SetMinimum(0.);
  // pfcand_pt_h2->SetMaximum(1.6);
  SetAxesTitle(pfcand_pt_h2, "pfEta", "pfPhi");

  pfcand_t->Draw("pfPhi:pfEta>>pfcand_pt_pass_h2(50, -2,2, 50, -3.2, 3.2)", "pfPass*pfPt", "colz");
  TH2D* pfcand_pt_pass_h2 = (TH2D*)gDirectory->Get("pfcand_pt_pass_h2");
  pfcand_pt_pass_h2->Scale(1./nEvents);
  // pfcand_pt_pass_h2->SetMinimum(0.);
  // pfcand_pt_pass_h2->SetMaximum(1.6);
  SetAxesTitle(pfcand_pt_pass_h2, "pfEta", "pfPhi");

  pfcand_t->Draw("pfPhi:pfEta>>pfcand_pt_nopass_h2(50, -2,2, 50, -3.2, 3.2)", "(!pfPass)*pfPt", "colz");
  TH2D* pfcand_pt_nopass_h2 = (TH2D*)gDirectory->Get("pfcand_pt_nopass_h2");
  pfcand_pt_nopass_h2->Scale(1./nEvents);
  // pfcand_pt_nopass_h2->SetMinimum(0.);
  // pfcand_pt_nopass_h2->SetMaximum(0.6);
  SetAxesTitle(pfcand_pt_nopass_h2, "pfEta", "pfPhi");

  std::cout
  << "pfcand_n_pass = " << pfcand_n_pass_h2->Integral()/pfcand_n_h2->Integral()*100 << " % "
  << "pfcand_n_nopass = " << pfcand_n_nopass_h2->Integral()/pfcand_n_h2->Integral()*100 << " % "
  << std::endl;

  std::cout
  << "pfcand_pt_pass = " << pfcand_pt_pass_h2->Integral()/pfcand_pt_h2->Integral()*100 << " % "
  << "pfcand_pt_nopass = " << pfcand_pt_nopass_h2->Integral()/pfcand_pt_h2->Integral()*100 << " % "
  << std::endl;

  TCanvas* pfcand_c = new TCanvas("pfcand_c", "", 1000, 600);
  pfcand_c->Divide(3,2);
  pfcand_c->cd(1);
  pfcand_n_h2->Draw("surf2");
  pfcand_c->cd(2);
  pfcand_n_pass_h2->Draw("surf2");
  pfcand_c->cd(3);
  pfcand_n_nopass_h2->Draw("surf2");
  pfcand_c->cd(4);
  pfcand_pt_h2->Draw("surf2");
  pfcand_c->cd(5);
  pfcand_pt_pass_h2->Draw("surf2");
  pfcand_c->cd(6);
  pfcand_pt_nopass_h2->Draw("surf2");

  pfcand_c->SaveAs("pfcand.pdf");


  track_t->Draw("trkPhi:trkEta>>trkn_hp_h2(50, -3,3, 50, -3.2, 3.2)", "highPurity&&trkAlgo==4&&trkPass", "surf2");
  TH2D* trkn_hp_h2 = (TH2D*)gDirectory->Get("trkn_hp_h2");
  trkn_hp_h2->Scale(1./nEvents);
  // trkn_hp_h2->SetMinimum(0.);
  // trkn_hp_h2->SetMaximum(0.6);
  SetAxesTitle(trkn_hp_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkn_nohp_h2(50, -3,3, 50, -3.2, 3.2)", "highPurity&&trkAlgo==4&&!trkPass", "surf2");
  TH2D* trkn_nohp_h2 = (TH2D*)gDirectory->Get("trkn_nohp_h2");
  trkn_nohp_h2->Scale(1./nEvents);
  // trkn_nohp_h2->SetMinimum(0.);
  // trkn_nohp_h2->SetMaximum(0.6);
  SetAxesTitle(trkn_nohp_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkn_pass_h2(50, -3,3, 50, -3.2, 3.2)", "highPurity&&trkAlgo==6&&trkPass", "surf2");
  TH2D* trkn_pass_h2 = (TH2D*)gDirectory->Get("trkn_pass_h2");
  trkn_pass_h2->Scale(1./nEvents);
  // trkn_pass_h2->SetMinimum(0.);
  // trkn_pass_h2->SetMaximum(0.6);
  SetAxesTitle(trkn_pass_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkn_nopass_h2(50, -3,3, 50, -3.2, 3.2)", "highPurity&&trkAlgo==6&&!trkPass", "surf2");
  TH2D* trkn_nopass_h2 = (TH2D*)gDirectory->Get("trkn_nopass_h2");
  trkn_nopass_h2->Scale(1./nEvents);
  // trkn_nopass_h2->SetMinimum(0.);
  // trkn_nopass_h2->SetMaximum(0.6);
  SetAxesTitle(trkn_nopass_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkn_hp_pass_h2(50, -3,3, 50, -3.2, 3.2)", "highPurity&&trkAlgo==7&&trkPass", "surf2");
  TH2D* trkn_hp_pass_h2 = (TH2D*)gDirectory->Get("trkn_hp_pass_h2");
  trkn_hp_pass_h2->Scale(1./nEvents);
  // trkn_hp_pass_h2->SetMinimum(0.);
  // trkn_hp_pass_h2->SetMaximum(0.6);
  SetAxesTitle(trkn_hp_pass_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkn_hp_nopass_h2(50, -3,3, 50, -3.2, 3.2)", "highPurity&&trkAlgo==7&&!trkPass", "surf2");
  TH2D* trkn_hp_nopass_h2 = (TH2D*)gDirectory->Get("trkn_hp_nopass_h2");
  trkn_hp_nopass_h2->Scale(1./nEvents);
  // trkn_hp_nopass_h2->SetMinimum(0.);
  // trkn_hp_nopass_h2->SetMaximum(0.6);
  SetAxesTitle(trkn_hp_nopass_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkpt_hp_h2(50, -3,3, 50, -3.2, 3.2)", "(highPurity&&trkAlgo==4&&trkPass)*trkPt", "surf2");
  TH2D* trkpt_hp_h2 = (TH2D*)gDirectory->Get("trkpt_hp_h2");
  trkpt_hp_h2->Scale(1./nEvents);
  // trkpt_hp_h2->SetMinimum(0.);
  // trkpt_hp_h2->SetMaximum(0.6);
  SetAxesTitle(trkpt_hp_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkpt_nohp_h2(50, -3,3, 50, -3.2, 3.2)", "(highPurity&&trkAlgo==4&&!trkPass)*trkPt", "surf2");
  TH2D* trkpt_nohp_h2 = (TH2D*)gDirectory->Get("trkpt_nohp_h2");
  trkpt_nohp_h2->Scale(1./nEvents);
  // trkpt_nohp_h2->SetMinimum(0.);
  // trkpt_nohp_h2->SetMaximum(0.6);
  SetAxesTitle(trkpt_nohp_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkpt_pass_h2(50, -3,3, 50, -3.2, 3.2)", "(highPurity&&trkAlgo==6&&trkPass)*trkPt", "surf2");
  TH2D* trkpt_pass_h2 = (TH2D*)gDirectory->Get("trkpt_pass_h2");
  trkpt_pass_h2->Scale(1./nEvents);
  // trkpt_pass_h2->SetMinimum(0.);
  // trkpt_pass_h2->SetMaximum(0.6);
  SetAxesTitle(trkpt_pass_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkpt_nopass_h2(50, -3,3, 50, -3.2, 3.2)", "(highPurity&&trkAlgo==6&&!trkPass)*trkPt", "surf2");
  TH2D* trkpt_nopass_h2 = (TH2D*)gDirectory->Get("trkpt_nopass_h2");
  trkpt_nopass_h2->Scale(1./nEvents);
  // trkpt_nopass_h2->SetMinimum(0.);
  // trkpt_nopass_h2->SetMaximum(0.6);
  SetAxesTitle(trkpt_nopass_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkpt_hp_pass_h2(50, -3,3, 50, -3.2, 3.2)", "(highPurity&&trkAlgo==7&&trkPass)*trkPt", "surf2");
  TH2D* trkpt_hp_pass_h2 = (TH2D*)gDirectory->Get("trkpt_hp_pass_h2");
  trkpt_hp_pass_h2->Scale(1./nEvents);
  // trkpt_hp_pass_h2->SetMinimum(0.);
  // trkpt_hp_pass_h2->SetMaximum(0.6);
  SetAxesTitle(trkpt_hp_pass_h2, "trkEta", "trkPhi");

  track_t->Draw("trkPhi:trkEta>>trkpt_hp_nopass_h2(50, -3,3, 50, -3.2, 3.2)", "(highPurity&&trkAlgo==7&&!trkPass)*trkPt", "surf2");
  TH2D* trkpt_hp_nopass_h2 = (TH2D*)gDirectory->Get("trkpt_hp_nopass_h2");
  trkpt_hp_nopass_h2->Scale(1./nEvents);
  // trkpt_hp_nopass_h2->SetMinimum(0.);
  // trkpt_hp_nopass_h2->SetMaximum(0.6);
  SetAxesTitle(trkpt_hp_nopass_h2, "trkEta", "trkPhi");

  float hp = trkn_hp_h2->Integral();
  float nohp = trkn_nohp_h2->Integral();
  float pass = trkn_pass_h2->Integral();
  float nopass = trkn_nopass_h2->Integral();
  float hp_pass = trkn_hp_pass_h2->Integral();
  float hp_nopass = trkn_hp_nopass_h2->Integral();

  std::cout
  << "trkn_hp = " << hp/(hp+nohp)*100 << " % "
  << "trkn_nohp = " << nohp/(hp+nohp)*100 << " % "
  << std::endl;

  std::cout
  << "trkn_pass = " << pass/(pass+nopass)*100 << " % "
  << "trkn_nopass = " << nopass/(pass+nopass)*100 << " % "
  << std::endl;

  std::cout
  << "trkn_hp_pass = " << hp_pass/(hp_pass+hp_nopass)*100 << " % "
  << "trkn_hp_nopass = " << hp_nopass/(hp_pass+hp_nopass)*100 << " % "
  << std::endl;

  hp = trkpt_hp_h2->Integral();
  nohp = trkpt_nohp_h2->Integral();
  pass = trkpt_pass_h2->Integral();
  nopass = trkpt_nopass_h2->Integral();
  hp_pass = trkpt_hp_pass_h2->Integral();
  hp_nopass = trkpt_hp_nopass_h2->Integral();

  std::cout
  << "trkpt_hp = " << hp/(hp+nohp)*100 << " % "
  << "trkpt_nohp = " << nohp/(hp+nohp)*100 << " % "
  << std::endl;

  std::cout
  << "trkpt_pass = " << pass/(pass+nopass)*100 << " % "
  << "trkpt_nopass = " << nopass/(pass+nopass)*100 << " % "
  << std::endl;

  std::cout
  << "trkpt_hp_pass = " << hp_pass/(hp_pass+hp_nopass)*100 << " % "
  << "trkpt_hp_nopass = " << hp_nopass/(hp_pass+hp_nopass)*100 << " % "
  << std::endl;

  TCanvas* trkn_c = new TCanvas("trkn_c", "", 800, 1000);
  trkn_c->Divide(2,3);
  trkn_c->cd(1);
  trkn_hp_h2->Draw("colz");
  trkn_c->cd(2);
  trkn_nohp_h2->Draw("colz");
  trkn_c->cd(3);
  trkn_pass_h2->Draw("colz");
  trkn_c->cd(4);
  trkn_nopass_h2->Draw("colz");
  trkn_c->cd(5);
  trkn_hp_pass_h2->Draw("colz");
  trkn_c->cd(6);
  trkn_hp_nopass_h2->Draw("colz");

  trkn_c->SaveAs("trackn.pdf");

  TCanvas* trkpt_c = new TCanvas("trkpt_c", "", 800, 1000);
  trkpt_c->Divide(2,3);
  trkpt_c->cd(1);
  trkpt_hp_h2->Draw("colz");
  trkpt_c->cd(2);
  trkpt_nohp_h2->Draw("colz");
  trkpt_c->cd(3);
  trkpt_pass_h2->Draw("colz");
  trkpt_c->cd(4);
  trkpt_nopass_h2->Draw("colz");
  trkpt_c->cd(5);
  trkpt_hp_pass_h2->Draw("colz");
  trkpt_c->cd(6);
  trkpt_hp_nopass_h2->Draw("colz");

  trkpt_c->SaveAs("trackpt.pdf");


  pseudojet_t->Draw("pseudojet_pt>>pseudojet_pt_h(100,0,200)");
  TH1D* pseudojet_pt_h = (TH1D*) gDirectory->Get("pseudojet_pt_h");

  pseudojet_t->Draw("pseudojet_pt_cut>>pseudojet_pt_cut_h(100,0,200)");
  TH1D* pseudojet_pt_cut_h = (TH1D*) gDirectory->Get("pseudojet_pt_cut_h");

  pseudojet_t->Draw("pseudojet_n>>pseudojet_n_h(100,0,200)");
  TH1D* pseudojet_n_h = (TH1D*) gDirectory->Get("pseudojet_n_h");

  pseudojet_t->Draw("pseudojet_n_cut>>pseudojet_n_cut_h(100,0,200)");
  TH1D* pseudojet_n_cut_h = (TH1D*) gDirectory->Get("pseudojet_n_cut_h");

  TCanvas* pseudojet_n_c = new TCanvas("pseudojet_n_c", "pseudojet_n_c", 800, 600);
  pseudojet_n_h->Scale(1./nEvents);
  pseudojet_n_cut_h->Scale(1./nEvents);
  pseudojet_n_c->cd();

  SetPlotStyle(pseudojet_n_h, 20, 2, 1, 2);
  SetPlotStyle(pseudojet_n_cut_h, 21, 4, 1, 4);
  SetAxesTitle(pseudojet_n_h, "nPfPart", "");
  SetAxesTitle(pseudojet_n_cut_h, "nPfPart", "");

  pseudojet_n_h->Draw();
  pseudojet_n_cut_h->Draw("same");
  TLegend* lg1 = new TLegend(0.7, 0.7, 0.9, 0.9);
  lg1->AddEntry("pseudojet_n_h", "nPFpart without cut", "lep");
  lg1->AddEntry("pseudojet_n_cut_h", "nPFpart with cut", "lep");
  lg1->Draw("same");
  pseudojet_n_c->SaveAs("pseudojet_n.pdf");

  TCanvas* pseudojet_pt_c = new TCanvas("pseudojet_pt_c", "pseudojet_pt_c", 800, 600);
  pseudojet_pt_h->Scale(1./nEvents);
  pseudojet_pt_cut_h->Scale(1./nEvents);
  pseudojet_pt_c->cd();

  SetPlotStyle(pseudojet_pt_h, 20, 2, 1, 2);
  SetPlotStyle(pseudojet_pt_cut_h, 21, 4, 1, 4);
  SetAxesTitle(pseudojet_pt_h, "pseudojet_pt", "");
  SetAxesTitle(pseudojet_pt_cut_h, "pseudojet_pt", "");

  pseudojet_pt_h->Draw();
  pseudojet_pt_cut_h->Draw("same");
  TLegend* lg2 = new TLegend(0.7, 0.7, 0.9, 0.9);
  lg2->AddEntry("pseudojet_pt_h", "pseodojet pt without cut", "lep");
  lg2->AddEntry("pseudojet_pt_cut_h", "pseudojet pt with cut", "lep");
  lg2->Draw("same");
  pseudojet_pt_c->SaveAs("pseudojet_pt.pdf");

  TCanvas* jetpt_c = new TCanvas("jetpt_c", "jetpt_c", 800, 600);
  pseudojet_t->Draw("pseudojet_pt_cut/pseudojet_pt>>jetpt_h(55,0,1.1)");
  TH1D* jetpt_h = (TH1D*) gDirectory->Get("jetpt_h");
  SetAxesTitle(jetpt_h, "ratio of pseudojet pt before/after cut", "");
  jetpt_h->Draw();
  jetpt_c->SaveAs("jetptratio.pdf");

  TCanvas* jetn_c = new TCanvas("jetn_c", "jetn_c", 800, 600);
  pseudojet_t->Draw("pseudojet_n_cut/pseudojet_n>>jetn_h(55,0,1.1)");
  TH1D* jetn_h = (TH1D*) gDirectory->Get("jetn_h");
  SetAxesTitle(jetn_h, "ratio of nPfpart before/after cut", "");
  jetn_h->Draw();
  jetn_c->SaveAs("jetnratio.pdf");


  TString str[16];
  str[0] = "(highPurity)*trkPt";
  str[1] = "(!highPurity)*trkPt";
  str[2] = "(highPurity&&trkPass)*trkPt";
  str[3] = "(highPurity&&!trkPass)*trkPt";
  str[4] = "(highPurity&&trkAlgo==4&&trkPass)*trkPt";
  str[5] = "(highPurity&&trkAlgo==4&&!trkPass)*trkPt";
  str[6] = "(highPurity&&trkAlgo==5&&trkPass)*trkPt";
  str[7] = "(highPurity&&trkAlgo==5&&!trkPass)*trkPt";
  str[8] = "(highPurity&&trkAlgo==6&&trkPass)*trkPt";
  str[9] = "(highPurity&&trkAlgo==6&&!trkPass)*trkPt";
  str[10] = "(highPurity&&trkAlgo==7&&trkPass)*trkPt";
  str[11] = "(highPurity&&trkAlgo==7&&!trkPass)*trkPt";
  str[12] = "(highPurity&&trkAlgo==22&&trkPass)*trkPt";
  str[13] = "(highPurity&&trkAlgo==22&&!trkPass)*trkPt";
  str[14] = "(highPurity&&trkAlgo==23&&trkPass)*trkPt";
  str[15] = "(highPurity&&trkAlgo==23&&!trkPass)*trkPt";

  for(int i=0; i<16; i++){
    track_t->Draw("trkPhi:trkEta>>hist(50, -3,3, 50, -3.2, 3.2)", Form("%s", str[i].Data()), "surf2");
    TH2D* hist = (TH2D*)gDirectory->Get("hist");
    std::cout<<str[i]<<" : " << hist->Integral()<<std::endl;
  }

  return 0;

}

void SetPlotStyle(TH1D* hist, int marker_style, int marker_color, int line_style, int line_color){
  hist->SetMarkerStyle(marker_style);
  hist->SetMarkerColor(marker_color);
  hist->SetLineStyle(line_style);
  hist->SetLineColor(line_color);
}

void SetAxesTitle(TH2D* hist, TString xname, TString yname){
  hist->GetXaxis()->SetTitle(xname);
  hist->GetYaxis()->SetTitle(yname);
}

void SetAxesTitle(TH1D* hist, TString xname, TString yname){
  hist->GetXaxis()->SetTitle(xname);
  hist->GetYaxis()->SetTitle(yname);
}
