#ifndef __IDENTIFICATOR__
#define __IDENTIFICATOR__

#include "Base.h"

/** Объект, моделирующий устройства идентификации банковской карты.
Выдает сигнал, содержащий текст результата идентификации.
*/

class Identifier : public Base {
public:
    Identifier(Base *parent, string name) : Base(parent, name) {};

    void signalReadPin(string &str) {} // метод сигнала объекту Reader для считывания пин-кода
    void signalCheckPin(string &str) {} // метод сигнала объекту Application для проверки верности пин-кода
    void signalSuccessfulAuth(string &str) {} // метод сигнала объекту Console для установки состояния "пользователь авторизован" (isAuth = true)

    void handlerIdentificate(string str); // метод обработчика сигнала от объекта Console, отправляет сигнал объекту Reader, чтобы тот считал пин-код
    void handlerWithEnteredPin(string str); // метод обработчика сигнала от объекта Reader, отправляет сигнал системе, чтобы та проверила корректность пин-кода
    void handlerPinIsCorrect(string str); // метод обработчика сигнала от объекта Applicarion для отправки сигнала консоли об успешной авторизации
};

#endif