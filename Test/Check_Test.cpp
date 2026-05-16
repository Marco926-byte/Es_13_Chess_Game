#include <gtest/gtest.h>
#include <memory>

#include "../Chess_Engine/MOVEMENT_PIECE/Movement_Piece.h"
#include "../Chess_Engine/FEN/Handle_Fen_String.h"
#include "../Chess_Engine/MOVE/Move.h"
#include "../Chess_Engine/UPDATE_MOVES/Update_Moves.h"
#include "../Chess_Engine/ENPASSANT/Handle_Enpassant.h"

class Check_Test: public ::testing::Test
{
protected:
    std::unique_ptr<Handle_Chessboard> chess_logic;
    std::shared_ptr<Find_King> engine_find_king;
    std::shared_ptr<Handle_Fen_String> fen_string;
    std::unique_ptr<Movement_Piece> engine;
    std::shared_ptr<Handle_Enpassant> engine_enpassant;
    std::shared_ptr<Check> engine_check_logic;  
    std::shared_ptr<Castling> engine_castling_logic;
    std::unique_ptr<Update_Moves> engine_update_moves;
public:
    void SetUp() override
    {
        //Inizializzo la logica dei turni
        chess_logic = std::make_unique<Handle_Chessboard>
        (
            
        );

        engine_find_king= std::make_shared<Find_King>
        (
            
        );

        //Inizializzo la fen:
        fen_string = std::make_shared<Handle_Fen_String>
        (
            chess_logic.get(),
            engine_find_king
        );

        //Inizializzo il motore delle mosse:
        engine = std::make_unique<Movement_Piece>
        (
            fen_string
        );
        
        
        engine_enpassant = std::make_shared<Handle_Enpassant>
        (
            fen_string,
            engine.get()
        );

        engine_check_logic = std::make_shared<Check>
        (

        );

        engine_castling_logic = std::make_shared<Castling>
        (
            fen_string,
            engine.get(),
            engine_check_logic,
            chess_logic.get(),
            engine_find_king
        );

        engine_update_moves = std::make_unique<Update_Moves>
        (
            fen_string,
            engine_enpassant,
            engine.get(),
            engine_castling_logic
        );
    }

    void TearDown() override
    {

    }
};

TEST_F(Check_Test, not_check_king_looking_forward)
{
    std::cout<<"ciao da not check king\n";
    std::string fen_start = "rnb1qbnr/ppp1pppp/2kp4/8/8/2KP4/RNB1QBNR w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    std::cout<<"imposto la fen\n";

    chess_logic.get()->set_turn(WHITE);

    std::cout<<"imposto il turno\n";

    engine_update_moves.get()->update_moves_all_piece();

    std::cout<<"aggiorno le mosse\n";

    Piece* king = engine_find_king.get()->find_king_current_turn
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    if(!king)
    {
        std::cout<<"ptr_king è nullptr\n";
    }

    bool success = engine_check_logic.get()->handle_check_on_king_straight
    (
        king->get_square(),
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_FALSE(success);
}

