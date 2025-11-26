#include "Draw_board.h"

Draw_board::Draw_board(wxFrame* parent)
    :MyPanel1(parent,6000,wxPoint(200,100)),
    //Inizializzazione dei puntatori:
        chess_handler(new Handle_Chessboard()),
        fen_shared(new Handle_Fen_String()),
        game_movement(new Movement_Piece()),
        mouse_handler(new Handle_Mouse_Input(this,fen_shared))           
    {
        //Posizione iniziale:
        fen_shared.get()->fen_string_stuff();

        //Rappresentazione dei pezzi:
        render_piece();

        //game_movement->update_move_pieces();
        
        Bind(wxEVT_PAINT,&Draw_board::on_paint,this);
     
        this->Bind(wxEVT_LEFT_DOWN, &Handle_Mouse_Input::onMouseLeftDown, mouse_handler);
        this->Bind(wxEVT_LEFT_UP, &Handle_Mouse_Input::onMouseLeftUp, mouse_handler);
    }


void Draw_board::on_paint(wxPaintEvent& evt)
{
    wxPaintDC dc(this);
    wxSize size= GetClientSize();   //Prende la grandezza della bitmap(guarda in start)    
    
    wxCoord square_size=size.GetWidth()/8; //Divido per 8 perchè ogni riga è formata da 8 caselle

    //Disegno la schacchiera:
    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {
            draw_squares(dc,row,col,square_size);
            draw_piece(dc,row,col,square_size);
        }
    }
}

/*

    Note per capire bene come vengono disegnati i quadrati nel caso fai ooh cazzo fai...
    Allora la riga zero è la parte superiore insomma il lato alto del quadrato (la schacchiera)
    riga 1 e colonna 1 appartiene alla grande diagonale a destra quindi va da 0(su) a
    7 (giù).

*/

void Draw_board::draw_squares(wxDC& dc, int row, int col, wxCoord square_size)
{
    wxCoord x= col*square_size;
    wxCoord y= row*square_size;
    
    wxColor square_color;

    //Imposto il colore delle caselle...
    if((row+col)%2==0)
    {
        square_color = wxColor(185,182,174);           
    }
    else
    {
        square_color = wxColour(75, 115, 153);
    }

    dc.SetPen(*wxTRANSPARENT_PEN);

    //Colora la casella selezionata
    if(mouse_handler->get_is_select_piece())
    {
        if(mouse_handler->get_selected_piece()==row*8+col)
        {
            square_color=wxColor(50,50,50);
            dc.SetPen(wxPen(wxColor(0,0,0),2));     
        }
    }
    
    
    dc.SetBrush(square_color);

    wxRect squareRect(x, y, square_size, square_size);    
    dc.DrawRectangle(squareRect);
}

void Draw_board::draw_piece(wxDC& dc, int row, int col, wxCoord square_size)
{
    if(fen_shared.get()->get_piece()[row*8+col]==nullptr)
    {
        return;
    }

    wxCoord x= col * square_size;
    wxCoord y= row * square_size;
    
    dc.DrawBitmap(chess_piece_bitmaps[
        fen_shared.get()->get_piece()[row*8+col]->get_name_piece()],x,y,true);
}

void Draw_board::render_piece()
{
    //wxLogMessage("entro in render_piece");
    char all_piece[]=
    {
        'b','k','n','p','q','r',
        'B','K','N','P','Q','R'
    };

    for(char piece:all_piece)
    { 
        //Percorso del file:
        std::string path = "/home/marco/Documenti/Visual_Studio_Code_esercizi/es13Creare_wxBitmap/image/"+std::string(1,piece)+".png";
        
        //Verifico il caricamento dell'immagine:
        bool load_result = bitmap.LoadFile(path,wxBITMAP_TYPE_PNG);
        
        int square_size= GetClientSize().GetWidth()/8;

        //Dimensiona immagine 100x100
        if(load_result && bitmap.IsOk())
        {
            wxImage image= bitmap.ConvertToImage();
            image.Rescale(square_size,square_size,wxIMAGE_QUALITY_HIGH);
            bitmap=wxBitmap(image);
            chess_piece_bitmaps[piece]=bitmap;
        }
        else
        {
            wxLogMessage("1 bitmap è inutilizzabile...");
            continue;
        }
    }    
}

void Draw_board::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}


Draw_board::~Draw_board()
{    
    delete game_movement;
    game_movement=nullptr;

    delete chess_handler;
    chess_handler=nullptr;

    delete mouse_handler;
    mouse_handler=nullptr;
}