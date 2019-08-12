#include <YNE.hpp>

YNE yne = YNE();

void setup() {
    pinMode(13, OUTPUT);

    yne.begin();
}

void loop() {
    yne.update();

    if (yne.alpha() > 10) {
        digitalWrite(13, HIGH);
    } else {
        digitalWrite(13, LOW);
    }

    delay(50);
}
