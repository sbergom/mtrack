project(mtrack)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Sql REQUIRED)

add_executable(mtrack
               main.cpp
               tracker.cpp
               window.cpp
               entry.cpp
               filter.cpp)

target_link_libraries(mtrack Qt5::Widgets Qt5::Sql)

               
