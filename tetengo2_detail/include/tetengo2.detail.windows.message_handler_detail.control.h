/*! \file
    \brief The definition of
           tetengo2::detail::windows::message_handler_detail::control.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_CONTROL_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_CONTROL_H

#include <cstddef>
#include <system_error>
#include <tuple>

#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows { namespace message_handler_detail
{
    namespace control
    {
        template <typename Button>
        boost::optional< ::LRESULT> on_tetengo2_command(
            Button&        button,
            const ::WPARAM w_param,
            const ::LPARAM l_param
        )
        {
            button.mouse_observer_set().clicked()();

            return boost::make_optional< ::LRESULT>(0);
        }

        template <typename Control>
        boost::optional< ::LRESULT> on_control_color(Control& control, const ::WPARAM w_param, const ::LPARAM l_param)
        {
            if (!control.background() && !control.text_color())
                return boost::none;

            const ::HDC device_context = reinterpret_cast< ::HDC>(w_param);
            if (!control.paint_observer_set().paint_background().empty())
            {
                typename Control::base_type::widget_canvas_type canvas(device_context);
                control.paint_observer_set().paint_background()(canvas);
            }

            if (control.text_color())
            {
                const ::COLORREF previous_color =
                    ::SetTextColor(
                        device_context,
                        RGB(control.text_color()->red(), control.text_color()->green(), control.text_color()->blue())
                    );
                if (previous_color == CLR_INVALID)
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't set text color."
                        )
                    );
                }
            }
            const int previous_background_mode = ::SetBkMode(device_context, TRANSPARENT);
            if (previous_background_mode == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't set background mode."
                    )
                );
            }

            return boost::make_optional(reinterpret_cast< ::LRESULT>(::GetStockObject(NULL_BRUSH)));
        }

        template <typename Control>
        boost::optional< ::LRESULT> on_set_focus(Control& control, const ::WPARAM w_param, const ::LPARAM l_param)
        {
            if (control.has_parent())
            {
                typename Control::base_type& dialog = control.root_ancestor();

                std::get<2>(*dialog.details()) = std::get<0>(*control.details()).get();
            }

            return boost::none;
        }


    }


}}}}


#endif
#endif