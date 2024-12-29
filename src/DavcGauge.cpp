#include <Arduino.h>
#include "DavcGauge.h"

String DavcGauge::m_pressureUnits[3] = {"Torr", "kPa", "mbar"};

void DavcGauge::setPressureUnit(String pressureUnit)
{
    int i = findPressureUnit(pressureUnit);
    if (i >= 0)
    {
        m_pressureUnit = m_pressureUnits[i];
        write("U" + String(i + 1));
    }
}

int DavcGauge::findPressureUnit(String pressureUnit)
{
    for (int i = 0; i < 3; ++i)
    {
        if (m_pressureUnits[i].equalsIgnoreCase(pressureUnit))
        {
            return i;
        }
    }
    return -1;
}

double DavcGauge::readValue()
{
    discardInput();

    String data = write("P");
    data.trim();
    int i = data.indexOf(' ');
    int j = data.lastIndexOf(' ');
    data = data.substring(i + 1, j);
    double value = data.toDouble();
    if (m_pressureUnit == "kPa")
    {
        value /= 1000;
    }
    return value;
}
