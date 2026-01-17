#include <gtest/gtest.h>
#include <memory>

#include "../Movement_Piece.h"
#include "../Handle_Fen_String.h"
#include "../Move.h"

class Move_Test: public ::testing::Test
{
protected:
    std::shared_ptr<Handle_Fen_String> fen_string;
    std::unique_ptr<Movement_Piece> engine;
public:
    void SetUp() override
    {
        //Inizializzo la fen:
        fen_string = std::make_shared<Handle_Fen_String>();
        std::string start_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR - w KQkq - 0 1";
        fen_string.get()->set_board_fenstring(start_fen);

        //Inizializzo il motore delle mosse:
        engine = std::make_unique<Movement_Piece>(nullptr,fen_string,nullptr);
        engine.get()->update_moves_all_piece();
    }

    void TearDown() override
    {
        //Distruttore
    }
};

// Test 1: Pedone Bianco E2 -> E4
TEST_F(Move_Test, White_Pawn_Moves_Forward) {
    int from = 52; // E2
    int to = 36;   // E4

    // Esegui
    bool success = engine->handle_move(from, to);

    // Verifica che la funzione ritorni true
    ASSERT_TRUE(success);// handle_move ha fallito!"

    // Verifica che il pezzo sia arrivato
    auto board = fen_string->get_piece();
    ASSERT_NE(board[to], nullptr); //"La casella di arrivo è vuota!"
    EXPECT_EQ(board[to]->get_name_piece(), 'P'); //"Non è un pedone!"
    EXPECT_EQ(board[from], nullptr); //"Il vecchio posto non è vuoto!"
}

TEST_F(Move_Test, Rook_Cannot_Jump) 
{
    int from_rook = 56; // A1 (Torre bianca)
    int to_jump = 40;   // A3 (Dietro il pedone A2)

    // La torre è bloccata dal pedone in A2 (48)
    bool success = engine->handle_move(from_rook, to_jump);

    // Deve fallire!
    ASSERT_FALSE(success) /*<< "La Torre ha saltato illegalmente il pedone!"*/;
}

TEST_F(Move_Test, Queen_Cannot_Jump)
{
    int from_queen = 59;    //D1 (Regina bianca)
    int to_jump= 43;        //D3 (davanti al pedone D2)

    //La regina vuole saltare il pedone ma non può!!!!
    bool success = engine.get()->handle_move(from_queen,to_jump);

    //Mi aspetto che fallisca, ASSERT si usa per errori fatali:
    ASSERT_FALSE(success);
}

TEST_F(Move_Test, Bishop_Cannot_Jump)
{
    int from_bishop = 61;
    int to_jump = 47;
       
    //L' alfiere vuole saltare il pedone ma non può!!!!
    bool success = engine.get()->handle_move(from_bishop,to_jump);

    //Mi aspetto che fallisca, ASSERT si usa per errori fatali:
    ASSERT_FALSE(success);
}

TEST_F(Move_Test, Knight_Can_Jump)
{
    int from_knight = 62;
    int to_jump = 47;
       
    //Il cavallo vuole saltare il pedone e può!!!!
    bool success = engine.get()->handle_move(from_knight,to_jump);

    //Mi aspetto che fallisca, ASSERT si usa per errori fatali:
    ASSERT_TRUE(success);
}

TEST_F(Move_Test, Knight_Legal_Move_Check)
{
    int from_knight = 62;
    int to_jump = 46;

    //Il cavallo non può andare in questa casella:
    bool success = engine.get()->handle_move(from_knight,to_jump);

    ASSERT_FALSE(success);
}

TEST_F(Move_Test, Pawn_After_Double_Move_Forward)
{
    //Creo la situazione di gioco:
    std::string fen_start = "rnbqkbnr/1ppppppp/p7/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2";
    fen_string.get()->set_board_fenstring(fen_start); 
    
    //inizializzo la posizione del pedone bianco e voglio fargli rifare un 
    //passo doppio
    int from_pawn = 36;
    int to_jump = 20;

    //Deve fallire...
    bool success = engine.get()->handle_move(from_pawn,to_jump);

    ASSERT_FALSE(success);
}

TEST_F(Move_Test, Queen_is_not_knight)
{
    //Creo la situazione di gioco:
    std::string fen_start = "rnbqkbnr/1ppppppp/8/p7/3P4/3Q4/PPP1PPPP/RNB1KBNR w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    //inizializzo la posizione del pedone bianco e voglio fargli rifare un 
    //passo doppio
    int from_queen = 43;
    int to_jump = 33;

    //Deve fallire...
    bool success = engine.get()->handle_move(from_queen,to_jump);

    ASSERT_FALSE(success);
}

TEST_F(Move_Test, Queen_is_bishop)
{
    //Creo la situazione di gioco:
    std::string fen_start = "rnbqkbnr/1ppppppp/8/p7/3P4/3Q4/PPP1PPPP/RNB1KBNR w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 


    //inizializzo la posizione del pedone bianco e voglio fargli rifare un 
    //passo doppio
    int from_queen = 43;
    int to_jump = 25;

    //Deve passare...
    engine.get()->update_moves_all_piece();
    bool success = engine.get()->handle_move(from_queen,to_jump);

    ASSERT_TRUE(success);
}

TEST_F(Move_Test, Queen_is_pawn_attack)
{
    //Creo la situazione di gioco:
    std::string fen_start = "rnbqkbnr/1ppppppp/8/p7/3P4/3Q4/PPP1PPPP/RNB1KBNR w KQkq - 0 3";
    fen_string.get()->set_board_fenstring(fen_start); 

    //inizializzo la posizione del pedone bianco e voglio fargli rifare un 
    //passo doppio
    int from_queen = 43;
    int to_jump = 34;

    //Deve passare...
    engine.get()->update_moves_all_piece();
    bool success = engine.get()->handle_move(from_queen,to_jump);

    ASSERT_TRUE(success);
}