/**
* microB_GiBUU_gvs_xsec.C
*
* This macro extracts the MicroBOONE flux-veraged GiBUU 
* cross-section from muon neutrino interaction with Argon.
* It will be used to compare GiBUU versions 2019 and 2021
*
*
* Change in header file (microB_GiBUU_gvs_xsec.h) which 
* ROOT file you want: from simulation with 
* GiBUU 2019 or GiBUU 2021
*
**/

#define microB_GiBUU_gvs_xsec_cxx
#include "microB_GiBUU_gvs_xsec.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <iostream>
#include <TROOT.h>
#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <THStack.h>
#include <TF1.h>
#include <TMath.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <TDirectory.h>
#include <TAxis.h>
#include <iostream>
#include <stdio.h>

using namespace std;

//*********************************************************Defining_Mass**************************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//


#define PI 3.14159265
#define mumass 0.1056583755 // GeV/c2
#define protonmass 0.93827208816 //GeV/c2
#define pionmass 0.1349768  //GeV/c2
#define cpionmass 0.1395703  //GeV/c2


/////////////////////////////// defining output files. one ROOT file (TFile format) and many text file (txt file) ///////////////////////////

ofstream microB_CC_GiBUU;
ofstream microB_CCQE_GiBUU;
ofstream microB_CCRES_GiBUU;
ofstream microB_CCMEC_GiBUU;
ofstream microB_CCDIS_GiBUU;
ofstream microB_other_GiBUU;


///////////////////////////// ROOT file ///////////////////////////////////////////////////////////////////
TFile *out_microB_xsec_GiBUU;


///// 1-D histograms, TH1D ///////////////////////////////

// true neutrino energy
TH1D *trueEnu_CC_GiBUU;



// true neutrino energy
TH1D *trueEnu_CCQE_GiBUU;
TH1D *trueEnu_CCMEC_GiBUU;
TH1D *trueEnu_CCRES_GiBUU;
TH1D *trueEnu_CCDIS_GiBUU;
TH1D *trueEnu_other_GiBUU;



////////////////////////////////////////////////////////////////////////  SOME COUNTERS //////////////////////////////////////////////////////////////////
int nCCQE=0;
int nCCRES=0;
int nCCMEC=0;
int nCCDIS=0;
int nother =0;/// just for debbuging
int ntotal=0;


void microB_GiBUU_gvs_xsec::Loop()
{	
//   In a ROOT session, you can do:
//      root> .L microB_GiBUU_gvs_xsec.C
//      root> microB_GiBUU_gvs_xsec t
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

   bool numuCC = false;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
//////////////// ROOt File ///////////////////////////////////////////////////////////////////

out_microB_xsec_GiBUU = new TFile("/home/gstenico/Desktop/SBND_GiBUU/GiBUU-GENIE/GiBUU_2021_2019/out_microB_xsec_GiBUU_2021.root","RECREATE");
   
//////////////// output files location and histogram definitions

microB_CC_GiBUU.open("/home/gstenico/Desktop/SBND_GiBUU/GiBUU-GENIE/GiBUU_2021_2019/microB_CC_GiBUU_2021.txt");
microB_CCQE_GiBUU.open("/home/gstenico/Desktop/SBND_GiBUU/GiBUU-GENIE/GiBUU_2021_2019/microB_CCQE_GiBUU_2021.txt");
microB_CCRES_GiBUU.open("/home/gstenico/Desktop/SBND_GiBUU/GiBUU-GENIE/GiBUU_2021_2019/microB_CCRES_GiBUU_2021.txt");
microB_CCMEC_GiBUU.open("/home/gstenico/Desktop/SBND_GiBUU/GiBUU-GENIE/GiBUU_2021_2019/microB_CCMEC_GiBUU_2021.txt");
microB_CCDIS_GiBUU.open("/home/gstenico/Desktop/SBND_GiBUU/GiBUU-GENIE/GiBUU_2021_2019/microB_CCDIS_GiBUU_2021.txt");
microB_other_GiBUU.open("/home/gstenico/Desktop/SBND_GiBUU/GiBUU-GENIE/GiBUU_2021_2019/microB_other_GiBUU_2021.txt");



//***********************************************True_neutrino_energy_GiBUU***********************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//


  const int NBINS = 10;
  double edges[NBINS + 1] = {0.2, 0.54, 0.705, 0.805, 0.92, 1.05, 1.2, 1.375, 1.57, 2.05, 4.0};
   // Bin 1 corresponds to range [0.0, 0.2]
   // Bin 2 corresponds to range [0.2, 0.3] etc...
   
trueEnu_CC_GiBUU= new TH1D("TrueEnu_CC_GiBUU", "TrueEnu_CC_GiBUU", NBINS, edges);
trueEnu_CCQE_GiBUU= new TH1D("TrueEnu_CCQE_GiBUU", "TrueEnu_CCQE_GiBUU", NBINS, edges);
trueEnu_CCRES_GiBUU= new TH1D("TrueEnu_CCRES_GiBUU", "TrueEnu_CCRES_GiBUU", NBINS, edges);
trueEnu_CCMEC_GiBUU= new TH1D("TrueEnu_CCMEC_GiBUU", "TrueEnu_CCMEC_GiBUU", NBINS, edges);
trueEnu_CCDIS_GiBUU= new TH1D("TrueEnu_CCDIS_GiBUU", "TrueEnu_CCDIS_GiBUU", NBINS, edges);
trueEnu_other_GiBUU= new TH1D("TrueEnu_other_GiBUU", "TrueEnu_other_GiBUU", NBINS, edges);


/*trueEnu_CC_GiBUU= new TH1D("TrueEnu_CC_GiBUU", "TrueEnu_CC_GiBUU", 60,0,3);
trueEnu_CCQE_GiBUU= new TH1D("TrueEnu_CCQE_GiBUU", "TrueEnu_CCQE_GiBUU", 60,0,3);
trueEnu_CCRES_GiBUU= new TH1D("TrueEnu_CCRES_GiBUU", "TrueEnu_CCRES_GiBUU", 60,0,3);
trueEnu_CCMEC_GiBUU= new TH1D("TrueEnu_CCMEC_GiBUU", "TrueEnu_CCMEC_GiBUU", 60,0,3);
trueEnu_CCDIS_GiBUU= new TH1D("TrueEnu_CCDIS_GiBUU", "TrueEnu_CCDIS_GiBUU", 60,0,3);
trueEnu_other_GiBUU= new TH1D("TrueEnu_other_GiBUU", "TrueEnu_other_GiBUU", 60,0,3);*/



//********************************************Start_of_the_loop_for_events*********************************************************************//   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue
      //std::cout<<"Event is"<<jentry<<std::endl;
      //std::cout<<"energy of lepton is"<<lepIn_E<<std::endl;
      
 //total_weight=total_weight+weight;     
//***********************************************************************************************************************************************//
//****************************************Applicable_for_the_microboone_formulae****************************************************************//
//***********************************************************************************************************************************************//

      double pmu = sqrt(lepOut_Px*lepOut_Px + lepOut_Py*lepOut_Py + lepOut_Pz*lepOut_Pz); /// true muon (absolute) momentum

      if(lepIn_E>0 && pmu >0) numuCC = true;/// this is the condition to select a numu CC event in true variables
      if (!numuCC) continue;
  //    if(lepIn_E>3) continue;
         
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
      double deltax =lepOut_Px;/// muon px (momentum in x)
      double deltay =lepOut_Py; // muon py (momentum in y)
      double Esum =0; /// sum of total kinetic energies
      double emu = sqrt(mumass*mumass + pmu*pmu); /// true muon energy
      double protonmom =0; //// momentum of the proton
      double pionmom = 0.;
      double Epionplus = 0.;
      double Epionneg = 0.;
      double Epion = 0.;  
      

//***********************************************************************************************************************************************//
//************************************************Imported_Code_from_Raquel***********************************************************************//
//************************************************Using_Microboone_Formulae********************************************************************//

     for (int ki=0;ki<barcode->size();ki++)
   {
     if ((*barcode)[ki] == 2212) {/// we look at each particle type using their PDG codes (https://pdg.lbl.gov/2007/reviews/montecarlorpp.pdf)
	  protonmom = sqrt((*Px)[ki]*(*Px)[ki] + (*Py)[ki]*(*Py)[ki] + (*Pz)[ki]*(*Pz)[ki]);
	  if(protonmom < 0.256) continue; //// ************************** proton detection threshold KE> 35 MeV/c ***************************
	  nproton++;
	  deltax= deltax + (*Px)[ki]; /// adding protons px
	  deltay= deltay + (*Py)[ki]; // addin protons py
	  //protonmom = sqrt((*Px)[ki]*(*Px)[ki] + (*Py)[ki]*(*Py)[ki] + (*Pz)[ki]*(*Pz)[ki]);
	  Esum= Esum + protonmom*protonmom/(2*protonmass); ///summatory of protons kinetic energy
	  protonmom =0;
	}
	else if ((*barcode)[ki] == 2112) nneutron++;
	else if ((*barcode)[ki] == 211){
	  pionmom =sqrt((*Px)[ki]*(*Px)[ki] + (*Py)[ki]*(*Py)[ki] + (*Pz)[ki]*(*Pz)[ki]);
	  if(pionmom < 0.053) continue; //// ************************** proton detection threshold KE> 10 MeV/c *********************************//
	  Epionplus = Epionplus + sqrt(pionmass*pionmass + pionmom*pionmom); /// summatory of pions energy
	  pionmom =0;
	  npospion++;
	}
	else if ((*barcode)[ki] == -211) {
	  pionmom = sqrt((*Px)[ki]*(*Px)[ki] + (*Py)[ki]*(*Py)[ki] + (*Pz)[ki]*(*Pz)[ki]);
	  if(pionmom < 0.053) continue; //// ************************** proton detection threshold KE> 10 MeV/c *********************************//
	  Epionneg = Epionneg + sqrt(pionmass*pionmass + pionmom*pionmom); /// summatory of pions energy
	  pionmom =0;
	  nnegpion++;
	}
	else if ((*barcode)[ki] == 111) nnpion++;
	else if (abs((*barcode)[ki]) == 321) nkaon++;
	else if (abs((*barcode)[ki]) == 211) neta++;
	else if (abs((*barcode)[ki]) == 213) nrho++;
   }//end of for loop

      Epion = Epionneg + Epionplus;
    
      //////////  end loop final state hadrons ///////////////

       double PTmiss = sqrt(deltax*deltax + deltay*deltay); /// missing transverse momentum (considering all protons in the final states)
       Esum= Esum + emu; /// total energy of the muon + protons kinetic energy

 
 ////////////////////////////////////////////////// All numu CC ///////////////////////////////////////////////////////////////// 
 
       // CCQE
      if (evType==1)
      {
        trueEnu_CCQE_GiBUU->Fill(lepIn_E,weight);

      }
      
      // CCRES
     else if ((evType>=2)&&(evType<=31))
      {
        trueEnu_CCRES_GiBUU->Fill(lepIn_E,weight);

      }
      
      // CCDIS
     else if ((evType==32)||(evType==33)||(evType==34)||(evType==37))
      {
        trueEnu_CCDIS_GiBUU->Fill(lepIn_E,weight);
	
      }
 
      // CCMEC
     else if ((evType==35)||(evType==36))
      {
         trueEnu_CCMEC_GiBUU->Fill(lepIn_E,weight);

	
      }

      // other
    else if ((evType>37)||(evType<1))
      {
        trueEnu_other_GiBUU->Fill(lepIn_E,weight);

	 }

       //total
       trueEnu_CC_GiBUU->Fill(lepIn_E,weight);
       ntotal++;

     }
     
     
   for (int i=1;i<trueEnu_CC_GiBUU->GetSize();i++) {
   microB_CC_GiBUU << trueEnu_CC_GiBUU->GetXaxis()->GetBinCenter(i) << " " << trueEnu_CC_GiBUU->GetBinContent(i) <<endl;
   microB_CCQE_GiBUU << trueEnu_CCQE_GiBUU->GetXaxis()->GetBinCenter(i) << " " << trueEnu_CCQE_GiBUU->GetBinContent(i) <<endl;
   microB_CCRES_GiBUU << trueEnu_CCRES_GiBUU->GetXaxis()->GetBinCenter(i) << " " << trueEnu_CCRES_GiBUU->GetBinContent(i) <<endl;
   microB_CCMEC_GiBUU << trueEnu_CCMEC_GiBUU->GetXaxis()->GetBinCenter(i) << " " << trueEnu_CCMEC_GiBUU->GetBinContent(i) <<endl;
   microB_CCDIS_GiBUU << trueEnu_CCDIS_GiBUU->GetXaxis()->GetBinCenter(i) << " " << trueEnu_CCDIS_GiBUU->GetBinContent(i) <<endl;
   microB_other_GiBUU << trueEnu_other_GiBUU->GetXaxis()->GetBinCenter(i) << " " << trueEnu_other_GiBUU->GetBinContent(i) <<endl;
   
   }
   
    
   ////////////////////////////// Export in ROOT format ////////////////////////////////////////////
   
   out_microB_xsec_GiBUU->cd();
   out_microB_xsec_GiBUU->Write();
   
  ////////////////////////////// PLOTS //////////////////////////////////////////////////
  
  TCanvas *c1 = new TCanvas("c1", "c1", 900, 900);
  
  trueEnu_CC_GiBUU-> SetFillColor(kMagenta);
 
  THStack *trueEnu_CC = new THStack("trueEnu_CC","");
  trueEnu_CC-> Add(trueEnu_CC_GiBUU);
  trueEnu_CC-> Draw("hist");
  trueEnu_CC->GetXaxis()->SetTitle("E_{#nu} [GeV]");
  trueEnu_CC->GetYaxis()->SetTitle("number of events");
  
  TLegend *l1 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l1 -> AddEntry(trueEnu_CC_GiBUU, "CC", "f");
  l1 -> Draw();
  
  c1->Update();
  c1->Print("/home/gstenico/Desktop/SBND_GiBUU/GiBUU-GENIE/GiBUU_2021_2019/microB_CC_GiBUU_2021.pdf");
   
  }


