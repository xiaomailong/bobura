/*! \file
    \brief Test of class bobura::load_save::save_to_file.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"


namespace
{
    // types

    using message_catalog_type = boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type;

    using model_type = boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type;

    using window_type = boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type;

    using save_to_file_type = boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::save_to_file>::type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(save_to_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        {
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);

            model_type model;
            window_type parent;
            const auto result = save_to_file(model, parent);

            BOOST_CHECK(!result);
        }
        {
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);

            model_type model;
            model.set_path(boost::filesystem::path("test"));
            window_type parent;
            const auto result = save_to_file(model, parent);

            BOOST_CHECK(!result);
        }
        {
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);

            model_type model;
            model.set_changed(true);
            window_type parent;
            const auto result = save_to_file(model, parent);

            BOOST_CHECK(!result);
        }
        {
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(true, message_catalog);

            model_type model;
            window_type parent;
            const auto result = save_to_file(model, parent);

            BOOST_CHECK(!result);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
