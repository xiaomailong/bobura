/*! \file
    \brief Test of class bobura::model::serializer::json_writer.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <sstream>
//#include <string>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.unique.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::station
        >::type
        station_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::grade_type_set
        >::type
        grade_type_set_type;

    typedef grade_type_set_type::local_type local_type;

    typedef grade_type_set_type::principal_type principal_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::station_location
        >::type
        station_location_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::time
        >::type
        time_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::stop
        >::type
        stop_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::train
        >::type
        train_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::timetable
        >::type
        timetable_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list,
            test_bobura::model::type::serialization::json_writer
        >::type
        writer_type;


    // variables

    const std::string json0 =
        "[\n"
        "    {\n"
        "        \"title\": \"\"\n"
        "    },\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json1 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        { \"name\": \"stationA\", \"grade\": \"local\", \"meterage\": 42 },\n"
        "        { \"name\": \"stationB\", \"grade\": \"principal\", \"meterage\": 4242 }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"101D\",\n"
        "            \"note\": \"fuga\",\n"
        "            \"stops\": [\n"
        "                [    -1,     -1, \"\"],\n"
        "                [    -1,     -1, \"\"]\n"
        "            ]\n"
        "        },\n"
        "        {\n"
        "            \"number\": \"123D\",\n"
        "            \"note\": \"\",\n"
        "            \"stops\": [\n"
        "                [    -1,  60030, \"1\"],\n"
        "                [ 60545,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"9324M\",\n"
        "            \"note\": \"piyo\",\n"
        "            \"stops\": [\n"
        "                [    -1,  62000, \"0A\"],\n"
        "                [    -1,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ]\n"
        "]\n";


    // functions

    std::unique_ptr<const timetable_type> create_timetable1()
    {
        std::unique_ptr<timetable_type> p_timetable =
            tetengo2::make_unique<timetable_type>();

        p_timetable->set_title("hoge");

        {
            p_timetable->insert_station_location(
                p_timetable->station_locations().end(),
                station_location_type(
                    station_type("stationA", local_type::instance()),
                    42
                )
            );
            p_timetable->insert_station_location(
                p_timetable->station_locations().end(),
                station_location_type(
                    station_type("stationB", principal_type::instance()),
                    4242
                )
            );
        }
        {
            {
                train_type train("101D", "fuga");
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type::uninitialized(),
                        ""
                    )
                );
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type::uninitialized(),
                        ""
                    )
                );
                p_timetable->insert_down_train(
                    p_timetable->down_trains().end(), train
                );
            }
            {
                train_type train("123D", "");
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type( 6, 0, 30),
                        "1"
                    )
                );
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type(6, 5, 45),
                        time_type::uninitialized(),
                        ""
                    )
                );
                p_timetable->insert_down_train(
                    p_timetable->down_trains().end(), train
                );
            }
        }
        {
            {
                train_type train("9324M", "piyo");
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type(6, 20, 0),
                        "0A"
                    )
                );
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type::uninitialized(),
                        ""
                    )
                );
                p_timetable->insert_up_train(
                    p_timetable->up_trains().end(), train
                );
            }
        }
        return std::move(p_timetable);
    }


}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(json_writer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const writer_type json_writer;
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        {
            writer_type json_writer;

            const timetable_type timetable;
            std::ostringstream stream;

            json_writer.write(timetable, stream);

            const std::string result = stream.str();
            BOOST_CHECK(result == json0);
        }
        {
            writer_type json_writer;

            const std::unique_ptr<const timetable_type> p_timetable =
                create_timetable1();
            std::ostringstream stream;

            json_writer.write(*p_timetable, stream);

            const std::string result = stream.str();
            BOOST_CHECK(result == json1);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
