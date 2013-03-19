#include <iostream>
#include "VolumeData.h"
#include "CriticleVertexLUTable.h"



inline signed_volume_data_t create_volume_data_2() {
    signed_volume_data_t result( 2, 2, 2 );
    //    result( 1, 0 ,0 ) = 2;
    //    result( 0, 1, 1 ) = 2;
    //
    //    result( 1, 0 ,1 ) = 3;
    //    result( 0, 1, 0 ) = 3;
    
    result( 0, 0 ,0 ) = -5;
    result( 1, 1, 1 ) = -5;
    return result;
}

inline volume_data_t create_volume_data() {
    volume_data_t result( 2, 2, 2 );
    result( 0, 0 ,0 ) = 1;
    result( 1, 1, 1 ) = 1;
    return result;
}

int main (int argc, char * const argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    const volume_data_t data1 = create_volume_data();
    criticle_vrtx_lut_t table( &data1 );
    assert( table.criticle_vrtx( 1, 1, 1 ) );


    return 0;
}
