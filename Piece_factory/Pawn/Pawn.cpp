#include "Pawn.h"
#include "../../Handle_Fen_String.h"

Pawn::Pawn(int pos, char character)
    :Piece(pos,character)
    {

    }

/*---------FUNZIONE VIRTUALE------------------*/
void Pawn::update_legal_moves(std::shared_ptr<Handle_Fen_String> ptr_smart)
{
    std::vector<int> legal_moves={};

    Piece** piece = ptr_smart.get()->get_piece();

    this->handle_movement(piece,legal_moves);
    this->handle_offensive(piece,legal_moves);
    
    set_legal_moves(legal_moves);
}
/*---------FINE FUNZIONE VIRTUALE-------------*/

/*---------FUNZIONI DEL PEDONE-----------------*/
void Pawn::handle_movement(Piece** ptr, std::vector<int>& legal_moves)
{
    //Ovviamente il pedone si può muovere di una casella avanti 
    int directions[2]{8,16};

    //Se il pedone non si è mosso può sfruttare il doppio salto
    int stop_index=get_ismoved() ? 1 : 2;

    //Siccome la mia scacchiera parte con 00 la parte superiore
    //allora siccome il bianco parte dal lato inferiore della 
    //scacchiera allora devo sottrarre a un numero già grande 
    int color_team=this->get_color()==WHITE ? -1 : 1;

    //Parto con il ciclo, serve per poter dire se nel quadrato è 
    //presente un pezzo, sennò aggiungi la posizione alle mosse possibili e legali

    for(int i=0; i<stop_index; i++)
    {
        int square= this->get_square() + directions[i] * color_team;

        if(square>0 && square<64)
        {
            if(ptr[square]==nullptr)
            {
                legal_moves.push_back(square);
            }
            else
                break;
        }
    }
}

void Pawn::handle_offensive(Piece**ptr, std::vector<int>& legal_moves)
{
    //le due direzioni di attacco
    int directions[2]{7,9};
    
    //Ottengo il colore della squadra
    int color_team= this->get_color()==WHITE? -1 : 1;
    
    //Ciclo le due direzioni d'attacco:
    for(int i=0; i<2; i++)
    {

        //this->get_map_path()[directions[i]]={};
        
        //Inizializzo square come la casella d'attacco
        int square= this->get_square()+directions[i]*color_team;

        if(square>=0 && square < 64 && abs(this->get_col()- square %8)<=1)
        {
            if(ptr[square] != nullptr && this->get_color()!=ptr[square]->get_color())
            {
                legal_moves.push_back(square);
                this->get_map_path()[directions[i]].push_back(square);
            }
        }
    }

}

void Pawn::get_attack(Piece **board, std::vector<int> &attacked_squares)
{
    // 1. Determina la direzione in base al colore
    // Se Bianco va su (-8), se Nero va giù (+8)
    int direction = (this->get_color() == WHITE) ? -8 : 8; 

    // 2. Le due diagonali di attacco (Sinistra e Destra)
    int attack_offsets[] = {direction - 1, direction + 1};

    for(int offset : attack_offsets)
    {
        int target = this->get_square() + offset;
        
        // Controllo se è fuori dalla scacchiera (verticalmente)
        if(target < 0 || target >= 64) 
            continue;

        // Controllo fondamentale: Il pedone non può "fare il giro" del bordo
        // Se sono sulla colonna H (7) non posso attaccare a destra (colonna 0)
        int current_col = this->get_col();
        int target_col = target % 8;

        if(abs(current_col - target_col) <= 1) 
        {
            // Aggiungo SEMPRE la casella, anche se è vuota!
            // Il Re non può andare lì perché è una "kill zone"
            attacked_squares.push_back(target);
        }
    }
}

void Pawn::handle_en_passant(int square)
{
    std::vector<int> v_legal_move = this->get_legal_moves();
    v_legal_move.push_back(square);
    this->set_legal_moves(v_legal_move);
}

/*-----------FINE FUNZIONI DEL PEDONE---------------*/
