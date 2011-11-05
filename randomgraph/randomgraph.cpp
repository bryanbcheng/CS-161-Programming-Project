#include <fstream>
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct edge {
	int start;
	int end;
};

edge* generateGraph(edge* edges, int num_nodes, int num_edges)
{
	for (int i = 0; i < num_edges; i++) {
		edges[i].start = rand() % num_nodes + 1;
		edges[i].end = rand() % num_nodes + 1;
		
		if (edges[i].start == edges[i].end) i--;
		
		// with set else adds it to set and check if true or not
	}
	
	return edges;
}

int main(int argc, char* argv[])
{
    /* initialize random seed: */
	srand ( time(NULL) );
	
	int num_nodes = atoi(argv[1]);
	int num_edges = atoi(argv[2]);
    char* outputFile = argv[3];

	edge edges[num_edges];
	generateGraph(edges, num_nodes, num_edges);
	
	// MAY NEED TO SORT CORRECTLY
	
    // Output the generated random graph into a file.
    std::ofstream os;
    os.open(outputFile);
    os << argv[1] << "\n" << argv[2] << "\n";
	
	// NEED TO CHANGE THIS TO USE ITERATOR WITH A SET
	for (int i = 0; i < num_edges; i++) {
		os << edges[i].start << " " << edges[i].end << "\n";
	}
	
    os.close();
    return 0;
}

