#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_ShareLibACM _target)

   target_link_libraries(${_target} ShareLibACM)

endfunction()

function(my_inc_import_ShareLibACM _target)

   target_include_directories(${_target} PRIVATE $<TARGET_PROPERTY:ShareLibACM,INTERFACE_INCLUDE_DIRECTORIES>)

endfunction()

