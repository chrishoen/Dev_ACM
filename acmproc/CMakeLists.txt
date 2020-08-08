cmake_minimum_required (VERSION 3.8)

project (acmproc CXX)
my_find_src_files (src_files acmproc)
add_executable (acmproc ${src_files})
my_add_compile_options (acmproc)
my_add_pch (acmproc)

my_inc_import_RisLib(acmproc)
my_inc_import_ShareLibACM(acmproc)

my_lib_import_ShareLibACM(acmproc)
my_lib_import_RisLib(acmproc)

if (MSVC)
   add_custom_command(
      TARGET  acmproc
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy acmproc.exe c:/aaa_cproc/bin/acmproc.exe
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_NP_TTA_ShareLib/acmproc)
elseif(NOT CMAKE_SYSTEM_VERSION EQUAL 101)
   install(TARGETS acmproc DESTINATION "/opt/prime/bin")
else()
   add_custom_command(
      TARGET  acmproc
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx acmproc rsync://debian@bbacm/prime/bin
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_ACM/acmproc)
endif()

