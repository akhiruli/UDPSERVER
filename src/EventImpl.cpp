//! @file   EventImpl.h 
//! @brief  
//! @author Akhirul Islam
//! 
#include <EventImpl.h>
#include <mutex>


static std::mutex g_mutex;
EventImpl* EventImpl::m_pevObj = NULL;

EventImpl::EventImpl(): m_pevbase(NULL) 
{
}

EventImpl::~EventImpl()
{
   if(m_pevbase)
      event_base_free(m_pevbase);
}

EventImpl* EventImpl::getInstance()
{
   if(!m_pevObj)
   {
      std::lock_guard<std::mutex> lock(g_mutex);
      if(!m_pevObj)
         m_pevObj = new EventImpl();
   }
   return m_pevObj;
}

bool EventImpl::initEv()
{
   m_pevbase = event_base_new();
   if(m_pevbase)
      return true;
   else
      return false;
}

void EventImpl::dispatchEvloop()
{
   event_base_dispatch(m_pevbase);
}

void EventImpl::attachFdtoEv(struct event *ev, int fd, event_callback_fn cb, void *cookie)
{
   event_assign(ev, m_pevbase, fd, EV_READ|EV_PERSIST, cb, cookie);
}

void EventImpl::addToEv(struct event *ev)
{
   event_add(ev, NULL);
}
/*
struct event* EventImpl::getNewPersistentEvent(event_callback_fn cb, void *cookie)
{
   struct event *ev = event_new(m_pevbase, -1, EV_READ|EV_PERSIST, cb, cookie);
   return ev;
}
*/
void EventImpl::addToEv(struct event *ev, struct timeval *t_intvl)
{
   event_add(ev, t_intvl);
}
