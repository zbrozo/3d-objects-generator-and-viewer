cmake_minimum_required(VERSION 3.10)

project(obj3d)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${obj3d_SOURCE_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Boost COMPONENTS filesystem system unit_test_framework program_options log REQUIRED)

set(BasicMathSRC
  src/Face.cpp
  src/Rotation.cpp
  src/Vertex3D.cpp
  src/Vector3D.cpp
  src/Object3D.cpp
  src/Vertices.cpp
  src/Vectors.cpp
  src/Faces.cpp
)

set(FactoriesSRC
  src/ObjectFactoryBase.cpp
  src/ObjectFactories.cpp
  src/ComponentFactoryBase.cpp
  src/ComponentFactories.cpp
  src/Components.cpp
  src/Cube.cpp
  src/CubeExt.cpp
  src/Thorus.cpp
  src/Composite.cpp
)

set(GeneratorSRC
  src/GeneratorMain.cpp
  src/ZbrFormatConverter.cpp
  src/FileSaver.cpp
)

set(ViewerSRC
  src/ViewerMain.cpp
  src/ViewerSortingFaces.cpp
  src/ViewerPerspective.cpp
  src/ViewerLight.cpp
  src/ViewerRotate.cpp
  src/ViewerDraw.cpp
  src/ZbrFormatConverter.cpp
  src/FileLoader.cpp
)

set(TestsSRC
  src/UnitTests.cpp
  src/VertexTests.cpp
  src/VectorTests.cpp
  src/ComponentsTests.cpp
  src/ObjectFactoryTests.cpp
  src/ZbrFormatConverter.cpp
  src/ZbrFormatConverterTests.cpp
)

add_library(basicmath STATIC ${BasicMathSRC})
add_library(factories STATIC ${FactoriesSRC})
add_executable(generator ${GeneratorSRC})
add_executable(viewer ${ViewerSRC})
add_executable(tests ${TestsSRC})

include_directories(${Boost_INCLUDE_DIRS})

set_target_properties(basicmath PROPERTIES CXX_STANDARD 17)
set_target_properties(factories PROPERTIES CXX_STANDARD 17)
set_target_properties(generator PROPERTIES CXX_STANDARD 17)
set_target_properties(viewer PROPERTIES CXX_STANDARD 17)
set_target_properties(tests PROPERTIES CXX_STANDARD 17)

set(FLAGS -Wall -Wextra -Wpedantic)
target_compile_options (basicmath PRIVATE ${FLAGS})
target_compile_options (factories PRIVATE ${FLAGS})
target_compile_options (generator PRIVATE ${FLAGS})
target_compile_options (viewer PRIVATE ${FLAGS})
target_compile_options (tests PRIVATE ${FLAGS})

target_include_directories(viewer PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(viewer PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(viewer PRIVATE ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(basicmath PRIVATE ${Boost_LIBRARIES} )
target_link_libraries(factories PRIVATE ${Boost_LIBRARIES} )
target_link_libraries(generator PRIVATE factories basicmath ${Boost_LIBRARIES} )
target_link_libraries(viewer PRIVATE factories basicmath SDL2::Main SDL2::Image SDL2::TTF ${Boost_LIBRARIES})
target_link_libraries(tests PRIVATE factories basicmath ${Boost_LIBRARIES})

enable_testing()
add_test(
  NAME unittests
  COMMAND $<TARGET_FILE:tests>
)
