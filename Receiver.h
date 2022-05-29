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
    int currentDeposit = 0;
public:
    Receiver(Base* parent, string name):Base(parent, name, 5){};

    void signalDepositToCard(string &str) {}
    void signalReturnCardBalance(string &str) {}
    void signalPrintAmount(string &str) {}


    void handlerAddMoneyToDeposit(string str); // добавление денег
    void handlerEndDeposit(string str); // окончание депозита
};
#endif