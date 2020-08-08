#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_ShareLib _target)

   target_link_libraries(${_target} ShareLib)

endfunction()

function(my_inc_import_ShareLib _target)

   target_include_directories(${_target} PRIVATE $<TARGET_PROPERTY:ShareLib,INTERFACE_INCLUDE_DIRECTORIES>)

endfunction()

