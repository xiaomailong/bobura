/*! \file
    \brief The definition of tetengo2::gui::win32::label.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_LABEL_H)
#define TETENGO2_GUI_WIN32_LABEL_H

//#include <cstddef>
//#include <stdexcept>
//#include <utility>

//#include <boost/bind.hpp>
//#include <boost/optional.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>

#include "tetengo2.cpp0x_keyword.h"
#include "tetengo2.gui.win32.widget.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a label for Win32 platforms.
 
        \tparam Traits A traits type.
   */
    template <typename Traits>
    class label : public widget<typename Traits::base_type>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The base type.
        typedef widget<typename traits_type::base_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a label.

            \param parent A parent widget.

            \throw std::runtime_error When a label cannot be created.
        */
        explicit label(base_type& parent)
        :
        base_type(make_message_handler_map(message_handler_map_type())),
        m_handle(create_window(parent, style))
        m_p_original_window_procedure(replace_window_procedure(m_handle))
        {
            initialize(this);
        }

        /*!
            \brief Destroys the label.
        */
        virtual ~label()
        TETENGO2_NOEXCEPT
        {}


    private:
        // static functions

        static handle_type create_window(const base_type& parent)
        {
            const handle_type handle = ::CreateWindowExW(
                0,
                L"Static",
                L"tetengo2::gui::win32::label",
                WS_CHILD | WS_TABSTOP | WS_VISIBLE,
                0,
                0,
                64,
                64,
                parent.handle(),
                NULL,
                ::GetModuleHandle(NULL),
                NULL
            );
            if (handle == NULL)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't create a label!")
                );
            }

            return handle;
        }

        static ::WNDPROC replace_window_procedure(const ::HWND handle)
        {
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(push)
#    pragma warning(disable: 4244)
#endif
            const ::LONG_PTR result = 
                ::SetWindowLongPtrW(
                    handle,
                    GWLP_WNDPROC,
                    reinterpret_cast< ::LONG_PTR>(
                        base_type::p_static_window_procedure()
                    )
                );
#if defined(_WIN32) && !defined(_WIN64)
#    pragma warning(pop)
#endif
            if (result == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't replace window procedure.")
                );
            }

            return reinterpret_cast< ::WNDPROC>(result);
        }


        // variables

        const handle_type m_handle;

        const ::WNDPROC m_p_original_window_procedure;


        // virtual functions

        virtual handle_type handle_impl()
        const
        {
            return m_handle;
        }

        virtual ::WNDPROC p_default_window_procedure()
        const
        {
            return m_p_original_window_procedure;
        }


        // functions

        message_handler_map_type make_message_handler_map(
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            return map;
        }


    };


}}}

#endif