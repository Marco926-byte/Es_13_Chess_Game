#include "Piece.h"
#include "../Handle_Fen_String.h"

/*Getter:*/
int Piece::get_row() const
{
    return row;
}

int Piece::get_col() const
{
    return coloum;
}

int Piece::get_square() const 
{
    return square;
}

std::string Piece::get_debug() const
{
    std::string ciao= "eila campione";
    return ciao;
}

char Piece::get_name_piece() const
{
    return name_piece;
}

bool Piece::get_ismoved() const
{
    return is_moved;
}

Color Piece::get_color() const
{
    return color;
}

std::vector<int> Piece::get_legal_moves() const
{
    return legal_moves;
}

std::map<int,std::vector<int>> Piece::get_map_path() const
{
    return map_path;
}

bool Piece::is_legal_move(int square) const
{
    for(std::size_t move=0; move!=this->legal_moves.size();move++)
    {
        if(square==this->legal_moves[move])
        {
            return true;
        }
        
    }
    
    return false;
}

bool Piece::is_king()
{
    return type_piece==KING;
}
bool Piece::is_queen()
{
    return type_piece==QUEEN;
}
bool Piece::is_pawn()
{
    return type_piece==PAWN;
}

bool Piece::is_rock()
{
    return type_piece==ROCK;
}

bool Piece::is_bishop()
{
    return type_piece=BISHOP;
}
bool Piece::is_knight()
{
    return type_piece=KNIGHT;
}
/*Fine Getter*/

/*Setter:*/
void Piece::set_row(int new_row)
{
    this->row=new_row;
}

void Piece::set_col(int new_col)
{
    this->coloum=new_col;
}

void Piece::set_square(int new_square)
{
    this->square=new_square;
    this->row=new_square/8;
    this->coloum=new_square%8;
}

void Piece::set_name_piece(char new_name)
{
    this->name_piece=new_name;
}

void Piece::set_ismoved(bool new_moved)
{
    this->is_moved=new_moved;
}

void Piece::set_color(Color new_color)
{
    this->color=new_color;
}

void Piece::set_legal_moves(std::vector<int> new_legal_moves)
{
    this->legal_moves=new_legal_moves;
}
/*Fine Setter*/

/*Costruttore*/
Piece::Piece(int pos_square,char c)
   :row(pos_square/8),
    coloum(pos_square%8),
    square(pos_square),
    name_piece(c)
{
    //Controllo se è maiuscolo o no...
    if(isupper(c))
        this->color=WHITE;
    else
        this->color=BLACK;

    //c=toupper(c);
    
    //Inizializzo tutti gli attributi privati
    //serve per stringa FIN
    std::map<char,Character> mp_character=
    {
        {'P',PAWN},{'R',ROCK},{'B',BISHOP},
        {'N',KNIGHT},{'Q',QUEEN},{'K',KING}
    };
    char upper_c=toupper(c);
    if(mp_character.count(upper_c))
    {
        this->type_piece=mp_character[upper_c];
    }
    
    //Inizializzo moved a false pk non ho ancora mosso
    this->is_moved=false;   
}
/*Fine Costruttore*/

/*Funzioni*/
void Piece::diagonal_move(Piece** ptr,std::vector<int> &legal_moves)
{
    //posizioni delle quattro diagonali della cella avanzato di 1 insomma   
    int diagonal[4]{-9,-7,7,9};

    this->map_path[this->square]={};

    //posizione delle quattro diagonali della cella in totale
    int end_board_diagonal[4]
    {
        std::min(this->row,this->coloum),
        std::min(this->row,7-this->coloum),
        std::min(7-this->row,this->coloum),
        std::min(7-this->row,7-this->coloum),
    };

    //Creo for per le 4 diagonali
    for(int i=0; i<4; i++)
    {
        int current_square_move=this->square;
                                            //Questa inizializzazione è per calcolarmi 
                                            //le mosse che può fare il pezzo 

        for(int j=0;j<end_board_diagonal[i];j++)
            //ciclo for per le mosse, ovviamente non devo uscire dalla scacchiera
        {
            current_square_move+=diagonal[i];   
                                            //Importante! qua la variabile memorizza
                                            //le mosse legali per la diagonale[i]

            if(current_square_move<0 || current_square_move>= 64)
                //Controllino per non avere il SegFault :))))
            {
                break; //Casella fuori dalla scacchiera 
            }

            //Se il pezzo è dello stesso colore allora stoppati
            if(ptr[current_square_move]!=nullptr && 
                this->color==ptr[current_square_move]->get_color())
            {
                break;
            }

            //Se il quadrato è vuoto oppure del colore opposto aggiungi alle mosse legali
            legal_moves.push_back(current_square_move);
            
            //Inserisco nella map_path la mossa legale
            this->map_path[this->square].push_back(current_square_move);
            
            //Se il quadrato è appartenuto a un pezzo di colore opposto allora stoppati
            if(ptr[current_square_move]!=nullptr&& 
                this->color!=ptr[current_square_move]->get_color())
            {
                break;
            }
            
        }

    }
}

void Piece::straight_move(Piece**ptr,std::vector<int> &legal_moves)
{
    //Singolo spostamento dritto
    int single_straight[4]={-8,8,-1,1};

    this->map_path[this->square]={};

    //Spostamento dritto fino alla fine della scacchiera
    int end_board_straight[4]=
    {
        this->row,
        7-this->row,
        this->coloum,
        7-this->coloum
    };

    for(int i=0; i<4; i++)
    {
        //Registro le possibili mosse dritte
        //Inizio mettendo lo square dove si trova il pezzo
        int current_square=this->square;
        int current_square_move=current_square;

        for(int j=0; j<end_board_straight[i]; j++)
        {
            current_square_move+=single_straight[i];

            if(current_square_move<0 || current_square_move>= 64)
            {
                break; //Casella fuori dalla scacchiera 
            }
            
            //Se c'è qualcosa e c'è un pezzo dello stesso colore allora...
            if(ptr[current_square_move]!=nullptr && 
                this->color==ptr[current_square_move]->color)
            {
                //rompi il ciclo
                break;
            }

            //Allora aggiungi il blocco alle mosse legali...
            legal_moves.push_back(current_square_move);
            this->map_path[current_square].push_back(current_square_move);

            //Se c'è qualcosa e c'è un pezzo del colore diverso allora...
            if(ptr[current_square_move]!=nullptr && 
                this->color!=ptr[current_square_move]->color)
            {
                //rompi il ciclo
                break;
            }
        }
    }
}

void Piece::add_legal_move(int square)
{
    for(int pos : this->legal_moves)
    {
        if(pos==square)
            return;
    }
    this->legal_moves.push_back(square);
}

void Piece::remove_legal_move(int square)
{
    for(std::size_t pos=0; pos!=this->legal_moves.size(); pos++)
    {
        if(this->legal_moves[pos]==square)
        {
            this->legal_moves.erase(this->legal_moves.begin()+pos);
            return;
        }
    }
}
/*Fine Funzioni*/
