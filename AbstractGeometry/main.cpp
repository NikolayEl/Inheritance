#include<iostream>
#include<Windows.h>
#include"math.h"
//#include<cmath>
using namespace std;

#define delimitr "\n----------------------------------------------------------\n"

namespace Geometry
{
	enum Color
	{
		red = 0x000000FF, 
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
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
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual double get_area()const = 0;
		virtual double get_perimeter() const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Rectangle :public Shape
	{
		static const int MIN_SIDE = 2;
		static const int MAX_SIDE = 50;
		double long_side;
		double width_side;
	public:
		Rectangle(double long_side, double width_side, Color color) :Shape(color)
		{
			set_long_side(long_side);
			set_width_side(width_side);
			//cout << "RectangleConstructor:\t" << this << endl;
		}
		Rectangle(double side, Color color) :Shape(color)
		{
			set_long_side(side);
			set_width_side(side);
			//cout << "SquareConstructor:\t" << this << endl;
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
			//1) Получаем окно консоли
			HWND hwnd = GetConsoleWindow(); //Получаем окно консоли
			//2) СОздаем контекст устройства
			HDC hdc = GetDC(hwnd); // СОздаем контекст устройства
			//3) Создаем кисть и карандаш
			HPEN hPen = CreatePen(PS_SOLID, 5, color); //карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color); //Кисть заливает цыетом фигуру

			//4) Выбираем чем и на чем будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) Рисуем фигуру
			::Rectangle(hdc, 100, 200, 100 + (long_side * 50), 200 + (width_side * 50));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			DeleteObject(hdc);
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < width_side; i++)
			{
				for (int j = 0; j < long_side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_defuult);*/
		}
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длинна стороны a: " << get_long_side() << endl;
			cout << "Длинна стороны b: " << get_width_side() << endl;
			Shape::info();
		}
		~Rectangle() {}

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
			//cout << "TConstructor:\t" << this << endl;
		}
		Triangle(double side, Color color) :Shape(color)
		{
			set_side_one(side);
			set_side_two(side);
			set_side_three(side);
			//cout << "IsoscelesTConstructor:\t" << this << endl;
		}
		~Triangle()
		{
			//cout << "TDestructor:\t" << this << endl;
		}
		double get_area() const override
		{
			double pperimetr = this->get_perimeter() / 2;
			return round(sqrt(pperimetr * (pperimetr - side_one) * (pperimetr - side_two) * (pperimetr - side_three)) * 10) / 10;
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
			double a_cattle = round(sqrt((one_side * one_side) - (this->get_height() * this->get_height())) * 10) / 10;
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
			//system("PAUSE");
		}
	};

	class Ellipses :public Shape
	{
		static const int MIN_SIZE = 5;
		static const int MAX_SIZE = 50;
		const double pi = 3.1415926;
		double semiaxis_a;
		double semiaxis_b;
	public:
		double get_semiaxis_a() const
		{
			return semiaxis_a;
		}
		double get_semiaxis_b() const
		{
			return semiaxis_b;
		}
		void set_semiaxis_a(double semiaxis_a)
		{
			this->semiaxis_a = semiaxis_a;
		}
		void set_semiaxis_b(double semiaxis_b)
		{
			this->semiaxis_b = semiaxis_b;
		}
		Ellipses(double semiaxis_a, double semiaxis_b, Color color) :Shape(color)
		{
			if (semiaxis_a < MIN_SIZE) semiaxis_a = MIN_SIZE;
			if (semiaxis_a > MAX_SIZE) semiaxis_a = MAX_SIZE;
			if (semiaxis_b < MIN_SIZE) semiaxis_b = MIN_SIZE;
			if (semiaxis_b > MAX_SIZE) semiaxis_b = MAX_SIZE;
			set_semiaxis_a(semiaxis_a);
			set_semiaxis_b(semiaxis_b);
			//cout << "EConstructor:\t" << this << endl;
		}
		Ellipses(double radius, Color color) :Shape(color)
		{
			if (radius < MIN_SIZE) radius = MIN_SIZE;
			if (radius > MAX_SIZE) radius = MAX_SIZE;
			set_semiaxis_a(radius);
			set_semiaxis_b(radius);
			//cout << "CircleConstructor:\t" << this << endl;
		}
		~Ellipses()
		{
			//cout << "EDestructor:\t" << this << endl;
		}
		double get_area() const override
		{
			return round(pi * semiaxis_a * semiaxis_b * 10) / 10;
		}
		double get_perimeter() const override
		{
			return round(2 * pi * sqrt((semiaxis_a * semiaxis_a + semiaxis_b * semiaxis_b) / 2) * 10) / 10;
		}
		void draw() const override
		{
			for (int i = 0; i < semiaxis_a * 2; i++) cout << "\n";
			//cout << "Рисуем круг, нажмите на любую клавишу" << endl;
			HWND handle = FindWindowA("ConsoleWindowClass", NULL);
			HDC hdc = GetDC(handle);

			//создаём перо (контур)
			HPEN hPen = CreatePen(PS_SOLID, 10, color); //сплошная линия, толщиной 10 пикселей, цвет - зеленый
			//создаём кисть (заливка)
			HBRUSH hBrush = CreateSolidBrush(0x0);//сплошной черный
			SelectObject(hdc, hPen);// указываем перо 
			SelectObject(hdc, hBrush);//указываем кисть
			//рисуем эллипс
			Ellipse(hdc, 500, 20, semiaxis_a * 10 * 2 + 500, semiaxis_b * 10 * 2 + 20);
			//500,20 -верхний левый semiaxis_a * 10 * 2 + 500, semiaxis_b * 10 * 2 + 20 - нижний правый углы описывающего прямоугольника
		}

	};
}
#define RECTANGLE_MAIN
//#define SQUARE_MAIN
//#define TRIANGLE_MAIN
//#define ELLIPS_MAIN
//#define CIRCLE_MAIN
void main()
{
	setlocale(LC_ALL, "");
#ifdef RECTANGLE_MAIN
	//					ПРЯМОУГОЛЬНИК
	Geometry::Rectangle rect(10, 5, Geometry::Color::blue);
	cout << delimitr << endl;
	system("PAUSE");
	rect.info();
#endif // RECTANGLE_MAIN


#ifdef SQUARE_MAIN
	//					Квадрат
	cout << delimitr << endl;
	Geometry::Rectangle square(5, Geometry::Color::red);
	cout << delimitr << endl;
	system("PAUSE");
	square.info();
#endif // SQUARE_MAIN


#ifdef TRIANGLE_MAIN
	//					Треугольник
	Geometry::Triangle triangle(11, Geometry::Color::console_blue);
	cout << delimitr << endl;
	system("PAUSE");
	triangle.info();
#endif // TRIANGLE_MAIN


#ifdef ELLIPS_MAIN
	//					Элипс
	Geometry::Ellipses ellipse(10, 5, Geometry::Color::green);
	cout << delimitr << endl;
	system("PAUSE");
	ellipse.info();
#endif // ELLIPS_MAIN
	
#ifdef CIRCLE_MAIN
	//					Круг
	Geometry::Ellipses circle(10, Geometry::Color::green);
	cout << delimitr << endl;
	system("PAUSE");
	circle.info();

#endif // CIRCLE_MAIN

}