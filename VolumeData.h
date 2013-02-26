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
    
    const T& operator()( const size_t& x, const size_t& y, const size_t& z ) {
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

#endif /* defined(__SubVoxeling__voxel_data__) */
