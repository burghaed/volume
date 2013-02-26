
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(voxel_data_tests)

BOOST_AUTO_TEST_CASE(CONSTRUCT_tests){
//    static const size_t res[] = {
//        1, 2, 3
//    };
//    static const size_t size = res[ 0 ] * res[ 1 ] * res[ 2 ];
//    const unsigned char data[] ={
//        0,1,2,3,4,5
//    };
//    voxel_data_t voxel_data( res, data  );
//    for( size_t index = 0; index < size; ++index ) {
//        BOOST_CHECK_EQUAL( voxel_data[ index ], data[ index] );
//    }
//    
//    for( int i = 0; i < 3; ++i ) {
//        BOOST_CHECK_EQUAL( voxel_data.get_resolution()[ i ], res[ i] );
//    }
//    size_t index = 0;
//    for (size_t iz = 0; iz < res[ 2 ]; ++iz) {
//        for (size_t iy = 0; iy < res[ 1 ]; ++iy ) {
//            for (size_t ix = 0; ix < res[ 0 ]; ++ix ) {
//                BOOST_CHECK_EQUAL( voxel_data( ix, iy, iz ), data[ index ] );
//                ++index;
//            }
//        }
//    }
}



BOOST_AUTO_TEST_CASE( voxel_tests ){
//    const size_t res[ 3 ] = {
//        2, 2, 2
//    };
//    
//    const unsigned char data[] ={
//        1, 0, 0, 0, 0, 0, 0, 1
//    };
//    
//    /const voxels_t criticle_vertex = create_test_voxel_data(res, data );
//    size_t index = 0;
//    for (size_t iz = 0; iz < res[ 2 ]; ++iz) {
//        for (size_t iy = 0; iy < res[ 1 ]; ++iy ) {
//            for (size_t ix = 0; ix < res[ 0 ]; ++ix ) {
//                BOOST_CHECK_EQUAL( criticle_vertex( ix, iy, iz ).get_parent_index(),  index );
//                BOOST_CHECK_EQUAL( criticle_vertex( ix, iy, iz ).get_value(),  data[ index ] );
//                BOOST_CHECK_EQUAL( criticle_vertex( ix, iy, iz ).get_parent_index(), criticle_vertex( ix, iy, iz ).get_index() );
//                
//                ++index;
//            }
//        }
//    }
    
}

BOOST_AUTO_TEST_SUITE_END()
