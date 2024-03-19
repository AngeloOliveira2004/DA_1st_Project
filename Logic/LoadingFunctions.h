#include <memory>
#include "stdafx.h"

std::unordered_set<DeliverySite> nodesToAdd;
std::vector<PumpingStations> edges;


void NormalizeString(std::string& str1 , std::string& str2) {

    std::string temp;
    for(auto c : str1)
    {
        if(isalnum(c))
        {
            temp += c;
        }
    }
    for(auto c : str2)
    {
        if(isdigit(c))
        {
            temp += c;
        }
    }
    size_t pos = temp.find('\r');
    if (pos != std::string::npos) {
        temp.erase(pos);
    }
    pos = temp.find('\n');
    if (pos != std::string::npos) {
        temp.erase(pos);
    }
    str1 = temp;
}

void Remove_terminations(std::string& str)
{
    size_t pos = str.find('\r');
    if (pos != std::string::npos) {
        str.erase(pos);
    }
    pos = str.find('\n');
    if (pos != std::string::npos) {
        str.erase(pos);
    }
    pos = str.find('\0');
    if (pos != std::string::npos) {
        str.erase(pos);
    }
}

void LoadCities() {

    std::cout << "LoadCities started." << std::endl;

    std::ifstream file("LargeDataSet/Cities.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file." << std::endl;
    }

    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;

        while (getline(lineStream, token, ',')) {
            tokens.push_back(token);
        }

        NormalizeString(tokens[4], tokens[5]);

        std::string name = tokens[0];
        std::string municipality;
        std::string code = tokens[2];
        int id = stoi(tokens[1]);

        int maxDelivery = 0;
        int demand = std::stoi(tokens[3]);
        int population = std::stoi(tokens[4]);
        //mandatory
        
        DeliverySite deliverySite(name, municipality, code, id, maxDelivery , demand , population , CITY);

        nodesToAdd.insert(deliverySite);
    }

    file.close();

    //
}

void LoadPipes() {

    std::cout << "LoadPipes started." << std::endl;

    std::ifstream file("LargeDataSet/Pipes.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file." << std::endl;
    }

    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;

        while (getline(lineStream, token, ',')) {
            tokens.push_back(token);
        }
        
        std::string servicePointA = tokens[0];
        std::string servicePointB = tokens[1];
        int capacity = stoi(tokens[2]);
        Remove_terminations(tokens[3]);
        bool direction = stoi(tokens[3]);

        PumpingStations pumpingStation(servicePointA, servicePointB, capacity,direction);

        edges.push_back(pumpingStation);
    }

    file.close();

    //
}

void LoadWaterReservoirs() {

    std::cout << "LoadWaterReservoirs started." << std::endl;

    std::ifstream file("LargeDataSet/Reservoir.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file." << std::endl;
    }

    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;

        while (getline(lineStream, token, ',')) {
            tokens.push_back(token);
        }

        Remove_terminations(tokens[4]);
        std::string name = tokens[0];
        std::string municipality = tokens[1];
        std::string code = tokens[3];
        int id = stoi(tokens[2]);

        int maxDelivery = stoi(tokens[4]);
        int demand = 0;
        int population = 0;
        //mandatory

        DeliverySite deliverySite(name, municipality, code, id, maxDelivery , demand , population , WATER_RESERVOIR);

        nodesToAdd.insert(deliverySite);
    }

    file.close();

    //
}

void LoadFireStations()
{
    std::cout << "LoadFireStations started." << std::endl;

    std::ifstream file("LargeDataSet/Stations.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file." << std::endl;
    }

    std::string line;
    getline(file, line);

    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;

        while (getline(lineStream, token, ',')) {
            if(!token.empty())
                tokens.push_back(token);
        }

        if(!tokens.empty()){

            Remove_terminations(tokens[1]);
            std::string name;
            std::string municipality;
            std::string code = tokens[1];
            int id = stoi(tokens[0]);

            int maxDelivery = 0;
            int demand = 0;
            int population = 0;
            //mandatory

            DeliverySite deliverySite(name, municipality, code, id, maxDelivery , demand , population , FIRE_STATION);

            nodesToAdd.insert(deliverySite);
        }
    }

    file.close();
    //std::this_thread::sleep_for(std::chrono::seconds(5));
}

bool createGraph(Graph<DeliverySite>* g)
{

    for(const DeliverySite& deliverySite : nodesToAdd){
        if(!g->addVertex(deliverySite)){
            std::cerr << "Error adding vertex " << deliverySite.getCode();
            return false;
        }
    }
    
    for(const PumpingStations& pumpingStation : edges){
        if(!g->findVertex(pumpingStation.getServicePointA())){
            std::cout << pumpingStation.getServicePointA();
        }
        DeliverySite deliverySiteA = DeliverySite(pumpingStation.getServicePointA());
        DeliverySite deliverySiteB = DeliverySite(pumpingStation.getServicePointB());

        if(!pumpingStation.getDirection()){
            if(!g->addEdge(deliverySiteA , deliverySiteB , pumpingStation.getCapacity())){
                std::cerr << "Error adding vertex";
                return false;
            }
            if(!g->addEdge(deliverySiteB , deliverySiteA , pumpingStation.getCapacity())){
                std::cerr << "Error adding vertex";
                return false;
            }

        }else{
            if(!g->addEdge(deliverySiteA , deliverySiteB , pumpingStation.getCapacity())){
                std::cerr << "Error adding vertex";
                return false;
            }
        }

    }
    
    return true;
}