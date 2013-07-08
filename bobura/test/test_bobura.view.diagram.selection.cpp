/*! \file
    \brief Test of class bobura::view::diagram::selection.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

 #include "bobura.type_list.h"
 
#include "bobura.view.diagram.selection.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef model_type::timetable_type::station_location_type::station_type station_type;

    typedef
        boost::mpl::at<bobura::model_type_list, bobura::type::model::station_grade_type_set>::type
        station_grade_type_set_type;
    
    typedef model_type::timetable_type::train_type train_type;

    typedef train_type::stops_type::size_type stop_index_type;

    typedef bobura::view::diagram::selection<station_type, train_type> selection_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(selection)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const selection_type selection;
    }

    BOOST_AUTO_TEST_CASE(selected_O_station)
    {
        BOOST_TEST_PASSPOINT();

        const selection_type selection;

        const station_type station(
            string_type(TETENGO2_TEXT("name")), station_grade_type_set_type::local_type::instance(), false, false
        );

        BOOST_CHECK(!selection.selected(station));
    }

    BOOST_AUTO_TEST_CASE(selected_O_train)
    {
        BOOST_TEST_PASSPOINT();

        const selection_type selection;

        const train_type train(
            string_type(TETENGO2_TEXT("number")),
            0,
            string_type(TETENGO2_TEXT("name")),
            string_type(TETENGO2_TEXT("name_number")),
            string_type(TETENGO2_TEXT("note"))
        );

        BOOST_CHECK(!selection.selected(train, boost::none));
    }

    BOOST_AUTO_TEST_CASE(select_O_station)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection;

        const train_type train(
            string_type(TETENGO2_TEXT("number")),
            0,
            string_type(TETENGO2_TEXT("name")),
            string_type(TETENGO2_TEXT("name_number")),
            string_type(TETENGO2_TEXT("note"))
        );
        
        selection.select(train, boost::none);
        
        const station_type station(
            string_type(TETENGO2_TEXT("name")), station_grade_type_set_type::local_type::instance(), false, false
        );

        selection.select(station);

        BOOST_CHECK(selection.selected(station));
        BOOST_CHECK(!selection.selected(train, boost::none));
        BOOST_CHECK(!selection.selected(train, boost::make_optional<stop_index_type>(42)));
    }

    BOOST_AUTO_TEST_CASE(select_O_train)
    {
        BOOST_TEST_PASSPOINT();

        {
            selection_type selection;

            const station_type station(
                string_type(TETENGO2_TEXT("name")), station_grade_type_set_type::local_type::instance(), false, false
            );
            selection.select(station);

            const train_type train(
                string_type(TETENGO2_TEXT("number")),
                0,
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("name_number")),
                string_type(TETENGO2_TEXT("note"))
            );
        
            selection.select(train, boost::none);
        
            BOOST_CHECK(!selection.selected(station));
            BOOST_CHECK(selection.selected(train, boost::none));
            BOOST_CHECK(!selection.selected(train, boost::make_optional<stop_index_type>(42)));
        }
        {
            selection_type selection;

            const station_type station(
                string_type(TETENGO2_TEXT("name")), station_grade_type_set_type::local_type::instance(), false, false
            );
            selection.select(station);

            const train_type train(
                string_type(TETENGO2_TEXT("number")),
                0,
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("name_number")),
                string_type(TETENGO2_TEXT("note"))
            );
        
            selection.select(train, boost::make_optional<stop_index_type>(42));
        
            BOOST_CHECK(!selection.selected(station));
            BOOST_CHECK(!selection.selected(train, boost::none));
            BOOST_CHECK(selection.selected(train, boost::make_optional<stop_index_type>(42)));
        }
    }

    BOOST_AUTO_TEST_CASE(unselect_all)
    {
        BOOST_TEST_PASSPOINT();

        selection_type selection;

        {
            const station_type station(
                string_type(TETENGO2_TEXT("name")), station_grade_type_set_type::local_type::instance(), false, false
            );
            const train_type train(
                string_type(TETENGO2_TEXT("number")),
                0,
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("name_number")),
                string_type(TETENGO2_TEXT("note"))
            );
            selection.select(station);

            selection.unselect_all();

            BOOST_CHECK(!selection.selected(station));
            BOOST_CHECK(!selection.selected(train, boost::none));
        }
        {
            const station_type station(
                string_type(TETENGO2_TEXT("name")), station_grade_type_set_type::local_type::instance(), false, false
            );
            const train_type train(
                string_type(TETENGO2_TEXT("number")),
                0,
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("name_number")),
                string_type(TETENGO2_TEXT("note"))
            );
            selection.select(train, boost::none);

            selection.unselect_all();

            BOOST_CHECK(!selection.selected(station));
            BOOST_CHECK(!selection.selected(train, boost::none));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()