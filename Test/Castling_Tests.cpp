#include <gtest/gtest.h>
#include <memory>

#include "../Chess_Engine/MOVEMENT_PIECE/Movement_Piece.h"
#include "../Chess_Engine/FEN/Handle_Fen_String.h"
#include "../Chess_Engine/MOVE/Move.h"
#include "../Chess_Engine/UPDATE_MOVES/Update_Moves.h"
#include "../Chess_Engine/ENPASSANT/Handle_Enpassant.h"

class Castling_Tests: public ::testing::Test
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
        
        std::string start_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR - w KQkq - 0 1";
        fen_string.get()->set_board_fenstring(start_fen);


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
        engine_update_moves.get()->update_moves_all_piece();
    }

    void TearDown() override
    {
        //Distruttore
    }
};


TEST_F(Castling_Tests, is_castling_dx_white_true)
{
    std::cout<<"--PARTE IS_CASTLING_DX_WHITE_TRUE--\n";
    std::string fen_start = "4k3/8/8/8/8/8/8/4K2R w K - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    std::cout<<"Fen inserita di partenza: "<<fen_string.get()->get_fen_string()<<std::endl;
    
    if(fen_string.get()->get_piece()[63]->get_ismoved())
    {
        std::cout<<"ATTENZIONE, LA TORRE IN 63 SI È MOSSA! \n";
    }
    else
    {
        std::cout<<"ATTENZIONE, LA TORRE IN 63 NON SI È MOSSA! \n";

    }
    if(fen_string.get()->get_piece()[60]->get_ismoved())
    {
        std::cout<<"ATTENZIONE! IMPOSTI A TRUE IL RE DURANTE IL SET_FEN DEL TEST!\n";
    }
    else
    {
        std::cout<<"ATTENZIONE! NON IMPOSTI GIÀ PRIMA A TRUE IL RE!\n";
    }
    engine_update_moves.get()->update_moves_all_piece();


    chess_logic.get()->set_turn(WHITE);
    
    bool success = engine_castling_logic.get()->is_castling_dx();

    ASSERT_TRUE(success);
}



TEST_F(Castling_Tests, is_castling_dx_black_true)
{
    std::string fen_start = "4k2r/8/8/8/8/8/8/4K3 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    engine_update_moves.get()->update_moves_all_piece();
   
    chess_logic.get()->set_turn(BLACK);
    
    bool success = engine_castling_logic.get()->is_castling_dx();

    ASSERT_TRUE(success);
}



TEST_F(Castling_Tests, is_castling_dx_white_false_static)
{
    std::string fen_start = "4k3/8/8/8/8/8/8/4K1R1 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    engine_update_moves.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(WHITE);
    
    bool success = engine_castling_logic.get()->is_castling_dx();

    ASSERT_FALSE(success);
}



TEST_F(Castling_Tests, is_castling_dx_black_false_static)
{
    std::string fen_start = "4k1r1/8/8/8/8/8/8/4K3 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    engine_update_moves.get()->update_moves_all_piece();

   
    chess_logic.get()->set_turn(BLACK);
    
    bool success = engine_castling_logic.get()->is_castling_dx();

    ASSERT_FALSE(success);
}

TEST_F(Castling_Tests, is_castling_dx_white_false_after_move)
{
    std::cout<<"-- PARTE IS_CASTLING_DX_WHITE --\n";
    std::string fen_start = "k7/8/8/8/7R/8/8/4K3 w -- 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    std::cout<<"Ciao dal TEST\n";
    std::cout<<"La fen impostata è: "<<fen_string.get()->get_fen_string()<<std::endl;
    
    engine_update_moves.get()->update_moves_all_piece();
    
    chess_logic.get()->set_turn(WHITE);

    engine.get()->handle_move(39,63);
    
    chess_logic.get()->set_turn(WHITE);
    bool success = engine_castling_logic.get()->is_castling_dx();

    ASSERT_FALSE(success);
}