/*! \file
    \brief The definition of tetengo2::gui::message::focus_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_FOCUSOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_FOCUSOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class for a focus observer set.
    */
    class focus_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of got-focus.
        */
        typedef void got_focus_type();

        //! The signal type of got-focus.
        typedef boost::signals2::signal<got_focus_type> got_focus_signal_type;

        /*!
            \brief The observer type of lost-focus.
        */
        typedef void lost_focus_type();

        //! The signal type of lost-focus.
        typedef
            boost::signals2::signal<lost_focus_type> lost_focus_signal_type;


        // functions

        /*!
            \brief Returns the observer called when a widget got a focus.

            \return The observer called when a widget got a focus.
        */
        const got_focus_signal_type& got_focus()
        const
        {
            return m_got_focus;
        }

        /*!
            \brief Returns the observer called when a widget got a focus.

            \return The observer called when a widget got a focus.
        */
        got_focus_signal_type& got_focus()
        {
            return m_got_focus;
        }

        /*!
            \brief Returns the observer called when a widget lost a focus.

            \return The observer called when a widget lost a focus.
        */
        const lost_focus_signal_type& lost_focus()
        const
        {
            return m_lost_focus;
        }

        /*!
            \brief Returns the observer called when a widget lost a focus.

            \return The observer called when a widget lost a focus.
        */
        lost_focus_signal_type& lost_focus()
        {
            return m_lost_focus;
        }


    private:
        // variables

        got_focus_signal_type m_got_focus;

        lost_focus_signal_type m_lost_focus;


    };


}}}


#endif