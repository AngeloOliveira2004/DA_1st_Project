#include <climits>
#include "Algorithms.h"
#include "stdafx.h"

double findMinResidualAlongPath(Vertex<DeliverySite> *source, Vertex<DeliverySite> *sink) {
    double f = DBL_MAX; // Traverse the augmenting path to find the minimum residual capacity

    for (Vertex<DeliverySite>* v = sink; v != source;) {
        Edge<DeliverySite>* e = v->getPath();
        if (e->getDest() == v){
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f; // Return the minimum residual capacity
}

bool findAugmentingPath(Graph<DeliverySite> *g, Vertex<DeliverySite> *source, Vertex<DeliverySite> *sink, Vertex<DeliverySite> *removed) {
// Mark all vertices as not visited
    for(Vertex<DeliverySite>* v : g->getVertexSet()) {
        v->setVisited(false);
    }
// Mark the source vertex as visited and enqueue it

    if (removed != nullptr) removed->setVisited(true);

    std::queue<Vertex<DeliverySite> *> q;
    q.push(source);
    source->setVisited(true);

// BFS to find an augmenting path
    while(!q.empty() && !sink->isVisited()) {
        Vertex<DeliverySite>* v = q.front();
        q.pop();
        for (Edge<DeliverySite>* e : v->getAdj()) {
            Vertex<DeliverySite>* dest = e->getDest();
            if (!dest->isVisited() && (e->getWeight() - e->getFlow() > 0)) {
                dest->setVisited(true);
                dest->setPath(e);
                q.push(dest);
            }
        }
        for (Edge<DeliverySite>* e: v->getIncoming()) {
            Vertex<DeliverySite>* origin = e->getOrig();
            if (!origin->isVisited() && (e->getFlow() > 0)) {
                origin->setVisited(true);
                origin->setPath(e);
                q.push(origin);
            }
        }
    }
    return sink->isVisited();
}

void augmentFlowAlongPath(Vertex<DeliverySite> *source, Vertex<DeliverySite> *sink, double f) {
// Traverse the augmenting path and update the flow values accordingly

    for (Vertex<DeliverySite>* v = sink; v != source;) {
        Edge<DeliverySite>* e = v->getPath();

        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }


}

double edmondsKarp(Graph<DeliverySite> *g, const DeliverySite& source, const DeliverySite& target) {
    double maxFlow = 0;
// Find source and target vertices in the graph
    Vertex<DeliverySite>* s = g->findVertex(source);
    Vertex<DeliverySite>* t = g->findVertex(target);
// Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
    for (auto v : g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
            e->setSelected(false);
        }
    }

// While there is an augmenting path, augment the flow along the path
    while(findAugmentingPath(g, s, t, nullptr) ) {
        double f = findMinResidualAlongPath(s, t);
        maxFlow += f;
        augmentFlowAlongPath(s, t, f);
    }
    return maxFlow;
}

//root will be the origin of edge with the lowest flow
//this edge will be locked to guarantee that it is not picked during this algorithm
//we can try to tell this algo to
//djikstra picks the paths with full edges
void Dijkstra(Graph<DeliverySite>*g , Vertex<DeliverySite>* root , Vertex<DeliverySite>* target) {

    MutablePriorityQueue<Vertex<DeliverySite>> vertexQueue;
    for(Vertex<DeliverySite>* v : g->getVertexSet()){
        vertexQueue.insert(v);
    }

    for (Vertex<DeliverySite> *v: g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }

    root->setDist(0);

    while (!vertexQueue.empty()){
        Vertex<DeliverySite>* u = vertexQueue.extractMin();

        for(Edge<DeliverySite>* e : u->getAdj()){
            //we want the minimum distance by flow
            Vertex<DeliverySite>* v = e->getDest();
            if(v->getDist() > (u->getDist() + e->getFlow())){
                v->setDist(u->getDist() + e->getFlow());
                v->setPath(e);
            }
        }
    }

    target->setDist(INF);
}

double minLeftOverCap(std::vector<Edge<DeliverySite>*>& path){
    auto a = 0;
    for(auto e : path){
        if(e->getFlow() != e->getWeight())
            a++;
    }

    auto min = DBL_MAX;
    for(Edge<DeliverySite>* edge : path){
        if(edge->getWeight() == edge->getFlow())
            return 0;
        if(edge->getWeight() - edge->getFlow() < min){
            min = edge->getWeight() - edge->getFlow();
        }
    }

    return min;
}

Metrics heuristic(Graph<DeliverySite>*g){
    std::vector<Edge<DeliverySite>*> edges;

    edges = g->getEdges();

    Metrics finalMetrics = g->calculateMetrics();
    Metrics initialMetrics = finalMetrics;

    g->printMetrics(initialMetrics);
    initialMetrics = {DBL_MAX , DBL_MAX , DBL_MAX , DBL_MAX};

    while(finalMetrics.variance < initialMetrics.variance || finalMetrics.avg < initialMetrics.avg){

        std::sort(edges.begin(), edges.end(), [](Edge<DeliverySite>* a, Edge<DeliverySite>* b) {

            if(a->getWeight() - a->getFlow() == b->getWeight() - b->getFlow()){
                return a->getWeight() > b->getWeight();
            }

            return a->getWeight() - a->getFlow() < b->getWeight() - b->getFlow();
        });

        for(Edge<DeliverySite>* e : edges){
            std::vector<Edge<DeliverySite>*> path;
            std::vector<std::vector<Edge<DeliverySite>*>> allPaths;

            allPaths = g->allPaths(e->getOrig()->getInfo() , e->getDest()->getInfo());

            double maxDiff = -1;
            if(allPaths.empty())
                continue;

            for(std::vector<Edge<DeliverySite>*> tempPath : allPaths){
                double minFlow = minLeftOverCap(tempPath);
                if (minFlow > maxDiff) {
                    maxDiff = minFlow;
                    path = tempPath;
                }
            }

            double waterToPump = maxDiff;
            if(e->getFlow() - waterToPump < 0)
                waterToPump = e->getFlow();

            e->setFlow(e->getFlow() - waterToPump);

            pumpWater(path , waterToPump);
        }

        initialMetrics = finalMetrics;

        finalMetrics = g->calculateMetrics();

    }

    finalMetrics = g->calculateMetrics();

    g->printMetrics(finalMetrics);

    for(auto e : g->getEdges()){
        if(e->getFlow() > e->getWeight()){
            print("SOBRECARGAAAA    " , false);
        }
        if(e->getFlow() < 0)
            print("DESCEU O CANOOOOO" , false);
    }
    return  finalMetrics;
}

void pumpWater(std::vector<Edge<DeliverySite>*>& path , double flowToPump){
    if(flowToPump != 0)
        auto a = 0;
    for(Edge<DeliverySite>* e : path){
        e->setFlow(e->getFlow() + flowToPump);
    }
}
