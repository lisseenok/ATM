#ifndef __READER__
#define __READER__

#include "Base.h"

/** Объект для чтения команд и данных. Считывает данные для подготовки и настройки банкомата.
После чтения очередной порции данных для настройки или данных команды, объект выдает сигнал с текстом полученных данных.
Все данные настройки и данные команды синтаксический корректны.
*/

class Reader : public Base {
public:
    Reader(Base *parent, string name) : Base(parent, name) {}

    void signalConsole(string &str) {} // сигнал консоли для передачи новой команды, обработчик - handlerText
    void signalAddUser(string &str) {} // метод сигнала объекту Application для добавления нового пользователя в поле users
    void signalAddMoney(string &str) {} // метод сигнала объекту Application для добавления информации об купюрах в поле money
    void signalWithEnteredPin(string &str) {} // метод сигнала объекту Identifier, передающий введенный пользователем пин-код, для отправки сигнала системе, чтобы та проверила правильности пин-кода
    void signalNotIsAuth(string &str) {} // метод сигнала объекту Console для установления статуса "не авторизован" (isAuth = false)

    void handlerReadNewCommand(string str); // обработчик сигналов от объектов Console и Application, считывает новую команду и отправляет пульту управления
    void handlerSetUp(string str); // обработчик сигнала от объекта Application, считывает настройки банкомата
    void handlerReadPin(string str); // обработчик сигнала от объекта Identifier, считывает пин-код и отправляет объекту Identifier с помощью signalWithEnteredPin
};

#endif