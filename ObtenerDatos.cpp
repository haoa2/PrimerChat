#include "ObtenerDatos.hpp"
#include <string>

ObtenerDatos::ObtenerDatos(wxWindow* parent, const wxString& titulo, Datos* d)
: wxDialog(parent, wxID_ANY, titulo, wxPoint(wxID_ANY, wxID_ANY), wxSize(280,250))
{
    datos = d;
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hbox5 = new wxBoxSizer(wxHORIZONTAL);

    ipServerLabel = new wxStaticText(panel, wxID_ANY, wxT("IP del Servidor: "), 
        wxDefaultPosition, wxSize(120,-1));
    puertoServerLabel = new wxStaticText(panel,wxID_ANY, wxT("Puerto del Servidor: "),
        wxDefaultPosition, wxSize(120,-1));
    puertoClienteLabel = new wxStaticText(panel,wxID_ANY,wxT("Puerto del Cliente: "),
        wxDefaultPosition, wxSize(120,-1));
    NicknameLabel = new wxStaticText(panel,wxID_ANY,wxT("Nickname a usar: "),
        wxDefaultPosition, wxSize(120,-1));

    ipServerCampo = new wxTextCtrl(panel, wxID_ANY);
    puertoServerCampo = new wxTextCtrl(panel, wxID_ANY);
    puertoClienteCampo = new wxTextCtrl(panel, wxID_ANY);
    NicknameCampo = new wxTextCtrl(panel, wxID_ANY);

    btnComenzar = new wxButton(panel, BUTTON_login, wxT("Comenzar Chat"));
    btnSalir = new wxButton(panel, wxID_EXIT, wxT("Salir"));

    hbox1->Add(ipServerLabel, 0);
    hbox1->Add(ipServerCampo, 1);
    hbox2->Add(puertoServerLabel, 0);
    hbox2->Add(puertoServerCampo, 1);
    hbox3->Add(puertoClienteLabel, 0);
    hbox3->Add(puertoClienteCampo, 1);
    hbox4->Add(NicknameLabel, 0);
    hbox4->Add(NicknameCampo, 1);
    hbox5->Add(btnComenzar);
    hbox5->Add(btnSalir);

    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    vbox->Add(hbox2, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    vbox->Add(hbox3, 2, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    vbox->Add(hbox4, 3, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
    vbox->Add(hbox5, 4, wxALIGN_RIGHT | wxTOP | wxRIGHT | wxBOTTOM, 10);

    Bind(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(ObtenerDatos::OnClose),this);

    panel->SetSizer(vbox);
    CenterOnParent();
    Centre();

}

wxBEGIN_EVENT_TABLE(ObtenerDatos, wxDialog)
    EVT_BUTTON(wxID_EXIT, ObtenerDatos::OnQuit)
    EVT_BUTTON(BUTTON_login, ObtenerDatos::OnLogin)
wxEND_EVENT_TABLE()

void ObtenerDatos::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Destroy();
    Close(true);
}

void ObtenerDatos::OnLogin(wxCommandEvent& WXUNUSED(event))
{
    wxString ipServer = ipServerCampo->GetValue();
    wxString puertoServer = puertoServerCampo->GetValue();
    wxString puertoCliente = puertoClienteCampo->GetValue();
    wxString nick = NicknameCampo->GetValue();

    if(nick.empty() || ipServer.empty() || puertoServer.empty() || puertoCliente.empty())
    {
        wxMessageBox(wxT("Faltan datos en la entrada"),wxT("Error Entrada"), wxICON_WARNING);
    }
    else
    {
        if(!puertoServer.Cmp(puertoCliente))
        {
            wxMessageBox(wxT("Los puertos no pueden ser iguales"), wxT("Error Entrada"), wxICON_WARNING);
        }
        else
        {
            wxMessageBox(wxT("Los datos son correctos"), wxT("Correcto"), wxICON_INFORMATION);
            DatosValidos = true;
            datos->setNickname(nick.ToStdString());
            datos->setIpServer(ipServer.ToStdString());
            datos->setPuertoServer(wxAtoi(puertoServer));
            datos->setPuertoCliente(wxAtoi(puertoCliente));
            Destroy();
        }
    }
}

void ObtenerDatos::OnClose(wxCloseEvent& event)
{
    if(!DatosValidos)
    {
        GetParent()->Close();
    }
    GetParent()->Enable();
    event.Skip();
}

ObtenerDatos::~ObtenerDatos()
{
    // Destructor.
}
