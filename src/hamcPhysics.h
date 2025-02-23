#ifndef ROOT_hamcPhysics
#define ROOT_hamcPhysics

//  hamcPhysics   -- abstract base class for the physics of an experiment.
//  d. Jaunzeikare, R. Michaels  May 2008

#include "Rtypes.h"
#include <vector>
#include <string>
#include <map>

class hamcExpt;
class hamcEloss;   
class hamcKine;   

class hamcPhysics {

  public:

     hamcPhysics();
     virtual ~hamcPhysics()=0;   // abstract class

     std::string GetName() const { return phy_name; };
     std::string GetProcess() const { return scatt_process; };
     virtual Int_t Init(hamcExpt* expt);
     virtual Int_t Radiate(hamcExpt* expt);     // Radiation at target
     virtual Int_t Generate(hamcExpt* expt);    // Generate crsec and asy.
 // The index "i" may point to a model or parameter set.
     virtual Float_t GetCrossSection(Int_t i=0) const { return crsec; };
     virtual Float_t GetAsymmetry(Int_t i=0) const { return asymmetry; };
     virtual Int_t NumberModels() const { return num_models; };
     hamcKine* kine;
     hamcEloss* eloss;


  protected:

     virtual Int_t CrossSection();    
     virtual Int_t Asymmetry();
     virtual Int_t Drate();

     Float_t tlen,tgtM;  // target length (RL), target mass (GeV)

     Bool_t do_radiate;
     Bool_t did_init;
     Float_t crsec, asymmetry;
     Float_t energy, theta_rad, theta_deg, phi_rad, phi_deg;
     Float_t dE_IntBrehm, dE_ExtBrehm, dE_Ionization;
     Int_t num_models;
     Float_t drate;

     std::string phy_name;
     std::string scatt_process;

  private: 


     hamcPhysics(const hamcPhysics& phys);
     hamcPhysics& operator=(const hamcPhysics& phys);


#ifndef NODICT
ClassDef (hamcPhysics, 0)   // physics
#endif

};

#endif



   
