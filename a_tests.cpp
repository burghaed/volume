#include "a.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(a_tests)

BOOST_AUTO_TEST_CASE(add_test)
{
	BOOST_CHECK_EQUAL(a::add(1, 2), 3);
}

BOOST_AUTO_TEST_CASE(multiply_test)
{
	BOOST_CHECK_EQUAL(a::multiply(2, 3), 6);
}

BOOST_AUTO_TEST_SUITE_END()
