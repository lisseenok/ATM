#ifndef __PRINTER__
#define __PRINTER__
#include "Base.h"

/** Объект для вывода состояния или результата операции банкомата на консоль
*/

class Printer:public Base
{
public:
    Printer(Base* parent, string name):Base(parent, name, 6){};
    void handlerTurnOff(string str);
    void handlerPrintReadyToWork(string str);
    void handlerPrintEnterPin(string str);
    void handlerPrintSelectTheCommand(string str);
    void handlerPrintCardBalance(string str);
};
#endif