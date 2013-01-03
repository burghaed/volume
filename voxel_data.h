//
//  voxel_data.h
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 10.10.12.
//
//

#ifndef __SubVoxeling__voxel_data__
#define __SubVoxeling__voxel_data__

#include <vector>
#include <assert.h>

template < typename T >
class VoxelData {
public:
    
    typedef typename std::vector< T >::const_iterator   const_iterator;
    typedef typename std::vector< T >::iterator   iterator;
    
      
    VoxelData() : nx_( 0 ), nx_ny_( 0 ){
        resolution_[ 0 ] = resolution_[ 1 ] = resolution_[ 2 ] = 0;
    }
    
    VoxelData( const size_t res[ 3 ], const T* data ) : nx_( 0  ), nx_ny_( 0 ){
        assert(data);
        set_resolution( res );
        std::copy(data, data + data_.size(), data_.begin() );
    }
    
    ~VoxelData(){
    }
    
    const T& operator()( size_t ix, size_t iy, size_t iz ) const{
        const size_t index = calc_index(ix, iy, iz );
        return data_[ index ];
    }
    
    T& operator()( size_t ix, size_t iy, size_t iz ){
        const size_t index = calc_index(ix, iy, iz );
        return data_[ index ];

    }
    
    const T& operator[]( size_t index ) const{
        assert( index < data_.size() );
        return data_[ index ];
    }
    
    T& operator[]( size_t index ) {
        assert( index < data_.size() );
        return data_[ index ];
    }
    
    void set_resolution( const size_t res[3] ){
        assert( res[ 0 ] != 0 && res[ 1 ] != 0 && res[ 2 ] != 0 );
        std::copy(res, res + 3, resolution_ );
        nx_        = resolution_[ 0 ];
        nx_ny_     = resolution_[ 0 ] * resolution_[ 1 ];
        data_.resize( nx_ny_ * resolution_[ 2 ] );
    }
    
    const size_t* get_resolution() const {
        return resolution_;
    }
    
private:
    
    size_t calc_index( size_t ix, size_t iy, size_t iz ) const {
        assert( ix < resolution_[ 0 ] );
        assert( iy < resolution_[ 1 ] );
        assert( iz < resolution_[ 2 ] );
        const size_t result = ix + nx_ * iy  + nx_ny_ * iz ;
        assert( result < data_.size() );
        return result;
    }
    
    size_t                      resolution_[3];
    size_t                      nx_, nx_ny_;
    std::vector< T >            data_;
        
    
};

typedef VoxelData< unsigned char >          voxel_data_t;

#endif /* defined(__SubVoxeling__voxel_data__) */
