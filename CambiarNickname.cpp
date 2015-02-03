#include "CambiarNickname.hpp"
#include <iostream>
#include <string>

CambiarNickname::CambiarNickname ( wxWindow * parent, wxWindowID id, const wxString & title,
                           const wxPoint & position, const wxSize & size, long style, Datos* dd )
: wxDialog( parent, id, title, position, size, style)
{
	data = dd;
	wxString s;
	wxPoint p;
	wxSize  sz;

	p.x = 6; p.y = 2;
 
	sz.SetWidth(size.GetWidth() - 20);
	sz.SetHeight(size.GetHeight() - 70);
 
	dialogText = new wxTextCtrl ( this, -1,"", p,sz);

	p.y += sz.GetHeight();
 
	wxButton * b = new wxButton( this, wxID_OK, _("Aceptar"), p, wxDefaultSize );
	p.x += 100;
	wxButton * c = new wxButton( this, wxID_CANCEL, _("Cancelar"), p, wxDefaultSize );
}

BEGIN_EVENT_TABLE(CambiarNickname, wxDialog)
	EVT_BUTTON(wxID_OK, CambiarNickname::OnOk)
END_EVENT_TABLE()

void CambiarNickname::OnOk(wxCommandEvent& event)
{
	if(dialogText->GetValue().ToStdString() != std::string(""))
		data->setNickname(dialogText->GetValue().ToStdString());
	
	std::cout << "Se ha cambiado el Nickname a: " << data->getNickname() << std::endl;
	GetParent()->Enable();
	event.Skip();
}