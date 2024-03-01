#include <memory>
#include "stdafx.h"

std::vector<City> citySet;
std::vector<Fire_Station> fireSet;
std::vector<PumpingStations> edges;
std::vector<WaterReservoir> sources;


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
    std::ifstream file("Project1DataSetSmall/Project1DataSetSmall/Cities_Madeira.csv");
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

        std::string name = tokens[0];
        std::string code = tokens[2];
        u_int8_t id = std::stoi(tokens[1]);
        uint16_t demand =  std::stoi(tokens[3]);
        NormalizeString(tokens[4], tokens[5]);
        uint16_t population =  std::stoi(tokens[4]);
        
        City city(name, code, id, demand, population);

        citySet.push_back(city);
    }

    file.close();
}

void LoadPipes() {

    std::ifstream file("Project1DataSetSmall/Project1DataSetSmall/Pipes_Madeira.csv");
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
        u_int16_t capacity = stoi(tokens[2]);
        Remove_terminations(tokens[3]);
        bool direction = stoi(tokens[3]);

        PumpingStations pumpingStation(servicePointA, servicePointB, capacity,direction);

        edges.push_back(pumpingStation);
    }

    for(auto e : edges)
    {
        e.printInfo();
    }

    file.close();
}

void LoadWaterReservoirs() {
    std::ifstream file("Project1DataSetSmall/Project1DataSetSmall/Reservoirs_Madeira.csv");
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

        std::string name = tokens[0];
        std::string municipality = tokens[1];
        std::string code = tokens[3];
        auto a = std::stoi(tokens[2]);
        uint16_t id =  a;
        Remove_terminations(tokens[4]);
        u_int16_t maxDelivery = stoi(tokens[4]);

        WaterReservoir waterReservoir(name, municipality, code, a ,maxDelivery);

        sources.push_back(waterReservoir);
    }

    for(auto s : sources)
    {
        s.printInfo();
    }

    file.close();
}

template <class T>
void LoadFireStations()
{

}

