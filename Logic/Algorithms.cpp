#include "Algorithms.h"

#include "stdafx.h"

double findMinResidualAlongPath(Vertex<DeliverySite> *s, Vertex<DeliverySite> *t) {
    double f = INF;
// Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
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
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
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
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
// While there is an augmenting path, augment the flow along the path
    while( findAugmentingPath(g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }

    auto end_time = std::chrono::steady_clock::now();
    std::cout << "Each EdmondsKarp takes: " << std::chrono::duration<double>(end_time - start_time).count() << " seconds" << std::endl;

}


double averagePipeCapacity(const std::vector<Edge<DeliverySite>*>& pipes){

    double sumCapacity = 0;
    double sumFlow = 0;

    for(Edge<DeliverySite>* p : pipes){
        sumCapacity += p->getWeight();
        sumFlow += p->getFlow();
    }

    double averageFlow = sumFlow / static_cast<double>(pipes.size());
    double averageCapacity = sumCapacity / static_cast<double>(pipes.size());

    #ifdef EXECUTED_FROM_MAIN
    print("The average flow is " , false);
    print(averageFlow , true);

    print("The average capacity is " , false);
    print(averageCapacity , true);

    #endif

    return averageFlow;
}

double variancePipeCapacityFlow(const std::vector<Edge<DeliverySite>*>& pipes , std::vector<std::pair<double , Edge<DeliverySite>*>>& varianceInEachPoint){

    double averageFlow = averagePipeCapacity(pipes);

    double variance = 0;
    double sumVariance = 0;

    for(Edge<DeliverySite>* p : pipes){
        variance =  (p->getFlow() - averageFlow)*(p->getFlow() - averageFlow);
        variance = std::sqrt(variance);
        variance /= static_cast<double>(pipes.size());

        sumVariance += variance;

        varianceInEachPoint.emplace_back(variance , p);
    }

    return variance;
}

std::pair<double , Edge<DeliverySite>*> maximumDIfferenceCapacityFlow(const std::vector<Edge<DeliverySite>*>& pipes){
    double maxDif = INT32_MIN;

    for(Edge<DeliverySite>* p : pipes){
        maxDif = std::max(maxDif , (p->getWeight() - p->getFlow()));
    }

    for(Edge<DeliverySite>* p : pipes){
        if(p->getWeight() - p->getFlow() == maxDif){
            return std::make_pair(maxDif , p);
        }
    }

    return std::make_pair(0.0, nullptr);
}


