#include<UdpServer.h>

void UdpServer::run()                                                                              
{                                                                                                     
   int fd = prepareUdpSvr();
   if(fd < 0)
   {    
      printf("UdpServer::run: failed to start the server\n");
      return;
   }    
        
   EventImpl *ev_obj = EventImpl::getInstance();                                                      
   ev_obj->attachFdtoEv(&m_evread, fd, on_read, this);                                                
   ev_obj->addToEv(&m_evread);
} 

int UdpServer::prepareUdpSvr()
{       
   int listen_fd = -1;
   struct sockaddr_in listen_addr;                                                                    
   int reuseaddr_on = 1;          
        
   /* Create our listening socket. This is largely boiler plate                                       
    * code that I'll abstract away in the future. */
   listen_fd = socket(PF_INET, SOCK_DGRAM, 0);
   if (listen_fd < 0)                                                                                 
   {                                                                                                  
      printf("UdpServer::prepareUdpSvr: listen failed\n");
      return listen_fd;
   }

   if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on,
      sizeof(reuseaddr_on)) == -1)
   {
      printf("UdpServer::prepareUdpSvr: setsockopt failed\n");
      return -1;
   }

   memset(&listen_addr, 0, sizeof(listen_addr));
   listen_addr.sin_family = AF_INET;
   listen_addr.sin_addr.s_addr = INADDR_ANY;
   listen_addr.sin_port = htons(9000);

   if (bind(listen_fd, (struct sockaddr *)&listen_addr,
      sizeof(listen_addr)) < 0)
   {
      printf("UdpServer::prepareUdpSvr: bind failed\n");
      return -1;
   }

   /* Set the socket to non-blocking, this is essential in event
    * based programming with libevent. */
   if (setnonblock(listen_fd) < 0)
   {
      printf("UdpServer::prepareUdpSvr: failed to set server socket to non-blocking\n");
      return -1;
   }

   return listen_fd;
}

int UdpServer::setnonblock(int fd)
{
   int flags;

   flags = fcntl(fd, F_GETFL);
   if (flags < 0)
      return flags;
   flags |= O_NONBLOCK;
   if (fcntl(fd, F_SETFL, flags) < 0)
      return -1;

   return 0;
}

void UdpServer::on_read(int fd, short ev, void *arg)
{
   int len = -1;
   // UdpServer *service = reinterpret_cast<UdpServer *>(arg); // we can retrieve the cookie
   Byte buffer[1024] = {'\0'};
   struct sockaddr_storage serverStorage;
   socklen_t addr_size;
   addr_size = sizeof serverStorage;

    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on serverStorage variable */
   len = recvfrom(fd, buffer, 1024, 0, (struct sockaddr *)&serverStorage, &addr_size);
   printf("message from client: %s\n", buffer);
   if(len > 0)
   {
    /*Send uppercase message back to client, using serverStorage as the address*/
      sendto(fd, buffer, len, 0,(struct sockaddr *)&serverStorage,addr_size);
   }
}


