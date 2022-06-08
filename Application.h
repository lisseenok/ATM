#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Base.h"


// Объект «система».
class Application : public Base {
    struct User {
        string card;
        string pin;
        int balance = 0;
    };
    vector <User> users;

    struct Money {
        int amountOf5000 = 0;
        int amountOf2000 = 0;
        int amountOf1000 = 0;
        int amountOf500 = 0;
        int amountOf100 = 0;
    } money;

public:
    Application() : Base(nullptr, "ATM") {};

    void buildTreeObjects(); // построение иерархии
    int execApp();
    int getCurrentSum(); // метод для подсчета общей суммы денег в банкомате

    void signalReadNewCommand(string &str) {} // сигнал ридеру прочесть новую строку
    void signalSetUp(string &str) {} // сигнал ридеру для настройки банкомата
    void signalPinIsCorrect(string &str) {} // метод сигнала объекту Identifier о корректности пин-кода

    void handlerAddUser(string str); // обработчик сигнала от объекта Reader для добавления нового пользователя в поле users
    void handlerAddMoney(string str); // обработчик сигнала от объекта Reader для добавления информации о купюрах в поле money
    void handlerDepositToCard(string str); // обработчик сигнала от ресивера, вносящий деньги на карту
    void handlerReturnCardBalance(string str); // обработчик, передающий баланс карты принтеру
    void handlerWithdrawMoneyToApp(string str); // обработчик сигнала от объекта Issuancer,  отвечает за выдачу денег
    void handlerCheckPin(string str); // обработчик сигнала от объекта Identifier, проверяет верный ли пин-код и отправляет сигнал обратно объекту Identifier (signalPinIsCorrect)
    void handlerShowTree(string str);
    void handlerAdd(string str);

};

#endif