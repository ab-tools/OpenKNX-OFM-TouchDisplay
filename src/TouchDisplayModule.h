#include "OpenKNX.h"
#include <lvgl.h>

#ifndef MODULE_TouchDisplayModule_Version
    #define MODULE_TouchDisplayModule_Version "dev"
#endif

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
        bool isBacklightOn();

    private:

        static void lv_log(const char * buf);

        inline static bool _backlightOn;
        inline static unsigned long _lastTouched;
};