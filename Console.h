#ifndef __CONSOLE__
#define __CONSOLE__
#include "Base.h"

/** Объект пульта управления, для отработки нажатия кнопок (команд). 
Объект после нажатия кнопки анализирует возможность его выполнения и выдает соответствующий сигнал. 
Выдает сигнал если запрошенная для снятия сумма не кратна 100 или на карте нет достаточных средств
*/
class Console:public Base
{
public:
    Console(Base* parent, string name):Base(parent, name, 3){};
    void signal(string &str);
    void handler(string str);
};
#endif