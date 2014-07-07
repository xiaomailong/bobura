/*! \file
    \brief Test of class bobura::model::serializer::reader_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <iterator>
#include <string>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using string_type = boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type;

    using window_type =
        tetengo2::gui::widget::window<
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::widget_traits>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::widget_details_traits>::type,
            boost::mpl::at<test_bobura::model::detail_type_list, test_bobura::model::type::detail::menu>::type
        >;

    using io_string_type = std::string;

    using input_stream_iterator_type =
        boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>;

    using message_catalog_type =
        tetengo2::message::message_catalog<
            input_stream_iterator_type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::size>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::encoder>::type,
            boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::encoder>::type
        >;

    using input_stream_iterator_type =
        boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>>;

    using reader_type =
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::reader
        >::type;

    using reader_set_type =
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::reader_set
        >::type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(reader_set)
    // test cases

    BOOST_AUTO_TEST_CASE(create_readers)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        string_type file_name{ TETENGO2_TEXT("hoge") };
        const message_catalog_type message_catalog{};
        const auto p_readers = reader_set_type::create_readers(parent, std::move(file_name), message_catalog);

        BOOST_REQUIRE(!p_readers.empty());
        BOOST_CHECK(p_readers[0]);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
