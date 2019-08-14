#include "YNE.hpp"
#include "Arduino.h"

YNE::YNE() {}

void YNE::begin() { Serial.begin(115200); }

void YNE::update() {
    _receivedData[_N - 1] = Serial.read();

    if (_receivedData[_N - 1] == -1) {
        return;
    }

    if ((_receivedData[_N - 6] == '/') && (_receivedData[_N - 5] == 'r') && (_receivedData[_N - 4] == 'e') && (_receivedData[_N - 3] == 'g')) {
        switch (_receivedData[_N - 2]) {
            case 0x64:
                _RM64 = _receivedData[_N - 1];
                break;
            case 0x65:
                _RM65 = _receivedData[_N - 1];
                break;
            case 0x66:
                _RM66 = _receivedData[_N - 1];
                break;
            case 0x67:
                _RM67 = _receivedData[_N - 1];
                break;
        }
    }

    if (strncmp(_receivedData, "/device", _N) == 0) {
        Serial.write(_comp, 32);
    }

    for (size_t i = 1; i < _N; ++i) {
        _receivedData[i - 1] = _receivedData[i];
    }
}

int YNE::alpha() { return _RM64; }

int YNE::heart() { return _RM66; }

int YNE::muscle() {
    int tmp = _RM67;

    if (_RM67 < 0) {
        tmp += 256;
    }

    return tmp;
}

int YNE::p300() { return _RM65; }
