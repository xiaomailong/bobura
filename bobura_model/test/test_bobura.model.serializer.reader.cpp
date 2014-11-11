/*! \file
    \brief Test of class bobura::model::serializer::reader.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <sstream>

#include <boost/core/ignore_unused.hpp>
#include <boost/predef.h>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/reader.h>
#include <bobura/model/timetable.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common<detail_type_list_type>;

    using ui_type_list_type = test_bobura::model::type_list::ui<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using string_type = common_type_list_type::string_type;

    using operating_distance_type = common_type_list_type::operating_distance_type;

    using speed_type = common_type_list_type::speed_type;

    using font_type = ui_type_list_type::font_type;

    using timetable_type =
        bobura::model::timetable<
            size_type, difference_type, string_type, operating_distance_type, speed_type, font_type
        >;

    using input_stream_iterator_type =
        boost::spirit::multi_pass<std::istreambuf_iterator<common_type_list_type::io_string_type::value_type>>;

    using reader_type =
        bobura::model::serializer::reader<
            size_type,
            difference_type,
            string_type,
            input_stream_iterator_type,
            operating_distance_type,
            speed_type,
            font_type
        >;

    using error_type = reader_type::error_type;

    class concrete_reader : public reader_type
    {
    public:
        virtual ~concrete_reader()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


    private:
        virtual bool selects_impl(const iterator first, const iterator last)
        override
        {
            boost::ignore_unused(first, last);

            return string_type{ first, last } == string_type{ TETENGO2_TEXT("hoge") };
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        override
        {
            boost::ignore_unused(first, last, error);

            return tetengo2::stdalt::make_unique<timetable_type>();
        }


    };

}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_reader reader{};
    }

#if !( \
    BOOST_OS_LINUX && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 7, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(4, 8, 0)) \
    )
    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        concrete_reader reader{};

        {
            std::istringstream input_stream{ "hoge" };
            BOOST_CHECK(
                reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            std::istringstream input_stream{ "fuga" };
            BOOST_CHECK(
                !reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        concrete_reader reader{};
        std::istringstream input_stream{ "hoge" };
        auto error = error_type::none;
        const auto p_timetable =
            reader.read(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                error
            );

        BOOST_REQUIRE(p_timetable);
        BOOST_CHECK(error == error_type::none);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
