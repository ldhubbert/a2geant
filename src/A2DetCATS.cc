//Vincent Bruening summer project under supervision by Dr. David Hornidge
//Mount Allison University Summer 2021
//Integrating Compton And Two photon Spectrometer (CATS) into newest version of A2Geant4
//DevNotes:still need: plastic scintillator in front
//CURRENT ISSUES:1. Back piece of lead box is not fully flush- missing 1 mm on both sides in y. Whenever I put in the full 100mm, the GUI cannot load.
//2. core is still one piece
#include "A2DetCATS.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4MultiUnion.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"
#include "G4Cons.hh"
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

fCATSSD = NULL;
fCATSVisSD = NULL;
fNistManager = G4NistManager::Instance();
}

//half-length of CATS. Made it a variable for ease of adjustment.
G4double z = 31.75*cm;

//destructor function
A2DetCATS::~A2DetCATS()  {
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
MakeLeadShield();

fMyPhysi = new G4PVPlacement(0, G4ThreeVector(0,0,100*cm), fMyLogic, "A2DetCATS", fMotherLogic, false, 1, true); //z=162cm 
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
fCoreLogic->SetSensitiveDetector(fCATSVisSD);
fregionCATS->AddRootLogicalVolume(fCoreLogic);

fAnnulusPiece1Logic->SetSensitiveDetector(fCATSVisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece1Logic);

fAnnulusPiece2Logic->SetSensitiveDetector(fCATSVisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece2Logic);

fAnnulusPiece3Logic->SetSensitiveDetector(fCATSVisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece3Logic);

fAnnulusPiece4Logic->SetSensitiveDetector(fCATSVisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece4Logic);

fAnnulusPiece5Logic->SetSensitiveDetector(fCATSVisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece5Logic);

fAnnulusPiece6Logic->SetSensitiveDetector(fCATSVisSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece6Logic);

}
else{
if(!fCATSSD)fCATSSD = new A2SD("CATSSD",7); 
SDman->AddNewDetector( fCATSSD );
fCoreLogic->SetSensitiveDetector(fCATSSD);
fregionCATS->AddRootLogicalVolume(fCoreLogic);

fAnnulusPiece1Logic->SetSensitiveDetector(fCATSSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece1Logic);

fAnnulusPiece2Logic->SetSensitiveDetector(fCATSSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece2Logic);

fAnnulusPiece3Logic->SetSensitiveDetector(fCATSSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece3Logic);

fAnnulusPiece4Logic->SetSensitiveDetector(fCATSSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece4Logic);

fAnnulusPiece5Logic->SetSensitiveDetector(fCATSSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece5Logic);

fAnnulusPiece6Logic->SetSensitiveDetector(fCATSSD);
fregionCATS->AddRootLogicalVolume(fAnnulusPiece6Logic);

}
}

void A2DetCATS::MakeLeadShield(){
G4double Leadx = 351.5*mm; 

G4double Longy = 50*mm;
//G4double Longz = 437.5*mm; //will add 1.3cm/2 have not yet
G4double Longzz = 450.5*mm;

//Two of the "Long" parts of the rectangle
G4Box* fLongBit1 = new G4Box("LongBit1", Leadx+100*mm, Longy, Longzz);
G4Box* fLongBit2 = new G4Box("LongBit2", Leadx+100*mm, Longy, Longzz); 

//The other two "Long" parts
G4Box* fOtherLongBit1 = new G4Box("OtherLongBit1", Longy, Leadx, Longzz);
G4Box* fOtherLongBit2 = new G4Box("OtherLongBit2", Longy, Leadx, Longzz);

//G4double enddimension = 451.5*mm;

G4Box* fEndBit = new G4Box("EndBit", Leadx+100*mm, Leadx+100*mm, Longy);//add 100mm-- was Leadx+100*mm but that doesnt load well

//subtraction solid here!
G4Box* fFrontBit = new G4Box("FrontBit", Longzz, Longzz, 105*mm);
G4Tubs* fFrontBitHole = new G4Tubs("FrontBitHole", 0*cm, 6.9*cm, 105.1*mm, 0*deg, 360*deg); //try 105.1

G4SubtractionSolid *subtraction = new G4SubtractionSolid("subtraction", fFrontBit, fFrontBitHole);

//making the inner cone! Give her a colour!
G4Cons* fLeadCone = new G4Cons("LeadCone", 138*mm, 260*mm, 187*mm, 260*mm, 73*mm, 0*deg, 360*deg);
fLeadConeLogic = new G4LogicalVolume(fLeadCone, fNistManager->FindOrBuildMaterial("G4_Pb"), "LeadConeLogic");
fLeadConePhysi = new G4PVPlacement(0, G4ThreeVector(0,0,-390.5*mm), fLeadConeLogic, "PLeadCone", fMyLogic, 17, true); //393

//endbit transform
G4ThreeVector EndDisplacement = G4ThreeVector(0,0,46.15*cm);//adding 5cm to z so no overlap with back scintillator --was 41.15
G4RotationMatrix none = G4RotationMatrix(); //for no rotation
none.rotateX(0.*deg);
none.rotateY(0.*deg);
none.rotateX(0.*deg);
G4Transform3D EndBitTransform = G4Transform3D(none, EndDisplacement);

G4double Placement = 401.5*mm;

G4double LongBitZ= -1.3*cm;

//LongBit1 transform
G4ThreeVector HighLongBit1 = G4ThreeVector(0,Placement,LongBitZ); //351.5
G4Transform3D LongBit1Transform = G4Transform3D(none, HighLongBit1);

//LongBit2 transform
G4ThreeVector LowLongBit2 = G4ThreeVector(0,-Placement,LongBitZ);
G4Transform3D LongBit2Transform = G4Transform3D(none, LowLongBit2);

//OtherLongBit1 transform
G4ThreeVector OLB1Displacement = G4ThreeVector(Placement,0,LongBitZ);
G4Transform3D OLB1Transform = G4Transform3D(none, OLB1Displacement);

//OtherLongBit2 transform
G4ThreeVector OLB2Displacement = G4ThreeVector(-Placement,0,LongBitZ);
G4Transform3D OLB2Transform = G4Transform3D(none, OLB2Displacement);
//front
G4ThreeVector FrontDisplacement = G4ThreeVector(0,0,-495.5*mm);//-495.5
G4Transform3D FrontBitTransform = G4Transform3D(none, FrontDisplacement);

G4MultiUnion* LeadBox = new G4MultiUnion("LeadBox");

LeadBox->AddNode(*fEndBit, EndBitTransform);
LeadBox->AddNode(*fLongBit1, LongBit1Transform);
LeadBox->AddNode(*fLongBit2, LongBit2Transform);
LeadBox->AddNode(*fOtherLongBit1, OLB1Transform);
LeadBox->AddNode(*fOtherLongBit2, OLB2Transform);
LeadBox->AddNode(*subtraction, FrontBitTransform);

LeadBox->Voxelize();

fLeadBoxLogic = new G4LogicalVolume(LeadBox, fNistManager->FindOrBuildMaterial("G4_Pb"), "LeadLogic");

G4VisAttributes* col5 = new G4VisAttributes( G4Colour(0.3,1.0,0.0));
col5->SetVisibility(true);

fLeadBoxLogic->SetVisAttributes(col5);

fLeadBoxPhysi = new G4PVPlacement(0, G4ThreeVector(0,0,0), fLeadBoxLogic, "PLeadBox", fMyLogic, 16, true);

}
