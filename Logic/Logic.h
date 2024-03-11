//Calling different algorithms from here

#include "stdafx.h"
#include "Algorithms.h"

std::vector<Vertex<DeliverySite>*> sources;

void getSources(Graph<DeliverySite>* g){
    for(Vertex<DeliverySite>* deliverySite : g->getVertexSet()){
        if(deliverySite->getInfo().getNodeType() == WATER_RESERVOIR){
            sources.push_back(deliverySite);
        }
    }
}

void calculateMaxFlow(Graph<DeliverySite>* g , DeliverySite& target ){

    if(sources.empty())
        getSources(g);

    double maxFlow = INT32_MIN;

    for(Vertex<DeliverySite>* source : sources){
        edmondsKarp(g , source->getInfo() , target);

        Vertex<DeliverySite> * t = g->findVertex(target);
        double flow = 0;
        for(Edge<DeliverySite>* e : t->getIncoming()){
            flow += e->getFlow();
            maxFlow = std::max(maxFlow , flow);

        }
    }
    std::cout << "MaxFlow: " << maxFlow << std::endl;
}