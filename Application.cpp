#include "Application.h"
#include "Console.h"
#include "Identifier.h"
#include "Issuancer.h"
#include "Printer.h"
#include "Receiver.h"
#include "Reader.h"

void Application::buildTreeObjects()
/**
* 1) построить дерево иерархии
* 2) установить связи сигналов и обработчиков между объектами
*/
{
    /**
    INITIALIZING OBJECTS
    */
    Reader *reader = new Reader(this, "Reader"); // Объект для чтения команд и данных
    Console *console = new Console(this, "Console"); // Объект пульта управления, для отработки нажатия кнопок (команд)
    Identifier *identifier = new Identifier(this, "Identifier"); // Объект, моделирующий устройства идентификации банковской карты
    Receiver *receiver = new Receiver(this, "Receiver"); // Объект, моделирующий устройства приема денег
    Issuancer *issuancer = new Issuancer(this, "Issuancer"); // Объект, моделирующий устройства выдачи денег
    Printer *printer = new Printer(this, "Printer"); // Объект для вывода состояния или результата операции банкомата на консоль.

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

    signal = SIGNAL_D(Application::signalPinIsCorrect);
    handler = HANDLER_D(Identifier::handlerPinIsCorrect);
    setConnection(identifier, signal, handler);


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

    signal = SIGNAL_D(Reader::signalWithEnteredPin);
    handler = HANDLER_D(Identifier::handlerWithEnteredPin);
    reader->setConnection(identifier, signal, handler);

    signal = SIGNAL_D(Reader::signalNotIsAuth);
    handler = HANDLER_D(Console::handlerNotIsAuth);
    reader->setConnection(console, signal, handler);

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

    signal = SIGNAL_D(Console::signalIdentificate);
    handler = HANDLER_D(Identifier::handlerIdentificate);
    console->setConnection(identifier, signal, handler);

    signal = SIGNAL_D(Console::signalShowTree);
    handler = HANDLER_D(Application::handlerShowTree);
    console->setConnection(this, signal, handler);


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

    signal = SIGNAL_D(Receiver::signalAdd);
    handler = HANDLER_D(Application::handlerAdd);
    receiver->setConnection(this, signal, handler);

    // issuancer's signals
    signal = SIGNAL_D(Issuancer::signalWithdrawMoneyToApp);
    handler = HANDLER_D(Application::handlerWithdrawMoneyToApp);
    issuancer->setConnection(this, signal, handler);

    // identifier's signals
    signal = SIGNAL_D(Identifier::signalReadPin);
    handler = HANDLER_D(Reader::handlerReadPin);
    identifier->setConnection(reader, signal, handler);

    signal = SIGNAL_D(Identifier::signalCheckPin);
    handler = HANDLER_D(Application::handlerCheckPin);
    identifier->setConnection(this, signal, handler);

    signal = SIGNAL_D(Identifier::signalSuccessfulAuth);
    handler = HANDLER_D(Console::handlerSuccessfulAuth);
    identifier->setConnection(console, signal, handler);

    signal = SIGNAL_D(Identifier::signalPrintMsg);
    handler = HANDLER_D(Printer::handlerPrintMsg);
    identifier->setConnection(printer, signal, handler);


}

int Application::execApp()
/**
1) привести все объекты в состояние готовности (done)
2) цикл для обработки вводимых данных для загрузки банкомата (done)
		- выдача сигнала объекту для ввода данных
		- отработка операции загрузки
3) цикл для обработки вводимых команд банкомата
		- выдача сигнала объекту для ввода команды
		- отработка команды
4) после ввода команды «Turn off the ATM» завершить работу (done)
*/
{
    emitSignal((TYPE_SIGNAL) (&Application::signalSetUp));

    emitSignal((TYPE_SIGNAL) (&Application::signalReadNewCommand));
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
            break;
        }
    }
}

void Application::handlerReturnCardBalance(string str) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].card == str)
            emitSignal((TYPE_SIGNAL) (&Application::signalPrintMsg), "Card balance " + to_string(users[i].balance));
    }

}

void Application::handlerWithdrawMoneyToApp(string str) {
    string card = str.substr(0, 19);
    int sum = stoi(str.substr(19));
    int tmpSum = sum;
    if (sum > getCurrentSum()) {
        emitSignal((TYPE_SIGNAL) (&Application::signalPrintMsg), "There is not enough money in the ATM");
        return;
    }
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].card == card) {
            if (users[i].balance < sum) {
                emitSignal((TYPE_SIGNAL) (&Application::signalPrintMsg), "There is not enough money on the card");
                return;
            }
        }
    }
    vector<int> withdrawMoney = {0, 0, 0, 0, 0};
    while (sum > 0) {
        if (sum >= 5000) {
            sum -= 5000;
            withdrawMoney[0] += 1;
        } else if (sum >= 2000) {
            sum -= 2000;
            withdrawMoney[1] += 1;
        } else if (sum >= 1000) {
            sum -= 1000;
            withdrawMoney[2] += 1;
        } else if (sum >= 500) {
            sum -= 500;
            withdrawMoney[3] += 1;
        } else if (sum >= 100) {
            sum -= 100;
            withdrawMoney[4] += 1;
        } else {
            emitSignal((TYPE_SIGNAL) (&Application::signalPrintMsg), "There is not enough money in the ATM");
            return;
        }
    }
    if (money.amountOf5000 < withdrawMoney[0] || money.amountOf2000 < withdrawMoney[1] ||
        money.amountOf1000 < withdrawMoney[2] || money.amountOf500 < withdrawMoney[3] ||
        money.amountOf100 < withdrawMoney[4]) {
        emitSignal((TYPE_SIGNAL) (&Application::signalPrintMsg), "There is not enough money in the ATM");
        return;
    }
    // выводим сообщение
    emitSignal((TYPE_SIGNAL) (&Application::signalPrintMsg),
               "Take the money: 5000 * " + to_string(withdrawMoney[0]) + " rub., 2000 * " +
               to_string(withdrawMoney[1]) + " rub., 1000 * " + to_string(withdrawMoney[2]) + " rub., 500 * " +
               to_string(withdrawMoney[3]) + " rub.,  100 * " + to_string(withdrawMoney[4]) + " rub.");
    // вычитаем с баланса
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].card == card) {
            users[i].balance -= tmpSum;
        }
    }

}

int Application::getCurrentSum() {
    /**
    метод, возвращающий текущую сумму денег в банкомате
    */

    return money.amountOf100 * 100 + money.amountOf500 * 500 + money.amountOf1000 * 1000 + money.amountOf2000 * 2000 +
           money.amountOf5000 * 5000;
}

void Application::handlerCheckPin(string str) {
    string pin = str.substr(0, 4);
    string card = str.substr(4);
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].card == card) {
            if (users[i].pin == pin) emitSignal((TYPE_SIGNAL) (&Application::signalPinIsCorrect));
            return;
        }
    }
}

void Application::handlerShowTree(string str) {
    printWithState("");
    cout << endl;
}

void Application::handlerAdd(string str)
{
    if (str == "5000") money.amountOf5000 += 1;
    if (str == "2000") money.amountOf2000 += 1;
    if (str == "1000") money.amountOf1000 += 1;
    if (str == "500") money.amountOf500 += 1;
    if (str == "100") money.amountOf100 += 1;
}


