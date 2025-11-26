#include "Piece.h"

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

bool Piece::is_pawn()
{
    return type_piece==PAWN;
}

bool Piece::is_rock()
{
    return type_piece==ROCK;
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

Piece::Piece(int pos_square, char c)
{
    this->square=pos_square;

    this->row=square/8;
    this->coloum=square%8;
    
    this->name_piece=c;

    //Controllo se è maiuscolo o no...
    if(isupper(c))
        this->color=WHITE;
    else
        this->color=BLACK;

    c=toupper(c);
    
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
    else
    {
        wxLogMessage(wxT("ERRORE NEL COSTRUTTORE DI PIECE"));
    
    }  
    //Inizializzo moved a false pk non ho ancora mosso
    this->is_moved=false;   
    
}
/*Fine Costruttore*/

/*Funzioni*/

void Piece::diagonal_move(Piece* board[64],std::vector<int> &legal_moves)
{
    //posizioni delle quattro diagonali della cella avanzato di 1 insomma   
    int diagonal[4]{9,7,-9,-7};
    
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
        //parte dal quadrato selezionato
    
        this->square=square;
        //registro le diagonali singole nella mappa
    
        this->map_path[diagonal[i]]={}; //L'ho messo perchè serve a resettare il vettore
        for(int j=0;j<end_board_diagonal[4];j++)
        {
            //Per ogni square:
            //somma al valore della diagonale singola
            square+=diagonal[i];

            //Se il pezzo è dello stesso colore allora stoppati
            if(board[square]!=nullptr && this->color==board[square]->get_color())
            {
                break;
            }

            //Se il quadrato è vuoto oppure del colore opposto aggiungi alle mosse legali
            legal_moves.push_back(square);
            this->map_path[diagonal[i]].push_back(square);

            //Se il quadrato è appartenuto a un pezzo di colore opposto allora stoppati
            if(board[square]!=nullptr&& this->color!=board[square]->get_color())
            {
                break;
            }
            
        }

    }
}

void Piece::straight_move(Piece* board[64],std::vector<int> &legal_moves)
{
    //Singolo spostamento dritto
    int single_straight[4]={-1,-8,+8,1};

    //Spostamento dritto fino alla fine della scacchiera
    int end_board_straight[4]=
    {
        this->row,
        this->coloum,
        7-this->row,
        7-this->coloum
    };

    for(int i=0; i<4; i++)
    {
        //Inzio mettendo lo square dove si trova il pezzo
        this->square=square;
        //Registro le possibili mosse dritte
        this->map_path[single_straight[4]]={};

        for(int j=0; j<end_board_straight[4]; j++)
        {
            //sommo la posizione con le mosse future diritte
            square+=single_straight[i];
            //Se c'è qualcosa e c'è un pezzo dello stesso colore allora...
            if(board[square]!=nullptr && this->color==board[square]->color)
            {
                //rompi il ciclo
                break;
            }
            //Allora aggiungi il blocco alle mosse legali...
            legal_moves.push_back(square);
            this->map_path[single_straight[i]].push_back(square);
            
            //Se c'è qualcosa e c'è un pezzo del colore diverso allora...
            if(board[square]!=nullptr && this->color!=board[square]->color)
            {
                //rompi il ciclo
                break;
            }
        }
    }
}

//Controlla il percorso del re:
std::vector<int> Piece::check_is_king(Piece* board[64], Piece *King)
{
    //Loop attraverso tutte le direzioni della mappa
    for(auto const &i : this->map_path)
    {
        auto const &direzione=i.first;
        auto const &percorso=i.second;
        //Loop fino allo square del percorso
        for(int square :percorso)
        {
            //Se nel quadrato del percorso trovi il Re
            if(board[square]==King)
            {
                //Riportami la posizione del percorso sulla mappa
                return this->map_path[direzione];
            }
        }
    }
    //Se non trovi nulla allora non riportarmi niente
    return {};
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
