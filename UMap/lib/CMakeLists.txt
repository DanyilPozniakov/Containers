
#if(MYUMAP_SHARED_LIBS)
#    add_library(UMap SHARED UMap.cpp)
#else()
#    add_library(UMap STATIC UMap.cpp)
#endif()

add_library(UMap INTERFACE)
target_include_directories(UMap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})