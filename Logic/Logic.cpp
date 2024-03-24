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
        g->addEdge(superSource , s->getInfo() , DBL_MAX);
    }

    //SuperSink
    DeliverySite superSink = DeliverySite("SuperSink");
    g->addVertex(superSink);

    for(Vertex<DeliverySite>* s : sinks){
        g->addEdge(s->getInfo() , superSink , DBL_MAX);
    }

    edmondsKarp(g , superSource , superSink);

    Vertex<DeliverySite>* superSinkVertex = g->findVertex(superSink);
    Vertex<DeliverySite>* superSourceVertex = g->findVertex(superSource);

    double maxFlow = 0;

    for(Edge<DeliverySite>* e : superSinkVertex->getIncoming()){
        maxFlow += e->getFlow();
    }

    double flow = 0;
    auto sum = 0;
    print("------------------------------------" , true);
    for(auto e : sources){
        sum = 0;
        for(auto f : e->getAdj()){
            sum += f->getFlow();
        }
        for(auto f : e->getIncoming()){
            std::cout << e->getInfo().getCode() <<" " <<e->getInfo().getMaxDelivery() << " " << f->getFlow() << " " << sum << "\n\n";
        }
    }

    //print(flow , true);


    g->removeVertex(superSink);
    g->removeVertex(superSource);

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