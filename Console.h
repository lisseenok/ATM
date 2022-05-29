#ifndef __CONSOLE__
#define __CONSOLE__
#include "Base.h"

/** Объект пульта управления, для отработки нажатия кнопок (команд). 
Объект после нажатия кнопки анализирует возможность его выполнения и выдает соответствующий сигнал. 
Выдает сигнал если запрошенная для снятия сумма не кратна 100 или на карте нет достаточных средств
*/
class Console:public Base
{
    bool isAuth = false; // обработать при правильном пин коде (сигнал от идентификатора)
    string currentCard;
    bool depositMode = false;
    int sumOfDeposits = 0;


public:
    Console(Base* parent, string name):Base(parent, name, 3){}
    void signalReadNewCommand(string &str){} // сигнал чтобы ридер считал новую строчку
    void signalPrintTurnOff(string &str){} // сигнал вывода выключения
    void signalPrintReadyToWork(string &srt){} // сигнал для вывода "Ready to work"
    void signalPrintEnterPin(string &srt){} // сигнал для вывода "Enter the PIN code"
    void signalPrintSelectTheCommand(string &srt){} // сигнал для вывода "Select the command"
    void signalDepositToCard(string &srt){} // сигнал для добавления суммы на баланс карты
    void signalReturnCardBalance(string &srt){} // сигнал системе чтобы отправила баланс принтеру

    void handlerText(string str);
};
#endif