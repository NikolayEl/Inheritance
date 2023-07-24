#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define delimitr "\n------------------------------------------------------------------------------\n"
int counter;

class Human;
class Student;
class Teacher;
class Gradute;

std::ostream& operator<<(std::ostream& out, const Human& obj);
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj);
void print(Human** group, const int n);
void save(Human** group, const int n, const string file);
Human** load(const std::string& filename, int& n);
Human* HumanFactory(const std::string& type);
std::ifstream& operator>>(std::ifstream& ifs, Human& obj);
//string remove_spaces(string line);
class Human
{
protected:
	static const int LAST_NAME_WIDTH = 12;
	static const int FIRST_NAME_WIDTH = 12;
	static const int AGE_WIDTH = 5;
	static int count;
private:
	string last_name;
	string first_name;
	int age;

public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	Human(const std::string& last_name, const std::string& first_name, int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		count++;
		counter++;
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		count--;
		cout << "HDestructor:\t" << this << endl;
	}

	virtual std::ostream& print(std::ostream& out) const
	{
		return out << last_name << " " << first_name << " " << age ;
	}
	virtual std::ofstream& print(std::ofstream& ofs) const
	{
		ofs << typeid(*this).name() << ": \t";
		ofs.width(LAST_NAME_WIDTH);
		ofs << std::left;
		ofs << last_name;
		ofs.width(FIRST_NAME_WIDTH);
		ofs << std::left;
		ofs << first_name;
		ofs.width(AGE_WIDTH);
		ofs << std::left;
		ofs << age;
		return ofs;
	}
	virtual std::ifstream& scan(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
};

int Human::count = 0;

class Student:public Human
{
	static const int SPECILITY_WIDTH = 22;
	static const int GROUP_WIDTH = 10;
	static const int RAITING_WIDTH = 8;
	static const int ATTENDANCE_WIDTH = 8;
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality() const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_raiting()const
	{
		return rating;
	}
	double get_attendance() const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_raiting(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//						constructors
	Student(const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality, const std::string& group, double raiting, double attendance
	):Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_group(group);
		set_raiting(raiting);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	std::ostream& print(std::ostream& out)const
	{
		Human::print(out) << " ";
		return out << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& print(std::ofstream& ofs)const
	{
		Human::print(ofs);
		ofs.width(SPECILITY_WIDTH);
		ofs << speciality;
		ofs.width(GROUP_WIDTH);
		ofs << group;
		ofs.width(RAITING_WIDTH);
		ofs << rating;
		ofs.width(ATTENDANCE_WIDTH);
		ofs << attendance;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)
	{
		Human::scan(ifs);
		char sz_speciality[SPECILITY_WIDTH + 1] = {};
		ifs.read(sz_speciality, SPECILITY_WIDTH);
		this->speciality = sz_speciality;
		ifs >> group >> rating >> attendance;
		return ifs;
	}
};

class Teacher :public Human //добавил 3 отличия от Human, специальность, стаж работы, ставка
{
protected:
	static const int PROFFESSION_WIDTH = 22;
	static const int EXPERIANCE_WIDTH = 5;
	static const int RATE_WIDTH = 5;
private:
	std::string profession;
	int work_experience;
	double rate;
public:
	const std::string& get_profession() const
	{
		return profession;
	}
	int get_work_experence() const
	{
		return work_experience;
	}
	double get_rate() const
	{
		return rate;
	}
	void set_profession(const std::string& profession)
	{
		this->profession = profession;
	}
	void set_work_experience(int work_experience)
	{
		this->work_experience = work_experience;
	}
	void set_rate(double rate)
	{
		this->rate = rate;
	}

	//					Constructors
	Teacher(const std::string& last_name, const std::string& first_name, int age, 
		const std::string& profession, int work_experience, double rate):
		Human(last_name, first_name, age)
	{
		set_profession(profession);
		set_work_experience(work_experience);
		set_rate(rate);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	std::ostream& print(std::ostream& out) const
	{
		Human::print(out) << " ";
		return out << profession << " " << work_experience << " " << rate;
	}
	std::ofstream& print(std::ofstream& ofs)const
	{
		Human::print(ofs);
		ofs.width(PROFFESSION_WIDTH);
		ofs << profession;
		ofs.width(EXPERIANCE_WIDTH);
		ofs << work_experience;
		ofs.width(RATE_WIDTH);
		ofs << rate;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)
	{
		Human::scan(ifs);
		char sz_speciality[PROFFESSION_WIDTH + 1] = {};
		ifs.read(sz_speciality, PROFFESSION_WIDTH);
		this->profession = sz_speciality;
		ifs >> work_experience >> rate;
		return ifs;
	}
};

class Gradute :public Student
{
protected:
	static const int THESIS_WIDTH = 70;
	static const int GRADUATION_WIDTH = 6;
	static const int DIPLOMA_WIDTH = 5;
	static const int HOURS_WIDTH = 7;
	static const int GPA_WIDTH = 9;
private:
	std::string thesis;
	std::string graduation_date;
	int diploma_assessment;
	int total_hours;
	double GPA; //Grade Point Average 
public:
	const std::string& get_thesis() const
	{
		return thesis;
	}
	const std::string& get_graduation_date() const
	{
		return graduation_date;
	}
	int get_diploma_assessment() const
	{
		return diploma_assessment;
	}
	int get_total_hours() const
	{
		return total_hours;
	}
	double get_GPA() const
	{
		return GPA;
	}
	void set_thesis(const std::string& thesis)
	{
		this->thesis = thesis;
	}
	void set_graduation_date(const std::string& graduation_date)
	{
		this->graduation_date = graduation_date;
	}
	void set_diploma_assessment(int diploma_assessment)
	{
		this->diploma_assessment = diploma_assessment;
	}
	void set_total_hours(int total_hours)
	{
		this->total_hours = total_hours;
	}
	void set_GPA(double GPA)
	{
		this->GPA = GPA;
	}

	//					Constructors
	Gradute(const std::string& last_name, const std::string& first_name, int age, 
		const std::string& speciality, const std::string& group, double raiting, double attendance,
		const std::string& thesis/*, const std::string& graduation_date, int diploma_assessment, int total_hours, double GPA*/) :
		Student(last_name, first_name, age, speciality, group, raiting, attendance)
	{
		set_thesis(thesis);
		/*set_graduation_date(graduation_date);
		set_diploma_assessment(diploma_assessment);
		set_total_hours(total_hours);
		set_GPA(GPA);*/
		cout << "GConstructor:\t" << this << endl;
	}
	~Gradute()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	std::ostream& print(std::ostream& out) const
	{
		Student::print(out) << " ";
		return out << thesis /*<< " " << graduation_date << " " << diploma_assessment << " " << total_hours << " " << GPA*/;
	}
	std::ofstream& print(std::ofstream& ofs)const
	{
		Student::print(ofs);
		ofs.width(THESIS_WIDTH);
		ofs << thesis;
		//ofs.width(GRADUATION_WIDTH);
		//ofs << graduation_date;
		//ofs.width(DIPLOMA_WIDTH);
		//ofs << diploma_assessment;
		//ofs.width(HOURS_WIDTH);
		//ofs << total_hours;
		//ofs.width(GPA_WIDTH);
		//ofs << GPA;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)
	{
		Student::scan(ifs);
		std::getline(ifs, thesis);
		return ifs;
	}

};
//#define HOME_WORK
//#define STORE_TO_FILE


void main()
{
	setlocale(LC_ALL, "");
#ifdef HOME_WORK
	Human human("Montana", "Antonio", 30);
	human.print();
	cout << delimitr;

	Student stud
	(
		"Pinkman", "Jessie", 25,
		"Chemistry", "WW_220", 95, 98
	);
	stud.print();
	cout << delimitr;

	Teacher teach
	(
		"Poliancsky", "Dmitrii", 52,
		"mathematician", 20, 1
	);
	teach.print();
	cout << delimitr;

	Gradute grad1
	(
		"Pinkman", "Jessie", 25,
		"Programmer", "WW_220", 95, 98,
		"Monitoring algorithm of the state of the data transmission network", "27.05.2023", 5, 8160, 4.73
	);
	grad1.print();
#endif // HOME_WORK


#ifdef STORE_TO_FILE
	Human* group[] =
	{
		// UPCAST
		new Human
		(
			"Proba", "Probovich", 40
		),
		new Student
		(
			"Pinkman", "Jessie", 25,
			"Chemistry", "WW_220", 95, 98
		),
		new Teacher
		(
			"Poliancsky", "Dmitrii", 52,
			"mathematician", 20, 1
		),
		new Gradute
		(
			"Pinkman", "Jessie", 25,
			"Programmer", "WW_220", 95, 98,
			"Monitoring algorithm of the state of the data transmission network"/*, "27.05.2023", 5, 8160, 4.73*/
		)

	};
	print(group, sizeof(group) / sizeof(group[0]));
	save(group, sizeof(group) / sizeof(group[0]), "group.txt");
#endif // STORE_TO_FILE

	int n;
	Human** group = load("group.txt", n);
	print(group, n);
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
}
std::ostream& operator<<(std::ostream& out, const Human& obj)
{
	return obj.print(out);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	obj.print(ofs);
	return ofs;
}

void print(Human** group, const int n)
{
	cout << delimitr;
	for (int i = 0; i < n; i++)
	{
		cout << typeid(*group[i]).name() << ": \t";
		/*group[i]->print();*/
		//cout << *group[i] << endl;
		//if(typeid(*group[i]) == typeid(Student)) //dynamic
		//cout << *dynamic_cast<Student*>(group[i]) << endl;
		cout << *group[i] << endl;
		cout << delimitr;

	}
}
void save(Human** group, const int n, const string filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
	std::string command = "start notepad ";
	command += filename;
	system(command.c_str());
}
Human* HumanFactory(const std::string& type)
{
	if (type.find("Teacher") != std::string::npos) return new Teacher("", "", 0, "", 0, 0);
	if (type.find("Student") != std::string::npos) return new Student("", "", 0, "", "", 0, 0);
	if (type.find("Gradute") != std::string::npos) return new Gradute("", "", 0, "", "", 0, 0, "");
}
Human** load(const std::string& filename, int& n)
{
	n = 0;
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		for(n = 0;!fin.eof(); n++)
		{
			std::string buffer;
			std::getline(fin, buffer);
		}
		//2) Выделяем память под массив
		group = new Human * [--n] {};
		string line;
		string word[10];
		int count = 0;
		fin.clear(); // - code of OA
		fin.seekg(0); // - code of OA
		//Создаем и читаем объекты
		for (int i = 0; i < n; i++)
		{
			std::string type;
			std::getline(fin, type, ':');
			fin.ignore();
			group[i] = HumanFactory(type);
			fin >> *group[i];
		}
		//while (getline(fin, line))
		//{
		//	string temp_line = line;

		//	int position = 0;
		//	position = temp_line.find(" ", 0);
		//	temp_line = temp_line.substr(position + 1);
		//	position = temp_line.find(" ", 0);
		//	word[0] = temp_line.substr(0, position - 1);
		//	temp_line = temp_line.substr(position + 2);
		//	int size;
		//	if (word[0] == "Human")size = 4;
		//	if (word[0] == "Student")size = 9;
		//	if (word[0] == "Teacher")size = 7;
		//	if (word[0] == "Gradute")size = 10;
		//	for (int i = 1; i < size; i++)
		//	{
		//		if (temp_line == "") break;
		//		if (i == 8 && size == 10 )
		//		{
		//			word[8] = temp_line;
		//			for (int k = 0; k < word[8].size(); k++) if (word[8][k] == ' ' && word[8][k + 1] != ' ')
		//			{
		//				word[8] = word[8].substr(k + 1);
		//				break;
		//			}
		//			break;
		//		}
		//		position = temp_line.find(" ", 0);
		//		word[i] = temp_line.substr(0, position);
		//		temp_line = temp_line.substr(position + 1);
		//		if (word[i] == " " or word[i] == "") i--;
		//	}
		//	if (word[0] == "Human")group[count] = new Human(word[1], word[2], stoi(word[3]));
		//	if (word[0] == "Student")group[count] = new Student(word[1], word[2], stoi(word[3]), word[4], word[5], stoi(word[6]), stoi(word[7]));
		//	if (word[0] == "Teacher")group[count] = new Teacher(word[1], word[2], stoi(word[3]), word[4], stoi(word[5]), stof(word[6]));
		//	if (word[0] == "Gradute")group[count] = new Gradute(word[1], word[2], stoi(word[3]), word[4], word[5], stoi(word[6]), stoi(word[7]), word[8]);
		//	count++;
		//	//for (int i = 0; i < 10;i++)word[i].clear();
		//}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	return group;
}
Human** loadmy(const std::string& filename)
{
	int n = 0;
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		for (n = 0; !fin.eof(); n++)
		{
			std::string buffer;
			std::getline(fin, buffer);
		}
		//2) Выделяем память под массив
		group = new Human * [--n] {};
		string line;
		string word[10];
		int count = 0;
		fin.close();
		std::ifstream fin(filename);
		while (getline(fin, line))
		{
			string temp_line = line;

			int position = 0;
			position = temp_line.find(" ", 0);
			temp_line = temp_line.substr(position + 1);
			position = temp_line.find(" ", 0);
			word[0] = temp_line.substr(0, position - 1);
			temp_line = temp_line.substr(position + 2);
			int size;
			if (word[0] == "Human")size = 4;
			if (word[0] == "Student")size = 9;
			if (word[0] == "Teacher")size = 7;
			if (word[0] == "Gradute")size = 10;
			for (int i = 1; i < size; i++)
			{
				if (temp_line == "") break;
				if (i == 8 && size == 10)
				{
					word[8] = temp_line;
					for (int k = 0; k < word[8].size(); k++) if (word[8][k] == ' ' && word[8][k + 1] != ' ')
					{
						word[8] = word[8].substr(k + 1);
						break;
					}
					break;
				}
				position = temp_line.find(" ", 0);
				word[i] = temp_line.substr(0, position);
				temp_line = temp_line.substr(position + 1);
				if (word[i] == " " or word[i] == "") i--;
			}
			if (word[0] == "Human")group[count] = new Human(word[1], word[2], stoi(word[3]));
			if (word[0] == "Student")group[count] = new Student(word[1], word[2], stoi(word[3]), word[4], word[5], stoi(word[6]), stoi(word[7]));
			if (word[0] == "Teacher")group[count] = new Teacher(word[1], word[2], stoi(word[3]), word[4], stoi(word[5]), stof(word[6]));
			if (word[0] == "Gradute")group[count] = new Gradute(word[1], word[2], stoi(word[3]), word[4], word[5], stoi(word[6]), stoi(word[7]), word[8]);
			count++;
			//for (int i = 0; i < 10;i++)word[i].clear();
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	return group;
}

std::ifstream& operator>>(std::ifstream& ifs, Human& obj)
{
	obj.scan(ifs);
	return ifs;
}