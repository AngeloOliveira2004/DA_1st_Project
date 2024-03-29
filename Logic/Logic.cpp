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
//trocar este source para superSource
void calculateMaxFlowInACity(Graph<DeliverySite>* g , DeliverySite& target ){

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
        if (v->getInfo().getCode() != "SuperSource" && v->getInfo().getNodeType() == CITY) {
            g->addEdge(v->getInfo(), SuperSink, INF);
        }
    }

}

void removeSuperSourceSink(Graph<DeliverySite>* g,DeliverySite SuperSource,DeliverySite SuperSink) {
    g->removeVertex(SuperSource);
    g->removeVertex(SuperSink);
}

void maxFlowWithSuperSource(Graph<DeliverySite>* g , DeliverySite& target){
    if(sources.empty())
        getSources(g);

    if(sinks.empty())
        getSinks(g);

    //SuperSource
    DeliverySite superSource = DeliverySite("SuperSource");
    g->addVertex(superSource);

    for(Vertex<DeliverySite>* s : sources){
        g->addEdge(superSource , s->getInfo() , INF);
    }

    edmondsKarp(g , superSource , target);

    Vertex<DeliverySite>* targetVertex = g->findVertex(target);

    double maxFlow = 0;

    for(Edge<DeliverySite>* e : targetVertex->getIncoming()){
        maxFlow += e->getFlow();
    }

    g->removeVertex(superSource);

    std::cout << maxFlow << std::endl;
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