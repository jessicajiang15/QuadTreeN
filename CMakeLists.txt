cmake_minimum_required(VERSION 3.13)
find_package(SFML COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "-O0 -ggdb")
set (CMAKE_CXX_STANDARD 11)


add_executable(QuadTree main.cpp Node.cpp QuadTree.cpp Point.cpp RectangleN.cpp twoVects.cpp Function.cpp GraphicsMechanics.cpp Forest.cpp Gaussian.cpp CompTwoFunc.cpp twoVectsDoub.cpp tripleVect.cpp LegendrePolynomial.cpp TestExponentialFunction.cpp OneDFunction.cpp Test2DExpFcn.cpp Pointint.cpp GaussianN.cpp)

target_link_libraries(QuadTree sfml-system sfml-window sfml-graphics sfml-audio)