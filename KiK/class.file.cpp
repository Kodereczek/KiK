// Filename: class.file.cpp
// Author:   Patryk Połeć

#include "engine.h"

////////////////////////////////////////////////////////////////////////////////////////////////// C_File::Constructor and destructor
C_File::C_File()
{
	position1 = 0;
	position2 = 0;

	data = "";
	line = "";
}

C_File::~C_File()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////// C_File::Protected methods
void C_File::OpenFile(string _pathFile, ios_base::openmode _mode)
{
	file.open(_pathFile.c_str(), _mode);
}

void C_File::CloseFile()
{
	file.close();
}

void C_File::LoadData()
{
	data.clear();

	SetPoinerAt(ios::beg);

	while(!file.eof())
    {
        getline(file, line);
		data += line + "\n";
    }

	SetPoinerAt(ios::beg);
}

void C_File::SaveData()
{
	file << data;
}

void C_File::SetPoinerAt(int _option)
{
	file.clear();
	file.seekg(0, _option);
}

size_t C_File::ReturnPositionPointner()
{
	return (size_t)file.tellg();
}

int C_File::ReturnLengthData()
{
	LoadData();
	return (int)data.length() - 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////// C_Config::Constructor and destructor
C_Config::C_Config(string _pathFile)
{
	OpenFile(_pathFile, ios::in | ios::out);
}

C_Config::~C_Config()
{
	CloseFile();
}

////////////////////////////////////////////////////////////////////////////////////////////////// C_Config::Public methods
void C_Config::SetValue(string _nameKey, string _value)
{
	string currentValue = GetValueS(_nameKey);

	if(currentValue != "")
	{
		LoadData();
		position1 = data.find(_nameKey + "=" + currentValue);
		data = data.replace(position1 + _nameKey.length() + 1, currentValue.length(), _value);
		SaveData();
	}
}

string C_Config::GetValueS(string _nameKey)
{
	LoadData();

	position1 = data.find(_nameKey);
	if(position1 != string::npos)
	{
		data = data.substr(position1 + _nameKey.length() + 1);
		position2 = data.find_first_of("\n");

		return data.substr(0, position2);
	}
	else
		return "";
}

int C_Config::GetValueI(string _nameKey)
{
	LoadData();

	position1 = data.find(_nameKey);
	if(position1 != string::npos)
	{
		data = data.substr(position1 + _nameKey.length() + 1);
		position2 = data.find_first_of("\n");

		return atoi(data.substr(0, position2).c_str());
	}
	else
		return 0;
}

float C_Config::GetValueF(string _nameKey)
{
	LoadData();

	position1 = data.find(_nameKey);
	if(position1 != string::npos)
	{
		data = data.substr(position1 + _nameKey.length() + 1);
		position2 = data.find_first_of("\n");

		return (float)atof(data.substr(0, position2).c_str());
	}
	else
		return 0.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////// C_Log::Constructor and destructor
C_Log::C_Log(string _pathFile)
{
	OpenFile(_pathFile, ios::out | ios::trunc);
}

C_Log::~C_Log()
{
	CloseFile();
}

////////////////////////////////////////////////////////////////////////////////////////////////// C_Log::Public methods
void C_Log::AddWarning(string _textWarning, string _param)
{
	data.clear();

	(_param == "") ? data = "Warning: " + _textWarning + "\n" : data = "Warning: " + _textWarning + " \"" + _param + "\"\n";

	SaveData();
}

void C_Log::AddError(string _textError, string _param, int &_state)
{
	data.clear();

	(_param == "") ? data = "Error: " + _textError + "\n" : data = "Error: " + _textError + " \"" + _param + "\"\n";

	_state = -1;

	SaveData();
}

void C_Log::AddTest(string _textTest)
{
	data.clear();

	data = _textTest;

	SaveData();
}