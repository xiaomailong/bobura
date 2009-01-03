/*! \file
    \brief Test of class bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H)
#define TESTBOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura { namespace model { namespace timetable_info
{
    class station_location
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void swap();

        static void operator_assign();

        static void operator_equal();

        static void station();

        static void meterage();

        static void before();


    };


}}}

#endif
