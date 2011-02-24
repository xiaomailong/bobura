/*! \file
    \brief The definition of tetengo2::detail::windows::gui_fixture.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GUIFIXTURE_H)
#define TETENGO2_DETAIL_WINDOWS_GUIFIXTURE_H

#include <stdexcept>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <CommCtrl.h>

#include "tetengo2.cpp0x.h"


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a GUI fixture.
    */
    class gui_fixture : private boost::noncopyable
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates a detail implementation of a GUI fixture.
        */
        gui_fixture()
        {
            setup_common_controls();
        }


    private:
        // static functions

        static void setup_common_controls()
        {
            ::INITCOMMONCONTROLSEX enabled_common_controls;
            enabled_common_controls.dwSize = sizeof(::INITCOMMONCONTROLSEX);
            enabled_common_controls.dwICC =
                ICC_WIN95_CLASSES |
                ICC_DATE_CLASSES |
                ICC_COOL_CLASSES |
                ICC_INTERNET_CLASSES |
                ICC_PAGESCROLLER_CLASS |
                ICC_NATIVEFNTCTL_CLASS |
                ICC_STANDARD_CLASSES |
                ICC_LINK_CLASS;
            if (::InitCommonControlsEx(&enabled_common_controls) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't initialize common controls!")
                );
            }
        }


    };


}}}


#endif