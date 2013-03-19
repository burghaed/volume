//
//  criticle_element_test.cpp
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 18.10.12.
//
//


#include <boost/test/unit_test.hpp>
#include "VolumeData.h"
#include "CriticleVertexLUTable.h"
#include "CriticleEdge.h"

BOOST_AUTO_TEST_SUITE( criticle_element_tests )

inline volume_data_t create_volume_data() {
    volume_data_t result( 2, 2, 2 );
    result( 0, 0 ,0 ) = 1;
    result( 1, 1, 1 ) = 1;
    return result;
}

inline signed_volume_data_t create_volume_data_2() {
    signed_volume_data_t result( 2, 2, 2 );
    result( 1, 0 ,0 ) = 2;
    result( 0, 1, 1 ) = 2;
    
    result( 1, 0 ,1 ) = 3;
    result( 0, 1, 0 ) = 3;
    
    result( 0, 0 ,0 ) = -5;
    result( 1, 1, 1 ) = -5;
    return result;
}

BOOST_AUTO_TEST_CASE( vertex_priority_determinator ){
    vrtx_prioritx_det_t  determinator;
    const volume_data_t data1 = create_volume_data();
    const unsigned char dominant_vrtx = determinator( data1 );
    BOOST_CHECK_EQUAL( dominant_vrtx, 1 );
    
    const signed_volume_data_t data2 = create_volume_data_2();
    VertexPriority< int > determinator2;
    const int dominant_vrtx2 = determinator2( data2 );
    BOOST_CHECK_EQUAL( dominant_vrtx2, -5  );

}



BOOST_AUTO_TEST_CASE( vertex_to_voxels ){
    const volume_data_t data1 = create_volume_data();
    volume_data_t voxels = get_voxels_contain_vrtx( data1, 1, 1, 1 );
    BOOST_CHECK_EQUAL( voxels.size(), 8 );
    for( size_t i = 0 ; i < data1.size(); ++i ){
        BOOST_CHECK_EQUAL( data1[ i ], voxels[ i ] );
    }

    const volume_data_t voxels_2 = get_voxels_contain_vrtx( data1, 0, 0, 0 );
    BOOST_CHECK_EQUAL( voxels_2.size(), 1 );
    BOOST_CHECK_EQUAL( data1[ 0 ], voxels_2[ 0 ] );
    
    const volume_data_t voxels_3 = get_voxels_contain_vrtx( data1, 0, 0, 1 );
    BOOST_CHECK_EQUAL( voxels_3.size(), 2 );
    BOOST_CHECK_EQUAL( data1[ 0 ], voxels_3[ 0 ] );
    BOOST_CHECK_EQUAL( data1( 0, 0, 1 ), voxels_3[ 1 ] );
    
    
    const volume_data_t voxels_4 = get_voxels_contain_vrtx( data1, 1, 0, 0 );
    BOOST_CHECK_EQUAL( voxels_4.size(), 2 );
    BOOST_CHECK_EQUAL( data1[ 0 ], voxels_4[ 0 ] );
    BOOST_CHECK_EQUAL( data1( 1, 0, 0 ), voxels_4[ 1 ] );
    
    {
        const volume_data_t voxels_4 = get_voxels_contain_vrtx( data1, 0, 1, 0 );
        BOOST_CHECK_EQUAL( voxels_4.size(), 2 );
        BOOST_CHECK_EQUAL( data1[ 0 ], voxels_4[ 0 ] );
        BOOST_CHECK_EQUAL( data1( 0, 1, 0 ), voxels_4[ 1 ] );
    }
    
    {
        const volume_data_t voxels_4 = get_voxels_contain_vrtx( data1, 1, 1, 0 );
        BOOST_CHECK_EQUAL( voxels_4.size(), 4 );
        BOOST_CHECK_EQUAL( data1[ 0 ], voxels_4[ 0 ] );
        BOOST_CHECK_EQUAL( data1( 1, 1, 0 ), voxels_4[ 3 ] );
        BOOST_CHECK_EQUAL( data1( 1, 1, 0 ), voxels_4[ 3 ] );
    }


}

inline volume_data_t create_volume_data_3() {
    volume_data_t result(2, 2, 2 );;
    result( 1, 0 ,0 ) = 2;
    result( 0, 1, 1 ) = 2;
    
    result( 1, 0 ,1 ) = 3;
    result( 0, 1, 0 ) = 3;

    result( 1, 1 ,0 ) = 6;
    result( 0, 0, 1 ) = 7;

    result( 0, 0 ,0 ) = 4;
    result( 1, 1, 1 ) = 5;
    return result;
}

BOOST_AUTO_TEST_CASE( criticle_vertex ){

    const volume_data_t data1 = create_volume_data();
    criticle_vrtx_lut_t table( &data1 );
   
    
    BOOST_CHECK( table.criticle_vrtx( 1, 1, 1 ) );
    BOOST_CHECK_EQUAL( table.dominant_vrtx( 1, 1, 1 ), 1 );

    const volume_data_t data3 = create_volume_data_3();
    criticle_vrtx_lut_t table3( &data3 );
    
    
    BOOST_CHECK( table3.criticle_vrtx( 1, 1, 1 ) );
    BOOST_CHECK_EQUAL( table3.dominant_vrtx( 1, 1, 1 ), 3 );

}

inline volume_data_t create_volume_data_criticle_edge() {
    volume_data_t result( 2, 2, 2 );
    result( 0, 0 ,0 ) = 1;
    result( 1, 1, 0 ) = 1;
    result( 1, 1, 1 ) = 1;
//    result( 0, 1, 0 ) = 1;
    return result;
}

BOOST_AUTO_TEST_CASE( EDGE_INDEX_Z_DIR ){
    const volume_data_t data    = create_volume_data_criticle_edge();
    const size_t vrtx_indx      = data.get_resolution().convert( 1, 1, 0 );
    edge_index_t edge           = edge_index_t( vrtx_indx, Z_DIR );

    const volume_data_t voxels  = get_voxels_contain_edge( data, edge );
    BOOST_CHECK_EQUAL( voxels.size(), 4 );
    BOOST_CHECK_EQUAL( voxels( 0, 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( voxels( 1, 0, 0 ), 0 );
    BOOST_CHECK_EQUAL( voxels( 0, 1, 0 ), 0 );
    BOOST_CHECK_EQUAL( voxels( 1, 1, 0 ), 1 );
}

BOOST_AUTO_TEST_CASE( EDGE_INDEX_Y_DIR ){
    const volume_data_t data    = create_volume_data_criticle_edge();
    const size_t vrtx_indx      = data.get_resolution().convert( 1, 0, 1 );
    edge_index_t edge           = edge_index_t( vrtx_indx, Y_DIR );
    
    const volume_data_t voxels  = get_voxels_contain_edge( data, edge );
    BOOST_CHECK_EQUAL( voxels.size(), 4 );
    BOOST_CHECK_EQUAL( voxels( 0, 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( voxels( 1, 0, 0 ), 0 );
    BOOST_CHECK_EQUAL( voxels( 0, 1, 0 ), 0 );
    BOOST_CHECK_EQUAL( voxels( 1, 1, 0 ), 0 );
}

BOOST_AUTO_TEST_CASE( EDGE_INDEX_X_DIR ){
    const volume_data_t data    = create_volume_data_criticle_edge();
    const size_t vrtx_indx      = data.get_resolution().convert( 1, 1, 1 );
    edge_index_t edge           = edge_index_t( vrtx_indx, X_DIR );
    
    const volume_data_t voxels  = get_voxels_contain_edge( data, edge );
    BOOST_CHECK_EQUAL( voxels.size(), 4 );
    BOOST_CHECK_EQUAL( voxels( 0, 0, 0 ), 0 );
    BOOST_CHECK_EQUAL( voxels( 1, 0, 0 ), 1 );
    BOOST_CHECK_EQUAL( voxels( 0, 1, 0 ), 0 );
    BOOST_CHECK_EQUAL( voxels( 1, 1, 0 ), 0 );
}


BOOST_AUTO_TEST_SUITE_END()
