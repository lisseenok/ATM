#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "Base.h"


// Объект «система».
class Application:public Base
{
    struct User
    {
        string card;
        string pin;
        int balance = 0;
    };
    vector<User> users;

    struct Money
    {
        int amountOf5000 = 0;
        int amountOf2000 = 0;
        int amountOf1000 = 0;
        int amountOf500 = 0;
        int amountOf100 = 0;
    } money;

public:
    Application(): Base(nullptr, "ATM"){};
    bool buildTreeObjects(); // построение иерархии
    int execApp();
    int getCurrentSum();


    void signalReadNewCommand(string &str){} // сигнал ридеру прочесть новую строку
    void signalSetUp(string &str){} // сигнал ридеру для настройки банкомата
    void signalPinIsCorrect(string &str){}

    void handlerAddUser(string str);
    void handlerAddMoney(string str);
    void handlerDepositToCard(string str); // обработчик, вносящий деньги на карту
    void handlerReturnCardBalance(string str); // обработчик, передающий баланс карты
    void handlerWithdrawMoneyToApp(string str);
    void handlerCheckPin(string str);
    void handlerShowTree(string str);
};
#endif