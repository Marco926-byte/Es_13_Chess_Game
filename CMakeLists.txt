cmake_minimum_required(VERSION 3.5.0)

project(w VERSION 0.1.0 LANGUAGES C CXX)

# Richiedi wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# 1. Definisci i file sorgente della LOGICA (tutto tranne il Main/App)
set(GAME_SOURCE_FILES
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
    Handle_Fen_String.cpp
    Movement_Piece.cpp
    Create_Piece.cpp
    Handle_Mouse_Input.cpp
    Move.cpp
    Draw_Promotion_Dialog.cpp
)

# 2. Crea una LIBRERIA STATICA con la logica del gioco
# Chiamiamola "w_lib" così i test la trovano
add_library(w_lib STATIC ${GAME_SOURCE_FILES})

# La libreria ha bisogno di wxWidgets per compilare (se usi wxString, wxPoint, ecc nei file sopra)
target_link_libraries(w_lib PRIVATE ${wxWidgets_LIBRARIES})

# 3. Crea l'ESEGUIBILE DEL GIOCO (Il Main)
# Qui metti solo i file che fanno partire l'app (presumo Es13.cpp e MyApp.cpp)
add_executable(${PROJECT_NAME} 
    Es13.cpp
    MyApp.cpp
)

# Linka l'eseguibile alla TUA libreria e a wxWidgets
target_link_libraries(${PROJECT_NAME} w_lib ${wxWidgets_LIBRARIES})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_subdirectory(Test)

include(CPack)