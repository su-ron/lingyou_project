cmake_minimum_required(VERSION 3.5)
project(mpc_polynomial_third)

## Compile as C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11 -O3)

# options for build configuration
option(BUILD_EXAMPLE "Whether or not building the CppAD & Ipopt example" OFF) 

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  geometry_msgs
  nav_msgs
  ackermann_msgs
  message_generation
  roscpp
  rospy
  std_msgs
  tf
  visualization_msgs
  custom_msgs_srvs
  util
)

# uncomment the following 4 lines to use the Eigen library
find_package(cmake_modules REQUIRED)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
add_definitions(${EIGEN_DEFINITIONS})

catkin_package(
   INCLUDE_DIRS include
#  LIBRARIES hypharos_minicar
#  CATKIN_DEPENDS costmap_2d dynamic_reconfigure geometry_msgs message_generation move_base roscpp rospy std_msgs tf visualization_msgs
#  DEPENDS system_lib
 LIBRARIES ${PROJECT_NAME}
 CATKIN_DEPENDS util
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories( ${catkin_INCLUDE_DIRS} include )
include_directories(/usr/include)
link_directories(/usr/lib)

# MPC_Node
#ADD_EXECUTABLE( MPC_Node src/MPC.cpp src/MPC_Node.cpp )
#TARGET_LINK_LIBRARIES(MPC_Node ipopt ${catkin_LIBRARIES} )


set(PATH_GENERATOR_SRCS
    src/common/path/path_generator.cc
    src/common/path/path_utils.cc
    src/common/math/cartesian_frenet_conversion.cc
    src/common/math/curve_math.cc
    src/common/math/lowpass_filter.cc
    src/common/math/math_utils.cc
    src/common/math/quintic_polynomial.cc
    src/common/math/transform.cc
    src/common/math/vec2d.cc
    src/common/line/line_utils.cc
    src/common/data_types/pnc_point.cc
    src/common/utils/linear_interpolation.cpp
    src/common/math/line_segment2d.cc
    )
ADD_EXECUTABLE( path_generator_test_third_node
    src/common/path/path_generator_test.cc
  ${PATH_GENERATOR_SRCS})

TARGET_LINK_LIBRARIES(path_generator_test_third_node ${catkin_LIBRARIES} )

# Local planner with MPC_Node for tracking
ADD_EXECUTABLE( tracking_reference_trajectory_third src/trackRefTraj.cpp src/trackRefTrajNode.cpp ${PATH_GENERATOR_SRCS})
TARGET_LINK_LIBRARIES(tracking_reference_trajectory_third ipopt ${catkin_LIBRARIES} )


install(TARGETS  tracking_reference_trajectory_third path_generator_test_third_node
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(DIRECTORY launch 
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

#############
## Example ##
#############
if(BUILD_EXAMPLE)
    ADD_EXECUTABLE( CppAD_started example/CppAD_started.cpp )
    TARGET_LINK_LIBRARIES(CppAD_started)
    
    ADD_EXECUTABLE( CppAD_Ipopt example/CppAD_Ipopt.cpp )
    TARGET_LINK_LIBRARIES(CppAD_Ipopt ipopt)
endif(BUILD_EXAMPLE)
