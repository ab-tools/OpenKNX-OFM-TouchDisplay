#include <Arduino.h>
#include <lvgl.h>

#ifndef DISPLAY_SLEEP_DELAY
    #define DISPLAY_SLEEP_DELAY 10000
#endif

class TouchDisplayModule : public OpenKNX::Module
{
    public:
        const std::string name() override;
        const std::string version() override;
        const uint8_t _major = 0; // also update library.json
        const uint8_t _minor = 0;
        const uint8_t _build = 1;
        void setup(bool configured);
        void loop(bool configured) override;
        void displayTouched();

    private:
        inline static bool _displayOn;
        inline static unsigned long _lastPressed;
};