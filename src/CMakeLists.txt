set(SOURCES main.cpp cloak_remover.cpp cloak_remover.h)

add_executable(invisibility_cloak ${SOURCES})
target_link_libraries(invisibility_cloak PRIVATE CONAN_PKG::opencv)
