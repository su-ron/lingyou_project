cmake_minimum_required(VERSION 3.0.2)
project(curve_generation)

find_package(catkin REQUIRED COMPONENTS
  angles
  roscpp
  util
)

find_package(Eigen3 REQUIRED)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES ${PROJECT_NAME}
 CATKIN_DEPENDS util
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/curve.cpp
  src/bspline_curve.cpp
  src/bezier_curve.cpp
  src/cubic_spline_curve.cpp
  src/dubins_curve.cpp
  src/polynomial_curve.cpp
  src/reeds_shepp_curve.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

install(TARGETS  ${PROJECT_NAME}
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)