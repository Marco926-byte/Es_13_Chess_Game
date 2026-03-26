///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-52-g73f12a06)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:

	protected:
		enum
		{
			ID_FRAME = 6000,
			ID_BOARD,
		};

		wxButton* btn_board;

	public:

		MyFrame1( wxWindow* parent, wxWindowID id = ID_FRAME, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxMAXIMIZE|wxTAB_TRAVERSAL );

		~MyFrame1();

};

///////////////////////////////////////////////////////////////////////////////
/// Class Promotion_dialog
///////////////////////////////////////////////////////////////////////////////
class Promotion_dialog : public wxDialog
{
	private:

	protected:
		enum
		{
			ID_PROMOTION_DIALOG = 6000,
			ID_BTN_QUEEN,
			ID_BTN_BISHOP,
			ID_BTN_ROOK,
			ID_BTN_KNIGHT,
		};

		wxButton* BTN_QUEEN;
		wxButton* BTN_BISHOP;
		wxButton* BTN_ROOK;
		wxButton* BTN_KNIGHT;

	public:

		Promotion_dialog( wxWindow* parent, wxWindowID id = ID_PROMOTION_DIALOG, const wxString& title = wxEmptyString, const wxPoint& pos = wxPoint( -1,-1 ), const wxSize& size = wxSize( 350,350 ), long style = 0 );

		~Promotion_dialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class MyPanel1
///////////////////////////////////////////////////////////////////////////////
class MyPanel1 : public wxPanel
{
	private:

	protected:
		enum
		{
			ID_PANEL = 6000,
		};


	public:

		MyPanel1( wxWindow* parent, wxWindowID id = ID_PANEL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 450,450 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~MyPanel1();

};

