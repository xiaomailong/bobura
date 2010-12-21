/*! \file
    \brief The definition of bobura::about_dialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_ABOUTDIALOG_H)
#define BOBURA_ABOUTDIALOG_H

#include <memory>
#include <sstream>
#include <utility>

#include <boost/format.hpp>
#include <boost/mpl/at.hpp>
#include <boost/scoped_ptr.hpp>

#include <tetengo2.cpp0x_keyword.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>

#include "bobura.message.type_list.h"


namespace bobura
{
    /*!
        \brief The class template for the about dialog.

        \tparam Dialog                     A dialog type.
        \tparam MessageCatalog             A message catalog type.
        \tparam Label                      A label type.
        \tparam Button                     A button type.
        \tparam AboutDialogMessageTypeList A message type.
    */
    template <
        typename Dialog,
        typename MessageCatalog,
        typename Label,
        typename Button,
        typename AboutDialogMessageTypeList
    >
    class about_dialog : public Dialog
    {
    public:
        // types

        //! The base type.
        typedef Dialog base_type;

        //! The abstract window type.
        typedef typename base_type::base_type abstract_window_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;

        //! The label type.
        typedef Label label_type;

        //! The button type.
        typedef Button button_type;

        //! The message type list type.
        typedef
            AboutDialogMessageTypeList about_dialog_message_type_list_type;


        // constructors and destructor

        /*!
            \brief Creates an about dialog.

            \param parent A parent window.
            \param message_catalog A message catalog.
        */
        about_dialog(
            abstract_window_type&       parent,
            const message_catalog_type& message_catalog
        )
        :
        base_type(parent),
        m_message_catalog(message_catalog),
        m_p_title_label(),
        m_p_copyright_label(),
        m_p_link_label(),
        m_p_ok_button()
        {
            initialize_dialog(parent);
        }

        /*!
            \brief Destroys the about dialog.
        */
        virtual ~about_dialog()
        TETENGO2_NOEXCEPT
        {}


    private:
        // variables

        const message_catalog_type& m_message_catalog;

        boost::scoped_ptr<label_type> m_p_title_label;

        boost::scoped_ptr<label_type> m_p_copyright_label;

        boost::scoped_ptr<label_type> m_p_link_label;

        boost::scoped_ptr<button_type> m_p_ok_button;


        // functions

        void initialize_dialog(const abstract_window_type& parent)
        {
            set_text(m_message_catalog.get(TETENGO2_TEXT("About")));

            this->set_client_dimension(
                typename about_dialog::dimension_type(36, 10)
            );

            typedef
                tetengo2::gui::position<typename about_dialog::position_type>
                pos_type;
            this->set_position(
                typename about_dialog::position_type(
                    pos_type::left(parent.position()) + 6,
                    pos_type::top(parent.position()) + 6
                )
            );

            m_p_title_label.reset(create_title_label().release());
            m_p_copyright_label.reset(create_copyright_label().release());
            m_p_link_label.reset(create_link_label().release());
            m_p_ok_button.reset(create_ok_button().release());
        }

        std::auto_ptr<label_type> create_title_label()
        {
            typedef typename base_type::string_type::value_type char_type;
            std::basic_ostringstream<char_type> title;
            title <<
                boost::basic_format<char_type>(TETENGO2_TEXT("%s  %s %s")) %
                    m_message_catalog.get(TETENGO2_TEXT("Bobura")) %
                    m_message_catalog.get(TETENGO2_TEXT("version")) %
                    typename base_type::string_type(TETENGO2_TEXT("0.0.0"));

            std::auto_ptr<label_type> p_label(new label_type(*this));

            p_label->set_text(title.str());
            p_label->set_dimension(typename about_dialog::dimension_type(32, 2));
            p_label->set_position(typename about_dialog::position_type(2, 1));

            return p_label;
        }

        std::auto_ptr<label_type> create_copyright_label()
        {
            std::auto_ptr<label_type> p_label(new label_type(*this));

            p_label->set_text(
                typename base_type::string_type(
                    TETENGO2_TEXT("Copyright (C) 2010 kaorut")
                )
            );
            p_label->set_dimension(typename about_dialog::dimension_type(32, 2));
            p_label->set_position(typename about_dialog::position_type(2, 3));

            return p_label;
        }

        std::auto_ptr<label_type> create_link_label()
        {
            std::auto_ptr<label_type> p_label(new label_type(*this));

            p_label->set_text(
                typename base_type::string_type(
                    TETENGO2_TEXT("http://www.tetengo.org/")
                )
            );
            p_label->set_dimension(typename about_dialog::dimension_type(32, 2));
            p_label->set_position(typename about_dialog::position_type(2, 5));

            return p_label;
        }

        std::auto_ptr<button_type> create_ok_button()
        {
            std::auto_ptr<button_type> p_button(
                new button_type(*this, button_type::style_default)
            );

            p_button->set_text(m_message_catalog.get(TETENGO2_TEXT("OK")));
            p_button->set_dimension(typename about_dialog::dimension_type(8, 2));
            p_button->set_position(typename about_dialog::position_type(26, 7));
            p_button->mouse_observer_set().clicked().connect(
                typename boost::mpl::at<
                    about_dialog_message_type_list_type,
                    message::about_dialog::type::ok_button_mouse
                >::type(*this)
            );

            return p_button;
        }


    };


}

#endif
