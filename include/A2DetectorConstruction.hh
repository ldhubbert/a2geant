
#ifndef A2DetectorConstruction_h
#define A2DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4NistManager.hh"
#include "G4ThreeVector.hh"
//#include "G4String.hh"

#include "A2Detector.hh"
#include "A2DetCrystalBall.hh"
#include "A2DetTAPS.hh"
#include "A2DetTOF.hh"
#include "A2Target.hh"
#include "A2DetMWPC.hh"
#include "A2DetCherenkov.hh"
#include "A2DetPizza.hh"
#include "A2DetCATS.hh" //edit

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class A2DetectorMessenger;
class G4Tubs;

class A2DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    A2DetectorConstruction(G4String detSet="macros/DetectorSetup.mac");
   ~A2DetectorConstruction();

  public:
   
     G4VPhysicalVolume* Construct();

     void UpdateGeometry();
     void DefineMaterials();
  void SetIsInteractive(G4int is){fIsInteractive=is;}
     
  //Set functions used by messenger class
  void SetUseCB(G4int use){fUseCB=use;}
  void SetUseTAPS(G4int use){fUseTAPS=use;}
  void SetUsePID(G4int use){fUsePID=use;}
  void SetUseMWPC(G4int use){fUseMWPC=use;}
  void SetUseCherenkov(G4int use){fUseCherenkov=use;}
  void SetUsePizza(G4int use){fUsePizza=use;}
  void SetUseCATS(G4int use){fUseCATS=use;}  //edit


  G4int GetUseMWPC() const { return fUseMWPC; }

  void SetUseTarget(G4String use){fUseTarget=use;}
  void SetTargetMaterial(G4String mat){fTargetMaterial=G4NistManager::Instance()->FindOrBuildMaterial(mat);}
  void SetDetectorSetup(G4String ds){fDetectorSetup=ds;}
  G4Material* GetTargetMaterial(){return fTargetMaterial;}
  void SetTargetLength(G4double zz){fTargetLength=zz;}
  void SetTargetRadius(G4double r){fTargetRadius=r;}
  void SetTargetZ(G4double zz){fTargetZ=zz;}
  void SetTargetMagneticCoils(G4String &type) { fTypeMagneticCoils = type; }
  void SetTargetMagneticFieldMap(G4String &name) { fNameFileFieldMap = name; }
  void SetHemiGap(G4ThreeVector zz){fHemiGap=zz;}
  void SetCBCrystGeometry(G4String geo) { fCBCrystGeometry = geo; }
  void SetTAPSFile(G4String file){fTAPSSetupFile=file;}
  void SetTAPSZ(G4double zz){fTAPSZ=zz;}
  void SetTAPSN(G4int nn){fTAPSN=nn;}
  void SetTAPSPbWO4Rings(G4int nn){fNPbWO4=nn;}
  void SetPIDZ(G4double zz){fPIDZ=zz;}
  void SetPIDRotation(G4double rot){fPIDRotation=rot;}
  void SetPizzaZ(G4double zz){fPizzaZ=zz;}

  A2Target* GetTarget(){return fTarget;}

  G4int GetNToFbars(){
    if(fUseTOF) return fTOF->GetNToF();
    else return 0;
  }
  void SetUseTOF(G4int use){fUseTOF=use;}
  void SetTOFFile(G4String file){fTOFparFile=file;}

public:
  
     
  const G4VPhysicalVolume* GetWorld() {return fWorldPhysi;}
                 
  private:
  G4int fIsInteractive;   // batch(0) or interactive(1) mode
     
  //G4Material*        fMaterialDefault;
           
  G4Box*             fWorldSolid;    //pointer to the solid World 
  G4LogicalVolume*   fWorldLogic;    //pointer to the logical World
  G4VPhysicalVolume* fWorldPhysi;    //pointer to the physical World
  
  
  A2DetCrystalBall* fCrystalBall;   //CrystalBall detector
  A2DetTAPS* fTAPS;   //TAPS detector
  A2Detector* fPID;   //PID detector
  A2DetMWPC* fMWPC;   //MWPC detector
  A2DetTOF* fTOF;   //MWPC detector
  A2DetCherenkov* fCherenkov; //Cherenkov detector
  A2DetPizza* fPizza; // Pizza detector
  A2DetCATS* fCATS; //CATS detector , edit

  G4ThreeVector fHemiGap;
  G4String fCBCrystGeometry;
  A2Target* fTarget;
  G4Material* fTargetMaterial;
  G4double fTargetLength;
  G4double fTargetRadius;
  G4double fTargetZ;
  G4String fTypeMagneticCoils;
  G4String fNameFileFieldMap;

  G4String fDetectorSetup; //Configuration macro name
  A2DetectorMessenger* fDetMessenger;  //pointer to the Messenger
  
  //build detctor flags, should be set by DetectorSetup.mac 
  //or changed interactively eg, /A2/det/useTAPS 0, then,  /A2/det/update
  G4int fUseCB;   //Build the Crystal Ball
  G4int fUseTAPS;   //Build TAPS
  G4int fUsePID;   //Build the PID
  G4int fUseMWPC;  //Build the Wire Chambers
  G4int fUseTOF;  //Build the TOF wall
  G4int fUseCherenkov; //Build the Cherenkov
  G4int fUsePizza; //Build the Pizza detector
  G4int fUseCATS; //Build the CATS detector, edit

  G4String fTOFparFile; //TOF setup configuration
  
  G4String fUseTarget; // target identifier
 
 //taps setup
  G4String fTAPSSetupFile; 
  G4int fTAPSN; //number of active taps crystals
  G4double fTAPSZ; // distance from taps to the target.
  G4int fNPbWO4; //number of PbWO4 rings (actually equivalent BaF2 rings)

  //PID setup
  G4double fPIDZ;
  G4double fPIDRotation;

  // Pizza setup
  G4double fPizzaZ;

  //CATS setup
 // G4double fCATS; // I dont think this part is necessary
private:
    
   
};


#endif

