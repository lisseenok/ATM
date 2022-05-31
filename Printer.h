#ifndef __PRINTER__
#define __PRINTER__
#include "Base.h"

/** Объект для вывода состояния или результата операции банкомата на консоль
*/

class Printer:public Base
{
public:
    Printer(Base* parent, string name):Base(parent, name, 6){};
    void handlerPrintMsg(string str);
    void handlerTurnOff(string str);
};
#endif