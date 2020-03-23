#include <unistd.h>
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
    for( size_t i=0 ; i<platforms.size() ; i++ ) {
        std::string buf;
        std::cout << "Platform " << (i+1) << "] " << std::endl;
        platforms[i].getInfo( CL_PLATFORM_PROFILE , &buf );
        std::cout << "  --profile: " << buf << std::endl;
        platforms[i].getInfo(  CL_PLATFORM_VERSION , &buf );
        std::cout << "  --version: " << buf << std::endl;
        platforms[i].getInfo(  CL_PLATFORM_NAME , &buf );
        std::cout << "  --name: " << buf << std::endl;
        platforms[i].getInfo(  CL_PLATFORM_VENDOR , &buf );
        std::cout << "  --vendor: " << buf << std::endl;
        platforms[i].getInfo(  CL_PLATFORM_EXTENSIONS , &buf );
        std::cout << "  --extensions: " << buf << std::endl;
    }
    auto platform = platforms.front();

    std::vector<cl::Device> devices;
    success = platform.getDevices(CL_DEVICE_TYPE_ALL,&devices);
    assert( CL_SUCCESS ==  success );
    assert( devices.size() > 0 );

    for( size_t i=0 ; i<devices.size() ; i++ ) {
        std::string sBuf;
        int iBuf;

        std::cout << "Device " << (i+1) << "] " << std::endl;
        devices[i].getInfo( CL_DEVICE_ADDRESS_BITS , &iBuf );
        std::cout << "  --address bits: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_AVAILABLE , &iBuf );
        std::cout << "  --available: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_COMPILER_AVAILABLE , &iBuf );
        std::cout << "  --compiler available: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_ENDIAN_LITTLE , &iBuf );
        std::cout << "  --endian little: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_ERROR_CORRECTION_SUPPORT , &iBuf );
        std::cout << "  --error correcton support: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_EXECUTION_CAPABILITIES , &iBuf );
        std::cout << "  --execution capabilities: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_EXTENSIONS , &sBuf );
        std::cout << "  --extensions: " << sBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_GLOBAL_MEM_CACHE_SIZE , &iBuf );
        std::cout << "  --global mem cache size: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_GLOBAL_MEM_CACHE_TYPE , &iBuf );
        std::cout << "  --global mem cache type: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE , &iBuf );
        std::cout << "  --global mem cacheline size: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_GLOBAL_MEM_SIZE , &iBuf );
        std::cout << "  --global mem size: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_IMAGE_SUPPORT , &iBuf );
        std::cout << "  --image support: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_IMAGE2D_MAX_HEIGHT , &iBuf );
        std::cout << "  --image2d max height: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_IMAGE2D_MAX_WIDTH , &iBuf );
        std::cout << "  --image2d max width: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_IMAGE3D_MAX_DEPTH , &iBuf );
        std::cout << "  --image3d max depth: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_IMAGE3D_MAX_HEIGHT , &iBuf );
        std::cout << "  --image3d max height: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_IMAGE3D_MAX_WIDTH , &iBuf );
        std::cout << "  --image3d max width: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_LOCAL_MEM_SIZE , &iBuf );
        std::cout << "  --local mem size: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_LOCAL_MEM_TYPE , &iBuf );
        std::cout << "  --local mem type: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_CLOCK_FREQUENCY , &iBuf );
        std::cout << "  --max clock frequency: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_COMPUTE_UNITS , &iBuf );
        std::cout << "  --max compute units: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_CONSTANT_ARGS , &iBuf );
        std::cout << "  --max constant args: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE , &iBuf );
        std::cout << "  --max constant buffer size: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_MEM_ALLOC_SIZE , &iBuf );
        std::cout << "  --max mem alloc size: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_PARAMETER_SIZE , &iBuf );
        std::cout << "  --max parameter size: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_READ_IMAGE_ARGS , &iBuf );
        std::cout << "  --max read image args: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_SAMPLERS , &iBuf );
        std::cout << "  --max samplers: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_WORK_GROUP_SIZE , &iBuf );
        std::cout << "  --CL_DEVICE_MAX_WORK_GROUP_SIZE: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS , &iBuf );
        std::cout << "  --CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_WORK_ITEM_SIZES , &iBuf );
        std::cout << "  --CL_DEVICE_MAX_WORK_ITEM_SIZES: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MAX_WRITE_IMAGE_ARGS , &iBuf );
        std::cout << "  --CL_DEVICE_MAX_WRITE_IMAGE_ARGS: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MEM_BASE_ADDR_ALIGN , &iBuf );
        std::cout << "  --CL_DEVICE_MEM_BASE_ADDR_ALIGN: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE , &iBuf );
        std::cout << "  --CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_NAME , &iBuf );
        std::cout << "  --CL_DEVICE_NAME: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_PLATFORM , &iBuf );
        std::cout << "  --CL_DEVICE_PLATFORM: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR , &iBuf );
        std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE , &iBuf );
        std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT , &iBuf );
        std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT , &iBuf );
        std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG , &iBuf );
        std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT , &iBuf );
        std::cout << "  --CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_PROFILE , &iBuf );
        std::cout << "  --CL_DEVICE_PROFILE: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_PROFILING_TIMER_RESOLUTION , &iBuf );
        std::cout << "  --CL_DEVICE_PROFILING_TIMER_RESOLUTION: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_QUEUE_PROPERTIES , &iBuf );
        std::cout << "  --CL_DEVICE_QUEUE_PROPERTIES: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_SINGLE_FP_CONFIG , &iBuf );
        std::cout << "  --CL_DEVICE_SINGLE_FP_CONFIG: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_TYPE , &iBuf );
        std::cout << "  --CL_DEVICE_TYPE: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_VENDOR_ID , &iBuf );
        std::cout << "  --CL_DEVICE_VENDOR_ID: " << iBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_VENDOR , &sBuf );
        std::cout << "  --CL_DEVICE_VENDOR: " << sBuf << std::endl;
        devices[i].getInfo( CL_DEVICE_VERSION , &sBuf );
        std::cout << "  --CL_DEVICE_VERSION: " << sBuf << std::endl;
        devices[i].getInfo( CL_DRIVER_VERSION , &sBuf );
        std::cout << "  --CL_DRIVER_VERSION: " << sBuf << std::endl;
    }

    auto device = devices.front();

    std::ifstream file(pathToSrc);
    std::string src( std::istreambuf_iterator<char>(file) , (std::istreambuf_iterator<char>()) );
    cl::Program::Sources sources = { std::pair<const char*, ::size_t>(src.c_str(), src.length()+1 ) };
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
    std::vector<utyp> vec( atoi(argv[1]) );
    for( size_t i=0 ; i<vec.size() ; i++ ) {
        initV = initV * 213453653 + 263408467;
        vec[i] = initV;
    }

    if( atoi(argv[2]) != 0 ) {
        cl::Buffer inBuf(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, sizeof(int)*vec.size(), vec.data() , &success );
        cl::Buffer outBuf(context,CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY , sizeof(utyp)*vec.size() , nullptr , &success );
        cl::Kernel kernel( program , "arr_process_00");
        success = kernel.setArg(0,inBuf);
        success = kernel.setArg(1,outBuf);
        cl::CommandQueue queue( context , device );
        success = queue.enqueueNDRangeKernel( kernel, cl::NullRange, cl::NDRange(vec.size()) );
        assert( success == CL_SUCCESS );
        success = queue.enqueueReadBuffer( outBuf, CL_TRUE, 0 , sizeof(utyp)*vec.size(), vec.data() );
        assert( success == CL_SUCCESS );
        cl::finish();
    } else {
        for( size_t i=0 ; i<vec.size() ; i++ ) {
            unsigned int x = vec[i] * 123;
            for( size_t j=0 ; j<10000000 ; j++ ) {
                x = (x * 3) + j;
                if( j & 1 ) {
                  x ^= 0xF5E9012A;
                } else {
                  x &= 0x7E8A0381;
                }
            }
            vec[i] = x;
        }
    }

//    for( size_t i=0 ; i<vec.size() ; i++ ) {
//        std::cout << (i+1) << "] " << vec[i] << std::endl;
//    }

    utyp sum = vec[0];
    for( size_t i=1 ; i<vec.size() ; i++ ) {
        sum ^= (vec[i]   + i);
        sum *= (vec[i-1] + i);
    }
    std::cout << sum << std::endl;

    return 0;
}
