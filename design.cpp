#include <iostream>
#include <algorithm>
#include "design.h"
#include "gates.h"
#include "net.h"

using namespace std;

Design::Design()
{

}

Design::Design(string n)
{
	desname = n;
}

Design::~Design()
{

}

string Design::name()
{
	return desname;	
}

void Design::add_pi(string n)
{
	pis.push_back(n);
}

void Design::add_po(string n)
{
	pos.push_back(n);
}

Net *Design::find_net(string net_name)
{
	if(design_nets.find(net_name) == design_nets.end())
	{
		return NULL;
	}
	return (design_nets.find(net_name)->second);

}

Gate *Design::find_gate(string inst_name)
{
	if(design_gates.find(inst_name) == design_gates.end())
	{
		return NULL;
	}
	return (design_gates.find(inst_name)->second);
}

Net* Design::add_find_net(string n)
{
	map<string, Net*>::iterator it;
	for (it = design_nets.begin(); it != design_nets.end(); it++)
	{
		if (it->first == n)
		{
			return (it->second);
		}
	
	}
	
	design_nets[n] = new Net(n);
	return (design_nets[n]);
	
}

//
Gate* Design::add_find_gate(int gtype, string n, int d)
{
	map<string, Gate*>::iterator it;
	for(it = design_gates.begin(); it != design_gates.end(); it++)
	{
		if (it->first == n)
		{
		
			return (it->second);
		}
	}
	
	if(gtype == AND)
	{
		design_gates[n] = new And(n,d);
		
	}
	else if(gtype == OR)
	{
		design_gates[n] = new Or(n,d);
	}
	else if(gtype == NAND)
	{
		design_gates[n] = new Nand(n,d);
	}
	else if(gtype == NOR)
	{
		design_gates[n] = new Nor(n,d);
	}
	else if(gtype == XOR)
	{
		design_gates[n] = new Xor(n,d);
	}
	else if(gtype == NOT)
	{
		design_gates[n] = new Not(n,d);
	}
	return design_gates[n];
	
}

vector<Net *> *Design::get_pi_nets()
{
	
	vector<string>::iterator ite;
	map<string, Net*>::iterator iter;
	vector<Net*>* pi_nets;
	pi_nets = new vector<Net*>();
	
	
	
	for(iter = design_nets.begin(); iter != design_nets.end(); iter++)
	{
		for(ite = pis.begin(); ite != pis.end(); ite++)
		{
			if((iter->first) == *ite)
			{
				pi_nets->push_back(iter->second);
			}
		}
	}
	
	return pi_nets;
}

vector<Net *> *Design::get_po_nets()
{
	vector<string>::iterator ite;
	map<string, Net*>::iterator iter;
	vector<Net*>* po_nets;
	po_nets = new vector<Net*>();
	
	
	
	for(iter = design_nets.begin(); iter != design_nets.end(); iter++)
	{
		for(ite = pos.begin(); ite != pos.end(); ite++)
		{
			if((iter->first) == *ite)
			{
				po_nets->push_back(iter->second);
			}
		}
	}
	return po_nets;
}

vector<Net *> *Design::get_wire_nets()
{
	vector<string>::iterator it1;
	vector<string>::iterator it2;
	map<string, Net*>::iterator iter;
	vector<Net*>* wire_nets;
	wire_nets = new vector<Net*>();
	
	for(iter = design_nets.begin(); iter != design_nets.end(); iter++)
	{
		if(find(pis.begin(), pis.end(), iter->first)==pis.end() && find(pos.begin(), pos.end(), iter->first)==pos.end())
		{
			wire_nets->push_back(iter->second);
		}
	
	}
	return wire_nets;
}

vector<Net *> *Design::all_nets()
{
	map<string, Net*>::iterator it;
	vector<Net*>* all_nets;
	all_nets = new vector<Net*>();
	
	for(it = design_nets.begin(); it != design_nets.end(); it++)
	{
		all_nets->push_back(it->second);
	}
	
	return all_nets;
}

vector<Gate *> *Design::all_gates()
{
	map<string, Gate*>::iterator it;
	vector<Gate*>* all_gates;
	all_gates = new vector<Gate*>();
	
	for(it = design_gates.begin(); it != design_gates.end(); it++)
	{
		all_gates->push_back(it->second);
	}
	
	return all_gates;
}

void Design::dump(ostream &os)
{
	os << "module " << Design::name() << "(";
	vector<string>::iterator it;
	for(it = pis.begin(); it != pis.end(); it++)
	{
		os << *it << ",";
	}
	vector<string>::iterator it1;
	for(it1 = pos.begin(); it1 != pos.end()-1; it1++)
	{
		os << *it1 << ",";
	}
	os << *it1 << ")" << endl;
	
	for(it = pis.begin(); it != pis.end(); it++)
	{
		os << "	input " << *it << ";" << endl;
	}
	for(it1 = pos.begin(); it1 != pos.end(); it1++)
	{
		os << "	output " << *it1 << ";" << endl;
	}
	
	vector<Net*>* wire_nets;
	wire_nets = new vector<Net*>();
	wire_nets = Design::get_wire_nets();
	vector<Net*>::iterator it2;
	for (it2 = wire_nets->begin(); it2 != wire_nets->end(); it2++)
	{
		Net* temp = new Net();
		temp = *it2;
		string wirename = temp->name();
		os << "	wire " << wirename << ";" << endl;
	}
	
	map<string, Gate*>::iterator it3;
	for(it3 = design_gates.begin(); it3 != design_gates.end(); it3++)
	{
		Gate* temp;
		temp = it3->second;
		os<< "	";
		temp->dump(os);
		int delay = temp->getDelay();
		string name = temp->name();
		Net* nettemp;
		nettemp = new Net();
		nettemp = temp->getOutput();
		
		os << " #" << delay << " " << name << "(" << nettemp->name();
		
		vector<Net*>* input;
		input = new vector<Net*>();
		input = temp->getInputs();
		vector<Net*>::iterator it;
		for(it= input->begin(); it!= input->end(); it++)
		{
			Net* temp = new Net();
			temp = *it;
			os << ", " <<  temp->name();
		}
		os << ");" << endl;
		
	}
	os << "endmodule" << endl;
}
