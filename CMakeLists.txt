project(zmq-assert-bug)

include(FetchContent)
FetchContent_Declare(libzmq
  GIT_REPOSITORY https://github.com/zeromq/libzmq.git
  GIT_TAG v4.3.2
)
FetchContent_MakeAvailable(libzmq)
add_executable(repro main.cpp)
target_compile_features(repro PRIVATE cxx_std_11)
target_link_libraries(repro libzmq-static)
target_compile_definitions(repro PRIVATE ZMQ_BUILD_DRAFT_API)
