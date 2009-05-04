/*! \file
    \brief The definition of tetengo2::gui::win32::dialog_message_loop.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DIALOGMESSAGELOOP_H)
#define TETENGO2_GUI_WIN32_DIALOGMESSAGELOOP_H

#include <cstddef>
#include <sstream>
#include <stdexcept>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.generator.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The generator class for a message loop for dialogs for Win32
               platforms.
    */
    class dialog_message_loop : public tetengo2::generator<int>
    {
    public:
        // functions

        /*!
            \brief Runs the message loop.

            \return The exit status code.

            \throw std::runtime_error When an error occurred in the message
                                      loop.
        */
        int operator()()
        const
        {
            ::MSG message;
            for (;;)
            {
                const ::BOOL result = ::GetMessageW(&message, NULL, 0, 0);
                if      (result == 0)
                {
                    return static_cast<int>(message.wParam);
                }
                else if (result == -1)
                {
                    std::ostringstream error_text;
                    error_text
                        << "Win32 Message Loop Error: "
                        << ::GetLastError();
                    throw std::runtime_error(error_text.str());
                }

                if (
                    ::IsDialogMessageW(message.hwnd, &message) != 0 ||
                    ::IsDialogMessageW(
                        ::GetAncestor(message.hwnd, GA_ROOT), &message
                    ) != 0
                )
                {
                    continue;
                }

                ::TranslateMessage(&message);
                ::DispatchMessageW(&message);
            }
        }


    };


}}}

#endif