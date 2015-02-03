#ifndef OBTENER_DATOS_HPP_INCLUDED
#define OBTENER_DATOS_HPP_INCLUDED

#include <wx/wx.h>
#include "Datos.hpp"

class ObtenerDatos : public wxDialog
{
public:
    ObtenerDatos(wxWindow* parent, const wxString& titulo, Datos* d);
    virtual ~ObtenerDatos();


private:
    Datos* datos;

    wxStaticText* ipServerLabel;
    wxStaticText* puertoServerLabel;
    wxStaticText* puertoClienteLabel;
    wxStaticText* NicknameLabel;

    wxTextCtrl* ipServerCampo;
    wxTextCtrl* puertoServerCampo;
    wxTextCtrl* puertoClienteCampo;
    wxTextCtrl* NicknameCampo;

    wxButton* btnComenzar;
    wxButton* btnSalir;

    bool DatosValidos = false; // Para garantizar integridad en datos.

    void OnQuit(wxCommandEvent& WXUNUSED(event));
    void OnLogin(wxCommandEvent& WXUNUSED(event));
    void OnClose(wxCloseEvent& event);

    enum 
    {
        BUTTON_login = wxID_HIGHEST + 1
    };

    wxDECLARE_EVENT_TABLE();
};

#endif
