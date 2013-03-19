//
//  CriticleVertexLUTable.h
//  SubVoxeling
//
//  Created by Burghardt, Eduard on 27.02.13.
//
//

#ifndef __SubVoxeling__CriticleVertexLUTable__
#define __SubVoxeling__CriticleVertexLUTable__

#include <vector>
#include <limits>
#include "VolumeData.h"


typedef typename Type< unsigned char >::criticle_vertex_lu_table_t     criticle_vertex_lu_table_t;

template < typename T >
class VertexPriority {
    typedef VolumeData< T >                     volume_data_t;
public:
    
    static const T  NON_CRITICLE;
    
    VertexPriority()  {
    
    }
    
    ~VertexPriority(){
    }
    
    T operator()( const volume_data_t& soround_vertices ) const {
        assert( soround_vertices.size() == 8 );
        T result = T();
        for( size_t i = 0; i < 4; ++i ){
            if( soround_vertices[ i ] == soround_vertices[ 7 - i ]  ){
                if( std::abs( soround_vertices[ i ] ) > std::abs( result ) ) {
                     result = soround_vertices[ i ];
                }
            }
        }

        if( result == T() ) {
            result = NON_CRITICLE;
        }
            
        return result;
    }
};

            
template< typename T > const T VertexPriority< T >::NON_CRITICLE = std::numeric_limits< T >::max();
            

typedef VertexPriority< unsigned char > vrtx_prioritx_det_t;

template< typename T,  class PriorityDeterminator = VertexPriority< T > >
class CriticleVertexLUtable {
public:
    typedef VolumeData< T >                                    volume_data_t;

    typedef T                                                  dominat_vertex_t;
    typedef std::vector< dominat_vertex_t >                    dominat_vertices_t;
    typedef typename Type< T >::criticle_vertex_lu_table_t     criticle_vertex_lu_table_t;


private:

    const VolumeResolution                      resolution_;
    dominat_vertices_t                          dominat_vrtx_lut_;
    
    
    void create_dominane_vrtx_lut( const volume_data_t* data, const PriorityDeterminator& priority_determinator ) {
        const size_t size = resolution_.get_x() * resolution_.get_y() * resolution_.get_z();
        dominat_vrtx_lut_.resize( size, PriorityDeterminator::NON_CRITICLE );
        for( size_t iz = 1; iz < data->get_resolution().get_z(); ++iz  ){
            for( size_t iy = 1; iy < data->get_resolution().get_y(); ++iy  ){
                for( size_t ix = 1; ix < data->get_resolution().get_x(); ++ix  ){
                    dominat_vrtx_lut_[ resolution_.convert( ix, iy, iz ) ] = priority_determinator( get_voxels_contain_vrtx(*data, ix, iy, iz ) );
                }
            }
        }
    }
    
public:
    
    
    CriticleVertexLUtable( const volume_data_t*  data, const PriorityDeterminator& priority_determinator = VertexPriority< T >() ) :
                                resolution_( data->get_resolution().get_x() + 1,
                                             data->get_resolution().get_y() + 1,
                                             data->get_resolution().get_x() + 1
                                           ){
       create_dominane_vrtx_lut( data, priority_determinator );
    }
    
    ~CriticleVertexLUtable(){
    }

    bool criticle_vrtx( const size_t& index ) const {
        assert( index < dominat_vrtx_lut_.size() );
        const bool result = dominat_vrtx_lut_[ index ] != PriorityDeterminator::NON_CRITICLE;
        return result;
    }
    
    bool criticle_vrtx( const size_t& x, const size_t& y, const size_t& z ) const {
       const bool result = dominat_vrtx_lut_[ resolution_.convert( x, y, z ) ] != PriorityDeterminator::NON_CRITICLE;
       return result;
    }

    
    dominat_vertex_t dominant_vrtx( const size_t& index ) const {
        assert( index < dominat_vrtx_lut_.size() );
        const dominat_vertex_t result = dominat_vrtx_lut_[ index ];
        return result;
    }
    
    dominat_vertex_t dominant_vrtx(  const size_t& x, const size_t& y, const size_t& z ) const {
        const dominat_vertex_t result = dominat_vrtx_lut_[ resolution_.convert( x, y, z ) ];
        return result;
    }
    
};

typedef CriticleVertexLUtable< unsigned char >  criticle_vrtx_lut_t;



template< typename T >
inline criticle_vertex_lu_table_t create_criticle_vertex_lu_table( const VolumeData< T >& volume_data ){
    const size_t vertex_size = ( volume_data.get_resolution().get_x() + 1 ) *
                               ( volume_data.get_resolution().get_y() + 1 ) *
                               ( volume_data.get_resolution().get_z() + 1 );

    criticle_vertex_lu_table_t result( vertex_size, -1 );
      
    return result;
}

#endif /* defined(__SubVoxeling__CriticleVertexLUTable__) */
