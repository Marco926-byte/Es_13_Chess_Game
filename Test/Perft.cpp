#include <gtest/gtest.h>
#include <memory>

#include "../Chess_Engine/MOVEMENT_PIECE/Movement_Piece.h"
#include "../Chess_Engine/FEN/Handle_Fen_String.h"
#include "../Chess_Engine/MOVE/Move.h"
#include "../Chess_Engine/UPDATE_MOVES/Update_Moves.h"
#include "../Chess_Engine/ENPASSANT/Handle_Enpassant.h"

class Perft: public ::testing::Test
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
        chess_logic.get()->set_turn(WHITE);

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

    int pert_test
    (
        int depth = 0,
        Color playing_color = WHITE
    )
    {
        if(depth == 0)
        { 
            return 1;
        }

        engine_update_moves.get()->update_moves_all_piece();

        std::map<int,std::vector<int>> m_piece_move;

        for(int i =0; i<64; i++)
        {
            if
            (
                fen_string.get()->get_piece()[i] 
                && 
                fen_string.get()->get_piece()[i]->get_color()==playing_color
            )
            {                
                std::vector<int> moves = 
                fen_string.get()->get_piece()[i]->get_legal_moves();

                if(moves.size()>0)
                {
                    m_piece_move[fen_string.get()->get_piece()[i]->get_square()]= moves;
                }                                                                                       
            }
        }

        int number_position = 0;
        Color next_turn;
        
        for(auto move : m_piece_move)
        {
            int start_square_piece = move.first;
    
            for(auto i: move.second)
            {
                //1) Salvo lo stato:
                std::string fen_saved = fen_string.get()->get_fen_string();
                
                if(chess_logic.get()->get_turn()==WHITE)
                {
                    next_turn = BLACK;
                }
                else
                {
                    next_turn = WHITE;
                }

                //2) Faccio la mossa e cambio turno:
                engine.get()->handle_move(start_square_piece,i);
                chess_logic.get()->set_turn(next_turn);
                
                //3) Ricorsione, accumulo i risultati:
                number_position+= pert_test(depth-1,next_turn);

                std::cout<<"Stato fen fine profondità: "<<fen_saved<<std::endl;

                //4) Cancella la mossa pk non ci sono più mosse da fare:
                fen_string.get()->set_board_fenstring(fen_saved);
                chess_logic.get()->set_turn(playing_color);
            }
        }
        return number_position;
    }      
    
    int divide
    (
        int depth = 0,
        int initial_depth =0,
        Color playing_color = WHITE
    )
    {
        if(depth==0)
        {
            return 1;
        }
        
        engine_update_moves.get()->update_moves_all_piece();

        std::map<int,std::vector<int>> m_piece_move;

        for(int i =0; i<64; i++)
        {
            if
            (
                fen_string.get()->get_piece()[i] 
                && 
                fen_string.get()->get_piece()[i]->get_color()==playing_color
            )
            {                
                std::vector<int> moves = 
                fen_string.get()->get_piece()[i]->get_legal_moves();

                if(moves.size()>0)
                {
                    m_piece_move[fen_string.get()->get_piece()[i]->get_square()]= moves;
                }                                                                                       
            }
        }
        int number_position = 0;
        Color next_turn;
        
        for(auto move : m_piece_move)
        {
            int start_square_piece = move.first;
    
            for(auto i: move.second)
            {
                //1) Salvo lo stato:
                std::string fen_saved = fen_string.get()->get_fen_string();
                
                if(chess_logic.get()->get_turn()==WHITE)
                {
                    next_turn = BLACK;
                }
                else
                {
                    next_turn = WHITE;
                }

                //2) Faccio la mossa e cambio turno:
                bool execute_move = engine.get()->handle_move(start_square_piece,i);
                if(!execute_move)
                {
                    std::cout<<"La mossa da: "<<start_square_piece<<" a: "<<i<<" NON È STATA EFFETTUATA\n";
                }
                
                chess_logic.get()->set_turn(next_turn);
                
                int all_moves_depth = divide(depth-1,initial_depth, next_turn);

                
                if(depth==initial_depth)
                {
                    std::cout<<"Mossa da: "<<move.first<<" a: "<<i<<" : "<<all_moves_depth<<std::endl;
                }
                
                //3) Ricorsione, accumulo i risultati:
                number_position += all_moves_depth;


                //4) Cancella la mossa pk non ci sono più mosse da fare:
                fen_string.get()->set_board_fenstring(fen_saved);
                chess_logic.get()->set_turn(playing_color);
            
                engine_update_moves.get()->update_moves_all_piece();
            }
        }
        std::cout<<"Numero totale di mosse: "<<number_position<<std::endl;
        return number_position;
    }

    void TearDown() override
    {
        //Distruttore
    }
};



TEST_F(Perft, Perft_deep_start_white)
{
    engine_update_moves.get()->update_moves_all_piece();
    chess_logic.get()->set_turn(WHITE);

    int legal_moves_white = 0;
    bool success = false;

    for (int i = 0; i < 64; i++)
    {
        if 
        (
            fen_string.get()->get_piece()[i] 
            &&
            fen_string.get()->get_piece()[i]->get_color()==WHITE
        )
        {
            legal_moves_white += fen_string.get()->get_piece()[i]->get_legal_moves().size(); 
        }        
    }

    std::cout<<"legal_moves_white: "<<legal_moves_white<<std::endl;
    std::cout<<"fen_string: "<<fen_string.get()->get_fen_string()<<std::endl;

    int total_moves_in_deap_zero = 20;

    if(legal_moves_white == total_moves_in_deap_zero)
    {
        success = true;    
    }
    ASSERT_TRUE(success);
}

TEST_F(Perft, Perft_deep_start_black)
{
    engine_update_moves.get()->update_moves_all_piece();
    
    chess_logic.get()->set_turn(BLACK);

    int legal_moves_black = 0;
    bool success = false;

    for (int i = 0; i < 64; i++)
    {
        if 
        (
            fen_string.get()->get_piece()[i] 
            &&
            fen_string.get()->get_piece()[i]->get_color()==WHITE
        )
        {
            legal_moves_black += fen_string.get()->get_piece()[i]->get_legal_moves().size(); 
        }        
    }
    
    std::cout<<"legal_moves_black: "<<legal_moves_black<<std::endl;
    std::cout<<"fen_string: "<<fen_string.get()->get_fen_string()<<std::endl;

    int total_moves_in_deap_zero = 20;

    if(legal_moves_black == total_moves_in_deap_zero)
    { 
        success = true;    
    }
    ASSERT_TRUE(success);
}

//Profondità 1: 20
TEST_F(Perft, Perft_test_deep_1)
{
    bool success = false;
    int pertf = pert_test(1);
    std::cout<<"pertf = "<<pertf<<std::endl;
    if(pertf == 20)
    {
        success = true;       
    }
    ASSERT_TRUE(success);
}

//Profondità 2: 400
TEST_F(Perft, Perft_test_deep_2)
{
    //Prova a sistemare la fen
    bool success = false;
    int pertf = pert_test(2,WHITE);
    std::cout<<"pertf = "<<pertf<<std::endl;
    if(pertf == 400)
    {
        success = true;       
    }
    ASSERT_TRUE(success);
}

//Profondità 3: 8902
TEST_F(Perft, Perft_test_deep_3)
{
    bool success = false;
    int pertf = pert_test(3,WHITE);
    std::cout<<"pertf = "<<pertf<<std::endl;
    if(pertf == 8902)
    {
        success = true;       
    }
    ASSERT_TRUE(success);
}

TEST_F(Perft, Perft_divide_deep_3)
{
    bool success = false;
    int pertf = divide(3,3,WHITE);

    ASSERT_FALSE(success);
    
}

TEST_F(Perft, Perft_divide_debug_3)
{
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/P7/1PPPPPPP/RNBQKBNR b KQkq - 0 1";
    fen_string.get()->set_board_fenstring(fen);   

    bool success = false;
    int pertf = divide(2,2,BLACK);

    ASSERT_FALSE(success);
}

TEST_F(Perft, Perft_divide_debug_3_error_pawn)
{
    //Problema pedone mosso in realtà non mosso...
    //Debug: in setfenstring inserisci un controllo e guarda se il pedone parte
    //dalla sua casella di partenza
    std::string fen = "r1bqkbnr/pppppppp/2n5/8/8/P7/1PPPPPPP/RNBQKBNR w KQkq - 1 2";
    fen_string.get()->set_board_fenstring(fen);  
    
    bool success = false;
    int pertf = divide(1,1,WHITE);

    ASSERT_FALSE(success);
}