#ifndef A2DetCATS_h
#define A2DetCATS_h 1

#include "A2Detector.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "A2SD.hh"
#include "A2VisSD.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Region;
class A2SD;
class A2VisSD;


class A2DetCATS : public A2Detector 
{
public: 
	A2DetCATS();
	~A2DetCATS();

	virtual  G4VPhysicalVolume* Construct(G4LogicalVolume *MotherLogic); 
	void MakeCore();
	void MakeAnnulus();
	void MakeRing();
	void MakeScintillators();
	void MakeSensitiveDetectors();
	void MakeLeadShield();
private:
	G4NistManager* fNistManager;

	//logical and physical volumes that are part of every detector class
	G4LogicalVolume* fMotherLogic; 
	G4LogicalVolume* fMyLogic; 
	G4VPhysicalVolume* fMyPhysi; 

	//volumes specifically for this detector
	G4LogicalVolume* fCoreLogic;
	G4VPhysicalVolume *fCorePhysi;

	G4LogicalVolume* fAnnulusPiece1Logic;
	G4VPhysicalVolume *fAnnulusPiece1Physi;
	G4LogicalVolume* fAnnulusPiece2Logic;
	G4VPhysicalVolume *fAnnulusPiece2Physi;
	G4LogicalVolume* fAnnulusPiece3Logic;
	G4VPhysicalVolume *fAnnulusPiece3Physi;
	G4LogicalVolume* fAnnulusPiece4Logic;
	G4VPhysicalVolume *fAnnulusPiece4Physi;
	G4LogicalVolume* fAnnulusPiece5Logic;
	G4VPhysicalVolume *fAnnulusPiece5Physi;
	G4LogicalVolume* fAnnulusPiece6Logic;
	G4VPhysicalVolume *fAnnulusPiece6Physi;

	G4LogicalVolume* fRingLogic;
	G4VPhysicalVolume *fRingPhysi;

	G4LogicalVolume* fScint1Logic;
	G4VPhysicalVolume * fScint1Physi;
	G4LogicalVolume* fScint2Logic;
        G4VPhysicalVolume * fScint2Physi;
 	G4LogicalVolume* fScint3Logic;
        G4VPhysicalVolume * fScint3Physi;
 	G4LogicalVolume* fScint4Logic;
        G4VPhysicalVolume * fScint4Physi;
	G4LogicalVolume* fScint5Logic;
        G4VPhysicalVolume * fScint5Physi;
	G4LogicalVolume* fScint6Logic;
	G4VPhysicalVolume * fScint6Physi;	

	G4LogicalVolume* fLeadConeLogic;
	G4VPhysicalVolume* fLeadConePhysi;	

	G4LogicalVolume* fLeadBoxLogic;
	G4VPhysicalVolume * fLeadBoxPhysi;	

	A2SD* fCATSSD;
	A2VisSD* fCATSVisSD;
	
	G4Region* fregionCATS;
} ;

#endif
