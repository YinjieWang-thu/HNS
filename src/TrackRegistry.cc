// TrackRegistry.cc
#include "TrackRegistry.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4LogicalVolume.hh"
#include "G4TrackStatus.hh"

namespace MD{

thread_local std::unordered_map<G4int, TrackInfo> TrackRegistry::registry_;

void TrackRegistry::RegisterTrack(const G4Track* track) {
    if (!track) return;

    TrackInfo info;
    info.trackID   = track->GetTrackID();
    info.parentID  = track->GetParentID();
    info.pdgCode   = track->GetDefinition()->GetPDGEncoding();

    if (track->GetCreatorProcess()) {
        info.creatorProcess = track->GetCreatorProcess()->GetProcessName();
    } else {
        info.creatorProcess = ""; // primary
    }

    if (track->GetLogicalVolumeAtVertex()) {
        info.volumeAtVertex = track->GetLogicalVolumeAtVertex()->GetName();
    } else {
        info.volumeAtVertex = "";
    }

    registry_[info.trackID] = std::move(info);
}

std::optional<TrackInfo> TrackRegistry::Lookup(G4int trackID) {
    auto it = registry_.find(trackID);
    if (it != registry_.end()) return it->second;
    return std::nullopt;
}

void TrackRegistry::ClearForNewEvent() {
    registry_.clear();
}
}