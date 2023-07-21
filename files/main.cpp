#include <iostream>
#include <fstream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_FROM_FILE


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

		//Закрываем поток
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif // READ_FROM_FILE

}