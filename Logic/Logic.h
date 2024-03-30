//Calling different algorithms from here

#include "stdafx.h"
#include "Algorithms.h"

void getSources(Graph<DeliverySite>* g);

void createSuperSourceSink(Graph<DeliverySite>* g,DeliverySite SuperSource,DeliverySite SuperSink);
void removeSuperSourceSink(Graph<DeliverySite>* g,DeliverySite SuperSource,DeliverySite SuperSink);

void calculateMaxFlowInACity(Graph<DeliverySite>* g , DeliverySite& target );
//Find the max flow in the whole graph we use super-source and super-sink
//The super-source node is connected to all the original source nodes by edges with infinite capacity,
// and the super-sink node is connected to all the original sink nodes by edges with capacity equal to their demand
void calculateMaxFlowInEntireNetwork(Graph<DeliverySite>* g);

void maxFlowWithSuperSource(Graph<DeliverySite>* g , DeliverySite& target);

std::vector<Edge<DeliverySite>*> getPipes(Graph<DeliverySite>* g);