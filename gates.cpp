#include <iostream>
#include "gates.h"
#include "net.h"

using namespace std;

Gate::Gate()
{
	inputs = new vector<Net*>();
}

Gate::Gate(string n, int d)
{
	inst_name = n;
	delay = d;
	inputs = new vector<Net*>();
	
}

Gate::~Gate()
{
	delete inputs;
	delete output;
}

string Gate::name()
{
	return inst_name;
}

void Gate::addInput(Net *n)
{
	inputs->push_back(n);
}

void Gate::addOutput(Net *n)
{
	output = n;
}

vector<Net *> *Gate::getInputs()
{
	return inputs;
}

Net* Gate::getOutput()
{
	return output;
}

int Gate::getNumInputs()
{
	return (int) inputs->size();
}

int Gate::getDelay()
{
	return delay;
}

//And
And::And(): Gate()
{
	
}

And::And(string n, int d): Gate(n,d)
{
	
}

And::~And()
{
	delete inputs;
	delete output;
}

char And::eval()
{

}

void And::dump(ostream &os)
{
	os<< "and";
}

//Or
Or::Or(): Gate()
{

}

Or::Or(string n, int d): Gate(n,d)
{

}

Or::~Or()
{
	delete inputs;
	delete output;
}

char Or::eval()
{

}

void Or::dump(ostream& os)
{
	os << "or";
}

//Nor
Nor::Nor(): Gate()
{

}

Nor::Nor(string n, int d): Gate(n,d)
{

}

Nor::~Nor()
{
	delete inputs;
	delete output;
}

char Nor::eval()
{

}

void Nor::dump(ostream& os)
{
	os << "nor";
}

//Nand
Nand::Nand(): Gate()
{

}

Nand::Nand(string n, int d): Gate(n,d)
{

}

Nand::~Nand()
{
	delete inputs;
	delete output;
}

char Nand::eval()
{

}

void Nand::dump(ostream& os)
{
	os << "nand";
}

//Xor
Xor::Xor(): Gate()
{

}

Xor::Xor(string n, int d): Gate(n,d)
{

}

Xor::~Xor()
{
	delete inputs;
	delete output;
}

char Xor::eval()
{

}

void Xor::dump(ostream& os)
{
	os << "xor";
}

//Not
Not::Not(): Gate()
{

}

Not::Not(string n, int d): Gate(n,d)
{

}

Not::~Not()
{
	delete inputs;
	delete output;
}

char Not::eval()
{

}

void Not::dump(ostream& os)
{
	os << "not";
}
