#include "SerialGauge.h"

class DavcGauge : SerialGauge
{
    String m_pressureUnit = "Torr";
    static String m_pressureUnits[];

public:
    DavcGauge(uint8_t uart) : SerialGauge(uart) {}
    void setup(int8_t rxPin, int8_t txPin) { SerialGauge::setup(9600, rxPin, txPin); }
    String getPressureUnit() { return m_pressureUnit; }
    void setPressureUnit(String pressureUnit);
    double readValue();

private:
    static int findPressureUnit(String pressureUnit);
};
