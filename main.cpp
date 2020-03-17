#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>

//#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/cl.hpp>


using utyp = unsigned int;

static cl::Program createClProgram(const std::string &pathToSrc) {
    std::vector< cl::Platform > platforms;
    cl_int success = cl::Platform::get( &platforms );
    assert( CL_SUCCESS ==  success );
    assert( platforms.size() > 0 );
    auto platform = platforms.front();
    std::vector<cl::Device> devices;
    success = platform.getDevices(CL_DEVICE_TYPE_ALL,&devices);
    assert( CL_SUCCESS ==  success );
    assert( devices.size() > 0 );
    auto device = devices.front();

    std::ifstream file(pathToSrc);
    std::string src( std::istreambuf_iterator<char>(file) , (std::istreambuf_iterator<char>()) );
    cl::Program::Sources sources = { std::pair<const char*,::size_t>(src.c_str(), src.length()+1 ) };
    cl::Context context(device);
    cl::Program program(context,sources);
    success = program.build("-cl-std=CL2.0");
    assert( CL_SUCCESS ==  success );
    return program;
}

int main(int argc, char *argv[] ) {
    cl_int success;
    cl::Program program = createClProgram("arr_process_00.cl");
    auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
    auto devices = program.getInfo<CL_PROGRAM_DEVICES>();
    auto device = devices.front();
    utyp initV = 123;
    std::vector<utyp> vec(1000000);
    for( size_t i=0 ; i<vec.size() ; i++ ) {
        initV = initV * 213453653 + 263408467;
        vec[i] = initV;
    }

    cl::Buffer inBuf(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, sizeof(int)*vec.size(), &vec[0] , &success );
    cl::Buffer outBuf(context,CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY , sizeof(utyp)*vec.size() , nullptr , &success );
    cl::Kernel kernel( program , "arr_process_00");
    success = kernel.setArg(0,inBuf);
    success = kernel.setArg(1,outBuf);
    cl::CommandQueue queue( context , device );
    success = queue.enqueueNDRangeKernel( kernel, cl::NullRange, cl::NDRange(vec.size()) );
    assert( success == CL_SUCCESS );
    success = queue.enqueueReadBuffer( outBuf, CL_FALSE, 0 , sizeof(utyp)*vec.size(), &vec[0] );
    assert( success == CL_SUCCESS );
    cl::finish();

//    for( int i=0 ; i<vec.size() ; i++ ) {
//        unsigned int x = vec[i];
//        vec[i] = x * 123;
//    }

    utyp sum = vec[0];
    for( size_t i=1 ; i<vec.size() ; i++ ) {
        sum ^= (vec[i]   + i);
        sum *= (vec[i-1] + i);
    }
    std::cout << sum << std::endl;

    return 0;
}
