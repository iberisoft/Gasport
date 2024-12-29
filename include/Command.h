struct Command
{
    String name;
    void (*handler)(String param, Stream &stream);
};
