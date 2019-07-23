class Activity {
  protected:
    unsigned long currTime = 0;      // Current time in millis, updated every call to update()
    unsigned long lastUpdateTime = 0; // Last time the update ran
    unsigned long interval = 0;      // How many millis between updates
    char* name;                      // Name of the activity
  public:
    Activity(char* name, unsigned long interval);
    virtual void update();
    char* getName();

    boolean isTimeToUpdate();
};

class NullActivity: public Activity {
  public:
    NullActivity();
    void update();
};

class BlinkActivity: public Activity {
  public:
    BlinkActivity();
    void update();
    private:
    boolean isLightOn;
};
