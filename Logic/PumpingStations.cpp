#include "PumpingStations.h"
#include "Algorithms.h"
#include "DeliverySites.h"

bool PumpingStations::canRemovePumping(Graph<DeliverySite> g, std::string PumpingStationRemove) {
    for(auto vertex:g.getVertexSet()){
        for (auto edge:vertex->getAdj()) {
            auto dest = edge->getDest();
            if (dest->getInfo() == PumpingStationRemove){
                g.removeVertex(dest->getInfo());
            }

        }
    }
}
