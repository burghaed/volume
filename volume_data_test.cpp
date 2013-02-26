//
//  volume_data_test.cpp
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 31.01.13.
//
//
#include <boost/test/unit_test.hpp>
#include "VolumeData.h"

BOOST_AUTO_TEST_SUITE(voxel_data_tests)

BOOST_AUTO_TEST_CASE( VOLUME_RESOLUTION ){
    VolumeResolution res( 2, 3, 4 );
    BOOST_CHECK_EQUAL( res.get_x(), 2 );
    BOOST_CHECK_EQUAL( res.get_y(), 3 );
    BOOST_CHECK_EQUAL( res.get_z(), 4 );
    
    BOOST_CHECK_EQUAL( res.get_z(), res[ 2 ] );
    
    BOOST_CHECK_EQUAL( res.get_x_offset(), 1 );
    BOOST_CHECK_EQUAL( res.get_y_offset(), 1 * 2 );
    BOOST_CHECK_EQUAL( res.get_z_offset(), 1 * 2 * 3 );
}

BOOST_AUTO_TEST_CASE( VOUME_DATA ){
    volume_data_t data1( 2, 2, 2 );;

    BOOST_CHECK_EQUAL( data1.size(), 8 );
    for( size_t i = 0; i < data1.size(); ++i ) {
        data1[ i ] = i;
    }
    
    for( size_t i = 0; i < data1.size(); ++i ) {
        BOOST_CHECK_EQUAL( data1[ i ], i );
    }

    
    const VolumeResolution res = data1.get_resolution();
    BOOST_CHECK_EQUAL( res.get_x(), 2 );
    BOOST_CHECK_EQUAL( res.get_y(), 2 );
    BOOST_CHECK_EQUAL( res.get_z(), 2 );
    
    const unsigned char test_data[ 8 ] = {
        8, 7, 1, 2, 4, 5, 6, 3
    };
    std::copy( test_data, test_data + 8, data1.begin() );
    volume_data_t::const_iterator it = data1.begin();
    for ( int i = 0; it != data1.end(); ++it, ++i ) {
        BOOST_CHECK_EQUAL( test_data[ i ], *it );
    }
    const size_t index = res.get_x_offset() * 1 + res.get_y_offset() * 1 + res.get_z_offset() * 1;
    BOOST_CHECK_EQUAL( test_data[ index ], data1( 1, 1, 1 ) );
}


BOOST_AUTO_TEST_SUITE_END()
