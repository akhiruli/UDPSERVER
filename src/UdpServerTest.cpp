#include <UdpServer.h>

int main(){
   UdpServer *server = new UdpServer();
   
   EventImpl *ev_obj = EventImpl::getInstance();
   if(ev_obj && ev_obj->initEv())
   {
      server->run();
      ev_obj->dispatchEvloop();
   }

   return 0;
}
