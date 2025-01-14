/*! \file
    \brief Test of class bobura::model::serializer::bzip2_reader.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <sstream>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/bzip2_reader.h>
#include <bobura/model/timetable.h>
#include <bobura/type_list.h>


namespace
{
    // types

    using detail_type_list_type = bobura::type_list::detail_for_test;

    using common_type_list_type = bobura::type_list::common;

    using ui_type_list_type = bobura::type_list::ui<detail_type_list_type>;

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

    using input_stream_iterator_type = common_type_list_type::input_stream_iterator_type;

    using bzip2_reader_type =
        bobura::model::serializer::bzip2_reader<
            size_type,
            difference_type,
            string_type,
            input_stream_iterator_type,
            operating_distance_type,
            speed_type,
            font_type
        >;

    using reader_type = bzip2_reader_type::base_type;

    using error_type = reader_type::error_type;

    class concrete_reader : public reader_type
    {
    public:
        virtual ~concrete_reader()
        = default;


    private:
        virtual bool selects_impl(const iterator first, const iterator last)
        override
        {
            boost::ignore_unused(first, last);

            return true;
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
BOOST_AUTO_TEST_SUITE(bzip2_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        auto p_reader = tetengo2::stdalt::make_unique<concrete_reader>();
        const bzip2_reader_type bzip2_reader{ std::move(p_reader) };
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        {
            auto p_reader = tetengo2::stdalt::make_unique<concrete_reader>();
            bzip2_reader_type bzip2_reader{ std::move(p_reader) };

            std::istringstream input_stream{ "BZ" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_CHECK(bzip2_reader.selects(first, last));
        }
        {
            auto p_reader = tetengo2::stdalt::make_unique<concrete_reader>();
            bzip2_reader_type bzip2_reader{ std::move(p_reader) };

            std::istringstream input_stream{ "AZ" };
            const auto first =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
                );
            const auto last =
                tetengo2::make_observable_forward_iterator(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                );
            BOOST_CHECK(!bzip2_reader.selects(first, last));
        }
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        auto p_reader = tetengo2::stdalt::make_unique<concrete_reader>();
        bzip2_reader_type bzip2_reader{ std::move(p_reader) };

        std::istringstream input_stream{ "BZ" };
        const auto first =
            tetengo2::make_observable_forward_iterator(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream))
            );
        const auto last =
            tetengo2::make_observable_forward_iterator(
                boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
            );
        auto error = error_type::none;
        const auto p_timetable = bzip2_reader.read(first, last, error);

        BOOST_REQUIRE(p_timetable);
        BOOST_CHECK(error == error_type::none);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
