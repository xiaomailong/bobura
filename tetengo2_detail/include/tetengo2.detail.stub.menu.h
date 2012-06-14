/*! \file
    \brief The definition of tetengo2::detail::stub::menu.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_MENU_H)
#define TETENGO2_DETAIL_STUB_MENU_H

#include <memory>
#include <system_error>

#include <boost/noncopyable.hpp>

#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a menu.
    */
    class menu : boost::noncopyable
    {
    public:
        // types

        //! The menu details type.
        struct menu_details_type {};

        //! The menu details pointer type.
        typedef std::unique_ptr<menu_details_type> menu_details_ptr_type;

        //! The shortcut key table details type.
        struct shortcut_key_table_details_type {};

        //! The shortcut key table details pointer type.
        typedef std::unique_ptr<shortcut_key_table_details_type> shortcut_key_table_details_ptr_type;

        //! The style tag type.
        struct style_tag {};


        // static functions

        /*!
            \brief Creates a menu bar.

            \return A unque pointer to a menu bar.

            \throw std::system_error When a menu bar cannot be created.
        */
        static menu_details_ptr_type create_menu_bar()
        {
            return tetengo2::make_unique<menu_details_type>();
        }

        /*!
            \brief Creates a popup menu.

            \return A unque pointer to a popup menu.

            \throw std::system_error When a popup menu cannot be created.
        */
        static menu_details_ptr_type create_popup_menu()
        {
            return tetengo2::make_unique<menu_details_type>();
        }

        /*!
            \brief Creates a menu.

            \return A unque pointer to a menu.
        */
        static menu_details_ptr_type create_menu()
        {
            return tetengo2::make_unique<menu_details_type>();
        }

        /*!
            \brief Sets an enabled status.

            \tparam MenuBase A menu base type.

            \param menu    A menu.
            \param enabled An enabled status.
        */
        template <typename MenuBase>
        static void set_enabled(MenuBase& menu, const bool enabled)
        {}

        /*!
            \brief Creates an empty shortcut key table.

            \tparam Entry A shortcut key table entry type.

            \return A unique pointer to a shortcut key table.
        */
        template <typename Entry>
        static shortcut_key_table_details_ptr_type create_shortcut_key_table()
        {
            return shortcut_key_table_details_ptr_type();
        }

        /*!
            \brief Creates a shortcut key table.

            \tparam InputIterator An input iterator type.

            \param first A first position among shortcut keys.
            \param last  A last position among shortcut keys.

            \return A unique pointer to a shortcut key table.

            \throw std::system_error When a shortcut key table cannot be
                                     created.
        */
        template <typename InputIterator>
        static shortcut_key_table_details_ptr_type create_shortcut_key_table(
            const InputIterator first,
            const InputIterator last
        )
        {
            return shortcut_key_table_details_ptr_type();
        }

        /*!
            \brief Inserts a menu.

            \tparam PopupMenu       A popup menu type.
            \tparam ForwardIterator An forward iterator type.
            \tparam MenuBase        A menu base type.
            \tparam Encoder         An encoder type.

            \param popup_menu A popup menu to which a menu is inserted.
            \param offset     An offset.
            \param menu       A menu to insert.
            \param encoder    An encoder.

            \throw std::system_error When a menu cannot be inserted.
        */
        template <typename PopupMenu, typename ForwardIterator, typename MenuBase, typename Encoder>
        static void insert_menu(
            PopupMenu&            popup_menu,
            const ForwardIterator offset,
            MenuBase&             menu,
            const Encoder&        encoder
        )
        {}

        /*!
            \brief Erases a menu.

            \tparam PopupMenu       A popup menu type.
            \tparam ForwardIterator An forward iterator type.

            \param popup_menu A popup menu to which a menu is inserted.
            \param first      A first position to erase.
            \param last       A last position to erase.

            \throw std::system_error When a menu cannot be erased.
        */
        template <typename PopupMenu, typename ForwardIterator>
        static void erase_menus(PopupMenu& popup_menu, const ForwardIterator first, const ForwardIterator last)
        {}

        /*!
            \brief Returns the menu bar style.

            \return The menu bar style.
        */
        static const style_tag& menu_bar_style()
        {
            static const style_tag singleton = style_tag();
            return singleton;
        }

        /*!
            \brief Returns the popup menu style.

            \return The popup menu style.
        */
        static const style_tag& popup_menu_style()
        {
            static const style_tag singleton = style_tag();
            return singleton;
        }

        /*!
            \brief Returns the menu command style.

            \return The menu command style.
        */
        static const style_tag& menu_command_style()
        {
            static const style_tag singleton = style_tag();
            return singleton;
        }

        /*!
            \brief Returns the menu separator style.

            \return The menu separator style.
        */
        static const style_tag& menu_separator_style()
        {
            static const style_tag singleton = style_tag();
            return singleton;
        }


    private:
        // forbidden operations

        menu();


    };


}}}


#endif
