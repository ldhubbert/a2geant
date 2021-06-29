#ifndef A2DetCATS_h
#define A2DetCATS_h 1

#include "A2Detector.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Material.hh"

/* These may be added later. Sensitive detector stuff definitly will be.
#include "G4Region.hh"
#include "G4OpticalSurface.hh"
#include "A2SD.hh"
#include "A2VisSD.hh"
*/

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
	void DefineMaterials();
	void MakeAnnulus();
	void MakeRing();
private:
	//nist manager
	G4NistManager* fNistManager;
	//A2SD* fCATSSD; //Will be included later when detector is made sensitive
	//A2VisSD* fCATSVisSD; //


	//logical and physical volumes that are part of every detector class
	G4LogicalVolume* fMotherLogic; //logical volume of the mother
	G4LogicalVolume* fMyLogic; //logical volume for CATS
	G4VPhysicalVolume* fMyPhysi; //physical volume for this detector

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
} ;

#endif
