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
    bool operator<(const edge &e) const
    { 
        if (start <= e.start && end <= e.end) {
            return false;
        }
        return true;
    }

} ;

set<edge> generateGraph(int num_nodes, int num_edges)
{
    set<edge> set;
	for (int i = 0; i < num_edges; i++) {
		edge e = {};
		e.start = rand() % num_nodes + 1;
		e.end = rand() % num_nodes + 1;
		
		//edges[i].start = rand() % num_nodes + 1;
		//edges[i].end = rand() % num_nodes + 1;
		int size = set.size();
		
		if (e.start == e.end) i--;
		else {
			set.insert(e);
			if (set.size() == size) i--;
            //cout << "added: " << edges[i].start << " " << edges[i].end << "\n";
        }
	}
	
	return set;
}

int main(int argc, char* argv[])
{
    /* initialize random seed: */
	srand ( time(NULL) );
	
	/*
	int milisec = 1000; // length of time to sleep, in miliseconds
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milisec * 1000000L;
	nanosleep(&req, (struct timespec *)NULL);
	*/
	
	int num_nodes = atoi(argv[1]);
	int num_edges = atoi(argv[2]);
    char* outputFile = argv[3];

	//edge edges[num_edges];
    set<edge> edgeSet = generateGraph(num_nodes, num_edges);
	
	// MAY NEED TO SORT CORRECTLY //
	
    // Output the generated random graph into a file.
    std::ofstream os;
    os.open(outputFile);
    os << argv[1] << "\n" << argv[2] << "\n";
    
    //cout << edgeSet.size() << "\n";
	
    for (set<edge>::iterator iter = edgeSet.begin(); iter != edgeSet.end(); ++iter) {
        edge e = *iter;
        os << e.start << " " << e.end << "\n";
        //cout << "iter\n";
    }
	
    os.close();
    return 0;
}

