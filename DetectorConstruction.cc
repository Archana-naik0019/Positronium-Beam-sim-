#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() {}
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    G4double worldSize = 50 * cm;

    // World volume
    G4Box* worldBox = new G4Box("World", worldSize, worldSize, worldSize);
    G4LogicalVolume* worldLV = new G4LogicalVolume(worldBox, nist->FindOrBuildMaterial("G4_AIR"), "WorldLV");
    G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0);

    // Ice detector volume
    G4double iceSize = 30 * cm;
    G4Box* iceBox = new G4Box("IceCube", iceSize, iceSize, iceSize);
    G4LogicalVolume* iceLV = new G4LogicalVolume(iceBox, nist->FindOrBuildMaterial("G4_WATER"), "IceLV");
    new G4PVPlacement(0, G4ThreeVector(), iceLV, "IceCube", worldLV, false, 0);

    // Add pixelated silicon detectors
    ConstructSiliconDetectors(worldLV);

    return worldPV;
}

void DetectorConstruction::ConstructSiliconDetectors(G4LogicalVolume* worldLV) {
    G4NistManager* nist = G4NistManager::Instance();
    G4double siThickness = 5000 * micrometer;
    G4double pixelSize = 3 * cm; // Adjust to match 10x10 grid on each face

    G4Box* pixelBox = new G4Box("SiPixel", pixelSize / 2, pixelSize / 2, siThickness / 2);
    G4LogicalVolume* pixelLV = new G4LogicalVolume(pixelBox, nist->FindOrBuildMaterial("G4_Si"), "SiPixelLV");

    // Register as a sensitive detector
    SensitiveDetector* siDetector = new SensitiveDetector("SiliconDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(siDetector);
    pixelLV->SetSensitiveDetector(siDetector);

    // Create 10x10 pixels per face
    G4int pixelID = 0;
    for (G4int i = -4; i <= 5; ++i) {
        for (G4int j = -4; j <= 5; ++j) {
            G4ThreeVector posX(30 * cm + siThickness / 2, i * pixelSize, j * pixelSize);
            new G4PVPlacement(0, posX, pixelLV, "SiPixel", worldLV, false, pixelID++);

            G4ThreeVector posY(-30 * cm - siThickness / 2, i * pixelSize, j * pixelSize);
            new G4PVPlacement(0, posY, pixelLV, "SiPixel", worldLV, false, pixelID++);

            G4ThreeVector posZ(i * pixelSize, j * pixelSize, 30 * cm + siThickness / 2);
            new G4PVPlacement(0, posZ, pixelLV, "SiPixel", worldLV, false, pixelID++);

            G4ThreeVector negZ(i * pixelSize, j * pixelSize, -30 * cm - siThickness / 2);
            new G4PVPlacement(0, negZ, pixelLV, "SiPixel", worldLV, false, pixelID++);

            G4ThreeVector posYplus(j * pixelSize, 30 * cm + siThickness / 2, i * pixelSize);
            new G4PVPlacement(0, posYplus, pixelLV, "SiPixel", worldLV, false, pixelID++);

            G4ThreeVector posYminus(j * pixelSize, -30 * cm - siThickness / 2, i * pixelSize);
            new G4PVPlacement(0, posYminus, pixelLV, "SiPixel", worldLV, false, pixelID++);
        }
    }
}
