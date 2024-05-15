set(src_dirs
        LED
        EXIT
        UART
        TIMER
        CAN
        I2C
        ESP_NOW_COMM)
        

set(include_dirs
        LED
        EXIT
        UART
        TIMER
        CAN
        I2C
        ESP_NOW_COMM)

# 其实，这个就是esp/v5.2.1/esp-idf/components/下的组建，到那个文件夹下可以看到如下文件夹
# dirver文件夹、esp_timer文件夹、esp_timer文件夹等
set(requires
        driver
        freertos
        esp_timer
        esp_wifi
        nvs_flash)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS
                        ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -Wno-error=format=-Wno-format)
# -O3: 这是一个优化级别选项，指示编译器尽可能地进行高级优化以生成更高效的代码。
#-Wno-error=format: 这将编译器关于格式字符串不匹配的警告从错误降级为警告。
#-Wno-format: 这将完全禁用关于格式字符串的警告。