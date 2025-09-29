#include "Movement_Piece.h"

Movement_Piece::Movement_Piece()
{
    //INIZIO: devo mettere i movimenti legali dei pezzi per fare le giocate
    update_move_pieces();
}

//Gestisci il movimento dei pezzi
void Movement_Piece::handle_move(int from_square, int to_square)
{
    Movement_Handler move;
    move.set_from_square(from_square);
    move.set_to_square(to_square);
    move.set_piece(piece[from_square]);

    //Gestione di controllo movimenti con legal_moves:
    //Se il movimento del pezzo non appartiene alla posizione finale
    //della scacchiera...
    if(!move.get_piece()->is_legal_move(to_square))
    {
        return;
    }

    this->count_draw++;

    //Movimenti pezzo:
    //Se nella posizione finale c'è un pezzo....
    if(piece[to_square] != nullptr)
    {
        move.set_captured_piece(piece[to_square]);
        move.set_captured_piece_type(piece[to_square]->get_name_piece());

        delete piece[to_square];    //---->non capisco questo...
        this->count_draw=0;
    }
    //Sennò:
    else
    {
        move.set_captured_piece(nullptr);
        move.set_captured_piece_type(' ');
    }

    piece[to_square]= move.get_piece();
    piece[from_square]= nullptr;

    //Il movimento del pedone resetta il count_draw a 0
    if(move.get_piece()->is_pawn())
    {
        this->count_draw=0;
    }

    //Aggiorna la casella del pezzo:
    move.get_piece()->set_square(to_square);

    //Aggiorna il movimento del pezzo: 
    move.get_piece()->set_ismoved(true);

    //Aggiungi la mossa allo stack

    this->add_move_to_stack(move);
    this->handle_enpassant_capture();
    //this->moveRookOnCastle();
    //this->changeTurn();
}

void Movement_Piece::add_move_to_stack(Movement_Handler move)
{
    move_stack.push(move);
}

void Movement_Piece::update_move_pieces()
{
    for(Piece*p:piece)
    {
        if(p!=nullptr)
        {
            p->update_legal_moves(piece);
        }
    }
}

void Movement_Piece::set_enpassant_square()
{
    //Devo ottenere l'ultima mossa registrata nello stack...
    Movement_Handler last_move = move_stack.top();

    //Se l'ultima mossa non è fatta da un pedone, esci:
    if(!last_move.get_piece()->is_pawn())
    {
        return;
    }

    //Se l'ultima mossa non è doppio passo allora esci:
    if(abs(last_move.get_from_square()-last_move.get_to_square())!=16)
    {
        return;
    }

    //A destra del pedone e a sinistra
    int directions[2]={-1,1};

    for(int i=0; i<2; ++i)
    {
        int square= last_move.get_to_square()+directions[i];    

        //Se lo square non è dentro alla scacchiera da 0 a 63 allora continua
        //"continua= ignora e vai avanti"

        if(square<0 || square>63)
        {
            continue;
        }

        //Se lo square accanto al pedone è vuoto continua
        if(piece[square]==nullptr)
        {
            continue;
        }

        //Se il pezzo è uguale al pezzo di riferimento, continua
        if(piece[square]->get_color()==last_move.get_piece()->get_color())
        {
            continue;
        }

        //Se il pezzo accanto al pedone di riferimento non è un pedone allora continua
        if(!piece[square]->is_pawn())
        {
            continue;
        }
        //Creo un puntatore su qualcosa che già esiste 
        //e lo converto in Pawn per l'ereditarietà
        Pawn *p= static_cast<Pawn*> (piece[square]);
        
        int color_team= p->get_color()==WHITE? -8: 8;
        
        p->handle_en_passant(last_move.get_to_square()+color_team);

    }
    
}

void Movement_Piece::handle_enpassant_capture()
{
    //Ottengo l'ultima mossa
    Movement_Handler last_move = move_stack.top();

    //Se l'ultima mossa è fatta da un pezzo diverso dal pedone esci
    if(!last_move.get_piece()->is_pawn())
    {
        return;
    }

    //Se l'ultima mossa non è una mossa diagonale, esci
    if(abs(last_move.get_from_square()-last_move.get_to_square())!=9 && 
       abs(last_move.get_from_square()-last_move.get_to_square())!=7)
       {
            return;
       }

    //Se la diagonale è nullptr, elimina il pedone enpassato catturato
    if(last_move.get_captured_piece()==nullptr)
    {
        int color_team=last_move.get_piece()->get_color()==WHITE? -8:8;
        last_move.set_captured_piece(piece[color_team+last_move.get_to_square()]);

        delete piece[color_team+last_move.get_to_square()];
        piece[color_team+last_move.get_to_square()]=nullptr;
    }
}

void Movement_Piece::handle_castling_rights()
{
    //Qui ho tanti puntatori che devono essere inizializzati ricordatelo!
    Handle_Chessboard* handle;
    Create_Piece* chess;
    King *king = handle->get_turn()==WHITE? chess->get_white_king(): chess->get_black_king();


    //Se il re si muove allora non può più arroccare:
    if(king->get_ismoved())
    {
        return;
    }

    //Devo ottenere la casella della torre:
    //incremento perchè a destra devo sommare a sinistra devo sottrarre:
    int rock_position_kingside= king->get_square()+3;
    king->handle_arrok(this->piece,rock_position_kingside,pieces_attacking);

    int rock_position_queenside= king->get_square()-4;
    king->handle_arrok(this->piece,rock_position_queenside,pieces_attacking);

}

void Movement_Piece::handle_castling_rook()
{
    Movement_Handler move = move_stack.top();

    //Se l'ultima mossa non è del re allora esci
    if(!move.get_piece()->is_king())
    {
        return;
    }

    //Se l'ultima mossa è del re ma non fa 2 spostamenti consegutivi 
    //allora esci
    if(!abs(move.get_from_square()-move.get_to_square())==2)
    {
        return;
    }

    //Ottieni la posizione della torre:
    int rook_position= move.get_to_square() > move.get_from_square() ? move.get_to_square()+1: move.get_to_square()-2;

    //La casella in cui la torre si sposterà:
    int rook_arrock= move.get_to_square() > move.get_from_square() ? move.get_to_square()-1 : move.get_to_square()+1;

    //Muovi la torre:
    piece[rook_arrock]= piece[rook_position];

    //la vecchia posizione della torre andrà a null
    piece[rook_position]=nullptr;
}