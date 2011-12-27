/*! \file
    \brief The definition of tetengo2::gui::menu_command.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MENUCOMMAND_H)
#define TETENGO2_GUI_MENUCOMMAND_H

//#include <utility>

#include "tetengo2.cpp11.h"
#include "tetengo2.gui.menu.menu.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a menu command.

        \tparam Traits      A traits type.
        \tparam MenuDetails A detail implementation type of a menu.
   */
    template <typename Traits, typename MenuDetails>
    class menu_command : public menu<Traits, MenuDetails>
    {
    public:
        // types

        //! The traits type.
        typedef Traits traits_type;

        //! The detail implementation type of a menu.
        typedef MenuDetails menu_details_type;

        //! The base type.
        typedef menu<traits_type, menu_details_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a menu command.

            \tparam S A string type.

            \param text A text.
        */
        template <typename S>
        explicit menu_command(S&& text)
        :
        base_type(std::forward<S>(text), menu_details_type::create_menu())
        {}

        /*!
            \brief Destroys the menu command.
        */
        virtual ~menu_command()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename base_type::style_type style_type;


        // virtual functions

        virtual const style_type& style_impl()
        const
        {
            return menu_details_type::menu_command_style();
        }


    };


}}


#endif
