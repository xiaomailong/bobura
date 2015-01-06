/*! \file
    \brief Test of class bobura::command::font_color.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <bobura/command/font_color.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using common_dialog_type_list_type = bobura::type_list::common_dialog<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using font_color_command_type =
        bobura::command::font_color<
            traits_type_list_type::command_type,
            ui_type_list_type::dialog_type,
            ui_type_list_type::point_unit_size_type,
            ui_type_list_type::color_type,
            ui_type_list_type::fast_canvas_type,
            common_dialog_type_list_type::font_type,
            common_dialog_type_list_type::color_type,
            message_catalog_type,
            traits_type_list_type::dialog_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(font_color)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog{};
        const font_color_command_type command{ message_catalog };
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
