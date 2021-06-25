//Vincent Bruening summer project under supervision by Dave Hornidge
//Mount Allison University Summer 2021
//Integrating Compton And Two photon Spectrometer (CATS) into newest version of A2Geant4, with insipration taken from an older version.
//
#include "A2DetCATS.hh"
#include "A2DetPizza.hh"

#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Colour.hh"

#include "A2SD.hh"
#include "A2VisSD.hh"
#include "A2Utils.hh"

// removed detector messenger and construction

using namespace CLHEP;

//Constructor Begins
A2DetCATS::A2DetCATS(){ 

//Initiate all pointers to NULL.
fMotherLogic = NULL;
fMyLogic = NULL;
fMyPhysi = NULL;
fVesselLogic = NULL; 

fNistManager = G4NistManager::Instance();
//for sensitive detectors, will add later
//fCATSSD=0;
//fCATSVisSD=0;
}

//destructor function
A2DetCATS::~A2DetCATS()  {
//Delete sensitive detector here
}

//Main Construction instructions
G4VPhysicalVolume* A2DetCATS::Construct(G4LogicalVolume *MotherLogical){ //logic 

  fMotherLogic=MotherLogical;//=MotherLogic? Not sure if it makes a difference.

//other functions
DefineMaterials();
MakeVessel();

G4VisAttributes* col0 = new G4VisAttributes( G4Colour(0.8,0.1,0.3));
col0->SetVisibility(true);

//MyLogic
G4Box* airbox = new G4Box("pizzabox", 300*cm, 300*cm, 300*cm);
fMyLogic = new G4LogicalVolume(airbox, fNistManager->FindOrBuildMaterial("G4_AIR"),"pizzabox");
//fMyLogic->SetVisAttributes(col0); //We can get fMyLogic to appear in red.
fMyLogic->SetVisAttributes(G4VisAttributes::Invisible); 
fMyPhysi = new G4PVPlacement(0, G4ThreeVector(0,0,162*cm), fMyLogic, "A2DetCATS", fMotherLogic, false, 11, true);

return fMyPhysi;
}

//Function to make Materials, must be called in Construct()
void A2DetCATS::DefineMaterials(){
}

//function to build vessel geometry
void A2DetCATS::MakeVessel() {

G4VisAttributes* col1 = new G4VisAttributes( G4Colour(0.4,0.5,0.1));
col1->SetVisibility(true);
//define a sold cylinder, this will be our CATS for now
G4Tubs *fVessel = new G4Tubs("Vessel", 0*cm, 20.*cm, 10.*cm, 0.*deg, 360.*deg);

//Make it a logical volume
fVesselLogic = new G4LogicalVolume(fVessel, fNistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL"),"VesselLogic");

//next define how it looks
fVesselLogic->SetVisAttributes(col1);
//here we give the logical volume a placement
fVesselPhysi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fVesselLogic, "VesselPlacement", fMyLogic, 10, true);
}//End of MakeVessel


