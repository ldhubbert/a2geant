//Vincent Bruening summer project under supervision by Dave Hornidge
//Mount Allison University Summer 2021
//Integrating Compton And Two photon Spectrometer (CATS) into newest version of A2Geant4, with insipration taken from an older version.
//
//This simulation will alow us to find the detector efficiency of the real CATS, as well as showing if the results we are looking for are attainable.
//Weird Particle Behavious: try changing to a vacuum
//DevNotes:still need: PMT's (maybe), Confirm hole size with dave, lead housing (measurements in long one), check if data is accurate, see if SD needs to be deleted or needs more delcarations. edit A2CBOutput.cc, Check Alicia's document to see if there is anything missing.
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

fregionCATS = NULL;
fregionCATS = new G4Region("CATS");

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
fScint1Logic = NULL;
fScint2Logic = NULL;
fScint3Logic = NULL;
fScint4Logic = NULL;
fScint5Logic = NULL;
fScint6Logic = NULL;

fCoreVisSD = NULL;
fCoreSD = NULL;

fAnnulusPiece1VisSD = NULL;
fAnnulusPiece1SD = NULL;
fAnnulusPiece2VisSD = NULL;
fAnnulusPiece2SD = NULL;
fAnnulusPiece3VisSD = NULL;
fAnnulusPiece3SD = NULL;
fAnnulusPiece4VisSD = NULL;
fAnnulusPiece4SD = NULL;
fAnnulusPiece5VisSD = NULL;
fAnnulusPiece5SD = NULL;
fAnnulusPiece6VisSD = NULL;
fAnnulusPiece6SD = NULL;

fNistManager = G4NistManager::Instance();
}

//half-length of CATS
G4double z = 31.75*cm;

//destructor function
A2DetCATS::~A2DetCATS()  {
//Delete sensitive detector?
}
//Main Construction instructions
G4VPhysicalVolume* A2DetCATS::Construct(G4LogicalVolume *MotherLogical){ 
fMotherLogic=MotherLogical;

DefineMaterials();

//WorldBox
G4Box* airbox = new G4Box("pizzabox", 300*cm, 300*cm, 300*cm);
fMyLogic = new G4LogicalVolume(airbox, fNistManager->FindOrBuildMaterial("G4_AIR"),"pizzabox");
fMyLogic->SetVisAttributes(G4VisAttributes::Invisible); 

//Define our Construction functions
MakeCore();
MakeAnnulus();
MakeRing();
MakeScintillators();

fMyPhysi = new G4PVPlacement(0, G4ThreeVector(0,0,162*cm), fMyLogic, "A2DetCATS", fMotherLogic, false, 11, true);  
//MakeDetector();
//MakeSensitiveDetector();
return fMyPhysi;
}

//Function to make Materials
void A2DetCATS::DefineMaterials(){
//creating Lithium Carbonate for insulation ring around Sodium Iodide Core
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
G4Tubs *fCore = new G4Tubs("Core", 1*cm, 13.335*cm, z, 0.*deg, 360.*deg); 
fCoreLogic = new G4LogicalVolume(fCore, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"),"CoreLogic");
fCoreLogic->SetVisAttributes(col1);

//making core sensitive- integer "1" is because we are trying to make a single object sensitive
G4SDManager* SDman = G4SDManager::GetSDMpointer();
if(fIsInteractive){ 
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

//make annulus sensitive
G4SDManager* SDman1 = G4SDManager::GetSDMpointer();
if(fIsInteractive){
if(!fAnnulusPiece1VisSD)fAnnulusPiece1VisSD = new A2VisSD("AnnulusPiece1VisSD",1);
SDman1->AddNewDetector( fAnnulusPiece1VisSD );
fAnnulusPiece1Logic->SetSensitiveDetector(fAnnulusPiece1VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece1Logic);
}
else{
if(!fAnnulusPiece1SD)fAnnulusPiece1SD = new A2SD("AnnulusPiece1SD",1);
SDman1->AddNewDetector( fAnnulusPiece1SD );
fAnnulusPiece1Logic->SetSensitiveDetector(fAnnulusPiece1SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece1Logic);
}

G4SDManager* SDman2 = G4SDManager::GetSDMpointer();
if(fIsInteractive){
if(!fAnnulusPiece2VisSD)fAnnulusPiece2VisSD = new A2VisSD("AnnulusPiece2VisSD",1);
SDman2->AddNewDetector( fAnnulusPiece2VisSD );
fAnnulusPiece2Logic->SetSensitiveDetector(fAnnulusPiece2VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece2Logic);
}
else{
if(!fAnnulusPiece2SD)fAnnulusPiece2SD = new A2SD("AnnulusPiece2SD",1);
SDman2->AddNewDetector( fAnnulusPiece2SD );
fAnnulusPiece2Logic->SetSensitiveDetector(fAnnulusPiece2SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece2Logic);
}

G4SDManager* SDman3 = G4SDManager::GetSDMpointer();
if(fIsInteractive){
if(!fAnnulusPiece3VisSD)fAnnulusPiece3VisSD = new A2VisSD("AnnulusPiece3VisSD",1);
SDman3->AddNewDetector( fAnnulusPiece3VisSD );
fAnnulusPiece3Logic->SetSensitiveDetector(fAnnulusPiece3VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece3Logic);
}
else{
if(!fAnnulusPiece3SD)fAnnulusPiece3SD = new A2SD("AnnulusPiece3SD",1);
SDman3->AddNewDetector( fAnnulusPiece3SD );
fAnnulusPiece3Logic->SetSensitiveDetector(fAnnulusPiece3SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece3Logic);
}

G4SDManager* SDman4 = G4SDManager::GetSDMpointer();
if(fIsInteractive){
if(!fAnnulusPiece4VisSD)fAnnulusPiece4VisSD = new A2VisSD("AnnulusPiece4VisSD",1);
SDman4->AddNewDetector( fAnnulusPiece4VisSD );
fAnnulusPiece4Logic->SetSensitiveDetector(fAnnulusPiece4VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece4Logic);
}
else{
if(!fAnnulusPiece4SD)fAnnulusPiece4SD = new A2SD("AnnulusPiece4SD",1);
SDman4->AddNewDetector( fAnnulusPiece4SD );
fAnnulusPiece4Logic->SetSensitiveDetector(fAnnulusPiece4SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece4Logic);
}

G4SDManager* SDman5 = G4SDManager::GetSDMpointer();
if(fIsInteractive){
if(!fAnnulusPiece5VisSD)fAnnulusPiece5VisSD = new A2VisSD("AnnulusPiece5VisSD",1);
SDman5->AddNewDetector( fAnnulusPiece5VisSD );
fAnnulusPiece5Logic->SetSensitiveDetector(fAnnulusPiece5VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece5Logic);
}
else{
if(!fAnnulusPiece5SD)fAnnulusPiece5SD = new A2SD("AnnulusPiece5SD",1);
SDman5->AddNewDetector( fAnnulusPiece5SD );
fAnnulusPiece5Logic->SetSensitiveDetector(fAnnulusPiece5SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece5Logic);
}

G4SDManager* SDman6 = G4SDManager::GetSDMpointer();
if(fIsInteractive){
if(!fAnnulusPiece6VisSD)fAnnulusPiece6VisSD = new A2VisSD("AnnulusPiece6VisSD",1);
SDman6->AddNewDetector( fAnnulusPiece6VisSD );
fAnnulusPiece6Logic->SetSensitiveDetector(fAnnulusPiece6VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece6Logic);
}
else{
if(!fAnnulusPiece6SD)fAnnulusPiece6SD = new A2SD("AnnulusPiece6SD",1);
SDman6->AddNewDetector( fAnnulusPiece6SD );
fAnnulusPiece6Logic->SetSensitiveDetector(fAnnulusPiece6SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece6Logic);
}

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

//making scintillators to veto cosmics rays
void A2DetCATS::MakeScintillators(){

G4VisAttributes* col4 = new G4VisAttributes( G4Colour(1.0,1.0,0.0));
col4->SetVisibility(true);

G4Tubs *fScint1 = new G4Tubs("Scint1", 25.13*cm, 35.13*cm, z, 0.*deg, 72*deg);
fScint1Logic = new G4LogicalVolume(fScint1, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic1");
fScint1Logic->SetVisAttributes(col4);
fScint1Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint1Logic, "Scint1Placement", fMyLogic, 31, true);

G4Tubs *fScint2 = new G4Tubs("Scint2", 25.13*cm, 35.13*cm, z, 72.*deg, 72*deg);
fScint2Logic = new G4LogicalVolume(fScint2, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic2");
fScint2Logic->SetVisAttributes(col4);
fScint2Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint2Logic, "Scint2Placement", fMyLogic, 32, true);

G4Tubs *fScint3 = new G4Tubs("Scint3", 25.13*cm, 35.13*cm, z, 144.*deg, 72*deg);
fScint3Logic = new G4LogicalVolume(fScint3, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic3");
fScint3Logic->SetVisAttributes(col4);
fScint3Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint3Logic, "Scint3Placement", fMyLogic, 33, true);

G4Tubs *fScint4 = new G4Tubs("Scint4", 25.13*cm, 35.13*cm, z, 216.*deg, 72*deg);
fScint4Logic = new G4LogicalVolume(fScint4, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic4");
fScint4Logic->SetVisAttributes(col4);
fScint4Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint4Logic, "Scint4Placement", fMyLogic, 34, true);

G4Tubs *fScint5 = new G4Tubs("Scint5", 25.13*cm, 35.13*cm, z, 288.*deg, 72*deg);
fScint5Logic = new G4LogicalVolume(fScint5, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic5");
fScint5Logic->SetVisAttributes(col4);
fScint5Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint5Logic, "Scint5Placement", fMyLogic, 35, true);

G4Tubs *fScint6 = new G4Tubs("Scint6", 0*cm, 35.13*cm, 4.7*cm, 0.*deg, 360*deg);
fScint6Logic = new G4LogicalVolume(fScint6, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic6");
fScint6Logic->SetVisAttributes(col4);
fScint6Physi = new G4PVPlacement(0, G4ThreeVector(0,0,36.45*cm), fScint6Logic, "Scint6Placement", fMyLogic, 36, true); 
}






