//
// Created by jose-costa on 2/26/24.
//

#include "PumpingStations.h"

bool PumpingStations::canRemovePumping(Graph<std::string> &g, const std::string &PumpingStationRemove) {
    for (auto vertex:g.getVertexSet()) { //Percorrer pelos vertices do grafo
        for (auto edge:vertex->getAdj()){ //Percorrer pela aresta de cada vertice percorrido
            auto dest = edge->getDest();
            if (dest->getInfo() == PumpingStationRemove){ //Ver se Destino da aresta é a estacao a ser removida
                vertex->removeEdge(dest->getInfo()); //Remover a edge temporariamente
            }
        }
    }
    return false;
}
