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

//A2DetectorConstruction.hh
//A2DetectorMessenger.hh
/*As of right now, A2DetectorConstruction.hh and A2DetectorMessenger.hh keep the code from compiling. I'm not sure, but I believe that by not including these headers the vessel geometry cannot be contructed
 *
 * . They give the following error:
 

*                  from /home/vincent/opt/A2Geant4/src/A2DetCATS.cc:5:
/home/vincent/opt/A2Geant4/include/A2DetectorConstruction.hh:105:3: error: ‘A2DetCATS’ does not name a type; did you mean ‘A2DetTAPS’?
  105 |   A2DetCATS* fCATS; //CATS detector
      |   ^~~~~~~~~
      |   A2DetTAPS
make[2]: *** [CMakeFiles/A2Geant4.dir/build.make:121: CMakeFiles/A2Geant4.dir/src/A2DetCATS.cc.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:95: CMakeFiles/A2Geant4.dir/all] Error 2
make: *** [Makefile:103: all] Error 2

 *
 *
 */


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
	void MakeVessel();
	void DefineMaterials();

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
	//G4Tubs* fVessel; //The inclusion of this line cause a "shadow" warning, but it still compiles
	G4LogicalVolume* fVesselLogic;
	G4VPhysicalVolume *fVesselPhysi;
} ;

#endif
