
#include "Console.h"

void Console::handlerText(string str) {
    cout << "came to controller" << endl;
    string command = str.substr(0, str.find(' '));
    cout << command << endl;

    if (command == "Turn")
    {
        emitSignal((TYPE_SIGNAL)(&Console::signalPrintTurnOff));
        return;
    }

    emitSignal((TYPE_SIGNAL)(&Console::signalReadNewCommand));
}

