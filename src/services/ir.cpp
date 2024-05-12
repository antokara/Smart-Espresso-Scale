#include "services/ir.h"
#include "services/device.h"
#include "TinyIRSender.hpp"

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief Ifrared
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */
uint8_t Ir::sendAddress = 0x02;
uint8_t Ir::sendCommand = 0x34;
uint8_t Ir::sendRepeats = 1;

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Ir::setup()
{
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Ir::loop()
{
}

void Ir::send()
{
    sendNEC(IR_SEND_PIN, Ir::sendAddress, Ir::sendCommand, Ir::sendRepeats);
}
