cmake_minimum_required(VERSION 3.26)
project(Projeto)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projeto main.cpp
        Data_Structures/Graph.h
        Logic/WaterReservoir.h
        Logic/PumpingStations.h
        Logic/PumpingStations.cpp
        Logic/DeliverySites.cpp
        Logic/WaterReservoir.cpp
        Interface/UI.h
        Logic/stdafx.h
        Data_Structures/MutablePriorityQueue.h)
