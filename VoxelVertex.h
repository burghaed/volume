//
//  VoxelVertex.h
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 23.10.12.
//
//

#ifndef SubVoxeling_VoxelVertex_h
#define SubVoxeling_VoxelVertex_h


class VoxelVertex {
    
    size_t       neighbour_[ 8 ];
public:
    VoxelVertex() {
        for( int i = 0; i < 8; ++i ) {
            neighbour_[ i ] = 0;
        }
    }
    
    VoxelVertex( const int neighbours[ 8 ] ) {
        std::copy( neighbours, neighbours + 8, neighbour_);
    }
    
    ~VoxelVertex() {
    }
    
    const size_t& get_neighbour( int index ) const {
        assert( 0 <= index && index < 8 );
        return neighbour_[ index ];
    }
    
    size_t& get_neighbour( int index ){
        assert( 0 <= index && index < 8 );
        return neighbour_[ index ];
    }
    
    bool operator==( const VoxelVertex& other ) const {
        bool result = true;
        for( int i = 0; i < 8 && result; ++i ) {
            result &= other.get_neighbour( i ) == this->get_neighbour( i );
        }
        return result;
    }
    
private:
};

#endif



