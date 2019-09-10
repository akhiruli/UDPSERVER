#ifndef _UDP_SERVER_H
#define _UDP_SERVER_H
#include <EventImpl.h>
//#include <ioctl.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char  Byte;

class UdpServer {
   public:
      void run();
      int prepareUdpSvr();
      int setnonblock(int fd);
      static void on_read(int fd, short ev, void *arg);
   private:
      struct event  m_evread;
}; 
#endif
