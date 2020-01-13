/*
   This software is the driver for my "cyberbracer" cosplay.
   See https://github.com/djsegfault/arduino/tree/master/cyberbracer for source and project information

   Copyright 2019 David Kramer david@thekramers.net

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef CYBERTRACER_ACTIVITIES_H
#define CYBERTRACER_ACTIVITIES

class Activity {
  protected:
    unsigned long currTime = 0;        // Current time in millis, updated every call to update()
    unsigned long lastUpdateTime = 0;  // Last time the update ran
    unsigned long interval = 0;        // How many millis between updates
    char* name;                        // Name of the activity
  public:
    Activity(char* name, unsigned long interval);
    virtual void update();
    virtual void leftButtonPressed();
    virtual void rightButtonPressed();

    char* getName();
    boolean isTimeToUpdate();
    void updated();
};

class NullActivity: public Activity {
  public:
    NullActivity();
    void update();
    void leftButtonPressed();
    void rightButtonPressed();
};

class BlinkActivity: public Activity {
  public:
    BlinkActivity();
    void update();
    void leftButtonPressed();
    void rightButtonPressed();
  private:
    boolean isLightOn;
};


class SoundActivity: public Activity {
  public:
    SoundActivity();
    void update();
    void leftButtonPressed();
    void rightButtonPressed();
  private:
    int16_t maxLevel;
};

class SoundColorWheelActivity: public Activity {
  public:
    SoundColorWheelActivity();
    void update();
    void leftButtonPressed();
    void rightButtonPressed();
  private:
    int16_t maxLevel;
    uint8_t currPixel;
};


class TemperatureActivity: public Activity {
  public:
    TemperatureActivity();
    void update();
    void leftButtonPressed();
    void rightButtonPressed();
  private:
    int16_t maxLevel;
    uint8_t currPixel;
};


// The singletons for each activity
NullActivity nullActivity;
BlinkActivity blinkActivity;
SoundActivity soundActivity;
SoundColorWheelActivity soundColorWheelActivity;
TemperatureActivity temperatureActivity;

#endif
