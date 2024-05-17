add_library(pico-eeprom24xx01 INTERFACE)

target_include_directories(pico-eeprom24xx01
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(pico-eeprom24xx01
  INTERFACE
  hardware_i2c
)

target_sources(pico-eeprom24xx01
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/eeprom24xx01.c
  ${CMAKE_CURRENT_LIST_DIR}/include/eeprom24xx01.h
)
