#ifndef CAMBIAR_NICKNAME_HPP
#define CAMBIAR_NICKNAME_HPP

#include <wx/wx.h>
#include "Datos.hpp"

class CambiarNickname: public wxDialog
{
public:
 
	CambiarNickname ( wxWindow * parent, wxWindowID id, const wxString & title,
	              	const wxPoint & pos = wxDefaultPosition,
	              	const wxSize & size = wxDefaultSize,
	              	long style = wxDEFAULT_DIALOG_STYLE, Datos* dd = NULL );
 
	wxTextCtrl * dialogText;
 
private:

	Datos* data;
 
	void OnOk( wxCommandEvent & event );
 
	DECLARE_EVENT_TABLE()
};

#endif