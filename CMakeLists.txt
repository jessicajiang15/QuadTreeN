cmake_minimum_required(VERSION 3.13)
find_package(SFML COMPONENTS system window graphics audio REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

find_path(SPLINTER_INCLUDE_DIR NAMES "bspline.h" "bsplinebuilder.h" "datatable.h"
PATHS . external/splinter/include
)


find_library(SPLINTER_LIBRARY_FILE 
NAMES SPLINTER-3-0
PATHS . external/splinter/build
)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})


set(CMAKE_CXX_FLAGS "-O0 -ggdb")
set (CMAKE_CXX_STANDARD 11)


add_executable(QuadTree main.cpp Node.cpp QuadTree.cpp Point.cpp RectangleN.cpp twoVects.cpp Function.cpp GraphicsMechanics.cpp Forest.cpp Gaussian.cpp CompTwoFunc.cpp twoVectsDoub.cpp tripleVect.cpp LegendrePolynomial.cpp TestExponentialFunction.cpp OneDFunction.cpp Test2DExpFcn.cpp Pointint.cpp GaussianN.cpp InterpolatedFunction.cpp)

target_link_libraries(QuadTree sfml-system sfml-window sfml-graphics sfml-audio)

target_include_directories(QuadTree PRIVATE ${SPLINTER_INCLUDE_DIR})
target_link_libraries(QuadTree  ${SPLINTER_LIBRARY_FILE})