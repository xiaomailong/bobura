/*! \file
    \brief The definition of tetengo2::gui::win32::quit_message_loop.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_QUITMESSAGELOOP_H)
#define TETENGO2_GUI_WIN32_QUITMESSAGELOOP_H

#include <functional>


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a message loop.

        \tparam MessageLoopDetails The detail implementationf of a message
                                   loop.
    */
    template <typename MessageLoopDetails>
    class quit_message_loop : public std::unary_function<int, void>
    {
    public:
        // types

        //! The detail implementation of a message loop.
        typedef MessageLoopDetails message_loop_details_type;


        // functions

        /*!
            \brief Quits the message loop.

            \param exit_code An exit status code.
        */
        void operator()(const int exit_code)
        const
        {
            message_loop_details_type::break_loop(exit_code);
        }


    };


}}}

#endif
