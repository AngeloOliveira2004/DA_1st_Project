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

int a = 0;
int iterations = 0;

void printShortestPath(Vertex<DeliverySite> *pVertex);

double averagePipeCapacity(const std::vector<Edge<DeliverySite>*>& pipes){

    double sumCapacity = 0;
    double sumFlow = 0;
    a++;
    for(Edge<DeliverySite>* p : pipes){
        sumCapacity += p->getWeight();
        sumFlow += p->getFlow();

        if(a == 1){
            print(p->getFlow() , true);
        }
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


//New heuristic
/*posso pegar nas edges e organizar por flow/capacityy e de seguida pegar nas com maior flow, pegar na origem,
 * gerar uma shortestPath para o final desse node e redistribuir o flow assim
 *
isto se for com network toda
senao so pego no caminho mesmo e procuro outro enquanto redistribuo a agua
pegar no caminho com menor flow de momento
 * */

void heuristic(Graph<DeliverySite>*g , std::vector<Edge<DeliverySite>*>& pipes){

    double initialVariance = variancePipeCapacityFlow(pipes , nullptr);
    double variance = INF , lastValue = initialVariance;
    int attempts = 10;

    std::vector<std::pair<double , Edge<DeliverySite>*>> edgesFraction;

    for(Edge<DeliverySite>* e : pipes){
        edgesFraction.emplace_back(e->getFlow() , e);
    }

    std::sort(edgesFraction.begin(), edgesFraction.end(), [](const std::pair<double , Edge<DeliverySite>*>& a, const std::pair<double , Edge<DeliverySite>*>& b) {
        if(a.first == b.first){
            return a.second->getWeight() > b.second->getWeight();
        }

        return a > b;
    });
    /*
    for(int i = 0 ; i < edgesFraction.size() ; i++){
        print(edgesFraction[i].first , false);
        print(edgesFraction[i].second->getOrig()->getInfo().getCode() , false);
        print("->" , false);
        print(edgesFraction[i].second->getDest()->getInfo().getCode() , false);
        print("- flow: " , false);
        print(edgesFraction[i].second->getFlow() , false);
        print(" - capacity: " , false);
        print(edgesFraction[i].second->getWeight() , true);
    }
     */

    //now for each iteration of the algorithm I don't want to calculate the shortest path but the path with leftover pipe capacity

    while (1){

        Edge<DeliverySite>* currEdge = edgesFraction.front().second;

        //now for each iteration of the algorithm I don't want to calculate the shortest path but the path with the highest leftover pipe capacity
        if(currEdge->getDest()->getIncoming().size() != 1) {
            calculate_Max_Leftover_Capacity(g, currEdge->getOrig(), currEdge->getDest(), currEdge);

            std::vector<Edge<DeliverySite> *> pumpPath = calculatePath(currEdge->getDest());

            pumpWater(pumpPath);

            //calcular varianica
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
                    attempts--;
                }
            }

            std::sort(edgesFraction.begin(), edgesFraction.end(), [](const std::pair<double, Edge<DeliverySite> *> &a,
                                                                     const std::pair<double, Edge<DeliverySite> *> &b) {
                if (a.first == b.first) {
                    return a.second->getWeight() > b.second->getWeight();
                }

                return a > b;
            });
        }
    }

}

void pumpWater(const std::vector<Edge<DeliverySite>*>& path){

    auto it = path.end();

    Edge<DeliverySite>* currentEdge = *it;

    double flowToCarry = currentEdge->getFlow();

    for(auto e : path){
        print(e->getOrig()->getInfo().getCode() , false);
        print(" -> " , false);
        print(e->getDest()->getInfo().getCode()  , true);
    }

    for( ; it != path.begin() ; it--){
        if(*it != nullptr) {
            currentEdge = *it;

            flowToCarry = std::min(currentEdge->getWeight() - currentEdge->getFlow(), flowToCarry);

            currentEdge->setFlow(flowToCarry);
        }
    }
}

//calculate app must also be wrong
std::vector<Edge<DeliverySite>*> calculatePath(Vertex<DeliverySite>* target){
    //if calculate_Max_Leftover_Capacity does not fail the path of root should not be a nullptr
    std::vector<Edge<DeliverySite>*> path;

    if(target->getPath() == nullptr){
        print("calculate_Max_Leftover_Capacity failed" , true);
        return path;
    }

    double leftoverFlow = 0;

    while (target->getPath() != nullptr){
        Edge<DeliverySite>* edge = target->getPath();

        leftoverFlow += edge->getWeight() - edge->getFlow();

        target->setPath(edge->getDest()->getPath()) ;

        path.push_back(edge);
    }

    return path;
}

//dijkstra must be wrong
void calculate_Max_Leftover_Capacity(Graph<DeliverySite>* g , Vertex<DeliverySite>* root , Vertex<DeliverySite>* target , Edge<DeliverySite>* edgeToAvoid){

    MutablePriorityQueue<Vertex<DeliverySite>> vertexQueue;
    for(Vertex<DeliverySite>* v : g->getVertexSet()){
        vertexQueue.insert(v);
    }

    for (Vertex<DeliverySite> *v: g->getVertexSet()) {
        v->setDist(-INF);
        v->setPath(nullptr);
    }

    for (Vertex<DeliverySite> *v: g->getVertexSet()) {
        for(Edge<DeliverySite> *e : v->getAdj()){
            e->getDest()->setDist(-1*std::max(e->getDest()->getDist() , v->getDist() + e->getWeight() - e->getFlow()));
        }
    }

    root->setDist(-INF);
    root->setPath(nullptr);

    while (!vertexQueue.empty()){

        //extrai a root primeiro com -INF e depois da set a 0
        Vertex<DeliverySite>* u = vertexQueue.extractMin();
        if(u == root)
            u->setDist(0);
        for(Edge<DeliverySite>* e : u->getAdj()){

            //agora queremos maximizar left over flow
            Vertex<DeliverySite>* node = e->getDest();

            double leftoverCapacity = e->getWeight() - e->getFlow();

            if(u->getDist() + leftoverCapacity > node->getDist()){
                node->setDist(std::max(node->getDist() , u->getDist() + leftoverCapacity));;
                node->setPath(e);
            }
        }
    }

    target->setDist(INF);
}