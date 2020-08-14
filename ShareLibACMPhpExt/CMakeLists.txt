cmake_minimum_required (VERSION 3.8)

project (ShareLibACMPhpExt CXX)

my_find_src_files (src_files ShareLibACMPhpExt)
add_library (ShareLibACMPhpExt SHARED ${src_files})
my_add_compile_options (ShareLibACMPhpExt)
my_add_pch (ShareLibACMPhpExt)


my_inc_import_RisLib(ShareLibACMPhpExt)
my_inc_import_ShareLibACM(ShareLibACMPhpExt)
my_inc_import_phpcpp(ShareLibACMPhpExt)

my_lib_import_RisLib(ShareLibACMPhpExt)
my_lib_import_ShareLibACM(ShareLibACMPhpExt)
my_lib_import_phpcpp(ShareLibACMPhpExt)

set_target_properties(ShareLibACMPhpExt PROPERTIES PREFIX "")

if(CMAKE_SYSTEM_VERSION EQUAL 101)
   add_custom_command(
      TARGET  ShareLibACMPhpExt
      POST_BUILD
      COMMAND rsync -azv --chmod=ugo=rwx ShareLibACMPhpExt.so rsync://debian@bbacm/prime/stage
      WORKING_DIRECTORY C:/Users/$ENV{username}/CMakeBuilds/Dev_NP_TTA_ShareLibACM/ShareLibACMPhpExt)
endif()

