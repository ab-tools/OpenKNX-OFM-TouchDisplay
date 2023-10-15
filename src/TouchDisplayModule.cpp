#include "TouchDisplayModule.h"
#include "versions.h"
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
    TouchDisplayModule::_backlightOn = true;
    TouchDisplayModule::_lastTouched = 0;

    lv_log_register_print_cb(lv_log);
    displayTouched();
}

void TouchDisplayModule::initUi() {
    lv_init();
    lv_xiao_disp_init();
    lv_xiao_touch_init();
}

void TouchDisplayModule::displayTouched() {
    TouchDisplayModule::_lastTouched = millis();

    if (!TouchDisplayModule::_backlightOn) {
        logInfoP("Turn display on.");
        TouchDisplayModule::_backlightOn = true;
        digitalWrite(XIAO_BL, HIGH);
    }
}

bool TouchDisplayModule::isBacklightOn() {
    return _backlightOn;
}

void TouchDisplayModule::loopUi()
{
    lv_timer_handler(); // let the GUI do its work 
    // delay(5); // this delay comes from the original LVGL sample, not sure if a good to delay here

    if (TouchDisplayModule::_backlightOn && (millis() - TouchDisplayModule::_lastTouched > DISPLAY_SLEEP_DELAY)) {
        logInfoP("Turn display off.");
        TouchDisplayModule::_backlightOn = false;
        digitalWrite(XIAO_BL, LOW);
    }
}