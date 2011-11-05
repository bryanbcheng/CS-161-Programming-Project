#include <fstream> 
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
	int vertex;
	bool explored;
};

struct edge {
	int start;
	int end;
	edge* next_edge;
};

struct scc {
	int leader;
	int components;
};

bool sccComp (scc i, scc j) { return (i.components > j.components); }

void hashEdge(map<int, edge*>& edges, int start, int end)
{
	// look up current
	edge *new_edge = new edge();
	new_edge->start = start;
	new_edge->end = end;
	new_edge->next_edge = edges[start];
	
	edges[start] = new_edge;
	//cout << "start: " << edges[start]->start << " end: " << edges[start]->end << " next: " << edges[start]->next_edge << endl;
}

void getNodesAndEdges(ifstream& is, node* nodes, map<int, edge*>& edgesfw, map<int, edge*>& edgesbk, int num_nodes, int num_edges)
{
	for (int i = 0; i < num_nodes; i++) {
		nodes[i].vertex = i + 1; // vertexs start from 1 and go to n
		nodes[i].explored = 0;
		//cout << "vertex: " << nodes[i].vertex << endl;
	}
	
	for (int i = 0; i < num_edges; i++) {
		int edge_start, edge_end;
		
		is >> edge_start;
		is >> edge_end;
		
		hashEdge(edgesfw, edge_start, edge_end);
		hashEdge(edgesbk, edge_end, edge_start);
		
		//is >> edges[i].start;
		//is >> edges[i].end;
		//cout << "start: " << edges[i].start << " end: " << edges[i].end << endl;
	}
}

void exploreNode(node* nodes, node* node, map<int, edge*>& edges, edge* edge, int* new_nodes, int* count)
{
	if (node->explored) return;
	
	node->explored = true;
	
	while (edge != NULL) {
		exploreNode(nodes, &nodes[edge->end - 1], edges, edges[nodes[edge->end - 1].vertex], new_nodes, count);
		
		edge = edge->next_edge;
	}
	
	new_nodes[*count] = node->vertex;
	(*count)++;
	//node->explored = true;
}

void dfsSubroutineFinishingTime(node* nodes, map<int, edge*>& edgesbk, int num_nodes, int* new_nodes)
{
	int count = 0;
	
	// Count down from n-1 to 0
	for (int i = num_nodes - 1; i >= 0; i--) {
		exploreNode(nodes, &nodes[i], edgesbk, edgesbk[nodes[i].vertex], new_nodes, &count);		
	}
}

void assignLeader(node* nodes, node* node, map<int, edge*>& edges, edge* edge, int* count)
{
	if (!node->explored) return; // all explores are set to true from previous dfs loop
	
	node->explored = false;
	
	while (edge != NULL) {
		assignLeader(nodes, &nodes[edge->end - 1], edges, edges[nodes[edge->end - 1].vertex], count);
		
		edge = edge->next_edge;
	}
	
	(*count)++;
	//node->explored = false;
}

void dfsSubroutineLeader(node* nodes, map<int, edge*>& edgesfw, int num_nodes, int* new_nodes, vector<scc>& leaders)
{
	for (int i = num_nodes - 1; i >= 0; i--) {
		int count = 0;
		
		assignLeader(nodes, &nodes[new_nodes[i] - 1], edgesfw, edgesfw[new_nodes[i]], &count);
		
		if (count >= 1) {
			scc s = {new_nodes[i], count};
			
			leaders.push_back(s);
		}
	}
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
void findSccs(char* inputFile, int out[5])
{
	std::ifstream is;
	is.open(inputFile, ios::in);
	
	int num_nodes, num_edges;
	
	is >> num_nodes;
	is >> num_edges;
	
	node nodes[num_nodes];
	map<int, edge*> edgesfw;
	map<int, edge*> edgesbk;
	
	getNodesAndEdges(is, nodes, edgesfw, edgesbk, num_nodes, num_edges);
	
	// implement algorithm to find SCCs
	int new_nodes[num_nodes];
	dfsSubroutineFinishingTime(nodes, edgesbk, num_nodes, new_nodes);
	
	// dfs subroutine forwards to find leaders
	vector<scc> scc_leaders;
	dfsSubroutineLeader(nodes, edgesfw, num_nodes, new_nodes, scc_leaders);
	
	// sort leaders vector
	sort(scc_leaders.begin(), scc_leaders.end(), sccComp);
	
	out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    out[4] = 0;
	
	for (int i = 0; i < 5; i++) {
		out[i] = scc_leaders[i].components;
	}   
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
    int sccSizes[5];
    char* inputFile = argv[1];
    char* outputFile = argv[2];

    findSccs(inputFile, sccSizes);
	
    // Output the first 5 sccs into a file.
    std::ofstream os;
    os.open(outputFile);
    os << sccSizes[0] << "\t" << sccSizes[1] << "\t" << sccSizes[2] <<
      "\t" << sccSizes[3] << "\t" << sccSizes[4];
    os.close();
    return 0;
}

