// TrackingAction.cc
#include "TrackingAction.hh"
#include "TrackRegistry.hh"
#include "G4Track.hh"
#include "G4ios.hh"

namespace MD{

TrackingAction::TrackingAction() = default;
TrackingAction::~TrackingAction() = default;

void TrackingAction::PreUserTrackingAction(const G4Track* track) {
    // Register every track at the beginning of its tracking.
    // This records PDG, parent ID, creator process, etc.
    TrackRegistry::RegisterTrack(track);

    // (optional) Debug print for primaries or interesting tracks:
    // if (track->GetParentID() == 0) {
    //    G4cout << "track created: TrackID= " << track->GetTrackID()
    //           << " PDG=" << track->GetDefinition()->GetPDGEncoding()
    //           << " at volume=" << (track->GetLogicalVolumeAtVertex() ?
    //                                track->GetLogicalVolumeAtVertex()->GetName() : "none")
    //           << G4endl;
    // }
}

void TrackingAction::PostUserTrackingAction(const G4Track* /*track*/) {
    // nothing for now; we keep the registry until next event clear
}
}