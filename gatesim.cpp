#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "net.h"
#include "gates.h"
#include "design.h"
#include "parse.h"

using namespace std;



int main(int argc, char * argv[])
{
	char* inputfile = argv[1];
	Design* des = new Design();	
	des = parse(inputfile);
	if( des != NULL)
	{
	des->dump(cout);
	ofstream outfile("output.v");
	des->dump(outfile);
	}
	else
	{
		cout << "Can't dump file due to error" << endl;
	}
	
	delete des;
	return 0;
}

