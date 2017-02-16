#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "net.h"
#include "gates.h"
#include "design.h"
#include "parse.h"

using namespace std;
int parsegate(Design* d, stringstream& ss, int line_no, int g_type)
{
			string next_token_temp;
			string next_token;
			getline(ss, next_token_temp, '(');
			//cout << next_token_temp << endl;
			
			string nexttoken;
			stringstream s1(next_token_temp);
			s1 >> next_token;
			s1 >> nexttoken;
			Gate* gatetemp;
			
			//delay included
			if(!s1.fail())
			{
				string delaynum = next_token.substr(1,1);
				int i = atoi(delaynum.c_str());
				//cout << "delay: " << next_token << endl;
				//cout << "delay num: " << i << endl;
				//cout << "gate name: " << nexttoken <<  endl;
				gatetemp = d->add_find_gate(g_type, nexttoken, i);
			}
			//not included
			else
			{
				//cout << "Gate name: " << next_token <<  endl;
				gatetemp = d->add_find_gate(g_type, next_token, 1);
			}
			
			//PORTS
			string port_list;
			getline(ss, port_list, ')');
			//cout << port_list<< endl;
			stringstream s2(port_list);
			
				//1st item (output)
			string output;
			getline(s2, output, ',');
			//cout << "output: " << output << endl;
			
			Net* nettemp = d->find_net(output);
			if(nettemp == NULL)
			{
				cout << "Output inputed for ";
				gatetemp->dump(cout);
				cout << " gate " << gatetemp->name() << " at line " << line_no << " is incorrect." << endl;
				return -1;
			}
			else
			{
			nettemp->addDriver(gatetemp);
			gatetemp->addOutput(nettemp);
			}
				//rest of the items (input)
			if(s2.eof())
			{
				cout << "not enough input for inputs!" << endl;
				return -1;
			}	
			else
			{
			while(!s2.eof())
			{
				string inputtemp;
				string input;
				getline(s2, inputtemp, ',');
				stringstream ss(inputtemp);
				ss >> input;
				//cout << "input: " << input << endl;
				
				Net* nettemp = d->find_net(input);
				if(nettemp == NULL)
				{
					cout << "Input inputed for ";
					gatetemp->dump(cout);
					cout << " gate " << gatetemp->name() << " at line " << line_no << " is incorrect." << endl;
					return NULL;
				}
				else
				{
				nettemp->addLoad(gatetemp);
				gatetemp->addInput(nettemp);
				}
			}
			}
			return 0;
}

Design* parse(char* filename)
{
	ifstream infile(filename);
	Design* d;
	
	if(!infile.good() )
	{
    	cout << "Unable to open file: " << filename << endl;
    	return NULL;
 	}
	
	
	int line_no = 0;
	string line_of_text;
	while (!infile.eof())
	{
		getline(infile, line_of_text);
		line_no++;
		
		stringstream ss(line_of_text);
		string token;
		ss >> token;
		if (ss.fail() || token == "//")
		{
			continue;
		}
		else
		{
			//cout << token << endl;
		}

		if (token == "module")
		{
			string next_token_temp;
			string next_token;
			getline(ss, next_token_temp, '(');
			stringstream s1(next_token_temp);
			s1 >> next_token;
			//cout << next_token << endl;
			
			d = new Design(next_token);
		
			string port_list;
			getline(ss, port_list, ')');
			//cout << port_list<< endl;
			stringstream s2(port_list);
			while(! s2.eof())
			{
				string port_temp;
				string port;
				getline(s2, port_temp, ',');
				stringstream s3(port_temp);
				s3 >> port;
				//cout << port << endl;
			}
		}
		else if (token == "input")
		{
			string next_token_temp;
			string next_token;
			getline(ss, next_token_temp, ';');
			stringstream s1(next_token_temp);
			s1 >> next_token;
			//cout << next_token << endl; 
			
			d->add_pi(next_token);
			d->add_find_net(next_token);
		}
		else if (token == "output")
		{
			string next_token_temp;
			string next_token;
			getline(ss, next_token_temp, ';');
			stringstream s1(next_token_temp);
			s1 >> next_token;
			//cout << next_token << endl; 
			
			d->add_po(next_token);
			d->add_find_net(next_token);
		}
		
		else if (token == "wire")
		{
			string next_token_temp;
			string next_token;
			getline(ss, next_token_temp, ';');
			stringstream s1(next_token_temp);
			s1 >> next_token;
			//cout << next_token << endl;
			
			d->add_find_net(next_token);
		}
		else if (token == "and")
		{
			int i = parsegate(d, ss, line_no, AND);
			if( i == -1)
			{
				return NULL;
			}
		}
		else if (token == "or")
		{
			int i = parsegate(d, ss, line_no, OR);
			if( i == -1)
			{
				return NULL;
			}
		}
		else if(token == "nand")
		{
			int i = parsegate(d, ss, line_no, NAND);
			if( i == -1)
			{
				return NULL;
			}
		}
		else if(token == "nor")
		{
			int i = parsegate(d, ss, line_no, NOR);
			if( i == -1)
			{
				return NULL;
			}
		}
		else if(token == "xor")
		{
			int i = parsegate(d, ss, line_no, XOR);
			if( i == -1)
			{
				return NULL;
			}
		}
		else if(token == "not")
		{
			int i = parsegate(d, ss, line_no, NOT);
			if( i == -1)
			{
				return NULL;
			}	
		}
		else if(token == "endmodule")
		{}
		else
		{
			cout << "error at coding input keyword at line: " << line_no << endl;
			break;
		}
	}
	
	return d;
}
