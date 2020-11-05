#pragma once

#include <iostream>
using namespace std;

class Process
{
private:
	string name;
	int runtime;
public:
	Process() 
	{
		this->name = "Std_name";
		this->runtime = 0;
	}
	Process(string name, int runtime)
	{
		this->name = name;
		this->runtime = runtime;
	}
	~Process() {};

	void operator =(Process& pr)
	{
		this->name = pr.name;
		this->runtime = pr.runtime;
	}

	friend ostream& operator<<(ostream& out, Process pr)
	{
		out << pr.name << " " << pr.runtime;
		return out;
	}

	friend istream& operator>>(istream& in, Process pr)
	{
		in >> pr.name >> pr.runtime;
		return in;
	}
};