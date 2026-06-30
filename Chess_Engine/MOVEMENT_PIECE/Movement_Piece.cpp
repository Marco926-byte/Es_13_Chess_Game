#include "Movement_Piece.h"

Movement_Piece::Movement_Piece
(
    std::shared_ptr<Handle_Fen_String> fen  
) 
    :fen_shared(fen)
       
{  


}

std::stack<Move> Movement_Piece::get_stack() const
{
    return stack;
}

bool Movement_Piece::handle_move(int from, int to)
{
    Piece* type_caracter = fen_shared.get()->get_piece()[from]; 
    
    bool to_is_good= false;
    
    if(type_caracter && type_caracter->get_legal_moves().size()==0)
    {
        return false;
    }
    
    if(fen_shared.get()->get_piece()[from])
    {
        for
        (
            int i=0;
            i<fen_shared.get()->get_piece()[from]->get_legal_moves().size();
            i++
        )
        {
            if(to == fen_shared.get()->get_piece()[from]->get_legal_moves()[i])
            {
                to_is_good=true;
                break;
            }
        }
    }

    if(!to_is_good)
    {    
        return false;
    }

    //Creo la nuova mossa:
    Move move;
    
    //Imposto la mossa da.. a...
    move.set_from_square(from);
    move.set_to_square(to);

    const auto &piece = fen_shared.get()->get_piece();

    //Imposto il colore per la mossa del pezzo:
    move.set_color_piece(piece[from]->get_color());
    if
    (
        piece[from]->get_name_piece()=='K'
        ||
        piece[from]->get_name_piece()=='k'

    )
    {
        move.set_type_piece(KING);       
    }

    if
    (
        piece[from]->get_name_piece()=='B'
        ||
        piece[from]->get_name_piece()=='b'

    )
    {
        move.set_type_piece(BISHOP);
    }

    if
    (
        piece[from]->get_name_piece()=='R'
        ||
        piece[from]->get_name_piece()=='r'

    )
    {
        move.set_type_piece(ROCK);
    }

    if
    (
        piece[from]->get_name_piece()=='Q'
        ||
        piece[from]->get_name_piece()=='q'

    )
    {
        move.set_type_piece(QUEEN);
    }

    if
    (
        piece[from]->get_name_piece()=='N'
        ||
        piece[from]->get_name_piece()=='n'

    )
    {
        move.set_type_piece(KNIGHT);
    }

    if
    (
        piece[from]->get_name_piece()=='P'
        ||
        piece[from]->get_name_piece()=='p'

    )
    {
        move.set_type_piece(PAWN);
    }

    //Gestisco la cattura:
    if(piece[move.get_to_square()]!=nullptr)
    {
        piece_capture = piece[move.get_to_square()]->get_name_piece();
    
        //elimino il pezzo puntato dal carattere ucciso:
        delete piece[move.get_to_square()];
    }        

    //Gestisco il movimento del pezzo:
    piece[move.get_to_square()]=piece[move.get_from_square()];
    piece[move.get_from_square()]=nullptr;

    //Imposto la casella al pezzo mosso e anche l'attributo si è
    //mosso
    piece[move.get_to_square()]->set_square(move.get_to_square());
    piece[move.get_to_square()]->set_ismoved(true);
    fen_shared.get()->set_is_moved(true,move.get_to_square());
    fen_shared.get()->set_is_moved(false,move.get_from_square());
    
    //Gestisco la mossa del nero per il discorso della fen 
    if(move.get_color_piece()==BLACK)
    {
        fen_shared.get()->set_is_last_move_black(true);
    }

    //RIGENERA LA NUOVA FEN_STRING:
    std::string new_fen = fen_shared.get()->generate_fen_string();
    fen_shared.get()->add_fen_to_map(new_fen);

    stack.push(move);

    return true;
}

bool Movement_Piece::unmake_move(int from, int to)
{
    bool is_unmake_move = false;
    const auto &piece = fen_shared.get()->get_piece();

    //1) Cancella l'ultima mossa dallo stack
    if(!stack.empty())
    {
        stack.pop();
    }

    //2) Rigenera il pezzo eventualmente mangiato
    if(isalpha(piece_capture)) //isalpha = se lettera
    {
        
        piece[to] = piece[from];
        piece[from] = nullptr;

        //Problema: mi da errore, problema nel creare il pezzo bad alloc.
        piece[from] = fen_shared.get()->get_create_ptr()->create_piece(piece_capture,from);
        
        piece_capture = ' ';
        is_unmake_move = true;
    }
    else
    {
        piece[to] = piece[from];
        piece[from] = nullptr;

        is_unmake_move = true;   
        piece_capture = ' ';
    }    

    //RIGENERA LA NUOVA FEN_STRING:
    std::string new_fen = fen_shared.get()->generate_fen_string();
    fen_shared.get()->add_fen_to_map(new_fen);
    
    //DA RICONTROLLARE LA GESTIONE DEL TURNO
    if(fen_shared.get()->get_turn_ptr()->get_turn()==WHITE)
    {
        fen_shared.get()->get_turn_ptr()->set_turn(BLACK);
    }    
    else
    {
        fen_shared.get()->decrease_count_move_black();
        fen_shared.get()->get_turn_ptr()->set_turn(WHITE);
    }
    //4) Cancella l'attributo is_moved = true al pezzo
    return is_unmake_move;
}

void Movement_Piece::print_all_move()
{
    for(int i=0; i<stack.size(); i++)
    {
        std::cout<<"__________________________________\n";
        std::cout<<"|Stampo tutte le mosse: .....     |\n";
        
        if(stack.top().get_color_piece()==1)
        {
            std::cout<<"|Il colore del pezzo: WHITE    |\n"<<std::endl;
        }
        else 
        {
            std::cout<<"|Il colore del pezzo: BLACK    |\n"<<std::endl;
        }
        
        if(stack.top().get_type_piece()==0)
        {
            std::cout<<"|Il tipo di pezzo: PAWN           |\n"<<std::endl;
        }

        if(stack.top().get_type_piece()==1)
        {
            std::cout<<"|Il tipo di pezzo: BISHOP           |\n"<<std::endl;
        }

        if(stack.top().get_type_piece()==2)
        {
            std::cout<<"|Il tipo di pezzo: KNIGHT           |\n"<<std::endl;
        }

        if(stack.top().get_type_piece()==3)
        {
            std::cout<<"|Il tipo di pezzo: QUEEN           |\n"<<std::endl;
        }

        if(stack.top().get_type_piece()==4)
        {
            std::cout<<"|Il tipo di pezzo: KING           |\n"<<std::endl;
        }

        if(stack.top().get_type_piece()==5)
        {
            std::cout<<"|Il tipo di pezzo: ROCK           |\n"<<std::endl;
        }
    
        std::cout<<"|La posizione dove era: ......    |\n"<<stack.top().get_from_square()<<std::endl;
        std::cout<<"|La posizione dove sarà: ......    |\n"<<stack.top().get_to_square()<<std::endl;
        
        std::cout<<"__________________________________\n";
    }
}