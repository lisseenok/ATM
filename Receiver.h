#ifndef __RECEIVER__
#define __RECEIVER__
#include "Base.h"

/** Объект, моделирующий устройства приема денег. 
После принятия очередной купюры сохраняет его. 
При внесении денег подряд производит суммирование. 
Выдает сигнал, содержащий сумму введенных денег для отображения на экран.
*/

class Receiver:public Base
{
public:
    Receiver(Base* parent, string name):Base(parent, name, 5){};
    void signal(string &str);
    void handler(string str);
};
#endif