#include "Printer.h"

void Printer::handlerTurnOff(string str) {
    cout << "Turn off the ATM";
}

void Printer::handlerPrintReadyToWork(string str) {
    cout << "Ready to work" << endl;
}

void Printer::handlerPrintEnterPin(string str) {
    cout << "Enter the PIN code" << endl;
}

void Printer::handlerPrintSelectTheCommand(string str) {
    cout << "Select the command" << endl;
}

void Printer::handlerPrintCardBalance(string str) {
    cout << "Card balance " << str << endl;
}

