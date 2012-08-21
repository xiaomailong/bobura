/*! \file
    \brief Test of class bobura::font_color_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef
        boost::mpl::at<bobura::dialog_type_list, bobura::type::dialog::font_color_dialog>::type
        font_color_dialog_type;


}


#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(font_color_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);
    }

    //BOOST_AUTO_TEST_CASE(company_name)
    //{
    //    BOOST_TEST_PASSPOINT();

    //    window_type window;
    //    const message_catalog_type message_catalog;
    //    const font_color_dialog_type font_color_dialog(window, message_catalog);

    //    BOOST_CHECK(font_color_dialog.company_name().empty());
    //}

    //BOOST_AUTO_TEST_CASE(set_company_name)
    //{
    //    BOOST_TEST_PASSPOINT();

    //    window_type window;
    //    const message_catalog_type message_catalog;
    //    font_color_dialog_type font_color_dialog(window, message_catalog);

    //    font_color_dialog.set_company_name(string_type(TETENGO2_TEXT("hoge")));

    //    BOOST_CHECK(font_color_dialog.company_name() == string_type(TETENGO2_TEXT("hoge")));
    //}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
