
#include "Console.h"

void Console::handlerText(string str) {
    string command = str.substr(0, str.find(' '));


    if (command == "Identification")
    {
        currentCard = str.substr(str.find(' ') + 1);
        emitSignal((TYPE_SIGNAL)(&Console::signalIdentificate), currentCard);
    }
    else if (command == "End")
    {
        emitSignal((TYPE_SIGNAL)(&Console::signalPrintMsg), "Ready to work");
        isAuth = false;
        // прекратить команду
    }

    // обработка завершения работы банкомата
    else if (command == "Turn")
    {
        emitSignal((TYPE_SIGNAL)(&Console::signalPrintTurnOff));
        return;
    }

    else
    {
        if (!isAuth)
        {
            emitSignal((TYPE_SIGNAL)(&Console::signalPrintMsg), "Ready to work");
        } else{
            if (command == "Deposit")
            {
                if (str.substr(14, 2) == "to")
                {
                    emitSignal((TYPE_SIGNAL)(&Console::signalEndDeposit), currentCard);
                } else {
                    emitSignal((TYPE_SIGNAL)(&Console::signalAddMoneyToDeposit), str.substr(14));
                }
            }
            else if (command == "Withdraw")
            {
                emitSignal((TYPE_SIGNAL)(&Console::signalWithdrawMoney), currentCard + str.substr(15));
            }
        }

    }

    emitSignal((TYPE_SIGNAL)(&Console::signalReadNewCommand));
}

void Console::handlerSuccessfulAuth(string str) {
    isAuth = true;
}

void Console::handlerNotIsAuth(string str) {
    isAuth = false;
}




