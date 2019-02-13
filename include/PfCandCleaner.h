// lxplus004

#ifndef __RANDOMCONE_H__
#define __RANDOMCONE_H__

#include <vector>
#include <string>

// root dependencies
#include "TString.h"
#include "TFile.h"
#include "TTree.h"

#define nref_max 10000
#define nTrk_max 50000

class PfCandCleaner{
public:
  PfCandCleaner(std::string& input, std::string& output){
    input_str = TString(input);
    output_str = TString(output);
  };
  void Init();
  void Execute();
  void PfCandTreeUpdate();
  void TrackTreeUpdate();
  void End();
  void Clear();
  bool PfPassCut(int key);

private:
  TString input_str;
  TString output_str;

  TFile* input_f;
  TFile* output_f;

  int nEvents;

  // pf cand tree
  TTree* pfcand_t;
  int nPFpart;
  std::vector<int>* pfId;
  std::vector<float>* pfPt;
  std::vector<float>* pfEta;
  std::vector<float>* pfPhi;
  std::vector<int>* trkidx;


  // jet tree
  TTree* jet_t;
  int nref;
  // static const int nref_max = 10000;
  float rawpt[nref_max];
  float jtpt[nref_max];
  float jteta[nref_max];
  float jtphi[nref_max];

  // track tree
  TTree* track_t;
  int	nTrk;
  // static const int nTrk_max = 50000;
  float trkPt[nTrk_max];
  float trkPtError[nTrk_max];
  unsigned char trkNHit[nTrk_max];
  bool highPurity[nTrk_max];
  float trkDxy1[nTrk_max];
  float trkDxyError1[nTrk_max];
  float trkDz1[nTrk_max];
  float trkDzError1[nTrk_max];
  unsigned char trkAlgo[nTrk_max];
  float trkEta[nTrk_max];
  float trkPhi[nTrk_max];

  TTree* pfcand_update_t;
  std::vector<bool>* pfPass;
  TTree* track_update_t;
  bool trkPass[nTrk_max];

  // output tree
  TTree* pseudojet_t;
  // scalar sum of pf pt
  std::vector<float>* pseudojet_pt;
  std::vector<float>* pseudojet_pt_cut;
  // number of pf cands
  std::vector<int>* pseudojet_n;
  std::vector<int>* pseudojet_n_cut;
  // jet position
  std::vector<float>* pseudojet_eta;
  std::vector<float>* pseudojet_phi;


};

#endif
