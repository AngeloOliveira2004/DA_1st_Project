#include "PumpingStations.h"
#include "Algorithms.h"
#include "DeliverySites.h"


bool PumpingStations::canRemovePumping(Graph<DeliverySite>* g, std::string PumpingStationRemove) {

    for(auto vertex:g->getVertexSet()){
        for (auto edge:vertex->getAdj()) {
            auto dest = edge->getDest();
            if (dest->getInfo() == PumpingStationRemove) {
                g->removeVertex(dest->getInfo());
            }
        }
    }
    Supersource_create(g);
    SuperSink_crete(g);
    Vertex<DeliverySite> *vertex_source = g->findVertex(DeliverySite("supersourciiie"));
    Vertex<DeliverySite> *vertex_sink = g->findVertex(DeliverySite("supersinkieee"));
    DeliverySite sourcieee("", "", "supersourciiie", 0, 0, 0, 0, WATER_RESERVOIR);
    DeliverySite sinkieee("", "", "supersinkieee", 0, 0, 0, 0, CITY);

    edmondsKarp(g, sourcieee, sinkieee);
    //adicionar as edges
    //remover as supersources
    return false;
}
