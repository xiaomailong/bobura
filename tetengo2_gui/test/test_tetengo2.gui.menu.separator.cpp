/*! \file
    \brief Test of class tetengo2::gui::menu::separator.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::menu_type_list,
            test_tetengo2::gui::type::menu::menu_details
        >::type
        menu_details_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::menu_type_list,
            test_tetengo2::gui::type::menu::separator
        >::type
        menu_separator_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(separator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const menu_separator_type menu_separator;
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const menu_separator_type menu_separator;

        BOOST_CHECK(
            &menu_separator.style() ==
            &menu_details_type::menu_separator_style()
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
