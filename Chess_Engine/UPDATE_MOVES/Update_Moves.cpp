#include "Update_Moves.h"

Update_Moves::Update_Moves
(
    std::shared_ptr<Handle_Fen_String> fen,
    std::shared_ptr<Handle_Enpassant> enpassant,
    Movement_Piece* movement,
    std::shared_ptr<Castling> castling
)
    :fen_shared(fen),
    enpassant_shared(enpassant),
    movement_ptr(movement),
    castling_shared(castling)
{
    
}

void Update_Moves::update_moves_all_piece()
{
    const auto& piece=fen_shared.get()->get_piece();
    for(int i=0; i<64; ++i)
    {
        if(piece[i])
        {
            piece[i]->update_legal_moves(fen_shared);
        }
    }
    enpassant_shared.get()->is_enpassant();
    castling_shared.get()->is_castling_dx();
    castling_shared.get()->is_castling_sx();
}

void Update_Moves::update_move_in_check(Color team_color,std::vector<int> v_attack)
{
    const auto& piece=fen_shared.get()->get_piece();
    
    if(v_attack.size()==0)
    {
        std::cout<<"Il vettore passato da paramentro in input è vuoto!\n";
    }
    //Itero tutto
    for (int i=0; i<64; i++)
    {
        //pulisco il vettore delle mosse per ogni pezzo
        attacked_square.clear();

        //Controllo se il pezzo è giusto...
        if
        (
            piece[i] 
            && 
            piece[i]->get_color()==team_color 
            &&
            !piece[i]->is_king()
        )
        {
            //Itero tutte le mosse legali del pezzo:
            for(int itr_normal_legal_move : piece[i]->get_legal_moves())
            {                
                //Itero tutto il vettore dell'attacco:
                for(int itr_attack : v_attack)
                {
                    std::cout<<itr_attack<<std::endl;
                    //Se un vettore di attacco contiene una mossa legale del pezzo allora inserisci:   
                    if(itr_attack == itr_normal_legal_move)
                    {
                        attacked_square.push_back(itr_attack);
                    }
                }
            }
            //Imposto le nuove mosse legali...
            piece[i]->set_legal_moves(attacked_square);
        }
    }
}