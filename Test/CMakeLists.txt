cmake_minimum_required(VERSION 3.5.0)

set(GTEST_DIR "${CMAKE_SOURCE_DIR}/Test/lib/googletest-main") 

include_directories("${GTEST_DIR}/include")
include_directories("${GTEST_DIR}")

add_subdirectory("${GTEST_DIR}" "${CMAKE_BINARY_DIR}/googletest-build")

set(TEST_SOURCE_FILES main_test.cpp)

add_executable(w_test 
    main_test.cpp
    Move_Test.cpp
    Chessboard_Test.cpp
    ../Movement_Piece.cpp
    ../Handle_Fen_String.cpp 
    ../Move.cpp 
    ../Create_Piece.cpp 
    ../Draw_board.cpp 
    ../Es13.cpp 
    ../Handle_Chessboard.cpp 
    ../Handle_Mouse_Input.cpp  
    ../Piece_factory/Piece.cpp 
    ../Piece_factory/Bishop/Bishop.cpp 
    ../Piece_factory/King/King.cpp 
    ../Piece_factory/Knight/Knight.cpp 
    ../Piece_factory/Pawn/Pawn.cpp 
    ../Piece_factory/Queen/Queen.cpp 
    ../Piece_factory/Rock/Rock.cpp
    ../start/MyProjectBase.cpp
)

target_link_libraries(w_test PRIVATE GTest::gtest ${wxWidgets_LIBRARIES})