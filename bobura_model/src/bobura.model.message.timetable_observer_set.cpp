/*! \file
    \brief The definition of bobura::model::message::timetable_observer_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/model/message/timetable_observer_set.h>


namespace bobura { namespace model { namespace message
{
    class timetable_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using changed_type = timetable_observer_set::changed_type;

        using changed_signal_type = timetable_observer_set::changed_signal_type;


        // functions

        const changed_signal_type& changed()
        const
        {
            return m_changed;
        }

        changed_signal_type& changed()
        {
            return m_changed;
        }


    private:
        // variables

        changed_signal_type m_changed;


    };


    timetable_observer_set::timetable_observer_set()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    timetable_observer_set::~timetable_observer_set()
    TETENGO2_STDALT_NOEXCEPT
    {}

    const timetable_observer_set::changed_signal_type& timetable_observer_set::changed()
    const
    {
        return m_p_impl->changed();
    }

    timetable_observer_set::changed_signal_type& timetable_observer_set::changed()
    {
        return m_p_impl->changed();
    }


}}}
