// Filename: class.converter.h
// Author:   Patryk Po³eæ

#pragma once

class C_Converter
{
	// Constructor and destructor
	public:
		C_Converter();
		~C_Converter();

	// Public methods
	public:
		string ToS(int _value);
		string ToS(float _value);

		   int ToI(string _value);

		 float ToF(string _value);
		 
	// Private methods
	private:

	// Public fields
	public:

	// Private fields
	private:

};