/*! \file
    \brief The definition of tetengo2::gui::message::window_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_WINDOWOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_WINDOWOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class for a window observer set.
    */
    class window_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of resizing.
        */
        typedef void resizing_type();

        //! The signal type of resizing.
        typedef boost::signals2::signal<resizing_type> resizing_signal_type;

        /*!
            \brief The observer type of resized
        */
        typedef void resized_type();

        //! The signal type of resizing.
        typedef boost::signals2::signal<resized_type> resized_signal_type;

        /*!
            \brief The observer type of closing.

            \param cancel Set true to cancel the window closing.
        */
        typedef void closing_type(bool& cancel);

        //! The signal type of closing.
        typedef boost::signals2::signal<closing_type> closing_signal_type;

        /*!
            \brief The observer type of destroyed.
        */
        typedef void destroyed_type();

        //! The signal type of destroyed.
        typedef boost::signals2::signal<destroyed_type> destroyed_signal_type;


        // functions

        /*!
            \brief Returns the observer called when a window is resizing.

            \return The observer called when a window is resizing.
        */
        const resizing_signal_type& resizing()
        const
        {
            return m_resizing;
        }

        /*!
            \brief Returns the observer called when a window is resizing.

            \return The observer called when a window is resizing.
        */
        resizing_signal_type& resizing()
        {
            return m_resizing;
        }

        /*!
            \brief Returns the observer called when a window is resized.

            \return The observer called when a window is resized.
        */
        const resized_signal_type& resized()
        const
        {
            return m_resized;
        }

        /*!
            \brief Returns the observer called when a window is resized.

            \return The observer called when a window is resized.
        */
        resized_signal_type& resized()
        {
            return m_resized;
        }

        /*!
            \brief Returns the observer called when a window is closing.

            \return The observer called when a window is closing.
        */
        const closing_signal_type& closing()
        const
        {
            return m_closing;
        }

        /*!
            \brief Returns the observer called when a window is closing.

            \return The observer called when a window is closing.
        */
        closing_signal_type& closing()
        {
            return m_closing;
        }

        /*!
            \brief Returns the observer called when a window is destroyed.

            \return The observer called when a window is destroyed.
        */
        const destroyed_signal_type& destroyed()
        const
        {
            return m_destroyed;
        }

        /*!
            \brief Returns the observer called when a window is destroyed.

            \return The observer called when a window is destroyed.
        */
        destroyed_signal_type& destroyed()
        {
            return m_destroyed;
        }


    private:
        // variables

        resizing_signal_type m_resizing;

        resized_signal_type m_resized;

        closing_signal_type m_closing;

        destroyed_signal_type m_destroyed;


    };


}}}


#endif
