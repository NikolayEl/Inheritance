#include<iostream>
#include<Windows.h>
#include"math.h"
//#include<cmath>
using namespace std;

#define delimitr "\n----------------------------------------------------------\n"

enum Color
{
	console_red = 0xCC, //0x - Hexadecimal 
	console_green = 0xAA,
	console_blue = 0x1,
	console_defuult = 0x07
};

class Shape
{
protected:
	Color color;
public:
	Shape(Color color):color(color){}
	virtual ~Shape() {}
	virtual double get_area()const = 0;
	virtual double get_perimeter() const = 0;
	virtual void draw()const = 0;
};

class Rectangles :public Shape
{
	static const int MIN_SIDE = 2;
	static const int MAX_SIDE = 50;
	double long_side;
	double width_side;
public:
	Rectangles(double long_side, double width_side, Color color) :Shape(color)
	{
		set_long_side(long_side);
		set_width_side(width_side);
		cout << "RectangleConstructor:\t" << this << endl;
	}
	Rectangles(double side, Color color) :Shape(color)
	{
		set_long_side(side);
		set_width_side(side);
		cout << "SquareConstructor:\t" << this << endl;
	}
	double get_long_side() const
	{
		return long_side;
	}
	double get_width_side() const
	{
		return width_side;
	}
	void set_long_side(double long_side)
	{
		if (long_side < MIN_SIDE) long_side = MIN_SIDE;
		if (long_side > MAX_SIDE) long_side = MAX_SIDE;
		this->long_side = long_side;
	}
	void set_width_side(double width_side)
	{
		if (width_side < MIN_SIDE) width_side = MIN_SIDE;
		if (width_side > MAX_SIDE) width_side = MAX_SIDE;
		this->width_side = width_side;
	}
	double get_area() const override
	{
		return long_side * width_side;
	}
	double get_perimeter() const override
	{
		return (long_side + width_side) * 2;
	}
	void draw() const override
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		for (int i = 0; i < width_side; i++)
		{
			for (int j = 0; j < long_side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
		SetConsoleTextAttribute(hConsole, Color::console_defuult);
	}
	~Rectangles()
	{
		cout << "RDestructor:\t" << this << endl;
	}

};

class Triangle :public Shape
{
	static const int MIN_SIDE = 2;
	static const int MAX_SIDE = 50;
	double side_one;
	double side_two;
	double side_three;
	double height;
public:
	double get_side_one() const
	{
		return side_one;
	}
	double get_side_two() const
	{
		return side_two;
	}
	double get_side_three() const
	{
		return side_three;
	}
	double get_height() const
	{
		return (2 * this->get_area()) / max((side_one, side_two), side_three);
	}
	void set_side_one(double side_one)
	{
		this->side_one = side_one;
	}
	void set_side_two(double side_two)
	{
		this->side_two = side_two;
	}
	void set_side_three(double side_three)
	{
		this->side_three = side_three;
	}
	Triangle(double side_one, double side_two, double side_three, Color color) :Shape(color)
	{
		set_side_one(side_one);
		set_side_two(side_two);
		set_side_three(side_three);
		cout << "TConstructor:\t" << this << endl;
	}
	Triangle(double side, Color color) :Shape(color)
	{
		set_side_one(side);
		set_side_two(side);
		set_side_three(side);
		cout << "IsoscelesTConstructor:\t" << this << endl;
	}
	~Triangle()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	double get_area() const override
	{
		double pperimetr = this->get_perimeter() / 2;
		return round(sqrt(pperimetr * (pperimetr - side_one) * (pperimetr - side_two) * (pperimetr - side_three))*10)/10;
	}
	double get_perimeter() const override
	{
		return side_one + side_two + side_three;
	}
	void draw() const override
	{
		double base_side = max((side_one, side_two), side_three);
		double one_side = min((side_one, side_two), side_three);
		double two_side = this->get_perimeter() - base_side - one_side;
		double a_cattle = round(sqrt((one_side * one_side) - (this->get_height() * this->get_height()))*10)/10;
		double b_cattle = base_side - a_cattle;
		//cout << base_side << " " << one_side << " " << two_side << " " << a_cattle << " " << b_cattle << " " << this->get_height() << endl;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		for (int i = 0; i < a_cattle - 1; i++)
		{
			for (int j = 0; j < i + 1; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
		for (int i = 0; i < a_cattle; i++) cout << "* ";
		cout << endl;
		for (int i = b_cattle - 1; i > -1; i--)
		{
			for (int j = i + 1; j > 0; j--)
			{
				cout << "* ";
			}
			cout << endl;
		}
		SetConsoleTextAttribute(hConsole, Color::console_defuult);
		system("PAUSE");
	}
};

class Circle :public Shape
{
	static const int MIN_SIZE = 5;
	static const int MAX_SIZE = 50;
	const double pi = 3.1415926;
	double radius;
public:
	double get_radius() const
	{
		return radius;
	}
	void set_radius(double radius)
	{
		this->radius = radius;
	}
	Circle(double radius, Color color) :Shape(color)
	{
		if (radius < MIN_SIZE) radius = MIN_SIZE;
		if (radius > MAX_SIZE) radius = MAX_SIZE;
		set_radius(radius);
		cout << "CConstructor:\t" << this << endl;
	}
	~Circle()
	{
		cout << "CDestructor:\t" << this << endl;
	}
	double get_area() const override
	{
		return round(pi * radius * radius *10)/10;
	}
	double get_perimeter() const override
	{
		return round(2 * pi * radius *10)/10;
	}
	void draw() const override
	{
		for (int i = 0; i < radius * 2; i++) cout << "\n";
		cout << "Рисуем круг, нажмите на любую клавишу" << endl;
		system("PAUSE");
		HWND handle = FindWindowA("ConsoleWindowClass", NULL);
		HDC hdc = GetDC(handle);

		//создаём перо (контур)
		HPEN hPen = CreatePen(PS_SOLID, 10, color); //сплошная линия, толщиной 10 пикселей, цвет - зеленый
		//создаём кисть (заливка)
		HBRUSH hBrush = CreateSolidBrush(0x0);//сплошной черный
		SelectObject(hdc, hPen);// указываем перо 
		SelectObject(hdc, hBrush);//указываем кисть
		//рисуем эллипс
		Ellipse(hdc, 500, 20, radius * 10 * 2 + 500, radius * 10 * 2 + 20); //100,100 -верхний левый 200,300 - нижний правый углы описывающего прямоугольника
	}
		
};

void main()
{
	setlocale(LC_ALL, "");
	//					ПРЯМОУГОЛЬНИК
	Rectangles rect(10, 5, Color::console_red);
	cout << delimitr << endl;
	cout << "Длинна прямоугольника: " << rect.get_long_side() << endl;
	cout << "Ширина прямоугольника: " << rect.get_width_side() << endl;
	cout << "Площадь прямоугольника: " << rect.get_area() << endl;
	cout << "Периметр прямоугольника: " << rect.get_perimeter() << endl;
	rect.draw();
	cout << delimitr << endl;

	//					Квадрат
	Rectangles square(5, Color::console_red);
	cout << delimitr << endl;
	cout << "Длинна стороны квадрата: " << square.get_long_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();
	cout << delimitr << endl;

	//					Треугольник
	Triangle triangle(11, Color::console_blue);
	cout << delimitr << endl;
	cout << "Длинна равностороннего треугольника: " << triangle.get_side_one() << endl;
	cout << "Площадь равностороннего треугольника: " << triangle.get_area() << endl;
	cout << "Периметр равностороннего треугольника: " << triangle.get_perimeter() << endl;
	cout << "Высота равностороннего треугольника: " << triangle.get_height() << endl;
	triangle.draw();
	cout << delimitr << endl;

	//					Круг
	Circle circle(15, Color::console_green);
	cout << delimitr << endl;
	cout << "Длинна окружности круга: " << circle.get_perimeter() << endl;
	cout << "радиус: " << circle.get_radius() << endl;
	cout << "Площадь круга: " << circle.get_area() << endl;
	circle.draw();
	cout << delimitr << endl;
}