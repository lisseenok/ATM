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
        int balance;
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
    Application(): Base(nullptr, ""){};
    bool buildTreeObjects(); // построение иерархии
    int execApp();


    void signalReadNewCommand(string &str){}
    void signalSetUp(string &str){}

    void handlerAddUser(string str);
    void handlerAddMoney(string str);
};
#endif