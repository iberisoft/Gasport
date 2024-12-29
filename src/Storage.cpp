#include <Arduino.h>
#include "Storage.h"
#include "globals.h"
#include "deviceConfig.h"

void Storage::setup()
{
    m_spi.begin(sdClkPin, sdMisoPin, sdMosiPin, sdCsPin);

    if (SD.begin(sdCsPin, m_spi))
    {
        Serial.println("SD card mounted");
    }
    else
    {
        Serial.println("SD card failed to mount");
    }
}

void Storage::traceLog(String fileName, uint64_t timestamp, String text)
{
    File file = SD.open(m_rootPath + fileName, FILE_APPEND);
    if (file)
    {
        String prefix = timestampToString(timestamp) + ",";
        file.print(prefix);
        file.println(text);
        file.close();

        if (verboseMode)
        {
            Serial.print(prefix);
            Serial.println(text);
        }
    }
}

String Storage::timestampToString(uint64_t timestamp)
{
    int seconds = timestamp / 1000;
    int minutes = seconds / 60;
    int hours = minutes / 60;
    return hmsToString(hours) + ":" + hmsToString(minutes % 60) + ":" + hmsToString(seconds % 60);
}

String Storage::hmsToString(int value)
{
    String text(value);
    if (value < 10)
    {
        text = "0" + text;
    }
    return text;
}

void Storage::printFileNames(Stream &outputStream)
{
    File dir = SD.open(m_rootPath);
    if (dir)
    {
        while (true)
        {
            File file = dir.openNextFile();
            if (file)
            {
                if (!file.isDirectory())
                {
                    outputStream.println(file.name());
                }
                file.close();
            }
            else
            {
                break;
            }
        }
        dir.close();
    }
}

void Storage::readFile(String fileName, Stream &outputStream)
{
    File file = SD.open(m_rootPath + fileName);
    if (file)
    {
        if (!file.isDirectory())
        {
            while (file.available())
            {
                outputStream.write(file.read());
            }
        }
        file.close();
    }
}

void Storage::removeFile(String fileName)
{
    File file = SD.open(m_rootPath + fileName);
    if (file)
    {
        if (!file.isDirectory())
        {
            SD.remove(file.path());
        }
        file.close();
    }
}
