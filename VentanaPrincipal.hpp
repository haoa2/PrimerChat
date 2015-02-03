#ifndef VENTANA_PRINCIPAL_HPP_INCLUDED
#define VENTANA_PRINCIPAL_HPP_INCLUDED
#define MAX_CHAR 1024

// GUI y Programación
#include <wx/wx.h>
#include "Datos.hpp"
//Redes
#include <fcntl.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
//Multithreading
#include <thread>
#include <mutex>


class VentanaPrincipal : public wxFrame
{
public:
    VentanaPrincipal(const wxString& titulo, Datos* d);
    virtual ~VentanaPrincipal();
    void iniciarConexion(); // inicia la conexión xD
    void iniciarServicio(); // inicia el servicio xD

private:
    // Multithreading
    void recibir_mensajes();
    void imprimir(std::string);
    void enviar(wxString);

    int sock;
    struct sockaddr_in otro_cliente;

	// Eventos de GUI
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnCambio(wxCommandEvent &event);
    void OnEnviarMensaje(wxCommandEvent& WXUNUSED(event));

    Datos* data;

    wxStaticText* labelPrincipal;

    wxMenuBar* barraMenu; 	// La barra de menús.
    wxMenu*	menuArchivo; 	// El menú "Archivo"
    wxMenu* menuAcercaDe;	// El menú "Acerca De"

    wxTextCtrl* mensajesRecibidos;	// Aquí se mostrará el chat.
    wxTextCtrl* mensajeEnviado;		// Aquí se escribe el mensaje.

    wxButton* btnEnviar;	// El botón para enviar el mensaje.

    enum Menu {
    	idSalir,
    	idCambioNick,
    	idAcerca,
    	idEnviar
    };

    DECLARE_EVENT_TABLE();
};

#endif
