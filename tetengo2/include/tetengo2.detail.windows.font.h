/*! \file
    \brief The definition of tetengo2::detail::windows::font.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_FONT_H)
#define TETENGO2_DETAIL_WINDOWS_FONT_H

#include <stdexcept>

#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.detail.windows.windows_version.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief Returns a nonclient metrics.

        \param metrics A metrics where the result is stored.
    */
    inline void get_nonclient_metrics(::NONCLIENTMETRICSW& metrics)
    {
        const ::UINT metrics_size =
            tetengo2::detail::windows::on_windows_vista_or_later() ?
            sizeof(::NONCLIENTMETRICSW) :
            sizeof(::NONCLIENTMETRICSW) - sizeof(int);
        metrics.cbSize = metrics_size;
        if (
            ::SystemParametersInfoW(
                SPI_GETNONCLIENTMETRICS,
                metrics_size,
                &metrics,
                0
            ) == 0
        )
        {
            BOOST_THROW_EXCEPTION(
                std::runtime_error("Can't get non-client metrics.")
            );
        }
    }

    /*!
        \brief Returns the message font.

        \return The message font.
    */
    inline ::LOGFONTW get_message_font()
    {
        ::NONCLIENTMETRICSW metrics;
        get_nonclient_metrics(metrics);

        return metrics.lfMessageFont;
    }


}}}


#endif