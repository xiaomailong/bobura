/*! \file
    \brief Test of class bobura::model::serializer::exec_json_reading_task.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/exec_json_reading_task.h>
#include <bobura/model/timetable.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using locale_type_list_type = bobura::type_list::locale<detail_type_list_type>;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using font_type = ui_type_list_type::font_type;

    using timetable_type =
        bobura::model::timetable<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

    using window_type = ui_type_list_type::window_type;

    using dialog_type = ui_type_list_type::dialog_type;

    using timer_type = ui_type_list_type::timer_type;

    using system_color_set_type = ui_type_list_type::system_color_set_type;

    using message_catalog_type = locale_type_list_type::message_catalog_type;

    using exec_json_reading_task_type =
        bobura::model::serializer::exec_json_reading_task<
            size_type,
            difference_type,
            string_type,
            operating_distance_type,
            speed_type,
            font_type,
            dialog_type,
            timer_type,
            system_color_set_type,
            message_catalog_type
        >;

    using promise_type = exec_json_reading_task_type::promise_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(exec_json_reading_task)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog{};
        const exec_json_reading_task_type task{ parent, message_catalog };
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const message_catalog_type message_catalog{};
            const exec_json_reading_task_type task{ parent, message_catalog };

            auto p_result = task([](promise_type&){ return std::unique_ptr<timetable_type>{}; });
            BOOST_CHECK(!p_result);
        }
        {
            window_type parent{};
            const message_catalog_type message_catalog{};
            const exec_json_reading_task_type task{ parent, message_catalog };

            auto p_result =
                task(
                    [](promise_type&)
                    {
                        auto p_timetable = tetengo2::stdalt::make_unique<timetable_type>();
                        p_timetable->set_line_name(string_type{ TETENGO2_TEXT("hoge") });
                        return std::move(p_timetable);
                    }
                );
            BOOST_REQUIRE(p_result);
            BOOST_CHECK(p_result->line_name() == string_type{ TETENGO2_TEXT("hoge") });
        }
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
