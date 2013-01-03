#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE my program tests

#include <boost/test/unit_test.hpp>
#include <boost/test/output/compiler_log_formatter.hpp>
#include "xcode_log_formatter.hpp"

using namespace boost::unit_test;

struct xcode_config
{
	xcode_config()
	{
		unit_test_log.set_formatter( new xcode_log_formatter );
	}
	
	~xcode_config() {}
};

BOOST_GLOBAL_FIXTURE(xcode_config);

