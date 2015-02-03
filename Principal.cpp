#include "Principal.hpp"
#include "VentanaPrincipal.hpp"
#include "ObtenerDatos.hpp"
#include "Datos.hpp"
#include <iostream>

bool Principal::OnInit()
{
	Datos* data = new Datos();
    VentanaPrincipal* pr = new VentanaPrincipal(wxT("Chat v0.1"), data);
    pr->Show(true);
    ObtenerDatos* datos = new ObtenerDatos(pr, wxT("Datos del otro Cliente"), data);
    datos->ShowModal();
    pr->iniciarServicio();
    wxMessageBox(wxT("Presione OK para conectarse al servidor..."), wxT("Iniciando Servicio"), wxICON_WARNING);
    pr->iniciarConexion();
    return true;
}

wxIMPLEMENT_APP(Principal);