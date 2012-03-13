/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>
//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::path>::type
        path_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::settings>::type
        settings_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(settings)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
    }

    BOOST_AUTO_TEST_CASE(base_path)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        path_type path(L"path/to");
        const settings_type settings(std::move(arguments), std::move(path));

        BOOST_CHECK(settings.base_path() == path_type(L"path/to"));
    }

    BOOST_AUTO_TEST_CASE(message_directory_path)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        path_type path(L"path/to");
        const settings_type settings(std::move(arguments), std::move(path));

        BOOST_CHECK(
            settings.message_directory_path() ==
            path_type(L"path/to/messages")
        );
    }

    BOOST_AUTO_TEST_CASE(image_directory_path)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        path_type path(L"path/to");
        const settings_type settings(std::move(arguments), std::move(path));

        BOOST_CHECK(
            settings.image_directory_path() == path_type(L"path/to/images")
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
