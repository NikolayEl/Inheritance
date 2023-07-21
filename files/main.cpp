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
	//1) ������� �����
	std::ofstream fout;
	//2) ��������� �����
	fout.open("file.txt", std::ios_base::app);
	//3) ����� � �����
	fout << "Hello files" << endl;
	fout << "�� ������" << endl;
	//4) ��������� �����:
	fout.close();

	system("start notepad file.txt");
#endif // WHRITE_TO_FILE

#ifdef READ_FROM_FILE
	//1)  ������� �����:
	std::ifstream fin;
	//2) ��������� �����:
	fin.open("file.txt");
	//3) ��������� �������� �� �����:
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
		//��������� �����
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif // READ_FROM_FILE

}