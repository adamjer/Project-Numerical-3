/*
	Made by Adam Jereczek
	Index: 149448
*/
#pragma once

#include "Factory.h"

using namespace Interpolation;

int main(int argc, char *argv[])
{
	Factory *factory = new Factory();
	factory->init();
	factory->interpolate(101);
	factory->interpolate(505);
	factory->interpolate(1010);

	delete factory;
	return 0;
}