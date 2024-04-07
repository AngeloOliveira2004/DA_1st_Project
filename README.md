# Flow Network Analysis Tool

## Inputs to reach each point in the program:

### 3.i Global number of airports and number of available flights

-> Consult Flight Statistics, Global Statistics

### 3.ii Number of flights out of an airport; and from how many different airlines

-> Consult Flights, Option A

### 3.iii Number of flights per city/airline

-> Consult Flight Statistics, Airline/City Statistics

### 3.iv Number of different countries that a given airport/city flies to

-> Consult Flight Statistics, Country Statistics

### 3.v Number of destinations (airports, cities or countries) available for a given airport

-> Consult Flight Statistics, Airport Statistics, Option A

### 3.vi Number of reachable destinations (airports, cities or countries) from a given airport in a maximum number of X stops (lay-overs)

-> Consult Flight Statistics, Airport Statistics, Option B

### 3.vii Maximum trip and corresponding pair of source-destination airports (or pairs, if more than one), that is, the flight trip(s) with the greatest number of stops in between them

-> Consult Flight Statistics, Option E

### 3.viii Identify the top-k airport with the greatest air traffic capacity, that is, with the greatest number of flights

-> Consult Flight Statistics, Airport Statistics, Option C

### 3.ix Identify the airports that are essential to the network’s circulation capability (airports are essential if, when removed, areas of the network start to be unreachable)

-> Consult Flight Statistics, Airport Statistics, Option D

### 4. Present the best flight option

->  Plan a Trip , choose the next option accordingly

### 5. Search for the best flight option with filters

->  Plan a Trip , choose the next option accordingly

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
<br>
2. LargeDataSet/Cities.csv
; SmallDataSet/Pipes.csv
; SmallDataSet/Reservoir.csv
; SmallDataSet/Stations.csv


