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

    for(Vertex<DeliverySite>* ds: g.getVertexSet()){
        int sumFlow = 0;
        for(Edge<DeliverySite>* p : ds->getIncoming()){
            sumFlow += p->getFlow();
        }
        ds->setIncomingFlow(sumFlow);

        int difference = ds->getInfo().getDemand() - ds->getIncomingFlow();

        if(ds->getInfo().getNodeType() == CITY && difference > 0 ){
            std::cout << "The city of " << ds->getInfo().getName() << " with code " << ds->getInfo().getCode() << " doesn't receive enough water needing more " << difference << " units \n";
        }
    }

    return 0;
}
