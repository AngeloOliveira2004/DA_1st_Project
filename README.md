# Flow Network Analysis Tool

## Inputs to reach each point in the program:

- Start Program

- Proceed the application

### 2.1 Determine the maximum amount of water

- Run Max Flow Algorithm

### 2.2 Determine if the water reservoirs supply enough water to all its delivery sites

- Run Check if every city meets it's water demand

### 2.3 Determine the heuristic to balance the load across the network

- Run Check heuristic stats of the max flow

### 3.1 Evaluate what happens in terms of the delivery capacity of the network if one specific water reservoir is out of commission.
- Evaluate network's resiliency, Water Reservoir out of comission.

### 3.2 Can any pumping station be temporarily taken out of service without affecting the delivery capacity to all the cities
- Evaluate network's resiliency, Pumping Station out of comission /in maintenance.

### 3.3 Determine which pipelines, if ruptured, would make it impossible to deliver the desired amount of water to a given city.
- Evaluate network's resiliency, Pipeline/s out of comission / ruptured.

## Post Scriptum:
If you are having troubles with running the project:
1. Make a copy of the dataset folder inside the cmake-build-debug
2. Delete cmake-build-debug
3. Run the program and when prompted with the running error, select the option : "Reload cmake project"
4. Put the folder copy inside the new cmake-build-debug
5. Have fun using the program

Also important, if you have the problem of not loading the csv files, be sure that they are in a folder named dataset inside the cmake-build-debug. Furthermore, the names of the datasets were altered
for simplification issues. If you have any problem while loading the CSVs please use the following names:
1. LargeDataSet/Cities.csv
   ; LargeDataSet/Pipes.csv
   ; LargeDataSet/Reservoir.csv
   ; LargeDataSet/Stations.csv

2. LargeDataSet/Cities.csv
   ; SmallDataSet/Pipes.csv
   ; SmallDataSet/Reservoir.csv
   ; SmallDataSet/Stations.csv
