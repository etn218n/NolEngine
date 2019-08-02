//#pragma once
//
//#include "NolAPI.h"
//#include "Event.h"
//
//namespace Nol
//{
//    class NOL_API KeyEvent : public Event
//    {
//    protected:
//        int _keycode;
//
//    public:
//        inline int GetKeyCode() const { return _keycode; }
//        virtual int GetCategoryFlags() const override
//        {
//            return EventCategory::EventCategoryInput | EventCategory::EventCategoryKeyboard;
//        }
//
//    protected:
//        KeyEvent(int keycode) : _keycode(keycode) {}
//    };
//
//
//    class NOL_API KeyPressedEvent : public KeyEvent
//    {
//    private:
//        int _repeatCount;
//
//    public:
//        KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), _repeatCount(repeatCount) {}
//
//        inline static EventType GetStaticEventType()   { return EventType::KeyPressed; }
//        inline EventType GetEventType() const override { return EventType::KeyPressed; }
//    };
//
//
//    class NOL_API KeyReleasedEvent : public KeyEvent
//    {
//    public:
//        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
//
//        inline static EventType GetStaticEventType()   { return EventType::KeyReleased; }
//        inline EventType GetEventType() const override { return EventType::KeyReleased; }
//    };
//}