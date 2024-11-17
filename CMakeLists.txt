cmake_minimum_required (VERSION 3.12)

project ("StupidCalculator" LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable (StupidCalculator 
	"StupidCalculator.cpp"
)

target_compile_features(StupidCalculator PRIVATE cxx_std_20)
