#ifndef __ISSUANCER__
#define __ISSUANCER__
#include "Base.h"

/** Объект, моделирующий устройства выдачи денег. 
Выдает сигнал, содержащий количество купюр возвращаемой суммы 
или информацию о невозможности получить необходимый состав купюр.
*/

class Issuancer:public Base
{
public:
    Issuancer(Base* parent, string name):Base(parent, name, 6){};

    void handlerWithdrawMoney(string str);
};
#endif