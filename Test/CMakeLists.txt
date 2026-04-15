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
    Castling_Tests.cpp

    ../Chess_Engine/MOVEMENT_PIECE/Movement_Piece.cpp
    ../Chess_Engine/FEN/Handle_Fen_String.cpp 
    ../Chess_Engine/MOVE/Move.cpp 
    ../Chess_Engine/PIN/Handle_Pin.cpp
    ../Chess_Engine/ENPASSANT/Handle_Enpassant.cpp
    ../Chess_Engine/UPDATE_MOVES/Update_Moves.cpp
    ../Chess_Engine/CASTLING/Castling.cpp
    ../Chess_Engine/FIND_KING/Find_King.cpp
    ../Chess_Engine/CHECK/Check.cpp
    ../Chess_Engine/PROMOTION_PAWN/Promotion_Pawn.cpp
    ../Chess_Engine/CREATE_PIECE/Create_Piece.cpp 
    ../Chess_Engine/CHESSBOARD_TURN/Handle_Chessboard.cpp

    ../Draw_board.cpp 
    ../Es13.cpp 
    ../Draw_Promotion_Dialog.cpp
     
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