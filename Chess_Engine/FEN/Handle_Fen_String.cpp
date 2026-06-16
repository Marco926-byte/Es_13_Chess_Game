#include "Handle_Fen_String.h"
#include "../../Piece_factory/Piece.h"

Handle_Fen_String::Handle_Fen_String
(
    Handle_Chessboard* chess_turn,
    std::shared_ptr<Find_King> find_king
)
    :create_ptr(new Create_Piece()),
    chess_turn_ptr(chess_turn),
    find_king_smart(find_king)
{
    
    piece=new Piece*[64];
    
    for(int i=0; i<64; ++i)
    {
        piece[i]=nullptr;
        map_is_moved[i]=false;
    }

    fen_string="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR - w KQkq - 0 1";

    //Imposto la scacchiera alla fase iniziale
    set_board_fenstring(fen_string);
}

std::map<int,bool> Handle_Fen_String::map_get_is_moved() const
{
    return map_is_moved;
}

void Handle_Fen_String::set_is_moved(bool moved, int position_square)
{
    map_is_moved[position_square]=moved;
}

void Handle_Fen_String::set_board_fenstring(std::string fen_string)
{
    std::string board_fen_string=fen_string.substr(0,fen_string.find(" "));

    //Cancello tutto
    for(int i=0; i<64; i++)
    {
        if(piece[i])
            delete piece[i];
        piece[i]=nullptr;
    }
    
    int row=0;
    int col=0;

    //Analizzo la fen: 
    for(char set_board : board_fen_string)
    {
        if(set_board=='/')
        {
            row++;
            col=0;
        }
        else 
        {
            if(std::isdigit(set_board))    //Controllo se ci sono numeri
            {
                int conv=set_board-'0'; //Nella conversione ASCII per avere 8 devo sottrare
                                        //il valore ASCII di 8 - il valore ASCII di 0 
                col+=conv;
                
            }
            else
            {
                //Creazione e posizionamento dei pezzi
                piece[row*8+col]=create_ptr->create_piece(set_board,row*8+col);
                piece[row*8+col]->set_name_piece(set_board);
                col++;                
            }
        }                               
    }
    this->fen_string=fen_string;
    //Inizio controllo della scacchiera!
    for(int i =0; i<64; i++)
    {
        controll_piece(i);
    }
}

Create_Piece* Handle_Fen_String::get_create_ptr() const
{
    return create_ptr;
}

std::string Handle_Fen_String::generate_fen_string()
{
    //Imposto la fen_string e il contatore nella posizione iniziale
    std::string fen_string="";
    int count_no_piece=0;

    //Devo iterare tutto nelle caselle della scacchiera:
    //Prima le righe:
    for(int row=0; row<8; row++)
    {
        count_no_piece = 0;
        //Poi le colonne
        for(int col=0; col<8; col++)
        {
            //Controllo se nella posizione tot c'è un pezzo:
            if(piece[row*8+col]==nullptr)
            {
                count_no_piece++;
            }
            else    //Se non c'è allora:
            {
                //Controllo se il contatore è numerato
                if(count_no_piece>0)
                {
                    //Prima metto gli eventuali spazi vuoti
                    fen_string+= std::to_string(count_no_piece);

                    //Poi imposto il contatore a 0
                    count_no_piece=0;
                }
                
                //E poi ovviamente inserisco il pezzo puntato.
                fen_string+=piece[row*8+col]->get_name_piece();
            }
        }

        //Fine della riga:
        //Prima controllo se il contatore è positivo:
        if(count_no_piece>0)
        {
            fen_string+=std::to_string(count_no_piece);
        }
        //Nella fen per dire che finisce la riga si usa '/'
        if(row<7)
        {
            fen_string+='/';
        }
    }

    //QUI FORSE DA CAMBIARE, NON SO FORSE È SBAGLIATO
    if(chess_turn_ptr->get_turn()==WHITE)
    {
        fen_string+=" b ";
    }
    else if(chess_turn_ptr->get_turn()==BLACK)
    {
        fen_string+=" w ";
    }

    Piece* king_white = find_king_smart.get()->find_king_current_turn(piece,WHITE);
    if
    (
        king_white
        &&
        !king_white->get_ismoved()
    )
    {
        fen_string+="KQ ";
    }

    Piece* king_black = find_king_smart.get()->find_king_current_turn(piece,BLACK);
    if
    (
        king_black
        &&
        !king_black->get_ismoved()
    )
    {
        fen_string+="kq ";
    }

    if(is_enpassant)
    {
        fen_string+=std::to_string(square_enpassant);
    }
    else
    {
        fen_string+=" - ";
    }

    //TODO: 
    //Contatore delle mosse

    fen_string+= " 0 ";

    if(is_last_move_black)
    {
        count_move_black+=1;
        is_last_move_black=false;
    }

    fen_string+=std::to_string(count_move_black);
    this->fen_string=fen_string;

    return fen_string;
}
void Handle_Fen_String::controll_piece(int i)
{
    /*---PEDONE INIZIO---*/
        if
        (
            piece[i]
            &&
            piece[i]->is_pawn()
            &&
            (
                piece[i]->get_square()>55
                ||
                piece[i]->get_square()<48
            )
            &&
            piece[i]->get_color()==WHITE
        )
        {
            piece[i]->set_ismoved(true);
        }
        
        if
        (
            piece[i]
            &&
            piece[i]->is_pawn()
            &&
            piece[i]->get_square()>=48
            &&
            piece[i]->get_square()<=55
            &&
            piece[i]->get_color()==WHITE
        )
        {
            piece[i]->set_ismoved(false);
        }

        if
        (
            piece[i]
            &&
            piece[i]->is_pawn()
            &&
            (
                piece[i]->get_square()<8
                ||
                piece[i]->get_square()>15
            )
            &&
            piece[i]->get_color()==BLACK
        )
        {
            piece[i]->set_ismoved(true);
        }

        if
        (
            piece[i]
            &&
            piece[i]->is_pawn()
            &&
            piece[i]->get_square()>=8
            &&
            piece[i]->get_square()<=15
            &&
            piece[i]->get_color()==BLACK
        )
        {
            piece[i]->set_ismoved(false);
        }
        /*FINE PEDONE*/

        /*INIZIO TORRE BIANCA*/
        //Controllo se torre bianca, non nella posizione di partenza, non si è mossa
        //Imposto is_moved = true
        if
        (
            piece[i]
            &&
            piece[i]->is_rock()
            &&
            !piece[i]->get_ismoved()
            &&
            piece[i]->get_color()==WHITE
            &&
            (piece[i]->get_square()!=63 && piece[i]->get_square()!=56)
        )
        {
            piece[i]->set_ismoved(true);
        }

        //Controllo se torre bianca nella posizione di partenza non si è mossa
        //imposto is_moved a false
        if
        (
            piece[i]
            &&
            piece[i]->is_rock()
            &&
            !piece[i]->get_ismoved()
            &&
            piece[i]->get_color()==WHITE
            &&
            (piece[i]->get_square()==63 || piece[i]->get_square()==56)
        )
        {
            piece[i]->set_ismoved(false);
        }
            
        //Controllo se torre bianca, non nella posizione di partenza, si è mossa
        //imposto is_moved = true
        if
        (
            piece[i]
            &&
            piece[i]->is_rock()
            &&
            piece[i]->get_ismoved()
            &&
            piece[i]->get_color()==WHITE
            &&
            (piece[i]->get_square()!=63 && piece[i]->get_square()!=56)
        )
        {
            piece[i]->set_ismoved(true);
        }
        

        //Controllo se torre bianca nella posizione di partenza si è mossa
        //imposto is_moved a true
        if
        (
            piece[i]
            &&
            piece[i]->is_rock()
            &&
            piece[i]->get_ismoved()
            &&
            piece[i]->get_color()==WHITE
            &&
            (piece[i]->get_square()==63 || piece[i]->get_square()==56)
        )
        {
            piece[i]->set_ismoved(true);
        }
        /*FINE TORRE BIANCA*/

        /*TORRE NERA*/
        //Controllo se torre bianca nella posizione di partenza non si è mossa
        //imposto is_moved a false
        if
        (
            piece[i]
            &&
            piece[i]->is_rock()
            &&
            !piece[i]->get_ismoved()
            &&
            piece[i]->get_color()==BLACK
            &&
            (piece[i]->get_square()==0 || piece[i]->get_square()==7)
        )
        {
            piece[i]->set_ismoved(false);
        }
        
        //Controllo se torre bianca, non nella posizione di partenza, si è mossa
        //imposto is_moved = true
        if
        (
            piece[i]
            &&
            piece[i]->is_rock()
            &&
            piece[i]->get_ismoved()
            &&
            piece[i]->get_color()==BLACK
            &&
            (piece[i]->get_square()!=0 && piece[i]->get_square()!=7)
        )
        {
            piece[i]->set_ismoved(true);
        }
        //Controllo se torre bianca, non nella posizione di partenza, non si è mossa
        //Imposto is_moved = true
        if
        (
            piece[i]
            &&
            piece[i]->is_rock()
            &&
            !piece[i]->get_ismoved()
            &&
            piece[i]->get_color()==BLACK
            &&
            (piece[i]->get_square()!=0 && piece[i]->get_square()!=7)
        )
        {
            piece[i]->set_ismoved(true);
        }

        //Controllo se torre bianca nella posizione di partenza si è mossa
        //imposto is_moved a true
        if
        (
            piece[i]
            &&
            piece[i]->is_rock()
            &&
            piece[i]->get_ismoved()
            &&
            piece[i]->get_color()==BLACK
            &&
            (piece[i]->get_square()==0 || piece[i]->get_square()==7)
        )
        {
            
            piece[i]->set_ismoved(true);
        }
        /*FINE TORRE NERA*/

        /*---INIZIO RE BIANCO---*/
        if
        (
            piece[i]
            &&
            piece[i]->is_king()
            &&
            piece[i]->get_color()==WHITE
            &&
            piece[i]->get_ismoved()
            &&
            piece[i]->get_square()!=60
        )
        {
            piece[i]->set_ismoved(true);
        }

        if
        (
            piece[i]
            &&
            piece[i]->is_king()
            &&
            piece[i]->get_color()==WHITE
            &&
            !piece[i]->get_ismoved()
            &&
            piece[i]->get_square()!=60
        )
        {
            piece[i]->set_ismoved(true);
        }

        if 
        (
            piece[i]
            &&
            piece[i]->is_king()
            &&
            piece[i]->get_color()==WHITE
            &&
            piece[i]->get_ismoved()
            &&
            piece[i]->get_square()==60
        )
        {
            piece[i]->set_ismoved(true);
        }

        if 
        (
            piece[i]
            &&
            piece[i]->is_king()
            &&
            piece[i]->get_color()==WHITE
            &&
            !piece[i]->get_ismoved()
            &&
            piece[i]->get_square()==60
        )
        {
            piece[i]->set_ismoved(false);
        }
        /*---FINE RE BIANCO---*/

        /*INIZIO RE NERO*/
        if
        (
            piece[i]
            &&
            piece[i]->is_king()
            &&
            piece[i]->get_color()==BLACK
            &&
            piece[i]->get_ismoved()
            &&
            piece[i]->get_square()!=4
        )
        {
            piece[i]->set_ismoved(true);
        }
        if
        (
            piece[i]
            &&
            piece[i]->is_king()
            &&
            piece[i]->get_color()==BLACK
            &&
            !piece[i]->get_ismoved()
            &&
            piece[i]->get_square()!=4
        )
        {
            piece[i]->set_ismoved(true);
        }    
        if
        (
            piece[i]
            &&
            piece[i]->is_king()
            &&
            piece[i]->get_color()==BLACK
            &&
            piece[i]->get_ismoved()
            &&
            piece[i]->get_square()==4
        )
        {
            piece[i]->set_ismoved(true);
        }    
        if
        (
            piece[i]
            &&
            piece[i]->is_king()
            &&
            piece[i]->get_color()==BLACK
            &&
            !piece[i]->get_ismoved()
            &&
            piece[i]->get_square()==4
        )
        {
            piece[i]->set_ismoved(false);
        }
        /*FINE RE NERO*/
        
        /*Controllo pezzo dopo la mossa*/
        if(piece [i] && map_is_moved[i]==true)
        {
            piece[i]->set_ismoved(true);
        }
        
}
void Handle_Fen_String::add_fen_to_map(std::string fen_string)
{
    //Conta quante volte è stata aggiunta la fen string
    this->occurences_position[fen_string]++;
}

std::string Handle_Fen_String::get_fen_string() const
{
    return fen_string;
}

Piece** Handle_Fen_String::get_piece()
{
    return piece;
}

void Handle_Fen_String::set_long_castling(bool long_castling)
{
    is_long_castling=long_castling;
}

void Handle_Fen_String::set_short_castling(bool short_castling)
{
    is_short_castling=short_castling;
}

void Handle_Fen_String::set_is_enpassant(bool enpassant)
{
    is_enpassant=enpassant;
}

void Handle_Fen_String::set_square_enpassant(int enpassant_square)
{
    square_enpassant=enpassant_square;
}

void Handle_Fen_String::set_is_last_move_black(bool last_black)
{
    is_last_move_black=last_black;
}

Handle_Fen_String::~Handle_Fen_String()
{    
    delete create_ptr;
    create_ptr=nullptr;

    for(int i=0; i<64; ++i)
    {
        if(piece[i]!=nullptr)
        {
            delete piece[i];
            piece[i]=nullptr;   
        }
        
    }
    delete[] piece;
}