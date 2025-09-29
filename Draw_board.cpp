#include "Draw_board.h"

Draw_board::Draw_board(wxFrame* parent)
    :MyPanel1(parent,6000,wxPoint(200,100))
    {
        Bind(wxEVT_PAINT,&Draw_board::on_paint,this);
        image.LoadFile(file,format);
    }


void Draw_board::on_paint(wxPaintEvent& evt)
{
    wxPaintDC dc(this);
    wxSize size= GetClientSize();   //Prende la grandezza della bitmap(guarda in start)
    
    wxCoord square_size=size.GetWidth()/8; //Divido per 8 perchè ogni riga è formata da 8 caselle
       
    //square_size=56

    //Disegno la schacchiera:
    for(int row=0; row<8; row++)
    {
        for(int col=0; col<8; col++)
        {
            draw_squares(dc,row,col,square_size);
        }
    }

    render_whiteking(dc);
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
    /*------------------------------------------------------------------*/
        if(x==0 && y==0)
        {
            square_color = wxColor(250,128,114);    //TODO: da togliere
        }
    /*-------------------------------------------------------------------*/
        else
        {
            square_color = wxColor(185,182,174);
        }            
    }
    else
    {
        square_color = wxColour(75, 115, 153);
    }

    dc.SetPen(*wxTRANSPARENT_PEN);

    if(selected_square==(row*8+col))
    {
        //Todo: fare il bordo esterno rotondo
    }

    dc.SetBrush(square_color);
    
    wxRect squareRect(x, y, square_size, square_size);
    
    dc.DrawRectangle(squareRect);

}

void Draw_board::render_whiteking(wxDC& dc)
{
    resized = wxBitmap(image.Scale(image_width, image_height, wxIMAGE_QUALITY_HIGH ));
    dc.DrawBitmap( resized, 218, 385, false );
}

void Draw_board::OnSize(wxSizeEvent& event)
{
    Refresh();
    //skip the event.
    event.Skip();
}
