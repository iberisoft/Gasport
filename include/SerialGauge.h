class SerialGauge
{
    HardwareSerial m_serial;
    int m_uart;

public:
    SerialGauge(uint8_t uart) : m_serial{uart} { m_uart = uart; }
    void setup(int baud, int8_t rxPin, int8_t txPin);
    void discardInput();
    String write(String command);
};
