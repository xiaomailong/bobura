/*! \file
    \brief Test of class bobura::configuration.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_CONFIGURATION_H)
#define TESTBOBURA_CONFIGURATION_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura
{
    class configuration
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void options();

        static void alert();

        static void construction();

        static void create_bobura();


    };


}

#endif
