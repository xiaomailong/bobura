/*! \file
    \brief The definition of bobura::command::open_www_tetengo_org.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/predef.h>

#include <tetengo2.h>

#include <bobura/command/open_www_tetengo_org.h>
#include <bobura/type_list.h>


namespace bobura { namespace command
{
    template <typename Traits, typename Shell>
    class open_www_tetengo_org<Traits, Shell>::impl
    {
    public:
        // types

        using shell_type = typename open_www_tetengo_org::shell_type;

        using abstract_window_type = typename open_www_tetengo_org::abstract_window_type;

        using model_type = typename open_www_tetengo_org::model_type;


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model, parent);

            shell_type::instance().execute(string_type{ TETENGO2_TEXT("http://www.tetengo.org/") });
        }


    private:
        // types

        using string_type = typename shell_type::string_type;


    };


    template <typename Traits, typename Shell>
    open_www_tetengo_org<Traits, Shell>::open_www_tetengo_org()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <typename Traits, typename Shell>
    open_www_tetengo_org<Traits, Shell>::~open_www_tetengo_org()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    template <typename Traits, typename Shell>
    void open_www_tetengo_org<Traits, Shell>::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class open_www_tetengo_org<
        typename application::traits_type_list_type::command_type, typename application::ui_type_list_type::shell_type
    >;
#endif

    template class open_www_tetengo_org<
        typename test::traits_type_list_type::command_type, typename test::ui_type_list_type::shell_type
    >;


}}
