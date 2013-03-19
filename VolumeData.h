//
//  voxel_data.h
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 10.10.12.
//
//

#ifndef __SubVoxeling__volume_data__
#define __SubVoxeling__volume_data__

#include <vector>
#include <assert.h>
#include <utility>



class VolumeResolution {
public:
    VolumeResolution( const size_t& res_x, const size_t& res_y, const size_t& res_z ){
        resolution_[ 0 ] = res_x;
        resolution_[ 1 ] = res_y;
        resolution_[ 2 ] = res_z;
        
        dir_offset_[ 0 ] = 1;
        dir_offset_[ 1 ] = res_x;
        dir_offset_[ 2 ] = res_x * res_y;
    }
    
    ~VolumeResolution(){
    }
    const size_t& operator[]( const size_t& i ) const {
        assert( 0 <= i && i < 3 );
        return resolution_[ i ];
    }
    
    const size_t& get_x() const {
        return resolution_[ 0 ];
    }

    
    const size_t& get_y() const {
        return resolution_[ 1 ];
    }

    
    const size_t& get_z() const {
        return resolution_[ 2 ];
    }
    
    
    const size_t& get_x_offset() const {
        return dir_offset_[ 0 ];
    }
    
    const size_t& get_y_offset() const {
        return dir_offset_[ 1 ];
    }
    
    const size_t& get_z_offset() const {
        return dir_offset_[ 2 ];
    }

    
    const size_t convert( const size_t& x, const size_t& y, const size_t& z ) const {
        const size_t result = x + dir_offset_[ 1 ] * y + dir_offset_[ 2 ] * z;
        return result;
    }
    
    const size_t convert( const size_t index[ 3 ] ) const {
        const size_t result = convert(index[ 0 ], index[ 1 ], index[ 2 ] );
        return result;
    }
    
    void convert( const size_t& index, size_t& x, size_t& y, size_t& z ) const{
        z                           = index / get_z_offset();
        const size_t index_minus_z  = index - z * get_z_offset();
        y                           = index_minus_z / get_y_offset();
        x = index_minus_z - y * get_y_offset();
    }
    
    void convert( const size_t& index, size_t result_index[ 3 ] ) const{
        convert( index, result_index[ 0 ], result_index[ 1 ], result_index[ 2 ] );
    }

private:
    size_t  resolution_[ 3 ];
    size_t  dir_offset_[ 3 ];
};



template < typename T >
class VolumeData {
    typedef std::vector< T >        data_container_t;
public:
    
    typedef typename data_container_t::iterator          iterator;
    typedef typename data_container_t::const_iterator    const_iterator;
    
    VolumeData( const size_t& res_x, const size_t& res_y, const size_t& res_z ) : resolution_( res_x, res_y, res_z ), size_( res_x * res_y * res_z  ){
        assert( size_ > 0 );
        data_.resize( size_ );
    }
        
    ~VolumeData(){
    }
    
    const T& operator()( const size_t& x, const size_t& y, const size_t& z ) const {
        const size_t index = resolution_.get_x_offset() * x +
                             resolution_.get_y_offset() * y +
                             resolution_.get_z_offset() * z;
        return this->operator[]( index );
    }
    
    T& operator()( const size_t& x, const size_t& y, const size_t& z ) {
        const size_t index = resolution_.get_x_offset() * x +
        resolution_.get_y_offset() * y +
        resolution_.get_z_offset() * z;
        return this->operator[]( index );
    }
    
    const size_t& size() const{
        assert( data_.size() == size_ );
        return size_;
    }
        
    T& operator[]( const size_t& index ) {
        assert( index < data_.size() );
        return data_[ index ];
    }

    const T& operator[]( const size_t& index ) const {
        assert( index < data_.size() );
        return data_[ index ];
    }
    
    const VolumeResolution& get_resolution() const {
        return resolution_;
    }

    
    iterator begin() {
        return  data_.begin();
    }
    
    const_iterator begin() const {
        return  data_.begin();
    }
    
    iterator end() {
        return  data_.end();
    }
    
    const_iterator end() const {
        return  data_.end();
    }
private:
    
    void init( const size_t& res_x, const size_t& res_y, const size_t& res_z ) {
    }
    
    VolumeResolution        resolution_;
    size_t                  size_;
    data_container_t        data_;
    
    
};

typedef VolumeData< unsigned char >         volume_data_t;
typedef VolumeData< int >                   signed_volume_data_t;


template< typename T >
struct Type {
    typedef std::vector< T>    criticle_vertex_lu_table_t;
    typedef VolumeData< T >    vrtx_to_surrounded_voxel_t;
};



template< typename T >
inline typename Type< T >::vrtx_to_surrounded_voxel_t  get_voxels_contain_vrtx( const VolumeData< T >& volume_data,
                                                                   const size_t& x,
                                                                   const size_t& y,
                                                                   const size_t& z ) {
    
    const size_t x_res = x == 0 || x == volume_data.get_resolution().get_x() ?  1 :  2;
    const size_t y_res = y == 0 || y == volume_data.get_resolution().get_y() ?  1 :  2;
    const size_t z_res = z == 0 || z == volume_data.get_resolution().get_z() ?  1 :  2;
    typename Type< T >::vrtx_to_surrounded_voxel_t result( x_res, y_res, z_res );
    
    for( size_t iz = 0 ; iz < z_res; ++iz  ){
        for( size_t iy = 0; iy < y_res; ++iy  ){
            for( size_t ix = 0; ix < x_res; ++ix  ){
                result( x_res - 1 - ix, y_res - 1 - iy, z_res - 1 - iz ) = volume_data( x - ix, y - iy, z - iz );
            }
        }
    }
    
    return result;
    
}



enum dir_t{
    X_DIR, Y_DIR, Z_DIR
};

typedef std::pair< size_t, dir_t > edge_index_t;

template< typename T >
inline  VolumeData< T >  get_voxels_contain_edge( const VolumeData< T >& volume_data,
                                                   const edge_index_t& edge_index ) {
    size_t index[ 3 ] = { 0 };
    size_t res[ 3 ] = { 0 };
    volume_data.get_resolution().convert( edge_index.first, index );
    for( size_t i = 0; i < 3; ++i ) {
        res[ i ] = index[ i ] == 0 || index[ i ] == volume_data.get_resolution()[ i ] ? 1 : 2;
    }
    res[ edge_index.second ] = 1;
    
    VolumeData< T > result( res[ 0 ], res[ 1 ], res[ 2 ] );
    
    for( size_t iz = 0 ; iz < res[ 2 ]; ++iz  ){
        for( size_t iy = 0; iy < res[ 1 ]; ++iy  ){
            for( size_t ix = 0; ix < res[ 0 ]; ++ix  ){
                result( res[ 0 ] - 1 - ix, res[ 1 ] - 1 - iy, res[ 2 ] - 1 - iz ) = volume_data( index[ 0 ] - ix, index[ 1 ] - iy, index[ 2 ] - iz );
            }
        }
    }

    return result;
}





#endif /* defined(__SubVoxeling__voxel_data__) */
