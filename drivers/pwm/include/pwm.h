/*
MIT License

Copyright (c) <2019-2024> <Matthew Eshleman - https://covemountainsoftware.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @brief public header for the PWM driver.
 *        The driver API is fully synchronous.
 */
#ifndef PWM_H
#define PWM_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief initializes the driver.
 * @return true - initialization completed successfully.
 *         false - some error.
 */
bool PwmInit();

/**
 * @brief  Turn off the PWM.
 * @return true -  completed successfully
 *         false - some error.
 */
bool PwmOff();

/**
 * @brief  Turn on the PWM.
 * @arg percent: [0.0 .. 1.0], percentage
 * @return true - completed successfully
 *         false - some error.
 */
bool PwmOn(float percent);

/**
 * @brief PwmFactoryTest executes a self test. Will fail if PWM is on.
 * @return The device ID read during the factory test.
 *         Return value is 0xFFFF if test failed.
 */
uint16_t PwmFactoryTest();

#ifdef __cplusplus
}
#endif

#endif //PWM_H
