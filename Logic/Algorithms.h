#include "stdafx.h"

template <class T>
void print(T _msg , bool _newline){
    std::cout << _msg << " ";
    if(_newline)
        std::cout << std::endl;
}

void edmondsKarp(Graph<DeliverySite> *g, DeliverySite source, DeliverySite target);


double averagePipeCapacity(const std::vector<Edge<DeliverySite>*>& pipes);
double variancePipeCapacityFlow(const std::vector<Edge<DeliverySite>*>& pipes , std::vector<std::pair<double , Edge<DeliverySite>*>>* varianceInEachPoint);
std::pair<double , Edge<DeliverySite>*>  maximumDIfferenceCapacityFlow(const std::vector<Edge<DeliverySite>*>& pipes);


void printDistance(Graph<DeliverySite>* g);
void Dijkstra(Graph<DeliverySite>*g , Vertex<DeliverySite>* root , Vertex<DeliverySite>* target);
void calculate_Max_Leftover_Capacity(Graph<DeliverySite>* g , Vertex<DeliverySite>* root);
void pumpWater(const std::vector<Edge<DeliverySite>*>& path);
std::vector<Edge<DeliverySite>*> calculatePath(Vertex<DeliverySite>* target);


//New heuristic
/*posso pegar nas edges e organizar por flow/capacityy e de seguida pegar nas com maior flow, pegar na origem,
 * gerar uma shortestPath para o final desse node e redistribuir o flow assim
 *
isto se for com network toda
senao so pego no caminho mesmo e procuro outro enquanto redistribuo a agua
pegar no caminho com menor flow de momento
 * */



//well try to get all pipes to redistribute water from one to another
//we repeat this process until the average of flow/variance are either < 1 or until a result does not improve after 5 iterations
//sort the edges by flow and get the minimum on and try to secure a path from the closest source to cthe losest sink by using that edge
//doing this by using Bell-Man ford algorithm and then pumping water from there simply by pumping the highest amount of water possible
//we can use bellmanFord and select the edges with lower flow on the relaxation process
//could probably use select variable inside edge class to force the path in ford-Fulkerson algorithm
void heuristic(Graph<DeliverySite>*g , std::vector<Edge<DeliverySite>*>& pipes);