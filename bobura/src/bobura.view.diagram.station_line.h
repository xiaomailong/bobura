/*! \file
    \brief The definition of bobura::view::diagram::station_line.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_STATIONLINE_H)
#define BOBURA_VIEW_DIAGRAM_STATIONLINE_H

#include <algorithm>
#include <cassert>
#include <stdexcept>
//#include <utility>
#include <vector>

#include <boost/range/adaptors.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.gui.measure.h>
#include <tetengo2.utility.h>

#include "bobura.view.diagram.item.h"
#include "bobura.view.diagram.utility.h"


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a station line in the diagram view.

        \tparam Model     A model type.
        \tparam Selection A selection type.
        \tparam Canvas    A canvas type.
    */
    template <typename Model, typename Selection, typename Canvas>
    class station_line : public item<Selection, Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The station type.
        typedef typename model_type::timetable_type::station_location_type::station_type station_type;

        //! The font and color type.
        typedef typename model_type::timetable_type::font_color_set_type::font_color_type font_color_type;

        //! The selection type.
        typedef Selection selection_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The string type.
        typedef typename canvas_type::string_type string_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The left type.
        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        //! The top type.
        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        //! The dimension type.
        typedef typename canvas_type::dimension_type dimension_type;

        //! The base type.
        typedef item<selection_type, canvas_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a station line.

            \param station              A station.
            \param selection            A selection.
            \param right                A right position.
            \param station_header_right A station header right position.
            \param top                  A top position.
            \param font_color           A font and color.
        */
        station_line(
            const station_type&    station,
            selection_type&        selection,
            const left_type&       right,
            const left_type&       station_header_right,
            top_type               top,
            const font_color_type& font_color
        )
        :
        base_type(selection),
        m_p_station(&station),
        m_right(right),
        m_station_header_right(station_header_right),
        m_top(std::move(top)),
        m_p_font_color(&font_color)
        {}

        /*!
            \brief Moves a station line.

            \param another Another station line.
        */
        station_line(station_line&& another)
        :
        base_type(another.selection()),
        m_p_station(another.m_p_station),
        m_right(std::move(another.m_right)),
        m_station_header_right(another.m_station_header_right),
        m_top(std::move(another.m_top)),
        m_p_font_color(another.m_p_font_color)
        {}

        /*!
            \brief Destroys the station line.
        */
        virtual ~station_line()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Assigns a station line.

            \param another Another station line.

            \return This station line.
        */
        station_line& operator=(station_line&& another)
        {
            if (&another == this)
                return *this;

            m_p_station = another.m_p_station;
            m_right = std::move(another.m_right);
            m_station_header_right = std::move(another.m_station_header_right);
            m_top = std::move(another.m_top);
            m_p_font_color = another.m_p_font_color;
            base_type::operator=(std::move(another));

            return *this;
        }


    private:
        // variables

        const station_type* m_p_station;

        left_type m_right;

        left_type m_station_header_right;

        top_type m_top;

        const font_color_type* m_p_font_color;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_font(m_p_font_color->font());
            canvas.set_color(m_p_font_color->color());

            draw_selectable_line(
                canvas, position_type(left_type(0), m_top), position_type(m_right, m_top), this->selected()
            );

            const auto& name = m_p_station->name();
            const auto name_dimension = canvas.calc_text_dimension(name);
            canvas.draw_text(
                name,
                position_type(
                    left_type(0),
                    m_top - top_type::from(tetengo2::gui::dimension<dimension_type>::height(name_dimension))
                )
            );
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        {
            const auto& x = tetengo2::gui::position<position_type>::left(position);
            const auto& y = tetengo2::gui::position<position_type>::top(position);
            if (
                (left_type(0) <= x && x <= m_station_header_right) &&
                (m_top - selected_line_margin<top_type>() <= y && y <= m_top + selected_line_margin<top_type>())
            )
            {
                return this;
            }
            else
            {
                return nullptr;
            }
        }

        virtual bool selected_impl()
        const
        {
            return this->selection().selected(*m_p_station);
        }

        virtual void select_impl(const bool switch_selection_style)
        {
            tetengo2::suppress_unused_variable_warning(switch_selection_style);

            this->selection().select(*m_p_station);
        }


    };


     /*!
        \brief The class template for a station line list in the diagram view.

        \tparam Model               A model type.
        \tparam Selection           A selection type.
        \tparam Canvas              A canvas type.
        \tparam StationGradeTypeSet A station grade type set type.
    */
    template <typename Model, typename Selection, typename Canvas, typename StationGradeTypeSet>
    class station_line_list : public item<Selection, Canvas>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;
        
        //! The time type.
        typedef typename model_type::timetable_type::train_type::stop_type::time_type time_type;

        //! The time span type.
        typedef typename time_type::time_span_type time_span_type;

        //! The selection type.
        typedef Selection selection_type;

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The position type.
        typedef typename canvas_type::position_type position_type;

        //! The left type.
        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        //! The top type.
        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        //! The dimension type.
        typedef typename canvas_type::dimension_type dimension_type;

        //! The width type.
        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        //! The height type.
        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        //! The horizontal scale type.
        typedef typename width_type::value_type horizontal_scale_type;

        //! The vertical scale type.
        typedef typename height_type::value_type vertical_scale_type;

        //! The base type.
        typedef item<selection_type, canvas_type> base_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;


        // constructors and destructor

        /*!
            \brief Creates a station line list.

            \param model                A model.
            \param time_offset          A time offset.
            \param selection            A selection.
            \param canvas_dimension     A canvas dimension.
            \param scroll_bar_position  A scroll bar position.
            \param station_header_right A right position of the station header.
            \param header_bottom        A bottom position of the header.
            \param time_header_height   A time header height.
            \param horizontal_scale     A horizontal scale.
            \param station_positions    Station positions.
        */
        station_line_list(
            const model_type&            model,
            const time_span_type&        time_offset,
            selection_type&              selection,
            const dimension_type&        canvas_dimension,
            const position_type&         scroll_bar_position,
            const left_type&             station_header_right,
            const top_type&              header_bottom,
            const height_type&           time_header_height,
            const horizontal_scale_type& horizontal_scale,
            const std::vector<top_type>& station_positions
        )
        :
        base_type(selection),
        m_station_lines(
            make_station_lines(
                model,
                time_offset,
                selection,
                canvas_dimension,
                scroll_bar_position,
                station_header_right,
                header_bottom,
                time_header_height,
                horizontal_scale,
                station_positions
            )
        )
        {}

        /*!
            \brief Moves a station line list.

            \param another Another station line list.
        */
        station_line_list(station_line_list&& another)
        :
        base_type(another.selection()),
        m_station_lines(std::move(another.m_station_lines))
        {}

        /*!
            \brief Destroys the station line list.
        */
        virtual ~station_line_list()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Assigns a station line list.

            \param another Another station line list.

            \return This station line list.
        */
        station_line_list& operator=(station_line_list&& another)
        {
            if (&another == this)
                return *this;

            m_station_lines = std::move(another.m_station_lines);
            base_type::operator=(std::move(another));

            return *this;
        }


    private:
        // types

        typedef station_line<model_type, selection_type, canvas_type> station_line_type;

        typedef typename model_type::timetable_type timetable_type;

        typedef typename timetable_type::font_color_set_type font_color_set_type;

        typedef typename font_color_set_type::font_color_type font_color_type;

        typedef typename timetable_type::station_location_type station_location_type;

        typedef typename station_location_type::station_type station_type;

        typedef typename station_type::grade_type station_grade_type;

        typedef typename canvas_type::size_type size_type;

        typedef typename canvas_type::string_type string_type;


        // static functions

        static std::vector<station_line_type> make_station_lines(
            const model_type&            model,
            const time_span_type&        time_offset,
            selection_type&              selection,
            const dimension_type&        canvas_dimension,
            const position_type&         scroll_bar_position,
            const left_type&             station_header_right,
            const top_type&              header_bottom,
            const height_type&           time_header_height,
            const horizontal_scale_type& horizontal_scale,
            const std::vector<top_type>& station_positions
        )
        {
            const auto canvas_right =
                left_type::from(tetengo2::gui::dimension<dimension_type>::width(canvas_dimension));
            const auto horizontal_scale_left = left_type::from(width_type(horizontal_scale));
            const auto last_time_position =
                time_to_left(
                    time_type(24 * 60 * 60 + time_offset.seconds()),
                    time_offset,
                    1,
                    tetengo2::gui::position<position_type>::left(scroll_bar_position),
                    station_header_right,
                    horizontal_scale_left
                );
            const auto line_right = std::min(canvas_right, last_time_position);

            const auto canvas_top = header_bottom + top_type::from(time_header_height);
            const auto canvas_bottom =
                top_type::from(tetengo2::gui::dimension<dimension_type>::height(canvas_dimension));

            std::vector<station_line_type> station_lines;
            station_lines.reserve(station_positions.size());
            for (decltype(station_positions.size()) i = 0; i < station_positions.size(); ++i)
            {
                const auto& position = station_positions[i];
                auto line_position =
                    position + canvas_top - tetengo2::gui::position<position_type>::top(scroll_bar_position);
                if (line_position < canvas_top)
                    continue;
                if (line_position > canvas_bottom)
                    break;

                const auto& station = model.timetable().station_locations()[i].station();
                station_lines.push_back(
                    station_line_type(
                        station,
                        selection,
                        line_right,
                        station_header_right,
                        std::move(line_position),
                        select_station_font_color(model.timetable().font_color_set(), station.grade())
                    )
                );
            }
            station_lines.shrink_to_fit();

            return std::move(station_lines);
        }

        static const font_color_type& select_station_font_color(
            const font_color_set_type& font_color_set,
            const station_grade_type&  grade
        )
        {
            if      (&grade == &station_grade_type_set_type::local_type::instance())
                return font_color_set.local_station();
            else if (&grade == &station_grade_type_set_type::principal_type::instance())
                return font_color_set.principal_station();
            else if (&grade == &station_grade_type_set_type::local_terminal_type::instance())
                return font_color_set.local_terminal_station();
            else if (&grade == &station_grade_type_set_type::principal_terminal_type::instance())
                return font_color_set.principal_terminal_station();

            assert(false);
            BOOST_THROW_EXCEPTION(std::invalid_argument("Unknown station grade."));
        }


        // variables

        std::vector<station_line_type> m_station_lines;


        // virtual functions

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {
            canvas.set_line_width(normal_line_width<size_type>());
            canvas.set_line_style(canvas_type::line_style_type::solid);

            for (const station_line_type& station_line: m_station_lines)
                station_line.draw_on(canvas);
        }

        virtual base_type* p_item_by_position_impl(const position_type& position)
        {
            for (station_line_type& station_line: boost::adaptors::reverse(m_station_lines))
            {
                auto* const p_item = station_line.p_item_by_position(position);
                if (p_item)
                    return p_item;
            }

            return nullptr;
        }


    };


}}}


#endif
