/*! \file
    \brief Test of class bobura::model::train_kind.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include <bobura/model/train_kind.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_bobura::model::type_list::detail_for_test;

    using common_type_list_type = test_bobura::model::type_list::common;

    using ui_type_list_type = test_bobura::model::type_list::ui<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using color_type = ui_type_list_type::color_type;

    using train_kind_type = bobura::model::train_kind<string_type>;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(train_kind)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const train_kind_type kind1{
                string_type{ TETENGO2_TEXT("hoge") },
                string_type{ TETENGO2_TEXT("fuga") },
                color_type{ 0, 128, 255 },
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid
            };
            const train_kind_type kind2{
                string_type{ TETENGO2_TEXT("hoge") },
                string_type{ TETENGO2_TEXT("fuga") },
                color_type{ 0, 128, 255 },
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid
            };

            BOOST_CHECK(kind1 == kind2);
        }
        {
            const train_kind_type kind1{
                string_type{ TETENGO2_TEXT("hoge") },
                string_type{ TETENGO2_TEXT("fuga") },
                color_type{ 0, 128, 255 },
                train_kind_type::weight_type::normal,
                train_kind_type::line_style_type::solid
            };
            const train_kind_type kind2{
                string_type{ TETENGO2_TEXT("foo") },
                string_type{ TETENGO2_TEXT("bar") },
                color_type{ 255, 128, 0 },
                train_kind_type::weight_type::bold,
                train_kind_type::line_style_type::dashed
            };

            BOOST_CHECK(kind1 != kind2);
        }
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };

        BOOST_CHECK(kind.name() == string_type{ TETENGO2_TEXT("hoge") });
    }

    BOOST_AUTO_TEST_CASE(abbreviation)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };

        BOOST_CHECK(kind.abbreviation() == string_type{ TETENGO2_TEXT("fuga") });
    }

    BOOST_AUTO_TEST_CASE(color)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };

        BOOST_CHECK((kind.color() == color_type{ 0, 128, 255 }));
    }

    BOOST_AUTO_TEST_CASE(weight)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };

        BOOST_CHECK(kind.weight() == train_kind_type::weight_type::normal);
    }

    BOOST_AUTO_TEST_CASE(line_style)
    {
        BOOST_TEST_PASSPOINT();

        const train_kind_type kind{
            string_type{ TETENGO2_TEXT("hoge") },
            string_type{ TETENGO2_TEXT("fuga") },
            color_type{ 0, 128, 255 },
            train_kind_type::weight_type::normal,
            train_kind_type::line_style_type::solid
        };

        BOOST_CHECK(kind.line_style() == train_kind_type::line_style_type::solid);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
