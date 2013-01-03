//
//  Voxel.h
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 23.10.12.
//
//

#ifndef SubVoxeling_Voxel_h
#define SubVoxeling_Voxel_h

#include <assert.h>
#include "VoxelFace.h"


//        0   1   2   3    0   1  2   3
//Face 0: vo, v1, v2, v3; e0, e1, e2, e3
//Face 1: v4, v5, v6, v7; e4, e5, e6, e7
//Face 2: vo, v1, v5, v4; e0, e9, e4, e8
//Face 2: v3, v2, v6, v7; e2, e10, e6, e11
//Face 2: vo, v4, v7, v3; e3, e8, e7, e11
//Face 2: v1, v5, v6, v2; e1, e9, e5, e10

template <typename T >
class Voxel {

    typedef  Voxel< T >         voxel_t;
    typedef  VoxelFace          face_t;
    typedef  VoxelEdge          edge_t;
    typedef  VoxelVertex        vertex_t;
    
    T           value_;
    T           parent_value_;
    size_t      index_;
    size_t      parent_index_;
    face_t      faces_[ 6 ];
    
 public:
  
    Voxel():
    value_( T() ),
    index_( 0 ),
    parent_value_( T() ),
    parent_index_( 0 ){
    }
    
    
    Voxel( const T& value, size_t index, const T& parent_value, size_t parent_index ) :
    value_( value ),
    index_( index ),
    parent_value_( parent_value ),
    parent_index_( parent_index ){
//        for( int i = 0; i < 6; ++i ){
//            this->get_face( i ).get_left_voxel_index = index;
//            this->get_face( i ).get_right_voxel_index = index;
//            this->get_face( i ).get_edge( )
//        }
    }
    
    ~Voxel(){
    }
    
     
    const face_t& get_face( int face ) const {
        assert( 0 <= face && face < 6 );
        return faces_[ face ];
    }
    
    face_t& get_face( int face )  {
        assert( 0 <= face && face < 6 );
        return faces_[ face ];
    }
    
    const T& get_value() const {
        return value_;
    }
    
    T& get_value()  {
        return value_;
    }
    
    const T& get_parent_value() const {
        return parent_value_;
    }
    
    T& get_parent_value()  {
        return parent_value_;
    }
    
    const size_t& get_index() const {
        return index_;
    }

    size_t& get_index()  {
        return index_;
    }

    const size_t& get_parent_index() const {
        return parent_index_;
    }

    size_t& get_parent_index()  {
        return parent_index_;
    }
    
    const bool operator==( const voxel_t& other ) const {
        const bool result = this->get_value() == other.get_value()                &&
                            this->get_index() == other.get_index()                &&
                            this->get_face() == other.get_face()                  &&
                            this->get_parent_value() == other.get_parent_value() ;
        return result;
    }
};

//
//template < typename T >
//std::ostream& operator<<( std::ostream& os, Voxel< T >& voxel ) {
//    os << "Voxel value = " << voxel.get_value() << " index = " << voxel.;
//    return os;
//}

template < typename T >
bool operator==( const T& value, const  Voxel< T >& voxel ) {
    const bool result = value == voxel.get_value();
    return result;
}


template < typename T >
bool operator==(  const  Voxel< T >& voxel, const T& value ) {
    const bool result = value == voxel.get_value();
    return result;
}


typedef Voxel< unsigned char >         voxel_t;
typedef VoxelData< voxel_t >           voxels_t;

//
//voxels_t create_test_voxel_data( const size_t res[ 3 ], const unsigned char* data ) {
//    voxels_t result;
//    result.set_resolution(res );
//    size_t index = 0;
//    for (size_t iz = 0; iz < res[ 2 ]; ++iz) {
//        for (size_t iy = 0; iy < res[ 1 ]; ++iy ) {
//            for (size_t ix = 0; ix < res[ 0 ]; ++ix ) {
//                result( ix, iy, iz ) = voxel_t( data[ index ], index, data[ index ], index );
//                ++index;
//            }
//        }
//    }
//
//   
//    index = 0;
//    for (size_t iz = 0; iz < res[ 2 ]; ++iz) {
//        for (size_t iy = 0; iy < res[ 1 ]; ++iy ) {
//            for (size_t ix = 0; ix < res[ 0 ]; ++ix ) {
//                size_t index[ 3 ] = { ix, iy, iz };
//                for( int dir = 0; dir < 3; ++dir ){
//                    result( index ).get_face( 3 * dir ).get_left_voxel_index() = result( index[ 0 ],index[ 1 ], index[ 2 ] );
//                    if( index[ dir ] > 0 ) {
//                        --index[ dir ];
//                        result( index ).get_face( 3 * dir ).get_left_voxel_index() = result( index[ 0 ],index[ 1 ], index[ 2 ] ).get_index();
//                        ++index[ dir ];
//                        result( index ).get_face( 3 * dir ).get_right_voxel_index() = result( index[ 0 ],index[ 1 ], index[ 2 ] ).get_index()
//                    }
//                    
//                }
//                ++index;
//            }
//        }
//    }
//   
//    
//    
//    return result;
//    
//}



#endif
