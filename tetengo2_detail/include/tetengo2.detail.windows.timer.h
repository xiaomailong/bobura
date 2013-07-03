/*! \file
    \brief The definition of tetengo2::detail::windows::timer.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_TIMER_H)
#define TETENGO2_DETAIL_WINDOWS_TIMER_H

#include <chrono>
#include <functional>

#include <boost/noncopyable.hpp>

#include "tetengo2.utility.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a timer.
    */
    class timer : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a timer.

            \tparam Widget A widget type.

            \param widget    A widget.
            \param procecure A procedure called by this timer.
            \param interval  An interval.
        */
        template <typename Widget>
        explicit timer(const Widget& widget, std::function<void ()> procedure, std::chrono::milliseconds interval)
        {
            suppress_unused_variable_warning(widget, procedure, interval);
        }


    };


}}}


#endif
