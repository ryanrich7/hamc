#ifndef ROOT_hamcPhyPREX
#define ROOT_hamcPhyPREX

//  hamcPhyPREX   -- class for the PREX physics
//  D. Jaunzeikare, R. Michaels  May 2008

#include "Rtypes.h"
#include "hamcPhysics.h"
#include "hamcTransMat.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

#define NOMODEL  0
#define HORPB    1
#define HORCA40  2
#define HORCA48  3
#define HORSN    4
#define SI       5
#define NL3P06   6
#define SLY4     7
#define SIII     8
#define FSU      9
#define NL3     10
#define NL3M05  11
#define ZIDUPB  12

using namespace std;

class hamcExpt;

class hamcPhyPREX : public hamcPhysics {

  public:

     hamcPhyPREX();
     virtual ~hamcPhyPREX(); 

     Int_t Init(hamcExpt* expt);
     Int_t Generate(hamcExpt* expt);    // Generate crsec and asy.

// The index "i" may point to a model or parameter set.
     Float_t GetCrossSection(Int_t i=0) const;
     Float_t GetAsymmetry(Int_t i=0) const;
     /* Reads CrossSection and Asymmetry from Horowitz tables and saves in class variables*/
     Int_t CrossSection(Float_t energy, Float_t angle, Int_t stretch=0);    
     Int_t Asymmetry(Float_t energy, Float_t angle, Int_t stretch=0);
     Int_t Drate(Float_t anum, Float_t tdens,Float_t tlen, Float_t crsec);

    /*Calculates CrossSection and Asymmetry using formulas*/
     Float_t CalculateCrossSection(Int_t nuc, Float_t energy, Float_t angle);
     Float_t CalculateAsymmetry(Int_t nuc);  // Born asymmetry.
     Float_t CalculateDrate(Float_t anum, Float_t tdens,Float_t tlen, Float_t crsec);
     Int_t SetModel(Int_t modeln);  // To set the model used

  protected:

  private: 

     Int_t LoadFiles();
     Int_t LoadHorowitzTable(vector<vector<Float_t> >&, vector<vector<Float_t> >&,Int_t stretch = 0);
     Int_t LoadFormFactorTable(); // qsq row, ffsq row
     vector<Float_t> qsq_row, ffsq_row;

     Int_t LoadC12FormFactorTable(); // qsq row, ffsq row
     vector<Float_t> c12qsq_row, c12ffsq_row;  // same for C12

     /*Helper methods*/
     Int_t FindAngleIndex(Float_t);
     Int_t FindEnergyIndex(Float_t);
     Float_t Interpolate(Float_t min, Float_t max, Float_t mid, Float_t val1, Float_t val2);
     Float_t InterpAsym(Float_t ene, Float_t angle_rad);
     void PrintAsymTable();

     hamcQuad *quad1, *quad2;

     Float_t qsq;
     Float_t asy0, asy1;  // unstretched and streteched R_N asymmetries 
     
     Float_t drate;
     Bool_t didWriteAngle;

     // Now considering 8 models.
     // The first one is "old" (~10 years)

     // Model        Rn(fm)    A(850 MeV, 6 deg)  A(1050 MeV, 5deg)
     // 1. horpb.dat and horpb1.dat
     // 2. SI          5.492   .731               .753
     // 3. NL3p06      5.604   .700               .721
     // 4. SLY4        5.618   .698               .719
     // 5. SIII        5.646   .683               .702
     // 6. FSU         5.679   .677               .695
     // 7. NL3         5.740   .655               .672
     // 8. NL3m05      5.851   .617               .631
     
     Int_t whichmodel;

     Bool_t didinit;

     hamcPhyPREX(const hamcPhyPREX& phys);
     hamcPhyPREX& operator=(const hamcPhyPREX& phys);

     /*3D vectors to save data from Horowitz tables*/
     vector< vector< vector<Float_t> > > crsc_tables;   
     vector< vector< vector<Float_t> > >asymmetry_tables;

     vector<Float_t> angle_row;  //to save the angle values of Horowitch table
     vector<Float_t> energy_row; //to save the energy values 

     TH1F *histphi; 
     TH1F *histene;
     TH1F *histprob;
     TH2F *histrast;
     TH1F *histmsc;
     TH1F *histinacc;
     TH1F *histz1a, *histz1b, *histz1c, *histz1d, *histz1e, *histz1f;
     TH1F *histz2a, *histz2b, *histz2c, *histz2d, *histz2e, *histz2f;
     TH1F *histz3a, *histz3b, *histz3c, *histz3d, *histz3e, *histz3f;
     TH1F *histz4a, *histz4b, *histz4c, *histz4d, *histz4e, *histz4f;
     TH1F *histz5a, *histz5b;
     TH1F *histang1,*histang2,*histang3,*histang4,*histang5, *histang0;
     TH1F *histang6,*histang7;
     TH1F *hpph1,*hpph2,*hpph3,*hpph4,*hpph6,*hd1;
     TH1F *hfom1,*hfom2,*hfom3,*hfom4,*hfom5, *hfom6;
     TH1F *hfom7, *hfom8, *hfom9, *hfom10, *hfom11, *hfom12, *hfom13;
     TH1F *hfom14, *hfom15, *hfom16, *hfom17, *hfom18, *hfom19, *hfom20;
     TH2F *hpph5;
     static const Int_t histo_test=0; // to test(1) or not(0) this code
     static const Int_t accept_test=0; // to test(1) or not(0) this acceptance
     static const Int_t quick_feasibility=0; 
     static const Int_t quick_check=0; 
     static const Int_t quick_fom=0; 
     static const Int_t power_integ=0; 
     static const Int_t neutron_power=0; 
     static const Int_t check_ms_1D=0;

#ifndef NODICT
ClassDef (hamcPhyPREX, 0)   // PREX physics
#endif

};

#endif
