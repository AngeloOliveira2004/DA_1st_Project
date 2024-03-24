#include "Logic/stdafx.h"
#include "Logic/LoadingFunctions.h"
#include "Logic/Logic.h"

int main() {

    LoadFireStations();
    LoadWaterReservoirs();
    LoadPipes();
    LoadCities();

    Graph<DeliverySite> g;

    createGraph(&g);

    calculateMaxFlowInEntireNetwork(&g);

    std::unordered_set<Edge<DeliverySite>*> edgesSet;

    for(Vertex<DeliverySite>* v : g.getVertexSet()){
        for(Edge<DeliverySite>* e : v->getAdj()){
            edgesSet.insert(e);
        }
    }

    std::vector<Edge<DeliverySite>*> edgeVector(edgesSet.begin() , edgesSet.end());
    std::vector<Edge<DeliverySite>*> pipes = getPipes(&g);

    Metrics metrics{};

    metrics = g.calculateMetrics();

    //print(metrics.variance , true);

    int initialFlow = g.calculateFlowAcrossEdges();

    print("Initial flow : " , false);
    print(initialFlow , true);

    heuristic(&g , edgeVector);

    initialFlow = g.calculateFlowAcrossEdges();

    print("End flow : " , false);
    print(initialFlow , true);

    g.calculateMetrics();

    return 0;
}
