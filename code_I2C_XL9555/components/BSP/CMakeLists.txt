set(src_dirs
        LED
        EXIT
        UART
        TIMER
        CAN)

set(include_dirs
        LED
        EXIT
        UART
        TIMER
        CAN)

set(requires
        driver
        esp_timer)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS
                        ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math)
# -O3: 这是一个优化级别选项，指示编译器尽可能地进行高级优化以生成更高效的代码。
#-Wno-error=format: 这将编译器关于格式字符串不匹配的警告从错误降级为警告。
#-Wno-format: 这将完全禁用关于格式字符串的警告。