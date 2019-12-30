#ifndef BUILDING_HPP
#define BUILDING_HPP

// Structure which contains the plan of a building that Wayne constructions would work on.
struct Building {

    int buildingNumber;
    int executionTime;
    int totalTime;

    Building(){}

    Building(int buildingNumber, int executionTime, int totalTime) {
        this->buildingNumber = buildingNumber;
        this->executionTime = executionTime;
        this->totalTime = totalTime;
    }
};


#endif // BUILDING_HPP
