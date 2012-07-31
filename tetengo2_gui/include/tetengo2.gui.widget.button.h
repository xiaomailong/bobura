/*! \file
    \brief The definition of tetengo2::gui::widget::button.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIDGET_BUTTON_H)
#define TETENGO2_GUI_WIDGET_BUTTON_H

//#include <stdexcept>

#include "tetengo2.gui.widget.control.h"


namespace tetengo2 { namespace gui { namespace widget
{
    /*!
        \brief The class template for a button.

        \tparam Traits                A traits type.
        \tparam WidgetDetails         A detail implementation type of a widget.
        \tparam MessageHandlerDetails A detail implementation type of a message handler.
   */
    template <typename Traits, typename WidgetDetails, typename MessageHandlerDetails>
    class button : public control<typename Traits::base_type, WidgetDetails, MessageHandlerDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

        //! The detail implementation type of a message handler.
        typedef MessageHandlerDetails message_handler_details_type;

        //! The base type.
        typedef control<typename traits_type::base_type, widget_details_type, message_handler_details_type> base_type;

        //! The widget type.
        typedef typename base_type::base_type widget_type;

        //! The detail implementation type.
        typedef typename widget_details_type::widget_details_type details_type;

        //! The detail implementation pointer type.
        typedef typename widget_details_type::widget_details_ptr_type details_ptr_type;

        //! The style type.
        struct style_type { enum enum_t //!< Scoped enum.
        {
            normal,   //!< A normal button.
            default_, //!< A default button.
            cancel    //!< A cancel button.
        };};


        // constructors and destructor

        /*!
            \brief Creates a button.

            The window cannot have plural buttons with style_type::default_. And so is style_type::cancel.
            When creating a second button with style_type::default_ or style_type::cancel, std::runtime_error is
            thrown.

            \param parent A parent widget.
            \param style  A style.
        */
        explicit button(widget_type& parent, const typename style_type::enum_t style = style_type::normal)
        :
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable: 4355)
#endif
        base_type(
            base_type::scroll_bar_style_type::none,
            message_handler_details_type::make_button_message_handler_map(*this, message_handler_map_type()),
            widget_details_type::create_button(parent, style == style_type::default_, style == style_type::cancel)
        ),
#if defined(_MSC_VER)
#   pragma warning(pop)
#endif
        m_style(style)
        {
            initialize(this);
        }

        /*!
            \brief Destroys the button.
        */
        virtual ~button()
        {}


        // functions

        /*!
            \brief Returns the style.

            \return The style.
        */
        typename style_type::enum_t style()
        const
        {
            return m_style;
        }


    private:
        // types

        typedef typename message_handler_details_type::message_handler_map_type message_handler_map_type;


        // variables

        const typename style_type::enum_t m_style;


    };


}}}


#endif
