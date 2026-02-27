// TrackRegistry.hh
#ifndef TRACK_REGISTRY_HH
#define TRACK_REGISTRY_HH

#include "G4Track.hh"
#include <string>
#include <unordered_map>
#include <optional>

namespace MD{

struct TrackInfo {
    G4int trackID = 0;
    G4int parentID = 0;
    G4int pdgCode = 0;
    std::string creatorProcess; // empty for primary
    std::string volumeAtVertex; // logical volume name at vertex (if any)
    // You can add more fields e.g. vertex position, kinetic energy at creation...
};

class TrackRegistry {
public:
    // Called by TrackingAction (or anywhere) to register a track
    static void RegisterTrack(const G4Track* track);

    // Lookup by trackID; returns std::optional<TrackInfo>
    static std::optional<TrackInfo> Lookup(G4int trackID);

    // Clear registry for a new event (should be called in EventAction::BeginOfEventAction)
    static void ClearForNewEvent();

private:
    // thread-local container: one per worker thread
    static thread_local std::unordered_map<G4int, TrackInfo> registry_;
};
}
#endif // TRACK_REGISTRY_HH
