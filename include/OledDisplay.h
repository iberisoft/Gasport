#include <Adafruit_SSD1306.h>

class OledDisplay
{
    Adafruit_SSD1306 m_display;
    String m_valueTexts[2];
    bool m_logIndicatorMode;

public:
    OledDisplay(int width, int height) : m_display(width, height) {}
    void setup();
    void showValue(double value, String unit, bool logging);

private:
    void updateDisplay();
    void displayLogIndicator();
    void displayText(String text, int xAlignment, int yAlignment);
};
