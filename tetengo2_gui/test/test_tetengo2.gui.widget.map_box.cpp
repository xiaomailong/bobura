/*! \file
    \brief Test of class tetengo2::gui::widget::map_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <stdexcept>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::map_box>::type
        map_box_type;

    typedef map_box_type::value_type value_type;

    typedef value_type::first_type key_type;

    typedef value_type::second_type mapped_type;


    // functions

    template <typename T, typename U>
    value_type make_value(const T& key, const U& mapped)
    {
        return value_type(key_type(key), mapped_type(mapped));
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(map_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const map_box_type map_box(parent);
    }

    BOOST_AUTO_TEST_CASE(value_count)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const map_box_type map_box(parent);

            BOOST_CHECK_EQUAL(map_box.value_count(), 0U);
        }
        {
            window_type parent;
            map_box_type map_box(parent);
            map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

            BOOST_CHECK_EQUAL(map_box.value_count(), 1U);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            map_box_type map_box(parent);
            map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

            BOOST_CHECK(map_box.value(0) == make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));
        }
        {
            window_type parent;
            const map_box_type map_box(parent);

            BOOST_CHECK_THROW(map_box.value(0), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(set_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            map_box_type map_box(parent);
            map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

            map_box.set_value(0, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("baz")));

            BOOST_CHECK(map_box.value(0) == make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("baz")));
        }
        {
            window_type parent;
            map_box_type map_box(parent);

            BOOST_CHECK_THROW(
                map_box.set_value(0, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("baz"))), std::out_of_range
            );
        }
    }

    BOOST_AUTO_TEST_CASE(insert_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            map_box_type map_box(parent);

            map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));
            map_box.insert_value(1, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("bar")));
            map_box.insert_value(0, make_value(TETENGO2_TEXT("piyo"), TETENGO2_TEXT("baz")));
            map_box.insert_value(2, make_value(TETENGO2_TEXT("piyoyo"), TETENGO2_TEXT("bazz")));

            BOOST_CHECK_EQUAL(map_box.value_count(), 4U);
            BOOST_CHECK(map_box.value(0) == make_value(TETENGO2_TEXT("piyo"), TETENGO2_TEXT("baz")));
            BOOST_CHECK(map_box.value(1) == make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));
            BOOST_CHECK(map_box.value(2) == make_value(TETENGO2_TEXT("piyoyo"), TETENGO2_TEXT("bazz")));
            BOOST_CHECK(map_box.value(3) == make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("bar")));
        }
        {
            window_type parent;
            map_box_type map_box(parent);

            BOOST_CHECK_THROW(
                map_box.insert_value(1, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("bar"))), std::out_of_range
            );
        }
    }

    BOOST_AUTO_TEST_CASE(erase_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            map_box_type map_box(parent);
            map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

            map_box.erase_value(0);

            BOOST_CHECK_EQUAL(map_box.value_count(), 0U);
        }
        {
            window_type parent;
            map_box_type map_box(parent);

            BOOST_CHECK_THROW(map_box.erase_value(0), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
        //window_type parent;
        //map_box_type map_box(parent);
        //map_box.insert_value(0, string_type(TETENGO2_TEXT("hoge")));
        //map_box.insert_value(1, string_type(TETENGO2_TEXT("fuga")));

        //map_box.clear();

        //BOOST_CHECK_EQUAL(map_box.value_count(), 0U);
    }

    BOOST_AUTO_TEST_CASE(selected_value_index)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
        //window_type parent;
        //const map_box_type map_box(parent);

        //BOOST_CHECK(!map_box.selected_value_index());
    }

    BOOST_AUTO_TEST_CASE(select_value)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
        //{
        //    window_type parent;
        //    map_box_type map_box(parent);
        //    map_box.insert_value(0, string_type(TETENGO2_TEXT("hoge")));

        //    map_box.select_value(0);

        //    BOOST_CHECK(map_box.selected_value_index());
        //    BOOST_CHECK_EQUAL(*map_box.selected_value_index(), 0U);
        //}
        //{
        //    window_type parent;
        //    map_box_type map_box(parent);

        //    BOOST_CHECK_THROW(map_box.select_value(0), std::out_of_range);
        //}
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
