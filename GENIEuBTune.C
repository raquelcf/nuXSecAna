//////// Simple macro for producing analysis variables, stored in a root file and also plotted, for muon-neutrino Charged Current inclusive (numu CC) events
//////// This code loops into events produced by a GENIE simulation (using MicroBooNE flux), performs a muon-neutrino Charged Current inclusive event selection without energy or angular thresolds, and calculate some kinematical variables.
//////// some resolutions are produced for the reconstructed neutrino energy
//////// event type is splitted into cathegories:
//////// CCQE: charged current quasi-elastic
//////// CCMEC: charged current meson-exchange current
//////// CCRES: charged current resonant (pion) production
//////// CCDIS: charged current deep inelastic scattering
//////// CCCOH: charged current coherent (pion) production
//////// other: just in case any event doesn't fall into any previous cathegory (for debbuging purposes)

#define GENIEuBTune_cxx
#include "GENIEuBTune.h"
#include <TH2.h>
#include "TH1D.h"
#include <TStyle.h>
#include <TCanvas.h>

#include "TVector3.h"
#include <vector>
#include  "TMath.h"
#include <iostream>
//#include <cstring>
#include <fstream> 
using namespace std;

/// define some common parameters that may be used later

#define PI 3.14159265
#define mumass 0.1056583755 // GeV/c2
#define protonmass 0.93827208816 //GeV/c2

/////////////////////////////// defining output files. one ROOT file (TFile format) and one text file (txt file) ///////////////////////////

ofstream anaGENIEuB;
TFile *outGENIEuB;

//////////////////////////////////////////////////////////////////// DECLARING HISTOGRAMS /////////////////////////////////////////////////////////////////

///// 1-D histograms, TH1D ///////////////////////////////

////// true momentum of the true muon selected:

TH1D *truemuon_truemom_CCQE_GENIE;
TH1D *truemuon_truemom_CCMEC_GENIE;
TH1D *truemuon_truemom_CCRES_GENIE;
TH1D *truemuon_truemom_CCDIS_GENIE;
TH1D *truemuon_truemom_CCCOH_GENIE;
TH1D *truemuon_truemom_other_GENIE;

////// true cosine of theta (angle with respect to the neutrino beam direction) of the true muon selected

TH1D *truemuon_truecostheta_CCQE_GENIE;
TH1D *truemuon_truecostheta_CCMEC_GENIE;
TH1D *truemuon_truecostheta_CCRES_GENIE;
TH1D *truemuon_truecostheta_CCDIS_GENIE;
TH1D *truemuon_truecostheta_CCCOH_GENIE;
TH1D *truemuon_truecostheta_other_GENIE;

////// true phi angle of the true muon selected (needs to double check. I want it from -pi to pi)

TH1D *truemuon_truephi_CCQE_GENIE;
TH1D *truemuon_truephi_CCMEC_GENIE;
TH1D *truemuon_truephi_CCRES_GENIE;
TH1D *truemuon_truephi_CCDIS_GENIE;
TH1D *truemuon_truephi_CCCOH_GENIE;
TH1D *truemuon_truephi_other_GENIE;

// true hadron multiplicity (considering the relevants: protons, neutrons, neutral/charged pions, etas and rhos)

TH1D *trueNh_CCQE_GENIE;
TH1D *trueNh_CCMEC_GENIE;
TH1D *trueNh_CCRES_GENIE;
TH1D *trueNh_CCDIS_GENIE;
TH1D *trueNh_CCCOH_GENIE;
TH1D *trueNh_other_GENIE;

// true (visible) hadron multiplicity, i.e. neutrons not accounted for (protons, charged/neutral pions, etas and rhos). Neutral mesons (pions, etas, rhos) decay very fast and their daughters are visible in a LArTPC (liquid argon time projection chamber) detector, as MicroBooNE

TH1D *trueNvish_CCQE_GENIE;
TH1D *trueNvish_CCMEC_GENIE;
TH1D *trueNvish_CCRES_GENIE;
TH1D *trueNvish_CCDIS_GENIE;
TH1D *trueNvish_CCCOH_GENIE;
TH1D *trueNvish_other_GENIE;

///// invariant mass (calculated from true neutrino energy)

TH1D *trueW_CCQE_GENIE;
TH1D *trueW_CCMEC_GENIE;
TH1D *trueW_CCRES_GENIE;
TH1D *trueW_CCDIS_GENIE;
TH1D *trueW_CCCOH_GENIE;
TH1D *trueW_other_GENIE;

///// missing transverse momentum (pT_miss), considering only a muon and protons are in the final state

TH1D *pT_CCQE_GENIE;
TH1D *pT_CCMEC_GENIE;
TH1D *pT_CCRES_GENIE;
TH1D *pT_CCDIS_GENIE;
TH1D *pT_CCCOH_GENIE;
TH1D *pT_other_GENIE;

///// reconstructed neutrino energy--- CCQE assumption

TH1D *EnuCCQE_CCQE_GENIE;
TH1D *EnuCCQE_CCMEC_GENIE;
TH1D *EnuCCQE_CCRES_GENIE;
TH1D *EnuCCQE_CCDIS_GENIE;
TH1D *EnuCCQE_CCCOH_GENIE;
TH1D *EnuCCQE_other_GENIE;

///// reconstructed neutrino energy--- calorimetry approach

TH1D *EnuCalo_CCQE_GENIE;
TH1D *EnuCalo_CCMEC_GENIE;
TH1D *EnuCalo_CCRES_GENIE;
TH1D *EnuCalo_CCDIS_GENIE;
TH1D *EnuCalo_CCCOH_GENIE;
TH1D *EnuCalo_other_GENIE;

///// reconstructed neutrino energy--- resonant+pion absoption assumption

TH1D *EnuRes_CCQE_GENIE;
TH1D *EnuRes_CCMEC_GENIE;
TH1D *EnuRes_CCRES_GENIE;
TH1D *EnuRes_CCDIS_GENIE;
TH1D *EnuRes_CCCOH_GENIE;
TH1D *EnuRes_other_GENIE;

//////////////////////////////////// RESOLUTIONS in neutrino energy reconstruction ////////////////////////////

//// 2-D histograms. We plot difference of true-reconstructed with respect to true quantity. The resolution would be: (true-reconstructed)/true

TH2D *Resolution_EnuCCQE_GENIE;
TH2D *Resolution_EnuCalo_GENIE;
TH2D *Resolution_EnuRes_GENIE;

//// profile plots to look at resolution: mean value at each bin for the (true - reconstructed) neutrino energy, plotted with respect to the true neutrino energy. 
TProfile *hprof_EnuCCQE_GENIE;
TProfile *hprof_EnuCalo_GENIE;
TProfile *hprof_EnuRes_GENIE;

///////////////////////////////////////////////////////////////////// END of DECLARING HISTROGRAMS ///////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////  SOME COUNTERS //////////////////////////////////////////////////////////////////

int totentries =0;/// number of total numu CC events selected
int nCCQE = 0;/// number of total numu CCQE events selected
int nCCMEC =0;/// number of total numu CCMEC events selected
int nCCRes =0;/// number of total numu CCRes events selected
int nCCDIS =0;/// number of total numu CCDIS events selected
int nCCCOH =0;/// number of total numu CCCOH events selected
int nCCNue =0;/// number of total numu CCNue events selected (they aren't selected, this is not used)
int nNC =0;/// number of total numu neutral current events selected (they aren't selected, this is not used)
int nantinu= 0;/// number of total anti-numu events selected (they aren't selected, this is not used) 
int nother =0;/// just for debbuging

///////////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////

///// formula of the reconstructed neutrino energy using calorimetry. Used previously by the ArgoNeuT experiment
//// np is 0, we use Ar40

double GetEcalomiss(double Esum, double PTmiss, int np) { 
  //Esum *= 1000; //convert to MeV
  //PTmiss *= 1000; //convert to MeV
  double Eexcit = 0.0304; //in GeV
  double Mass = 0; // in GeV
  if(np == 0) Mass = 37.2050; //Ar40 in GeV
  else if(np == 1) Mass = 36.2758; //Ar39
  else if(np == 2) Mass = 35.3669; //Cl38
  else if(np == 3) Mass = 34.4201; //S37
  else if(np == 4) Mass = 33.4957; //P36
  else if(np == 5) Mass = 32.5706; //Si35
  else if(np == 6) Mass = 31.6539; //Al34
  else if(np == 7) Mass = 30.7279; //Mg33
  else if(np == 8) Mass = 29.8111; //Na32
  else if(np == 9) Mass = 28.8918; //Ne31
  else if(np >= 10) Mass = 27.9789; //F30

  double Ekinrecoil = sqrt(PTmiss*PTmiss + Mass*Mass) - Mass;
  return Esum + Eexcit + Ekinrecoil; // return result in GeV

}

///// formula of the reconstructed neutrino energy assuming it was a CCQE interaction and that the nucleon was at rest (proton mass does not correct for bound nucleon, we should do! but need to get this number for argon first. Effect should be minimal). 

double GetEnuCCQE(double emu, double cosmu, double pmu){

  double Enum = (protonmass*emu) - (mumass*mumass)/2.;
  double Eden = protonmass - emu + (pmu*cosmu);
 
  return (Enum/Eden); // return result in GeV
  
}

///// formula of the reconstructed neutrino energy assuming all events are produced via resonant pion production interaction, and the pions were absorved by the nucleus.

double GetEnuRes(double emu, double cosmu){
  
  double mdelta= 1.232;//delta mass GeV/c2
  double Enum = (mdelta*mdelta) - (protonmass*protonmass) + (2.*protonmass*emu);
  double Eden = 2.*(protonmass-(emu*(1.-cosmu)));
 
  return (Enum/Eden);// return result in GeV
  
}

/// computing the cosine angle of a trajectory with respect to the neutrino beam direction
double cosine(double px, double py , double pz){

  double norm_P = sqrt(pow(px,2) + pow(py,2)+ pow(pz,2));
  
  TVector3 pdir;
  pdir[0] = px;
  pdir[1] = py;
  pdir[2] = pz;

  TVector3 beamdir;
  beamdir[0] = 0;
  beamdir[1] = 0;
  beamdir[2] = 1;

  double cos; // scalar product
  cos = pdir.Dot(beamdir);
  cos = cos/(norm_P);

  return cos;

}

/// computing the phi angle /// ***** NEEDS DOUBLE CHECK
double Getphi(double x, double y, double z){ /// [-PI, PI] 

  double r = sqrt(x*x + y*y + z*z);
  double calcphi = acos(z/r);
  
  return calcphi;
 
}

//// calculating number of hadrons per event
int Nh(int neutron, int npion, int pi0, int ppion, int proton, int kaon, int eta, int rho){//// total number of hadrons
 
  int tothad = neutron + npion + pi0 + ppion + proton + kaon + eta + rho; 
  return tothad;

}

//// calculating number of hadrons per event, except for neutrons
int Nvish(int npion, int pi0, int ppion, int proton, int kaon, int eta, int rho){//// total number of hadrons

  int tothad = npion + pi0 + ppion + proton + kaon + eta + rho;
  return tothad;

}

//// calculating 4-momentum transfer. We could also use as input any reconstructed neutrino energy
double GetQ2(double enu, double emu, double pmuz){ /// invariant 4-momentum transfer

  double pmuL = pmuz;
  double mom4 = 2 * enu * (emu - pmuL) - mumass*mumass;
  return mom4;
  
}

//// calculating the energy transfer from the neutrino to the nucleus. We could use as input reconstructred neutrino energy also to test resolutions
double w(double emu, double enu){ ///// energy transfer

  return (enu - emu);
  
}
///// calculating the hadronic invariant mass. We could also use as input the reconstructed energy transfer
double InvMass(double momtrans, double enutrans){ /// invariant hadronic mass

  double invm = protonmass*protonmass + 2*protonmass*enutrans - momtrans*momtrans;

  return sqrt(invm);
}

/// Bjorken scaling variable. We could use also reconstructed momentum transfer and energy transfer. IS a good variable to test the inelasticity of the interaction
double Bkorken(double momtrans, double enutrans){ ///// Bjorken scaling variable

  double bj = (momtrans*momtrans);
  return (bj/(2*protonmass*enutrans));

}

/// relative energy transfer of the neutrino to the nucleus. Very useful as we have an spread neutrino energy spectra
double wRel(double enutrans, double enu){ //// relative energy transfer
  return enutrans/enu;
}
/////////////////////////////////////////////////////////////


////////// topological description of the event using the particle content that escapes formt he nucleus after the interaction (final state particles). We will play with this later. Needs modifications forour own studies.

int Topology(int nmuons, int nelectrons, int npions, int npi0, int nprotons) {
  //// This function return the true topology of the event, numu & anti-numu                                                        
  ////1. CC0Pion0Proton                                                                                                            
  ////2. CC0Pion1Proton                                  
  ////3. CC0Pion2Proton                                                                                                            
  ////4. CC0PionNProton                                                                                                            
  ////5. CC1PionNProton (1 Pion= 1 charged pion || 1 neutral pion)
  ////6. CCNPionNProton    
  ////7. CCnue-antinue   
  ////8. NC                                                                                            
  ////9. OOFV (nu event out of FV)                                                                                                 
  ////10. Cosmic                                                                                                       
  ////11. Other (just in case, let's check!)                                                                     
  /// e.g. numu CC inclusive= Topology >0 && Topology < 7

  if (nmuons >0 && (nelectrons + npions + npi0 ) == 0 && nprotons ==0 ) return 1;
  if (nmuons >0 && (nelectrons + npions + npi0 ) == 0 && nprotons ==1 ) return 2;
  if (nmuons >0 && (nelectrons + npions + npi0 ) == 0 && nprotons ==2 ) return 3;
  if (nmuons >0 && (nelectrons + npions + npi0 ) == 0 && nprotons >2 ) return 4;
  if (nmuons >0 && (nelectrons ) == 0 && (npions + npi0) == 1 ) return 5;
  if (nmuons >0 && (nelectrons ) == 0 && (npions + npi0) > 1 ) return 6;
  //  if (nmuons == 0 && nelectrons > 0 ) return 7;
  //  if (nmuons==0  && nelectrons ==0) return 8;

  else return 11;

}

///////////////////////////////////////////// HERE WE START LOOPING EVENT TO EVENT ///////////////////////////////////////////////////
void GENIEuBTune::Loop() ///// variables read from GENIE file, are specific to GENIE nomenclature
{
//   In a ROOT session, you can do:
//      root> .L GENIEuBTune.C
//      root> GENIEuBTune t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

  
  if (fChain == 0) return;

  bool numuCC = false; //// by default we don't have any event selected as numu CC
   
  Long64_t nentries = fChain->GetEntriesFast();

   /////////// output files location and histogram definitions /////////////// **** CHANGE TO YOUR OWN PATH   *** //////////////
  outGENIEuB = new TFile("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning/output/analysis_GENIE.root","RECREATE");
  anaGENIEuB.open("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning/output/info_uBGENIE.txt");

  //// histograms must include range and number of bins ////
  //// be careful when using TStack you need all histograms with the same range and number of bins

  truemuon_truemom_CCQE_GENIE = new TH1D("truemuon_truemom_CCQE_GENIE", "truemuon_truemom_CCQE_GENIE", 60, 0, 3);
  truemuon_truemom_CCMEC_GENIE = new TH1D("truemuon_truemom_CCMEC_GENIE", "truemuon_truemom_CCMEC_GENIE", 60, 0, 3);
  truemuon_truemom_CCRES_GENIE = new TH1D("truemuon_truemom_CCRES_GENIE", "truemuon_truemom_CCRES_GENIE", 60, 0, 3);
  truemuon_truemom_CCDIS_GENIE = new TH1D("truemuon_truemom_CCDIS_GENIE", "truemuon_truemom_CCDIS_GENIE", 60, 0, 3);
  truemuon_truemom_CCCOH_GENIE = new TH1D("truemuon_truemom_CCCOH_GENIE", "truemuon_truemom_CCCOH_GENIE", 60, 0, 3);
  truemuon_truemom_other_GENIE = new TH1D("truemuon_truemom_other_GENIE", "truemuon_truemom_other_GENIE", 60, 0, 3);
 
  truemuon_truecostheta_CCQE_GENIE = new TH1D("truemuon_truecostheta_CCQE_GENIE", "truemuon_truecostheta_CCQE_GENIE", 60, -1, 1);
  truemuon_truecostheta_CCMEC_GENIE = new TH1D("truemuon_truecostheta_CCMEC_GENIE", "truemuon_truecostheta_CCMEC_GENIE", 60, -1, 1);
  truemuon_truecostheta_CCRES_GENIE = new TH1D("truemuon_truecostheta_CCRES_GENIE", "truemuon_truecostheta_CCRES_GENIE", 60, -1, 1);
  truemuon_truecostheta_CCDIS_GENIE = new TH1D("truemuon_truecostheta_CCDIS_GENIE", "truemuon_truecostheta_CCDIS_GENIE", 60, -1, 1);
  truemuon_truecostheta_CCCOH_GENIE = new TH1D("truemuon_truecostheta_CCCOH_GENIE", "truemuon_truecostheta_CCCOH_GENIE", 60, -1, 1);
  truemuon_truecostheta_other_GENIE = new TH1D("truemuon_truecostheta_other_GENIE", "truemuon_truecostheta_other_GENIE", 60, -1, 1);

  truemuon_truephi_CCQE_GENIE = new TH1D("truemuon_truephi_CCQE_GENIE", "truemuon_truephi_CCQE_GENIE", 60, -3.15, 3.15);
  truemuon_truephi_CCMEC_GENIE = new TH1D("truemuon_truephi_CCMEC_GENIE", "truemuon_truephi_CCMEC_GENIE", 60, -3.15, 3.15);
  truemuon_truephi_CCRES_GENIE = new TH1D("truemuon_truephi_CCRES_GENIE", "truemuon_truephi_CCRES_GENIE", 60, -3.15, 3.15);
  truemuon_truephi_CCDIS_GENIE = new TH1D("truemuon_truephi_CCDIS_GENIE", "truemuon_truephi_CCDIS_GENIE", 60, -3.15, 3.15);
  truemuon_truephi_CCCOH_GENIE = new TH1D("truemuon_truephi_CCCOH_GENIE", "truemuon_truephi_CCCOH_GENIE", 60, -3.15, 3.15);
  truemuon_truephi_other_GENIE = new TH1D("truemuon_truephi_other_GENIE", "truemuon_truephi_other_GENIE", 60, -3.15, 3.15);

  trueNh_CCQE_GENIE = new TH1D("trueNh_CCQE_GENIE", "trueNh_CCQE_GENIE", 15, 0, 15);
  trueNh_CCMEC_GENIE = new TH1D("trueNh_CCMEC_GENIE", "trueNh_CCMEC_GENIE", 15, 0, 15);
  trueNh_CCRES_GENIE = new TH1D("trueNh_CCRES_GENIE", "trueNh_CCRES_GENIE", 15, 0, 15);
  trueNh_CCDIS_GENIE = new TH1D("trueNh_CCDIS_GENIE", "trueNh_CCDIS_GENIE", 15, 0, 15);
  trueNh_CCCOH_GENIE = new TH1D("trueNh_CCCOH_GENIE", "trueNh_CCCOH_GENIE", 15, 0, 15);
  trueNh_other_GENIE = new TH1D("trueNh_other_GENIE", "trueNh_other_GENIE", 15, 0, 15);

  trueNvish_CCQE_GENIE = new TH1D("trueNvish_CCQE_GENIE", "trueNvish_CCQE_GENIE", 15, 0, 15);
  trueNvish_CCMEC_GENIE = new TH1D("trueNvish_CCMEC_GENIE", "trueNvish_CCMEC_GENIE", 15, 0, 15);
  trueNvish_CCRES_GENIE = new TH1D("trueNvish_CCRES_GENIE", "trueNvish_CCRES_GENIE", 15, 0, 15);
  trueNvish_CCDIS_GENIE = new TH1D("trueNvish_CCDIS_GENIE", "trueNvish_CCDIS_GENIE", 15, 0, 15);
  trueNvish_CCCOH_GENIE = new TH1D("trueNvish_CCCOH_GENIE", "trueNvish_CCCOH_GENIE", 15, 0, 15);
  trueNvish_other_GENIE = new TH1D("trueNvish_other_GENIE", "trueNvish_other_GENIE", 15, 0, 15);

  trueW_CCQE_GENIE = new TH1D("trueW_CCQE_GENIE", "trueW_CCQE_GENIE", 50, 0, 2);
  trueW_CCMEC_GENIE = new TH1D("trueW_CCMEC_GENIE", "trueW_CCMEC_GENIE", 50, 0, 2);
  trueW_CCRES_GENIE = new TH1D("trueW_CCRES_GENIE", "trueW_CCRES_GENIE", 50, 0, 2);
  trueW_CCDIS_GENIE = new TH1D("trueW_CCDIS_GENIE", "trueW_CCDIS_GENIE", 50, 0, 2);
  trueW_CCCOH_GENIE = new TH1D("trueW_CCCOH_GENIE", "trueW_CCCOH_GENIE", 50, 0, 2);
  trueW_other_GENIE = new TH1D("trueW_other_GENIE", "trueW_other_GENIE", 50, 0, 2);

  pT_CCQE_GENIE = new TH1D("pT_CCQE_GENIE", "pT_CCQE_GENIE", 50, 0, 2);
  pT_CCMEC_GENIE = new TH1D("pT_CCMEC_GENIE", "pT_CCMEC_GENIE", 50, 0, 2);
  pT_CCRES_GENIE = new TH1D("pT_CCRES_GENIE", "pT_CCRES_GENIE", 50, 0, 2);
  pT_CCDIS_GENIE = new TH1D("pT_CCDIS_GENIE", "pT_CCDIS_GENIE", 50, 0, 2);
  pT_CCCOH_GENIE = new TH1D("pT_CCCOH_GENIE", "pT_CCCOH_GENIE", 50, 0, 2);
  pT_other_GENIE = new TH1D("pT_other_GENIE", "pT_other_GENIE", 50, 0, 2);

  EnuCCQE_CCQE_GENIE = new TH1D("EnuCCQE_CCQE_GENIE", "EnuCCQE_CCQE_GENIE", 60, 0, 3);
  EnuCCQE_CCMEC_GENIE = new TH1D("EnuCCQE_CCMEC_GENIE", "EnuCCQE_CCMEC_GENIE", 60, 0, 3);
  EnuCCQE_CCRES_GENIE = new TH1D("EnuCCQE_CCRES_GENIE", "EnuCCQE_CCRES_GENIE", 60, 0, 3);
  EnuCCQE_CCDIS_GENIE = new TH1D("EnuCCQE_CCDIS_GENIE", "EnuCCQE_CCDIS_GENIE", 60, 0, 3);
  EnuCCQE_CCCOH_GENIE = new TH1D("EnuCCQE_CCCOH_GENIE", "EnuCCQE_CCCOH_GENIE", 60, 0, 3);
  EnuCCQE_other_GENIE = new TH1D("EnuCCQE_other_GENIE", "EnuCCQE_other_GENIE", 60, 0, 3);

  EnuCalo_CCQE_GENIE = new TH1D("EnuCalo_CCQE_GENIE", "EnuCalo_CCQE_GENIE", 60, 0, 3);
  EnuCalo_CCMEC_GENIE = new TH1D("EnuCalo_CCMEC_GENIE", "EnuCalo_CCMEC_GENIE", 60, 0, 3);
  EnuCalo_CCRES_GENIE = new TH1D("EnuCalo_CCRES_GENIE", "EnuCalo_CCRES_GENIE", 60, 0, 3);
  EnuCalo_CCDIS_GENIE = new TH1D("EnuCalo_CCDIS_GENIE", "EnuCalo_CCDIS_GENIE", 60, 0, 3);
  EnuCalo_CCCOH_GENIE = new TH1D("EnuCalo_CCCOH_GENIE", "EnuCalo_CCCOH_GENIE", 60, 0, 3);
  EnuCalo_other_GENIE = new TH1D("EnuCalo_other_GENIE", "EnuCalo_other_GENIE", 60, 0, 3);

  EnuRes_CCQE_GENIE = new TH1D("EnuRes_CCQE_GENIE", "EnuRes_CCQE_GENIE", 60, 0, 3);
  EnuRes_CCMEC_GENIE = new TH1D("EnuRes_CCMEC_GENIE", "EnuRes_CCMEC_GENIE", 60, 0, 3);
  EnuRes_CCRES_GENIE = new TH1D("EnuRes_CCRES_GENIE", "EnuRes_CCRES_GENIE", 60, 0, 3);
  EnuRes_CCDIS_GENIE = new TH1D("EnuRes_CCDIS_GENIE", "EnuRes_CCDIS_GENIE", 60, 0, 3);
  EnuRes_CCCOH_GENIE = new TH1D("EnuRes_CCCOH_GENIE", "EnuRes_CCCOH_GENIE", 60, 0, 3);
  EnuRes_other_GENIE = new TH1D("EnuRes_other_GENIE", "EnuRes_other_GENIE", 60, 0, 3);

  //// resolution neutrino energy reconstruction //// 2-D histograms has the range in X and Y
  
  Resolution_EnuCCQE_GENIE= new TH2D("Resolution_EnuCCQE_GENIE", "Resolution_EnuCCQE_GENIE",40,0.,2., 80, -2,2.);
  Resolution_EnuCalo_GENIE= new TH2D("Resolution_EnuCalo_GENIE", "Resolution_EnuCalo_GENIE",40,0.,2., 80, -2,2.);
  Resolution_EnuRes_GENIE= new TH2D("Resolution_EnuRes_GENIE", "Resolution_EnuRes_GENIE",40,0.,2., 80, -2,2.);

  hprof_EnuCCQE_GENIE = new TProfile("hprof_EnuCCQE_GENIE;", "",50,0,1.5,-2.,2.);
  hprof_EnuCalo_GENIE = new TProfile("hprof_EnuCalo_GENIE;", "",50,0,1.5,-2.,2.);
  hprof_EnuRes_GENIE = new TProfile("hprof_EnuRes_GENIE;", "",50,0,1.5,-2.,2.);

///////////////////////////////////////////

  /////// and here starts the real loop event by event
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      numuCC = false; /// re-initiate the boolean to false, so we don't select  events by mistake

      if(neu == 14 && cc && Ev>0 && El >0) numuCC = true; /// this is the condition to select a numu CC event in true variables (neu== neutrino pdg is for muon neutrino, cc== is a charged current event, Ev== neutrino energy, El==charged lepton energy). Boolean is TRUE if the event is numu CC
      if (!numuCC) continue; 
      
      totentries++; /// counting number of events selected as numu CC

      //couting number of particles int eh final state by type.
      int nneutron = 0; /// number of neutrons
      int nnpion = 0; /// number of negative pions
      int nproton = 0; /// number of protons
      int nnegpion = 0;/// number of negative pions
      int npospion = 0;/// number of positive pions
      int nkaon = 0;/// number of kaons (we don't care if negative or positive)
      int neta = 0;/// number of etas (we don't care if negative or positive)
      int nrho = 0;/// number of rhos (we don't care if negative or positive)

      /////// some true kinematics for all events //////
      double deltax =pxl;/// muon px (momentum in x)
      double deltay =pyl; // muon py (momentum in y)
      double Esum =0; /// sum of total kinetic energies
      double pmu = sqrt(pxl*pxl + pyl*pyl + pzl*pzl); /// true muon (absolute) momentum
      double emu = sqrt(mumass*mumass + pmu*pmu); /// true muon energy
      double q2 = GetQ2(Ev, emu, pzl); /// 4-momentum transfer from true kinematics
      double omega = w(emu, Ev); /// true energy transfer
      double protonmom =0; //// momentum of the proton

      //////// loop over all final state hadrons per event // later we decide the interaction type ///

      //std::cout<<"number of FS particles "<<nf <<std::endl;
 
      for(Int_t ki=0; ki<nf; ++ki ){
	if (pdgf[ki] == 2212) {/// we look at each particle type using their PDG codes (https://pdg.lbl.gov/2007/reviews/montecarlorpp.pdf)
	  nproton++;
	  deltax= deltax + pxf[ki]; /// adding protons px
	  deltay= deltay + pyf[ki]; // addin protons py
	  protonmom = sqrt(pxf[ki]*pxf[ki] + pyf[ki]*pyf[ki] + pzf[ki]*pzf[ki]);
	  Esum= Esum + protonmom*protonmom/(2*protonmass); /// summatory of protons kinetic energy    
	}
	else if (pdgf[ki] == 2112) nneutron++;
	else if (pdgf[ki] == 211) npospion++;
	else if (pdgf[ki] == -211) nnegpion++;
	else if (pdgf[ki] == 111) nnpion++;
	else if (abs(pdgf[ki]) == 321) nkaon++;
	else if (abs(pdgf[ki]) == 211) neta++;
	else if (abs(pdgf[ki]) == 213) nrho++;
	}
    
      //////////  end loop final state hadrons ///////////////

       double PTmiss = sqrt(deltax*deltax + deltay*deltay); /// missing transverse momentum (considering all protons in the final states)
       Esum= Esum + emu; /// total energy of the muon + protons kinetic energy
       
       /// check interaction type and fill histograms ///////

       if(qel==true){
	 nCCQE++;

	 //// true kinematics /////
	 truemuon_truemom_CCQE_GENIE->Fill(sqrt(pow(pxl,2)+ pow(pyl,2)+pow(pzl,2)));
	 truemuon_truecostheta_CCQE_GENIE->Fill(cosine(pxl, pyl , pzl));
	 truemuon_truephi_CCQE_GENIE->Fill(Getphi(pxl, pyl, pzl));
	 trueNh_CCQE_GENIE->Fill(Nh(nneutron, nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueNvish_CCQE_GENIE->Fill(Nvish(nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueW_CCQE_GENIE->Fill(InvMass(q2, omega));
	 pT_CCQE_GENIE->Fill(PTmiss);/// assuming 1muon + protons in the final state
	 EnuCCQE_CCQE_GENIE->Fill(GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 EnuCalo_CCQE_GENIE->Fill(GetEcalomiss(Esum, PTmiss, 0));/// assuming 1muon + protons int eh final state, Ar40 (np=0)
	 EnuRes_CCQE_GENIE->Fill(GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 ///// filling resolution histograms in all interaction types
	 Resolution_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 Resolution_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0));
	 Resolution_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 hprof_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu),1);
	 hprof_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0),1);
	 hprof_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)),1);
       }

       else if(mec==true){
	 nCCMEC++;

	 /// true kinematics /////
	 truemuon_truemom_CCMEC_GENIE->Fill(sqrt(pow(pxl,2)+ pow(pyl,2)+pow(pzl,2)));
	 truemuon_truecostheta_CCMEC_GENIE->Fill(cosine(pxl, pyl , pzl));
	 truemuon_truephi_CCMEC_GENIE->Fill(Getphi(pxl, pyl, pzl));
	 trueNh_CCMEC_GENIE->Fill(Nh(nneutron, nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueNvish_CCMEC_GENIE->Fill(Nvish(nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueW_CCMEC_GENIE->Fill(InvMass(q2, omega));
	 pT_CCMEC_GENIE->Fill(PTmiss);/// assuming 1muon + protons int he final state
	 EnuCCQE_CCMEC_GENIE->Fill(GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 EnuCalo_CCMEC_GENIE->Fill(GetEcalomiss(Esum, PTmiss, 0));/// assuming 1muon + protons int eh final state, Ar40 (np=0)
	 EnuRes_CCMEC_GENIE->Fill(GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 //// filling resolution histograms in all interaction types
	 Resolution_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 Resolution_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0));
	 Resolution_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 hprof_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu),1);
	 hprof_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0),1);
	 hprof_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)),1);
       }

       else if(res==true){
	 nCCRes++;

	////// true kinematics /////
	 truemuon_truemom_CCRES_GENIE->Fill(sqrt(pow(pxl,2)+ pow(pyl,2)+pow(pzl,2)));
	 truemuon_truecostheta_CCRES_GENIE->Fill(cosine(pxl, pyl , pzl));
	 truemuon_truephi_CCRES_GENIE->Fill(Getphi(pxl, pyl, pzl));
	 trueNh_CCRES_GENIE->Fill(Nh(nneutron, nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueNvish_CCRES_GENIE->Fill(Nvish(nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueW_CCRES_GENIE->Fill(InvMass(q2, omega));
	 pT_CCRES_GENIE->Fill(PTmiss);/// assuming 1muon + protons int he final state
	 EnuCCQE_CCRES_GENIE->Fill(GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 EnuCalo_CCRES_GENIE->Fill(GetEcalomiss(Esum, PTmiss, 0));/// assuming 1muon + protons int eh final state, Ar40 (np=0)
	 EnuRes_CCRES_GENIE->Fill(GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 //// filling resolution histograms in all interaction types
	 Resolution_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 Resolution_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0));
	 Resolution_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 hprof_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu),1);
	 hprof_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0),1);
	 hprof_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)),1);
       }

       else if(dis==true){
	 nCCDIS++;

	 //// true kinematics /////
	 truemuon_truemom_CCDIS_GENIE->Fill(sqrt(pow(pxl,2)+ pow(pyl,2)+pow(pzl,2)));
	 truemuon_truecostheta_CCDIS_GENIE->Fill(cosine(pxl, pyl , pzl));
	 truemuon_truephi_CCDIS_GENIE->Fill(Getphi(pxl, pyl, pzl));
	 trueNh_CCDIS_GENIE->Fill(Nh(nneutron, nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueNvish_CCDIS_GENIE->Fill(Nvish(nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueW_CCDIS_GENIE->Fill(InvMass(q2, omega));
	 pT_CCDIS_GENIE->Fill(PTmiss);/// assuming 1muon + protons int he final state
	 EnuCCQE_CCDIS_GENIE->Fill(GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 EnuCalo_CCDIS_GENIE->Fill(GetEcalomiss(Esum, PTmiss, 0));/// assuming 1muon + protons int eh final state, Ar40 (np=0)
	 EnuRes_CCDIS_GENIE->Fill(GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	////// filling resolution histograms in all interaction types
	 Resolution_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 Resolution_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0));
	 Resolution_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 hprof_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu),1);
	 hprof_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0),1);
	 hprof_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)),1);

       }

       else if(coh==true){
	 nCCCOH++;

	 /// true kinematics /////
	 truemuon_truemom_CCCOH_GENIE->Fill(sqrt(pow(pxl,2)+ pow(pyl,2)+pow(pzl,2)));
	 truemuon_truecostheta_CCCOH_GENIE->Fill(cosine(pxl, pyl , pzl));
	 truemuon_truephi_CCCOH_GENIE->Fill(Getphi(pxl, pyl, pzl));
	 trueNh_CCCOH_GENIE->Fill(Nh(nneutron, nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueNvish_CCCOH_GENIE->Fill(Nvish(nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueW_CCCOH_GENIE->Fill(InvMass(q2, omega));
	 pT_CCCOH_GENIE->Fill(PTmiss);/// assuming 1muon + protons int he final state
	 EnuCCQE_CCCOH_GENIE->Fill(GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 EnuCalo_CCCOH_GENIE->Fill(GetEcalomiss(Esum, PTmiss, 0));/// assuming 1muon + protons int eh final state, Ar40 (np=0)
	 EnuRes_CCCOH_GENIE->Fill(GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 //// filling resolution histograms in all interaction types
	 Resolution_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 Resolution_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0));
	 Resolution_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 hprof_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu),1);
	 hprof_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0),1);
	 hprof_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)),1);
       }

       else{
	 nother++;

	///// true kinematics /////
	 truemuon_truemom_other_GENIE->Fill(sqrt(pow(pxl,2)+ pow(pyl,2)+pow(pzl,2)));
	 truemuon_truecostheta_other_GENIE->Fill(cosine(pxl, pyl , pzl));
	 truemuon_truephi_other_GENIE->Fill(Getphi(pxl, pyl, pzl));
	 trueNh_other_GENIE->Fill(Nh(nneutron, nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueNvish_other_GENIE->Fill(Nvish(nnegpion, nnpion, npospion, nproton, nkaon, neta, nrho));
	 trueW_other_GENIE->Fill(InvMass(q2, omega));
	 pT_other_GENIE->Fill(PTmiss);/// assuming 1muon + protons int he final state
	 EnuCCQE_other_GENIE->Fill(GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 EnuCalo_other_GENIE->Fill(GetEcalomiss(Esum, PTmiss, 0));/// assuming 1muon + protons int eh final state, Ar40 (np=0)
	 EnuRes_other_GENIE->Fill(GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 /////// filling resolution histograms in all interaction types
	 Resolution_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu));
	 Resolution_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0));
	 Resolution_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)));

	 hprof_EnuCCQE_GENIE->Fill(EvRF,EvRF - GetEnuCCQE(emu, cosine(pxl, pyl , pzl), pmu),1);
	 hprof_EnuCalo_GENIE->Fill(EvRF,EvRF - GetEcalomiss(Esum, PTmiss, 0),1);
	 hprof_EnuRes_GENIE->Fill(EvRF,EvRF - GetEnuRes(emu, cosine(pxl, pyl , pzl)),1);
       }
      
   } /// END LOOP OF ENTRIES ///////


   ///// write few information in the txt file, and write the ROOT file before closing
   
   anaGENIEuB<<" number of CC :  "<<totentries<<endl;
   //std::cout<<"hhhh "<< cout<<stdl;
   anaGENIEuB<<" number of CCQE events in CC :  "<<nCCQE<<endl;
   anaGENIEuB<<" number of CCMEC events in CC :  "<<nCCMEC<<endl;
   anaGENIEuB<<" number of CCRes events in CC :  "<<nCCRes<<endl;
   anaGENIEuB<<" number of CCDIS events in CC :  "<<nCCDIS<<endl;
   anaGENIEuB<<" number of CCCOH events in CC :  "<<nCCCOH<<endl;
   anaGENIEuB<<" number of CCother events in CC :  "<<nother<<endl;

   anaGENIEuB<< "Output file written" << std::endl;

   outGENIEuB->cd();
   outGENIEuB->Write();

   ////////////////////////////////////////////////////////// DRAWING //////////////////////////

   /////// preliminary drawing style ////

   gStyle->SetOptStat(0000);
   gStyle->SetOptFit(1111);
   gStyle->SetOptTitle(0);
   gStyle->SetPadColor(kWhite);
   gStyle->SetStatY(0.90);
   gStyle->SetStatX(0.90);
   gStyle->SetStatW(0.15);
   gStyle->SetStatH(0.2);
   gStyle->SetLabelSize(0.04,"X");
   gStyle->SetLabelFont(62,"X");
   gStyle->SetTitleSize(0.04,"X");
   gStyle->SetTitleFont(62,"X");
   gStyle->SetTitleOffset(0.85,"X");

  //  gStyle->SetLabelOffset(0.015,"Y");
   gStyle->SetLabelSize(0.03,"Y");
   gStyle->SetLabelFont(62,"Y");
   gStyle->SetTitleSize(0.04,"Y");
   gStyle->SetTitleFont(62,"Y");
   gStyle->SetTitleOffset(1.3,"Y");
   gStyle->SetTitleX(0.22);
   gStyle->SetTitleY(0.98);
   gStyle->SetTitleSize(0.04,"t");
   gStyle->SetTitleBorderSize(0);
   gStyle->SetCanvasBorderSize(0);

   //////////////////// PLOTS //////
   //// each plot goes in a canvas
   /// most 1-D histograms are grouped into TStack
   /// each plot is stored as pdf, eps png and also in .C (sometimes helps when one cannot re-run the entire code but needs to change any style)
   /// some legends are misplaced, need to check one-by-one
   
  TCanvas *c1 = new TCanvas("c1", "c1", 900, 900);
  
  truemuon_truemom_CCQE_GENIE-> SetFillColor(kRed);
  truemuon_truemom_CCMEC_GENIE-> SetFillColor(kGreen);
  truemuon_truemom_CCRES_GENIE-> SetFillColor(kYellow);
  truemuon_truemom_CCDIS_GENIE-> SetFillColor(kBlue);
  truemuon_truemom_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *truemuon_truemom_GENIE = new THStack("truemuon_truemom_GENIE","");
  truemuon_truemom_GENIE-> Add(truemuon_truemom_CCQE_GENIE);
  truemuon_truemom_GENIE-> Add(truemuon_truemom_CCMEC_GENIE);
  truemuon_truemom_GENIE-> Add(truemuon_truemom_CCRES_GENIE);
  truemuon_truemom_GENIE-> Add(truemuon_truemom_CCDIS_GENIE);
  truemuon_truemom_GENIE-> Add(truemuon_truemom_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  truemuon_truemom_GENIE-> Draw();
  truemuon_truemom_GENIE->GetXaxis()->SetTitle("p_{#mu} [GeV/c]");
  truemuon_truemom_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l1 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l1 -> AddEntry(truemuon_truemom_CCQE_GENIE, "CCQE", "f");
  l1 -> AddEntry(truemuon_truemom_CCMEC_GENIE, "CCMEC", "f");
  l1 -> AddEntry(truemuon_truemom_CCRES_GENIE, "CCRES", "f");
  l1 -> AddEntry(truemuon_truemom_CCCOH_GENIE, "CC-Coh", "f");
  l1 -> AddEntry(truemuon_truemom_CCDIS_GENIE, "CCDIS", "f");
  l1 -> Draw();

  c1->Update();
  c1->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truemom_GENIE.pdf");
  c1->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truemom_GENIE.eps");
  c1->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truemom_GENIE.png");
  c1->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truemom_GENIE.C");
  
  TCanvas *c2 = new TCanvas("c2", "c2", 900, 900);
  
  truemuon_truecostheta_CCQE_GENIE-> SetFillColor(kRed);
  truemuon_truecostheta_CCMEC_GENIE-> SetFillColor(kGreen);
  truemuon_truecostheta_CCRES_GENIE-> SetFillColor(kYellow);
  truemuon_truecostheta_CCDIS_GENIE-> SetFillColor(kBlue);
  truemuon_truecostheta_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *truemuon_truecostheta_GENIE = new THStack("truemuon_truecostheta_GENIE","");
  truemuon_truecostheta_GENIE-> Add(truemuon_truecostheta_CCQE_GENIE);
  truemuon_truecostheta_GENIE-> Add(truemuon_truecostheta_CCMEC_GENIE);
  truemuon_truecostheta_GENIE-> Add(truemuon_truecostheta_CCRES_GENIE);
  truemuon_truecostheta_GENIE-> Add(truemuon_truecostheta_CCDIS_GENIE);
  truemuon_truecostheta_GENIE-> Add(truemuon_truecostheta_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  truemuon_truecostheta_GENIE-> Draw();
  truemuon_truecostheta_GENIE->GetXaxis()->SetTitle("cos #theta_{#mu}");
  truemuon_truecostheta_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l2 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l2 -> AddEntry(truemuon_truecostheta_CCQE_GENIE, "CCQE", "f");
  l2 -> AddEntry(truemuon_truecostheta_CCMEC_GENIE, "CCMEC", "f");
  l2 -> AddEntry(truemuon_truecostheta_CCRES_GENIE, "CCRES", "f");
  l2 -> AddEntry(truemuon_truecostheta_CCCOH_GENIE, "CC-Coh", "f");
  l2 -> AddEntry(truemuon_truecostheta_CCDIS_GENIE, "CCDIS", "f");
  l2 -> Draw();

  c2->Update();
  c2->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truecostheta_GENIE.pdf");
  c2->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truecostheta_GENIE.eps");
  c2->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truecostheta_GENIE.png");
  c2->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truecostheta_GENIE.C");

  TCanvas *c3 = new TCanvas("c3", "c3", 900, 900);
  
  truemuon_truephi_CCQE_GENIE-> SetFillColor(kRed);
  truemuon_truephi_CCMEC_GENIE-> SetFillColor(kGreen);
  truemuon_truephi_CCRES_GENIE-> SetFillColor(kYellow);
  truemuon_truephi_CCDIS_GENIE-> SetFillColor(kBlue);
  truemuon_truephi_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *truemuon_truephi_GENIE = new THStack("truemuon_truephi_GENIE","");
  truemuon_truephi_GENIE-> Add(truemuon_truephi_CCQE_GENIE);
  truemuon_truephi_GENIE-> Add(truemuon_truephi_CCMEC_GENIE);
  truemuon_truephi_GENIE-> Add(truemuon_truephi_CCRES_GENIE);
  truemuon_truephi_GENIE-> Add(truemuon_truephi_CCDIS_GENIE);
  truemuon_truephi_GENIE-> Add(truemuon_truephi_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  truemuon_truephi_GENIE-> Draw();
  truemuon_truephi_GENIE->GetXaxis()->SetTitle("#phi_{#mu}");
  truemuon_truephi_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l3 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l3 -> AddEntry(truemuon_truephi_CCQE_GENIE, "CCQE", "f");
  l3 -> AddEntry(truemuon_truephi_CCMEC_GENIE, "CCMEC", "f");
  l3 -> AddEntry(truemuon_truephi_CCRES_GENIE, "CCRES", "f");
  l3 -> AddEntry(truemuon_truephi_CCCOH_GENIE, "CC-Coh", "f");
  l3 -> AddEntry(truemuon_truephi_CCDIS_GENIE, "CCDIS", "f");
  l3 -> Draw();

  c3->Update();
  c3->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truephi_GENIE.pdf");
  c3->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truephi_GENIE.eps");
  c3->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truephi_GENIE.png");
  c3->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/truemuon_truephi_GENIE.C");

  TCanvas *c4 = new TCanvas("c4", "c4", 900, 900);
  
  trueNh_CCQE_GENIE-> SetFillColor(kRed);
  trueNh_CCMEC_GENIE-> SetFillColor(kGreen);
  trueNh_CCRES_GENIE-> SetFillColor(kYellow);
  trueNh_CCDIS_GENIE-> SetFillColor(kBlue);
  trueNh_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *trueNh_GENIE = new THStack("trueNh_GENIE","");
  trueNh_GENIE-> Add(trueNh_CCQE_GENIE);
  trueNh_GENIE-> Add(trueNh_CCMEC_GENIE);
  trueNh_GENIE-> Add(trueNh_CCRES_GENIE);
  trueNh_GENIE-> Add(trueNh_CCDIS_GENIE);
  trueNh_GENIE-> Add(trueNh_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  trueNh_GENIE-> Draw();
  trueNh_GENIE->GetXaxis()->SetTitle("number of hadrons in the final state");
  trueNh_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l4 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l4 -> AddEntry(trueNh_CCQE_GENIE, "CCQE", "f");
  l4 -> AddEntry(trueNh_CCMEC_GENIE, "CCMEC", "f");
  l4 -> AddEntry(trueNh_CCRES_GENIE, "CCRES", "f");
  l4 -> AddEntry(trueNh_CCCOH_GENIE, "CC-Coh", "f");
  l4 -> AddEntry(trueNh_CCDIS_GENIE, "CCDIS", "f");
  l4 -> Draw();

  c4->Update();
  c4->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueNh_GENIE.pdf");
  c4->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueNh_GENIE.eps");
  c4->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueNh_GENIE.png");
  c4->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueNh_GENIE.C");

  TCanvas *c5 = new TCanvas("c5", "c5", 900, 900);
  
  trueNvish_CCQE_GENIE-> SetFillColor(kRed);
  trueNvish_CCMEC_GENIE-> SetFillColor(kGreen);
  trueNvish_CCRES_GENIE-> SetFillColor(kYellow);
  trueNvish_CCDIS_GENIE-> SetFillColor(kBlue);
  trueNvish_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *trueNvish_GENIE = new THStack("trueNvish_GENIE","");
  trueNvish_GENIE-> Add(trueNvish_CCQE_GENIE);
  trueNvish_GENIE-> Add(trueNvish_CCMEC_GENIE);
  trueNvish_GENIE-> Add(trueNvish_CCRES_GENIE);
  trueNvish_GENIE-> Add(trueNvish_CCDIS_GENIE);
  trueNvish_GENIE-> Add(trueNvish_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  trueNvish_GENIE-> Draw();
  trueNvish_GENIE->GetXaxis()->SetTitle("number of hadrons in the final state (without neutrons)");
  trueNvish_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l5 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l5 -> AddEntry(trueNvish_CCQE_GENIE, "CCQE", "f");
  l5 -> AddEntry(trueNvish_CCMEC_GENIE, "CCMEC", "f");
  l5 -> AddEntry(trueNvish_CCRES_GENIE, "CCRES", "f");
  l5 -> AddEntry(trueNvish_CCCOH_GENIE, "CC-Coh", "f");
  l5 -> AddEntry(trueNvish_CCDIS_GENIE, "CCDIS", "f");
  l5 -> Draw();

  c5->Update();
  c5->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueNvish_GENIE.pdf");
  c5->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueNvish_GENIE.eps");
  c5->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueNvish_GENIE.png");
  c5->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueNvish_GENIE.C");

  TCanvas *c6 = new TCanvas("c6", "c6", 900, 900);
  
  trueW_CCQE_GENIE-> SetFillColor(kRed);
  trueW_CCMEC_GENIE-> SetFillColor(kGreen);
  trueW_CCRES_GENIE-> SetFillColor(kYellow);
  trueW_CCDIS_GENIE-> SetFillColor(kBlue);
  trueW_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *trueW_GENIE = new THStack("trueW_GENIE","");
  trueW_GENIE-> Add(trueW_CCQE_GENIE);
  trueW_GENIE-> Add(trueW_CCMEC_GENIE);
  trueW_GENIE-> Add(trueW_CCRES_GENIE);
  trueW_GENIE-> Add(trueW_CCDIS_GENIE);
  trueW_GENIE-> Add(trueW_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  trueW_GENIE-> Draw();
  trueW_GENIE->GetXaxis()->SetTitle("invariant mass");
  trueW_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l6 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l6 -> AddEntry(trueW_CCQE_GENIE, "CCQE", "f");
  l6 -> AddEntry(trueW_CCMEC_GENIE, "CCMEC", "f");
  l6 -> AddEntry(trueW_CCRES_GENIE, "CCRES", "f");
  l6 -> AddEntry(trueW_CCCOH_GENIE, "CC-Coh", "f");
  l6 -> AddEntry(trueW_CCDIS_GENIE, "CCDIS", "f");
  l6 -> Draw();

  c6->Update();
  c6->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueW_GENIE.pdf");
  c6->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueW_GENIE.eps");
  c6->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueW_GENIE.png");
  c6->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/trueW_GENIE.C");

  TCanvas *c7 = new TCanvas("c7", "c7", 900, 900);
  
  pT_CCQE_GENIE-> SetFillColor(kRed);
  pT_CCMEC_GENIE-> SetFillColor(kGreen);
  pT_CCRES_GENIE-> SetFillColor(kYellow);
  pT_CCDIS_GENIE-> SetFillColor(kBlue);
  pT_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *pT_GENIE = new THStack("pT_GENIE","");
  pT_GENIE-> Add(pT_CCQE_GENIE);
  pT_GENIE-> Add(pT_CCMEC_GENIE);
  pT_GENIE-> Add(pT_CCRES_GENIE);
  pT_GENIE-> Add(pT_CCDIS_GENIE);
  pT_GENIE-> Add(pT_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  pT_GENIE-> Draw();
  pT_GENIE->GetXaxis()->SetTitle("missing momentum transfer [GeV/c]");
  pT_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l7 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l7 -> AddEntry(trueW_CCQE_GENIE, "CCQE", "f");
  l7 -> AddEntry(trueW_CCMEC_GENIE, "CCMEC", "f");
  l7 -> AddEntry(trueW_CCRES_GENIE, "CCRES", "f");
  l7 -> AddEntry(trueW_CCCOH_GENIE, "CC-Coh", "f");
  l7 -> AddEntry(trueW_CCDIS_GENIE, "CCDIS", "f");
  l7 -> Draw();

  c7->Update();
  c7->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/pT_GENIE.pdf");
  c7->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/pT_GENIE.eps");
  c7->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/pT_GENIE.png");
  c7->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/pT_GENIE.C");
  
  TCanvas *c8 = new TCanvas("c8", "c8", 900, 900);
  
  EnuCCQE_CCQE_GENIE-> SetFillColor(kRed);
  EnuCCQE_CCMEC_GENIE-> SetFillColor(kGreen);
  EnuCCQE_CCRES_GENIE-> SetFillColor(kYellow);
  EnuCCQE_CCDIS_GENIE-> SetFillColor(kBlue);
  EnuCCQE_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *EnuCCQE_GENIE = new THStack("EnuCCQE_GENIE","");
  EnuCCQE_GENIE-> Add(EnuCCQE_CCQE_GENIE);
  EnuCCQE_GENIE-> Add(EnuCCQE_CCMEC_GENIE);
  EnuCCQE_GENIE-> Add(EnuCCQE_CCRES_GENIE);
  EnuCCQE_GENIE-> Add(EnuCCQE_CCDIS_GENIE);
  EnuCCQE_GENIE-> Add(EnuCCQE_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  EnuCCQE_GENIE-> Draw();
  EnuCCQE_GENIE->GetXaxis()->SetTitle("reconstructed neutrino energy in CCQE aproach [GeV/c]");
  EnuCCQE_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l8 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l8 -> AddEntry(EnuCCQE_CCQE_GENIE, "CCQE", "f");
  l8 -> AddEntry(EnuCCQE_CCMEC_GENIE, "CCMEC", "f");
  l8 -> AddEntry(EnuCCQE_CCRES_GENIE, "CCRES", "f");
  l8 -> AddEntry(EnuCCQE_CCCOH_GENIE, "CC-Coh", "f");
  l8 -> AddEntry(EnuCCQE_CCDIS_GENIE, "CCDIS", "f");
  l8 -> Draw();

  c8->Update();
  c8->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuCCQE_GENIE.pdf");
  c8->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuCCQE_GENIE.eps");
  c8->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuCCQE_GENIE.png");
  c8->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuCCQE_GENIE.C");

  TCanvas *c9 = new TCanvas("c9", "c9", 900, 900);
  
  EnuCalo_CCQE_GENIE-> SetFillColor(kRed);
  EnuCalo_CCMEC_GENIE-> SetFillColor(kGreen);
  EnuCalo_CCRES_GENIE-> SetFillColor(kYellow);
  EnuCalo_CCDIS_GENIE-> SetFillColor(kBlue);
  EnuCalo_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *EnuCalo_GENIE = new THStack("EnuCalo_GENIE","");
  EnuCalo_GENIE-> Add(EnuCalo_CCQE_GENIE);
  EnuCalo_GENIE-> Add(EnuCalo_CCMEC_GENIE);
  EnuCalo_GENIE-> Add(EnuCalo_CCRES_GENIE);
  EnuCalo_GENIE-> Add(EnuCalo_CCDIS_GENIE);
  EnuCalo_GENIE-> Add(EnuCalo_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  EnuCalo_GENIE-> Draw();
  EnuCalo_GENIE->GetXaxis()->SetTitle("calorimetric reconstructed neutrino energy [GeV/c]");
  EnuCalo_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l9 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l9 -> AddEntry(EnuCalo_CCQE_GENIE, "CCQE", "f");
  l9 -> AddEntry(EnuCalo_CCMEC_GENIE, "CCMEC", "f");
  l9 -> AddEntry(EnuCalo_CCRES_GENIE, "CCRES", "f");
  l9 -> AddEntry(EnuCalo_CCCOH_GENIE, "CC-Coh", "f");
  l9 -> AddEntry(EnuCalo_CCDIS_GENIE, "CCDIS", "f");
  l9 -> Draw();

  c9->Update();
  c9->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuCalo_GENIE.pdf");
  c9->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuCalo_GENIE.eps");
  c9->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuCalo_GENIE.png");
  c9->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuCalo_GENIE.C");

  TCanvas *c10 = new TCanvas("c10", "c10", 900, 900);
  
  EnuRes_CCQE_GENIE-> SetFillColor(kRed);
  EnuRes_CCMEC_GENIE-> SetFillColor(kGreen);
  EnuRes_CCRES_GENIE-> SetFillColor(kYellow);
  EnuRes_CCDIS_GENIE-> SetFillColor(kBlue);
  EnuRes_CCCOH_GENIE-> SetFillColor(kMagenta);
 
  THStack *EnuRes_GENIE = new THStack("EnuRes_GENIE","");
  EnuRes_GENIE-> Add(EnuRes_CCQE_GENIE);
  EnuRes_GENIE-> Add(EnuRes_CCMEC_GENIE);
  EnuRes_GENIE-> Add(EnuRes_CCRES_GENIE);
  EnuRes_GENIE-> Add(EnuRes_CCDIS_GENIE);
  EnuRes_GENIE-> Add(EnuRes_CCCOH_GENIE); 
  //truemuon_truemom_GENIE-> SetMaximum(100);  
  EnuRes_GENIE-> Draw();
  EnuRes_GENIE->GetXaxis()->SetTitle("reconstructed neutrino energy in resonant approach [GeV/c]");
  EnuRes_GENIE->GetYaxis()->SetTitle("number of events");

  TLegend *l10 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l10 -> AddEntry(EnuRes_CCQE_GENIE, "CCQE", "f");
  l10 -> AddEntry(EnuRes_CCMEC_GENIE, "CCMEC", "f");
  l10 -> AddEntry(EnuRes_CCRES_GENIE, "CCRES", "f");
  l10 -> AddEntry(EnuRes_CCCOH_GENIE, "CC-Coh", "f");
  l10 -> AddEntry(EnuRes_CCDIS_GENIE, "CCDIS", "f");
  l10 -> Draw();

  c10->Update();
  c10->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuRes_GENIE.pdf");
  c10->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuRes_GENIE.eps");
  c10->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuRes_GENIE.png");
  c10->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/EnuRes_GENIE.C");  

  /////////////// 2-D plots for the resolutions in reconstructed neutrino energy
  
  TCanvas *c11 = new TCanvas("c11", "c11", 900, 900);
  gStyle->SetOptStat(kFALSE);

  Resolution_EnuCCQE_GENIE->GetXaxis()->SetTitle("true neutrino energy [GeV]");
  Resolution_EnuCCQE_GENIE->GetYaxis()->SetTitle("(true - reconstructed) neutrino energy [GeV]");
  Resolution_EnuCCQE_GENIE->Draw("colz");

  c11->Update();
  c11->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuCCQE_GENIE.pdf");
  c11->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuCCQE_GENIE.eps");
  c11->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuCCQE_GENIE.png");
  c11->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuCCQE_GENIE.C");  

  TCanvas *c12 = new TCanvas("c12", "c12", 900, 900);
  gStyle->SetOptStat(kFALSE);

  Resolution_EnuCalo_GENIE->GetXaxis()->SetTitle("true neutrino energy [GeV]");
  Resolution_EnuCalo_GENIE->GetYaxis()->SetTitle("(true - reconstructed) neutrino energy [GeV]");
  Resolution_EnuCalo_GENIE->Draw("colz");

  c12->Update();
  c12->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuCalo_GENIE.pdf");
  c12->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuCalo_GENIE.eps");
  c12->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuCalo_GENIE.png");
  c12->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuCalo_GENIE.C");  
  
  TCanvas *c13 = new TCanvas("c13", "c13", 900, 900);
  gStyle->SetOptStat(kFALSE);

  Resolution_EnuRes_GENIE->GetXaxis()->SetTitle("true neutrino energy [GeV]");
  Resolution_EnuRes_GENIE->GetYaxis()->SetTitle("(true - reconstructed) neutrino energy [GeV]");
  Resolution_EnuRes_GENIE->Draw("colz");

  c13->Update();
  c13->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuRes_GENIE.pdf");
  c13->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuRes_GENIE.eps");
  c13->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuRes_GENIE.png");
  c13->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/Resolution_EnuRes_GENIE.C");  

  ///// profile plots
  
  TCanvas *c14 = new TCanvas("c14","",900, 900); 

  c14->SetGrid();

  hprof_EnuCCQE_GENIE->SetTitle("");
  hprof_EnuCCQE_GENIE->GetXaxis()->SetTitle("true neutrino energy [GeV]");
  hprof_EnuCCQE_GENIE->GetYaxis()->SetTitle("(true - reconstructed) neutrino energy [GeV]");
  hprof_EnuCCQE_GENIE->SetLineColor(kRed);
  hprof_EnuCCQE_GENIE->SetLineWidth(2);
  hprof_EnuCCQE_GENIE->SetMarkerColor(kRed);
  hprof_EnuCCQE_GENIE->SetMarkerStyle(20);

  hprof_EnuCCQE_GENIE->GetYaxis()->SetLimits(-0.6, 0.6);
  hprof_EnuCCQE_GENIE->GetYaxis()->SetRangeUser(-0.6, 0.6);
  hprof_EnuCCQE_GENIE->Draw("e1");

  hprof_EnuRes_GENIE->SetLineColor(kGreen);
  hprof_EnuRes_GENIE->SetLineWidth(2);
  hprof_EnuRes_GENIE->SetMarkerColor(kGreen);
  hprof_EnuRes_GENIE->SetMarkerStyle(20);
  hprof_EnuRes_GENIE->Draw("e1same");

  hprof_EnuCalo_GENIE->SetLineColor(kBlack);
  hprof_EnuCalo_GENIE->SetLineWidth(2);
  hprof_EnuCalo_GENIE->SetMarkerColor(kBlack);
  hprof_EnuCalo_GENIE->SetMarkerStyle(20);
  hprof_EnuCalo_GENIE->Draw("e1same");  

  TLegend *l14 = new TLegend(0.50, 0.25, 0.9, 0.1);
  //l14 -> SetNColumns(2);
  l14 -> AddEntry(hprof_EnuCCQE_GENIE, "CCQE approach", "l");
  l14 -> AddEntry(hprof_EnuCalo_GENIE, "Calorimetry approach", "l");
  l14 -> AddEntry(hprof_EnuRes_GENIE, "Resonant approach", "l");
  l14 -> Draw();

  c14->Update();
  c14->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/TProfileResol_Enu_GENIE.pdf");
  c14->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/TProfileResol_Enu_GENIE.eps");
  c14->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/TProfileResol_Enu_GENIE.png");
  c14->Print("/Users/castillofernr/Documents/SBN/GENIE/microboonetunning//output/plots/TProfileResol_Enu_GENIE.C");

}
