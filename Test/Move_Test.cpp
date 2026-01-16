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
    ASSERT_TRUE(success) << "handle_move ha fallito!";

    // Verifica che il pezzo sia arrivato
    auto board = fen_string->get_piece();
    ASSERT_NE(board[to], nullptr) << "La casella di arrivo è vuota!";
    EXPECT_EQ(board[to]->get_name_piece(), 'P') << "Non è un pedone!";
    EXPECT_EQ(board[from], nullptr) << "Il vecchio posto non è vuoto!";
}

TEST_F(Move_Test, Rook_Cannot_Jump) 
{
    int from_rook = 56; // A1 (Torre bianca)
    int to_jump = 40;   // A3 (Dietro il pedone A2)

    // La torre è bloccata dal pedone in A2 (48)
    bool success = engine->handle_move(from_rook, to_jump);

    // Deve fallire!
    ASSERT_FALSE(success) << "La Torre ha saltato illegalmente il pedone!";
}