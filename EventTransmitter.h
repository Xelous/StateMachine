//#pragma once
//
//#include "EventSystem.h"
//
//namespace xelous
//{
//    class Event;    
//
//    class EventTransmitter
//    {
//    public:
//        inline void EnqueueEvent(const Event* pEvent)
//        {
//            auto eventSystem = EventSystem::Get();
//            if (eventSystem)
//            {
//                eventSystem->EnqueueEvent(pEvent);
//            }
//        }
//    };
//
//}