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


public:
    Console(Base* parent, string name):Base(parent, name, 3){}
    void signalReadNewCommand(string &str){} // сигнал чтобы ридер считал новую строчку
    void signalPrintTurnOff(string &str){} // сигнал вывода выключения
    void signalPrintReadyToWork(string &srt){} // сигнал для вывода "Ready to work"
    void signalPrintEnterPin(string &srt){} // сигнал для вывода "Enter the PIN code"
    void signalPrintSelectTheCommand(string &srt){} // сигнал для вывода "Select the command"

    void signalAddMoneyToDeposit(string &srt){} // сигнал ресиверу о внесении новой суммы
    void signalEndDeposit(string &srt){} // сигнал ресиверу, о том, что внесение денег окончено
    void signalWithdrawMoney(string &srt){} // сигнал для выдавателя денег
    //void signalIdentifyCard(string &srt){}

    void handlerText(string str); // обработчик команды
};
#endif