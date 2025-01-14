/*! \file
    \brief The definition of bobura::view::diagram::header.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/type_list.h>
#include <bobura/view/diagram/header.h>


namespace bobura { namespace view { namespace diagram
{
    template <typename Traits>
    class company_line_name_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using string_type = typename traits_type::string_type;

        using canvas_type = typename traits_type::canvas_type;

        using font_type = typename canvas_type::font_type;

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using dimension_type = typename canvas_type::dimension_type;

        using selection_type = typename company_line_name_header::selection_type;


        // constructors and destructor

        impl(
            selection_type&,
            string_type       company_line_name,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        )
        :
        m_company_line_name(std::move(company_line_name)),
        m_p_font(&font),
        m_p_color(&color),
        m_position(std::move(position)),
        m_dimension(std::move(dimension))
        {}

        impl(impl&& another)
        :
        m_company_line_name(std::move(another.m_company_line_name)),
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_company_line_name = std::move(another.m_company_line_name);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);
            canvas.draw_text(m_company_line_name, m_position);
        }


    private:
        // variables

        string_type m_company_line_name;

        const font_type* m_p_font;

        const color_type* m_p_color;

        position_type m_position;

        dimension_type m_dimension;


    };


    template <typename Traits>
    company_line_name_header<Traits>::company_line_name_header(
        selection_type&   selection,
        string_type       company_line_name,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension
    )
    :
    base_type(selection),
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            selection, std::move(company_line_name), font, color, std::move(position), std::move(dimension)
        )
    )
    {}

    template <typename Traits>
    company_line_name_header<Traits>::company_line_name_header(company_line_name_header&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    company_line_name_header<Traits>::~company_line_name_header()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <typename Traits>
    company_line_name_header<Traits>& company_line_name_header<Traits>::operator=(company_line_name_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void company_line_name_header<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(canvas);
    }


    template <typename Traits>
    class note_header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using string_type = typename traits_type::string_type;

        using canvas_type = typename traits_type::canvas_type;

        using font_type = typename canvas_type::font_type;

        using color_type = typename canvas_type::color_type;

        using position_type = typename canvas_type::position_type;

        using dimension_type = typename canvas_type::dimension_type;

        using selection_type = typename note_header::selection_type;


        // constructors and destructor

        impl(
            selection_type&,
            string_type       note,
            const font_type&  font,
            const color_type& color,
            position_type     position,
            dimension_type    dimension
        )
        :
        m_note(std::move(note)),
        m_p_font(&font),
        m_p_color(&color),
        m_position(std::move(position)),
        m_dimension(std::move(dimension))
        {}

        impl(impl&& another)
        :
        m_note(std::move(another.m_note)),
        m_p_font(another.m_p_font),
        m_p_color(another.m_p_color),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_note = std::move(another.m_note);
            m_p_font = another.m_p_font;
            m_p_color = another.m_p_color;
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);

            return *this;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_font(*m_p_font);
            canvas.set_color(*m_p_color);
            canvas.draw_text(m_note, m_position);
        }


    private:
        // variables

        string_type m_note;

        const font_type* m_p_font;

        const color_type* m_p_color;

        position_type m_position;

        dimension_type m_dimension;


    };


    template <typename Traits>
    note_header<Traits>::note_header(
        selection_type&   selection,
        string_type       note,
        const font_type&  font,
        const color_type& color,
        position_type     position,
        dimension_type    dimension
    )
    :
    base_type(selection),
    m_p_impl(
        tetengo2::stdalt::make_unique<impl>(
            selection, std::move(note), font, color, std::move(position), std::move(dimension)
        )
    )
    {}

    template <typename Traits>
    note_header<Traits>::note_header(note_header&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    note_header<Traits>::~note_header()
    TETENGO2_STDALT_NOEXCEPT
    {}


    template <typename Traits>
    note_header<Traits>& note_header<Traits>::operator=(note_header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    void note_header<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(canvas);
    }


    template <typename Traits>
    class header<Traits>::impl : private boost::noncopyable
    {
    public:
        // types

        using traits_type = Traits;

        using canvas_type = typename traits_type::canvas_type;

        using dimension_type = typename canvas_type::dimension_type;

        using selection_type = typename header::selection_type;

        using model_type = typename header::model_type;


        // constructors and destructor

        impl(
            const model_type&     model,
            selection_type&       selection,
            canvas_type&          canvas,
            const dimension_type& canvas_dimension
        )
        :
        m_p_company_line_name_header(),
        m_p_note_header(),
        m_position(left_type{ 0 }, top_type{ 0 }),
        m_dimension(width_type{ 0 }, height_type{ 0 })
        {
            auto company_line_name = make_company_line_name(model);
            const auto& company_line_name_font = model.timetable().font_color_set().company_line_name().font();
            auto note = make_note(model);
            const auto& note_font = model.timetable().font_color_set().note().font();
            position_type company_line_name_position{ left_type{ 0 }, top_type{ 0 } };
            dimension_type company_line_name_dimension{ width_type{ 0 }, height_type{ 0 } };
            position_type note_position{ left_type{ 0 }, top_type{ 0 } };
            dimension_type note_dimension{ width_type{ 0 }, height_type{ 0 } };
            calculate_positions_and_dimensions(
                canvas,
                canvas_dimension,
                company_line_name,
                company_line_name_font,
                note,
                note_font,
                company_line_name_position,
                company_line_name_dimension,
                note_position,
                note_dimension,
                m_position,
                m_dimension
            );

            const auto& company_line_name_color = model.timetable().font_color_set().company_line_name().color();
            const auto& note_color = model.timetable().font_color_set().note().color();
            m_p_company_line_name_header =
                tetengo2::stdalt::make_unique<company_line_name_header_type>(
                    selection,
                    std::move(company_line_name),
                    company_line_name_font,
                    company_line_name_color,
                    std::move(company_line_name_position),
                    std::move(company_line_name_dimension)
                );
            m_p_note_header =
                tetengo2::stdalt::make_unique<note_header_type>(
                    selection,
                    std::move(note),
                    note_font,
                    note_color,
                    std::move(note_position),
                    std::move(note_dimension)
                );                    
        }

        impl(impl&& another)
        :
        m_p_company_line_name_header(std::move(another.m_p_company_line_name_header)),
        m_p_note_header(std::move(another.m_p_note_header)),
        m_position(std::move(another.m_position)),
        m_dimension(std::move(another.m_dimension))
        {}


        // functions

        impl& operator=(impl&& another)
        {
            if (&another == this)
                return *this;

            m_p_company_line_name_header = std::move(another.m_p_company_line_name_header);
            m_p_note_header = std::move(another.m_p_note_header);
            m_position = std::move(another.m_position);
            m_dimension = std::move(another.m_dimension);

            return *this;
        }

        const dimension_type& dimension()
        const
        {
            return m_dimension;
        }

        void draw_on_impl(canvas_type& canvas)
        const
        {
            assert(m_p_company_line_name_header);
            m_p_company_line_name_header->draw_on(canvas);

            assert(m_p_note_header);
            m_p_note_header->draw_on(canvas);
        }


    private:
        // types

        using company_line_name_header_type = company_line_name_header<traits_type>;

        using note_header_type = note_header<traits_type>;

        using string_type = typename traits_type::string_type;

        using font_type = typename canvas_type::font_type;

        using position_type = typename canvas_type::position_type;

        using left_type = typename tetengo2::gui::position<position_type>::left_type;

        using top_type = typename tetengo2::gui::position<position_type>::top_type;

        using width_type = typename tetengo2::gui::dimension<dimension_type>::width_type;

        using height_type = typename tetengo2::gui::dimension<dimension_type>::height_type;


        // static functions

        static string_type make_company_line_name(const model_type& model)
        {
            return
                model.timetable().company_name() +
                (model.timetable().company_name().empty() ? string_type{} : string_type{ TETENGO2_TEXT(" ") }) +
                model.timetable().line_name();
        }

        static string_type make_note(const model_type& model)
        {
            return model.timetable().note();
        }

        static void calculate_positions_and_dimensions(
            canvas_type&          canvas,
            const dimension_type& canvas_dimension,
            const string_type&    company_line_name,
            const font_type&      company_line_name_font,
            const string_type&    note,
            const font_type&      note_font,
            position_type&        company_line_name_position,
            dimension_type&       company_line_name_dimension,
            position_type&        note_position,
            dimension_type&       note_dimension,
            position_type&        position,
            dimension_type&       dimension
        )
        {
            const auto& canvas_width = tetengo2::gui::dimension<dimension_type>::width(canvas_dimension);

            canvas.set_font(company_line_name_font);
            auto company_line_name_dimension_ = canvas.calc_text_dimension(company_line_name);
            const auto& company_line_name_width =
                tetengo2::gui::dimension<dimension_type>::width(company_line_name_dimension_);
            const auto& company_line_name_height =
                company_line_name.empty() ?
                height_type{ 0 } : tetengo2::gui::dimension<dimension_type>::height(company_line_name_dimension_);

            canvas.set_font(note_font);
            const auto note_dimension_ = canvas.calc_text_dimension(note);
            const auto& note_width = tetengo2::gui::dimension<dimension_type>::width(note_dimension_);
            const auto& note_height =
                note.empty() ? height_type{ 0 } : tetengo2::gui::dimension<dimension_type>::height(note_dimension_);

            position_type company_line_name_position_{ left_type{ 0 }, top_type{ 0 } };
            position_type note_position_{ left_type{ 0 }, top_type{ 0 } };
            width_type header_width{ 0 };
            height_type header_height{ 0 };
            if (company_line_name_width + note_width <= canvas_width)
            {
                header_width = canvas_width;

                const auto height_diff = top_type::from(company_line_name_height) - top_type::from(note_height);
                if (height_diff > 0)
                {
                    const top_type note_top{ height_diff / top_type{ 2 } };
                    company_line_name_position_ = position_type{ left_type{ 0 }, top_type{ 0 } };
                    note_position_ = position_type{ left_type::from(canvas_width - note_width), note_top };
                    header_height = company_line_name_height;
                }
                else
                {
                    const top_type company_line_name_top{ (top_type{ 0 } - height_diff) / top_type{ 2 } };
                    company_line_name_position_ = position_type{ left_type{ 0 }, company_line_name_top };
                    note_position_ = position_type{ left_type::from(canvas_width - note_width), top_type{ 0 } };
                    header_height = note_height;
                }
            }
            else
            {
                company_line_name_position_ = position_type{ left_type{ 0 }, top_type{ 0 } };
                note_position_ = position_type{ left_type{ 0 }, top_type::from(company_line_name_height) };
                header_width = std::max(company_line_name_width, note_width);
                header_height = company_line_name_height + note_height;
            }

            company_line_name_position = std::move(company_line_name_position_);
            company_line_name_dimension = std::move(company_line_name_dimension_);
            note_position = std::move(note_position_);
            note_dimension = std::move(note_dimension_);
            position = position_type{ left_type{ 0 }, top_type{ 0 } };
            dimension = dimension_type{ std::move(header_width), std::move(header_height) };
        }


        // variables

        std::unique_ptr<company_line_name_header_type> m_p_company_line_name_header;

        std::unique_ptr<note_header_type> m_p_note_header;

        position_type m_position;

        dimension_type m_dimension;


    };


    template <typename Traits>
    header<Traits>::header(
        const model_type&     model,
        selection_type&       selection,
        canvas_type&          canvas,
        const dimension_type& canvas_dimension
    )
    :
    base_type(selection),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(model, selection, canvas, canvas_dimension))
    {}

    template <typename Traits>
    header<Traits>::header(header&& another)
    :
    base_type(another.get_selection()),
    m_p_impl(tetengo2::stdalt::make_unique<impl>(std::move(*another.m_p_impl)))
    {}

    template <typename Traits>
    header<Traits>::~header()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <typename Traits>
    header<Traits>& header<Traits>::operator=(header&& another)
    {
        if (&another == this)
            return *this;

        *m_p_impl = std::move(*another.m_p_impl);
        base_type::operator=(std::move(another));

        return *this;
    }

    template <typename Traits>
    const typename header<Traits>::dimension_type& header<Traits>::dimension()
    const
    {
        return m_p_impl->dimension();
    }

    template <typename Traits>
    void header<Traits>::draw_on_impl(canvas_type& canvas)
    const
    {
        m_p_impl->draw_on_impl(canvas);
    }

        
    namespace
    {
#if BOOST_COMP_MSVC
        namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class company_line_name_header<typename application::traits_type_list_type::diagram_view_type>;

    template class note_header<typename application::traits_type_list_type::diagram_view_type>;

    template class header<typename application::traits_type_list_type::diagram_view_type>;
#endif

    template class company_line_name_header<typename test::traits_type_list_type::diagram_view_type>;

    template class note_header<typename test::traits_type_list_type::diagram_view_type>;

    template class header<typename test::traits_type_list_type::diagram_view_type>;


}}}
