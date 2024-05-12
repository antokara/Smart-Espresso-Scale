#include "services/device.h"
#include "services/lcd.h"
#include "services/buttons.h"
#include "services/modes_controller.h"
#include "services/presets/presets.h"
#include "services/scale.h"
#include "services/buzzer.h"
#include "services/ir.h"
#include "modes/select_preset.h"
#include "modes/brew.h"
#include "modes/tare.h"
#include "utils.h"

modes Mode_Brew::getMode()
{
    return modes_brew;
}

/**
 * @brief sets the brewing stage (it's kind of a like a sub-mode)
 *
 * @param stage
 */
void Mode_Brew::setStage(brew_stages stage)
{
    if (Mode_Brew::stage != stage)
    {
#ifdef SERIAL_DEBUG
        Serial.print("Mode_Brew::setStage");
        Serial.println(stage);
#endif
        Mode_Brew::stage = stage;
        Buttons::ignoreAll();
        Mode_Brew::render();
        if (stage == brew_stage_in_progress)
        {
            // keep the time the brew started
            Mode_Brew::brewStartTime = millis();
            if (Presets::getPreset()->autoPump == true)
            {
                // start the brew (toggle the relay switch)
                Ir::send();
#ifdef SERIAL_DEBUG
                Serial.println("Mode_Brew::start pump");
#endif
            }
        }
        else if (stage == brew_stage_stopping)
        {
            // keep the time the last drop fell (auto-refreshes if weight changes)
            Mode_Brew::timeAtLastDrop = millis();
        }
        else if (stage == brew_stage_done)
        {
            Buzzer::on(1500);
        }
    }
}

void Mode_Brew::setup()
{
    // reset
    Mode_Brew::brewStartTime = 0;
    Mode_Brew::brewSeconds = 0;
    Mode_Brew::estBrewWeight = 0;
    Mode_Brew::estBrewSecondsLeft = 99999;
    Mode_Brew::setStage(brew_stage_waiting);

    // start warning at 3...
    Mode_Brew::estBrewSecondsLeftWarning = 4;

    // calculate the ideal brew weight we expect at the end of the brewDuration
    Mode_Brew::targetBrewWeight = Presets::getPreset()->coffeeWeight * Presets::getPreset()->brewRatio;

    // auto-tare right before we start, to negate the cup (that should already be on the scale)
    Mode_Tare *mode_tare = new Mode_Tare();
    mode_tare->setup();
    delete mode_tare;
    Mode_Brew::render();
    if (Presets::getPreset()->autoPump == true)
    {
        Mode_Brew::setStage(brew_stage_in_progress);
    }
};

void Mode_Brew::loop()
{
    bool render = false;

    // handle brew time progression
    if (Mode_Brew::stage == brew_stage_in_progress || Mode_Brew::stage == brew_stage_stopping)
    {
        float brewSeconds = Utils::roundFloat((millis() - Mode_Brew::brewStartTime) / 1000.0, 1);
        if (abs(Mode_Brew::brewSeconds - brewSeconds) >= BREW_SECONDS_DELTA_RENDER)
        {
            Mode_Brew::brewSeconds = brewSeconds;
            render = true;
#ifdef SERIAL_DEBUG
            Serial.print(String(Mode_Brew::brewSeconds));
            Serial.print("  ");
            Serial.println(String(Scale::getWeight()));
#endif
#ifdef SERIAL_DEBUG_PLOT_TIME
            Serial.print(">time:");
            Serial.println(String(Mode_Brew::brewSeconds));
#endif
        }
    }

    // handle weight changes
    if (Scale::hasWeightChanged)
    {
        if (Mode_Brew::stage == brew_stage_waiting && Presets::getPreset()->startTimer == startTimer_first_drop)
        {
            if (Scale::getWeight() >= FIRST_DROP_WEIGHT)
            {
                Mode_Brew::setStage(brew_stage_in_progress);
            }
        }
        else if (Mode_Brew::stage == brew_stage_in_progress && Scale::getWeight() >= MIN_BREW_WEIGHT)
        {
            // calculate the estimated target brew weight and seconds left
            Mode_Brew::estBrewWeight = Scale::getWeight() / Mode_Brew::brewSeconds * Presets::getPreset()->brewDuration;
            Mode_Brew::estBrewSecondsLeft = round(Mode_Brew::brewSeconds / Scale::getWeight() * Mode_Brew::targetBrewWeight - Mode_Brew::brewSeconds);
            if (Mode_Brew::estBrewSecondsLeft <= 0)
            {
                if (Presets::getPreset()->autoPump == true)
                {
                    // stop the brew pump
                    Ir::send();
#ifdef SERIAL_DEBUG
                    Serial.print(String(Mode_Brew::brewSeconds));
                    Serial.print("  ");
                    Serial.print(String(Scale::getWeight()));
                    Serial.print("  ");
                    Serial.println("Mode_Brew::stop pump");
#endif
                }

                // check if we need to stop the timer
                if (Presets::getPreset()->stopTimer == stopTimer_pump)
                {
                    Mode_Brew::setStage(brew_stage_stopping);
                }
                else if (Presets::getPreset()->stopTimer == stopTimer_last_drop)
                {
                    Mode_Brew::setStage(brew_stage_stopping);
                }
            }

            // when the estimated brew seconds are more than zero and
            // are equal or less than the estimated brew seconds left warning,
            // reduce the estimated brew seconds left warning and beep accordingly
            // TODO: check why this is faster than ideal...
            //       most likely due to accelarated weight increase
            if (Presets::getPreset()->autoPump == false && Mode_Brew::estBrewSecondsLeft >= 0 && Mode_Brew::estBrewSecondsLeft < Mode_Brew::estBrewSecondsLeftWarning)
            {
                // count down the warnings...
                Mode_Brew::estBrewSecondsLeftWarning--;
                if (Mode_Brew::estBrewSecondsLeftWarning > 0)
                {
                    // warn the user that we approach the end
                    Buzzer::on(350);
                }
                else
                {
                    // notify the user to stop the brew pump!
                    Buzzer::on(1000);
                }
            }
        }
        render = true;
    }
    else if (Mode_Brew::hasRenderBuffered())
    {
        render = true;
    }

    // handle stopTimer_last_drop
    if (Mode_Brew::stage == brew_stage_stopping && Presets::getPreset()->stopTimer == stopTimer_last_drop)
    {
        // TODO: specify a delta for weight of drop. maybe use the FIRST_DROP_WEIGHT and rename
        if (Scale::hasWeightChanged)
        {
            // refresh the time the last drop fell
            Mode_Brew::timeAtLastDrop = millis();
        }
        else if (millis() - Mode_Brew::timeAtLastDrop >= TIME_SINCE_LAST_DROP_TO_STOP)
        {
            // don't count the "time-out", since no drop has fell in that period
            Mode_Brew::brewSeconds -= round(TIME_SINCE_LAST_DROP_TO_STOP / 1000);
            // end the brew
            Mode_Brew::setStage(brew_stage_done);
        }
    }

    if (render)
    {
        Mode_Brew::render();
    }
};

void Mode_Brew::render()
{
    if (Scale::hasWeightChanged)
    {
        // while brewing, always show the weight
        Mode_Brew::tryRenderNow("Brew " + Scale::getFormattedWeight(), 0, 0);
    }
    else
    {
        Mode_Brew::tryRenderBuffered();
    }

    if (Mode_Brew::stage == brew_stage_waiting)
    {
        if (Presets::getPreset()->startTimer == startTimer_pump && Presets::getPreset()->autoPump == false)
        {
            Lcd::print("Start pump and", 0, 0, clearLcd_row);
            Lcd::print("press OK...", 0, 1, clearLcd_row);
        }
        else if (Presets::getPreset()->startTimer == startTimer_first_drop)
        {
            Lcd::print("Waiting for drop", 0, 1, clearLcd_row);
        }
    }
    else if (Mode_Brew::stage == brew_stage_in_progress)
    {

        String postMsg;
        if (Presets::getPreset()->autoPump == false && Mode_Brew::estBrewSecondsLeft <= Mode_Brew::estBrewSecondsLeftWarning)
        {
            // show the seconds remaining until the brew pump needs to stop manually
            postMsg = "..." + String(Mode_Brew::estBrewSecondsLeftWarning);
        }
        else
        {
            // show the brew speed in relation to the wanted target
            float estBrewWeightDelta = Mode_Brew::estBrewWeight - Mode_Brew::targetBrewWeight;
            if (estBrewWeightDelta > GOOD_BREW_WEIGHT_DELTA)
            {
                postMsg = "fast";
            }
            else if (estBrewWeightDelta < GOOD_BREW_WEIGHT_DELTA)
            {
                postMsg = "slow";
            }
            else
            {
                postMsg = "good";
            }
        }

        Lcd::print(Mode_Brew::getFormattedBrewSeconds() + " - " + postMsg, 0, 1, clearLcd_row);
    }
    else if (Mode_Brew::stage == brew_stage_stopping)
    {
        Lcd::print(Mode_Brew::getFormattedBrewSeconds() + " - stop", 0, 1, clearLcd_row);
    }
    else if (Mode_Brew::stage == brew_stage_done)
    {
        Lcd::print(Mode_Brew::getFormattedBrewSeconds() + " - done!", 0, 1, clearLcd_row);
    }
};

String Mode_Brew::getFormattedBrewSeconds()
{
    float formattedSeconds = Mode_Brew::brewSeconds;

    // pad prefix with spaces
    const int totalWidth = Utils::numberLength(BREW_SECONDS_DECIMALS + BREW_SECONDS_MAX);
    // +1 for the null terminator
    char buffer[totalWidth + 1];
    dtostrf(formattedSeconds, totalWidth, BREW_SECONDS_DECIMALS, buffer);

    // Find the position of the decimal point
    char *decimalPoint = strchr(buffer, '.');

    // If decimal point is found, move characters to the right to add leading zeros
    if (decimalPoint != NULL)
    {
        int zerosToAdd = totalWidth - (decimalPoint - buffer);
        memmove(buffer + zerosToAdd, buffer, strlen(buffer) + 1);
        memset(buffer, ' ', zerosToAdd);
    }

    return String(buffer) + " " + "s.";
};

void Mode_Brew::tare(button_states button_state) {}

void Mode_Brew::up(button_states button_state)
{
}

void Mode_Brew::down(button_states button_state)
{
}

void Mode_Brew::ok(button_states button_state)
{
    if (button_state == button_pressed)
    {
        if (Mode_Brew::stage == brew_stage_waiting && Presets::getPreset()->startTimer == startTimer_pump && Presets::getPreset()->autoPump == false)
        {
            Mode_Brew::setStage(brew_stage_in_progress);
        }
        else if (Mode_Brew::stage == brew_stage_stopping)
        {
            Mode_Brew::setStage(brew_stage_done);
        }
        else if (Mode_Brew::stage == brew_stage_done)
        {
            Modes_Controller::setMode(modes_scale);
        }
    }
}

void Mode_Brew::cancel(button_states button_state)
{
    if (button_state == button_pressed)
    {
        if (Mode_Brew::stage == brew_stage_in_progress)
        {
            // stop the brew
            Mode_Brew::setStage(brew_stage_stopping);
        }
        else
        {
            Modes_Controller::setMode(modes_scale);
        }
    }
}

void Mode_Brew::coffee(button_states button_state)
{
    Mode_Brew::ok(button_state);
}
