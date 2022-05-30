#include "Receiver.h"

void Receiver::handlerAddMoneyToDeposit(string str) {
    int sum = stoi(str);
    if (sum % 100 == 0 && (sum == 5000 || sum == 2000 || sum == 1000 || sum == 500 || sum == 100))
    {
        currentDeposit += sum;
        emitSignal((TYPE_SIGNAL)(&Receiver::signalPrintMsg), "The amount: " + to_string(currentDeposit));
    }
}

void Receiver::handlerEndDeposit(string str) {
    emitSignal((TYPE_SIGNAL)(&Receiver::signalDepositToCard), str + to_string(currentDeposit)); // кладем на баланс
    emitSignal((TYPE_SIGNAL)(&Receiver::signalReturnCardBalance), str); // отправляем сигнал системе, чтобы та отправила принтеру баланс
    currentDeposit = 0;
}

