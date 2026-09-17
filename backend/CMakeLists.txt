find_package(Qt6 REQUIRED COMPONENTS Core HttpServer Sql)

add_library(scheduler_core
    src/scheduler/ConflictGraph.cpp
    src/scheduler/Coloring.cpp
)

target_include_directories(scheduler_core PUBLIC include)
target_compile_features(scheduler_core PUBLIC cxx_std_20)

if(MSVC)
    target_compile_options(scheduler_core PRIVATE /W4)
else()
    target_compile_options(scheduler_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(ENABLE_WARNINGS_AS_ERRORS)
    if(MSVC)
        target_compile_options(scheduler_core PRIVATE /WX)
    else()
        target_compile_options(scheduler_core PRIVATE -Werror)
    endif()
endif()

add_executable(smart_timetable_api src/main.cpp)
target_link_libraries(smart_timetable_api PRIVATE Qt6::Core Qt6::HttpServer Qt6::Sql scheduler_core)

add_executable(scheduler_tests tests/scheduler_tests.cpp)
target_link_libraries(scheduler_tests PRIVATE scheduler_core)
add_test(NAME scheduler_tests COMMAND scheduler_tests)
