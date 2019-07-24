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


// The singletons for each activity
NullActivity nullActivity;
BlinkActivity blinkActivity;
SoundActivity soundActivity;
SoundColorWheelActivity soundColorWheelActivity;

#endif
