#pragma once

const int SIZE = 100;
int numGraphs = 0;
bool notAllVerts = false, notHamiltonian = false;

void printCycle(fstream& outFile, int numVerts, int path[]) {
	cout << "\nHamiltonian Cycle:\n";
	outFile << "\nHamiltonian Cycle:\n";

	for (int i = 0; i < numVerts; i++) {
		cout << path[i] << " ";
		outFile << path[i] << " ";
	}
	
	//print the first vertex again
	cout << path[0] << endl;      
	outFile << path[0] << endl;

	if (notAllVerts == true) {
		cout << "Not all vertices are in the cycle\n";
		outFile << "Not all vertices are in the cycle\n";
		notAllVerts = false;
	}
}

bool isValid(fstream& outFile, int vert, int x, int path[], int graph[][SIZE]) {
	//if there is no edge
	if (graph[path[x - 1]][vert] == 0)	{
		return false;
	}

	//if vertex is already taken, skip that
	for (int i = 0; i < x; i++) {
		if (path[i] == vert) {
			cout << "Vertex " << path[i] << " has already been visited\n";
			outFile << "Vertex " << path[i] << " has already been visited\n";
			return false;
		}
	}

	return true;
}

bool cycleFound(fstream& outFile, int x, int numVerts, int path[], int graph[][SIZE]) {
	//when all vertices are in the path
	if (x == numVerts) {
		if (graph[path[x - 1]][path[0]] == 1) {
			return true;
		}
		else {

			notHamiltonian = true;
			return false;
		}
	}
	
	//for all vertices except starting point
	for (int v = 1; v < numVerts + 1; v++) {
		//if possible to add v in the path
		if (isValid(outFile, v, x, path, graph)) {
			path[x] = v;

			cout << "Add vertex " << path[x] << endl;
			outFile << "Add vertex " << path[x] << endl;

			cout << "Add edge " << path[x - 1] << "-" << path[x] << endl;
			outFile << "Add edge " << path[x - 1] << "-" << path[x] << endl;

			if (cycleFound(outFile, x + 1, numVerts, path, graph) == true) {
				return true;
			}
			else if (notHamiltonian) {
				return false;
			}
			else {
				cout << "Remove vertex " << path[x] + 1 << endl;
				outFile << "Remove vertex " << path[x] + 1 << endl;

				//when k vertex will not be in the solution
				path[x + 1] = -1;

				notAllVerts = true;
				return true;
			}
		}
	}

	return false;
}

bool hamiltonianCycle(fstream& outFile, int numVerts, int path[], int graph[][SIZE]) {
	for (int i = 0; i < numVerts; i++) {
		path[i] = -1;
	}

	path[0] = 1; //first vertex as 1
	cout << "Add vertex " << path[0] << endl;
	outFile << "Add vertex " << path[0] << endl;

	if (cycleFound(outFile, 1, numVerts, path, graph) == false) {

		cout << "\nNo Hamiltonian Cycle\n";
		outFile << "\nNo Hamiltonian Cycle\n";

		notHamiltonian = false;
		return false;
	}

	cout << "Add edge " << path[numVerts - 1] << "-" << path[0] << endl;
	outFile << "Add edge " << path[numVerts - 1] << "-" << path[0] << endl;

	printCycle(outFile, numVerts, path);
	return true;
}