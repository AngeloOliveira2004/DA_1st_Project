#include <climits>
#include "Logic.h"

std::vector<Vertex<DeliverySite>*> sources;
std::vector<Vertex<DeliverySite>*> sinks;
std::unordered_map<Vertex<DeliverySite>* , int> flowMap;

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
            sinks.push_back(deliverySite);
        }
    }
}

//Find the max flow in the whole graph we use super-source and super-sink
//The super-source node is connected to all the original source nodes by edges with infinite capacity,
// and the super-sink node is connected to all the original sink nodes by edges with capacity equal to their demand

void createSuperSourceSink(Graph<DeliverySite>* g,DeliverySite SuperSource,DeliverySite SuperSink){
    g->addVertex(SuperSource);
    g->addVertex(SuperSink);

    for (auto v: g->getVertexSet()) {
        nodeTypes code = v->getInfo().getNodeType();
        if (code == WATER_RESERVOIR){
            g->addEdge(SuperSource,v->getInfo(),v->getInfo().getMaxDelivery());
        } else if (code == CITY && v->getInfo().getCode() != "SuperSource" && v->getInfo().getCode() != "SuperSink") {
            g->addEdge(v->getInfo(),SuperSource, v->getInfo().getDemand());
        }
    }

    for (auto v : g->getVertexSet()) {
        if (v->getInfo().getCode() != "SuperSource" && v->getInfo().getCode() != "SuperSink" && v->getInfo().getNodeType() == CITY) {
            g->addEdge(v->getInfo(), SuperSink, v->getInfo().getDemand());
        }
    }

}

void createSuperSource(Graph<DeliverySite>* g,DeliverySite SuperSource){
    g->addVertex(SuperSource);

    for (auto v: g->getVertexSet()) {
        nodeTypes code = v->getInfo().getNodeType();
        if (code == WATER_RESERVOIR){
            g->addEdge(SuperSource,v->getInfo(),v->getInfo().getMaxDelivery());
        } else if (code == CITY && v->getInfo().getCode() != "SuperSource" && v->getInfo().getCode() != "SuperSink") {
            g->addEdge(v->getInfo(),SuperSource, v->getInfo().getDemand());
        }
    }

}

void removeSuperSourceSink(Graph<DeliverySite>* g,DeliverySite SuperSource,DeliverySite SuperSink) {
    g->removeVertex(SuperSource);
    g->removeVertex(SuperSink);
}

void removeSuperSource(Graph<DeliverySite>* g,DeliverySite SuperSource) {
    g->removeVertex(SuperSource);
}

std::vector<Edge<DeliverySite>*> getPipes(Graph<DeliverySite>* g){
    std::unordered_set<Edge<DeliverySite>*> res;

    for(auto v : g->getVertexSet()){
        for(Edge<DeliverySite>* e : v->getAdj()){
            if(res.find(e) == res.end())
                res.insert(e);
        }
    }

    std::vector<Edge<DeliverySite>*> result(res.begin(), res.end());

    return result;
}