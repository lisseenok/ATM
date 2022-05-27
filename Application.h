#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include "Base.h"


// Объект «система».
class Application:public Base
{
public:
    Application(): Base(nullptr, ""){};
    bool buildTreeObjects(); // построение иерархии
    int execApp(); // печать иерархии

    // new methods
    void enterConnections();
    void signal(string &str);
    void handler(string str);
};
#endif