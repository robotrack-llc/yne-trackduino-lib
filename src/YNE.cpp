#include "YNE.hpp"

#include "Arduino.h"

namespace YNE {
namespace {
char _receivedData[30];
char _comp[32] = {0x01, 0x1C, 0x40, 0x00, 0x19, 0x3C, 0x44, 0x45, 0x56, 0x49, 0x43, 0x45, 0x3E, 0x52, 0x4F, 0x42,
                  0x4F, 0x54, 0x3C, 0x2F, 0x44, 0x45, 0x56, 0x49, 0x43, 0x45, 0x3E, 0x0D, 0x0A, 0x0D, 0xC7, 0x1E};

const int _N = 7;

int _RM64 = 0;
int _RM65 = 0;
int _RM66 = 0;
int _RM67 = 0;
int _RM68 = 0;

int signedToUnsigned(int number) {
    int tmp = number;

    if (tmp < 0) {
        tmp += 256;
    }

    return tmp;
}
};  // namespace

void begin() { Serial.begin(115200); }

void update() {
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
            case 0x68:
                _RM68 = _receivedData[_N - 1];
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

int alpha() { return signedToUnsigned(_RM64); }

int beta() { return signedToUnsigned(_RM68); }

int heart() { return signedToUnsigned(_RM66); }

int muscle() { return signedToUnsigned(_RM67); }

int p300() { return signedToUnsigned(_RM65); }
};  // namespace YNE
