/*! \file
    \brief The definition of bobura::property_bar.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <cassert>
#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/message/property_bar.h>
#include <bobura/property_bar.h>
#include <bobura/type_list.h>


namespace bobura
{
    template <
        typename String,
        typename Position,
        typename Dimension,
        typename AbstractWindow,
        typename SideBar,
        typename MapBox,
        typename MessageCatalog,
        typename ConfigTraits
    >
    class property_bar<
        String, Position, Dimension, AbstractWindow, SideBar, MapBox, MessageCatalog, ConfigTraits
    >::impl :
        private boost::noncopyable
    {
    public:
        // types

        using abstract_window_type = AbstractWindow;

        using map_box_type = MapBox;

        using message_catalog_type = MessageCatalog;

        using settings_type = typename property_bar::settings_type;


        // constructors and destructor

        impl(
            property_bar&               self,
            abstract_window_type&,
            settings_type&              settings,
            const message_catalog_type& message_catalog
        )
        :
        m_settings(settings),
        m_message_catalog(message_catalog),
        m_p_map_box()
        {
            initialize_property_bar(self);
        }


        // functions

        const map_box_type& map_box()
        const
        {
            assert(m_p_map_box);
            return *m_p_map_box;
        }

        map_box_type& map_box()
        {
            assert(m_p_map_box);
            return *m_p_map_box;
        }

        void save_settings(property_bar& self)
        {
            m_settings.set_property_bar_width(self.normal_preferred_width());
            m_settings.set_property_bar_minimized(self.minimized());
            m_settings.set_property_bar_splitter_position(m_p_map_box->splitter_position());
        }


    private:
        // types

        using position_type = Position;

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using dimension_type = Dimension;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using base_type = SideBar;

        using resized_observer_type = message::property_bar::resized<base_type, map_box_type>;

        using mouse_pressed_observer_type = message::property_bar::mouse_pressed<map_box_type>;


        // variables

        settings_type& m_settings;

        const message_catalog_type& m_message_catalog;

        std::unique_ptr<map_box_type> m_p_map_box;


        // functions

        void initialize_property_bar(property_bar& self)
        {
            self.set_text(m_message_catalog.get(TETENGO2_TEXT("PropertyBar:Properties")));

            m_p_map_box = tetengo2::stdalt::make_unique<map_box_type>(self);

            self.size_observer_set().resized().connect(resized_observer_type{ self, *m_p_map_box });

            m_p_map_box->mouse_observer_set().pressed().connect(mouse_pressed_observer_type{ *m_p_map_box });

            load_settings(self);
        }

        void load_settings(property_bar& self)
        {
            const auto width = m_settings.property_bar_width();
            if (width)
                self.set_width(*width);
            else
                self.set_width(width_type{ 32 });

            self.size_observer_set().resized()();

            const auto minimized = m_settings.property_bar_minimized();
            if (minimized)
                self.set_minimized(*minimized);
            else
                self.set_minimized(false);

            const auto splitter_position = m_settings.property_bar_splitter_position();
            if (splitter_position)
                m_p_map_box->set_splitter_position(*splitter_position);
            else
                m_p_map_box->set_splitter_position(left_type{ 16 });
        }


    };


    template <
        typename String,
        typename Position,
        typename Dimension,
        typename AbstractWindow,
        typename SideBar,
        typename MapBox,
        typename MessageCatalog,
        typename ConfigTraits
    >
    property_bar<
        String, Position, Dimension, AbstractWindow, SideBar, MapBox, MessageCatalog, ConfigTraits
    >::property_bar(abstract_window_type& parent, settings_type& settings, const message_catalog_type& message_catalog)
    :
    base_type(parent),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(*this, parent, settings, message_catalog))
    {}

    template <
        typename String,
        typename Position,
        typename Dimension,
        typename AbstractWindow,
        typename SideBar,
        typename MapBox,
        typename MessageCatalog,
        typename ConfigTraits
    >
    property_bar<
        String, Position, Dimension, AbstractWindow, SideBar, MapBox, MessageCatalog, ConfigTraits
    >::~property_bar()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <
        typename String,
        typename Position,
        typename Dimension,
        typename AbstractWindow,
        typename SideBar,
        typename MapBox,
        typename MessageCatalog,
        typename ConfigTraits
    >
    const typename property_bar<
        String, Position, Dimension, AbstractWindow, SideBar, MapBox, MessageCatalog, ConfigTraits
    >::map_box_type&
    property_bar<String, Position, Dimension, AbstractWindow, SideBar, MapBox, MessageCatalog, ConfigTraits>::map_box()
    const
    {
        return m_p_impl->map_box();
    }

    template <
        typename String,
        typename Position,
        typename Dimension,
        typename AbstractWindow,
        typename SideBar,
        typename MapBox,
        typename MessageCatalog,
        typename ConfigTraits
    >
    typename property_bar<
        String, Position, Dimension, AbstractWindow, SideBar, MapBox, MessageCatalog, ConfigTraits
    >::map_box_type&
    property_bar<String, Position, Dimension, AbstractWindow, SideBar, MapBox, MessageCatalog, ConfigTraits>::map_box()
    {
        return m_p_impl->map_box();
    }

    template <
        typename String,
        typename Position,
        typename Dimension,
        typename AbstractWindow,
        typename SideBar,
        typename MapBox,
        typename MessageCatalog,
        typename ConfigTraits
    >
    void
    property_bar<
        String, Position, Dimension, AbstractWindow, SideBar, MapBox, MessageCatalog, ConfigTraits
    >::save_settings()
    {
        m_p_impl->save_settings(*this);
    }

        
    namespace
    {
 #if BOOST_COMP_MSVC
       namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using locale_type_list_type = type_list::locale<detail_type_list_type>;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class property_bar<
        typename application::common_type_list_type::string_type,
        typename application::ui_type_list_type::position_type,
        typename application::ui_type_list_type::dimension_type,
        typename application::ui_type_list_type::abstract_window_type,
        typename application::ui_type_list_type::side_bar_type,
        typename application::ui_type_list_type::map_box_type,
        typename application::locale_type_list_type::message_catalog_type,
        typename application::traits_type_list_type::config_type
    >;
#endif

    template class property_bar<
        typename test::common_type_list_type::string_type,
        typename test::ui_type_list_type::position_type,
        typename test::ui_type_list_type::dimension_type,
        typename test::ui_type_list_type::abstract_window_type,
        typename test::ui_type_list_type::side_bar_type,
        typename test::ui_type_list_type::map_box_type,
        typename test::locale_type_list_type::message_catalog_type,
        typename test::traits_type_list_type::config_type
    >;


}
