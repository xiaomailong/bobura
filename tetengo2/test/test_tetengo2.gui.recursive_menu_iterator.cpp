/*! \file
    \brief Test of class tetengo2::gui::recursive_menu_iterator.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <memory>
#include <string>

#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.encode.h"
#include "stub_tetengo2.gui.menu.h"
#include "stub_tetengo2.gui.popup_menu.h"
#include "tetengo2.gui.menu_observer.h"

#include "tetengo2.gui.recursive_menu_iterator.h"


namespace
{
    // types

    typedef
        stub_tetengo2::gui::menu<
            unsigned int,
            const void*,
            std::string,
            stub_tetengo2::encode,
            tetengo2::gui::menu_observer
        >
        menu_type;

    typedef stub_tetengo2::gui::popup_menu<menu_type> popup_menu_type;

    typedef tetengo2::gui::recursive_menu_iterator<menu_type> iterator_type;


    // functions

    std::auto_ptr<menu_type> create_menu()
    {
        std::auto_ptr<menu_type> p_menu(new popup_menu_type("0"));

        p_menu->insert(
            p_menu->end(), std::auto_ptr<menu_type>(new popup_menu_type("1"))
        );
        p_menu->begin()->insert(
            p_menu->begin()->end(),
            std::auto_ptr<menu_type>(new popup_menu_type("2"))
        );
        p_menu->insert(
            p_menu->end(), std::auto_ptr<menu_type>(new popup_menu_type("3"))
        );

        return p_menu;
    }


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(recursive_menu_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        {
            const iterator_type iterator;
        }
        {
            const std::auto_ptr<menu_type> p_menu = create_menu();

            const iterator_type iterator(p_menu.get());
        }
    }

    BOOST_AUTO_TEST_CASE(operator_preincrement)
    {
        BOOST_CHECKPOINT("");

        {
            const std::auto_ptr<menu_type> p_menu = create_menu();

            iterator_type iterator(p_menu.get());

            BOOST_CHECK(iterator->text() == "0");
            ++iterator;
            BOOST_CHECK(iterator->text() == "1");
            ++iterator;
            BOOST_CHECK(iterator->text() == "2");
            ++iterator;
            BOOST_CHECK(iterator->text() == "3");
            ++iterator;
            BOOST_CHECK(iterator == iterator_type());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()