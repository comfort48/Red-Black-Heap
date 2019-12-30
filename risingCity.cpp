#include "Building.hpp"
#include "Min_Heap.cpp"
#include "Red_Black_Tree.cpp"
#include "Red_Black_Tree_Node.cpp"
#include <fstream>

int globalTime = 0;      // Global Counter to keep track of Wayne construction's work.
Min_Heap min_heap(2000); // Min Heap initialization.
RBTree red_black_tree;	 // Red-Black Tree initialization.

void insertBuilding(string line, ofstream &output) {										// Insert Building into Red-Black tree and Min Heap - Takes care of Insert.
    int buildingNumber = atoi(line.substr(line.find("(")+1, line.find(",")).c_str());
    int totalTime = atoi(line.substr(line.find(",")+1, line.find(")")).c_str());
    Building plan(buildingNumber, 0, totalTime);
    if(red_black_tree.search(red_black_tree.root, buildingNumber) == NULL) {
        RBTNode *correspondence = red_black_tree.insert(plan);
        min_heap.push(make_pair(plan, correspondence));
    }
    else {
        output<<"Building record already exists!"<<endl;              // If building is already present.
    }
}


void printBuildingInfo(string range, ofstream &output) {								   // Prints the building info from Red-Black Tree - Takes care of PrintBuilding(a, b) or PrintBuilding(a).
    if(range.find(",") != -1) {															   // Case PrintBuilding(a, b).
        int firstBuilding = atoi(range.substr(range.find("(")+1, range.find(",")).c_str());
        int lastBuilding =  atoi(range.substr(range.find(",")+1, range.find(")")).c_str());
        string rangeValues = "";
        red_black_tree.searchAndStore(red_black_tree.root, firstBuilding, lastBuilding, rangeValues);

            if(rangeValues == "") {
                output<<"("<<0<<","<<0<<","<<0<<")"<<endl;
            }
            else{
                rangeValues.pop_back();
                output<<rangeValues<<endl;
            }
    }
    else {																				// Case PrintBuilding(a);
        int oneBuilding = atoi(range.substr(range.find("(")+1, range.find(")")).c_str());
        RBTNode *t = red_black_tree.search(red_black_tree.root, oneBuilding);
        if(t == NULL)
            output<<"("<<0<<","<<0<<","<<0<<")"<<endl;
        else {
            output<<"("<<t->value.buildingNumber<<","<<t->value.executionTime<<","<<t->value.totalTime<<")"<<endl;
        }
    }
}

void constructBuilding(ofstream &output) {												// Construct building function that takes care of Wayne Construction's construction work.
        Building constructMe = min_heap.top().first;
        RBTNode* nodeptr = min_heap.top().second;
        min_heap.pop();
        int daysToConstruct = min(constructMe.totalTime - constructMe.executionTime, 5);	// Takes the minimum of either 5 or remaining time for building construction.
        for(int i = 1; i <= daysToConstruct; i++) {
            constructMe.executionTime += 1;
            globalTime += 1;
            red_black_tree.update(red_black_tree.root, constructMe.buildingNumber, constructMe.executionTime);
         }
        if(constructMe.executionTime == constructMe.totalTime) {
            red_black_tree.deleteFromRBTree(constructMe.buildingNumber);
            output<<"("<<constructMe.buildingNumber<<","<<globalTime<<")"<<endl;
        }
        else {
            min_heap.push(make_pair(constructMe, nodeptr));
        }
}


string line;
int locTime;
char operation;

int main(int argc, char *argv[]) {

	string inputFile = argv[1];
	ifstream input(inputFile);         // Input file given as argument.
	ofstream output("output_file.txt");	// output file is fixed as output_file.txt
    getline(input, line);
    insertBuilding(line, output);
    getline(input, line);
    int read = 1;

    while(read && line.size() > 2) {				// If there is input that is yet to be processed.

        int locTime = atoi(line.substr(0, line.find(":")).c_str());				// Time at which present input arrives
        char operation = line.substr(line.find(": ")+2, line.find("(")).at(0);

        if(globalTime >= locTime) {				   // If input arrival time is less than global time - execute all the operations
            if(operation == 'I' && read) {         // If operation read is 'I'nsert.
                insertBuilding(line, output);	   // Insert building
                read = 0;
                getline(input, line);
                read = 1;
                continue;
            }
            if(operation == 'P' && read) {		   // If operation read is 'P'rintBuilding
                printBuildingInfo(line.substr(line.find("(")), output);	 // PrintBuilding
                read = 0;
                getline(input, line);
                read = 1;
                continue;
            }
        }
        if(min_heap.size() > 0) {                  // If there are buildings to be constructed and globalTime is less than the next Input arrival time - Then start construction on existing buildings.
            if(globalTime < locTime) {
                Building constructMe = min_heap.top().first;	// Takes the top element from min heap which has less execution time.
                RBTNode* nodeptr = min_heap.top().second;		// Correspondence pointer to Red-Black Tree.
                min_heap.pop();
                int daysToConstruct = min(constructMe.totalTime - constructMe.executionTime, 5);
                for(int i = 1; i <= daysToConstruct; i++) {												// Starts construction.
                    constructMe.executionTime += 1;
                    globalTime += 1;
                    red_black_tree.update(red_black_tree.root, constructMe.buildingNumber, constructMe.executionTime); // Red-Black Tree updation.
                    if(operation == 'P' && locTime == globalTime && read) {
                        printBuildingInfo(line.substr(line.find("(")), output);
                        read = 0;
                        if(getline(input, line) && line.size() > 2) {
                            locTime = atoi(line.substr(0, line.find(":")).c_str());
                            operation = line.substr(line.find(": ")+2, line.find("(")).at(0);
                            read = 1;
                        }
                    }
                    if(operation == 'I' && locTime == globalTime && read) {							// Takes input and check the input arrival time and global time.
                        insertBuilding(line, output);
                        read = 0;
                        if(getline(input, line) && line.size() > 2) {								// Take next input.
                            locTime = atoi(line.substr(0, line.find(":")).c_str());
                            operation = line.substr(line.find(": ")+2, line.find("(")).at(0);
                            read = 1;
                        }
                    }
                    if(constructMe.executionTime == constructMe.totalTime) {
                        red_black_tree.deleteFromRBTree(constructMe.buildingNumber);				// If construction is finished, then remove from the Red Black Tree.
                        output<<"("<<constructMe.buildingNumber<<","<<globalTime<<")"<<endl;
                    }
                }

                if(constructMe.totalTime != constructMe.executionTime) {
                    min_heap.push(make_pair(constructMe, nodeptr));									// Push unfinished Building to Min Heap for further construction.
                }
            }
        }
        else {																					   // Case when Wayne construction is free from work and next work arriving is far away from globalTime.
            globalTime = locTime;
            if(operation == 'P' && read) {
                printBuildingInfo(line.substr(line.find("(")), output);
                read = 0;
                if(getline(input, line) && line.size() > 2)
                    read = 1;
            }
            if(operation == 'I' && read) {
                insertBuilding(line, output);
                read = 0;
                if(getline(input, line) && line.size() > 2)
                    read = 1;
            }
        }
    }

    input.close();
    while(min_heap.size() > 0) {	// If all the inputs from the input file are taken care off - Then work on the remaining unfinished buildings.
        constructBuilding(output);
    }

    output.close();

}

