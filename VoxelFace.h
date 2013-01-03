//
//  VoxelFace.h
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 23.10.12.
//
//

#ifndef SubVoxeling_VoxelFace_h
#define SubVoxeling_VoxelFace_h

#include "VoxelEdge.h"


class VoxelFace {
    typedef VoxelEdge      edge_t;
    typedef VoxelVertex    vertex_t;
    
    size_t  left_voxel_ndex_, right_voxel_index_;
    edge_t  edges_[ 4 ];
public:
    VoxelFace() :
    left_voxel_ndex_( 0 )
    ,right_voxel_index_( 0 ){
    }
    
    ~VoxelFace(){
    }
    
    
    const size_t& get_left_voxel_index() const {
        return left_voxel_ndex_;
    }
    
    size_t& get_left_voxel_index()  {
         return left_voxel_ndex_;
    }
    
    const size_t& get_right_voxel_index() const {
        return right_voxel_index_;
    }
    
    size_t& get_right_voxel_index()  {
        return right_voxel_index_;
    }
    
    const edge_t& get_edge( int index ) const {
        assert( 0 <= index && index < 4);
        return edges_[ index ];
    }

    edge_t& get_edge( int index ) {
        assert( 0 <= index && index < 4);
        return edges_[ index ];
    }

    bool operator==( const VoxelFace& other ) const {
        bool result = this->get_left_voxel_index() == other.get_left_voxel_index() &&
                      this->get_right_voxel_index() == other.get_right_voxel_index()  ;
        for( int i = 0; i < 4 && result; ++i) {
            result &= this->get_edge( i ) == other.get_edge( i );
        }
        return result;
    }
};
#endif
