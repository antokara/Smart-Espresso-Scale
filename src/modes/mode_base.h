#ifndef MODE_BASE
#define MODE_BASE

class Mode_Base
{
public:
    // constructor
    Mode_Base();

    // standard
    void setup();
    void loop();

    /**
     * @brief user actions
     *
     * those are abstract and must be implemented by the derived class
     * even for NOOP, to ensure we did not forget to handle a user action
     *
     */
    virtual void up() = 0;
    virtual void down() = 0;
    virtual void ok() = 0;
    virtual void cancel() = 0;
};

#endif // MODE_BASE