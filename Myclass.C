#define Myclass_cxx
#include "Myclass.h"
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

//*********************************************************Defining_Mass**************************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//

#define PI 3.14159265
#define mumass 0.1056583755 // GeV/c2
#define protonmass 0.93827208816 //GeV/c2
#define pionmass 0.1349768  //GeV/c2


//*********************************************************GiBBU_nomenclature*********************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//
THStack *Stack_em=new THStack("Stack_em","");
TH1D* CCQE = new TH1D("CCQE","CCQE",30,0,30);
TH1D* Cresonant = new TH1D("Cresonant","Cresonant",30,0,30);
TH1D* pi_plus_plus_n_bkg = new TH1D("pi_plus_plus_n_bkg","pi_plus_plus_n_bkg",30,0,30);
TH1D* pi_zero_plus_p_bkg = new TH1D("pi_zero_plus_p_bkg","pi_zero_plus_p_bkg",30,0,30);
TH1D* CCDIS = new TH1D("CCDIS","CCDIS",30,0,30);
TH1D* CCQE_two_p_two_h = new TH1D("CCQE_two_p_two_h","CCQE_two_p_two_h",30,0,30);
TH1D* Delta_two_p_two_h = new TH1D("Delta_two_p_two_h","Delta_two_p_two_h",30,0,30);
TH1D* two_pion_bkg = new TH1D("two_pion_bkg","two_pion_bkg",30,0,30);
TH1D* ninth= new TH1D("ninth","ninth",30,0,30);

//*********************************************Histogram_for_angle_of_muon************************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//
TH1D* cosine_muon = new TH1D("cosine_muon","cosine_muon",10,-1,1);

//**************************************************Resolution_Histograms*************************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//
TH2D* Resolution_EnuCCQE_GiBBU= new TH2D("Resolution_EnuCCQE_GiBBU", "Resolution_EnuCCQE_GiBBU",40,0.,2., 80, -2,2.);
TH2D* Resolution_EnuCalo_GiBBU= new TH2D("Resolution_EnuCalo_GiBBU", "Resolution_EnuCalo_GiBBU",40,0.,2., 80, -2,2.);
TH2D* Resolution_EnuRes_GiBBU= new TH2D("Resolution_EnuRes_GiBBU", "Resolution_EnuRes_GiBBU",40,0.,2., 80, -2,2.);

//***********************************************True_neutrino_energy_GiBBU***********************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//
TH1D* TrueEnu_CCQE_GiBBU= new TH1D("TrueEnu_CCQE_GiBBU", "TrueEnu_CCQE_GiBBU", 60, 0, 3);
TH1D* TrueEnu_CCMEC_GiBBU= new TH1D("TrueEnu_CCMEC_GiBBU", "TrueEnu_CCMEC_GiBBU", 60, 0, 3);
TH1D* TrueEnu_CCRES_GiBBU= new TH1D("TrueEnu_CCRES_GiBBU", "TrueEnu_CCRES_GiBBU", 60, 0, 3);
TH1D* TrueEnu_CCDIS_GiBBU= new TH1D("TrueEnu_CCDIS_GiBBU", "TrueEnu_CCDIS_GiBBU", 60, 0, 3);
TH1D* TrueEnu_CCCOH_GiBBU= new TH1D("TrueEnu_CCCOH_GiBBU", "TrueEnu_CCCOH_GiBBU", 60, 0, 3);

//**************************************************Histogram_for_the_ratio***********************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//
TH1D* TrueEnu_CCQE_ratio= new TH1D("TrueEnu_CCQE_ratio", "TrueEnu_CCQE_ratio", 60, 0, 20);
TH1D* TrueEnu_CCMEC_ratio= new TH1D("TrueEnu_CCMEC_ratio", "TrueEnu_CCMEC_ratio", 60, 0, 20);
TH1D* TrueEnu_CCRES_ratio= new TH1D("TrueEnu_CCRES_ratio", "TrueEnu_CCRES_ratio", 60, 0, 20);
TH1D* TrueEnu_CCDIS_ratio= new TH1D("TrueEnu_CCDIS_ratio", "TrueEnu_CCDIS_ratio", 60, 0, 20);
TH1D* TrueEnu_CCCOH_ratio= new TH1D("TrueEnu_CCCOH_ratio", "TrueEnu_CCCOH_ratio", 60, 0, 20);

//**********************************************Histogram_for_the_Tprofile plots******************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//
TProfile *hprof_EnuCCQE_GiBBU = new TProfile("hprof_EnuCCQE_GiBBU", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuCalo_GiBBU = new TProfile("hprof_EnuCalo_GiBBU", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuRES_GiBBU = new TProfile("hprof_EnuRES_GiBBU", "",50,0,1.5,-2.,2.);

TProfile *hprof_EnuCCQE_GiBBUnorw=new TProfile("hprof_EnuCCQE_GiBBUnorw", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuCalo_GiBBUnorw=new TProfile("hprof_EnuCalo_GiBBUnorw", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuRes_GiBBUnorw=new TProfile("hprof_EnuRes_GiBBUnorw", "",50,0,1.5,-2.,2.);

TProfile *hprof_EnuDL_GiBBU=new TProfile("hprof_EnuDL_GiBBU", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuPanN_GiBBU=new TProfile("hprof_EnuPanN_GiBBU", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuPan0_GiBBU=new TProfile("hprof_EnuPan0_GiBBU", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuWC_GiBBU=new TProfile("hprof_EnuWC_GiBBU", "",50,0,1.5,-2.,2.);

TProfile *hprof_EnuDL_GiBBUnorw=new TProfile("hprof_EnuDL_GiBBUnorw", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuPanN_GiBBUnorw=new TProfile("hprof_EnuPanN_GiBBUnorw", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuPan0_GiBBUnorw=new TProfile("hprof_EnuPan0_GiBBUnorw", "",50,0,1.5,-2.,2.);
TProfile *hprof_EnuWC_GiBBUnorw=new TProfile("hprof_EnuWC_GiBBUnorw", "",50,0,1.5,-2.,2.);


//*******************************************Histogram_for_the_Reconstructed_bins*****************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//
TH1D* bins_1_5= new TH1D("bins_1_5", "bins_1_5", 5, 0, 2.5);
TH1D* bins_6_10= new TH1D("bins_6_10", "bins_6_10", 5, 0, 2.5);
TH1D* bins_11_15= new TH1D("bins_11_15", "bins_11_15", 5, 0, 2.5);
TH1D* bins_16_19= new TH1D("bins_16_19", "bins_16_19", 4, 0, 2.5);
TH1D* bins_20_23= new TH1D("bins_20_23", "bins_20_23", 4, 0, 2.5);
TH1D* bins_24_27= new TH1D("bins_24_27", "bins_24_27", 4, 0, 2.5);
TH1D* bins_28_32= new TH1D("bins_28_32", "bins_28_32", 5, 0, 2.5);
TH1D* bins_33_37= new TH1D("bins_33_37", "bins_33_37", 5, 0, 2.5);
TH1D* bins_38_42= new TH1D("bins_38_42", "bins_38_42", 5, 0, 2.5);


//*************************************************Truth_bins_for_the_reconstruction**************************************************************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//
TH1D* bin_1 = new TH1D("bin_1","bin_1",30,0,30);
TH1D* bin_2 = new TH1D("bin_2","bin_2",30,0,30);
TH1D* bin_3 = new TH1D("bin_3","bin_3",30,0,30);
TH1D* bin_4= new TH1D("bin_4","bin_4",30,0,30);
TH1D* bin_5= new TH1D("bin_5","bin_5",30,0,30);
TH1D* bin_6= new TH1D("bin_6","bin_6",30,0,30);
TH1D* bin_7= new TH1D("bin_7","bin_7",30,0,30);
TH1D* bin_8= new TH1D("bin_8","bin_8",30,0,30);
TH1D* bin_9= new TH1D("bin_9","bin_9",30,0,30);
TH1D* bin_10= new TH1D("bin_10","bin_10",30,0,30);
TH1D* bin_11= new TH1D("bin_11","bin_11",30,0,30);
TH1D* bin_12= new TH1D("bin_12","bin_12",30,0,30);
TH1D* bin_13= new TH1D("bin_13","bin_13",30,0,30);
TH1D* bin_14= new TH1D("bin_14","bin_14",30,0,30);
TH1D* bin_15= new TH1D("bin_15","bin_15",30,0,30);
TH1D* bin_16= new TH1D("bin_16","bin_16",30,0,30);
TH1D* bin_17= new TH1D("bin_17","bin_17",30,0,30);
TH1D* bin_18= new TH1D("bin_18","bin_18",30,0,30);
TH1D* bin_19= new TH1D("bin_19","bin_19",30,0,30);
TH1D* bin_20= new TH1D("bin_20","bin_20",30,0,30);
TH1D* bin_21= new TH1D("bin_21","bin_21",30,0,30);
TH1D* bin_22= new TH1D("bin_22","bin_22",30,0,30);
TH1D* bin_23= new TH1D("bin_23","bin_23",30,0,30);
TH1D* bin_24= new TH1D("bin_24","bin_24",30,0,30);
TH1D* bin_25= new TH1D("bin_25","bin_25",30,0,30);
TH1D* bin_26= new TH1D("bin_26","bin_26",30,0,30);
TH1D* bin_27= new TH1D("bin_27","bin_27",30,0,30);
TH1D* bin_28= new TH1D("bin_28","bin_28",30,0,30);
TH1D* bin_29= new TH1D("bin_29","bin_29",30,0,30);
TH1D* bin_30= new TH1D("bin_30","bin_30",30,0,30);
TH1D* bin_31= new TH1D("bin_31","bin_31",30,0,30);
TH1D* bin_32= new TH1D("bin_32","bin_32",30,0,30);
TH1D* bin_33= new TH1D("bin_33","bin_33",30,0,30);
TH1D* bin_34= new TH1D("bin_34","bin_34",30,0,30);
TH1D* bin_35= new TH1D("bin_35","bin_35",30,0,30);
TH1D* bin_36= new TH1D("bin_36","bin_36",30,0,30);
TH1D* bin_37= new TH1D("bin_37","bin_37",30,0,30);
TH1D* bin_38= new TH1D("bin_38","bin_38",30,0,30);
TH1D* bin_39= new TH1D("bin_39","bin_39",30,0,30);
TH1D* bin_40= new TH1D("bin_40","bin_40",30,0,30);
TH1D* bin_41= new TH1D("bin_41","bin_41",30,0,30);
TH1D* bin_42= new TH1D("bin_42","bin_42",30,0,30);


/******************************************** reconstructed neutrino energy in uB ***************************************************************/
/************************************************************************************************************************************************/
/********************************************reconstructed neutrino energy in the Deep Learning analysis for 1muon+ 1 proton selection***********/

TH1D *EnuDL_CCQE_GiBBU=new TH1D("EnuDL_CCQE_GiBBU", "EnuDL_CCQE_GiBBU", 60, 0, 3);
TH1D *EnuDL_CCMEC_GiBBU=new TH1D("EnuDL_CCMEC_GiBBU", "EnuDL_CCMEC_GiBBU", 60, 0, 3);
TH1D *EnuDL_CCRES_GiBBU=new TH1D("EnuDL_CCRES_GiBBU", "EnuDL_CCRES_GiBBU", 60, 0, 3);
TH1D *EnuDL_CCDIS_GiBBU=new TH1D("EnuDL_CCDIS_GiBBU", "EnuDL_CCDIS_GiBBU", 60, 0, 3);
TH1D *EnuDL_CCCOH_GiBBU=new TH1D("EnuDL_CCCOH_GiBBU", "EnuDL_CCCOH_GiBBU", 60, 0, 3);
TH1D *EnuDL_other_GiBBU=new TH1D("EnuDL_other_GiBBU", "EnuDL_other_GiBBU", 60, 0, 3);

TH1D *EnuDL_CCQE_GiBBUnorw=new TH1D("EnuDL_CCQE_GiBBUnorw", "EnuDL_CCQE_GiBBUnorw", 60, 0, 3);
TH1D *EnuDL_CCMEC_GiBBUnorw=new TH1D("EnuDL_CCMEC_GiBBUnorw", "EnuDL_CCMEC_GiBBUnorw", 60, 0, 3);
TH1D *EnuDL_CCRES_GiBBUnorw=new TH1D("EnuDL_CCRES_GiBBUnorw", "EnuDL_CCRES_GiBBUnorw", 60, 0, 3);
TH1D *EnuDL_CCDIS_GiBBUnorw=new TH1D("EnuDL_CCDIS_GiBBUnorw", "EnuDL_CCDIS_GiBBUnorw", 60, 0, 3);
TH1D *EnuDL_CCCOH_GiBBUnorw=new TH1D("EnuDL_CCCOH_GiBBUnorw", "EnuDL_CCCOH_GiBBUnorw", 60, 0, 3);
TH1D *EnuDL_other_GiBBUnorw=new TH1D("EnuDL_other_GiBBUnorw", "EnuDL_other_GiBBUnorw", 60, 0, 3);

//*****************************reconstructed neutrino energy in the Pandora analysis for 1muon+ N(>0) proton selection***************************// 

TH1D *EnuPanN_CCQE_GiBBU=new TH1D("EnuPanN_CCQE_GiBBU", "EnuPanN_CCQE_GiBBU", 60, 0, 3);
TH1D *EnuPanN_CCMEC_GiBBU=new TH1D("EnuPanN_CCMEC_GiBBU", "EnuPanN_CCMEC_GiBBU", 60, 0, 3);
TH1D *EnuPanN_CCRES_GiBBU=new TH1D("EnuPanN_CCRES_GiBBU", "EnuPanN_CCRES_GiBBU", 60, 0, 3);
TH1D *EnuPanN_CCDIS_GiBBU=new TH1D("EnuPanN_CCDIS_GiBBU", "EnuPanN_CCDIS_GiBBU", 60, 0, 3);
TH1D *EnuPanN_CCCOH_GiBBU=new TH1D("EnuPanN_CCCOH_GiBBU", "EnuPanN_CCCOH_GiBBU", 60, 0, 3);
TH1D *EnuPanN_other_GiBBU=new TH1D("EnuPanN_other_GiBBU", "EnuPanN_other_GiBBU", 60, 0, 3);

TH1D *EnuPanN_CCQE_GiBBUnorw=new TH1D("EnuPanN_CCQE_GiBBUnorw", "EnuPanN_CCQE_GiBBUnorw", 60, 0, 3);
TH1D *EnuPanN_CCMEC_GiBBUnorw=new TH1D("EnuPanN_CCMEC_GiBBUnorw", "EnuPanN_CCMEC_GiBBUnorw", 60, 0, 3);
TH1D *EnuPanN_CCRES_GiBBUnorw=new TH1D("EnuPanN_CCRES_GiBBUnorw", "EnuPanN_CCRES_GiBBUnorw", 60, 0, 3);
TH1D *EnuPanN_CCDIS_GiBBUnorw=new TH1D("EnuPanN_CCDIS_GiBBUnorw", "EnuPanN_CCDIS_GiBBUnorw", 60, 0, 3);
TH1D *EnuPanN_CCCOH_GiBBUnorw=new TH1D("EnuPanN_CCCOH_GiBBUnorw", "EnuPanN_CCCOH_GiBBUnorw", 60, 0, 3);
TH1D *EnuPanN_other_GiBBUnorw=new TH1D("EnuPanN_other_GiBBUnorw", "EnuPanN_other_GiBBUnorw", 60, 0, 3);

//******************************reconstructed neutrino energy in the Pandora analysis for 1muon+ 0 proton selection******************************//

TH1D *EnuPan0_CCQE_GiBBU=new TH1D("EnuPan0_CCQE_GiBBU", "EnuPan0_CCQE_GiBBU", 60, 0, 3);
TH1D *EnuPan0_CCMEC_GiBBU=new TH1D("EnuPan0_CCMEC_GiBBU", "EnuPan0_CCMEC_GiBBU", 60, 0, 3);
TH1D *EnuPan0_CCRES_GiBBU=new TH1D("EnuPan0_CCRES_GiBBU", "EnuPan0_CCRES_GiBBU", 60, 0, 3);
TH1D *EnuPan0_CCDIS_GiBBU=new TH1D("EnuPan0_CCDIS_GiBBU", "EnuPan0_CCDIS_GiBBU", 60, 0, 3);
TH1D *EnuPan0_CCCOH_GiBBU=new TH1D("EnuPan0_CCCOH_GiBBU", "EnuPan0_CCCOH_GiBBU", 60, 0, 3);
TH1D *EnuPan0_other_GiBBU=new TH1D("EnuPan0_other_GiBBU", "EnuPan0_other_GiBBU", 60, 0, 3);

TH1D *EnuPan0_CCQE_GiBBUnorw=new TH1D("EnuPan0_CCQE_GiBBUnorw", "EnuPan0_CCQE_GiBBUnorw", 60, 0, 3);
TH1D *EnuPan0_CCMEC_GiBBUnorw=new TH1D("EnuPan0_CCMEC_GiBBUnorw", "EnuPan0_CCMEC_GiBBUnorw", 60, 0, 3);
TH1D *EnuPan0_CCRES_GiBBUnorw=new TH1D("EnuPan0_CCRES_GiBBUnorw", "EnuPan0_CCRES_GiBBUnorw", 60, 0, 3);
TH1D *EnuPan0_CCDIS_GiBBUnorw=new TH1D("EnuPan0_CCDIS_GiBBUnorw", "EnuPan0_CCDIS_GiBBUnorw", 60, 0, 3);
TH1D *EnuPan0_CCCOH_GiBBUnorw=new TH1D("EnuPan0_CCCOH_GiBBUnorw", "EnuPan0_CCCOH_GiBBUnorw", 60, 0, 3);
TH1D *EnuPan0_other_GiBBUnorw=new TH1D("EnuPan0_other_GiBBUnorw", "EnuPan0_other_GiBBUnorw", 60, 0, 3);

//****************reconstructed neutrino energy in the Wire Cell analysis for 1muon+ X (any) proton selection  (numu CC inclusive)***************//

TH1D *EnuWC_CCQE_GiBBU=new TH1D("EnuWC_CCQE_GiBBU", "EnuWC_CCQE_GiBBU", 60, 0, 3);
TH1D *EnuWC_CCMEC_GiBBU=new TH1D("EnuWC_CCMEC_GiBBU", "EnuWC_CCMEC_GiBBU", 60, 0, 3);
TH1D *EnuWC_CCRES_GiBBU=new TH1D("EnuWC_CCRES_GiBBU", "EnuWC_CCRES_GiBBU", 60, 0, 3);
TH1D *EnuWC_CCDIS_GiBBU=new TH1D("EnuWC_CCDIS_GiBBU", "EnuWC_CCDIS_GiBBU", 60, 0, 3);
TH1D *EnuWC_CCCOH_GiBBU=new TH1D("EnuWC_CCCOH_GiBBU", "EnuWC_CCCOH_GiBBU", 60, 0, 3);
TH1D *EnuWC_other_GiBBU=new TH1D("EnuWC_other_GiBBU", "EnuWC_other_GiBBU", 60, 0, 3);

TH1D *EnuWC_CCQE_GiBBUnorw=new TH1D("EnuWC_CCQE_GiBBUnorw", "EnuWC_CCQE_GiBBUnorw", 60, 0, 3);
TH1D *EnuWC_CCMEC_GiBBUnorw=new TH1D("EnuWC_CCMEC_GiBBUnorw", "EnuWC_CCMEC_GiBBUnorw", 60, 0, 3);
TH1D *EnuWC_CCRES_GiBBUnorw=new TH1D("EnuWC_CCRES_GiBBUnorw", "EnuWC_CCRES_GiBBUnorw", 60, 0, 3);
TH1D *EnuWC_CCDIS_GiBBUnorw=new TH1D("EnuWC_CCDIS_GiBBUnorw", "EnuWC_CCDIS_GiBBUnorw", 60, 0, 3);
TH1D *EnuWC_CCCOH_GiBBUnorw=new TH1D("EnuWC_CCCOH_GiBBUnorw", "EnuWC_CCCOH_GiBBUnorw", 60, 0, 3);
TH1D *EnuWC_other_GiBBUnorw=new TH1D("EnuWC_other_GiBBUnorw", "EnuWC_other_GiBBUnorw", 60, 0, 3);

std::vector<double> smearing_matrix;
std::vector<double> Truth_bins;
std::vector<double> Reconstructed_bins;
double Reweighting_Gibbu[60][5];
double Rewighting_Gibbu_Genie_norw[60][5];

//*******************************Calculating 4-momentum transfer. We could also use as input any reconstructed neutrino energy********************//
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//
double GetQ2(double enu, double emu, double pmuz){ /// invariant 4-momentum transfer

  double pmuL = pmuz;
  double mom4 = 2 * enu * (emu - pmuL) - mumass*mumass;
  return mom4;
  
}

//*calculating the energy transfer from the neutrino to the nucleus. We could use as input reconstructred neutrino energy also to test resolutions*/
//************************************************************************************************************************************************//
//************************************************************************************************************************************************//

double w(double emu, double enu){ ///// energy transfer

  return (enu - emu);
  
}


//...........................................Calculating_the_final_momenta(hadrons)...............................................................//
//................................................................................................................................................//
//................................................................................................................................................//
double momentum(vector<double> Momentum_Px[],vector<double> Momentum_Py[],vector<double> Momentum_Pz[],int counter)
{
  double norm=pow((*Momentum_Px)[counter],2.0)+pow((*Momentum_Py)[counter],2.0)+pow((*Momentum_Pz)[counter],2.0);
  return norm;
}
//*************************************************************************************************************************************************/
//**************************************************Energy_Reconstruction_through_Microboone_Methods***********************************************/
//*************************************************************************************************************************************************/
double GetEuB(double Epion, double Esum, int X , int np) 
{

  double enu = 0.;

  if (X == 1){ /// Pandora approach
    enu = Esum;
  }
  else if (X == 2){ /// Depp Learning approach
    enu = Esum + 0.040;
  }
  else if (X == 3){ /// Wire Cell approach
    enu = Esum + Epion + np*0.0086;
  }
 
  return enu; // return result in GeV

}

//*************************************************************************************************************************************************/
//**************************************************Energy_Reconstruction_through_CCCQE_Method***********************************************/
//*************************************************************************************************************************************************/
double Enu_CCQE(double M_Proton,double E_Muon,double M_Muon,double P_Muon, double Cosine_Muon)
{
  double E_neutrino=0;
  E_neutrino=((M_Proton*E_Muon)-(pow(M_Muon,2.0))/2)/(M_Proton-E_Muon+(P_Muon*Cosine_Muon));
  return E_neutrino;
}


//*************************************************************************************************************************************************/
//**************************************************Energy_Reconstruction_through_CCRES_Method***********************************************/
//*************************************************************************************************************************************************/
double Enu_RES(double M_delta,double M_Proton,double E_Muon,double M_Muon, double Cosine_Muon)
{
 double E_neutrino=0;
 E_neutrino= (pow(M_delta,2.0)-pow(M_Proton,2.0)+(2*M_Proton*E_Muon))/(2*(M_Proton-(E_Muon*(1-Cosine_Muon))));
 return E_neutrino;
}


//***********************************************************************************************************************************************//
//**************************************************Energy_Reconstruction_through_Calorimetry_Methods********************************************//
//***********************************************************************************************************************************************//
double Enu_Calo(double Missing_PT, vector<double> M_Px[],vector<double> M_Py[],vector<double> M_Pz[],double Mu_E)
{
  double M_argon=37.205;
  double summa=0;
  double E_excited=0.0304;
  double E_kin_recoil=0;
  double proton_mass=0.938;
  for (int k=0;k<M_Px->size();k++)
    {
     double hadron_momenta= momentum(M_Px,M_Py,M_Pz,k);
     summa+=hadron_momenta/(2*proton_mass);  
    }
    summa=summa+Mu_E;
    E_kin_recoil=pow(Missing_PT+pow(M_argon,2.0),0.5)-M_argon;
    double reconstructed_neu_energy_calorie=summa+E_kin_recoil+E_excited;
    return reconstructed_neu_energy_calorie;
     
}

//***********************************************************************************************************************************************//
//**************************************************Finding_the_Missing_PT***********************************************************************//
//***********************************************************************************************************************************************//
double Missing_PT(int index, vector<double> Hadron_Px[],vector<double> Hadron_Py[],double lep_Px,double lep_Py)
{
      double transverse=0;    
      double x_component=0;
      double y_component=0;
      x_component=(*Hadron_Px)[index]+lep_Px;
      y_component=(*Hadron_Py)[index]+lep_Py;
      transverse=pow(x_component,2.0)+pow(y_component,2.0);
      return transverse;
}


//***********************************************************************************************************************************************//
//**************************************************Finding_the_cos_theta***********************************************************************//
//***********************************************************************************************************************************************//
double cos_theta(double Mu_Px, double Mu_Py,double Mu_Pz)
{
      double cosine_mu=0;
      double norm=pow((pow(Mu_Px,2.0)+pow(Mu_Py,2.0)+pow(Mu_Pz,2.0)),0.5);
      if (norm==0)std::cout<<" Oh almighty god, what happened "<<std::endl;
      cosine_mu=Mu_Pz/norm;
      return cosine_mu;
}

//***********************************************************************************************************************************************//
//**************************************************Finding_the_Invariant_Mass*******************************************************************//
//***********************************************************************************************************************************************//
double invariant_mass(double nu_E,double mu_E, double mu_Pz)
{
  double Nucelon_mass=0.9395;
  double invariant_mass=pow(Nucelon_mass,2.0)+2*Nucelon_mass*(nu_E-mu_E)-2*nu_E*(mu_E-mu_Pz)-pow(0.10566,2.0);
  return invariant_mass;
}


//***********************************************************************************************************************************************//
//**************************************************Finding_the_highest_energy_proton************************************************************//
//***********************************************************************************************************************************************//
int indices_func(vector<double> B[],vector<int> C[],int number)
 { 
   int value=-100;
   int greatest=-1;
   //code to check that there is actually proton in the final state
   for (int k=0;k<number;k++)
      {
         if ((*C)[k]==2212)
         {
          greatest=0;
         }
      } 
      //if it is there than find the indice corresponding to then highest energy proton.
     if (greatest==0)
     {
     for (int v=0;v<number;v++)
     {
       if (((*B)[v]>value)&&((*C)[v]==2212))
       {
         value=(*B)[v];
         greatest=v;
       }
      
     }
     }
      return greatest;
 }
void Myclass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Myclass.C
//      root> Myclass t
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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int kai=0;
   
   
//************************************************************************************************************************************************//
//**************************************************Getting_the_GENIE_FILES***********************************************************************//
//************************************************************************************************************************************************//
   TFile *f = new TFile("analysis_GENIErw.root");
   TH1D *TrueEnu_CCQE_GENIE = (TH1D*)f->Get("TrueEnu_CCQE_GENIE");
   TH1D *TrueEnu_CCMEC_GENIE = (TH1D*)f->Get("TrueEnu_CCMEC_GENIE");
   TH1D *TrueEnu_CCRES_GENIE = (TH1D*)f->Get("TrueEnu_CCRES_GENIE");
   TH1D *TrueEnu_CCDIS_GENIE = (TH1D*)f->Get("TrueEnu_CCDIS_GENIE");
   TH1D *TrueEnu_CCCOH_GENIE = (TH1D*)f->Get("TrueEnu_CCCOH_GENIE");
   TH2D *Resolution_EnuCCQE_GENIE= (TH2D*)f->Get("Resolution_EnuCCQE_GENIE");
   

//***********************************************************************************************************************************************//
//********************************************************GENIE_REWEIGHTED***********************************************************************//
//***********************************************************************************************************************************************//
   
   TH1D *TrueEnu_CCQE_GENIEnorw = (TH1D*)f->Get("TrueEnu_CCQE_GENIEnorw");
   TH1D *TrueEnu_CCMEC_GENIEnorw = (TH1D*)f->Get("TrueEnu_CCMEC_GENIEnorw");
   TH1D *TrueEnu_CCRES_GENIEnorw = (TH1D*)f->Get("TrueEnu_CCRES_GENIEnorw");
   TH1D *TrueEnu_CCDIS_GENIEnorw = (TH1D*)f->Get("TrueEnu_CCDIS_GENIEnorw");
   TH1D *TrueEnu_CCCOH_GENIEnorw = (TH1D*)f->Get("TrueEnu_CCCOH_GENIEnorw");
   
//********************************************Start_of_the_loop_for_events*********************************************************************//   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue
      //std::cout<<"Event is"<<jentry<<std::endl;
      //std::cout<<"energy of lepton is"<<lepIn_E<<std::endl;
      int vi=0;
      double proton_mass=0.938;
      double muon_mass=0.106;
      double mass_delta=1.232;
      vi=indices_func(E,barcode,barcode->size());
      /*if (vi==-1)
      {
      kai++;
      continue;
      }*/
      
//***********************************************************************************************************************************************//
//*********************************************************Invariant_Mass************************************************************************//
//***********************************************************************************************************************************************//
      float invari=invariant_mass(lepIn_E,lepOut_E, lepOut_Pz);
      
//***********************************************************************************************************************************************//
//********************************************************Muon_Momentum**************************************************************************//
//***********************************************************************************************************************************************//
      float muon_momentum=pow((pow(lepOut_Px,2.0)+pow(lepOut_Py,2.0)+pow(lepOut_Pz,2.0)),0.5);
     
//***********************************************************************************************************************************************//
//******************************************************Energy_Reconstruction********************************************************************//
//***********************************************************************************************************************************************//
      
      
      double Energy_CCQE=Enu_CCQE(proton_mass,lepOut_E,muon_mass,muon_momentum,cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz));
      Resolution_EnuCCQE_GiBBU->Fill(lepIn_E,lepIn_E-Energy_CCQE);
      hprof_EnuCCQE_GiBBU->Fill(lepIn_E,lepIn_E-Energy_CCQE);
      
      double Energy_RES=Enu_RES(mass_delta,proton_mass,lepOut_E,muon_mass,cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz));
      //std::cout<<" energy "<<muon_neutrino_1<<std::endl;
      Resolution_EnuRes_GiBBU->Fill(lepIn_E,lepIn_E-Energy_RES);
      hprof_EnuRES_GiBBU->Fill(lepIn_E,lepIn_E-Energy_RES);
      
      if (vi!=-1)
      {
      kai++;
      double Energy_Calo=Enu_Calo(Missing_PT(vi,Px,Py, lepOut_Px,lepOut_Py),Px,Py,Pz,lepOut_E);
      Resolution_EnuCalo_GiBBU->Fill(lepIn_E,lepIn_E-Energy_Calo);
      hprof_EnuCalo_GiBBU->Fill(lepIn_E,lepIn_E-Energy_Calo);
      }
      
         
//***********************************************************************************************************************************************//
//*************************************************Finding_the_cosine(muon)***********************************************************************//
//***********************************************************************************************************************************************//
      cosine_muon->Fill(cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz),weight);
      
      
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
      double pmu = sqrt(lepOut_Px*lepOut_Px + lepOut_Py*lepOut_Py + lepOut_Pz*lepOut_Pz); /// true muon (absolute) momentum
      double emu = sqrt(mumass*mumass + pmu*pmu); /// true muon energy
      double q2 = GetQ2(lepOut_E, emu,lepOut_Pz); /// 4-momentum transfer from true kinematics
      double omega = w(emu, lepOut_E); /// true energy transfer
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
      
      if (evType==1)
      {
      TrueEnu_CCQE_GiBBU->Fill(lepIn_E,weight);
      

         /// 1muon+ X proton //// Wire Cell signal (any number of protons)
	 EnuWC_CCQE_GiBBU->Fill(GetEuB(Epion, Esum, 3 , nproton), 1);
	 EnuWC_CCQE_GiBBUnorw->Fill(GetEuB(Epion, Esum, 3 , nproton),weight);
	 hprof_EnuWC_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(Epion, Esum, 3 , nproton),1);
	 hprof_EnuWC_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(Epion, Esum, 3 , nproton),weight);
	 
	 /// 1muon+ 0 proton + 0 pion //// Pandora 0proton signal
	 if ((npospion + nnegpion + nnpion + nproton) ==0){
	   EnuPan0_CCQE_GiBBU->Fill(GetEuB(0, Esum, 1 , nproton), 1);
	   EnuPan0_CCQE_GiBBUnorw->Fill(GetEuB(0, Esum, 1 , nproton),weight);
	   hprof_EnuPan0_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),1);
	   hprof_EnuPan0_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),weight);
	 }
	 
	 /// 1muon+ N proton + 0 pion //// Pandora Nproton signal
	 if (((npospion + nnegpion + nnpion) ==0) && (nproton > 0)) {
	   EnuPanN_CCQE_GiBBU->Fill(GetEuB(0, Esum, 1 , nproton), 1);
	   EnuPanN_CCQE_GiBBUnorw->Fill(GetEuB(0, Esum, 1 , nproton),weight);
	   hprof_EnuPanN_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),1);
	   hprof_EnuPanN_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),weight);
	 }
	 
	 //// 1muon+1 proton //// Deep Learning signal
	 if (((npospion + nnegpion + nnpion) ==0) && (nproton ==1)) {
	   EnuDL_CCQE_GiBBU->Fill(GetEuB(0, Esum, 2 , nproton), 1);
	   EnuDL_CCQE_GiBBUnorw->Fill(GetEuB(0, Esum, 2 , nproton),weight);
	   hprof_EnuDL_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 2 , nproton),1);
	   hprof_EnuDL_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 2 , nproton),weight);
	 }
	 
      }
      if ((evType>=2)||(evType<=31))
      {
      TrueEnu_CCRES_GiBBU->Fill(lepIn_E,weight);
      
        /// 1muon+ X proton //// Wire Cell signal (any number of protons)
	 EnuWC_CCRES_GiBBU->Fill(GetEuB(Epion, Esum, 3 , nproton), 1);
	 EnuWC_CCRES_GiBBUnorw->Fill(GetEuB(Epion, Esum, 3 , nproton),weight);
	 hprof_EnuWC_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(Epion, Esum, 3 , nproton),1);
	 hprof_EnuWC_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(Epion, Esum, 3 , nproton),weight);
	 
	 /// 1muon+ 0 proton + 0 pion //// Pandora 0proton signal
	 if ((npospion + nnegpion + nnpion + nproton) ==0){
	   EnuPan0_CCRES_GiBBU->Fill(GetEuB(0, Esum, 1 , nproton), 1);
	   EnuPan0_CCRES_GiBBUnorw->Fill(GetEuB(0, Esum, 1 , nproton),weight);
	   hprof_EnuPan0_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),1);
	   hprof_EnuPan0_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),weight);
	 }
	 
	 /// 1muon+ N proton + 0 pion //// Pandora Nproton signal
	 if (((npospion + nnegpion + nnpion) ==0) && nproton > 0) {
	   EnuPanN_CCRES_GiBBU->Fill(GetEuB(0, Esum, 1 , nproton), 1);
	   EnuPanN_CCRES_GiBBUnorw->Fill(GetEuB(0, Esum, 1 , nproton),weight);
	   hprof_EnuPanN_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),1);
	   hprof_EnuPanN_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),weight);
	 }
	 
	 //// 1muon+1 proton //// Deep Learning signal
	 if (((npospion + nnegpion + nnpion) ==0) && nproton ==1) {
	   EnuDL_CCRES_GiBBU->Fill(GetEuB(0, Esum, 2 , nproton), 1);
	   EnuDL_CCRES_GiBBUnorw->Fill(GetEuB(0, Esum, 2 , nproton),weight);
	   hprof_EnuDL_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 2 , nproton),1);
	   hprof_EnuDL_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 2 , nproton),weight);
	 }

      }
      //if (evType==32){std::cout<<" I got em "<<std::endl;}
      
      if ((evType==32)||(evType==33)||(evType==34)||(evType==37))
      {
      TrueEnu_CCDIS_GiBBU->Fill(lepIn_E,weight);
      //std::cout<<" Is there any CCDIS data "<<std::endl;
          /// 1muon+ X proton //// Wire Cell signal (any number of protons)
	 EnuWC_CCDIS_GiBBU->Fill(GetEuB(Epion, Esum, 3 , nproton), 1);
	 EnuWC_CCDIS_GiBBUnorw->Fill(GetEuB(Epion, Esum, 3 , nproton),weight);
	 hprof_EnuWC_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(Epion, Esum, 3 , nproton),1);
	 hprof_EnuWC_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(Epion, Esum, 3 , nproton),weight);
	 
	 /// 1muon+ 0 proton + 0 pion //// Pandora 0proton signal
	 if ((npospion + nnegpion + nnpion + nproton) ==0){
	   EnuPan0_CCDIS_GiBBU->Fill(GetEuB(0, Esum, 1 , nproton), 1);
	   EnuPan0_CCDIS_GiBBUnorw->Fill(GetEuB(0, Esum, 1 , nproton),weight);
	   hprof_EnuPan0_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),1);
	   hprof_EnuPan0_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),weight);
	 }
	 
	 /// 1muon+ N proton + 0 pion //// Pandora Nproton signal
	 if (((npospion + nnegpion + nnpion) ==0) && nproton > 0) {
	   EnuPanN_CCDIS_GiBBU->Fill(GetEuB(0, Esum, 1 , nproton), 1);
	   EnuPanN_CCDIS_GiBBUnorw->Fill(GetEuB(0, Esum, 1 , nproton),weight);
	   hprof_EnuPanN_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),1);
	   hprof_EnuPanN_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),weight);
	 }
	 
	 //// 1muon+1 proton //// Deep Learning signal
	 if (((npospion + nnegpion + nnpion) ==0) && nproton ==1) {
	   EnuDL_CCDIS_GiBBU->Fill(GetEuB(0, Esum, 2 , nproton), 1);
	   EnuDL_CCDIS_GiBBUnorw->Fill(GetEuB(0, Esum, 2 , nproton),weight);
	   hprof_EnuDL_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 2 , nproton),1);
	   hprof_EnuDL_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 2 , nproton),weight);
	 } 
      }
      /*else if (evType==33)
      {
      TrueEnu_CCDIS_GiBBU->Fill(lepIn_E,weight);
      //std::cout<<"energy is"<< lepIn_E<<std::endl;
      }
      else if (evType==34)
      {
      TrueEnu_CCDIS_GiBBU->Fill(lepIn_E,weight);
      //std::cout<<"energy is"<< lepIn_E<<std::endl;
      }*/
      if ((evType==35)||(evType==36))
      {
      TrueEnu_CCMEC_GiBBU->Fill(lepIn_E,weight);
          /// 1muon+ X proton //// Wire Cell signal (any number of protons)
	 EnuWC_CCMEC_GiBBU->Fill(GetEuB(Epion, Esum, 3 , nproton), 1);
	 EnuWC_CCMEC_GiBBUnorw->Fill(GetEuB(Epion, Esum, 3 , nproton),weight);
	 hprof_EnuWC_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(Epion, Esum, 3 , nproton),1);
	 hprof_EnuWC_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(Epion, Esum, 3 , nproton),weight);
	 
	 /// 1muon+ 0 proton + 0 pion //// Pandora 0proton signal
	 if ((npospion + nnegpion + nnpion + nproton) ==0){
	   EnuPan0_CCMEC_GiBBU->Fill(GetEuB(0, Esum, 1 , nproton), 1);
	   EnuPan0_CCMEC_GiBBUnorw->Fill(GetEuB(0, Esum, 1 , nproton),weight);
	   hprof_EnuPan0_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),1);
	   hprof_EnuPan0_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),weight);
	 }
	 
	 /// 1muon+ N proton + 0 pion //// Pandora Nproton signal
	 if (((npospion + nnegpion + nnpion) ==0) && nproton > 0) {
	 //std::cout<<" Is there any PanN data "<<std::endl;
	   EnuPanN_CCMEC_GiBBU->Fill(GetEuB(0, Esum, 1 , nproton), 1);
	   EnuPanN_CCMEC_GiBBUnorw->Fill(GetEuB(0, Esum, 1 , nproton),weight);
	   hprof_EnuPanN_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),1);
	   hprof_EnuPanN_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 1 , nproton),weight);
	 }
	 
	 //// 1muon+1 proton //// Deep Learning signal
	 if (((npospion + nnegpion + nnpion) ==0) && nproton ==1) {
	 //std::cout<<" Is there any EnuDL data "<<std::endl;
	   EnuDL_CCMEC_GiBBU->Fill(GetEuB(0, Esum, 2 , nproton), 1);
	   EnuDL_CCMEC_GiBBUnorw->Fill(GetEuB(0, Esum, 2 , nproton),weight);
	   hprof_EnuDL_GiBBU->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 2 , nproton),1);
	   hprof_EnuDL_GiBBUnorw->Fill(lepIn_E,lepIn_E - GetEuB(0, Esum, 2 , nproton),weight);
	 }
      }
      /*else if (evType==36)
      {
      TrueEnu_CCMEC_GiBBU->Fill(lepIn_E,weight);
      //std::cout<<"energy is"<< lepIn_E<<std::endl;
      }
      else if (evType==37)
      {
      TrueEnu_CCDIS_GiBBU->Fill(lepIn_E,weight);
      //std::cout<<"energy is"<< lepIn_E<<std::endl;
      }*/
      if ((evType>37)&&(evType<1))
      {
      ninth->Fill(lepIn_E,weight);
      }


//***********************************************************************************************************************************************//
//*****************************************Getting_the_bins_for_Truth_Simulation******************************************************************//
//*******************************************************************************************************************************************//     
      if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-1)&&( cos_theta(lepOut_Px,          lepOut_Py,lepOut_Pz)<-0.5)&&( muon_momentum>=0)&&( muon_momentum<0.18))
      {
      bin_1->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-1)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<-0.5)&&( muon_momentum>=0.18)&&( muon_momentum<0.30))
      {
      bin_2->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-1)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<-0.5)&&( muon_momentum>=0.30)&&( muon_momentum<0.45))
      {
      bin_3->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-1)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<-0.5)&&( muon_momentum>=0.45)&&( muon_momentum<0.77))
      {
      bin_4->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-1)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<-0.5)&&( muon_momentum>=0.77)&&( muon_momentum<2.50))
      {
      bin_5->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-0.5)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0)&&( muon_momentum>=0)&&( muon_momentum<0.18))
      {
      bin_6->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-0.5)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0)&&( muon_momentum>=0.18)&&( muon_momentum<0.30))
      {
      bin_7->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-0.5)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0)&&( muon_momentum>=0.30)&&( muon_momentum<0.45))
      {
      bin_8->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-0.5)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0)&&( muon_momentum>=0.45)&&( muon_momentum<0.77))
      {
      bin_9->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=-0.5)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0)&&( muon_momentum>=0.77)&&( muon_momentum<2.50))
      {
      bin_10->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.27)&&( muon_momentum>=0)&&( muon_momentum<0.18))
      {
      bin_11->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.27)&&( muon_momentum>=0.18)&&( muon_momentum<0.30))
      {
      bin_12->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.27)&&( muon_momentum>=0.30)&&( muon_momentum<0.45))
      {
      bin_13->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.27)&&( muon_momentum>=0.45)&&( muon_momentum<0.77))
      {
      bin_14->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.27)&&( muon_momentum>=0.77)&&( muon_momentum<2.50))
      {
      bin_15->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.27)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.45)&&( muon_momentum>=0)&&( muon_momentum<0.30))
      {
      bin_16->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.27)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.45)&&( muon_momentum>=0.30)&&( muon_momentum<0.45))
      {
      bin_17->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.27)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.45)&&( muon_momentum>=0.45)&&( muon_momentum<0.77))
      {
      bin_18->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.27)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.45)&&( muon_momentum>=0.77)&&( muon_momentum<2.50))
      {
      bin_19->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.45)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.62)&&( muon_momentum>=0)&&( muon_momentum<0.30))
      {
      bin_20->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.45)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.62)&&( muon_momentum>=0.30)&&( muon_momentum<0.45))
      {
      bin_21->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.45)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.62)&&( muon_momentum>=0.45)&&( muon_momentum<0.77))
      {
      bin_22->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.45)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.62)&&( muon_momentum>=0.77)&&( muon_momentum<2.50))
      {
      bin_23->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.62)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.76)&&( muon_momentum>=0)&&( muon_momentum<0.30))
      {
      bin_24->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.62)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.76)&&( muon_momentum>=0.30)&&( muon_momentum<0.45))
      {
      bin_25->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.62)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.76)&&( muon_momentum>=0.45)&&( muon_momentum<0.77))
      {
      bin_26->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.62)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.76)&&( muon_momentum>=0.77)&&( muon_momentum<2.50))
      {
      bin_27->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.76)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.86)&&( muon_momentum>=0)&&( muon_momentum<0.30))
      {
      bin_28->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.76)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.86)&&( muon_momentum>=0.30)&&( muon_momentum<0.45))
      {
      bin_29->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.76)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.86)&&( muon_momentum>=0.45)&&( muon_momentum<0.77))
      {
      bin_30->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.76)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.86)&&( muon_momentum>=0.77)&&( muon_momentum<1.28))
      {
      bin_31->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.76)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.86)&&( muon_momentum>=1.28)&&( muon_momentum<2.50))
      {
      bin_32->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.86)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.94)&&( muon_momentum>=0)&&( muon_momentum<0.30))
      {
      bin_33->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.86)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.94)&&( muon_momentum>=0.30)&&( muon_momentum<0.45))
      {
      bin_34->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.86)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.94)&&( muon_momentum>=0.45)&&( muon_momentum<0.77))
      {
      bin_35->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.86)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.94)&&( muon_momentum>=0.77)&&( muon_momentum<1.28))
      {
      bin_36->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.86)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<0.94)&&( muon_momentum>=1.28)&&( muon_momentum<2.50))
      {
      bin_37->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.94)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<1)&&( muon_momentum>=0)&&( muon_momentum<0.30))
      {
      bin_38->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.94)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<1)&&( muon_momentum>=0.30)&&( muon_momentum<0.45))
      {
      bin_39->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.94)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<1)&&( muon_momentum>=0.45)&&( muon_momentum<0.77))
      {
      bin_40->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.94)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<1)&&( muon_momentum>=0.77)&&( muon_momentum<1.28))
      {
      bin_41->Fill(barcode->size(),weight);
      }
      else if (( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)>=0.94)&&( cos_theta(lepOut_Px, lepOut_Py,lepOut_Pz)<1)&&( muon_momentum>=1.28)&&( muon_momentum<2.50))
      {
      bin_42->Fill(barcode->size(),weight);
      }
      else 
      {
      //std::cout<<"dumped"<<std::endl;
      }
   }


//***********************************************************************************************************************************************//
//*************************************************Creating_the_smearing_vector******************************************************************//
//***********************************************************************************************************************************************//
string myText;
string data;
ifstream MyReadFile("smearing_matrix.txt");
int iter=1;
while (getline (MyReadFile,myText))
{ 
  stringstream ss(myText);
  
 while(std::getline(ss, data, ' '))
  {
  //std::cout<<" iter: "<<iter<<" and the data "<<stod(data)<<std::endl;
  smearing_matrix.push_back(stod(data));
  //iter=iter+1;
  }
}
//std::cout<<" matrix "<<smearing_matrix[0]<<" and the length of the smearing matrix is "<<smearing_matrix.size()<<std::endl;
data.clear();
myText.clear();
MyReadFile.close();


//***********************************************************************************************************************************************//
//*************************************************Scalling_the_histograms***********************************************************************//
//***********************************************************************************************************************************************//
double norm_GiBBU=TrueEnu_CCQE_GiBBU->Integral()+TrueEnu_CCMEC_GiBBU->Integral()+TrueEnu_CCRES_GiBBU->Integral()+TrueEnu_CCDIS_GiBBU->Integral(); 
double norm_GENIE=TrueEnu_CCQE_GENIE->Integral()+TrueEnu_CCMEC_GENIE->Integral()+TrueEnu_CCRES_GENIE->Integral()+TrueEnu_CCDIS_GENIE->Integral()+TrueEnu_CCCOH_GENIE->Integral();
double norm_GENIEnorw=TrueEnu_CCQE_GENIEnorw->Integral()+TrueEnu_CCMEC_GENIEnorw->Integral()+TrueEnu_CCRES_GENIEnorw->Integral()+TrueEnu_CCDIS_GENIEnorw->Integral()+TrueEnu_CCCOH_GENIEnorw->Integral();


//***********************************************************************************************************************************************//
//*************************************************Scalling_for_GENIE***********************************************************************//
//***********************************************************************************************************************************************//
TrueEnu_CCQE_GENIE->Scale(1/norm_GENIE);
TH1D* CCQE_GENIE=(TH1D*) TrueEnu_CCQE_GENIE->Clone("CCQE_GENIE");
std::cout<<" Entries_CCQE_GENIE is "<<TrueEnu_CCQE_GENIE->Integral()<<std::endl;

TrueEnu_CCMEC_GENIE->Scale(1/norm_GENIE);  
TH1D* CCMEC_GENIE=(TH1D*) TrueEnu_CCMEC_GENIE->Clone("CCMEC_GENIE");
std::cout<<" Entries_CCMEC_GENIE is "<<TrueEnu_CCMEC_GENIE->Integral()<<std::endl;

TrueEnu_CCRES_GENIE->Scale(1/norm_GENIE);
TH1D* CCRES_GENIE=(TH1D*) TrueEnu_CCRES_GENIE->Clone("CCRES_GENIE");
std::cout<<" Entries_CCRES_GENIE is "<<TrueEnu_CCRES_GENIE->Integral()<<std::endl;

TrueEnu_CCDIS_GENIE->Scale(1/norm_GENIE);
TH1D* CCDIS_GENIE=(TH1D*) TrueEnu_CCDIS_GENIE->Clone("CCDIS_GENIE");
std::cout<<" Entries_CCDIS_GENIE is "<<TrueEnu_CCDIS_GENIE->Integral()<<std::endl;

TrueEnu_CCCOH_GENIE->Scale(1/norm_GENIE);
TH1D* CCCOH_GENIE=(TH1D*) TrueEnu_CCCOH_GENIE->Clone("CCCOH_GENIE");
std::cout<<" Entries_CCCOH_GENIE is "<<TrueEnu_CCCOH_GENIE->Integral()<<std::endl;


//****************************************************NOT REWEIGHTED*****************************************************************************//
TrueEnu_CCMEC_GENIEnorw->Scale(1/norm_GENIEnorw);
TrueEnu_CCMEC_GENIEnorw->Scale(1/norm_GENIEnorw);  
TrueEnu_CCRES_GENIEnorw->Scale(1/norm_GENIEnorw);
TrueEnu_CCDIS_GENIEnorw->Scale(1/norm_GENIEnorw);
TrueEnu_CCCOH_GENIEnorw->Scale(1/norm_GENIEnorw);	



 					      

//***********************************************************************************************************************************************//
//*************************************************Scalling_for_GiBBU***********************************************************************//
//***********************************************************************************************************************************************//

TrueEnu_CCQE_GiBBU->Scale(1/norm_GiBBU);
TH1D* CCQE_GiBBU=(TH1D*) TrueEnu_CCQE_GiBBU->Clone("CCQE_GiBBU");
//std::cout<<" Entries_CCQE_GiBBU is "<<TrueEnu_CCQE_GiBBU->Integral()<<std::endl;
     
TrueEnu_CCMEC_GiBBU->Scale(1/norm_GiBBU);  
TH1D* CCMEC_GiBBU=(TH1D*) TrueEnu_CCMEC_GiBBU->Clone("CCMEC_GiBBU");
//std::cout<<" Entries_CCMEC_GiBBU is "<<TrueEnu_CCMEC_GiBBU->Integral()<<std::endl;

TrueEnu_CCRES_GiBBU->Scale(1/norm_GiBBU);
TH1D* CCRES_GiBBU=(TH1D*) TrueEnu_CCRES_GiBBU->Clone("CCRES_GiBBU");
//std::cout<<" Entries_CCRES_GiBBU is "<<TrueEnu_CCRES_GiBBU->Integral()<<std::endl;

TrueEnu_CCDIS_GiBBU->Scale(1/norm_GiBBU);
TH1D* CCDIS_GiBBU=(TH1D*) TrueEnu_CCDIS_GiBBU->Clone("CCDIS_GiBBU");
//std::cout<<" Entries_CCDIS_GiBBU is "<<TrueEnu_CCDIS_GiBBU->Integral()<<std::endl;

ninth->Scale(1/norm_GiBBU);


//***********************************************************************************************************************************************//
//******************************************Forming_the_reweighting_matrix_GENIE_REWEIGHTED********************************************//
//***********************************************************************************************************************************************//

for (int i=0;i<60;i++)
{
//std::cout<<" GiBBU "<<TrueEnu_CCQE_GiBBU->GetBinContent(i+1)<<" genie "<<TrueEnu_CCQE_GENIE->GetBinContent(i+1)<<std::endl;

//*******************************************************************CCQE************************************************************************//
	if (TrueEnu_CCQE_GiBBU->GetBinContent(i+1)==0)
	{
	 Reweighting_Gibbu[i][0]=TrueEnu_CCQE_GENIE->GetBinContent(i+1);
	}
		else
		{
	 	 Reweighting_Gibbu[i][0]=TrueEnu_CCQE_GENIE->GetBinContent(i+1)/TrueEnu_CCQE_GiBBU->GetBinContent(i+1);
		}
//******************************************************************CCMEC***********************************************************************//
	if (TrueEnu_CCMEC_GiBBU->GetBinContent(i+1)==0)
	{
	 Reweighting_Gibbu[i][1]=TrueEnu_CCMEC_GENIE->GetBinContent(i+1);
	}
		else
		{
	 	 Reweighting_Gibbu[i][1]=TrueEnu_CCMEC_GENIE->GetBinContent(i+1)/TrueEnu_CCMEC_GiBBU->GetBinContent(i+1);
		}
//******************************************************************CCRES***********************************************************************//
	if (TrueEnu_CCRES_GiBBU->GetBinContent(i+1)==0)
	{
	 Reweighting_Gibbu[i][2]=TrueEnu_CCRES_GENIE->GetBinContent(i+1);
	}
		else
		{
	 	 Reweighting_Gibbu[i][2]=TrueEnu_CCRES_GENIE->GetBinContent(i+1)/TrueEnu_CCRES_GiBBU->GetBinContent(i+1);
		}
//******************************************************************CCDIS***********************************************************************//
	if (TrueEnu_CCDIS_GiBBU->GetBinContent(i+1)==0)
	{
	 Reweighting_Gibbu[i][3]=TrueEnu_CCDIS_GENIE->GetBinContent(i+1);
	}
		else
		{
	 	 Reweighting_Gibbu[i][3]=TrueEnu_CCDIS_GENIE->GetBinContent(i+1)/TrueEnu_CCDIS_GiBBU->GetBinContent(i+1);
		}
//******************************************************************CCCOH***********************************************************************//
	if (TrueEnu_CCCOH_GiBBU->GetBinContent(i+1)==0)
	{
	 Reweighting_Gibbu[i][4]=TrueEnu_CCCOH_GENIE->GetBinContent(i+1);
	}
		else
		{
	 	 Reweighting_Gibbu[i][4]=TrueEnu_CCCOH_GENIE->GetBinContent(i+1)/TrueEnu_CCCOH_GiBBU->GetBinContent(i+1);
		}	

//std::cout<<" k is "<<k<<std::endl;
TrueEnu_CCQE_ratio->Fill(Reweighting_Gibbu[i][0]);
TrueEnu_CCMEC_ratio->Fill(Reweighting_Gibbu[i][1]);
TrueEnu_CCRES_ratio->Fill(Reweighting_Gibbu[i][2]);
TrueEnu_CCDIS_ratio->Fill(Reweighting_Gibbu[i][3]);
TrueEnu_CCCOH_ratio->Fill(Reweighting_Gibbu[i][4]);
/*std::cout<<" 1st_element"<<Reweighting_Gibbu[i][0]<<" i "<<i<<std::endl;
std::cout<<" 2nd_element"<<Reweighting_Gibbu[i][1]<<std::endl;
std::cout<<" 3rd_element"<<Reweighting_Gibbu[i][2]<<std::endl;
std::cout<<" 4th_element"<<Reweighting_Gibbu[i][3]<<std::endl;
std::cout<<" 5th_element"<<Reweighting_Gibbu[i][4]<<std::endl;*/
}



//***********************************************************************************************************************************************//
//******************************************Forming_the_reweighting_matrix_GENIE__not_reweighted********************************************//
//***********************************************************************************************************************************************//

for (int i=0;i<60;i++)
{
//std::cout<<" GiBBU "<<TrueEnu_CCQE_GiBBU->GetBinContent(i)<<" genie "<<TrueEnu_CCQE_GENIEnorw->GetBinContent(i)<<std::endl;
//******************************************************************CCQE***********************************************************************//
	if (TrueEnu_CCQE_GiBBU->GetBinContent(i+1)==0)
	{
	 Rewighting_Gibbu_Genie_norw[i][0]=TrueEnu_CCQE_GENIEnorw->GetBinContent(i+1);
	}
		else
		{
	 	 Rewighting_Gibbu_Genie_norw[i][0]=TrueEnu_CCQE_GENIEnorw->GetBinContent(i+1)/TrueEnu_CCQE_GiBBU->GetBinContent(i+1);
		}
//**************************************************************CCMEC***********************************************************************//	
	if (TrueEnu_CCMEC_GiBBU->GetBinContent(i+1)==0)
	{
	 Rewighting_Gibbu_Genie_norw[i][1]=TrueEnu_CCMEC_GENIEnorw->GetBinContent(i+1);
	}
		else
		{
	 	 Rewighting_Gibbu_Genie_norw[i][1]=TrueEnu_CCMEC_GENIEnorw->GetBinContent(i+1)/TrueEnu_CCMEC_GiBBU->GetBinContent(i+1);
		}
//***************************************************************CCRES***********************************************************************//	
	if (TrueEnu_CCRES_GiBBU->GetBinContent(i+1)==0)
	{
	 Rewighting_Gibbu_Genie_norw[i][2]=TrueEnu_CCRES_GENIEnorw->GetBinContent(i+1);
	}
		else
		{
	 	 Rewighting_Gibbu_Genie_norw[i][2]=TrueEnu_CCRES_GENIEnorw->GetBinContent(i)/TrueEnu_CCRES_GiBBU->GetBinContent(i);
		}
//********************************************************CCQE***********************************************************************//		
	if (TrueEnu_CCDIS_GiBBU->GetBinContent(i+1)==0)
	{
	 Rewighting_Gibbu_Genie_norw[i][3]=TrueEnu_CCDIS_GENIEnorw->GetBinContent(i);
	}
		else
		{
	 	 Rewighting_Gibbu_Genie_norw[i][3]=TrueEnu_CCDIS_GENIEnorw->GetBinContent(i+1)/TrueEnu_CCDIS_GiBBU->GetBinContent(i+1);
		}
//********************************************************CCQE***********************************************************************//		
	if (TrueEnu_CCCOH_GiBBU->GetBinContent(i+1)==0)
	{
	 Rewighting_Gibbu_Genie_norw[i][4]=TrueEnu_CCCOH_GENIEnorw->GetBinContent(i+1);
	}
		else
		{
	 	 Rewighting_Gibbu_Genie_norw[i][4]=TrueEnu_CCCOH_GENIEnorw->GetBinContent(i+1)/TrueEnu_CCCOH_GiBBU->GetBinContent(i+1);
		}	

/*std::cout<<" k is "<<k<<std::endl;
std::cout<<" 1st_element"<<Rewighting_Gibbu_Genie_norw[i][0]<<" i "<<i<<std::endl;
std::cout<<" 2nd_element"<<Rewighting_Gibbu_Genie_norw[i][1]<<std::endl;
std::cout<<" 3rd_element"<<Rewighting_Gibbu_Genie_norw[i][2]<<std::endl;
std::cout<<" 4th_element"<<Rewighting_Gibbu_Genie_norw[i][3]<<std::endl;
std::cout<<" 5th_element"<<Rewighting_Gibbu_Genie_norw[i][4]<<std::endl;*/
}



//***********************************************************************************************************************************************//
//*****************************************************************DRAWING***********************************************************************//
//***********************************************************************************************************************************************//
								    //CCQE//
TCanvas *c1= new TCanvas;
c1->Divide(1,2);
c1->cd(1);

TrueEnu_CCQE_GENIE->Draw();
TrueEnu_CCQE_GiBBU->Draw("SAME");
auto legend_1 = new TLegend(0.1,0.7,0.48,0.9);
legend_1->SetHeader("The Legend Title","C"); // option "C" allows to center the header
legend_1->AddEntry(TrueEnu_CCQE_GENIE,"","f");
legend_1->AddEntry(TrueEnu_CCQE_GiBBU,"","f");
legend_1->Draw();
c1->cd(2);
CCQE_GENIE->Divide(CCQE_GiBBU);
CCQE_GENIE->Draw("Hist");
   
								    //CCMEC//
TCanvas *c2= new TCanvas;
c2->Divide(1,2);
c2->cd(1);

TrueEnu_CCMEC_GENIE->Draw();
TrueEnu_CCMEC_GiBBU->Draw("SAME");
auto legend_2 = new TLegend(0.1,0.7,0.48,0.9);
legend_2->SetHeader("The Legend Title","C"); // option "C" allows to center the header
legend_2->AddEntry(TrueEnu_CCMEC_GENIE,"","f");
legend_2->AddEntry(TrueEnu_CCMEC_GiBBU,"","f");
legend_2->Draw();
c2->cd(2);
CCMEC_GENIE->Divide(CCMEC_GiBBU);
CCMEC_GENIE->Draw("Hist");

 								    //CCRES//
TCanvas *c3= new TCanvas;
c3->Divide(1,2);
c3->cd(1);

TrueEnu_CCRES_GENIE->Draw();
TrueEnu_CCRES_GiBBU->Draw("SAME");
auto legend_3 = new TLegend(0.1,0.7,0.48,0.9);
legend_3->SetHeader("The Legend Title","C"); // option "C" allows to center the header
legend_3->AddEntry(TrueEnu_CCRES_GENIE,"","f");
legend_3->AddEntry(TrueEnu_CCRES_GiBBU,"","f");
legend_3->Draw();
c3->cd(2);
CCRES_GENIE->Divide(CCRES_GiBBU);
CCRES_GENIE->Draw("Hist");  

 								    //CCDIS//
TCanvas *c4= new TCanvas;
c4->Divide(1,2);
c4->cd(1);

TrueEnu_CCDIS_GENIE->Draw();
TrueEnu_CCDIS_GiBBU->Draw("SAME");
auto legend_4 = new TLegend(0.1,0.7,0.48,0.9);
legend_4->SetHeader("The Legend Title","C"); // option "C" allows to center the header
legend_4->AddEntry(TrueEnu_CCDIS_GENIE,"","f");
legend_4->AddEntry(TrueEnu_CCDIS_GiBBU,"","f");
legend_4->Draw();
c4->cd(2);
CCDIS_GENIE->Divide(CCDIS_GiBBU);
CCDIS_GENIE->Draw("Hist");        

 								    //CCCOH//
TCanvas *c5= new TCanvas;
c5->SetGrid();

hprof_EnuCCQE_GiBBU->SetTitle("");
hprof_EnuCCQE_GiBBU->GetXaxis()->SetTitle("true neutrino energy [GeV]");
hprof_EnuCCQE_GiBBU->GetYaxis()->SetTitle("(true - reconstructed) neutrino energy [GeV]");
hprof_EnuCCQE_GiBBU->SetLineColor(kRed);
hprof_EnuCCQE_GiBBU->SetLineWidth(2);
hprof_EnuCCQE_GiBBU->SetMarkerColor(kRed);
hprof_EnuCCQE_GiBBU->SetMarkerStyle(20);
hprof_EnuCCQE_GiBBU->GetYaxis()->SetLimits(-0.6, 0.6);
hprof_EnuCCQE_GiBBU->GetYaxis()->SetRangeUser(-0.6, 0.6);
hprof_EnuCCQE_GiBBU->Draw("e1");

hprof_EnuRES_GiBBU->SetLineColor(kGreen);
hprof_EnuRES_GiBBU->SetLineWidth(2);
hprof_EnuRES_GiBBU->SetMarkerColor(kGreen);
hprof_EnuRES_GiBBU->SetMarkerStyle(20);
hprof_EnuRES_GiBBU->Draw("e1same");

hprof_EnuCalo_GiBBU->SetLineColor(kBlack);
hprof_EnuCalo_GiBBU->SetLineWidth(2);
hprof_EnuCalo_GiBBU->SetMarkerColor(kBlack);
hprof_EnuCalo_GiBBU->SetMarkerStyle(20);
hprof_EnuCalo_GiBBU->Draw("e1same");  

TLegend *legend_5 = new TLegend(0.50, 0.25, 0.9, 0.1);
  //legend_5 -> SetNColumns(2);
legend_5 -> AddEntry(hprof_EnuCCQE_GiBBU, "CCQE approach", "l");
legend_5 -> AddEntry(hprof_EnuCalo_GiBBU, "Calorimetry approach", "l");
legend_5 -> AddEntry(hprof_EnuRES_GiBBU, "Resonant approach", "l");
legend_5 -> Draw();

c5->Update();

///////////
  TCanvas *c6 = new TCanvas("c6", "c6", 900, 900);
  
  EnuDL_CCQE_GiBBUnorw-> SetFillColor(kRed);
  EnuDL_CCMEC_GiBBUnorw-> SetFillColor(kGreen);
  EnuDL_CCRES_GiBBUnorw-> SetFillColor(kYellow);
  EnuDL_CCDIS_GiBBUnorw-> SetFillColor(kBlue);
  //EnuDL_CCCOH_GiBBUnorw-> SetFillColor(kMagenta);
 
  THStack *EnuDL_GiBBUnorw = new THStack("EnuDL_GiBBUnorw","");
  EnuDL_GiBBUnorw-> Add(EnuDL_CCQE_GiBBUnorw);
  EnuDL_GiBBUnorw-> Add(EnuDL_CCMEC_GiBBUnorw);
  EnuDL_GiBBUnorw-> Add(EnuDL_CCRES_GiBBUnorw);
  EnuDL_GiBBUnorw-> Add(EnuDL_CCDIS_GiBBUnorw);
  //EnuDL_GiBBU-> Add(EnuDL_CCCOH_GiBBUnorw); 
  //truemuon_truemom_GiBBU-> SetMaximum(100);  
  EnuDL_GiBBUnorw-> Draw("hist");
  EnuDL_GiBBUnorw->GetXaxis()->SetTitle("EnuDL_reconstructed neutrino energy [GeV/c]");
  EnuDL_GiBBUnorw->GetYaxis()->SetTitle("number of events");

  TLegend *l6 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l6 -> AddEntry(EnuDL_CCQE_GiBBUnorw, "CCQE", "f");
  l6 -> AddEntry(EnuDL_CCMEC_GiBBUnorw, "CCMEC", "f");
  l6 -> AddEntry(EnuDL_CCRES_GiBBUnorw, "CCRES", "f");
  //l6 -> AddEntry(EnuDL_CCCOH_GiBBUnorw, "CC-Coh", "f");
  l6 -> AddEntry(EnuDL_CCDIS_GiBBUnorw, "CCDIS", "f");
  l6 -> Draw();

  c6->Update();
  
  ///////////
  TCanvas *c7 = new TCanvas("c7", "c7", 900, 900);
  
  EnuPanN_CCQE_GiBBUnorw-> SetFillColor(kRed);
  EnuPanN_CCMEC_GiBBUnorw-> SetFillColor(kGreen);
  EnuPanN_CCRES_GiBBUnorw-> SetFillColor(kYellow);
  EnuPanN_CCDIS_GiBBUnorw-> SetFillColor(kBlue);
  //EnuPanN_CCCOH_GiBBUnorw-> SetFillColor(kMagenta);
 
  THStack *EnuPanN_GiBBUnorw = new THStack("EnuPanN_GiBBUnorw","");
  EnuPanN_GiBBUnorw-> Add(EnuPanN_CCQE_GiBBUnorw);
  EnuPanN_GiBBUnorw-> Add(EnuPanN_CCMEC_GiBBUnorw);
  EnuPanN_GiBBUnorw-> Add(EnuPanN_CCRES_GiBBUnorw);
  EnuPanN_GiBBUnorw-> Add(EnuPanN_CCDIS_GiBBUnorw);
  //EnuPanN_GiBBU-> Add(EnuPanN_CCCOH_GiBBUnorw); 
  //truemuon_truemom_GiBBU-> SetMaximum(100);  
  EnuPanN_GiBBUnorw-> Draw("hist");
  EnuPanN_GiBBUnorw->GetXaxis()->SetTitle("EnuPanN_reconstructed neutrino energy [GeV/c]");
  EnuPanN_GiBBUnorw->GetYaxis()->SetTitle("number of events");

  TLegend *l7 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l7 -> AddEntry(EnuPanN_CCQE_GiBBUnorw, "CCQE", "f");
  l7 -> AddEntry(EnuPanN_CCMEC_GiBBUnorw, "CCMEC", "f");
  l7 -> AddEntry(EnuPanN_CCRES_GiBBUnorw, "CCRES", "f");
  //l7 -> AddEntry(EnuPanN_CCCOH_GiBBUnorw, "CC-Coh", "f");
  l7 -> AddEntry(EnuPanN_CCDIS_GiBBUnorw, "CCDIS", "f");
  l7 -> Draw();

  c7->Update();
  
  
  ////////
  TCanvas *c8 = new TCanvas("c8", "c8", 900, 900);
  
  EnuPan0_CCQE_GiBBUnorw-> SetFillColor(kRed);
  EnuPan0_CCMEC_GiBBUnorw-> SetFillColor(kGreen);
  EnuPan0_CCRES_GiBBUnorw-> SetFillColor(kYellow);
  EnuPan0_CCDIS_GiBBUnorw-> SetFillColor(kBlue);
  //EnuPan0_CCCOH_GiBBUnorw-> SetFillColor(kMagenta);
 
  THStack *EnuPan0_GiBBUnorw = new THStack("EnuPan0_GiBBUnorw","");
  EnuPan0_GiBBUnorw-> Add(EnuPan0_CCQE_GiBBUnorw);
  EnuPan0_GiBBUnorw-> Add(EnuPan0_CCMEC_GiBBUnorw);
  EnuPan0_GiBBUnorw-> Add(EnuPan0_CCRES_GiBBUnorw);
  EnuPan0_GiBBUnorw-> Add(EnuPan0_CCDIS_GiBBUnorw);
  //EnuPan0_GiBBU-> Add(EnuPan0_CCCOH_GiBBUnorw); 
  //truemuon_truemom_GiBBU-> SetMaximum(100);  
  EnuPan0_GiBBUnorw-> Draw("hist");
  EnuPan0_GiBBUnorw->GetXaxis()->SetTitle("EnuPan0_reconstructed neutrino energy [GeV/c]");
  EnuPan0_GiBBUnorw->GetYaxis()->SetTitle("number of events");

  TLegend *l8 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l8 -> AddEntry(EnuPan0_CCQE_GiBBUnorw, "CCQE", "f");
  l8 -> AddEntry(EnuPan0_CCMEC_GiBBUnorw, "CCMEC", "f");
  l8 -> AddEntry(EnuPan0_CCRES_GiBBUnorw, "CCRES", "f");
  //l8 -> AddEntry(EnuPan0_CCCOH_GiBBUnorw, "CC-Coh", "f");
  l8 -> AddEntry(EnuPan0_CCDIS_GiBBUnorw, "CCDIS", "f");
  l8 -> Draw();

  c8->Update();
  
  
  /////////
  TCanvas *c9 = new TCanvas("c9", "c9", 900, 900);
  
  EnuWC_CCQE_GiBBUnorw-> SetFillColor(kRed);
  EnuWC_CCMEC_GiBBUnorw-> SetFillColor(kGreen);
  EnuWC_CCRES_GiBBUnorw-> SetFillColor(kYellow);
  EnuWC_CCDIS_GiBBUnorw-> SetFillColor(kBlue);
  //EnuWC_CCCOH_GiBBUnorw-> SetFillColor(kMagenta);
 
  THStack *EnuWC_GiBBUnorw = new THStack("EnuWC_GiBBUnorw","");
  EnuWC_GiBBUnorw-> Add(EnuWC_CCQE_GiBBUnorw);
  EnuWC_GiBBUnorw-> Add(EnuWC_CCMEC_GiBBUnorw);
  EnuWC_GiBBUnorw-> Add(EnuWC_CCRES_GiBBUnorw);
  EnuWC_GiBBUnorw-> Add(EnuWC_CCDIS_GiBBUnorw);
  //EnuWC_GiBBU-> Add(EnuWC_CCCOH_GiBBUnorw); 
  //truemuon_truemom_GiBBU-> SetMaximum(100);  
  EnuWC_GiBBUnorw-> Draw("hist");
  EnuWC_GiBBUnorw->GetXaxis()->SetTitle("EnuWC_reconstructed neutrino energy [GeV/c]");
  EnuWC_GiBBUnorw->GetYaxis()->SetTitle("number of events");

  TLegend *l9 = new TLegend(0.5, 0.7, 0.9, 0.9);
  l9 -> AddEntry(EnuWC_CCQE_GiBBUnorw, "CCQE", "f");
  l9 -> AddEntry(EnuWC_CCMEC_GiBBUnorw, "CCMEC", "f");
  l9 -> AddEntry(EnuWC_CCRES_GiBBUnorw, "CCRES", "f");
  //l9 -> AddEntry(EnuWC_CCCOH_GiBBUnorw, "CC-Coh", "f");
  l9 -> AddEntry(EnuWC_CCDIS_GiBBUnorw, "CCDIS", "f");
  l9 -> Draw();

  c9->Update();
  
  /////////
  TCanvas *c10 = new TCanvas("c10","",900, 900); 

  c10->SetGrid();

  hprof_EnuDL_GiBBUnorw->SetTitle("");
  hprof_EnuDL_GiBBUnorw->GetXaxis()->SetTitle("true neutrino energy [GeV]");
  hprof_EnuDL_GiBBUnorw->GetYaxis()->SetTitle("(true - reconstructed) neutrino energy [GeV]");
  hprof_EnuDL_GiBBUnorw->SetLineColor(kRed);
  hprof_EnuDL_GiBBUnorw->SetLineWidth(2);
  hprof_EnuDL_GiBBUnorw->SetMarkerColor(kRed);
  hprof_EnuDL_GiBBUnorw->SetMarkerStyle(20);

  hprof_EnuDL_GiBBUnorw->GetYaxis()->SetLimits(-0.1, 0.5);
  hprof_EnuDL_GiBBUnorw->GetYaxis()->SetRangeUser(-0.1, 0.5);
  hprof_EnuDL_GiBBUnorw->Draw("e1");

  hprof_EnuPanN_GiBBUnorw->SetLineColor(kBlack);
  hprof_EnuPanN_GiBBUnorw->SetLineWidth(2);
  hprof_EnuPanN_GiBBUnorw->SetMarkerColor(kBlack);
  hprof_EnuPanN_GiBBUnorw->SetMarkerStyle(20);
  hprof_EnuPanN_GiBBUnorw->Draw("e1same");  

  hprof_EnuPan0_GiBBUnorw->SetLineColor(kGreen);
  hprof_EnuPan0_GiBBUnorw->SetLineWidth(2);
  hprof_EnuPan0_GiBBUnorw->SetMarkerColor(kGreen);
  hprof_EnuPan0_GiBBUnorw->SetMarkerStyle(20);
  hprof_EnuPan0_GiBBUnorw->Draw("e1same");  

  hprof_EnuWC_GiBBUnorw->SetLineColor(kCyan);
  hprof_EnuWC_GiBBUnorw->SetLineWidth(2);
  hprof_EnuWC_GiBBUnorw->SetMarkerColor(kCyan);
  hprof_EnuWC_GiBBUnorw->SetMarkerStyle(20);
  hprof_EnuWC_GiBBUnorw->Draw("e1same");  
  
  TLegend *l10 = new TLegend(0.50, 0.25, 0.9, 0.1);
  l10 -> AddEntry(hprof_EnuDL_GiBBUnorw, "DL approach", "l");
  l10 -> AddEntry(hprof_EnuPanN_GiBBUnorw, "Pandora N proton approach", "l");
  l10 -> AddEntry(hprof_EnuPan0_GiBBUnorw, "Pandora 0 proton approach", "l");
  l10 -> AddEntry(hprof_EnuWC_GiBBUnorw, "Wire Cell approach", "l");

  l10 -> Draw();
  c10->Update();





      
      
      
//***********************************************************************************************************************************************//
//******************************************Storing_the_truth_bins********************************************//
//***********************************************************************************************************************************************//
Truth_bins.push_back((bin_1->Integral())/10);
//std::cout<<" bin_1 "<<bin_1->Integral()<<std::endl;
Truth_bins.push_back((bin_2->Integral())/10);
//std::cout<<" bin_2 "<<bin_2->Integral()<<std::endl;
Truth_bins.push_back((bin_3->Integral())/10);
//std::cout<<" bin_3 "<<bin_3->Integral()<<std::endl;
Truth_bins.push_back((bin_4->Integral())/10);
//std::cout<<" bin_4 "<<bin_4->Integral()<<std::endl;
Truth_bins.push_back((bin_5->Integral())/10);
//std::cout<<" bin_5 "<<bin_5->Integral()<<std::endl;
Truth_bins.push_back((bin_6->Integral())/10);
Truth_bins.push_back((bin_7->Integral())/10);
Truth_bins.push_back((bin_8->Integral())/10);
Truth_bins.push_back((bin_9->Integral())/10);
Truth_bins.push_back((bin_10->Integral())/10);
Truth_bins.push_back((bin_11->Integral())/10);
Truth_bins.push_back((bin_12->Integral())/10);
Truth_bins.push_back((bin_13->Integral())/10);
Truth_bins.push_back((bin_14->Integral())/10);
Truth_bins.push_back((bin_15->Integral())/10);
Truth_bins.push_back((bin_16->Integral())/10);
Truth_bins.push_back((bin_17->Integral())/10);
Truth_bins.push_back((bin_18->Integral())/10);
Truth_bins.push_back((bin_19->Integral())/10);
Truth_bins.push_back((bin_20->Integral())/10);
Truth_bins.push_back((bin_21->Integral())/10);
Truth_bins.push_back((bin_22->Integral())/10);
Truth_bins.push_back((bin_23->Integral())/10);
Truth_bins.push_back((bin_24->Integral())/10);
Truth_bins.push_back((bin_25->Integral())/10);
Truth_bins.push_back((bin_26->Integral())/10);
Truth_bins.push_back((bin_27->Integral())/10);
Truth_bins.push_back((bin_28->Integral())/10);
Truth_bins.push_back((bin_29->Integral())/10);
Truth_bins.push_back((bin_30->Integral())/10);
Truth_bins.push_back((bin_31->Integral())/10);
Truth_bins.push_back((bin_32->Integral())/10);
Truth_bins.push_back((bin_33->Integral())/10);
Truth_bins.push_back((bin_34->Integral())/10);
Truth_bins.push_back((bin_35->Integral())/10);
Truth_bins.push_back((bin_36->Integral())/10);
Truth_bins.push_back((bin_37->Integral())/10);
Truth_bins.push_back((bin_38->Integral())/10);
Truth_bins.push_back((bin_39->Integral())/10);
Truth_bins.push_back((bin_40->Integral())/10);
Truth_bins.push_back((bin_41->Integral())/10);
Truth_bins.push_back((bin_42->Integral())/10);


//***********************************************************************************************************************************************//
//******************************************Printing_out_Truth_bins********************************************//
//***********************************************************************************************************************************************//
/*double check_prod=0;
for (int i=42;i<84;i++)
{
check_prod+=smearing_matrix[i]*Truth_bins[i-42];
std::cout<<" Truth_bin no. "<<i<<" and the content is "<<Truth_bins[i-42]<<std::endl;
}
std::cout<<" prod is "<<check_prod<<std::endl;*/


//***********************************************************************************************************************************************//
//******************************************Getting_the_Reconstructed_bins********************************************//
//***********************************************************************************************************************************************//
double prod=0;
for( int k=0;k<smearing_matrix.size();k++)
{
//***************************************************handling the case k=0***********************************************************************//
 if (k==0)
 {
   prod=smearing_matrix[0]*Truth_bins[0];
 } 
 //getting the bins from a particular row, multiplying with the Truth_bins, and adding the product to get the reconstructed_bins( is same as matrix multiplication)**********************************************************************************************************************************//  
 if ((k%42)!=0)
 {
  prod+=smearing_matrix[k]*Truth_bins[(k%42)];
 }
 //****************************************************handling the end case*********************************************************************//
 if (k==(smearing_matrix.size()-1))
 {
 Reconstructed_bins.push_back(prod);
 }
 //**************************************************here k mod 42==0 signifies that we are moving in to next row*********************************//
 if (((k%42)==0)&&(k!=0))
 {
  //Reconstructed_bins.push_back(0.042238*prod);
 // std::cout<<" prod "<<prod<<std::endl;
 Reconstructed_bins.push_back(prod);
  prod=0;
  prod=smearing_matrix[k]*Truth_bins[0];
 }
 
}
/*for (int i=0;i<42;i++)
{
std::cout<<" Reconstructed_elements "<<Reconstructed_bins[i]<<std::endl;
}*/
for (int i=0;i<42;i++)
{
//std::cout<<" Reconstructed_elements "<<Reconstructed_bins[i]<<std::endl;
//if (i==0)bins_1_5->SetBinContent(0,0);
if ((i>=0)&&(i<=4))bins_1_5->SetBinContent(i+1,Reconstructed_bins[i]);
if ((i>=5)&&(i<=9))bins_6_10->SetBinContent((i+2)%6,Reconstructed_bins[i]);
if ((i>=10)&&(i<=14))bins_11_15->SetBinContent((i+3)%6,Reconstructed_bins[i]);
if ((i>=15)&&(i<=18))bins_16_19->SetBinContent((i+1)%5,Reconstructed_bins[i]);
if ((i>=19)&&(i<=22))bins_20_23->SetBinContent((i+2)%5,Reconstructed_bins[i]);
if ((i>=23)&&(i<=26))bins_24_27->SetBinContent((i+3)%5,Reconstructed_bins[i]);
if ((i>=27)&&(i<=31))bins_28_32->SetBinContent((i+4)%6,Reconstructed_bins[i]);
if ((i>=32)&&(i<=36))bins_33_37->SetBinContent((i+5)%6,Reconstructed_bins[i]);
if ((i>=37)&&(i<=41))bins_38_42->SetBinContent((i+6)%6,Reconstructed_bins[i]);
}

   /*CCQE->SetFillColor(kRed);
   CCQE->SetMarkerStyle(20);
   //CCQE->Draw("Hist");
   //CCQE->Draw("E6");
   //v->SetParameters(CCQE->GetMaximum(),CCQE->GetMean(),CCQE->GetRMS());
   //CCQE->Draw("Hist");
   Cresonant->SetFillColor(kYellow);
   Cresonant->SetMarkerStyle(21);
   //Cresonant->Draw("Hist SAME C");
   pi_plus_plus_n_bkg->SetFillColor(kGreen);
   pi_plus_plus_n_bkg->SetMarkerStyle(22);
   //pi_plus_plus_n_bkg->Draw("Hist SAME C");
   pi_zero_plus_p_bkg->SetFillColor(kGray);
   pi_zero_plus_p_bkg->SetMarkerStyle(23);
   //pi_zero_plus_p_bkg->Draw("Hist SAME C");
   CCDIS->SetFillColor(kOrange);
   CCDIS->SetMarkerStyle(24);
   //CCDIS->Draw("Hist SAME C");
   CCQE_two_p_two_h->SetFillColor(kCyan);
   CCQE_two_p_two_h->SetMarkerStyle(25);
   //CCQE_two_p_two_h->Draw("Hist SAME C");
   Delta_two_p_two_h->SetFillColor(kBlue);
   Delta_two_p_two_h->SetMarkerStyle(26);
   //Delta_two_p_two_h->Draw("Hist SAME C");
   two_pion_bkg->SetFillColor(kViolet);
   two_pion_bkg->SetMarkerStyle(27);
   //two_pion_bkg->Draw("Hist SAME C");
   //ninth->Draw("Hist SAME C");
   //muon->SetFillColor(kRed);
   //highest_energy_proton->SetFillColor(kBlue);
   muon->SetMarkerStyle(27);
   highest_energy_proton->SetMarkerStyle(23);
   muon->Draw("");
   highest_energy_proton->Draw("SAME");
   Stack_em->Add(CCQE);
   Stack_em->Add(Cresonant);
   Stack_em->Add(pi_plus_plus_n_bkg);
   Stack_em->Add(pi_zero_plus_p_bkg);
   Stack_em->Add(CCDIS);
   Stack_em->Add(CCQE_two_p_two_h);
   Stack_em->Add(Delta_two_p_two_h);
   Stack_em->Add(two_pion_bkg);
   Stack_em->Draw("Hist");
   //CCQE_two_p_two_h->Draw("Hist");
   //Delta_two_p_two_h->Draw("Hist");
   auto legend = new TLegend(0.1,0.7,0.48,0.9);
   legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
   legend->AddEntry(CCQE,"","f");
   legend->AddEntry(Cresonant,"","f");
   legend->AddEntry(pi_plus_plus_n_bkg,"","f");
   legend->AddEntry(pi_zero_plus_p_bkg,"","f");
   legend->AddEntry(CCDIS,"","f");
   legend->AddEntry(CCQE_two_p_two_h,"","f");
   legend->AddEntry(Delta_two_p_two_h,"","f");
   legend->AddEntry(two_pion_bkg,"","f");
   legend->Draw();*/
   //Resolution_EnuCalo_GiBBU->Draw("colz");
//.............................................................Writing_in_a_file..............................................................//
//............................................................................................................................................//
//............................................................................................................................................//
TFile lite("clot.root", "RECREATE");
/*bin_1->Write();
bin_2->Write();
bin_3->Write();
bin_4->Write();
bin_5->Write();
bin_6->Write();
bin_7->Write();
bin_8->Write();
bin_9->Write();
bin_10->Write();
bin_11->Write();
bin_12->Write();
bin_13->Write();
bin_14->Write();
bin_15->Write();
bin_16->Write();
bin_17->Write();
bin_18->Write();
bin_19->Write();
bin_20->Write();
bin_21->Write();
bin_22->Write();
bin_23->Write();
bin_24->Write();
bin_25->Write();
bin_26->Write();
bin_27->Write();
bin_28->Write();
bin_29->Write();
bin_30->Write();
bin_31->Write();
bin_32->Write();
bin_33->Write();
bin_34->Write();
bin_35->Write();
bin_36->Write();
bin_37->Write();
bin_38->Write();
bin_39->Write();
bin_40->Write();
bin_41->Write();
bin_42->Write();
*/
bins_1_5->Write();
bins_6_10->Write();
bins_11_15->Write();
bins_16_19->Write();
bins_20_23->Write();
bins_24_27->Write();
bins_28_32->Write();
bins_33_37->Write();
bins_38_42->Write();
Resolution_EnuRes_GiBBU->Write();
TrueEnu_CCQE_GiBBU->Write();     
TrueEnu_CCMEC_GiBBU->Write();  
TrueEnu_CCRES_GiBBU->Write();
TrueEnu_CCDIS_GiBBU->Write();
TrueEnu_CCCOH_GiBBU->Write();
TrueEnu_CCQE_GENIE->Write();

//Stack_em->Write();
//lite.WriteObjectAny(&Reconstructed_bins,"std::vector<double>","Reconstructed_bins");
lite.WriteObject(&Reconstructed_bins,"Reconstructed_bins");
//lite.WriteObject(&Rewighting_Gibbu_Genie_norw,"std::array[double]","Rewighting_Gibbu_Genie_norw");
//lite.WriteObject(&Reweighting_Gibbu,"Reweighting_Gibbu");
lite.Close();
}


