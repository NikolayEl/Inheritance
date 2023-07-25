#include <iostream>
#include <fstream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
//#define READ_FROM_FILE


void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	cout << "Hello files" << endl;
	//1) Создаем поток
	std::ofstream fout;
	//2) Открываем поток
	fout.open("file.txt", std::ios_base::app);
	//3) Пишем в поток
	fout << "Hello files" << endl;
	fout << "Ну привет" << endl;
	//4) Закрываем поток:
	fout.close();

	system("start notepad file.txt");
#endif // WHRITE_TO_FILE

#ifdef READ_FROM_FILE
	//1)  Создаем поток:
	std::ifstream fin;
	//2) Открываем поток:
	fin.open("file.txt");
	//3) Проверяем открылся ли поток:
	if (fin.is_open())
	{
		//TODO: read file
		while (!fin.eof())
		{
			const int SIZE = 10256;
			char sz_buffer[SIZE] = {};
			//fin >> sz_buffer;
			fin.getline(sz_buffer, SIZE);
			cout << sz_buffer << endl;
		}
		//Закрываем поток
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif // READ_FROM_FILE
	//Создаем и открываем входящий поток
	//Открываем сразу исходящий поток
	std::ifstream fin("201 ready.txt");
	std::ofstream fout_raw("201 RAW.txt");
	std::ofstream fout_DHCPD("201 DHCPD");
	if (fin.is_open())
	{
		const int MAC_SIZE = 18;
		const int IP_SIZE = 16;
		char* cz_mac_buffer = new char[MAC_SIZE] {};
		char* cz_ip_buffer = new char[IP_SIZE] {};
		while (!fin.eof())
		{
			fin >> cz_mac_buffer >> cz_ip_buffer;
			if (strlen(cz_ip_buffer) == 0) continue;
			fout_raw << cz_ip_buffer << "\t" << cz_mac_buffer << endl;
			cout << cz_ip_buffer << "\t" << cz_mac_buffer << endl;
		}
		cout << endl << endl;
		fin.clear();
		fin.seekg(0);
		for (int i = 0; !fin.eof(); i++)
		{
			fin >> cz_mac_buffer >> cz_ip_buffer;
			if (strlen(cz_ip_buffer) == 0) continue;
			fout_DHCPD << "host 201-" << i + 1 << endl;
			fout_DHCPD << "{\n";
			for (int j = 0; j < strlen(cz_mac_buffer); j++) if (cz_mac_buffer[j] == '-') cz_mac_buffer[j] = ':';
			fout_DHCPD << "\t" << "hardware ethernet\t" << cz_mac_buffer << ";" << endl;
			fout_DHCPD << "\tfixed-adress\t\t" << cz_ip_buffer << ";" << endl;
			fout_DHCPD << "}\n";

			cout << "host 201-" << i + 1 << endl;
			cout << "{\n";
			cout << "\t" << "hardware ethernet\t" << cz_mac_buffer << ";" << endl;
			cout << "\tfixed-adress\t\t" << cz_ip_buffer << ";" << endl;
			cout << "}\n";
		}
		fin.close();
	}
	else
	{
		cerr << "Error: File not open!" << endl;
	}
	fout_raw.close();
	fout_DHCPD.close();
	system("start notepad 201 RAW.txt");
	system("start notepad 201 DHCPD");
}