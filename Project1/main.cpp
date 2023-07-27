#include <windows.h>
int main()
{
    HWND handle = FindWindowA("ConsoleWindowClass", NULL);
    HDC hdc = GetDC(handle);

    //создаём перо (контур)
    HPEN hPen = CreatePen(PS_SOLID, 10, 0xCC); //сплошная линия, толщиной 10 пикселей, цвет - синий
    //создаём кисть (заливка)
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));//сплошной черный
    SelectObject(hdc, hPen);// указываем перо 
    SelectObject(hdc, hBrush);//указываем кисть
    //рисуем эллипс
    Ellipse(hdc, 100, 100, 300, 300); //100,100 -верхний левый 200,300 - нижний правый углы описывающего прямоугольника

    return 0;
}