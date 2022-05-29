
#include "Console.h"

void Console::handlerText(string str) {
    string command = str.substr(0, str.find(' '));

    //cout << command << endl;

    if (command == "Identification")
    {
        //emitSignal((TYPE_SIGNAL)(&Console::signalIdentifyCard));
        currentCard = str.substr(str.find(' ') + 1);
        emitSignal((TYPE_SIGNAL)(&Console::signalPrintMsg), "Enter the PIN code");
    }

    else if (command == "PIN-code")
    {
        // дописать проверку верности пин кода
        isAuth = true;
        emitSignal((TYPE_SIGNAL)(&Console::signalPrintMsg), "Select the command");
    } else
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
                int intSum = stoi( str.substr(16));
                string strSum =  str.substr(16);

                if (intSum % 100 != 0) emitSignal((TYPE_SIGNAL)(&Console::signalPrintMsg), "The amount is not a multiple of 100");

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




