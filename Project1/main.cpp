#include <windows.h>
int main()
{
    HWND handle = FindWindowA("ConsoleWindowClass", NULL);
    HDC hdc = GetDC(handle);

    //������ ���� (������)
    HPEN hPen = CreatePen(PS_SOLID, 10, 0xCC); //�������� �����, �������� 10 ��������, ���� - �����
    //������ ����� (�������)
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));//�������� ������
    SelectObject(hdc, hPen);// ��������� ���� 
    SelectObject(hdc, hBrush);//��������� �����
    //������ ������
    Ellipse(hdc, 100, 100, 300, 300); //100,100 -������� ����� 200,300 - ������ ������ ���� ������������ ��������������

    return 0;
}