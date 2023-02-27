#include <cstdarg>
#include <fstream>
#include <windows.h>

#include "SIRC.h"

using namespace std;

int SIRC::Connect(char *host, unsigned short port)
{
  hostEnt = gethostbyname(host);

  addr.sin_addr.s_addr = *(unsigned int *)hostEnt->h_addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);

  return connect(irc, (sockaddr *)&addr, sizeof(sockaddr_in));
}

int SIRC::Send(char *data, ...)
{
  char *buf = new char[1024];

  memset(buf, 0, 1024);

  va_list list;
  va_start(list, data);

  _vsnprintf(buf, 1023, data, list);

  va_end(list);

  int ret = send(irc, buf, strlen(buf), 0);

  delete buf;
  delete list;

  return ret;
}

int SIRC::Receive(char *data, int length)
{
  return recv(irc, data, length, 0);
}

SIRC::~SIRC()
{
  closesocket(irc);

  WSACleanup();
}

SIRC::SIRC()
{
  WSAStartup(MAKEWORD(2, 0), &data);

  irc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void SIRC::Log(char *fileName, char *data, ...)
{
  char *buf = new char[1024];

  memset(buf, 0, 1024);

  va_list list;
  va_start(list, data);

  _vsnprintf(buf, 1023, data, list);

  va_end(list);

  ofstream *file = new ofstream();

  file->open(fileName, ios::out | ios::app | ios::binary);
  file->write(buf, strlen(buf));
  file->close();

  delete buf;
  delete file;
}

void SIRC::Quit(char *message)
{
  char *buf = new char[1024];

  memset(buf, 0, 1024);

  _snprintf(buf, 1023, "QUIT :%s\r\n", message);

  send(irc, buf, strlen(buf), 0);

  delete buf;
}