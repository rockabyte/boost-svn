#ifndef BOOST_CHECKED_DELETE_HPP_INCLUDED
#define BOOST_CHECKED_DELETE_HPP_INCLUDED

#if _MSC_VER >= 1020
#pragma once
#endif

//
//  boost/checked_delete.hpp
//
//  Copyright (c) 1999, 2000, 2001, 2002 boost.org
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

namespace boost
{

// verify that types are complete for increased safety

template< typename T > inline void checked_delete(T * x)
{
    typedef char type_must_be_complete[sizeof(T)];
    delete x;
}

template< typename T > inline void checked_array_delete(T * x)
{
    typedef char type_must_be_complete[sizeof(T)];
    delete [] x;
}

template<class T> struct checked_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x)
    {
        checked_delete(x);
    }
};

template<class T> struct checked_array_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x)
    {
        checked_array_delete(x);
    }
};

} // namespace boost

#endif  // #ifndef BOOST_CHECKED_DELETE_HPP_INCLUDED
