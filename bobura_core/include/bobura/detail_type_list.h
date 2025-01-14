/*! \file
    \brief The definition of bobura::detail_type_list.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_DETAILTYPELIST_H)
#define BOBURA_DETAILTYPELIST_H

#include <boost/predef.h>

#include <tetengo2/detail/stub/alert.h>
#include <tetengo2/detail/stub/common_dialog.h>
#include <tetengo2/detail/stub/cursor.h>
#include <tetengo2/detail/stub/drawing.h>
#include <tetengo2/detail/stub/gui_fixture.h>
#include <tetengo2/detail/stub/icon.h>
#include <tetengo2/detail/stub/menu.h>
#include <tetengo2/detail/stub/message_handler.h>
#include <tetengo2/detail/stub/message_loop.h>
#include <tetengo2/detail/stub/mouse_capture.h>
#include <tetengo2/detail/stub/scroll.h>
#include <tetengo2/detail/stub/shell.h>
#include <tetengo2/detail/stub/system_color.h>
#include <tetengo2/detail/stub/timer.h>
#include <tetengo2/detail/stub/unit.h>
#include <tetengo2/detail/stub/virtual_key.h>
#include <tetengo2/detail/stub/widget.h>
#if BOOST_COMP_MSVC
#   include <tetengo2/detail/windows/alert.h>
#   include <tetengo2/detail/windows/common_dialog.h>
#   include <tetengo2/detail/windows/config.h>
#   include <tetengo2/detail/windows/cursor.h>
#   include <tetengo2/detail/windows/direct2d/drawing.h>
#   include <tetengo2/detail/windows/encoding.h>
#   include <tetengo2/detail/windows/gdiplus/drawing.h>
#   include <tetengo2/detail/windows/gdiplus/gui_fixture.h>
#   include <tetengo2/detail/windows/gui_fixture.h>
#   include <tetengo2/detail/windows/icon.h>
#   include <tetengo2/detail/windows/menu.h>
#   include <tetengo2/detail/windows/message_handler.h>
#   include <tetengo2/detail/windows/message_loop.h>
#   include <tetengo2/detail/windows/mouse_capture.h>
#   include <tetengo2/detail/windows/scroll.h>
#   include <tetengo2/detail/windows/shell.h>
#   include <tetengo2/detail/windows/system_color.h>
#   include <tetengo2/detail/windows/timer.h>
#   include <tetengo2/detail/windows/unit.h>
#   include <tetengo2/detail/windows/virtual_key.h>
#   include <tetengo2/detail/windows/widget.h>
#else
#   include <tetengo2/detail/unixos/config.h>
#   include <tetengo2/detail/unixos/encoding.h>
#endif


namespace bobura { namespace type_list
{
    /**** Detail Implementation **************************************************************************************/

#if !defined(DOCUMENTATION)
    namespace detail { namespace detail
    {
        namespace application
        {
#if BOOST_COMP_MSVC
            using alert_type = tetengo2::detail::windows::alert;

            using common_dialog_type = tetengo2::detail::windows::common_dialog;

            using config_type = tetengo2::detail::windows::config;

            using cursor_type = tetengo2::detail::windows::cursor;

            using drawing_type = tetengo2::detail::windows::gdiplus::drawing;

            using fast_drawing_type = tetengo2::detail::windows::direct2d::drawing;

            using encoding_type = tetengo2::detail::windows::encoding;

            struct gui_fixture_type
            {
                tetengo2::detail::windows::gui_fixture m_windows_gui_fixture;
                tetengo2::detail::windows::gdiplus::gui_fixture m_gdiplus_gui_fixutre;
            };

            using icon_type = tetengo2::detail::windows::icon;

            using menu_type = tetengo2::detail::windows::menu;

            using message_handler_type = tetengo2::detail::windows::message_handler;

            using message_loop_type = tetengo2::detail::windows::message_loop;

            using mouse_capture_type = tetengo2::detail::windows::mouse_capture;

            using scroll_type = tetengo2::detail::windows::scroll;

            using shell_type = tetengo2::detail::windows::shell;

            using system_color_type = tetengo2::detail::windows::system_color;

            using timer_type = tetengo2::detail::windows::timer;

            using unit_type = tetengo2::detail::windows::unit;

            using virtual_key_type = tetengo2::detail::windows::virtual_key;

            using widget_type = tetengo2::detail::windows::widget;
#endif

        }

        namespace test
        {
            using alert_type = tetengo2::detail::stub::alert;

            using common_dialog_type = tetengo2::detail::stub::common_dialog;

#if BOOST_COMP_MSVC
            using config_type = tetengo2::detail::windows::config;
#else
            using config_type = tetengo2::detail::unixos::config;
#endif

            using cursor_type = tetengo2::detail::stub::cursor;

            using drawing_type = tetengo2::detail::stub::drawing;

            using fast_drawing_type = tetengo2::detail::stub::drawing;

#if BOOST_COMP_MSVC
            using encoding_type = tetengo2::detail::windows::encoding;
#else
            using encoding_type = tetengo2::detail::unixos::encoding;
#endif

            struct gui_fixture_type
            {
                tetengo2::detail::stub::gui_fixture m_stub_gui_fixture;
            };

            using icon_type = tetengo2::detail::stub::icon;

            using menu_type = tetengo2::detail::stub::menu;

            using message_handler_type = tetengo2::detail::stub::message_handler;

            using message_loop_type = tetengo2::detail::stub::message_loop;

            using mouse_capture_type = tetengo2::detail::stub::mouse_capture;

            using scroll_type = tetengo2::detail::stub::scroll;

            using shell_type = tetengo2::detail::stub::shell;

            using system_color_type = tetengo2::detail::stub::system_color;

            using timer_type = tetengo2::detail::stub::timer;

            using unit_type = tetengo2::detail::stub::unit;

            using virtual_key_type = tetengo2::detail::stub::virtual_key;

            using widget_type = tetengo2::detail::stub::widget;

        }

    }}
#endif

    /*!
        \brief The detail type list for the application.
    */
    struct detail_for_application
    {
#if BOOST_COMP_MSVC || defined(DOCUMENTATION)
        //! The detail implementation type of the alert.
        using alert_type = detail::detail::application::alert_type;

        //! The detail implementation type of the common dialogs.
        using common_dialog_type = detail::detail::application::common_dialog_type;

        //! The detail implementation type of the configuration.
        using config_type = detail::detail::application::config_type;

        //! The detail implementation type of the cursor.
        using cursor_type = detail::detail::application::cursor_type;

        //! The detail implementation type of the drawing.
        using drawing_type = detail::detail::application::drawing_type;

        //! The detail implementation type of the fast drawing.
        using fast_drawing_type = detail::detail::application::fast_drawing_type;

        //! The detail implementation type of the encoding.
        using encoding_type = detail::detail::application::encoding_type;

        //! The detail implementation type of the GUI fixture.
        using gui_fixture_type = detail::detail::application::gui_fixture_type;

        //! The detail implementation type of the icon.
        using icon_type = detail::detail::application::icon_type;

        //! The detail implementation type of the menu.
        using menu_type = detail::detail::application::menu_type;

        //! The detail implementation type of the message handler.
        using message_handler_type = detail::detail::application::message_handler_type;

        //! The detail implementation type of the message loop.
        using message_loop_type = detail::detail::application::message_loop_type;

        //! The detail implementation type of the mouse capture.
        using mouse_capture_type = detail::detail::application::mouse_capture_type;

        //! The detail implementation type of the scroll.
        using scroll_type = detail::detail::application::scroll_type;

        //! The detail implementation type of the shell.
        using shell_type = detail::detail::application::shell_type;

        //! The detail implementation type of the system color.
        using system_color_type = detail::detail::application::system_color_type;

        //! The detail implementation type of the timer.
        using timer_type = detail::detail::application::timer_type; 

        //! The detail implementation type of the unit.
        using unit_type = detail::detail::application::unit_type;

        //! The detail implementation type of the virtual key.
        using virtual_key_type = detail::detail::application::virtual_key_type;

        //! The detail implementation type of the widget.
        using widget_type = detail::detail::application::widget_type;
#endif

    };

    /*!
        \brief The detail type list for the testing.
    */
    struct detail_for_test
    {
        //! The detail implementation type of the alert.
        using alert_type = detail::detail::test::alert_type;

        //! The detail implementation type of the common dialogs.
        using common_dialog_type = detail::detail::test::common_dialog_type;

        //! The detail implementation type of the configuration.
        using config_type = detail::detail::test::config_type;

        //! The detail implementation type of the cursor.
        using cursor_type = detail::detail::test::cursor_type;

        //! The detail implementation type of the drawing.
        using drawing_type = detail::detail::test::drawing_type;

        //! The detail implementation type of the fast drawing.
        using fast_drawing_type = detail::detail::test::fast_drawing_type;

        //! The detail implementation type of the encoding.
        using encoding_type = detail::detail::test::encoding_type;

        //! The detail implementation type of the GUI fixture.
        using gui_fixture_type = detail::detail::test::gui_fixture_type;

        //! The detail implementation type of the icon.
        using icon_type = detail::detail::test::icon_type;

        //! The detail implementation type of the menu.
        using menu_type = detail::detail::test::menu_type;

        //! The detail implementation type of the message handler.
        using message_handler_type = detail::detail::test::message_handler_type;

        //! The detail implementation type of the message loop.
        using message_loop_type = detail::detail::test::message_loop_type;

        //! The detail implementation type of the mouse capture.
        using mouse_capture_type = detail::detail::test::mouse_capture_type;

        //! The detail implementation type of the scroll.
        using scroll_type = detail::detail::test::scroll_type;

        //! The detail implementation type of the shell.
        using shell_type = detail::detail::test::shell_type;

        //! The detail implementation type of the system color.
        using system_color_type = detail::detail::test::system_color_type;

        //! The detail implementation type of the timer.
        using timer_type = detail::detail::test::timer_type; 

        //! The detail implementation type of the unit.
        using unit_type = detail::detail::test::unit_type;

        //! The detail implementation type of the virtual key.
        using virtual_key_type = detail::detail::test::virtual_key_type;

        //! The detail implementation type of the widget.
        using widget_type = detail::detail::test::widget_type;

    };


}}


#endif
