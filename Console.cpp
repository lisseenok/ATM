
#include "Console.h"

void Console::handlerText(string str) {
    string command = str.substr(0, str.find(' '));


    if (command == "Identification")
    {
        currentCard = str.substr(str.find(' ') + 1);
        emitSignal((TYPE_SIGNAL)(&Console::signalIdentificate), currentCard);
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



    // обработка завершения работы банкомата
    if (command == "Turn")
    {
        emitSignal((TYPE_SIGNAL)(&Console::signalPrintTurnOff));
        return;
    }

    emitSignal((TYPE_SIGNAL)(&Console::signalReadNewCommand));
}

void Console::handlerSuccessfulAuth(string str) {
    isAuth = true;
}




