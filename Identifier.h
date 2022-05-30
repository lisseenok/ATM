#ifndef __IDENTIFICATOR__
#define __IDENTIFICATOR__
#include "Base.h"

/** Объект, моделирующий устройства идентификации банковской карты. 
Выдает сигнал, содержащий текст результата идентификации.
*/

class Identifier: public Base
{
public:
    Identifier(Base* parent, string name): Base(parent, name, 4){};
    void signalReadPin(string &str){}
    void signalCheckPin(string &str){}
    void signalSuccessfulAuth(string &str){}

    void handlerIdentificate(string str);
    void handlerWithEnteredPin(string str);
    void handlerPinIsCorrect(string str);
};
#endif