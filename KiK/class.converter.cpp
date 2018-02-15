// Filename: class.converter.cpp
// Author:   Patryk Po³eæ

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// Constructor and destructor
C_Converter::C_Converter()
{
	
}

C_Converter::~C_Converter()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////// Public methods
string C_Converter::ToS(int _value)
{
	stringstream value;
	value.str("");
	value << _value;

	return value.str();
}

string C_Converter::ToS(float _value)
{
	stringstream value;
	value.str("");
	value << _value;

	return value.str();
}

int C_Converter::ToI(string _value)
{
	return atoi(_value.c_str());
}

float C_Converter::ToF(string _value)
{
	return (float)atof(_value.c_str());
}