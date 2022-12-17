#include <windows.h>
#include <iostream>
using namespace std;

HANDLE hSerial;

void ReadCOM() {
    bool flag = false;
    bool flag2 = true;
    DWORD iSize;
    unsigned char sReceived = 0b00000000;
    while (true) {
        ReadFile(hSerial, &sReceived, 1, &iSize, 0); 
        if (iSize > 0) {
            if (flag == true) {
                if (flag2 == true) {
                    cout << "Temperature: " << (float)sReceived * 1, 96 - 273;
                    flag = false;
                }
                else {
                    cout << "Luminosity: " << (float)sReceived * 3, 2745;
                    flag = true;
                }
                flag = false;
            }
            else {
                flag = true;
            }
        }
        if (flag == true) system("cls");
    }
}

int main() {
    LPCTSTR sPortName = L"COM1";
    hSerial = CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cout << "getting state error\n";
    }
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cout << "error setting serial port state\n";
    }
    while (true) {
        ReadCOM();
    }
}