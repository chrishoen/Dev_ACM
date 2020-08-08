cmake_minimum_required (VERSION 3.8)

project (ShareLibACM CXX)

my_find_src_files (src_files ShareLibACM)
my_find_inc_files (inc_files)
add_library (ShareLibACM SHARED ${src_files})
my_add_compile_options_so (ShareLibACM)
my_add_pch (ShareLibACM)

target_include_directories(ShareLibACM INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(ShareLibACM)

if (MSVC OR CMAKE_SYSTEM_VERSION EQUAL 101)
   install(FILES ${inc_files} DESTINATION "C:/MyTools/MyLib/include/ShareLibACM")
   install(TARGETS ShareLibACM DESTINATION "C:/MyTools/MyLib/lib")
else()
   install(FILES ${inc_files} DESTINATION "/usr/local/include/ShareLibACM")
   install(TARGETS ShareLibACM DESTINATION "/usr/local/lib")
endif()

if(CMAKE_SYSTEM_VERSION EQUAL 101)
   install(FILES ${inc_files} DESTINATION "C:/MyTools/MyLib/include/ShareLibACM")
   install(TARGETS ShareLibACM DESTINATION "C:/MyTools/MyLib/lib")
   add_custom_command(
      TARGET  ShareLibACM
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx libShareLibACM.so rsync://debian@bbacm/prime/stage
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_ACM/ShareLibACM)
endif()

