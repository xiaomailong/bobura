/*! \file
    \brief Test of class tetengo2::config::persistent_config.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>
//#include <boost/variant.hpp>

#include "test_tetengo2.type_list.h"
#include "tetengo2.detail.stub.config.h"
#include "tetengo2.text.h"

#include "tetengo2.config.persistent_config.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::string>::type string_type;

    typedef boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::size>::type uint_type;

    typedef
        tetengo2::config::persistent_config<string_type, uint_type, tetengo2::detail::stub::config>
        persistent_config_type;

    typedef persistent_config_type::base_type config_base_type;

    typedef persistent_config_type::value_type value_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(persistent_config)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const persistent_config_type config(string_type(TETENGO2_TEXT("group")));
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        const persistent_config_type config(string_type(TETENGO2_TEXT("group")));

        //{
        //    const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("foo")));
        //    BOOST_REQUIRE(value);
        //    BOOST_CHECK(boost::get<string_type>(*value) == string_type(TETENGO2_TEXT("hoge")));
        //}
        //{
        //    const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("foo")));
        //    BOOST_REQUIRE(value);
        //    BOOST_CHECK(boost::get<string_type>(*value) == string_type(TETENGO2_TEXT("hoge")));
        //}
        //{
        //    const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("baz")));
        //    BOOST_REQUIRE(!value);
        //}
    }

    BOOST_AUTO_TEST_CASE(set)
    {
        BOOST_TEST_PASSPOINT();

        const persistent_config_type config(string_type(TETENGO2_TEXT("group")));

        //config.set(string_type(TETENGO2_TEXT("foo")), value_type(4242));

        //const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("foo")));
        //BOOST_REQUIRE(value);
        //BOOST_CHECK_EQUAL(boost::get<uint_type>(*value), 4242U);
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
