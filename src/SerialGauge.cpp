#include <Arduino.h>
#include "SerialGauge.h"
#include "globals.h"

void SerialGauge::setup(int baud, int8_t rxPin, int8_t txPin)
{
    m_serial.begin(baud, SERIAL_8N1, rxPin, txPin);
    m_serial.setTimeout(100);
}

void SerialGauge::discardInput()
{
    while (m_serial.available())
    {
        m_serial.read();
    }
}

String SerialGauge::write(String command)
{
    if (verboseMode)
    {
        Serial.print("--> UART #");
        Serial.print(m_uart);
        Serial.print(": ");
        Serial.println(command);
    }

    command = command + "\r";
    m_serial.write(command.c_str());
    String response = m_serial.readStringUntil('\r');

    if (verboseMode)
    {
        Serial.print("<-- UART #");
        Serial.print(m_uart);
        Serial.print(": ");
        Serial.println(response);
    }

    return response;
}
