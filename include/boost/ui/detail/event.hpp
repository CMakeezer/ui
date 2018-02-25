// Copyright (c) 2018 Kolya Kosenko

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#include <boost/move/utility.hpp>
#else
#include <boost/bind.hpp>
#endif

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#define BOOST_UI_DETAIL_HANDLER(handler, cls) \
    template <class F, class ...Args> \
    cls& on_##handler(F&& f, Args&&... args) \
        { on_##handler##_raw(std::bind(boost::forward<F>(f), boost::forward<Args>(args)...)); return *this; } \

#define BOOST_UI_DETAIL_HANDLER_EVENT(handler, cls, event) \
    template <class F, class ...Args> \
    cls& on_##handler(F&& f, Args&&... args) \
        { on_##handler##_raw(std::bind(boost::forward<F>(f), boost::forward<Args>(args)..., std::placeholders::_1)); return *this; } \

#else // defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#define BOOST_UI_DETAIL_HANDLER(handler, cls) \
    cls& on_##handler(const boost::function<void()>& handler) \
        { on_##handler##_raw(handler); return *this; } \
    template <class F, class Arg1> \
    cls& on_##handler(F f, Arg1 a1) \
        { on_##handler##_raw(boost::bind(f, a1)); return *this; } \
    template <class F, class Arg1, class Arg2> \
    cls& on_##handler(F f, Arg1 a1, Arg2 a2) \
        { on_##handler##_raw(boost::bind(f, a1, a2)); return *this; } \

#define BOOST_UI_DETAIL_HANDLER_EVENT(handler, cls, event) \
    cls& on_##handler(const boost::function<void(event&)>& handler) \
        { on_##handler##_raw(handler); return *this; } \
    template <class F, class Arg1> \
    cls& on_##handler(F f, Arg1 a1) \
        { on_##handler##_raw(boost::bind(f, a1, _1)); return *this; } \
    template <class F, class Arg1, class Arg2> \
    cls& on_##handler(F f, Arg1 a1, Arg2 a2) \
        { on_##handler##_raw(boost::bind(f, a1, a2, _1)); return *this; } \

#endif
