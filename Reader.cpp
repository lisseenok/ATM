#include "Reader.h"

void Reader::handlerReadNewCommand(string str) {
    string text;
    getline(cin, text);
    // передаем сигнал пульту управления
    emitSignal((TYPE_SIGNAL)(&Reader::signalConsole), text);
}

void Reader::handlerSetUp(string str) {
    string text;
    while (true)
    {
        getline(cin, text);
        if (text == "End card loading") break;
        emitSignal((TYPE_SIGNAL)(&Reader::signalAddUser), text);
    }

    getline(cin, text);
    emitSignal((TYPE_SIGNAL)(&Reader::signalAddMoney), text);

    getline(cin, text);

    emitSignal((TYPE_SIGNAL)(&Reader::signalPrintMsg), "Ready to work");
}

void Reader::handlerReadPin(string str) {
    string text;
    getline(cin, text);
    string pin = text.substr(9);
    emitSignal((TYPE_SIGNAL)(&Reader::signalWithEnteredPin), pin + str);

}
