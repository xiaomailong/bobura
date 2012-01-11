/*! \file
    \brief Test of class tetengo2::gui::menu::shortcut_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.gui.virtual_key.h"

#include "tetengo2.gui.menu.shortcut_key.h"


namespace
{
    // types

    typedef
        tetengo2::detail::stub::virtual_key<std::string>
        virtual_key_details_type;

    typedef
        tetengo2::gui::virtual_key<virtual_key_details_type> virtual_key_type;

    typedef
        tetengo2::gui::menu::shortcut_key<virtual_key_type>
        shortcut_key_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(shortcut_key)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, false, false
            );
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, false, false
            );
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, false, true
            );
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, true, false
            );
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, true, true
            );
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), true, false, false
            );
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), true, false, true
            );
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), true, true, false
            );
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), true, true, true
            );
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key1(
                virtual_key_type::char_a(), false, false, false
            );
            const shortcut_key_type shortcut_key2(
                virtual_key_type::char_a(), false, false, false
            );

            BOOST_CHECK(shortcut_key1 == shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1(
                virtual_key_type::char_a(), false, false, false
            );
            const shortcut_key_type shortcut_key2(
                virtual_key_type::char_b(), false, false, false
            );

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1(
                virtual_key_type::char_a(), false, false, false
            );
            const shortcut_key_type shortcut_key2(
                virtual_key_type::char_a(), true, false, false
            );

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1(
                virtual_key_type::char_a(), false, false, false
            );
            const shortcut_key_type shortcut_key2(
                virtual_key_type::char_a(), false, true, false
            );

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
        {
            const shortcut_key_type shortcut_key1(
                virtual_key_type::char_a(), false, false, false
            );
            const shortcut_key_type shortcut_key2(
                virtual_key_type::char_a(), false, false, true
            );

            BOOST_CHECK(shortcut_key1 != shortcut_key2);
        }
    }

    BOOST_AUTO_TEST_CASE(key)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, false, false
            );

            BOOST_CHECK(shortcut_key.key() == virtual_key_type::char_a());
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::enter(), false, false, false
            );

            BOOST_CHECK(shortcut_key.key() == virtual_key_type::enter());
        }
    }

    BOOST_AUTO_TEST_CASE(shift)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, false, false
            );

            BOOST_CHECK(!shortcut_key.shift());
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), true, false, false
            );

            BOOST_CHECK(shortcut_key.shift());
        }
    }

    BOOST_AUTO_TEST_CASE(control)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, false, false
            );

            BOOST_CHECK(!shortcut_key.control());
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, true, false
            );

            BOOST_CHECK(shortcut_key.control());
        }
    }

    BOOST_AUTO_TEST_CASE(meta)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, false, false
            );

            BOOST_CHECK(!shortcut_key.meta());
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, false, true
            );

            BOOST_CHECK(shortcut_key.meta());
        }
    }

    BOOST_AUTO_TEST_CASE(to_string)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_a(), false, false, false
            );

            BOOST_CHECK(shortcut_key.to_string() == "A");
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_b(), false, true, false
            );

            BOOST_CHECK(shortcut_key.to_string() == "Ctrl+B");
        }
        {
            const shortcut_key_type shortcut_key(
                virtual_key_type::char_c(), true, false, true
            );

            BOOST_CHECK(shortcut_key.to_string() == "Shift+Alt+C");
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()