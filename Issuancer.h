#ifndef __ISSUANCER__
#define __ISSUANCER__

#include "Base.h"

/** Объект, моделирующий устройства выдачи денег.
Выдает сигнал, содержащий количество купюр возвращаемой суммы
или информацию о невозможности получить необходимый состав купюр.
*/

class Issuancer : public Base {
public:
    Issuancer(Base *parent, string name) : Base(parent, name) {};

    void signalWithdrawMoneyToApp(string &srt) {} // метод сигнала для объекта Application для выдачи денег

    void handlerWithdrawMoney(string str); // метод обработчика сигнала от объекта Console для отправки сигнала системе (signalWithdrawMoneyToApp)

};

#endif