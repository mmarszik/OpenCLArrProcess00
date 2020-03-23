__kernel void arr_process_00(__global unsigned int* data, __global unsigned int* outData) {
    const unsigned int id = get_global_id(0);
    __private unsigned int x = data[ id ] * 123;
    for( __private size_t j=0 ; j<10000000 ; j++ ) {
        x = (x * 3) + j;
        if( j & 1 ) {
          x ^= 0xF5E9012A;
        } else {
          x &= 0x7E8A0381;
        }
    }
    outData[ get_global_id(0) ] = x;
}
