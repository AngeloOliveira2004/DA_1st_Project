#ifndef LOADING_FUNCTIONS_H
#define LOADING_FUNCTIONS_H

#include <unordered_set>
#include <vector>
#include "DeliverySites.h"
#include "PumpingStations.h"
#include "../data_structures/Graph.h"

void NormalizeString(std::string& str1 , std::string& str2);
void Remove_terminations(std::string& str);
void LoadCities();
void LoadPipes();
void LoadWaterReservoirs();
void LoadFireStations();
bool createGraph(Graph<DeliverySite>* g);

#endif // LOADING_FUNCTIONS_H
