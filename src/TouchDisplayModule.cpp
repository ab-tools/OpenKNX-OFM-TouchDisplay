#include "TouchDisplayModule.h"
#include "versions.h"
#include <ui.h>
#include "lv_xiao_round_screen.h"

// Give your Module a name
// it will be displayed when you use the method log("Hello")
//  -> Log     Hello
const std::string TouchDisplayModule::name()
{
    return "TouchDisplay";
}

// You can also give it a version
// will be displayed in Command Infos
const std::string TouchDisplayModule::version()
{
    return MODULE_TouchDisplayModule_Version;
}

void TouchDisplayModule::lv_log(const char * buf)
{
    logTraceP(buf);
}

void TouchDisplayModule::setup(bool configured)
{
    TouchDisplayModule::displayOn = true;
    TouchDisplayModule::lastTouched = 0;

    lv_log_register_print_cb(lv_log);
    lv_init();
    lv_xiao_disp_init();
    lv_xiao_touch_init();
    ui_init();

    displayTouched();
}

void TouchDisplayModule::displayTouched() {
    TouchDisplayModule::_lastTouched = millis();

    if (!TouchDisplayModule::_displayOn) {#
        logDebugP("Turn display on.");
        TouchDisplayModule::_displayOn = true;
        digitalWrite(XIAO_BL, HIGH);
    }
}

void TouchDisplayModule::loop(bool configured)
{
    lv_timer_handler(); // let the GUI do its work 
    // delay(5); // this delay comes from the original LVGL sample, not sure if a good to delay here

    if (TouchDisplayModule::_displayOn && (millis() - TouchDisplayModule::_lastTouched > DISPLAY_SLEEP_DELAY)) {
        logDebugP("Turn display off.");
        TouchDisplayModule::_displayOn = false;
        digitalWrite(XIAO_BL, LOW);
    }
}