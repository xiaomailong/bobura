/*! \file
    \brief Test of class bobura::model::serializer::reader_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <memory>
#include <utility>

#include <boost/predef.h>
#include <boost/rational.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/reader_set.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common<detail_type_list_type>;

    using ui_type_list_type = test_bobura::model::type_list::ui<detail_type_list_type>;

    using size_type_ = common_type_list_type::size_type;

    using difference_type_ = common_type_list_type::difference_type;

    using string_type_ = common_type_list_type::string_type;

    using operating_distance_type_ = common_type_list_type::operating_distance_type;

    using speed_type_ = common_type_list_type::speed_type;

    using font_type_ = ui_type_list_type::font_type;

    using window_type = ui_type_list_type::window_type;

    using input_stream_iterator_type =
        tetengo2::observable_forward_iterator<
            boost::spirit::multi_pass<std::istreambuf_iterator<common_type_list_type::io_string_type::value_type>>
        >;

    using encoder_type_ = common_type_list_type::encoder_type;

    using message_catalog_type_ =
        tetengo2::message::message_catalog<
            input_stream_iterator_type, string_type_, size_type_, encoder_type_, encoder_type_
        >;

    using io_encoder_type = common_type_list_type::io_encoder_type;

    using abstract_window_type_ = ui_type_list_type::abstract_window_type;

    struct exec_json_reading_task_type
    {
        using size_type = size_type_;

        using difference_type = difference_type_;

        using string_type = string_type_;

        using operating_distance_type = operating_distance_type_;

        using speed_type = speed_type_;

        using font_type = font_type_;

        using timetable_type =
            bobura::model::timetable<
                size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
            >;

        using abstract_window_type = abstract_window_type_;

        using message_catalog_type = message_catalog_type_;

        using promise_type = tetengo2::concurrent::progressive_promise<int, boost::rational<std::size_t>>;

        using read_timetable_type = std::function<std::unique_ptr<timetable_type> (promise_type& promise)>;

        exec_json_reading_task_type(abstract_window_type&, const message_catalog_type&)
        {}

        std::unique_ptr<timetable_type> operator()(read_timetable_type read_timetable)
        const
        {
            promise_type promise{ 0 };
            return read_timetable(promise);
        }

    };

    struct select_oudia_diagram_type
    {
        using size_type = size_type_;

        using string_type = string_type_;

        using encoder_type = encoder_type_;

        using abstract_window_type = abstract_window_type_;

        using message_catalog_type = message_catalog_type_;

        string_type m_wanted;

        select_oudia_diagram_type(abstract_window_type&, string_type, const message_catalog_type&)
        :
        m_wanted()
        {}

        explicit select_oudia_diagram_type(string_type wanted)
        :
        m_wanted(std::move(wanted))
        {}

        template <typename Iterator>
        Iterator operator()(const Iterator first, const Iterator last)
        const
        {
            return std::find(first, last, m_wanted);
        }

    };

    using reader_set_type =
        bobura::model::serializer::reader_set<
            size_type_,
            difference_type_,
            string_type_,
            input_stream_iterator_type,
            operating_distance_type_,
            speed_type_,
            exec_json_reading_task_type,
            select_oudia_diagram_type,
            font_type_,
            io_encoder_type,
            io_encoder_type
        >;


}


#if 0 // until reader_set implementation is moved to .cpp.
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader_set)
    // test cases

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(create_readers)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        string_type_ file_name{ TETENGO2_TEXT("hoge") };
        const message_catalog_type_ message_catalog{};
        const auto p_readers = reader_set_type::create_readers(parent, std::move(file_name), message_catalog);

        BOOST_REQUIRE(!p_readers.empty());
        BOOST_CHECK(p_readers[0]);
    }
#endif


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
