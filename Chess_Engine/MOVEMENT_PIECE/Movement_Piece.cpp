#include "Movement_Piece.h"

Movement_Piece::Movement_Piece
(
    std::shared_ptr<Handle_Fen_String> fen  
) 
    :fen_shared(fen)
       
{  


}

void Movement_Piece::set_num_debug(int num)
{
    num_debug = num;
}

int Movement_Piece::get_num_debug() const
{
    return num_debug;
}

bool Movement_Piece::get_is_case_enpassant() const
{
    return is_case_enpassant;
}
std::stack<Move> Movement_Piece::get_stack() const
{
    return stack;
}

char Movement_Piece::get_piece_capture() const
{
    return piece_capture;
}

void Movement_Piece::set_piece_capture(char capture)
{
    piece_capture = capture;
}

bool Movement_Piece::handle_move(int from, int to)
{
    /*--- INIZIO CONTROLLO PSEUDOMOSSA -----*/
    Piece* type_caracter = fen_shared.get()->get_piece()[from]; 
    
    bool to_is_good= false;
    
    if(type_caracter && type_caracter->get_legal_moves().size()==0)
    {
        std::cout<<"MOSSA NON FATTA PERCHÈ IL PEZZO IN FROM HA 0 MOSSE LEGALI\n";
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
        std::cout<<"mossa non fatta perchè non trovata nelle mosse legali di tale pezzo\n";
        return false;
    }
    /*---- FINE CONTROLLO PSEUDOMOSSA MOSSA ----*/

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

    //Gestisco caso enpassant:
    if(fen_shared.get()->get_is_enpassant())
    {
        if(fen_shared.get()->get_fen_string() == "kn6/1p1p4/pPpP1pp1/P1P2P2/Pp3p1p/1P2pPpP/4P1P1/6NK b  -  0 ")
        {
            num_debug = 69;
        }

        //ATTENZIONE: questo controllo da fare solamente con color offset
        if(piece[move.get_to_square()])
        {
            piece_capture = piece[move.get_to_square()]->get_name_piece();
        }
        else
        {
            piece_capture = ' ';
        }
        
        //Eseguo il movimento:
        piece[move.get_to_square()]=piece[move.get_from_square()];
        piece[move.get_from_square()]=nullptr;
        
        //Imposto la casella al pezzo mosso e anche l'attributo si è
        //mosso
        piece[move.get_to_square()]->set_square(move.get_to_square());        
        piece[move.get_to_square()]->set_ismoved(true);
        fen_shared.get()->set_is_moved(true,move.get_to_square());
        fen_shared.get()->set_is_moved(false,move.get_from_square());

        //RIGENERA LA NUOVA FEN_STRING:
        std::string new_fen = fen_shared.get()->generate_fen_string();
        fen_shared.get()->add_fen_to_map(new_fen);

        is_case_enpassant = false;

        int color_offset = move.get_color_piece() == WHITE ? 8 : -8;
        
        // Se la casella enpassant non è nullptr, elimina il pezzo
        if
        (
            //DA CORREGGERE
            fen_shared.get()->get_piece()[move.get_to_square()]->get_is_pawn_enpassant()
        )
        {
            if(piece[move.get_to_square()+color_offset])
            {
                piece_capture = piece[move.get_to_square()+color_offset]->get_name_piece();
                is_moved_piece_from_enpassant = piece[move.get_to_square()+color_offset]->get_ismoved();
            }
            
            //Kill pezzo vittima enpassant:
            delete fen_shared.get()->get_piece()[move.get_to_square()+color_offset];

            fen_shared.get()->get_piece()[move.get_to_square()+color_offset]=nullptr;

            //RIGENERA LA NUOVA FEN_STRING:
            std::string new_fen = fen_shared.get()->generate_fen_string();
            fen_shared.get()->add_fen_to_map(new_fen);
            
            is_case_enpassant = true;

            //Pusho nuova mossa nello stack
            stack.push(move);
            
            return true;
        }
        
        //Pusho nuova mossa nello stack
        stack.push(move);
        return true;
    }
    else
    {
        std::cout<<"Il pezzo in to_square non ha potere enpassant"<<std::endl;
        is_case_enpassant = false;
    }

    if(piece[move.get_to_square()]!=nullptr)
    {
        piece_capture = piece[move.get_to_square()]->get_name_piece();

        //recupero is_moved dal pezzo prima che avvenga la kill
        is_moved_piece_from = piece[move.get_from_square()]->get_ismoved();        
        is_moved_piece_to =  piece[move.get_to_square()]->get_ismoved();   
        
        //elimino il pezzo puntato dal carattere ucciso:
        delete piece[move.get_to_square()];
    }        
    else
    {
        piece_capture = ' ';
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
    bool is_capture_case = false;
    const auto &piece = fen_shared.get()->get_piece();

    if(fen_shared.get()->get_fen_string() == "kn6/1p1p4/pPpP1pp1/P1P2P2/5p1p/pP2pPpP/4P1P1/6NK w 32 0 ")
    {
        std::cout<<"----------CIAOOOOOOOO DA UNMAKE_MOVE-------------"<<std::endl;
        num_debug = 96;
    }
    
    //1) Cancella l'ultima mossa dallo stack
    if(!stack.empty())
    {
        stack.pop();
    }

    //2) Rigenera il pezzo eventualmente mangiato
    if(isalpha(piece_capture)) //isalpha = se lettera
    {
        if(num_debug == 96)
        {
            std::cout<<"to: "<<to<<" from: "<<from<<std::endl;
        }

        //HO FATTO QUESTA MODIFICA IMPORTANTE A LOGICA UNMAKE
        if(piece[from]->get_is_pawn_enpassant())
        {
            if(num_debug == 96)
            {
                std::cout<<"Il pezzo in from è il pedone con potere enpassant"<<std::endl;
            }

            int color_offset = piece[from]->get_color() == WHITE ? 8 : -8;

            if(num_debug == 96)
            {
                std::cout<<"color_offset: "<<color_offset<<std::endl;
                std::cout<<"from + color_offset: "<<color_offset+from<<std::endl;
                std::cout<<"FINE CASO ENPASSANT UNMAKE_MOVE"<<std::endl;
            }
            
            //Riporto il pedone alla sua posizione di partenza
            piece[to] = piece[from];
            piece[from] = nullptr;

            piece[from+color_offset] = fen_shared.get()->get_create_ptr()->create_piece(piece_capture,from+color_offset);
            
            //Resetto attributi per i pezzi prima della mossa fatta
            piece[to]->set_square(to);
            piece[to]->set_ismoved(is_moved_piece_from);
            piece[from+color_offset]->set_square(from+color_offset);
            piece[from+color_offset]->set_ismoved(is_moved_piece_from_enpassant);
        }
        else
        {
            piece[to] = piece[from];
            piece[from] = nullptr;

            piece[from] = fen_shared.get()->get_create_ptr()->create_piece(piece_capture,from);

            //Resetto attributi per i pezzi prima della mossa fatta
            piece[to]->set_square(to);
            piece[to]->set_ismoved(is_moved_piece_from);
            piece[from]->set_square(from);
            piece[from]->set_ismoved(is_moved_piece_to);
        }        
        //--------------------------------------------------------
        //RIGENERA LA NUOVA FEN_STRING:
        std::string new_fen = fen_shared.get()->generate_fen_string();
    
        fen_shared.get()->add_fen_to_map(new_fen);

        piece_capture = ' ';
        is_capture_case = true;  
    }
    else
    {
        piece[to] = piece[from];
        piece[from] = nullptr;
        
        //Aggiunta....
        if(piece[to])
            piece[to]->set_square(to);

        //RIGENERA LA NUOVA FEN_STRING:
        std::string new_fen = fen_shared.get()->generate_fen_string();
        fen_shared.get()->add_fen_to_map(new_fen);

        is_capture_case = false;   
        piece_capture = ' ';    
    }    

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
    return is_capture_case;
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