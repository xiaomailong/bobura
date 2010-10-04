/*! \file
    \brief Test of class tetengo2::encoder.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"
#include "tetengo2.encoding.ascii.h"

#include "tetengo2.encoder.h"


namespace
{
    // types

    typedef tetengo2::encoding::ascii encoding_type;

    typedef tetengo2::encoder<encoding_type, encoding_type> encoder_type;

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(encoder)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const encoding_type encoding1;
            const encoding_type encoding2;
            const encoder_type encoder(encoding1, encoding2);
        }
        {
            const encoding_type encoding1;
            const encoding_type encoding2;
            const encoder_type encoder1(encoding1, encoding2);
            const encoder_type encoder2(encoder1);

            BOOST_CHECK(encoder1 == encoder2);
        }
    }

    BOOST_AUTO_TEST_CASE(swap)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1;
        const encoding_type encoding2;
        encoder_type encoder1(encoding1, encoding2);
        encoder_type encoder2(encoding2, encoding1);

        boost::swap(encoder1, encoder2);
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1;
        const encoding_type encoding2;
        encoder_type encoder1(encoding1, encoding2);
        const encoder_type encoder2(encoding2, encoding1);

        encoder1 = encoder2;

        BOOST_CHECK(encoder1 == encoder2);
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1;
        const encoding_type encoding2;
        encoder_type encoder1(encoding1, encoding2);
        encoder_type encoder2(encoding1, encoding2);

        BOOST_CHECK(encoder1 == encoder2);
    }

    BOOST_AUTO_TEST_CASE(internal_encoding)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1;
        const encoding_type encoding2;
        const encoder_type encoder(encoding1, encoding2);
    }

    BOOST_AUTO_TEST_CASE(external_encoding)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1;
        const encoding_type encoding2;
        const encoder_type encoder(encoding1, encoding2);
    }

    BOOST_AUTO_TEST_CASE(encode)
    {
        BOOST_TEST_PASSPOINT();

        const encoder_type::internal_string_type internal_string(
            TETENGO2_TEXT("Tetengo2")
        );
        const encoder_type::external_string_type external_string(
            TETENGO2_TEXT("Tetengo2")
        );

        const encoding_type encoding1;
        const encoding_type encoding2;
        const encoder_type encoder(encoding1, encoding2);

        BOOST_CHECK(encoder.encode(internal_string) == external_string);
    }

    BOOST_AUTO_TEST_CASE(decode)
    {
        BOOST_TEST_PASSPOINT();

        const encoder_type::internal_string_type internal_string(
            TETENGO2_TEXT("Tetengo2")
        );
        const encoder_type::external_string_type external_string(
            TETENGO2_TEXT("Tetengo2")
        );

        const encoding_type encoding1;
        const encoding_type encoding2;
        const encoder_type encoder(encoding1, encoding2);

        BOOST_CHECK(encoder.decode(external_string) == internal_string);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
