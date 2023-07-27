#include <windows.h>
#include <iostream>

int InputInteger(const char* str, int min, int max) {
    int x;
    std::cout << str;
    bool ErrorFlag;
    do {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin >> x;
        ErrorFlag = !std::cin.good() || x< min || x>max;
        if (ErrorFlag) {
            std::cout << "Error. " << str;
        }
    } while (ErrorFlag);
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return x;
}

int main() {
    HWND hWnd = GetConsoleWindow();
    HDC hDC = GetDC(hWnd);
    RECT temp;
    GetClientRect(hWnd, &temp);
    HDC hBufferDC = CreateCompatibleDC(hDC);
    HBITMAP hBufferBmp = CreateBitmap(temp.right, temp.bottom, 1, 32, NULL);
    HBITMAP hBufferBmpOld = (HBITMAP)SelectObject(hBufferDC, hBufferBmp);
    FillRect(hBufferDC, &temp, (HBRUSH)GetStockObject(WHITE_BRUSH));
    std::cout << "Enter color:\n";
    int r, g, b;
    r = InputInteger("Enter R value[0,255]:", 0, 255);
    g = InputInteger("Enter G value[0,255]:", 0, 255);
    b = InputInteger("Enter B value[0,255]:", 0, 255);
    system("cls");
    HBRUSH hBrush = CreateSolidBrush(RGB(r, g, b));
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(r, g, b));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hBufferDC, hBrush);
    HPEN hOldPen = (HPEN)SelectObject(hBufferDC, hPen);
    RECT circle = { 0,0,110,110 };
    size_t step_h = 3, step_v = 3;
    while (!GetAsyncKeyState(VK_ESCAPE)) {
        FillRect(hBufferDC, &circle, (HBRUSH)GetStockObject(WHITE_BRUSH));
        if (GetAsyncKeyState(VK_LEFT)) {
            circle.left -= step_h;
            circle.right -= step_h;
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            circle.left += step_h;
            circle.right += step_h;
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            circle.top += step_v;
            circle.bottom += step_v;
        }
        if (GetAsyncKeyState(VK_UP)) {
            circle.top -= step_v;
            circle.bottom -= step_v;
        }
        Ellipse(hBufferDC, circle.left, circle.top, circle.right, circle.bottom);
        BitBlt(hDC, 0, 0, temp.right, temp.bottom, hBufferDC, 0, 0, SRCCOPY);
        Sleep(10);
    }
    SelectObject(hBufferDC, hOldBrush);
    SelectObject(hBufferDC, hOldPen);
    SelectObject(hBufferDC, hBufferBmpOld);
    DeleteObject(hBrush);
    DeleteObject(hPen);
    DeleteObject(hBufferBmp);
    DeleteDC(hBufferDC);
    ReleaseDC(hWnd, hDC);
    return 0;
}