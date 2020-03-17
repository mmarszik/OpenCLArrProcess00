__kernel void arr_process_00(__global unsigned int* data, __global unsigned int* outData) {
    const unsigned int id = get_global_id(0);
    unsigned int x = data[ id ] * 123;
    outData[ id ] = x;
}
