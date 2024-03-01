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
        if(isalnum(c))
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


template<class T>
void LoadCities(Graph<T>* g) {
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

    for(auto c : citySet){
        c.printInfo();
    }

    file.close();
}

template<class T>
void LoadPipes(Graph<T>& g) {
    // Implementation of LoadPipes function
}

template<class T>
void LoadWaterReservoirs(Graph<T>& g) {
    // Implementation of LoadWaterReservoirs function
}


