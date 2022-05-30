#include "Receiver.h"

void Receiver::handlerAddMoneyToDeposit(string str) {
    if (stoi(str) % 100 == 0)
    {
        currentDeposit += stoi(str);
        emitSignal((TYPE_SIGNAL)(&Receiver::signalPrintMsg), "The amount: " + str);
    }
}

void Receiver::handlerEndDeposit(string str) {
    emitSignal((TYPE_SIGNAL)(&Receiver::signalDepositToCard), str + to_string(currentDeposit)); // кладем на баланс
    emitSignal((TYPE_SIGNAL)(&Receiver::signalReturnCardBalance), str); // отправляем сигнал системе, чтобы та отправила принтеру баланс
    currentDeposit = 0;
}

