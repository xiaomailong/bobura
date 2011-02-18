/*! \file
    \brief Test of class tetengo2::gui::recursive_menu_iterator.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.gui.abstract_popup_menu.h"
#include "stub_tetengo2.gui.menu.h"
#include "stub_tetengo2.gui.popup_menu.h"
#include "tetengo2.cpp0x.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"
#include "tetengo2.gui.menu_observer_set.h"
#include "tetengo2.gui.traits.menu_traits.h"

#include "tetengo2.gui.recursive_menu_iterator.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, encoding_type>
        encoder_type;

    typedef
        tetengo2::gui::traits::menu_traits<
            unsigned int,
            const void*,
            std::string,
            encoder_type,
            tetengo2::gui::menu_observer_set
        >
        menu_traits_type;

    typedef stub_tetengo2::gui::menu<menu_traits_type> menu_type;

    typedef
        stub_tetengo2::gui::abstract_popup_menu<menu_traits_type>
        abstract_popup_menu_type;

    typedef stub_tetengo2::gui::popup_menu<menu_traits_type> popup_menu_type;

    typedef tetengo2::gui::recursive_menu_iterator<menu_type> iterator_type;


    // functions

    tetengo2::cpp0x::unique_ptr<menu_type>::type create_menu()
    {
        tetengo2::cpp0x::unique_ptr<menu_type>::type p_menu(
            new popup_menu_type("0")
        );

        p_menu->insert(
            p_menu->end(),
            tetengo2::cpp0x::unique_ptr<menu_type>::type(
                new popup_menu_type("1")
            )
        );
        p_menu->begin()->insert(
            p_menu->begin()->end(),
            tetengo2::cpp0x::unique_ptr<menu_type>::type(
                new popup_menu_type("2")
            )
        );
        p_menu->insert(
            p_menu->end(),
            tetengo2::cpp0x::unique_ptr<menu_type>::type(
                new popup_menu_type("3")
            )
        );

        return std::move(p_menu);
    }


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(recursive_menu_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const iterator_type iterator;
        }
        {
            const tetengo2::cpp0x::unique_ptr<menu_type>::type p_menu(
                create_menu()
            );

            const iterator_type iterator(p_menu.get());
        }
    }

    BOOST_AUTO_TEST_CASE(operator_preincrement)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::cpp0x::unique_ptr<menu_type>::type p_menu(
                create_menu()
            );

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
