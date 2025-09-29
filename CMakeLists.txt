cmake_minimum_required(VERSION 3.5.0)
project(w VERSION 0.1.0 LANGUAGES C CXX)

add_executable(${PROJECT_NAME} 
    Es13.cpp
    MyApp.cpp
    start/MyProjectBase.cpp
    Draw_board.cpp
    Piece_factory/Piece.cpp
    Piece_factory/Bishop/Bishop.cpp
    Piece_factory/Pawn/Pawn.cpp
    Piece_factory/Queen/Queen.cpp
    Piece_factory/Rock/Rock.cpp 
    Piece_factory/Knight/Knight.cpp 
    Piece_factory/King/King.cpp
    Handle_Chessboard.cpp
    Movement_Handler.cpp
    Handle_Fen_String.cpp
    Movement_Piece.cpp
    Create_Piece.cpp
)
# Richiedi wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
# Includi e link automatici
include(${wxWidgets_USE_FILE})



include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
# Linka wxWidgets alle librerie
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

#include(FetchContent) 


#FetchContent_Declare(
#    googletest
#    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
#)

#FetchContent_MakeAvailable(googletest)

#include(GoogleTest)
#gtest_discover_tests(w)