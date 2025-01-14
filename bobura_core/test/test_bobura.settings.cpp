/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <cstddef>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/settings.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using traits_type_list_type = bobura::type_list::traits<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using position_type = ui_type_list_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using dimension_type = ui_type_list_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using settings_type =
        bobura::settings<string_type, position_type, dimension_type, traits_type_list_type::config_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(settings)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(base_path)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        BOOST_CHECK(settings.base_path() == boost::filesystem::path{ string_type{ TETENGO2_TEXT("path/to") } });

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(input)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            BOOST_CHECK(!settings.input());

            settings.clear_config();
        }
        {
            const std::vector<string_type> arguments{
                string_type{ TETENGO2_TEXT("path/to/exe") }, string_type{ TETENGO2_TEXT("input_file") }
            };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            BOOST_REQUIRE(settings.input());
            BOOST_CHECK(*settings.input() == boost::filesystem::path{ string_type{ TETENGO2_TEXT("input_file") } });

            settings.clear_config();
        }
    }

    BOOST_AUTO_TEST_CASE(message_directory_path)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        BOOST_CHECK(
            settings.message_directory_path() ==
            boost::filesystem::path{ string_type{ TETENGO2_TEXT("path/to/messages") } }
        );

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(image_directory_path)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        BOOST_CHECK(
            settings.image_directory_path() ==
            boost::filesystem::path{ string_type{ TETENGO2_TEXT("path/to/images") } }
        );

        settings.clear_config();
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(main_window_dimension)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            const auto dimension = settings.main_window_dimension();

            //TODO FIX IT BOOST_CHECK(!dimension);

            settings.clear_config();
        }
        {
            const std::vector<string_type> arguments{
                string_type{ TETENGO2_TEXT("path/to/exe") }, string_type{ TETENGO2_TEXT("--dimension=240x120") }
            };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            const auto dimension = settings.main_window_dimension();

            BOOST_REQUIRE(dimension);
            BOOST_CHECK_EQUAL(
                tetengo2::gui::dimension<dimension_type>::width(*dimension).to_pixels<std::size_t>(), 240U
            );
            BOOST_CHECK_EQUAL(
                tetengo2::gui::dimension<dimension_type>::height(*dimension).to_pixels<std::size_t>(), 120U
            );

            settings.clear_config();
        }
        {
            const std::vector<string_type> arguments{
                string_type{ TETENGO2_TEXT("path/to/exe") },
                string_type{ TETENGO2_TEXT("-d") },
                string_type{ TETENGO2_TEXT("240x120") }
            };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            const auto dimension = settings.main_window_dimension();

            BOOST_REQUIRE(dimension);
            BOOST_CHECK_EQUAL(
                tetengo2::gui::dimension<dimension_type>::width(*dimension).to_pixels<std::size_t>(), 240U
            );
            BOOST_CHECK_EQUAL(
                tetengo2::gui::dimension<dimension_type>::height(*dimension).to_pixels<std::size_t>(), 120U
            );

            settings.clear_config();
        }
    }

    BOOST_AUTO_TEST_CASE(set_main_window_dimension)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        settings.set_main_window_dimension(dimension_type{ width_type{ 42 }, height_type{ 24 } });

        const auto dimension = settings.main_window_dimension();

        BOOST_REQUIRE(dimension);
        BOOST_CHECK(tetengo2::gui::dimension<dimension_type>::width(*dimension) == width_type{ 42 });
        BOOST_CHECK(tetengo2::gui::dimension<dimension_type>::height(*dimension) == height_type{ 24 });

        settings.clear_config();
    }
#endif

    BOOST_AUTO_TEST_CASE(main_window_maximized)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        const auto maximized = settings.main_window_maximized();

        //TODO FIX IT BOOST_CHECK(!maximized);

        settings.clear_config();
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(set_main_window_maximized)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.set_main_window_maximized(false);

            const auto maximized = settings.main_window_maximized();

            BOOST_REQUIRE(maximized);
            BOOST_CHECK(!*maximized);

            settings.clear_config();
        }
        {
            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.set_main_window_maximized(true);

            const auto maximized = settings.main_window_maximized();

            BOOST_REQUIRE(maximized);
            BOOST_CHECK(*maximized);

            settings.clear_config();
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(property_bar_width)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        const auto width = settings.property_bar_width();

        //TODO FIX IT BOOST_CHECK(!width);

        settings.clear_config();
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(set_property_bar_width)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        settings.set_property_bar_width(width_type{ 42 });

        const auto width = settings.property_bar_width();

        BOOST_REQUIRE(width);
        BOOST_CHECK(*width == width_type{ 42 });

        settings.clear_config();
    }
#endif

    BOOST_AUTO_TEST_CASE(property_bar_minimized)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        const auto minimized = settings.property_bar_minimized();

        //TODO FIX IT BOOST_CHECK(!minimized);

        settings.clear_config();
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(set_property_bar_minimized)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.set_property_bar_minimized(false);

            const auto minimized = settings.property_bar_minimized();

            BOOST_REQUIRE(minimized);
            BOOST_CHECK(!*minimized);

            settings.clear_config();
        }
        {
            const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
            settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

            settings.set_property_bar_minimized(true);

            const auto minimized = settings.property_bar_minimized();

            BOOST_REQUIRE(minimized);
            BOOST_CHECK(*minimized);

            settings.clear_config();
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(property_bar_splitter_position)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        const auto position = settings.property_bar_splitter_position();

        //TODO FIX IT BOOST_CHECK(!position);

        settings.clear_config();
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(set_property_bar_splitter_position)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };

        settings.set_property_bar_splitter_position(left_type{ 42 });

        const auto position = settings.property_bar_splitter_position();

        BOOST_REQUIRE(position);
        BOOST_CHECK(*position == left_type{ 42 });

        settings.clear_config();
    }

    BOOST_AUTO_TEST_CASE(clear_config)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<string_type> arguments{ string_type{ TETENGO2_TEXT("path/to/exe") } };
        settings_type settings{ arguments, string_type{ TETENGO2_TEXT("test_bobura") } };
        settings.set_main_window_maximized(true);

        settings.clear_config();

        BOOST_CHECK(!settings.main_window_maximized());

        settings.clear_config();
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
