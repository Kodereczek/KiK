// Filename: class.file.h
// Author:   Patryk Połeć

#pragma once

class C_File
{
	// Constructor and destructor
	public:
		C_File();
		~C_File();

	// Public methods
	public:

	// Private methods
	private:

	// Protected methods
	protected:
		void OpenFile(string _pathFile, ios_base::openmode _mode);
		void CloseFile();

		void LoadData();
		void SaveData();

		void SetPoinerAt(int _option);
	  size_t ReturnPositionPointner();
		 int ReturnLengthData();

	// Public fields
	public:

	// Private fields
	private:

	// Protected fields
	protected:
		fstream 
			file;

		size_t
			position1,
			position2;

		string
			data,
			line;
};

// Class C_Config
class C_Config: public C_File
{
	// Constructor and destructor
	public:
		C_Config(string _pathFile);
		~C_Config();

	// Public methods
	public:
		void SetValue(string _nameKey, string _value);

	  string GetValueS(string _nameKey);
		 int GetValueI(string _nameKey);
	   float GetValueF(string _nameKey);

	// Private methods
	private:

	// Public fields
	public:

	// Private fields
	private:

};

// Class C_Log
class C_Log: public C_File
{
	// Constructor and destructor
	public:
		C_Log(string _pathFile);
		~C_Log();

	// Public methods
	public:
		void AddWarning(string _textWarning, string _param = "");
	    void AddError(string _textError, string _param, int &_state);
		void AddTest(string _textTest);

	// Private methods
	private:

	// Public fields
	public:

	// Private fields
	private:

};