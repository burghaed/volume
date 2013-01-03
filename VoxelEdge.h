//
//  VoxelEdge.h
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 23.10.12.
//
//

#ifndef SubVoxeling_VoxelEdge_h
#define SubVoxeling_VoxelEdge_h

#include "VoxelVertex.h"


class VoxelEdge {

    typedef VoxelVertex   vertex_t;
    
    vertex_t            vertices_[ 2 ];
    size_t              neighbor_[ 4 ];
public:
    
    VoxelEdge(){
        for ( int i = 0; i < 4; ++i ) {
            neighbor_[ i ] = 0;
        }
    }

    ~VoxelEdge(){
    }

    
    const vertex_t& get_vertex( int index ) const {
        assert( 0 <= index && index < 2 );
        return vertices_[ index ];
    }
    
    vertex_t& get_vertex( int index )  {
        assert( 0 <= index && index < 2 );
        return vertices_[ index ];
    }
    
    
    const size_t& get_neighbor( int index ) const {
        assert( 0 <= index && index < 4 );
        return neighbor_[ index ];

    }
    
    size_t& get_neighbor( int index )  {
        assert( 0 <= index && index < 4 );
        return neighbor_[ index ];
    }
    
    bool operator==( const VoxelEdge& other ) const {
        bool result = this->get_vertex( 0 ) == other.get_vertex( 0 ) &&
                      this->get_vertex( 1 ) == other.get_vertex( 1 )  ;
        for( int i = 0; i < 4 && result; ++i ) {
            result &= this->get_neighbor( i ) == other.get_neighbor( i );
        }
        
        return result;
    }
    
};


#endif
