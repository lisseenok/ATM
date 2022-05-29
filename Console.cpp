
#include "Console.h"

void Console::handlerText(string str) {
    string command = str.substr(0, str.find(' '));

    //cout << command << endl;

    if (command == "Identification")
    {
        currentCard = str.substr(str.find(' ') + 1);
        emitSignal((TYPE_SIGNAL)(&Console::signalPrintEnterPin));
    }

    else if (command == "PIN-code")
    {
        // дописать проверку верности пин кода
        isAuth = true;
        emitSignal((TYPE_SIGNAL)(&Console::signalPrintSelectTheCommand));
    } else
    {
        if (!isAuth)
        {
            emitSignal((TYPE_SIGNAL)(&Console::signalPrintReadyToWork));
        } else{
            if (command == "Deposit")
            {
                if (str.substr(14, 2) == "to")
                {
                    emitSignal((TYPE_SIGNAL)(&Console::signalDepositToCard), currentCard + to_string(sumOfDeposits));
                    emitSignal((TYPE_SIGNAL)(&Console::signalReturnCardBalance), currentCard); // отправляем сигнал системе, чтобы та отправила принтеру баланс
                    sumOfDeposits = 0;
                } else {
                    sumOfDeposits += stoi(str.substr(14));
                }
            }
        }

    }



    // обработка завершения работы банкомата
    if (command == "Turn")
    {
        emitSignal((TYPE_SIGNAL)(&Console::signalPrintTurnOff));
        return;
    }

    emitSignal((TYPE_SIGNAL)(&Console::signalReadNewCommand));
}

