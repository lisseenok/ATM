#ifndef __CONSOLE__
#define __CONSOLE__

#include "Base.h"

/** Объект пульта управления, для отработки нажатия кнопок (команд).
Объект после нажатия кнопки анализирует возможность его выполнения и выдает соответствующий сигнал.
Выдает сигнал если запрошенная для снятия сумма не кратна 100 или на карте нет достаточных средств
*/
class Console : public Base {
    bool isAuth = false; // обработать при правильном пин коде (сигнал от идентификатора)
    string currentCard;

public:
    Console(Base *parent, string name) : Base(parent, name) {}

    void signalReadNewCommand(string &str) {} // метод сигнала объекту Reader для считывания новой строки данных
    void signalPrintTurnOff(string &str) {} // метод сигнала объекту Printer для вывода сообщения о выключении банкомата

    void signalAddMoneyToDeposit(string &srt) {} // метод сигнала объекту Receiver для добавления суммы на баланс пользователя
    void signalEndDeposit(string &srt) {} // метод сигнала объекту Receiver об окончании внесения денег на карту
    void signalWithdrawMoney(string &srt) {} // метод сигнала объекту Issuancer для выдачи денег
    void signalIdentificate(string &srt) {} // метод сигнала объекту Identifier с номером карты для запроса пин-кода

    void signalShowTree(string &srt) {} // метод сигнала объекту Application для вывода дерева иерархии объектов

    void handlerText(string str); // метод обработчика сигнала от объекта Reader для обработки новой порции данных (команды)
    void handlerSuccessfulAuth(string str); // метод обработчика сигнала от объекта Identifier для установки состояния "пользователь авторизован" (isAuth = true)
    void handlerNotIsAuth(string str); // метод обработчика сигнала от объекта Reader для установки состояния "пользователь не авторизован" (isAuth = false)
};

#endif