/*! \file
    \brief The definition of bobura::command::horizontally_zoom_out.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <cassert>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/command/horizontally_zoom_out.h>
#include <bobura/main_window.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/zoom.h>


namespace bobura { namespace command
{
    class horizontally_zoom_out::impl
    {
    public:
        // types

        using model_type = horizontally_zoom_out::model_type;

        using abstract_window_type = horizontally_zoom_out::abstract_window_type;

        using diagram_view_type = horizontally_zoom_out::diagram_view_type;


        // constructors and destructor

        explicit impl(diagram_view_type& diagram_view)
        :
        m_diagram_view(diagram_view)
        {}


        // functions

        void execute(model_type& model, abstract_window_type& parent)
        const
        {
            boost::ignore_unused(model);

            auto* const p_main_window = dynamic_cast<main_window_type*>(&parent);
            assert(p_main_window);
            zoom_type zoom{ p_main_window->diagram_picture_box(), m_diagram_view };

            zoom.horizontally_zoom_out(true);
        }


    private:
        // types

        using main_window_type = boost::mpl::at<main_window_type_list, type::main_window::main_window>::type;

        using traits_type = boost::mpl::at<view_type_list, type::view::traits>::type;

        using zoom_type = view::diagram::zoom<traits_type, boost::mpl::at<ui_type_list, type::ui::picture_box>::type>;


        // variables

        diagram_view_type& m_diagram_view;


    };


    horizontally_zoom_out::horizontally_zoom_out(diagram_view_type& diagram_view)
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>(diagram_view))
    {}

    horizontally_zoom_out::~horizontally_zoom_out()
    TETENGO2_STDALT_NOEXCEPT
    {}
    
    void horizontally_zoom_out::execute_impl(model_type& model, abstract_window_type& parent)
    const
    {
        m_p_impl->execute(model, parent);
    }


}}
