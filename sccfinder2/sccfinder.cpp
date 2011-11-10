#include <fstream> 
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct Edge {
	int start;
	int end;
};

struct Node {
	int vertex;
	vector<Edge*> edges;
};

void hashEdge(Node* nodes, int start, int end)
{
	// look up current
	Edge *new_edge = new Edge();
	new_edge->start = start;
	new_edge->end = end;
	
	nodes[start - 1].edges.push_back(new_edge);
}

void getNodesAndEdges(ifstream& is, Node* nodes, int num_nodes, int num_edges)
{
	for (int i = 0; i < num_nodes; i++) {
		nodes[i].vertex = i + 1; // vertexs start from 1 and go to n
	}
	
	for (int i = 0; i < num_edges; i++) {
		int edge_start, edge_end;
		
		is >> edge_start;
		is >> edge_end;
		
		hashEdge(nodes, edge_start, edge_end);
	}
}

Node* getMax(Node* nodes, int num_nodes)
{
	int max = 0;
	Node *n = NULL;
	for (int i = 0; i < num_nodes; i++) {
		if (nodes[i].edges.size() > max) {
			n = &nodes[i];
			max = nodes[i].edges.size();
		}
	}
	return n;
}


/**
 * Given an input file (inputFile) and an integer array (out) of size 5, fills
 * the 5 largest SCC sizes into (out) in decreasing order. In the case where
 * there are fewer than 5 components, you should fill in 0 for the remaining
 * values in (out). For example, if there are only 2 components of size 100 and
 * 50, you should fill:
 * out[0] = 100
 * out[1] = 50
 * out[2] = 0
 * out[3] = 0
 * out[4] = 0
 */
void findSccs(char* inputFile, Node **n)
{
	std::ifstream is;
	is.open(inputFile, ios::in);
	
	int num_nodes, num_edges;
	
	is >> num_nodes;
	is >> num_edges;
	
	Node* nodes = new Node[num_nodes + 1];
	
	getNodesAndEdges(is, nodes, num_nodes, num_edges);
	
	(*n) = getMax(nodes, num_nodes);
}

/*
 * sccfinder should be your main class. If you decide to code in C, you can
 * rename this file to sccfinder.c. We only want your binary to be named
 * sccfinder and we want "make sccfinder" to build sccfinder.
 * Main takes two arguments: 1) input file and 2) output file.
 * You should fill in the findSccs function.
 * Warning: Don't change the part of main that outputs the result of findSccs.
 * It outputs in the correct format.
 */
int main(int argc, char* argv[])
{
    Node *n;
    char* inputFile = argv[1];
    char* outputFile = argv[2];

    findSccs(inputFile, &n);
	
    // Output the first 5 sccs into a file.
    std::ofstream os;
    os.open(outputFile);
    os << n->vertex << "\t" << n->edges.size() << "\t" << endl;
    os.close();
    return 0;
}

