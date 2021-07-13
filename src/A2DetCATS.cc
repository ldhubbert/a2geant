//Vincent Bruening summer project under supervision by Dave Hornidge
//Mount Allison University Summer 2021
//Integrating Compton And Two photon Spectrometer (CATS) into newest version of A2Geant4, with insipration taken from an older version.
//
//This simulation will alow us to find the detector efficiency of the real CATS, as well as showing if the results we are looking for are attainable.
//
//DevNotes:still need: PMT's (maybe), sensitive detectors must be made sensitive, Scintillators, entrance hole, lead housing
//
//SD notes: Right now, I'm trying to put fCore in the place of an integer. We are trying the method used for MWPC, but this may also require and integer input. check MWPC some more.
// fIsInteractive is declared in A2DetectorConstruction.cc.
//EXAMPLES: Good rotation matrix in A2DetCrystalBall.cc, sensitive detectors 66% in CB,
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

#include "G4SDManager.hh"

using namespace CLHEP;

//Constructor Begins
A2DetCATS::A2DetCATS(){ 

fregionCATS = NULL; //new, added for SD stuff
fregionCATS = new G4Region("CATS");
//fregionCATS = NULL; //new, added for SD stuff

fMotherLogic = NULL;
fMyLogic = NULL;
fMyPhysi = NULL;
fCoreLogic = NULL; 
fAnnulusPiece1Logic = NULL;
fAnnulusPiece2Logic = NULL;
fAnnulusPiece3Logic = NULL;
fAnnulusPiece4Logic = NULL;
fAnnulusPiece5Logic = NULL;
fAnnulusPiece6Logic = NULL;
fRingLogic = NULL;

fCoreVisSD = NULL;
fCoreSD = NULL;

fNistManager = G4NistManager::Instance();
//for sensitive detectors, will add later
//fCATSSD=0;
//fCATSVisSD=0;
}

//half-length of CATS
G4double z = 32.*cm;

//destructor function
A2DetCATS::~A2DetCATS()  {
//Delete sensitive detector here
}
//Main Construction instructions
G4VPhysicalVolume* A2DetCATS::Construct(G4LogicalVolume *MotherLogical){ 
fMotherLogic=MotherLogical;

DefineMaterials();

//WorldBox
G4Box* airbox = new G4Box("pizzabox", 300*cm, 300*cm, 300*cm);
fMyLogic = new G4LogicalVolume(airbox, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"),"pizzabox");
fMyLogic->SetVisAttributes(G4VisAttributes::Invisible); 

//Define our Construction functions
MakeCore();
MakeAnnulus();
MakeRing();

fMyPhysi = new G4PVPlacement(0, G4ThreeVector(0,0,162*cm), fMyLogic, "A2DetCATS", fMotherLogic, false, 11, true);
//MWPC: Here, they include two lines:
//MakeDetector();
//MakeSensitiveDetector();
return fMyPhysi;
}

//Function to make Materials
void A2DetCATS::DefineMaterials(){
//creating Lithium Carbonate for the ring around Sodium Iodide Core
G4double atm_num, a, density;
G4String name, symbol;
G4int ncomponents, natoms;

a=12.01*g/mole;
G4Element* elC = new G4Element(name="Carbon", symbol="C", atm_num=6., a);
a=16.00*g/mole;
G4Element* elO = new G4Element(name="Oxygen", symbol="O", atm_num=8., a);
a=6.94*g/mole;
G4Element* elLi = new G4Element(name="Lithium", symbol="Li", atm_num=3., a);

density=2.11*g/cm3;
G4Material* Li2CO3 = new G4Material(name="Li2CO3",density,ncomponents=3);
Li2CO3->AddElement(elC, natoms=1);
Li2CO3->AddElement(elO, natoms=3);
Li2CO3->AddElement(elLi, natoms=2);
}

//function to build sodium iodide CATS core
void A2DetCATS::MakeCore() {
G4VisAttributes* col1 = new G4VisAttributes( G4Colour(0.4,0.5,0.1));
col1->SetVisibility(true);

//Measurements of CATS Core. Technically two cylinders cemented together, but this if fine for now.
G4Tubs *fCore = new G4Tubs("Core", 0*cm, 13.335*cm, z, 0.*deg, 360.*deg);

fCoreLogic = new G4LogicalVolume(fCore, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"),"CoreLogic");
fCoreLogic->SetVisAttributes(col1);

G4SDManager* SDman = G4SDManager::GetSDMpointer();
if(fIsInteractive){ //Check TAPS and CB to see if fIsInteractive is declared. MWPC uses something else ...
if(!fCoreVisSD)fCoreVisSD = new A2VisSD("CoreVisSD",1);
SDman->AddNewDetector( fCoreVisSD );
fCoreLogic->SetSensitiveDetector(fCoreVisSD);
fregionCATS->AddRootLogicalVolume(fCoreLogic);
}
else{
if(!fCoreSD)fCoreSD = new A2SD("CoreSD",1);
SDman->AddNewDetector( fCoreSD );
fCoreLogic->SetSensitiveDetector(fCoreSD);
fregionCATS->AddRootLogicalVolume(fCoreLogic);
}

fCorePhysi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fCoreLogic, "CorePlacement", fMyLogic, 10, true);
}

//function to make Sodium Iodide annulus around the core of our detector
void A2DetCATS::MakeAnnulus(){

G4VisAttributes* col2 = new G4VisAttributes( G4Colour(0.0,1.0,1.0));
col2->SetVisibility(true);

G4VisAttributes* col3 = new G4VisAttributes( G4Colour(1.0,0,0));
col3->SetVisibility(true);

G4Tubs *fAnnulusPiece1 = new G4Tubs("AnnulusPiece1", 13.335*cm, 24.13*cm, z, 0.*deg, 60*deg);
fAnnulusPiece1Logic = new G4LogicalVolume(fAnnulusPiece1, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic1");
fAnnulusPiece1Logic->SetVisAttributes(col2);
fAnnulusPiece1Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece1Logic, "AnnulusPlacement1", fMyLogic, 21, true);

G4Tubs *fAnnulusPiece2 = new G4Tubs("AnnulusPiece2", 13.335*cm, 24.13*cm, z, 60.*deg, 60*deg);
fAnnulusPiece2Logic = new G4LogicalVolume(fAnnulusPiece2, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic2");
fAnnulusPiece2Logic->SetVisAttributes(col3);
fAnnulusPiece2Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece2Logic, "AnnulusPlacement2", fMyLogic, 22, true);

G4Tubs *fAnnulusPiece3 = new G4Tubs("AnnulusPiec3", 13.335*cm, 24.13*cm, z, 120.*deg, 60*deg);
fAnnulusPiece3Logic = new G4LogicalVolume(fAnnulusPiece3, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic3");
fAnnulusPiece3Logic->SetVisAttributes(col2);
fAnnulusPiece3Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece3Logic, "AnnulusPlacement3", fMyLogic, 23, true);

G4Tubs *fAnnulusPiece4 = new G4Tubs("AnnulusPiece4", 13.335*cm, 24.13*cm, z, 180.*deg, 60*deg);
fAnnulusPiece4Logic = new G4LogicalVolume(fAnnulusPiece4, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic4");
fAnnulusPiece4Logic->SetVisAttributes(col3);
fAnnulusPiece4Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece4Logic, "AnnulusPlacement4", fMyLogic, 24, true);

G4Tubs *fAnnulusPiece5 = new G4Tubs("AnnulusPiece5", 13.335*cm, 24.13*cm, z, 240.*deg, 60*deg);
fAnnulusPiece5Logic = new G4LogicalVolume(fAnnulusPiece5, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic5");
fAnnulusPiece5Logic->SetVisAttributes(col2);
fAnnulusPiece5Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece5Logic, "AnnulusPlacement5", fMyLogic, 25, true);

G4Tubs *fAnnulusPiece6 = new G4Tubs("AnnulusPiece6", 13.335*cm, 24.13*cm, z, 300.*deg, 60*deg);
fAnnulusPiece6Logic = new G4LogicalVolume(fAnnulusPiece6, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic6");
fAnnulusPiece6Logic->SetVisAttributes(col3);
fAnnulusPiece6Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece6Logic, "AnnulusPlacement6", fMyLogic, 26, true);
}

//function to create lithium carbonate ring around sodium iodide
void A2DetCATS::MakeRing(){

G4VisAttributes* col4 = new G4VisAttributes( G4Colour(1.0,0.0,1.0));
col4->SetVisibility(true);

G4Tubs *fRing = new G4Tubs("Ring", 24.13*cm, 25.13*cm, z, 0.*deg, 360.*deg);
fRingLogic = new G4LogicalVolume(fRing, fNistManager->FindOrBuildMaterial("Li2CO3"), "RingLogic");
fRingLogic->SetVisAttributes(col4);
fRingPhysi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fRingLogic, "RingPlacement", fMyLogic, 27, true);
}



