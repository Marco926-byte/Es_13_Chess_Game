///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-52-g73f12a06)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyProjectBase.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	btn_board = new wxButton( this, ID_BOARD, _("disegna scacchiera"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( btn_board, 0, wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );
}

MyFrame1::~MyFrame1()
{
}

Promotion_dialog::Promotion_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	BTN_QUEEN = new wxButton( this, ID_BTN_QUEEN, _("REGINA"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( BTN_QUEEN, 0, wxALL|wxEXPAND, 5 );

	BTN_BISHOP = new wxButton( this, ID_BISHOP, _("ALFIERE"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( BTN_BISHOP, 0, wxALL|wxEXPAND, 5 );

	BTN_ROOK = new wxButton( this, ID_BTN_ROOK, _("TORRE"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( BTN_ROOK, 0, wxALL|wxEXPAND, 5 );

	BTN_KNIGHT = new wxButton( this, wxID_ANY, _("CAVALLO"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( BTN_KNIGHT, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();

	this->Centre( wxBOTH );
}

Promotion_dialog::~Promotion_dialog()
{
}

MyPanel1::MyPanel1( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );


	this->SetSizer( bSizer2 );
	this->Layout();
}

MyPanel1::~MyPanel1()
{
}
