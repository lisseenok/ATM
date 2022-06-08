#ifndef __PRINTER__
#define __PRINTER__

#include "Base.h"

/** Объект для вывода состояния или результата операции банкомата на консоль
*/

class Printer : public Base {
public:
    Printer(Base *parent, string name) : Base(parent, name) {};

    void handlerPrintMsg(string str); // метод обработчика сигнала от любого объекта, унаследованного от Base, для вывода на экран сообщения, переданного в параметрах
    void handlerTurnOff(string str); // метод обработчика сигнала от объекта Console для вывода сообщения о выключении банкомата
};

#endif