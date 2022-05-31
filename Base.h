#ifndef __BASE_H__
#define __BASE_H__
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

// new
class Base;
typedef void (Base::*TYPE_SIGNAL)(string &);
typedef void (Base::*TYPE_HANDLER)(string);

// каст к TYPE_SIGNAL и TYPE_HANDLER
#define SIGNAL_D(s) (TYPE_SIGNAL)(&s);
#define HANDLER_D(h) (TYPE_HANDLER)(&h);

class Base
{
    struct Connection
    {
        Base* connected; // объект, принимающий сигнал
        TYPE_SIGNAL signal; // указатель на метод отправляющий сигнал
        TYPE_HANDLER handler; // указатель на метод принимающий сигнал
        Connection(Base* c, TYPE_SIGNAL s, TYPE_HANDLER h): connected(c), signal(s), handler(h){};
    };
    int number;
    vector<Connection*> connections; // связи текущего объекта

    string name;
    Base* parent;
    vector<Base*> children;
    int state;
    Base* current;

public:
    Base(Base* parent, string name="", int number = 1);
    ~Base();
    string getName();
    void setName(string name);
    Base* getParent();
    void setParent(Base* newParent);

    void print(string s);

    Base* search(string name);
    bool setState(int state);
    void printWithState(string s);
    int getState();

    Base* getByPath(string path);
    void setCurrent(Base* current);
    Base* getCurrent();


    // new
    void setConnection(Base* c, TYPE_SIGNAL s, TYPE_HANDLER h);
    void deleteConnection(Base* c, TYPE_SIGNAL s, TYPE_HANDLER h);
    void emitSignal(TYPE_SIGNAL s, string str="");
    int getNumber();
    string getPath();

    void signalPrintMsg(string &str){}


};
#endif