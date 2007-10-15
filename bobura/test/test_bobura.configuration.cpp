/*! \file
    \brief Test of class bobura::configuration.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.configuration.h"

#include "test_bobura.configuration.h"


namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* configuration::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::cofiguration");

        p_suite->add(BOOST_TEST_CASE(test_bobura::configuration::options));
        p_suite->add(BOOST_TEST_CASE(test_bobura::configuration::alert));
        p_suite->add(BOOST_TEST_CASE(test_bobura::configuration::construction));
        p_suite->add(BOOST_TEST_CASE(test_bobura::configuration::create_bobura));

        return p_suite;
    }

    void configuration::options()
    {
        const boost::program_options::options_description options =
            bobura::configuration::options();

        {
            const boost::program_options::option_description* const p_option =
                options.find_nothrow("help", false);
            BOOST_CHECK(p_option != NULL);
        }
        {
            const boost::program_options::option_description* const p_option =
                options.find_nothrow("h", true);
            BOOST_CHECK(p_option != NULL);
        }
    }

    void configuration::alert()
    {
        const bobura::configuration::alert_type alert =
            bobura::configuration::alert();
    }

    void configuration::construction()
    {
        const boost::program_options::variables_map variables_map;
        const bobura::configuration configuration(variables_map);
    }

    void configuration::create_bobura()
    {
        const boost::program_options::variables_map variables_map;
        const bobura::configuration configuration(variables_map);

        const boost::scoped_ptr<bobura::configuration::bobura_type> p_bobura(
            configuration.create_bobura()
        );
        BOOST_CHECK(p_bobura.get() != NULL);
    }


}
