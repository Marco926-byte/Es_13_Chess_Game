#include <gtest/gtest.h>
#include <memory>

#include "../Movement_Piece.h"
#include "../Handle_Fen_String.h"
#include "../Move.h"

class Castling_Tests: public ::testing::Test
{
protected:
    std::shared_ptr<Handle_Fen_String> fen_string;
    std::unique_ptr<Handle_Chessboard> chess_logic;
    std::unique_ptr<Movement_Piece> engine;
public:
    void SetUp() override
    {
        //Inizializzo la fen:
        fen_string = std::make_shared<Handle_Fen_String>();
        std::string start_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR - w KQkq - 0 1";
        fen_string.get()->set_board_fenstring(start_fen);

        chess_logic = std::make_unique<Handle_Chessboard>(nullptr,fen_string); 

        //Inizializzo il motore delle mosse:
        engine = std::make_unique<Movement_Piece>(nullptr,fen_string,chess_logic.get());
        engine.get()->update_moves_all_piece();
    }

    void TearDown() override
    {
        //Distruttore
    }
};


TEST_F(Castling_Tests, is_castling_dx_white_true)
{
    std::string fen_start = "4k3/8/8/8/8/8/8/4K2R w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    engine.get()->update_moves_all_piece();

   
    chess_logic.get()->set_turn(WHITE);
    
    bool success = engine.get()->is_castling_dx();

    ASSERT_TRUE(success);
}



TEST_F(Castling_Tests, is_castling_dx_black_true)
{
    std::string fen_start = "4k2r/8/8/8/8/8/8/4K3 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    engine.get()->update_moves_all_piece();

   
    chess_logic.get()->set_turn(BLACK);
    
    bool success = engine.get()->is_castling_dx();

    ASSERT_TRUE(success);
}



TEST_F(Castling_Tests, is_castling_dx_white_false_static)
{
    std::string fen_start = "4k3/8/8/8/8/8/8/4K1R1 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    engine.get()->update_moves_all_piece();

   
    chess_logic.get()->set_turn(WHITE);
    
    bool success = engine.get()->is_castling_dx();

    ASSERT_TRUE(success);
}



TEST_F(Castling_Tests, is_castling_dx_black_false_static)
{
    std::string fen_start = "4k1r1/8/8/8/8/8/8/4K3 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    engine.get()->update_moves_all_piece();

   
    chess_logic.get()->set_turn(BLACK);
    
    bool success = engine.get()->is_castling_dx();

    ASSERT_TRUE(success);
}

TEST_F(Castling_Tests, is_castling_dx_white_false_after_move)
{
    std::string fen_start = "k7/8/8/8/7R/8/8/4K3 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    engine.get()->update_moves_all_piece();
    
    chess_logic.get()->set_turn(WHITE);

    engine.get()->handle_move(39,63);
    
    chess_logic.get()->set_turn(WHITE);
    bool success = engine.get()->is_castling_dx();

    ASSERT_FALSE(success);
}
