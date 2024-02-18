#ifdef _WIN32
    #include <windows.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

// ----------------------------------------------------//
#define ROWS 4 // ���������� ����� ������ ����
// ----------------------------------------------------//
#define A cout << 'A'
#define O cout << '*'
#define H cout << 'H'
#define _ cout << " "
#define N cout << endl

int _size, step, _count, _end, stepDec, width, height;

int randomInt(int min_value, int max_value) {
    return rand() % (max_value - min_value + 1) + min_value;
}

void setColor(int backCol, int textCol) {
    //cout << "\[s"; // ��������� ������� �������
    char com[] = "[37m [40m";
    com[3] = textCol+'0';
    com[9] = backCol+'0';
    cout << com << "\b";
    //cout << "\[u"; // ������������ ������� �������
}

void printTree() {
    cout << "[1;1H"; // ����������� ������ � ������ ������ ������
    step = 1;
    _count = 6;
    _end = _size / 2 - step;
    stepDec = 4;
    // �����
    for (int i = 0; i <= _end; i++) {
        _; // ������
        if (i == _end && step <= _size) {
            for (int j = 0; j < step; j++) {
                // �������
                if (j & 1) { // ���� ����� ��������
                    int rndCol = randomInt(0, 4);
                    rndCol = (rndCol == 0) ? 1 : (rndCol == 1) ? 4 : (rndCol == 2) ? 5 : (rndCol == 3) ? 6 : 7;
                    setColor(0, rndCol);
                    O; // ����� O - �������
                }
                // �������
                else {
                    setColor(0, 2);
                    A; // ����� � - �������
                }
            }
            N; // ����� �����
            i = 0;
            step += 2;
            if (step > _count) {
                step -= stepDec;
                stepDec += 2;
                _count += step;
            }
            if (_end == 1) break;
            _end = _size / 2 - step / 2;
        }
    }

    // �����
    setColor(0, 3); // ������ ���, ���� �����
    cout << "\[G"; // ������ � ������ ������
    for (int j = 0; j < height; j++) { // ������
        for (int i = 0; i <= (_size/2-(width/2)); i++) { // ������
            if (i == _size/2-(width/2)) {
                for (int w = 0; w < width; w++) H; // ������ ������
            }
            _; // ������
        }
        cout << endl;
    }
    setColor(0, 7); // ������ ���, ����� �����
}

int main() {
    #ifdef _WIN32
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
        #define DISABLE_NEWLINE_AUTO_RETURN  0x0008
        HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD consoleMode;
        GetConsoleMode( handleOut , &consoleMode);
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
        SetConsoleMode( handleOut , consoleMode );
    #endif

    srand(time(0)); // �������������� ������������
    cout << "[?25l"; // ��������� ����������� �������
    _size = ROWS == 1 ? 5 : 3; // 5
    for (int i = 1; i <= ROWS; i++) {
        _size += i * 2;
    }
    // ������ ������
    width = (_size * 0.15 > 0) ? _size * 0.15 : 1;
    height = width * 2;
    if (!(width & 1)) width++; // ������������� ������ ������
    while (1) printTree();
    return 0;
}


