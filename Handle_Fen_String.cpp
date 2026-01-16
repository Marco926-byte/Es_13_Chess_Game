#include "Handle_Fen_String.h"
#include "Piece_factory/Piece.h"

Handle_Fen_String::Handle_Fen_String()
    :create_ptr(new Create_Piece())
    
{
    piece=new Piece*[64];
    for(int i=0; i<64; ++i)
    {
        piece[i]=nullptr;
    }

    fen_string="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR - w KQkq - 0 1";
    //Imposto la scacchiera alla fase iniziale
    set_board_fenstring(fen_string);
}

void Handle_Fen_String::set_board_fenstring(std::string fen_string)
{
    std::string board_fen_string=fen_string.substr(0,fen_string.find(" "));

    for(int i=0; i<64; i++)
    {
        if(piece[i])
            delete piece[i];
        piece[i]=nullptr;
    }
    
    int row=0;
    int col=0;

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
                //fen_string+=piece[row*8+col]->get_name_piece();
                fen_string+=piece[row*8+col]->get_name_piece();
            }
        }

        //Fine della riga:
        //Prima controllo se il contatore è positivo:
        if(count_no_piece>0)
        {
            fen_string+=std::to_string(count_no_piece);
            //count_no_piece=0;
        }
        //Nella fen per dire che finisce la riga si usa '/'
        if(row<7)
        {
            fen_string+='/';
        }
    }

    fen_string+= "w KQkq - 0 1";
    this->fen_string=fen_string;
    //set_board_fenstring(fen_string);
    //add_fen_to_map(fen_string);

    return fen_string;
}

void Handle_Fen_String::add_fen_to_map(std::string fen_string)
{
    //Conta quante volte è stata aggiunta la fen string
    this->occurences_position[fen_string]++;
}

std::string Handle_Fen_String::get_fen_string()
{
    return fen_string;
}

Piece** Handle_Fen_String::get_piece()
{
    return piece;
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
