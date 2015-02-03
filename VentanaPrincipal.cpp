#include "VentanaPrincipal.hpp"
#include "CambiarNickname.hpp"
#include <iostream>
#include <string>

BEGIN_EVENT_TABLE(VentanaPrincipal, wxFrame)
	EVT_MENU(idSalir, VentanaPrincipal::OnExit)
	EVT_MENU(idAcerca, VentanaPrincipal::OnAbout)
	EVT_MENU(idCambioNick, VentanaPrincipal::OnCambio)
	EVT_BUTTON(idEnviar, VentanaPrincipal::OnEnviarMensaje)
END_EVENT_TABLE()

VentanaPrincipal::VentanaPrincipal(const wxString& titulo, Datos* d) 
: wxFrame(NULL, wxID_ANY, titulo, wxDefaultPosition, wxSize(400,700), wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER)
{
	data = d;

    wxPanel* panel = new wxPanel(this,-1);

    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    this->barraMenu = new wxMenuBar(); 
    this->menuArchivo = new wxMenu();
    this->menuAcercaDe = new wxMenu();

    this->menuAcercaDe->Append(idAcerca, wxT("&Acerca de..."));
    this->menuArchivo->Append(idCambioNick, wxT("&Cambiar Nickname\tCtrl-C"));
    this->menuArchivo->AppendSeparator();
    this->menuArchivo->Append(idSalir, wxT("&Salir\tCtrl-F4"));

    this->barraMenu->Append(menuArchivo, wxT("&Archivo"));
    this->barraMenu->Append(menuAcercaDe, wxT("&Otros"));

    this->SetMenuBar(barraMenu);

    this->mensajesRecibidos = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
    this->mensajeEnviado = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_MULTILINE);

   	this->btnEnviar = new wxButton(panel, idEnviar, wxT("&Enviar Mensaje"));	// El botón para enviar el mensaje.

    this->labelPrincipal = new wxStaticText(panel, wxID_ANY, wxT("Mensajes Enviados/Recibidos:"), wxDefaultPosition, wxSize(300,30));

    hbox1->Add(labelPrincipal,1,wxALIGN_CENTER | wxTOP, 10);
    hbox2->Add(mensajesRecibidos, 3, wxEXPAND | wxALIGN_CENTER, 10);
    hbox3->Add(mensajeEnviado,2,wxEXPAND, 10);
    hbox3->Add(btnEnviar,0,wxLEFT,10);

    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT, 20);
    vbox->Add(hbox2, 5, wxEXPAND | wxLEFT | wxRIGHT, 20);
    vbox->Add(hbox3, 2, wxEXPAND | wxBOTTOM | wxTOP | wxLEFT | wxRIGHT, 20);

    //vbox->SetSizeHints(this);

    panel->SetSizer(vbox);

    //Bind(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(VentanaPrincipal::OnExit),this);

    Centre();

    //iniciarConexion();
}

// Mutex para las impresiones
std::mutex mtx;

void VentanaPrincipal::imprimir(std::string a = "ERROR")
{
    mtx.lock();
    this->mensajesRecibidos->AppendText(wxString(a));
    mtx.unlock();
}

void VentanaPrincipal::recibir_mensajes()
{
    imprimir("Esperando mensajes...\n");
    char temp[MAX_CHAR];
    int sock_server, sock_client, len, size;
    struct sockaddr_in Server, Client;
    
    sock_server = socket(AF_INET, SOCK_STREAM, 0);

    Server.sin_family = AF_INET;
    Server.sin_addr.s_addr = htonl(INADDR_ANY);
    Server.sin_port = htons(data->getPuertoCliente());

    len = bind(sock_server, (struct sockaddr*)&Server, sizeof(Server));
    if(len < 0){
        throw "Él puerto se encuentra ocupado, trata de nuevo en unos momentos...";
        return;
    }

    len = listen(sock_server, 10);

    size = sizeof(struct sockaddr_in);

    sock_client = accept(sock_server, (struct sockaddr*)&Client, (socklen_t* )&size);

    len = 10;

    while(len > 0)
    {
        len = recv(sock_client, temp, MAX_CHAR, 0);
        temp[len] = '\0';
        imprimir(std::string(temp));
    }
    close(sock_client);
}

VentanaPrincipal::~VentanaPrincipal()
{
    // Algo interesante.
}

void VentanaPrincipal::OnExit(wxCommandEvent& event)
{
	this->Destroy();
}

void VentanaPrincipal::OnCambio(wxCommandEvent& event)
{
	//CambiarNickname* cmb = new CambiarNickname(this,wxT("Cambio de Nickname"),data);
    CambiarNickname aboutDialog ( this, wxID_ANY, wxT("Cambio de Nickname"),
                              wxDefaultPosition, wxSize(250, 100), wxDEFAULT_DIALOG_STYLE, data);
    if ( aboutDialog.ShowModal() != wxID_OK )
        std::cout << "Se ha cancelado el cambio de Nickname." << std::endl;
    else
        std::cout << "Se ha cambiado el Nickname correctamente." << std::endl;
}

void VentanaPrincipal::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(wxT("Programa Creado por: Humberto Alejandro Ortega Alcocer\n\nCreado usando wxWidgets para el uso de toda la humanidad.\n\nSi tu computadora explota, es tu culpa,\npor confiar en mi Software, ni yo confío en él. (LOL)"), wxT("Acerca de..."), wxICON_WARNING);
}

void VentanaPrincipal::enviar(wxString msg)
{
    int len = 0;
    std::string ms = msg.ToStdString();
    len = send(sock,ms.c_str(),ms.length(),0);
}

void VentanaPrincipal::OnEnviarMensaje(wxCommandEvent& WXUNUSED(event))
{
    size_t espacios = data->getNickname().length();

    wxString original = mensajeEnviado->GetValue();
    wxString temp;

    for (int i = 0; i < original.Length(); ++i)
    {
        if (original[i] == '\n')
        {
            temp += original[i];
            for (int j = 0; j <= espacios+3; j++)
                temp += ' ';
        }
        else
            temp += original[i];

    }

    original = temp;

	wxString msg = data->getNickname() + ": " + original + "\n";
	mensajeEnviado->SetValue("");
	imprimir(msg.ToStdString());
    enviar(msg);
}

void VentanaPrincipal::iniciarServicio()
{
	if (data->getIpServer() == std::string("localhost"))
	{
		std::cout << "Se reparó la dirección \"localhost\" por 127.0.0.1" << std::endl;
		data->setIpServer("127.0.0.1");
	}
	wxString temp = "El usuario es: " + data->getNickname() + "\n";
	this->mensajesRecibidos->AppendText(temp);
	temp = "La IP del Servidor es: " + data->getIpServer() + "\n";
	this->mensajesRecibidos->AppendText(temp);
	//temp = "El puerto del Servidor es: " + data->getPuertoServer() + "\n";
	//this->mensajesRecibidos->AppendText(temp);
	//temp = "Nuestro puerto es: " + data->getPuertoCliente() + "\n";
	//this->mensajesRecibidos->AppendText(temp);
    std::thread(&VentanaPrincipal::recibir_mensajes,this).detach();
}

void VentanaPrincipal::iniciarConexion()
{
    otro_cliente.sin_addr.s_addr = inet_addr(data->getIpServer().c_str());
    otro_cliente.sin_family = AF_INET;
    otro_cliente.sin_port = htons(data->getPuertoServer());
    sock = socket(AF_INET, SOCK_STREAM,0);
    if(connect(sock, (struct sockaddr*)&otro_cliente, sizeof(otro_cliente)))
        this->mensajesRecibidos->AppendText(wxT("Comenzará la transmisión de datos...\n\n"));
    else
        std::cout << "No se conectó..." << std::endl;
}