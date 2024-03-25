#include <climits>
#include "Algorithms.h"

#include "stdafx.h"

double calculateMaxFlow(std::vector<Vertex<DeliverySite>*>& vertexSet){
    double flow = 0;

    for(Vertex<DeliverySite>* v : vertexSet){
        if(v->getInfo().getNodeType() == CITY)
            for(auto e : v->getAdj()){
                flow += e->getFlow();
            }
    }
    return flow;
}

double findMinResidualAlongPath(Vertex<DeliverySite> *s, Vertex<DeliverySite> *t) {
    double f = INF;
// Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            if(e->getOrig()->getInfo().getNodeType() == WATER_RESERVOIR){
                double remainDelivery = e->getOrig()->getInfo().calculateRemainingDeliviry(e->getOrig()->getAdj());
                if(f > remainDelivery){
                    f = remainDelivery;
                }
            }
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
// Return the minimum residual capacity
    return f;
}


void testAndVisit(std::queue< Vertex<DeliverySite>*> &q, Edge<DeliverySite> *e, Vertex<DeliverySite> *w, double residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
// Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}


bool findAugmentingPath(Graph<DeliverySite> *g, Vertex<DeliverySite> *s, Vertex<DeliverySite> *t) {
// Mark all vertices as not visited
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
// Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<Vertex<DeliverySite> *> q;
    q.push(s);
// BFS to find an augmenting path
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
// Process outgoing edges
        for(auto e: v->getAdj()) {
            Vertex<DeliverySite>* dest = e->getDest();
            if (!dest->isVisited() && (e->getWeight() - e->getFlow() > 0)) {

                if (dest->getInfo().getNodeType() == WATER_RESERVOIR){

                    double remainDelivery = dest->getInfo().calculateRemainingDeliviry(dest->getAdj());
                    if (remainDelivery == 0){
                        dest->setVisited(true);
                        continue;
                    }

                }
                dest->setVisited(true);
                dest->setPath(e);
                q.push(dest);
            }

        }
// Process incoming edges
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
// Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

void augmentFlowAlongPath(Vertex<DeliverySite> *s, Vertex<DeliverySite> *t, double f) {
// Traverse the augmenting path and update the flow values accordingly


    for (auto v = t; v != s; ) {
        auto e = v->getPath();

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

void edmondsKarp(Graph<DeliverySite> *g, DeliverySite source, DeliverySite target) {

    auto start_time = std::chrono::steady_clock::now();
// Find source and target vertices in the graph
    Vertex<DeliverySite>* s = g->findVertex(source);
    Vertex<DeliverySite>* t = g->findVertex(target);
// Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

// While there is an augmenting path, augment the flow along the path
// While there is an augmenting path, augment the flow along the path
    while( findAugmentingPath(g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
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
                maxDiff = 0;

            for(std::vector<Edge<DeliverySite>*> tempPath : allPaths){
                if(tempPath.size() == 1){
                    maxDiff = 0;
                    continue;
                }
                double minFlow = minLeftOverCap(tempPath);
                if (minFlow > maxDiff) {
                    maxDiff = minFlow;
                    path = tempPath;
                }
            }

            double waterToPump = maxDiff;
            e->setFlow(e->getFlow() - waterToPump);
            pumpWater(path , waterToPump);
        }

        finalMetrics = g->calculateMetrics();

        initialMetrics = finalMetrics;
    }

    finalMetrics = g->calculateMetrics();

    g->printMetrics(finalMetrics);

    return  finalMetrics;
}

void pumpWater(std::vector<Edge<DeliverySite>*>& path , double flowToPump){
    if(flowToPump != 0)
        auto a = 0;
    for(Edge<DeliverySite>* e : path){
            e->setFlow(e->getFlow() + flowToPump);
    }
}

