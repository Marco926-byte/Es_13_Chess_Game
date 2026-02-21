#include <gtest/gtest.h>
#include <memory>

#include "../Handle_Chessboard.h"
#include "../Handle_Fen_String.h"
#include "../Movement_Piece.h"
#include "../Move.h"

class Chessboard_Test: public ::testing::Test
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

        //Inizializzo il motore della logica:
        chess_logic = std::make_unique<Handle_Chessboard>(nullptr,fen_string);
        
        //Inizializzo il motore delle mosse:
        engine = std::make_unique<Movement_Piece>(nullptr,fen_string,nullptr);
        engine.get()->update_moves_all_piece();
    }

    void TearDown() override
    {
        //Distruttore
    }
};

//TEST: scacco in orizzontale e verticale
TEST_F(Chessboard_Test, test_check_straight_under_rock_white)
{
    std::string fen_start = "4K3/PPPP1PPP/8/8/8/8/4r3/1k6 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(WHITE);

    bool success= chess_logic.get()->handle_check_on_king_straight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

//TEST: scacco in orizzontale e verticale
TEST_F(Chessboard_Test, test_check_straight_under_rock_black)
{
    std::string fen_start = "4k3/PPPP1PPP/8/8/8/8/4R3/1K6 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_check_on_king_straight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

//TEST: scacco in orizzontale e verticale
TEST_F(Chessboard_Test, test_not_check_straight_under_rock_black)
{
    std::string fen_start = "4k3/PPPPpPPP/8/8/8/8/4R3/1K6 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_check_on_king_straight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_FALSE(success);
}

//TEST: scacco in diagonale
TEST_F(Chessboard_Test, test_check_diagonal_bishop_false_white)
{
    std::string fen_start = "2N4r/pp3p2/4b2p/4k1p1/2P1P3/1P6/P4PPP/3RK3 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(WHITE);

    bool success= chess_logic.get()->handle_check_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_FALSE(success);
}

TEST_F(Chessboard_Test, test_check_diagonal_bishop_sx_up_white)
{
    std::string fen_start = "1b6/pp6/8/4K3/2P1P3/1P6/P4PPP/4k3 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(WHITE);

    bool success= chess_logic.get()->handle_check_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

TEST_F(Chessboard_Test, test_check_diagonal_bishop_sx_up_black)
{
    std::string fen_start = "1B6/pp6/8/4k3/2P1P3/1P6/P4PPK/3R4 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_check_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

TEST_F(Chessboard_Test, test_check_diagonal_bishop_sx_under_white)
{
    std::string fen_start = "8/8/8/4K3/2P1P3/1P6/P4PPk/bR6 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(WHITE);

    bool success= chess_logic.get()->handle_check_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

TEST_F(Chessboard_Test, test_check_diagonal_bishop_sx_under_black)
{
    std::string fen_start = "8/8/8/4K3/2P1P3/1P6/P4PPk/bR6 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(WHITE);

    bool success= chess_logic.get()->handle_check_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

TEST_F(Chessboard_Test, test_check_diagonal_bishop_dx_up_white)
{
    
    std::string fen_start = "k7/7b/8/8/4K3/8/8/8 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(WHITE);

    bool success= chess_logic.get()->handle_check_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

TEST_F(Chessboard_Test, test_check_diagonal_bishop_dx_up_black)
{
    std::string fen_start = "K7/7B/8/8/4k3/8/8/8 w KQkq - 0 3";    
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_check_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

TEST_F(Chessboard_Test, test_check_diagonal_bishop_dx_under_white)
{
    std::string fen_start = "k7/b7/8/8/8/8/8/6K1 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(WHITE);

    bool success= chess_logic.get()->handle_check_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

//TEST: scacco col cavallo:
TEST_F(Chessboard_Test, test_check_knight_black)
{
    std::string fen_start = "5k2/3N4/8/1K6/8/8/8/8 b KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_check_on_king_knight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );
    
    ASSERT_TRUE(success);
}

//TEST: pin in orizzontale e verticale:
TEST_F(Chessboard_Test, pin_straight_under)
{
    std::string fen_start = "k7/pp6/8/4q3/5p2/4P3/4K3/8 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();
    chess_logic.get()->set_turn(WHITE);

    bool success= chess_logic.get()->handle_pin_on_king_straight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_TRUE(success);
}

//TODO: 
TEST_F(Chessboard_Test, pin_straight_sx_single_enemy_black)
{
    std::string fen_start = "rnbq1bnr/ppQ1pk2/3p4/P2P2p1/7p/8/8/4K3 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();
    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_pin_on_king_straight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_TRUE(success);
}

//TODO:
TEST_F(Chessboard_Test, pin_straight_dx_single_enemy_black)
{
    std::string fen_start = "rnbq1bnr/2kp1Q2/8/8/8/8/1K6/8 b KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();
    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_pin_on_king_straight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_TRUE(success);
}

//TODO:
TEST_F(Chessboard_Test, pin_straight_under_single_enemy_black)
{
    std::string fen_start = "rnbq1bnr/8/4k3/4b3/8/4Q3/1K6/8 b KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();
    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_pin_on_king_straight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_TRUE(success);
}

//TODO:
TEST_F(Chessboard_Test, pin_straight_up_single_enemy_black)
{
    std::string fen_start = "r1bq1bnr/8/4Q3/8/4n3/4k3/1K6/8 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();
    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_pin_on_king_straight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_TRUE(success);
}


TEST_F(Chessboard_Test, pin_straight_sx_double_enemy)
{
    std::string fen_start = "8/Q2ppk2/2P5/4q3/5p2/4P3/4K3/8 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();
    chess_logic.get()->set_turn(BLACK);

    bool success= chess_logic.get()->handle_pin_on_king_straight
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_FALSE(success);
}

//TEST: pin in diagonale:
TEST_F(Chessboard_Test, test_pin_diagonal_game_sghebbro)
{
    std::string fen_start = "2N6r/pp3p2/4b2p/4k1p1/2P1P3/1P6/P4PPP/3RK2K w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    bool success= chess_logic.get()->handle_pin_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_FALSE(success);
}

TEST_F(Chessboard_Test, test_pin_diagonal_sx_under_black)
{
    std::string fen_start = "8/4k3/3p4/8/1Q6/K7/8/8 w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    bool success= chess_logic.get()->handle_pin_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_TRUE(success);
}

TEST_F(Chessboard_Test, test_pin_diagonal_sx_up_black)
{
    std::string fen_start = "K7/1Q6/8/3p4/4k3/8/8/8 b KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    bool success= chess_logic.get()->handle_pin_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_TRUE(success);
}

TEST_F(Chessboard_Test, test_pin_diagonal_dx_up_black)
{
    std::string fen_start = "6K1/5Q2/8/3p4/2k5/8/8/8 b KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    bool success= chess_logic.get()->handle_pin_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_TRUE(success);
}

TEST_F(Chessboard_Test, test_pin_diagonal_dx_under_black)
{
    std::string fen_start = "8/2K5/3Q4/8/5p2/6k1/8/8 b KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start);

    engine.get()->update_moves_all_piece();

    bool success= chess_logic.get()->handle_pin_on_king_diagonal
    (
        fen_string.get()->get_piece(),
        chess_logic.get()->get_turn()
    );

    ASSERT_TRUE(success);
}
