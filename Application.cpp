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
    /**
     INITIALIZING OBJECTS
     */
    Reader *reader = new Reader(this, "reader"); // Объект для чтения команд и данных
    Console *console = new Console(this, "console"); // Объект пульта управления, для отработки нажатия кнопок (команд)
    Identifier *identifier = new Identifier(this, "identifier"); // Объект, моделирующий устройства идентификации банковской карты
    Receiver *receiver = new Receiver(this, "receiver"); // Объект, моделирующий устройства приема денег
    Issuancer *issuancer = new Issuancer(this, "issuancer"); // Объект, моделирующий устройства выдачи денег
    Printer *printer = new Printer(this, "printer"); // Объект для вывода состояния или результата операции банкомата на консоль.

    /**
     SETTING CONNECTIONS
     */
    TYPE_SIGNAL signal;
    TYPE_HANDLER handler;

    // application's signals
    signal = SIGNAL_D(Application::signalReadNewCommand);
    handler = HANDLER_D(Reader::handlerReadNewCommand);
    setConnection(reader, signal, handler);

    signal = SIGNAL_D(Application::signalSetUp);
    handler = HANDLER_D(Reader::handlerSetUp);
    setConnection(reader, signal, handler);

    signal = SIGNAL_D(Application::signalPrintMsg);
    handler = HANDLER_D(Printer::handlerPrintMsg);
    setConnection(printer, signal, handler);


    // reader's signals
    signal = SIGNAL_D(Reader::signalConsole);
    handler = HANDLER_D(Console::handlerText);
    reader->setConnection(console, signal, handler);

    signal = SIGNAL_D(Reader::signalAddUser);
    handler = HANDLER_D(Application::handlerAddUser);
    reader->setConnection(this, signal, handler);

    signal = SIGNAL_D(Reader::signalAddMoney);
    handler = HANDLER_D(Application::handlerAddMoney);
    reader->setConnection(this, signal, handler);

    signal = SIGNAL_D(Reader::signalPrintMsg);
    handler = HANDLER_D(Printer::handlerPrintMsg);
    reader->setConnection(printer, signal, handler);

    // console's signals
    signal = SIGNAL_D(Console::signalReadNewCommand);
    handler = HANDLER_D(Reader::handlerReadNewCommand);
    console->setConnection(reader, signal, handler);

    signal = SIGNAL_D(Console::signalPrintTurnOff);
    handler = HANDLER_D(Printer::handlerTurnOff);
    console->setConnection(printer, signal, handler);

    signal = SIGNAL_D(Console::signalPrintMsg);
    handler = HANDLER_D(Printer::handlerPrintMsg);
    console->setConnection(printer, signal, handler);

    signal = SIGNAL_D(Console::signalAddMoneyToDeposit);
    handler = HANDLER_D(Receiver::handlerAddMoneyToDeposit);
    console->setConnection(receiver, signal, handler);

    signal = SIGNAL_D(Console::signalEndDeposit);
    handler = HANDLER_D(Receiver::handlerEndDeposit);
    console->setConnection(receiver, signal, handler);

    signal = SIGNAL_D(Console::signalWithdrawMoney);
    handler = HANDLER_D(Issuancer::handlerWithdrawMoney);
    console->setConnection(issuancer, signal, handler);


    // receiver's signals
    signal = SIGNAL_D(Receiver::signalDepositToCard);
    handler = HANDLER_D(Application::handlerDepositToCard);
    receiver->setConnection(this, signal, handler);

    signal = SIGNAL_D(Receiver::signalReturnCardBalance);
    handler = HANDLER_D(Application::handlerReturnCardBalance);
    receiver->setConnection(this, signal, handler);

    signal = SIGNAL_D(Receiver::signalPrintMsg);
    handler = HANDLER_D(Printer::handlerPrintMsg);
    receiver->setConnection(printer, signal, handler);

    // issuancer's signals
    signal = SIGNAL_D(Issuancer::signalWithdrawMoneyToApp);
    handler = HANDLER_D(Application::handlerWithdrawMoneyToApp);
    issuancer->setConnection(this, signal, handler);

    return true;

}

int Application::execApp()
/**
 * 1) привести все объекты в состояние готовности (done)
 * 2) цикл для обработки вводимых данных для загрузки банкомата (done)
 *       - выдача сигнала объекту для ввода данных
 *       - отработка операции загрузки
   3) цикл для обработки вводимых команд банкомата
        - выдача сигнала объекту для ввода команды
        - отработка команды
   4) после ввода команды «Turn off the ATM» завершить работу (done)
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

void Application::handlerDepositToCard(string str) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].card == str.substr(0, 19)) {
            users[i].balance += stoi(str.substr(19));
        }
    }
}

void Application::handlerReturnCardBalance(string str) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].card == str) emitSignal((TYPE_SIGNAL)(&Application::signalPrintMsg), "Card balance " + to_string(users[i].balance));
    }

}

void Application::handlerWithdrawMoneyToApp(string str) {
    string card = str.substr(0, 19);
    int sum = stoi(str.substr(19));
    if (sum > getCurrentSum()) {
        emitSignal((TYPE_SIGNAL) (&Application::signalPrintMsg), "There is not enough money in the ATM");
        return;
    }
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].card == card)
        {
            if (users[i].balance < sum)
            {
                emitSignal((TYPE_SIGNAL)(&Application::signalPrintMsg), "There is not enough money on the card");
                return;
            }
        }
    }
    vector<int> withdrawMoney = {0, 0, 0, 0, 0};
    while (sum > 0)
    {
        if (sum >= 5000)
        {
            sum -= 5000;
            withdrawMoney[0] += 1;
        } else if (sum >= 2000)
        {
            sum -= 2000;
            withdrawMoney[1] += 1;
        } else if (sum >= 1000)
        {
            sum -= 1000;
            withdrawMoney[2] += 1;
        } else if (sum >= 500)
        {
            sum -= 500;
            withdrawMoney[3] += 1;
        } else if (sum >= 100)
        {
            sum -= 100;
            withdrawMoney[4] += 1;
        }
    }
    cout << withdrawMoney[0] << endl;
    cout << withdrawMoney[1] << endl;
    cout << withdrawMoney[2] << endl;
    cout << withdrawMoney[3] << endl;
    cout << withdrawMoney[4] << endl;
}

int Application::getCurrentSum() {
    /**
     метод, возвращающий текущую сумму денег в банкомате
     */
    return money.amountOf100 * 100 + money.amountOf500 * 500 + money.amountOf1000 * 1000 + money.amountOf2000 * 2000 + money.amountOf5000 * 5000;
}


