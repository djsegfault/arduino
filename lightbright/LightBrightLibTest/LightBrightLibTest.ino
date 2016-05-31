#include <Pin.h>
#include <DigitalOutPin.h>
#include <Channel.h>
#include <ArduinoUnit.h>

#define TEST_PIN 13

Pin testPin1(TEST_PIN);

DigitalOutPin testDOPin1(TEST_PIN);
Channel testChannel1(testPin1);

test(PinPin)
{
  Pin testPinL1(TEST_PIN);
  assertEqual(TEST_PIN, testPinL1.getPinNumber());
  testPinL1.setPinNumber(11);
  assertEqual(11, testPinL1.getPinNumber());
}

test(PinValue)
{
  testPin1.off();
  testPin1.on();
  assertEqual(PIN_MAX_VALUE, testPin1.getValue());

  testPin1.off();
  assertEqual(PIN_MIN_VALUE, testPin1.getValue());

  testPin1.setValue(PIN_MAX_VALUE);
  assertEqual(PIN_MAX_VALUE, testPin1.getValue());

  testPin1.setValue(10);
  assertEqual(10, testPin1.getValue());

  testPin1.setValue(0);
  assertEqual(0, testPin1.getValue());
}

test(PinMockMode)
{
  testPin1.setMock(false);
  testPin1.setMock(true);
  assertEqual(true, testPin1.getMock());
  testPin1.setMock(false);
  assertEqual(false, testPin1.getMock());
}

test(DOPinOnOff)
{
  testDOPin1.off();
  testDOPin1.on();
  assertEqual(HIGH, testDOPin1.getValue());
  testDOPin1.off();
  assertEqual(LOW, testDOPin1.getValue());
}

test(ChannelPin)
{
  assertEqual(TEST_PIN, testChannel1.getPin().getPinNumber());
}

test(ChannelLevel)
{
    testChannel1.setMasterLevel(PIN_MAX_VALUE);
    testPin1.setDebug(true);
    
    testChannel1.setLevel(42);
    assertEqual(42, testChannel1.getPin().getValue());
    
    testChannel1.setMasterLevel(128);
    assertEqual(42 * ((float)128/(float)PIN_MAX_VALUE), testChannel1.getPin().getValue());

    testChannel1.setMasterLevel(10);
    assertEqual(42 * ((float)10/(float)PIN_MAX_VALUE), testChannel1.getPin().getValue());

    testChannel1.off();
    assertEqual(0, testChannel1.getPin().getValue());

    testChannel1.on();
    assertEqual(10, testChannel1.getPin().getValue());

    testChannel1.setMasterLevel(100);
}


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Test::run();
}
