#include "Logic.h"

std::vector<Vertex<DeliverySite>*> sources;
std::vector<Vertex<DeliverySite>*> sinks;

void getSources(Graph<DeliverySite>* g){
    for(Vertex<DeliverySite>* deliverySite : g->getVertexSet()){
        if(deliverySite->getInfo().getNodeType() == WATER_RESERVOIR){
            sources.push_back(deliverySite);
        }
    }
}

void getSinks(Graph<DeliverySite>* g){
    for(Vertex<DeliverySite>* deliverySite : g->getVertexSet()){
        if(deliverySite->getInfo().getNodeType() == CITY){
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
//Find the max flow in the whole graph we use super-source and super-sink
//The super-source node is connected to all the original source nodes by edges with infinite capacity,
// and the super-sink node is connected to all the original sink nodes by edges with capacity equal to their demand
void calculateMaxFlowInEntireNetwork(Graph<DeliverySite>* g){

    //create superSink
    if(sources.empty())
        getSources(g);

    if(sinks.empty())
        getSinks(g);

    //SuperSource
    DeliverySite superSource = DeliverySite("SuperSource");
    g->addVertex(superSource);

    for(Vertex<DeliverySite>* s : sources){
        g->addEdge(s->getInfo() , superSource , INF);
        g->addEdge(superSource , s->getInfo() , INF);
    }

    //SuperSink
    DeliverySite superSink = DeliverySite("SuperSink");
    g->addVertex(superSink);

    for(Vertex<DeliverySite>* s : sinks){
        g->addEdge(s->getInfo() , superSink , s->getInfo().getDemand());
        g->addEdge(superSink , s->getInfo() , s->getInfo().getDemand());
    }

    edmondsKarp(g , superSource , superSink);

    Vertex<DeliverySite>* superSinkVertex = g->findVertex(superSink);
    double maxFlow = 0;

    for(Edge<DeliverySite>* e : superSinkVertex->getIncoming()){
        maxFlow += e->getFlow();
    }

    g->removeVertex(superSink);
    g->removeVertex(superSource);

    std::cout << maxFlow << std::endl;
}

