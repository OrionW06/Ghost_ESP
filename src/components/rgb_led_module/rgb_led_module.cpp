#include "rgb_led_module.h"
#include <Arduino.h>
#include <core/system_manager.h>

void RGBLedModule::init() {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    Rainbow(1, 4);
    fadeOutAllPins(400);
}

void RGBLedModule::breatheLED(int ledPin, int breatheTime, bool FadeOut)
{
    int fadeAmount = 5; // Amount of brightness change per step, adjust for different breathing speeds
    int wait = breatheTime / ((255 / fadeAmount) * 2); // Calculate wait time to fit the breathe cycle into the given total time

    if (FadeOut)
    {
        // Fade out (brightness increases for inverted logic)
        for (int brightness = 0; brightness <= 255; brightness += fadeAmount) {
            analogWrite(ledPin, brightness);
            delay(wait);
        }
    }
    else
    {
        // Fade in (brightness decreases for inverted logic)
        for (int brightness = 255; brightness >= 0; brightness -= fadeAmount) {
            analogWrite(ledPin, brightness);
            delay(wait);
        }

        // Fade out (brightness increases for inverted logic)
        for (int brightness = 0; brightness <= 255; brightness += fadeAmount) {
            analogWrite(ledPin, brightness);
            delay(wait);
        }
    }
}


void RGBLedModule::fadeOutAllPins(int fadeTime)
{
    int fadeAmount = 5; // Amount of brightness change per step, adjust for different fading speeds
    int wait = fadeTime / (255 / fadeAmount); // Calculate wait time to fit the fade cycle into the given total time

    // Fade out all pins (brightness increases for inverted logic)
    for (int brightness = 0; brightness <= 255; brightness += fadeAmount) {
        analogWrite(redPin, brightness);
        analogWrite(greenPin, brightness);
        analogWrite(bluePin, brightness);
        delay(wait);
    }
}

void RGBLedModule::Song()
{
    
}

void RGBLedModule::Rainbow(int strength, int stepDelay) 
{
if (SystemManager::getInstance().Settings.getRGBMode() == FSettings::RGBMode::Rainbow)
{
    float brightnessFactor = constrain(brightnessFactor, 0.0, 1.0);

    // Ensure strength is between 0 and 255
    int maxStrength = static_cast<int>(255 * brightnessFactor);

    // Color transitions
    for (int g = 0; g <= maxStrength; g += 5) {
        analogWrite(redPin, maxStrength);
        analogWrite(greenPin, g);
        analogWrite(bluePin, 0);
        delay(stepDelay);
    }

    for (int r = maxStrength; r >= 0; r -= 5) {
        analogWrite(redPin, r);
        analogWrite(greenPin, maxStrength);
        analogWrite(bluePin, 0);
        delay(stepDelay);
    }

    for (int b = 0; b <= maxStrength; b += 5) {
        analogWrite(redPin, 0);
        analogWrite(greenPin, maxStrength);
        analogWrite(bluePin, b);
        delay(stepDelay);
    }

    for (int g = maxStrength; g >= 0; g -= 5) {
        analogWrite(redPin, 0);
        analogWrite(greenPin, g);
        analogWrite(bluePin, maxStrength);
        delay(stepDelay);
    }

    for (int r = 0; r <= maxStrength; r += 5) {
        analogWrite(redPin, r);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, maxStrength);
        delay(stepDelay);
    }

    for (int b = maxStrength; b >= 0; b -= 5) {
        analogWrite(redPin, maxStrength);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, b);
        delay(stepDelay);
    }

    if (SystemManager::getInstance().Settings.getRGBMode() != FSettings::RGBMode::Rainbow)
    {
        fadeOutAllPins(500);
    }
}
}

void RGBLedModule::setColor(int red, int green, int blue) {

    int pwmRed = red;
    int pwmGreen = green;
    int pwmBlue = blue;

    digitalWrite(redPin, pwmRed);
    digitalWrite(greenPin, pwmGreen);
    digitalWrite(bluePin, pwmBlue);
}