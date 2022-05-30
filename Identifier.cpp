//
// Created by Елизавета Цаплина on 29.05.2022.
//

#include "Identifier.h"

void Identifier::handlerIdentificate(string str) {
    emitSignal((TYPE_SIGNAL)(&Identifier::signalPrintMsg), "Enter the PIN code");
    emitSignal((TYPE_SIGNAL)(&Identifier::signalReadPin), str);
}

void Identifier::handlerWithEnteredPin(string str) {
    emitSignal((TYPE_SIGNAL)(&Identifier::signalCheckPin), str);
}

void Identifier::handlerPinIsCorrect(string str) {
    emitSignal((TYPE_SIGNAL)(&Identifier::signalPrintMsg), "Select the command");
    emitSignal((TYPE_SIGNAL)(&Identifier::signalSuccessfulAuth));
}

