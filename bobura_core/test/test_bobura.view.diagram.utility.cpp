/*! \file
    \brief Test of class bobura::view::diagram::utility.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <vector>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/model/train_info/time.h>
#include <bobura/model/train_info/time_span.h>
#include <bobura/type_list.h>
#include <bobura/view/diagram/utility.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using window_type = ui_type_list_type::window_type;

    using picture_box_type = ui_type_list_type::picture_box_type;

    using position_type = picture_box_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using canvas_type = ui_type_list_type::canvas_type;

    using time_span_type = bobura::model::train_info::time_span<difference_type>;

    using time_type = bobura::model::train_info::time<size_type, difference_type>;

    using unit_size_type = canvas_type::unit_size_type;


}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
    // test cases

    BOOST_AUTO_TEST_CASE(time_to_left)
    {
        BOOST_TEST_PASSPOINT();

        const auto result =
            bobura::view::diagram::time_to_left(
                time_type{ 1 }, time_span_type{ 2 }, 0, left_type{ 3 }, left_type{ 4 }, left_type{ 5 }
            );

        BOOST_CHECK_EQUAL(result.value(), (left_type::value_type{ 86435, 36 }));
    }

    BOOST_AUTO_TEST_CASE(station_index_to_top)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<top_type> station_positions{ top_type{ 0 }, top_type{ 42 } };

        const auto result =
            bobura::view::diagram::station_index_to_top(
                station_positions, size_type{ 1 }, top_type{ 2 }, top_type{ 3 }, top_type{ 4 }
            );

        BOOST_CHECK_EQUAL(result.value(), 47);
    }

    BOOST_AUTO_TEST_CASE(normal_line_width)
    {
        BOOST_TEST_PASSPOINT();

        bobura::view::diagram::normal_line_width<unit_size_type>();
    }

    BOOST_AUTO_TEST_CASE(bold_line_width)
    {
        BOOST_TEST_PASSPOINT();

        bobura::view::diagram::bold_line_width<unit_size_type>();
    }

    BOOST_AUTO_TEST_CASE(selected_line_margin)
    {
        BOOST_TEST_PASSPOINT();

        bobura::view::diagram::selected_line_margin<unit_size_type>();
    }

    BOOST_AUTO_TEST_CASE(draw_selectable_line)
    {
        BOOST_TEST_PASSPOINT();

        window_type window{};
        const picture_box_type picture_box{ window, picture_box_type::scroll_bar_style_type::both };
        const auto p_canvas = picture_box.create_canvas();

        bobura::view::diagram::draw_selectable_line(
            *p_canvas,
            position_type{ left_type{ 24 }, top_type{ 24 } },
            position_type{ left_type{ 42 }, top_type{ 42 } },
            false
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
