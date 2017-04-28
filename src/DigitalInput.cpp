#include "DigitalInput.h"
#include "Constants.h"

#if defined(ST_ARDUINO)
    #include <Arduino.h>
#endif

namespace st
{
    //private:

    //public:
    DigitalInput::DigitalInput(uint8_t pin, bool pullup, bool invertLogic):
        m_bPullup(pullup),
        m_bInvertLogic(invertLogic)
    {
        setPin(pin);
    }

    void DigitalInput::setPin(uint8_t pin)
    {
        m_nPin = pin;
        
    #if defined(ST_ARDUINO)
        if(m_bPullup)
            pinMode(m_nPin, INPUT_PULLUP);
        else
            pinMode(m_nPin, INPUT);
    #endif    
    }

    void DigitalInput::setPullup(bool pullup)
    {
        m_bPullup = pullup;
        setPin(m_nPin);
    }

    void DigitalInput::setInvertLogic(bool invertLogic)
    {
        m_bInvertLogic = invertLogic;
    }

    bool DigitalInput::operator()()
    {
        bool result = false;

    #if defined(ST_ARDUINO)
        result = digitalRead(m_nPin);
    #endif

        if(m_bInvertLogic)
            result = !result;

        return result;
    }

    bool DigitalInput::isTrue()
    {
        return (*this)();
    }

    bool DigitalInput::isFalse()
    {
        return !(*this)();
    }
}
