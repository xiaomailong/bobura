/*! \file
    \brief Test of class bobura::model::train_info::time.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <stdexcept>

#include <boost/core/ignore_unused.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <bobura/model/train_info/time.h>
#include <bobura/model/train_info/time_span.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    using common_type_list_type = test_bobura::model::type_list::common;

    using size_type = common_type_list_type::size_type;

    using difference_type = common_type_list_type::difference_type;

    using time_span_type = bobura::model::train_info::time_span<difference_type>;

    using time_type = bobura::model::train_info::time<size_type, difference_type>;

    using hours_minutes_seconds_type_ = time_type::hours_minutes_seconds_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(train_info)
BOOST_AUTO_TEST_SUITE(time)
BOOST_AUTO_TEST_SUITE(hours_minutes_seconds_type)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const hours_minutes_seconds_type_ hours_minutes_seconds{ 12, 34, 56 };
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const hours_minutes_seconds_type_ hours_minutes_seconds1{ 12, 34, 56 };
            const hours_minutes_seconds_type_ hours_minutes_seconds2{ 12, 34, 56 };

            BOOST_CHECK(hours_minutes_seconds1 == hours_minutes_seconds2);
        }
        {
            const hours_minutes_seconds_type_ hours_minutes_seconds1{ 12, 34, 56 };
            const hours_minutes_seconds_type_ hours_minutes_seconds2{ 56, 34, 12 };

            BOOST_CHECK(hours_minutes_seconds1 != hours_minutes_seconds2);
        }
    }

    BOOST_AUTO_TEST_CASE(hours)
    {
        BOOST_TEST_PASSPOINT();

        const hours_minutes_seconds_type_ hours_minutes_seconds{ 12, 34, 56 };

        BOOST_CHECK_EQUAL(hours_minutes_seconds.hours(), 12U);
    }

    BOOST_AUTO_TEST_CASE(minutes)
    {
        BOOST_TEST_PASSPOINT();

        const hours_minutes_seconds_type_ hours_minutes_seconds{ 12, 34, 56 };

        BOOST_CHECK_EQUAL(hours_minutes_seconds.minutes(), 34U);
    }

    BOOST_AUTO_TEST_CASE(seconds)
    {
        BOOST_TEST_PASSPOINT();

        const hours_minutes_seconds_type_ hours_minutes_seconds{ 12, 34, 56 };

        BOOST_CHECK_EQUAL(hours_minutes_seconds.seconds(), 56U);
    }


BOOST_AUTO_TEST_SUITE_END()
    // test cases

    BOOST_AUTO_TEST_CASE(uninitialized)
    {
        BOOST_TEST_PASSPOINT();

        const auto time = time_type::uninitialized();
        boost::ignore_unused(time);
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_type time{ 0 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            const time_type time{ 1 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);
        }
        {
            const time_type time{ 2 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 2U);
        }
        {
            const time_type time{ 24 * 60 * 60 - 1 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 24U * 60U * 60U - 1U);
        }
        {
            const time_type time{ 24 * 60 * 60 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            const time_type time{ 0, 0, 0 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            const time_type time{ 0, 0, 1 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);
        }
        {
            const time_type time{ 0, 0, 59 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 59U);
        }
        {
            BOOST_CHECK_THROW((time_type{ 0, 0, 60 }), std::out_of_range);
        }
        {
            const time_type time{ 0, 1, 0 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 60U);
        }
        {
            const time_type time{ 0, 59, 0 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 3540U);
        }
        {
            BOOST_CHECK_THROW((time_type{ 0, 60, 0 }), std::out_of_range);
        }
        {
            const time_type time{ 1, 0, 0 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 3600U);
        }
        {
            const time_type time{ 23, 0, 0 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 82800U);
        }
        {
            BOOST_CHECK_THROW((time_type{ 24, 0, 0 }), std::out_of_range);
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(operator_plus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            time_type time{ 0 };
            const time_span_type time_span{ 0 };

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time{ 0 };
            const time_span_type time_span{ 1 };

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);
        }
        {
            time_type time{ 0 };
            const time_span_type time_span{ -1 };

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 24U * 60U * 60U - 1U);
        }
        {
            time_type time{ 24 * 60 * 60 - 1 };
            const time_span_type time_span{ 1 };

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time{ 0 };
            const time_span_type time_span{ 24, 0, 0 };

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time{ 0 };
            const time_span_type time_span{ -24, 0, 0 };

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            auto time = time_type::uninitialized();
            const time_span_type time_span{ 1 };

            time += time_span;

            BOOST_CHECK(!time.initialized());
        }
    }

    BOOST_AUTO_TEST_CASE(operator_minus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            time_type time{ 0 };
            const time_span_type time_span{ 0 };

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time{ 0 };
            const time_span_type time_span{ -1 };

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);
        }
        {
            time_type time{ 0 };
            const time_span_type time_span{ 1 };

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 24U * 60U * 60U - 1U);
        }
        {
            time_type time{ 24 * 60 * 60 - 1 };
            const time_span_type time_span{ -1 };

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time{ 0 };
            const time_span_type time_span{ 24, 0, 0 };

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time{ 0 };
            const time_span_type time_span{ -24, 0, 0 };

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            auto time = time_type::uninitialized();
            const time_span_type time_span{ 1 };

            time -= time_span;

            BOOST_CHECK(!time.initialized());
        }
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(operator_minus)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_type time1{ 0 };
            const time_type time2{ 0 };

            const auto time_span = time1 - time2;

            BOOST_CHECK_EQUAL(time_span.seconds(), 0);
        }
        {
            const time_type time1{ 1 };
            const time_type time2{ 0 };

            const auto time_span = time1 - time2;

            BOOST_CHECK_EQUAL(time_span.seconds(), 1);
        }
        {
            const time_type time1{ 0 };
            const time_type time2{ 1 };

            const auto time_span = time1 - time2;

            BOOST_CHECK_EQUAL(time_span.seconds(), 24 * 60 * 60 - 1);
        }
        {
            const time_type time1{ 1 };
            const time_type time2{ 24 * 60 * 60 - 1 };

            const auto time_span = time1 - time2;

            BOOST_CHECK_EQUAL(time_span.seconds(), 2);
        }
        {
            const time_type time2{ 1 };

            BOOST_CHECK_THROW(time_type::uninitialized() - time2, std::logic_error);
        }
        {
            const time_type time1{ 1 };

            BOOST_CHECK_THROW(time1 - time_type::uninitialized(), std::logic_error);
        }
        {
            BOOST_CHECK_THROW(time_type::uninitialized() - time_type::uninitialized(), std::logic_error);
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_type time1{ 1 };
            const time_type time2{ 1 };

            BOOST_CHECK(time1 == time2);
        }
        {
            const time_type time1{ 1 };
            const time_type time2{ 2 };

            BOOST_CHECK(time1 != time2);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less_than)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_type time1{ 1 };
            const time_type time2{ 1 };

            BOOST_CHECK(!(time1 < time2));
            BOOST_CHECK(time1 <= time2);
            BOOST_CHECK(!(time1 > time2));
            BOOST_CHECK(time1 >= time2);
        }
        {
            const time_type time1{ 1 };
            const time_type time2{ 2 };

            BOOST_CHECK(time1 < time2);
            BOOST_CHECK(time1 <= time2);
            BOOST_CHECK(!(time1 > time2));
            BOOST_CHECK(!(time1 >= time2));
        }
        {
            const time_type time1{ 2 };
            const time_type time2{ 1 };

            BOOST_CHECK(!(time1 < time2));
            BOOST_CHECK(!(time1 <= time2));
            BOOST_CHECK(time1 > time2);
            BOOST_CHECK(time1 >= time2);
        }
    }

// This test case causes a segmentation fault on Cygwin.
#if !( \
    __CYGWIN__ /*BOOST_OS_CYGWIN*/ && \
    (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(4, 9, 0) && BOOST_COMP_GNUC < BOOST_VERSION_NUMBER(5, 0, 0)) \
)
    BOOST_AUTO_TEST_CASE(seconds_from_midnight)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_type time{ 0 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            const time_type time{ 1 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);
        }
        {
            const time_type time{ 2 };

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 2U);
        }
        {
            BOOST_CHECK_THROW(time_type::uninitialized().seconds_from_midnight(), std::logic_error);
        }
    }

    BOOST_AUTO_TEST_CASE(hours_minutes_seconds)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_type time{ 0, 0, 0 };

            BOOST_CHECK(time.hours_minutes_seconds() == hours_minutes_seconds_type_(0U, 0U, 0U));
        }
        {
            const time_type time{ 0, 0, 1 };

            BOOST_CHECK(time.hours_minutes_seconds() == hours_minutes_seconds_type_(0U, 0U, 1U));
        }
        {
            const time_type time{ 0, 1, 0 };

            BOOST_CHECK(time.hours_minutes_seconds() == hours_minutes_seconds_type_(0U, 1U, 0U));
        }
        {
            const time_type time{ 1, 0, 0 };

            BOOST_CHECK(time.hours_minutes_seconds() == hours_minutes_seconds_type_(1U, 0U, 0U));
        }
        {
            const time_type time{ 1, 2, 3 };

            BOOST_CHECK(time.hours_minutes_seconds() == hours_minutes_seconds_type_(1U, 2U, 3U));
        }
        {
            BOOST_CHECK_THROW(time_type::uninitialized().hours_minutes_seconds(), std::logic_error);
        }
    }
#endif

    BOOST_AUTO_TEST_CASE(initialized)
    {
        BOOST_TEST_PASSPOINT();

        {
            const time_type time{ 0, 0, 0 };

            BOOST_CHECK(time.initialized());
        }
        {
            const time_type time{ time_type::uninitialized() };

            BOOST_CHECK(!time.initialized());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
