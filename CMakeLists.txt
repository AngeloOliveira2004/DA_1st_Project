cmake_minimum_required(VERSION 3.26)
project(Projeto)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projeto main.cpp
        data_structures/Graph.h
        Logic/PumpingStations.h
        Logic/PumpingStations.cpp
        Logic/DeliverySites.cpp
        Interface/UI.h
        Logic/stdafx.h
        data_structures/MutablePriorityQueue.h
        Logic/LoadingFunctions.h
        Logic/Logic.h
        Logic/Algorithms.h
        Logic/Algorithms.cpp)
