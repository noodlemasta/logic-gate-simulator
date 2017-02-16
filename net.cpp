#include <iostream>
#include "net.h"

using namespace std;

Net::Net()
{
	drivers = new vector<Gate*>();
	loads = new vector<Gate*>();
}

Net::Net(string n)
{
	netname = n;
	drivers = new vector<Gate*>();
	loads = new vector<Gate*>();
}

Net::~Net()
{
	delete drivers;
	delete loads;
}

void Net::addDriver(Gate *g)
{
	
	drivers->push_back(g);
	
}

void Net::addLoad(Gate *g)
{
	loads->push_back(g);
}

vector<Gate *>* Net::getLoads()
{
	return loads;
}

vector<Gate *>* Net::getDrivers()
{ 
	return drivers;
}

string Net::name()
{
	return netname;
}


void Net::setVal(char v)
{

}

char Net::computeVal()
{

}

char Net::getVal()
{
	return val;
}

void Net::printDriversLoads()
{

}

