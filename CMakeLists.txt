cmake_minimum_required(VERSION 3.8)
project(AP1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ID.h Employee.cpp Employee.h Jobs.h Classes.h Plane.cpp Plane.h Date.cpp Date.h Flight.cpp Flight.h Reservation.cpp Reservation.h Customer.cpp Customer.h MyImplementation.cpp MyImplementation.h Ex2.h RW.cpp RW.h interface.h)
add_executable(AP1 ${SOURCE_FILES})