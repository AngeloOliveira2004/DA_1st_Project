#include "Algorithms.h"
#include "DeliverySites.h"
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


void printShortestPath(Vertex<DeliverySite> *pVertex);

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

//objective is to identify the closest source/sink
void BFS(){

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

void printDistance(Graph<DeliverySite>* g){
    for(Vertex<DeliverySite>* v : g->getVertexSet()){
        if(v->getInfo().getNodeType() == WATER_RESERVOIR){
            Dijkstra(g , v , nullptr);

            // Print the result of Dijkstra's search from the current water reservoir
            std::cout << "Search starting from water reservoir " << v->getInfo().getCode() << ":" << std::endl;
            std::cout << "------------------------------------" << std::endl;

            // Traverse all vertices in the graph
            for(Vertex<DeliverySite>* u : g->getVertexSet()) {
                if (u->getDist() != INF) {
                    // Print the shortest path from the current water reservoir to the current vertex
                    std::cout << "Shortest path to " << u->getInfo().getCode() << ": ";
                    printShortestPath(u);
                } else {
                    // Print that there's no path to this vertex from the current water reservoir
                    std::cout << "No path to " << u->getInfo().getCode() << std::endl;
                }
            }

            std::cout << "------------------------------------" << std::endl;
        }
    }
}

void printShortestPath(Vertex<DeliverySite> *pVertex) {
    std::stack<Edge<DeliverySite>*> pathStack;
    Vertex<DeliverySite>* currentVertex = pVertex;

    // Push all edges of the shortest path onto the stack
    while (currentVertex->getPath() != nullptr) {
        pathStack.push(currentVertex->getPath());
        currentVertex = currentVertex->getPath()->getOrig();
    }

    // Print the edges in reverse order to get the shortest path
    while (!pathStack.empty()) {
        Edge<DeliverySite>* edge = pathStack.top();
        pathStack.pop();

        std::cout << edge->getOrig()->getInfo().getCode() << " --- " << edge->getFlow() << " ---> ";
        std::cout << edge->getDest()->getInfo().getCode() << std::endl;
    }
}



//well try to get all pipes to redistribute water from one to another
//we repeat this process until the average of flow/variance are either < 1 or until a result does not improve after 5 iterations
//sort the edges by flow and get the minimum on and try to secure a path from the closest source to cthe losest sink by using that edge
//doing this by using Dijkstra algorithm and then pumping water from there simply by pumping the highest amount of water possible
//we can use bellmanFord and select the edges with lower flow on the relaxation process
//could probably use select variable inside edge class to force the path in ford-Fulkerson algorithm



//sort all edges by flow , if equal by capacity in descending order
//pick the first one because it will have the highest flow which has to be redistributed
//calculate path with the biggest leftover distance
//pick the path
//test variance and repeat
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

            calculate_Max_Leftover_Capacity(g, currEdge->getOrig() , currEdge->getDest());

            std::vector<Edge<DeliverySite> *> pumpPath = calculatePath(g, currEdge->getOrig() , currEdge->getDest() , currEdge);

            double subtract = pumpWater(pumpPath , currEdge->getDest());

            currEdge->setFlow(currEdge->getFlow() - subtract);

            variance = variancePipeCapacityFlow(pipes, nullptr);

            if (variance < lastValue) {
                lastValue = variance;
            } else {
                if (attempts < 0) {
                    if (lastValue < initialVariance) {
                        print("Flow was well redistributed", true);
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

            print(variance , true);

        }else{
            edgesFraction.pop_front();
        }
    }

}

double pumpWater(const std::vector<Edge<DeliverySite>*>& path , Vertex<DeliverySite>* target){
    bool present = false;
    double flowToSubtract = INF;

    for(auto e : path){
        if(e->getDest() == target){
            present = true;
        }
        flowToSubtract = std::min(flowToSubtract , e->getDest()->getDist());
    }


    if(present) {
        for(Edge<DeliverySite>* e : path){
            if(e->getFlow()+flowToSubtract > e->getWeight()){
                flowToSubtract = e->getWeight() - e->getFlow();
                e->setFlow(e->getWeight());
            }else {
                e->setFlow(e->getFlow() + flowToSubtract);
            }
        }
    }



    return flowToSubtract;
}


std::vector<Edge<DeliverySite>*> calculatePath(Graph<DeliverySite>* g, Vertex<DeliverySite>* source , Vertex<DeliverySite>* target , Edge<DeliverySite>* edgeToAvoid){

    std::vector<Edge<DeliverySite>*> path;
    std::unordered_set<int> valuesToAvoid;

    if(source->getPath() == nullptr){
        print("calculate_Max_Leftover_Capacity failed" , true);
        return path;
    }

    for(auto v : g->getVertexSet()){
        if(v->getAdj().size() == 0){
            v->setVisited(true);
        }
    }

    Edge<DeliverySite>* pushEdge;
    Edge<DeliverySite>* prevEdge;
    int flow = INF;
    int attempts = 10;

    while (target != source || attempts > 0){
        for(Edge<DeliverySite>* e : source->getAdj()){
            if(e->getDest()->getDist() < flow && e->getDest()->getDist() != 0 && !e->getDest()->isVisited() && e != edgeToAvoid){
                flow = e->getDest()->getDist();
                pushEdge = e;
            }
        }
        if(prevEdge == pushEdge){
            attempts--;
        }
        prevEdge = pushEdge;
        source->setVisited(true);
        path.push_back(pushEdge);
        source = pushEdge->getDest();
        flow = 100000000;

        if(path.size() > g->getVertexSet().size()) {
            path.clear();
            return path;
        }

    }

    return path;
}

//literally just go to each node and get the minimum capacity - flow from each node

//Let's abandon this idea and just make a BFS
//change queue to priority queue with dist as an argument with all nodes inside and simply update dist
void calculate_Max_Leftover_Capacity(Graph<DeliverySite>* g , Vertex<DeliverySite>* root , Vertex<DeliverySite>* target){
    MutablePriorityQueue<Vertex<DeliverySite>> q;

    for(Vertex<DeliverySite>* v : g->getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
        v->setDist(INF);
    }

    for(Vertex<DeliverySite>* v : g->getVertexSet()){
        q.insert(v);
    }

    root->setDist(0);

    while (!q.empty()){
        Vertex<DeliverySite>* node = q.extractMin();

        if(node == target) continue;

        for(Edge<DeliverySite>* e : node->getAdj()){

            Vertex<DeliverySite>* dest = e->getDest();
            double leftOver_Flow = e->getWeight() - e->getFlow();

            if (dest->getDist() == INF){
                dest->setDist(std::min(node->getDist() , leftOver_Flow));
                dest->setPath(e);
            }else{
                if(std::min(node->getDist() , leftOver_Flow) > dest->getDist()){
                    dest->setDist(std::min(node->getDist() , leftOver_Flow));
                    dest->setPath(e);
                }
            }
        }
    }

    for(Vertex<DeliverySite>* node : g->getVertexSet()){
        if(node->getInfo().getNodeType() == WATER_RESERVOIR || node->getDist() == INF)
            node->setDist(0);
    }
/*
    for(auto v : g->getVertexSet()){
        if(v != target && v->getDist() > target->getDist()) {
            print(v->getInfo().getCode(), false);
            print(" ", false);
            print(v->getDist(), true);
        }
    }
    */
}