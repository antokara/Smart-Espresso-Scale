#ifndef MODE_BASE
#define MODE_BASE

class Mode_Base
{
public:
    // standard methods (must be implemented by the derived class)
    virtual void setup() = 0;
    virtual void loop() = 0;

    /**
     * @brief user actions
     *
     * these are abstract and must be implemented by the derived class
     * even for NOOP, to ensure we did not forget to handle a user action
     *
     */
    virtual void tare() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
    virtual void ok() = 0;
    virtual void cancel() = 0;
    virtual void coffee() = 0;
};

#endif // MODE_BASE