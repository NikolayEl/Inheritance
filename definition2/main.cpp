#include <iostream>
#include <vector>

using namespace std;

class Definition
{
	std::string name;
	std::string definit;
public:
	const std::string& get_name() const
	{
		return name;
	}
	const std::string& get_definit() const
	{
		return definit;
	}
	void set_name(const std::string& name)
	{
		this->name = name;
	}
	void set_definit(const std::string& definit)
	{
		this->definit = definit;
	}

	//				Constructor
	Definition(const std::string& name, const std::string& definit) :name(name), definit(definit)
	{
		cout << "Constructor:\t" << this << endl;
	}
	~Definition()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//				Method's
	void print() const
	{
		cout << name << ": " << definit << endl;
	}
};

class Definitiones
{
	std::vector<Definition> deF;

public:
	struct Exception {};
	Definition Search(const std::string& letters)
	{
		for (auto& r : deF)
			if (r.get_name() == letters) return r;
		throw Exception();
	}
};

void main()
{
	setlocale(LC_ALL, "");
}