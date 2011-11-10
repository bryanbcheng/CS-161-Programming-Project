#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define NUM_FILES 100

void processFiles(int num_nodes)
{
	int count = 0;
	for (int i = 0; i < NUM_FILES; i++) {
		
		char inputFile[50];
		sprintf (inputFile, "../randomgraph/output/output%d.txt", i);
		
		std::ifstream is;
		is.open(inputFile, ios::in);
		
		int out[5];
		
		is >> out[0];
		is >> out[1];
		is >> out[2];
		is >> out[3];
		is >> out[4];
		
		cout << "0: " << out[0] << " 1: " << out[1] << " 2: " << out[2] << " 3: " << out[3] << " 4: " << out[4] << endl;
		
		if (out[0] == num_nodes && out[1] == 0) count++;
	}
	
	cout << "total: " << count << "/" << NUM_FILES << " - " << ((double)count)/NUM_FILES << endl; 
}

int main(int argc, char* argv[])
{
    int num_nodes = atoi(argv[1]);
	
	processFiles(num_nodes);

    return 0;
}

