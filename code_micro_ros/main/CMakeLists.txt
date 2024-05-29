idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES micro_ros_espidf_component #告诉编译器components/micro_ros_espidf_component
                    REQUIRES BSP) #告诉编译器components/BSP 
