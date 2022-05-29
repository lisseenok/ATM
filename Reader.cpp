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
