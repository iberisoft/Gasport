#include <Arduino.h>
#include "OledDisplay.h"

void OledDisplay::setup()
{
    m_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    m_display.setTextColor(WHITE);
    updateDisplay();
}

void OledDisplay::showValue(double value, String unit, bool logging)
{
    if (value >= 1 || value == 0)
    {
        m_valueTexts[0] = String(value, 2);
    }
    else
    {
        int exp = (int)log10(value) - 1;
        m_valueTexts[0] = String(value / pow(10, exp), 2) + "x10" + String(exp);
    }
    m_valueTexts[1] = unit;
    m_logIndicatorMode = logging;
    updateDisplay();
}

void OledDisplay::updateDisplay()
{
    m_display.clearDisplay();

    m_display.setTextSize(2, 3);
    displayText(m_valueTexts[0], 50, 0);
    m_display.setTextSize(1, 1);
    displayText(m_valueTexts[1], 100, 100);
    if (m_logIndicatorMode)
    {
        displayLogIndicator();
    }

    m_display.display();
}

const int logIndicatorSize = 8;
const uint8_t logIndicatorBitmap[] =
    {
        0b11000000,
        0b11110000,
        0b11111100,
        0b11111111,
        0b11111111,
        0b11111100,
        0b11110000,
        0b11000000};

void OledDisplay::displayLogIndicator()
{
    m_display.drawBitmap(0, m_display.height() - logIndicatorSize, logIndicatorBitmap, logIndicatorSize, logIndicatorSize, WHITE);
}

void OledDisplay::displayText(String text, int xAlignment, int yAlignment)
{
    int16_t x, y;
    uint16_t textWidth, textHeight;
    m_display.getTextBounds(text.c_str(), 0, 0, &x, &y, &textWidth, &textHeight);
    m_display.setCursor((m_display.width() - textWidth) * xAlignment / 100, (m_display.height() - textHeight) * yAlignment / 100);
    m_display.print(text);
}
