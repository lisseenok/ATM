#ifndef __READER__
#define __READER__
#include "Base.h"

/** Объект для чтения команд и данных. Считывает данные для подготовки и настройки банкомата. 
После чтения очередной порции данных для настройки или данных команды, объект выдает сигнал с текстом полученных данных. 
Все данные настройки и данные команды синтаксический корректны.
*/

class Reader:public Base
{
public:
    Reader(Base* parent, string name):Base(parent, name, 2){}

    void signalConsole(string &str){}
    void signalAddUser(string &str){}
    void signalAddMoney(string &str){}
    void signalPrintReadyToWork(string &str){}

    void handlerReadNewCommand(string str);
    void handlerSetUp(string str);
};
#endif