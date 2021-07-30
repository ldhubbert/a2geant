//Vincent Bruening summer project under supervision by Dr. David Hornidge
//Mount Allison University Summer 2021
//Integrating Compton And Two photon Spectrometer (CATS) into newest version of A2Geant4
//DevNotes:still need: Confirm hole size with dave, look at some histograms, see integration of sensitive detectors and A2CBOutput and figure out why histograms are not filling. PMTs? Maybe delete SD's?
//With no detector and the beam set to hit the face of CATS, reactions look pretty good! One thing we could try- write a macro to shoot beam at CATS and see what the output histograms are.
//In an attempt to fix output, I added "==1" after FisInteractice.
//Another thing to try: changing phi offset in EvGen.in
//Look at:MWPC
#include "A2DetCATS.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
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
//new!
fCATSSD = NULL;
fCATSVisSD = NULL;
fNistManager = G4NistManager::Instance();
}

//half-length of CATS. Made it a variable for ease of adjustment.
G4double z = 31.75*cm;

//destructor function
A2DetCATS::~A2DetCATS()  {
if (fregionCATS) delete fregionCATS;
if (fCATSSD) delete fCATSSD;
if (fCATSVisSD) delete fCATSVisSD;
}

//Main Construction instructions
G4VPhysicalVolume* A2DetCATS::Construct(G4LogicalVolume *MotherLogical){ 
fMotherLogic=MotherLogical;

//WorldBox
G4Box* airbox = new G4Box("pizzabox", 300*cm, 300*cm, 300*cm);
fMyLogic = new G4LogicalVolume(airbox, fNistManager->FindOrBuildMaterial("G4_AIR"),"pizzabox");
fMyLogic->SetVisAttributes(G4VisAttributes::Invisible); 

//Define our Construction functions
MakeCore();
MakeAnnulus();
MakeRing();
MakeScintillators();
MakeSensitiveDetectors();

fMyPhysi = new G4PVPlacement(0, G4ThreeVector(0,0,162*cm), fMyLogic, "A2DetCATS", fMotherLogic, false, 1, true);  
return fMyPhysi;
}

//function to build sodium iodide CATS core
void A2DetCATS::MakeCore() {
G4VisAttributes* col1 = new G4VisAttributes( G4Colour(0.4,0.5,0.1));
col1->SetVisibility(true);

//Measurements of CATS Core. Technically two cylinders cemented together, but this if fine for now.
G4Tubs *fCore = new G4Tubs("Core", 1*cm, 13.335*cm, z, 0.*deg, 360.*deg); 
fCoreLogic = new G4LogicalVolume(fCore, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"),"CoreLogic");
fCoreLogic->SetVisAttributes(col1);
fCorePhysi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fCoreLogic, "CorePlacement", fMyLogic, 2, true);
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
fAnnulusPiece1Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece1Logic, "AnnulusPlacement1", fMyLogic, 3, true);

G4Tubs *fAnnulusPiece2 = new G4Tubs("AnnulusPiece2", 13.335*cm, 24.13*cm, z, 60.*deg, 60*deg);
fAnnulusPiece2Logic = new G4LogicalVolume(fAnnulusPiece2, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic2");
fAnnulusPiece2Logic->SetVisAttributes(col3);
fAnnulusPiece2Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece2Logic, "AnnulusPlacement2", fMyLogic, 4, true);

G4Tubs *fAnnulusPiece3 = new G4Tubs("AnnulusPiec3", 13.335*cm, 24.13*cm, z, 120.*deg, 60*deg);
fAnnulusPiece3Logic = new G4LogicalVolume(fAnnulusPiece3, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic3");
fAnnulusPiece3Logic->SetVisAttributes(col2);
fAnnulusPiece3Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece3Logic, "AnnulusPlacement3", fMyLogic, 5, true);

G4Tubs *fAnnulusPiece4 = new G4Tubs("AnnulusPiece4", 13.335*cm, 24.13*cm, z, 180.*deg, 60*deg);
fAnnulusPiece4Logic = new G4LogicalVolume(fAnnulusPiece4, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic4");
fAnnulusPiece4Logic->SetVisAttributes(col3);
fAnnulusPiece4Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece4Logic, "AnnulusPlacement4", fMyLogic, 6, true);

G4Tubs *fAnnulusPiece5 = new G4Tubs("AnnulusPiece5", 13.335*cm, 24.13*cm, z, 240.*deg, 60*deg);
fAnnulusPiece5Logic = new G4LogicalVolume(fAnnulusPiece5, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic5");
fAnnulusPiece5Logic->SetVisAttributes(col2);
fAnnulusPiece5Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece5Logic, "AnnulusPlacement5", fMyLogic, 7, true);

G4Tubs *fAnnulusPiece6 = new G4Tubs("AnnulusPiece6", 13.335*cm, 24.13*cm, z, 300.*deg, 60*deg);
fAnnulusPiece6Logic = new G4LogicalVolume(fAnnulusPiece6, fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE"), "AnnulusPieceLogic6");
fAnnulusPiece6Logic->SetVisAttributes(col3);
fAnnulusPiece6Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fAnnulusPiece6Logic, "AnnulusPlacement6", fMyLogic, 8, true);
}

//function to create lithium carbonate ring around sodium iodide
void A2DetCATS::MakeRing(){

G4VisAttributes* col4 = new G4VisAttributes( G4Colour(1.0,0.0,1.0));
col4->SetVisibility(true);

G4Tubs *fRing = new G4Tubs("Ring", 24.13*cm, 25.13*cm, z, 0.*deg, 360.*deg);
fRingLogic = new G4LogicalVolume(fRing, fNistManager->FindOrBuildMaterial("G4_LITHIUM_CARBONATE"), "RingLogic");//Li2CO3 
fRingLogic->SetVisAttributes(col4);
fRingPhysi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fRingLogic, "RingPlacement", fMyLogic, 9, true);
}

//making scintillators to veto cosmics rays
void A2DetCATS::MakeScintillators(){

G4VisAttributes* col4 = new G4VisAttributes( G4Colour(1.0,1.0,0.0));
col4->SetVisibility(true);

G4Tubs *fScint1 = new G4Tubs("Scint1", 25.13*cm, 35.13*cm, z, 0.*deg, 72*deg);
fScint1Logic = new G4LogicalVolume(fScint1, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic1");
fScint1Logic->SetVisAttributes(col4);
fScint1Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint1Logic, "Scint1Placement", fMyLogic, 10, true);

G4Tubs *fScint2 = new G4Tubs("Scint2", 25.13*cm, 35.13*cm, z, 72.*deg, 72*deg);
fScint2Logic = new G4LogicalVolume(fScint2, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic2");
fScint2Logic->SetVisAttributes(col4);
fScint2Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint2Logic, "Scint2Placement", fMyLogic, 11, true);

G4Tubs *fScint3 = new G4Tubs("Scint3", 25.13*cm, 35.13*cm, z, 144.*deg, 72*deg);
fScint3Logic = new G4LogicalVolume(fScint3, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic3");
fScint3Logic->SetVisAttributes(col4);
fScint3Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint3Logic, "Scint3Placement", fMyLogic, 12, true);

G4Tubs *fScint4 = new G4Tubs("Scint4", 25.13*cm, 35.13*cm, z, 216.*deg, 72*deg);
fScint4Logic = new G4LogicalVolume(fScint4, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic4");
fScint4Logic->SetVisAttributes(col4);
fScint4Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint4Logic, "Scint4Placement", fMyLogic, 13, true);

G4Tubs *fScint5 = new G4Tubs("Scint5", 25.13*cm, 35.13*cm, z, 288.*deg, 72*deg);
fScint5Logic = new G4LogicalVolume(fScint5, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic5");
fScint5Logic->SetVisAttributes(col4);
fScint5Physi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fScint5Logic, "Scint5Placement", fMyLogic, 14, true);
//this one is located on the back of CATS
G4Tubs *fScint6 = new G4Tubs("Scint6", 0*cm, 35.13*cm, 4.7*cm, 0.*deg, 360*deg);
fScint6Logic = new G4LogicalVolume(fScint6, fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "ScintLogic6");
fScint6Logic->SetVisAttributes(col4);
fScint6Physi = new G4PVPlacement(0, G4ThreeVector(0,0,36.45*cm), fScint6Logic, "Scint6Placement", fMyLogic, 15, true);
}

void A2DetCATS::MakeSensitiveDetectors(){
G4SDManager* SDman = G4SDManager::GetSDMpointer();
if(fIsInteractive==1){ //==1
if(!fCATSVisSD)fCATSVisSD = new A2VisSD("CATSVisSD",7);//seven because we are making 7 parts sensitive 
SDman->AddNewDetector( fCATSVisSD );
fCoreLogic->SetSensitiveDetector(fCoreVisSD);
fregionCATS->AddRootLogicalVolume(fCoreLogic);

fAnnulusPiece1Logic->SetSensitiveDetector(fAnnulusPiece1VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece1Logic);

fAnnulusPiece2Logic->SetSensitiveDetector(fAnnulusPiece2VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece2Logic);

fAnnulusPiece3Logic->SetSensitiveDetector(fAnnulusPiece3VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece3Logic);

fAnnulusPiece4Logic->SetSensitiveDetector(fAnnulusPiece4VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece4Logic);

fAnnulusPiece5Logic->SetSensitiveDetector(fAnnulusPiece5VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece5Logic);

fAnnulusPiece6Logic->SetSensitiveDetector(fAnnulusPiece6VisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece6Logic);

}
else{
if(!fCATSSD)fCATSSD = new A2SD("CATSSD",7); 
SDman->AddNewDetector( fCATSSD );
fCoreLogic->SetSensitiveDetector(fCoreSD);
fregionCATS->AddRootLogicalVolume(fCoreLogic);

fAnnulusPiece1Logic->SetSensitiveDetector(fAnnulusPiece1SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece1Logic);

fAnnulusPiece2Logic->SetSensitiveDetector(fAnnulusPiece2SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece2Logic);

fAnnulusPiece3Logic->SetSensitiveDetector(fAnnulusPiece3SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece3Logic);

fAnnulusPiece4Logic->SetSensitiveDetector(fAnnulusPiece4SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece4Logic);

fAnnulusPiece5Logic->SetSensitiveDetector(fAnnulusPiece5SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece5Logic);

fAnnulusPiece6Logic->SetSensitiveDetector(fAnnulusPiece6SD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece6Logic);

}
}



