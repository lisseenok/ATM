#ifndef __RECEIVER__
#define __RECEIVER__

#include "Base.h"

/** Объект, моделирующий устройства приема денег.
После принятия очередной купюры сохраняет его.
При внесении денег подряд производит суммирование.
Выдает сигнал, содержащий сумму введенных денег для отображения на экран.
*/

class Receiver : public Base {
    int currentDeposit = 0;
public:
    Receiver(Base *parent, string name) : Base(parent, name) {};

    void signalDepositToCard(string &str) {} // метод сигнала объекту Application для добавления суммы на баланс текущего пользователя
    void signalReturnCardBalance(string &str) {} // метод сигнала объекту Application для получения баланса текущего пользователя
    void signalAdd(string &str) {}

    void handlerAddMoneyToDeposit(string str); // метод обработчика сигнала от объекта Console, добавляющий сумму на депозит (поле currentDeposit)
    void handlerEndDeposit(string str); // ометод обработчика сигнала от объекта Console для окончания режима депозита (для внесения накопленной суммы на карту)
};

#endif