#include <PubSubClient.h>

#include <TaskManager.h>


void setup()
{
    Serial.begin(115200);
    delay(2000);

    // task interval is 1000[ms] and repeat forever
    Tasks.interval(1000, []{
        Serial.print("interval forever task: now = ");
        Serial.println(millis());
    });

    // task interval is 500[ms] and 10 times only
    Tasks.interval(500, 10, []{
        Serial.print("interval limited task: now = ");
        Serial.println(millis());
    });

    Serial.print("task start: now = ");
    Serial.println(millis());
}

void loop()
{
    Tasks.update();
}
