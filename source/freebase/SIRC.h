class SIRC
{
  private:
    hostent *hostEnt;

    int irc;

    sockaddr_in addr;

    WSADATA data;

  public:
    ~SIRC();
    SIRC();

    int Connect(char *host, unsigned short port);
    int Send(char *data, ...);
    int Receive(char *data, int length);

    void Log(char *fileName, char *data, ...);
    void Quit(char *message);
};
