cmake_minimum_required(VERSION 3.26)
project(Projeto)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projeto main.cpp
        Logic/Graph.h
        Logic/stdfx.hpp
        Logic/WaterReservoir.h
        Logic/PumpingStations.h
        Logic/PumpingStations.cpp
        Logic/DeliverySites.cpp
        Logic/WaterReservoir.cpp)
