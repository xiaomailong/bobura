/*! \file
    \brief The initialization of test of bobura_model.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#define BOOST_TEST_MODULE test_bobura_model
#include <boost/test/unit_test.hpp>

#include "init_bobura.model.h"


boost::unit_test::test_suite* init_unit_test_suite(
    const int    /* argc */,
    char** const /* argv */
)
{
    boost::unit_test::test_suite* const p_suite = BOOST_TEST_SUITE("init");

    p_suite->add(test_bobura::model::suite());

    return p_suite;
}
