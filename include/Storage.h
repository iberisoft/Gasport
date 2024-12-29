#include <SD.h>

class Storage
{
    String m_rootPath;
    SPIClass m_spi;

public:
    Storage(String rootPath) { m_rootPath = rootPath; }
    void setup();
    void traceLog(String fileName, uint64_t timestamp, String text);
    void printFileNames(Stream &outputStream);
    void readFile(String fileName, Stream &outputStream);
    void removeFile(String fileName);

private:
    static String timestampToString(uint64_t timestamp);
    static String hmsToString(int value);
};
