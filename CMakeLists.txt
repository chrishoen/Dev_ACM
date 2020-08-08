cmake_minimum_required (VERSION 3.8)

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/MyOverrides.cmake")
include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)

project ("Dev_ACM")
my_init_global_import_variables()

add_subdirectory ("ShareLibACM")
add_subdirectory ("acmproc")
return()

add_subdirectory ("Test")
add_subdirectory ("commtest")
return()


add_subdirectory ("Test")
return()

add_subdirectory ("CommonLib")
add_subdirectory ("commtest")
add_subdirectory ("Experiment")
add_subdirectory ("Test")
return()

add_subdirectory ("Experiment")
return()

