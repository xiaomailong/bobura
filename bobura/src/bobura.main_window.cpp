/*! \file
    \brief The definition of bobura::main_window.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <cassert>
//#include <memory>
//#include <utility>

//#include <boost/mpl/at.hpp>
//#include <boost/noncopyable.hpp>
//#include <boost/optional.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>
#include <tetengo2.utility.h>

#include "bobura.message.type_list.h"
#include "bobura.type_list.h"

#include "bobura.main_window.h"


namespace bobura
{
    namespace
    {
        template <
            typename Window,
            typename MessageCatalog,
            typename DiagramPictureBox,
            typename PropertyBar,
            typename Settings,
            typename ConfirmFileSave
        >
        class main_window<Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave>::impl :
            private boost::noncopyable
        {
        public:
            // types

            typedef Window base_type;

            typedef typename base_type::string_type string_type;

            typedef typename base_type::window_state_type window_state_type;

            typedef MessageCatalog message_catalog_type;

            typedef DiagramPictureBox diagram_picture_box_type;

            typedef PropertyBar property_bar_type;

            typedef Settings settings_type;

            typedef ConfirmFileSave confirm_file_save_type;


            // constructors and destructor

            impl(
                base_type&                    base,
                const message_catalog_type&   message_catalog,
                settings_type&                settings,
                const confirm_file_save_type& confirm_file_save
            )
            :
            m_base(base),
            m_message_catalog(message_catalog),
            m_p_diagram_picture_box(),
            m_p_property_bar(),
            m_settings(settings),
            m_confirm_file_save(confirm_file_save)
            {
                initialize_window();
            }


            // functions

            void set_title(const boost::optional<string_type>& document_name, const bool changed)
            {
                auto title = document_name ? *document_name : m_message_catalog.get(TETENGO2_TEXT("Common:Untitled"));
                if (changed)
                    title += string_type(TETENGO2_TEXT(" *"));
                title += string_type(TETENGO2_TEXT(" - "));
                title += m_message_catalog.get(TETENGO2_TEXT("App:Bobura"));

                m_base.set_text(title);
            }

            const diagram_picture_box_type& diagram_picture_box()
            const
            {
                assert(m_p_diagram_picture_box);
                return *m_p_diagram_picture_box;
            }

            diagram_picture_box_type& diagram_picture_box()
            {
                assert(m_p_diagram_picture_box);
                return *m_p_diagram_picture_box;
            }

            const property_bar_type& property_bar()
            const
            {
                assert(m_p_property_bar);
                return *m_p_property_bar;
            }

            property_bar_type& property_bar()
            {
                assert(m_p_property_bar);
                return *m_p_property_bar;
            }


        private:
            // types

            typedef typename boost::mpl::at<ui_type_list, type::ui::message_loop_break>::type message_loop_break_type;

            typedef
                typename boost::mpl::at<main_window_type_list, type::main_window::message_type_list>::type
                message_type_list_type;

            typedef typename base_type::position_type position_type;

            typedef typename tetengo2::gui::position<position_type>::left_type left_type;

            typedef typename tetengo2::gui::position<position_type>::top_type top_type;

            typedef typename base_type::dimension_type dimension_type;


            // variables

            base_type& m_base;

            const message_catalog_type& m_message_catalog;

            std::unique_ptr<diagram_picture_box_type> m_p_diagram_picture_box;

            std::unique_ptr<property_bar_type> m_p_property_bar;

            settings_type& m_settings;

            const confirm_file_save_type& m_confirm_file_save;


            // functions

            void initialize_window()
            {
                m_p_diagram_picture_box = tetengo2::make_unique<diagram_picture_box_type>(m_base);
                m_p_property_bar = tetengo2::make_unique<property_bar_type>(m_base, m_message_catalog);

                set_message_observers();

                set_title(boost::none, false);
                
                auto dimension = m_settings.main_window_dimension();
                if (dimension)
                    m_base.set_dimension(std::move(*dimension));
                const auto maximized = m_settings.main_window_maximized();
                if (maximized && *maximized)
                    m_base.set_window_state(window_state_type::maximized);
                else
                    m_base.set_window_state(window_state_type::normal);
            }

            void set_message_observers()
            {
                m_base.focus_observer_set().got_focus().connect(
                    [this]() { this->m_p_diagram_picture_box->set_focus(); }
                );
                m_base.paint_observer_set().paint_background().connect(
                    [](typename base_type::canvas_type&) { return true; }
                );
                m_base.window_observer_set().closing().connect(
                    typename boost::mpl::at<message_type_list_type, message::main_window::type::window_closing>::type(
                        m_base, m_confirm_file_save, m_settings
                    )
                );
                m_base.window_observer_set().destroyed().connect([](){ return message_loop_break_type()(0); });
            }


        };


    }


    template <
        typename Window,
        typename MessageCatalog,
        typename DiagramPictureBox,
        typename PropertyBar,
        typename Settings,
        typename ConfirmFileSave
    >
    main_window<Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave>::main_window(
        const message_catalog_type&   message_catalog,
        settings_type&                settings,
        const confirm_file_save_type& confirm_file_save
    )
    :
    base_type(),
    m_p_impl(tetengo2::make_unique<impl>(*this, message_catalog, settings, confirm_file_save))
    {}

    template <
        typename Window,
        typename MessageCatalog,
        typename DiagramPictureBox,
        typename PropertyBar,
        typename Settings,
        typename ConfirmFileSave
    >
    main_window<Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave>::~main_window()
    TETENGO2_CPP11_NOEXCEPT
    {}

    template <
        typename Window,
        typename MessageCatalog,
        typename DiagramPictureBox,
        typename PropertyBar,
        typename Settings,
        typename ConfirmFileSave
    >
    void main_window<Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave>::set_title(
        const boost::optional<string_type>& document_name,
        const bool                          changed
    )
    {
        m_p_impl->set_title(document_name, changed);
    }

    template <
        typename Window,
        typename MessageCatalog,
        typename DiagramPictureBox,
        typename PropertyBar,
        typename Settings,
        typename ConfirmFileSave
    >
    const typename main_window<
        Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave
    >::diagram_picture_box_type&
    main_window<
        Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave
    >::diagram_picture_box()
    const
    {
        return m_p_impl->diagram_picture_box();
    }

    template <
        typename Window,
        typename MessageCatalog,
        typename DiagramPictureBox,
        typename PropertyBar,
        typename Settings,
        typename ConfirmFileSave
    >
    typename main_window<
        Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave
    >::diagram_picture_box_type&
    main_window<
        Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave
    >::diagram_picture_box()
    {
        return m_p_impl->diagram_picture_box();
    }

    template <
        typename Window,
        typename MessageCatalog,
        typename DiagramPictureBox,
        typename PropertyBar,
        typename Settings,
        typename ConfirmFileSave
    >
    const typename main_window<
        Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave
    >::property_bar_type& main_window<
        Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave
    >::property_bar()
    const
    {
        return m_p_impl->property_bar();
    }

    template <
        typename Window,
        typename MessageCatalog,
        typename DiagramPictureBox,
        typename PropertyBar,
        typename Settings,
        typename ConfirmFileSave
    >
    typename main_window<
        Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave
    >::property_bar_type& main_window<
        Window, MessageCatalog, DiagramPictureBox, PropertyBar, Settings, ConfirmFileSave
    >::property_bar()
    {
        return m_p_impl->property_bar();
    }

    template class main_window<
        typename boost::mpl::at<ui_type_list, type::ui::window>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
        typename boost::mpl::at<main_window_type_list, type::main_window::diagram_picture_box>::type,
        typename boost::mpl::at<main_window_type_list, type::main_window::property_bar>::type,
        typename boost::mpl::at<setting_type_list, type::setting::settings>::type,
        typename boost::mpl::at<load_save_type_list, type::load_save::confirm_file_save>::type
    >;


}