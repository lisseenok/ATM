#include "Application.h"
#include "Console.h"
#include "Identifier.h"
#include "Issuancer.h"
#include "Printer.h"
#include "Receiver.h"
#include "Reader.h"

bool Application::buildTreeObjects()
/**
 * 1) построить дерево иерархии
 * 2) установить связи сигналов и обработчиков между объектами
 */
{
    Reader *reader = new Reader(this, "reader"); // Объект для чтения команд и данных
    Console *console = new Console(this, "console"); // Объект пульта управления, для отработки нажатия кнопок (команд)
    Identifier *identifier = new Identifier(this, "identifier"); // Объект, моделирующий устройства идентификации банковской карты
    Receiver *receiver = new Receiver(this, "receiver"); // Объект, моделирующий устройства приема денег
    Issuancer *issuancer = new Issuancer(this, "issuancer"); // Объект, моделирующий устройства выдачи денег
    Printer *printer = new Printer(this, "printer"); // Объект для вывода состояния или результата операции банкомата на консоль.

    // установка связей
    TYPE_SIGNAL signal;
    TYPE_HANDLER handler;

    // signals application
    signal = SIGNAL_D(Application::signalReadNewCommand);
    handler = HANDLER_D(Reader::handlerReadNewCommand);
    setConnection(reader, signal, handler);

    signal = SIGNAL_D(Application::signalSetUp);
    handler = HANDLER_D(Reader::handlerSetUp);
    setConnection(reader, signal, handler);

    // signals reader
    signal = SIGNAL_D(Reader::signalConsole);
    handler = HANDLER_D(Console::handlerText);
    reader->setConnection(console, signal, handler);

    signal = SIGNAL_D(Reader::signalAddUser);
    handler = HANDLER_D(Application::handlerAddUser);
    reader->setConnection(this, signal, handler);

    signal = SIGNAL_D(Reader::signalAddMoney);
    handler = HANDLER_D(Application::handlerAddMoney);
    reader->setConnection(this, signal, handler);

    // signals console
    signal = SIGNAL_D(Console::signalReadNewCommand);
    handler = HANDLER_D(Reader::handlerReadNewCommand);
    console->setConnection(reader, signal, handler);

    signal = SIGNAL_D(Console::signalPrintTurnOff);
    handler = HANDLER_D(Printer::handlerTurnOff);
    console->setConnection(printer, signal, handler);

    return true;

}

int Application::execApp()
/**
 * 1) привести все объекты в состояние готовности
 * 2) цикл для обработки вводимых данных для загрузки банкомата
 *       - выдача сигнала объекту для ввода данных
 *       - отработка операции загрузки
   3) цикл для обработки вводимых команд банкомата
        - выдача сигнала объекту для ввода команды
        - отработка команды
   4) после ввода команды «Turn off the ATM» завершить работу
 */

{
    emitSignal((TYPE_SIGNAL)(&Application::signalSetUp));

    emitSignal((TYPE_SIGNAL)(&Application::signalReadNewCommand));
    return 0;
}


void Application::handlerAddUser(string str) {
    string card = str.substr(0, 19);
    string pin = str.substr(20, 4);
    int balance = stoi(str.substr(25));
    users.push_back({card, pin, balance});
}

void Application::handlerAddMoney(string str) {
    money.amountOf5000 = stoi(str.substr(0, str.find(' ')));
    str = str.substr(str.find(' ') + 1);

    money.amountOf2000 = stoi(str.substr(0, str.find(' ')));
    str = str.substr(str.find(' ') + 1);

    money.amountOf1000 = stoi(str.substr(0, str.find(' ')));
    str = str.substr(str.find(' ') + 1);

    money.amountOf500 = stoi(str.substr(0, str.find(' ')));
    str = str.substr(str.find(' ') + 1);

    money.amountOf100 = stoi(str);


}


