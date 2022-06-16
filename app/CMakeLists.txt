include_directories(hybrid-lambda/include)

add_executable(hybridlambda main.cpp)

target_link_libraries(hybridlambda
                      Boost::boost
                    )
# We need C++ 20 activated with the concepts library
target_compile_features(hybridlambda PUBLIC cxx_std_20)

install(
  TARGETS
    hybridlambda
  RUNTIME
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    COMPONENT bin
)
