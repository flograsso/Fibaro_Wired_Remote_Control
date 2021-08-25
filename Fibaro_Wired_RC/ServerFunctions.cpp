//#include "ESP32_Fibaro_RS485.h"
#include "ServerFunctions.h"

WebServer server(80);


 
// Funcion al recibir petición POST
// 192.168.0.200/cortina?NUM=1&ACTION=U
// U (Subir) | D (bajar) | S (stop) | F (fauvorite)
void accionarSobreCortina() 
{

   
   // ACTION!
   moverCortina(server.arg(0).toInt(), server.arg(1).charAt(0));

   DEBUG_SERIAL.println("POST RECIBIDO");
   DEBUG_SERIAL.print("Cortina Number: ");
   DEBUG_SERIAL.println(server.arg(0));
   DEBUG_SERIAL.print("Action: ");
   DEBUG_SERIAL.println(server.arg(1));


   // devolver respuesta
   //server.send(200, "text/plain", String("POST ") + server.arg(String("Id")) + " " + server.arg(String("Status")));
      server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
      server.send(200);

      //ledBlink(SENDING_LED_PIN);
}


// Funcion que se ejecutara en la URI '/'
/*
void handleRoot() 
{
   server.send(200, "text/plain", "Hola mundo!");
}
*/


void handleNotFound() 
{
   server.send(404, "text/plain", "Not found");
}


void InitServer()
{
   // Ruteo para '/'
   //server.on("/", handleRoot);
 
   // Definimos dos routeos
   server.on("/cortina", HTTP_POST, accionarSobreCortina);
   server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
 
 
   server.begin();
   DEBUG_SERIAL.println("HTTP server started");
}