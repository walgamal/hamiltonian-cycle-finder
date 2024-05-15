using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <ios>

#include "Hamiltonian.h"

void endProgram(fstream& inFile, fstream& outFile);

void newGraph(fstream& inFile, fstream& outFile) {
	int numVerts, numEdges, v1, v2;
	int currGraph[SIZE][SIZE];
	bool notValid = false, isDuplicate = false;
	int path[SIZE];

	numGraphs++;
	cout << "\n===========================================\n";
	outFile << "\n===========================================\n";
	cout << "\nGraph " << numGraphs << " Input:\n";
	outFile << "\nGraph " << numGraphs << " Input:\n";

	inFile >> numVerts;
	inFile >> numEdges;

	if (numVerts == 0) {
		cout << "Graph has no vertices\n";
		outFile << "Graph has no vertices\n";
		endProgram(inFile, outFile);
	}

	cout << numVerts << " Vertices\n";
	cout << numEdges << " Edges\n";
	outFile << numVerts << " Vertices\n";
	outFile << numEdges << " Edges\n";

	for (int i = 0; i < numVerts + 1; i++) {
		for (int j = 0; j < numVerts + 1; j++) {
			currGraph[i][j] = 0;
		}
	}

	for (int i = 0; i < numEdges; i++) {
		inFile >> v1;
		inFile >> v2;

		if (v1 == v2 || currGraph[v1][v2] != 0) {
			isDuplicate = true;
			cout << "Invalid Edge " << v1 << "-" << v2 << " Duplicate or Parallel Edge\n";
			outFile << "Invalid Edge " << v1 << "-" << v2 << " Duplicate or Parallel Edge\n";
			i--;
		}
		else if (v1 < 1 || v1 > numVerts || v2 < 1 || v2 > numVerts) {
			notValid = true;
			cout << "Invalid Edge " << v1 << "-" << v2 << " Invalid Vertex\n";
			outFile << "Invalid Edge " << v1 << "-" << v2 << " Invalid Vertex\n";
			i--;
		}
		else if (!notValid && !isDuplicate) {
			cout << "Add Edge " << v1 << "-" << v2 << endl;
			outFile << "Add Edge " << v1 << "-" << v2 << endl;
			currGraph[v1][v2] = 1;
			currGraph[v2][v1] = 1;
		}

		isDuplicate = false;
		notValid = false;
	}

	cout << "\nGraph " << numGraphs << " Vertices:\n";
	outFile << "\nGraph " << numGraphs << " Vertices:\n";

	for (int i = 1; i < numVerts + 1; i++) {
		cout << i << endl;
		outFile << i << endl;
	}

	cout << "\nGraph " << numGraphs << " Edges\n";
	outFile << "\nGraph " << numGraphs << " Edges\n";

	for (int i = 1; i < numVerts + 1; i++) {
		for (int j = 1; j < numVerts + 1; j++) {
			if (currGraph[i][j] == 1 && j > i) {
				cout << i << "-" << j << endl;
				outFile << i << "-" << j << endl;
			}
		}
	}

	//print Graph
	cout << "\nGraph " << numGraphs << " Matrix:\n";
	outFile << "\nGraph " << numGraphs << " Matrix:\n";
	for (int i = 0; i < numVerts; i++) {
		for (int j = 0; j < numVerts; j++) {
			cout << currGraph[i + 1][j + 1] << "  ";
			outFile << currGraph[i + 1][j + 1] << "  ";
		}
		cout << endl;
		outFile << endl;
	}

	//print path build
	cout << "\nGraph " << numGraphs << " Path Build\n";
	outFile << "\nGraph " << numGraphs << " Path Build\n";

	hamiltonianCycle(outFile, numVerts, path, currGraph);

	cout << "\n===========================================\n";
	outFile << "\n===========================================\n";
	
	if (!inFile.eof()) {
		newGraph(inFile, outFile);
	}
}

void endProgram(fstream& inFile, fstream& outFile) {
	if (!inFile.eof()) {
		newGraph(inFile, outFile); 
	}

	cout << "Program has completed. Thank you.\n";
	outFile << "Program has completed. Thank you.\n";
	cout << "===========================================\n";
	outFile << "===========================================\n";

	inFile.close();
	outFile.close();
	exit(0);
}


int main(){
	string fileName;
	fstream inFile, outFile;

	cout << "Welcome. The program has started successfully.\n";
	cout << "Enter a filename for the log file: \n";
	cin >> fileName;
	outFile.open(fileName);

	if (!outFile.is_open()) {
		cout << fileName << " could not be opened.\nProgram has completed. Thank you.";
		exit(1);
	}
	else {
		cout << fileName << " has opened successfully.\n";
	}

	cout << "\nEnter a filename for the graph file: \n";
	cin >> fileName;

	inFile.open(fileName);
	inFile.seekg(0, inFile.end);
		
	if (!inFile.is_open())	{
		cout << fileName << " could not be opened.\nProgram has completed. Thank you.";
		exit(2);
	}

	if (inFile.tellg() == 0) {
		cout << fileName << " is empty.\nProgram has completed. Thank you.";
		exit(2);
	}
	inFile.seekg(0, inFile.beg);	
	cout << fileName << " has opened successfully.\n";

	newGraph(inFile, outFile);

	cout << "Program has completed. Thank you.\n";
	outFile << "Program has completed. Thank you.\n";
	cout << "===========================================\n";
	outFile << "===========================================\n";

	inFile.close();
	outFile.close();
	return 0;
}