#include "PfCandCleaner.h"
#include <iostream>

float deltaR(float eta1, float phi1, float eta2, float phi2);

void PfCandCleaner::Init(){
  input_f = new TFile(input_str, "READ");
  output_f = new TFile(output_str, "RECREATE");

  if(!input_f || !output_f){
    std::cout << "File pointer: Null!" << std::endl;
    exit(-1);
  }

  std::cout << "Init(): Processing " << input_str << std::endl;
  std::cout << "Init(): Output " << output_str << std::endl;

  jet_t = (TTree*) input_f->Get("akPu4CaloJetAnalyzer/t");
  // jet_t = (TTree*) input_f->Get("akCs4PFJetAnalyzer/t");

  pfcand_t = (TTree*) input_f->Get("pfcandAnalyzer/pfTree");
  track_t = (TTree*) input_f->Get("ppTrack/trackTree");


  if(!pfcand_t || !jet_t || !track_t){
    std::cout << "Tree pointer: Null!" << std::endl;
    exit(-1);
  }

  nEvents = (int) pfcand_t->GetEntries();

  pfcand_t->SetBranchStatus("*", 0);
  pfcand_t->SetBranchStatus("nPFpart", 1);
  pfcand_t->SetBranchStatus("pfId", 1);
  pfcand_t->SetBranchStatus("pfPt", 1);
  pfcand_t->SetBranchStatus("pfEta", 1);
  pfcand_t->SetBranchStatus("pfPhi", 1);
  pfcand_t->SetBranchStatus("trkidx", 1);

  pfId = new std::vector<int>();
  pfPt = new std::vector<float>();
  pfPhi = new std::vector<float>();
  pfEta = new std::vector<float>();
  trkidx = new std::vector<int>();

  pfcand_t->SetBranchAddress("nPFpart", &nPFpart);
  pfcand_t->SetBranchAddress("pfId", &pfId);
  pfcand_t->SetBranchAddress("pfPt", &pfPt);
  pfcand_t->SetBranchAddress("pfEta", &pfEta);
  pfcand_t->SetBranchAddress("pfPhi", &pfPhi);
  pfcand_t->SetBranchAddress("trkidx", &trkidx);

  jet_t->SetBranchStatus("*", 0);
  jet_t->SetBranchStatus("nref", 1);
  jet_t->SetBranchStatus("rawpt", 1);
  jet_t->SetBranchStatus("jtpt", 1);
  jet_t->SetBranchStatus("jteta", 1);
  jet_t->SetBranchStatus("jtphi", 1);

  jet_t->SetBranchAddress("nref", &nref);
  jet_t->SetBranchAddress("rawpt", rawpt);
  jet_t->SetBranchAddress("jtpt", jtpt);
  jet_t->SetBranchAddress("jteta", jteta);
  jet_t->SetBranchAddress("jtphi", jtphi);

  track_t->SetBranchStatus("*", 0);
  track_t->SetBranchStatus("nTrk", 1);
  track_t->SetBranchStatus("trkPt", 1);
  track_t->SetBranchStatus("trkPtError", 1);
  track_t->SetBranchStatus("trkNHit", 1);
  track_t->SetBranchStatus("highPurity", 1);
  track_t->SetBranchStatus("trkDxy1", 1);
  track_t->SetBranchStatus("trkDxyError1", 1);
  track_t->SetBranchStatus("trkDz1", 1);
  track_t->SetBranchStatus("trkDzError1", 1);
  track_t->SetBranchStatus("trkAlgo", 1);
  track_t->SetBranchStatus("trkEta", 1);
  track_t->SetBranchStatus("trkPhi", 1);
  track_t->SetBranchStatus("pfEcal", 1);
  track_t->SetBranchStatus("pfHcal", 1);

  track_t->SetBranchAddress("nTrk", &nTrk);
  track_t->SetBranchAddress("trkPt", trkPt);
  track_t->SetBranchAddress("trkPtError", trkPtError);
  track_t->SetBranchAddress("trkNHit", trkNHit);
  track_t->SetBranchAddress("highPurity", highPurity);
  track_t->SetBranchAddress("trkDxy1", trkDxy1);
  track_t->SetBranchAddress("trkDxyError1", trkDxyError1);
  track_t->SetBranchAddress("trkDz1", trkDz1);
  track_t->SetBranchAddress("trkDzError1", trkDzError1);
  track_t->SetBranchAddress("trkAlgo", trkAlgo);
  track_t->SetBranchAddress("trkPhi", trkPhi);
  track_t->SetBranchAddress("trkEta", trkEta);
  track_t->SetBranchAddress("pfEcal", pfEcal);
  track_t->SetBranchAddress("pfHcal", pfHcal);

  // output tree
  // pf cands matched to calo jets
  pseudojet_t = new TTree("pseudojet_t", "pseudojet_t");
  pseudojet_pt = new std::vector<float>();
  pseudojet_n = new std::vector<int>();
  pseudojet_pt_cut = new std::vector<float>();
  pseudojet_n_cut = new std::vector<int>();
  pseudojet_eta = new std::vector<float>();
  pseudojet_phi = new std::vector<float>();

  pseudojet_t->Branch("pseudojet_pt", pseudojet_pt);
  pseudojet_t->Branch("pseudojet_n", pseudojet_n);
  pseudojet_t->Branch("pseudojet_pt_cut", pseudojet_pt_cut);
  pseudojet_t->Branch("pseudojet_n_cut", pseudojet_n_cut);
  pseudojet_t->Branch("pseudojet_eta", pseudojet_eta);
  pseudojet_t->Branch("pseudojet_phi", pseudojet_phi);

  // pfcand with trkidx and cut
  pfcand_update_t = new TTree("pfcand_update_t", "pfcand_update_t");
  pfPass = new std::vector<bool>();
  pfAlgo = new std::vector<int>();
  pfZeroCalo = new std::vector<bool>();
  pfcand_update_t->Branch("nPFpart", &nPFpart);
  pfcand_update_t->Branch("pfId", &pfId);
  pfcand_update_t->Branch("pfPt", &pfPt);
  pfcand_update_t->Branch("pfEta", &pfEta);
  pfcand_update_t->Branch("pfPhi", &pfPhi);
  pfcand_update_t->Branch("trkidx", &trkidx);
  pfcand_update_t->Branch("pfPass", &pfPass);
  pfcand_update_t->Branch("pfAlgo", &pfAlgo);
  pfcand_update_t->Branch("pfZeroCalo", &pfZeroCalo);

  // track with cut
  track_update_t = new TTree("track_update_t", "track_update_t");
  // trkPass = new std::vector<bool>();
  track_update_t->Branch("nTrk", &nTrk);
  track_update_t->Branch("trkPt", trkPt, "trkPt[nTrk]/F");
  track_update_t->Branch("trkPtError", trkPtError, "trkPtError[nTrk]/F");
  track_update_t->Branch("trkEta", trkEta, "trkEta[nTrk]/F");
  track_update_t->Branch("trkPhi", trkPhi, "trkPhi[nTrk]/F");
  track_update_t->Branch("trkNHit", trkNHit, "trkNHit[nTrk]/b");
  track_update_t->Branch("highPurity", highPurity, "highPurity[nTrk]/O");
  track_update_t->Branch("trkDxy1", trkDxy1, "trkDxy1[nTrk]/F");
  track_update_t->Branch("trkDxyError1", trkDxyError1, "trkDxyError1[nTrk]/F");
  track_update_t->Branch("trkDz1", trkDz1, "trkDz1[nTrk]/F");
  track_update_t->Branch("trkDzError1", trkDzError1, "trkDzError1[nTrk]/F");
  track_update_t->Branch("trkAlgo", trkAlgo, "trkAlgo[nTrk]/b");
  track_update_t->Branch("trkPass", trkPass, "trkPass[nTrk]/O");
  track_update_t->Branch("pfEcal", pfEcal, "pfEcal[nTrk]/F");
  track_update_t->Branch("pfHcal", pfHcal, "pfHcal[nTrk]/F");

  std::cout << "Init(): nEvents " << nEvents << std::endl;
  std::cout << "Init(): Initialization Complete! " << std::endl;

};

void PfCandCleaner::PfCandTreeUpdate(){
  for(int evt=0; evt<nEvents; evt++){
    PfCandCleaner::Clear();
    pfcand_t->GetEntry(evt);
    track_t->GetEntry(evt);
    for(int ipfcand=0; ipfcand<nPFpart; ipfcand++){
      int key = trkidx->at(ipfcand);
      bool pass = PfCandCleaner::PfPassCut(key);
      pfPass->push_back(pass);
      bool zerocalo = PfCandCleaner::PfZeroCalo(key);
      pfZeroCalo->push_back(zerocalo);
      int trkalgo = PfCandCleaner::PfTrackAlgo(key);
      pfAlgo->push_back(trkalgo);
    }
    pfcand_update_t->Fill();
  }
};

void PfCandCleaner::TrackTreeUpdate(){
  for(int evt=0; evt<nEvents; evt++){
    PfCandCleaner::Clear();
    track_t->GetEntry(evt);
    for(int itrk=0; itrk<nTrk; itrk++){
      bool pass = PfCandCleaner::TrkPassCut(itrk);
      trkPass[itrk] = pass;
    }
    track_update_t->Fill();
  }
};


void PfCandCleaner::Execute(){
  for(int evt=0; evt<nEvents; evt++){
    PfCandCleaner::Clear();
    pfcand_t->GetEntry(evt);
    jet_t->GetEntry(evt);
    track_t->GetEntry(evt);
    // std::cout << "nref: " << nref << " nPFpart: " << nPFpart << " nTrk: " << nTrk << std::endl;
    if(nref<=0 || nPFpart<=0 || nTrk<=0) continue;

    for(int ijet=0; ijet<nref; ijet++){
      float pfcandpt = 0;
      float pfcandn = 0;
      float pfcandpt_cut = 0;
      float pfcandn_cut = 0;
      for(int ipfcand=0; ipfcand<nPFpart; ipfcand++){
        float dr = deltaR(jteta[ijet], jtphi[ijet], pfEta->at(ipfcand), pfPhi->at(ipfcand));
        if(dr>0.4) continue;
        pfcandn++;
        pfcandpt += pfPt->at(ipfcand);

        float key = trkidx->at(ipfcand);
        if(PfCandCleaner::PfPassCut(key)){
          pfcandn_cut++;
          pfcandpt_cut += pfPt->at(ipfcand);
        }
      }
      pseudojet_pt->push_back(pfcandpt);
      pseudojet_n->push_back(pfcandn);
      pseudojet_pt_cut->push_back(pfcandpt_cut);
      pseudojet_n_cut->push_back(pfcandn_cut);
      pseudojet_eta->push_back(jteta[ijet]);
      pseudojet_phi->push_back(jtphi[ijet]);
    }
  pseudojet_t->Fill();
  }
  std::cout << "Execute(): Complete! " << std::endl;

};

void PfCandCleaner::End(){
  output_f->cd();
  pseudojet_t->Write();
  pfcand_update_t->Write();
  track_update_t->Write();
  input_f->Close();
  output_f->Close();
  std::cout<< "End(): Process End!" << std::endl;

};

//.	HF path	single track path
// Quality	highPurity	highPurity
// nHits	> 11	> 11
// trkPtErr/trkPt	< 0.3	< 0.1
// trkDCA	-	< 3
bool PfCandCleaner::PfPassCut(int key){
  if(key<0) return true;
  else{
    // uncomment the line below to enable ZeroCalo filter
    // if(!PfZeroCalo(key)) return true;
    float trkDCA = std::sqrt(std::pow(trkDxy1[key], 2) + std::pow(trkDz1[key], 2));
    if(highPurity[key] && trkNHit[key]>11 && std::abs(trkPtError[key]/trkPt[key])<0.3 && trkDCA<3.0)
      return true;
    else
      return false;
  }
};

bool PfCandCleaner::TrkPassCut(int key){
  if(key<0) return true;
  else{
    float trkDCA = std::sqrt(std::pow(trkDxy1[key], 2) + std::pow(trkDz1[key], 2));
    if(highPurity[key] && trkNHit[key]>11 && std::abs(trkPtError[key]/trkPt[key])<0.3 && trkDCA<3.0)
      return true;
    else
      return false;
  }
};


int PfCandCleaner::PfTrackAlgo(int key){
  if(key<0) return -9999;
  else{
    return (int) trkAlgo[key];
  }
}

bool PfCandCleaner::PfZeroCalo(int key){
  if(pfHcal[key]>0 || pfEcal[key]>0) return false;
  else return true;
}

void PfCandCleaner::Clear(){
  pfId->clear();
  pfPt->clear();
  pfPhi->clear();
  pfEta->clear();
  trkidx->clear();
  pfPass->clear();
  pfAlgo->clear();
  pfZeroCalo->clear();
  // trkPass->clear();
  pseudojet_pt->clear();
  pseudojet_n->clear();
  pseudojet_pt_cut->clear();
  pseudojet_n_cut->clear();
  pseudojet_eta->clear();
  pseudojet_phi->clear();
};

float deltaR(float eta1, float phi1, float eta2, float phi2){
  float dr = std::pow(eta1-eta2, 2) + std::pow(phi1-phi2, 2);
  return (float) std::sqrt(dr);
};
