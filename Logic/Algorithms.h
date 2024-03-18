#include "stdafx.h"

template <class T>
void print(T _msg , bool _newline){
    std::cout << _msg << " ";
    if(_newline)
        std::cout << std::endl;
}

void edmondsKarp(Graph<DeliverySite> *g, DeliverySite source, DeliverySite target);


double averagePipeCapacity(const std::vector<Edge<DeliverySite>*>& pipes);
double variancePipeCapacityFlow(const std::vector<Edge<DeliverySite>*>& pipes , std::vector<std::pair<double , Edge<DeliverySite>*>>& varianceInEachPoint);
std::pair<double , Edge<DeliverySite>*>  maximumDIfferenceCapacityFlow(const std::vector<Edge<DeliverySite>*>& pipes);
