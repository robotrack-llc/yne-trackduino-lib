#include "YNE.hpp"
#include "Arduino.h"

YNE::YNE() {}

void YNE::begin() { Serial.begin(115200); }

void YNE::update() {
    _receivedData[_N - 1] = Serial.read();

    if (_receivedData[_N - 1] == -1) {
        return;
    }

    if (strncmp(_receivedData, "/reg", 4) == 0) {
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

    for (size_t kil = 1; kil < _N; ++kil) {
        _receivedData[kil - 1] = _receivedData[kil];
    }
}

int YNE::alpha() { return _RM64; }

int YNE::heart() { return _RM66; }

int YNE::muscle() {
    int tmp;
    if (_RM67 < 0) {
        tmp = _RM67 + 256;
    } else {
        tmp = _RM67;
    }

    return constrain(tmp, 0, 127);
}

int YNE::p300() { return _RM65; }
