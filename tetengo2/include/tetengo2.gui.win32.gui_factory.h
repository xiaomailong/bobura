/*! \file
    \brief The definition of tetengo2::gui::win32::gui_factory.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_GUIFACTORY_H)
#define TETENGO2_GUI_WIN32_GUIFACTORY_H

#include <string>

#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.gui.gui_factory.h"
#include "tetengo2.gui.win32.alerter.h"
#include "tetengo2.gui.win32.canvas.h"
#include "tetengo2.gui.win32.message_loop.h"
#include "tetengo2.gui.win32.window.h"
#include "tetengo2.gui.win32.window_message_receiver.h"


namespace tetengo2 { namespace gui { namespace win32
{
    namespace
    {
        typedef
            canvas<
                ::HDC,
                std::size_t,
                std::wstring,
                ::HWND
            >
            canvas_type;

        typedef alerter< ::HWND> alerter_type;

        typedef
            window<
                ::HWND,
                window_message_receiver,
                alerter_type,
                canvas_type,
                std::wstring
            >
            window_type;
    }

    //! The GUI object factory type for Win32 platforms.
    typedef
        tetengo2::gui::gui_factory<
            canvas_type,
            window_type,
            message_loop,
            alerter_type
        >
        gui_factory;

}}}

#endif
