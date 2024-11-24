# CMakeList.txt: proyecto de CMake para Proyecto, incluya el origen y defina
# la lógica específica del proyecto aquí.
#

# Agregue un origen al ejecutable de este proyecto.
add_executable (Proyecto "Proyecto.cpp" "Proyecto.h"  "SudokuClass.h" "SudokuClass.cpp" "JsonClass.cpp" "JsonClass.h" "Auxiliares.h" "Auxiliares.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Proyecto PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
if (OpenMP_CXX_FOUND)
  target_link_libraries(Proyecto PUBLIC ${OpenMP_LIBS})
  target_compile_options(Proyecto PUBLIC ${OpenMP_FLAGS})
endif()