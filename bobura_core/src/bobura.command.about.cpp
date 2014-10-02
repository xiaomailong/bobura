/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/about_dialog.h>
#include <bobura/basic_type_list.h>
#include <bobura/command/about.h>
#include <bobura/command/traits.h>


namespace bobura { namespace command
{
    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename ConfigTraits,
        typename MessageCatalog
    >
    class about<Traits, Position, Dimension, Dialog, ConfigTraits, MessageCatalog>::impl
    {
    public:
        // types

        using model_type = typename about::model_type;

        using abstract_window_type = typename about::abstract_window_type;

        using config_traits_type = typename about::config_traits_type;

        using message_catalog_type = typename about::message_catalog_type;

        using settings_type = typename about::settings_type;


        // constructors and destructor

        impl(const message_catalog_type& message_catalog, const settings_type& settings)
        :
        m_message_catalog(message_catalog),
        m_settings(settings)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            about_dialog_type{ parent, m_message_catalog, m_settings }.do_modal();
        }


    private:
        // types

        using about_dialog_type =
            about_dialog<
                string_type, position_type, dimension_type, dialog_type, message_catalog_type, config_traits_type
            >;


        // variables

        const message_catalog_type& m_message_catalog;

        const settings_type& m_settings;


    };


    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename ConfigTraits,
        typename MessageCatalog
    >
    about<Traits, Position, Dimension, Dialog, ConfigTraits, MessageCatalog>::about(
        const message_catalog_type& message_catalog,
        const settings_type&        settings
    )
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(message_catalog, settings))
    {}

    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename ConfigTraits,
        typename MessageCatalog
    >
    about<Traits, Position, Dimension, Dialog, ConfigTraits, MessageCatalog>::~about()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <
        typename Traits,
        typename Position,
        typename Dimension,
        typename Dialog,
        typename ConfigTraits,
        typename MessageCatalog
    >
    void about<Traits, Position, Dimension, Dialog, ConfigTraits, MessageCatalog>::execute_impl(
        model_type&           model,
        abstract_window_type& parent
    )
    const
    {
        m_p_impl->execute(model, parent);
    }


    template class about<
        traits<
            typename boost::mpl::at<common_type_list, type::size>::type,
            typename boost::mpl::at<common_type_list, type::difference>::type,
            typename boost::mpl::at<common_type_list, type::string>::type,
            typename boost::mpl::at<model_type_list, type::model::operating_distance>::type,
            typename boost::mpl::at<model_type_list, type::model::speed>::type,
            typename boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
            typename boost::mpl::at<ui_type_list, type::ui::abstract_window>::type
        >,
        typename boost::mpl::at<ui_type_list, type::ui::position>::type,
        typename boost::mpl::at<ui_type_list, type::ui::dimension>::type,
        typename boost::mpl::at<ui_type_list, type::ui::dialog>::type,
        typename boost::mpl::at<bobura::setting_type_list, bobura::type::setting::config_traits>::type,
        typename boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
    >;


}}
