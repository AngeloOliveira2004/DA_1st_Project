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

    return averageFlow;
}

double variancePipeCapacityFlow(const std::vector<Edge<DeliverySite>*>& pipes , std::vector<std::pair<double , Edge<DeliverySite>*>>* varianceInEachPoint){

    double averageFlow = averagePipeCapacity(pipes);

    double variance = 0;
    double sumVariance = 0;

    for(Edge<DeliverySite>* p : pipes){
        variance =  (p->getFlow() - averageFlow)*(p->getFlow() - averageFlow);
        variance = std::sqrt(variance);
        variance /= static_cast<double>(pipes.size());

        sumVariance += variance;

        if(varianceInEachPoint != nullptr)
            varianceInEachPoint->emplace_back(variance , p);
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

void heuristic(Graph<DeliverySite>*g , std::vector<Edge<DeliverySite>*>& pipes){

    double initialVariance = variancePipeCapacityFlow(pipes , nullptr);
    double variance = INF , lastValue = initialVariance;
    int attempts = 10;

    std::list<std::pair<double , Edge<DeliverySite>*>> edgesFraction;

    for(Edge<DeliverySite>* e : pipes){
        edgesFraction.emplace_back(e->getFlow() , e);
    }

    edgesFraction.sort([](const std::pair<double, Edge<DeliverySite>*>& a, const std::pair<double, Edge<DeliverySite>*>& b) {
        if (a.first == b.first) {
            return a.second->getWeight() > b.second->getWeight();
        }
        return a.first > b.first;
    });

    //now for each iteration of the algorithm I don't want to calculate the shortest path but the path with leftover pipe capacity
    while (1){
        //switch vector to list
        Edge<DeliverySite>* currEdge = edgesFraction.front().second;

        //now for each iteration of the algorithm I don't want to calculate the shortest path but the path with the highest leftover pipe capacity
        if(currEdge->getDest()->getIncoming().size() != 1) {

            std::pair<std::vector<Vertex<DeliverySite>*> , int> temp = calculatePath(g, currEdge->getOrig() , currEdge->getDest());

            std::vector<Vertex<DeliverySite>*> pumpPath = temp.first;
            int flowToPump = temp.second;

            pumpWater(pumpPath , flowToPump);

            currEdge->setFlow(currEdge->getFlow() - flowToPump);

            variance = variancePipeCapacityFlow(pipes, nullptr);
            auto a = 0;
            Edge<DeliverySite>* debug;
            for(auto v : g->getVertexSet()){
                for(auto e : v->getAdj()){
                    if(e->getDest()->getInfo().getCode() == "PS_3" && e->getOrig()->getInfo().getCode() == "PS_2"){
                        a += 1;
                        debug = e;
                    }
                }
            }

            if (variance < lastValue) {
                lastValue = variance;
            } else {
                if (attempts < 0) {
                    if (lastValue < initialVariance) {
                        print("Flow was well redistributed", true);
                        print(variance , true);
                    }
                    return;
                } else {
                    edgesFraction.pop_front();
                    attempts--;
                }
            }

            edgesFraction.sort([](const std::pair<double, Edge<DeliverySite>*>& a, const std::pair<double, Edge<DeliverySite>*>& b) {
                if (a.first == b.first) {
                    return a.second->getWeight() > b.second->getWeight();
                }
                return a.first > b.first;
            });

        }else{
            edgesFraction.pop_front();
        }
    }

}

int pumpWater(std::vector<Vertex<DeliverySite>*>& path , int flowToPump){

    for(Vertex<DeliverySite>* p : path){
        if(p->getPath() != nullptr){
            Edge<DeliverySite>* e = p->getPath();
            if(flowToPump > e->getWeight() - e->getFlow()){
                flowToPump = e->getWeight() - e->getFlow();
            }
        }
    }

    for(Vertex<DeliverySite>* p : path){
        if(p->getPath() != nullptr){
            Edge<DeliverySite>* e = p->getPath();
            e->setFlow(e->getFlow() + flowToPump);
        }
    }

    return flowToPump;
}

//calculate all paths using dfs
std::pair<std::vector<Vertex<DeliverySite>*> , int> calculatePath(Graph<DeliverySite>* g , Vertex<DeliverySite>* root , Vertex<DeliverySite>* target){

    std::vector<std::vector<Vertex<DeliverySite>*>> allPaths = g->allPaths(root->getInfo() , target->getInfo());

    auto it = allPaths.begin();
    while (it != allPaths.end()) {
        if (it->size() == 2) {
            it = allPaths.erase(it);
        } else {
            ++it;
        }
    }

    std::vector<Vertex<DeliverySite>*> path;

    if(allPaths.empty()){
        return std::make_pair(path , 0);
    }

    int minFLow = INF;
    for(std::vector<Vertex<DeliverySite>*> p : allPaths){
        for(int i = 0 ; i < p.size() - 1 ; i++){
            Vertex<DeliverySite>* curr = p[i];
            Vertex<DeliverySite>* next = p[i+1];

            for(Edge<DeliverySite>* e : curr->getAdj()){
                if(e->getDest() == next){
                    next->setPath(e);
                    int leftOverCap = e->getWeight() - e->getFlow();
                    if(minFLow > leftOverCap){
                        minFLow = leftOverCap;
                        path = p;
                    }
                }
            }
        }
    }

    return std::make_pair(path , minFLow);
}