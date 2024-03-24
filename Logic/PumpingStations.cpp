#include "PumpingStations.h"
#include "Algorithms.h"
#include "DeliverySites.h"

bool PumpingStations::canRemovePumping(Graph<DeliverySite> &g, const std::string &PumpingStationRemove) {
    Graph<DeliverySite> temp = g;
    for (auto vertex:temp.getVertexSet()) { //Percorrer pelos vertices do grafo
        for (auto edge:vertex->getAdj()){ //Percorrer pela aresta de cada vertice percorrido
            auto dest = edge->getDest();
            if (dest->getInfo() == PumpingStationRemove){ //Ver se Destino da aresta é a estacao a ser removida
                vertex->removeEdge(dest->getInfo()); //Remover a edge temporariamente
            }
        }
    }
    DeliverySite source("source");
    DeliverySite target("target");
    edmondsKarp(&temp, source, target);

    return false;
}
