#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void load(const std::string filename, std::string*& str, const int counter);
int counter_line(const std::string filename);
void words_from_line(std::string*& line, const int n, std::string*& ip_adress, std::string*& mac_adress);
void save(std::string filename, const int n, std::string*& ip_adress, std::string*& mac_adress, const std::string key);

void main()
{
	setlocale(LC_ALL, "");
	string filename = "201 RAW.txt";
	int count_line_in_file = counter_line(filename);
	std::string* line = new string[count_line_in_file]{};
	load(filename, line, count_line_in_file);
	std::string* ip_adress = new string[count_line_in_file]{};
	std::string* mac_adress = new string[count_line_in_file]{};
	words_from_line(line, count_line_in_file, ip_adress, mac_adress);
	save("201 ready.txt", count_line_in_file, ip_adress, mac_adress, "ready");
	save("201 DHCPD", count_line_in_file, ip_adress, mac_adress, "DHCPD");

	//for (int i = 0; i < count_line_in_file; i++) cout << line[i] << endl;
}
int counter_line(const std::string filename)
{
	//1) Создаем и открываем поток
	std::ifstream fin(filename);
	//2) Проверяем открылся ли поток
	int counter;
	if (fin.is_open())
	{
		for (counter = 0; !fin.eof(); counter++)
		{
			std::string temp;
			std::getline(fin, temp);
		}
		fin.close();
		return counter;
	}
	else
	{
		std::cerr << "Errror: File not found" << endl;
		fin.close();
		return 0;
	}
}
void load(const std::string filename, std::string*& line, const int counter)
{
	//1) Создаем и открываем поток
	std::ifstream fin(filename);
	//2) Проверяем открылся ли поток
	if (fin.is_open())
	{
		for (int i = 0; !fin.eof(); i++)
		{
			std::getline(fin, line[i]);
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
		fin.close();
	}
}
void words_from_line(std::string*& line, const int n, std::string*& ip_adress, std::string*& mac_adress)
{
	for (int i = 0; i < n - 1; i++)
	{
		string temp = line[i];
		int position = 0;
		position = temp.find(" ", 0);
		ip_adress[i] = temp.substr(0, position);
		mac_adress[i] = temp.substr(position);
		for (int j = 0; j < mac_adress[i].size(); j++)
		{
			if (mac_adress[i][j] == ' ' && mac_adress[i][j + 1] != ' ')
			{
				mac_adress[i] = mac_adress[i].substr(j + 1);
				break;
			}
		}
		cout << "ip adress:\t" << ip_adress[i] << endl;
		cout << "mac adress:\t" << mac_adress[i] << endl;
	}
}
void save(std::string filename, const int n, std::string*& ip_adress, std::string*& mac_adress, const std::string key)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n - 1; i++)
	{
		string temp = mac_adress[i];
		if (key == "DHCPD") fout << "host 201-" << i + 1 << endl << "{" << endl << "\thardware ethernet\t";
		if (key == "DHCPD") for (int j = 0; j < temp.size(); j++) if (temp[j] == '-')temp[j] = ':';
		fout << temp;
		if (key == "DHCPD") fout << ";" << endl << "\tfixed-address\t";
		fout << "\t" << ip_adress[i];
		if (key == "DHCPD") fout << ";" << endl << "}" << endl;
		fout << endl;
	}
	fout.close();
}