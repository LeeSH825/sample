cmake_minimum_required(VERSION 3.12)
project(MARVELS)

set(CMAKE_CURRENT_SOURCE_DIR "../srcs")
set(CMAKE_CURRENT_HEADER_DIR "../includes")

# Add your source files here
set(SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/controller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/neuron.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/learning_module.cpp
)

set(HEADERS
	${CMAKE_CURRENT_HEADER_DIR}/controller.h
	${CMAKE_CURRENT_HEADER_DIR}/neuron.h
	${CMAKE_CURRENT_HEADER_DIR}/learning_module.h
)

# Add any additional include directories here
include_directories(
	${CMAKE_CURRENT_HEADER_DIR}/rapidjson
)

# Add any additional libraries or dependencies here
set(LIBRARIES
	# Add library names here
)


# Set the executable name and link the libraries
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})