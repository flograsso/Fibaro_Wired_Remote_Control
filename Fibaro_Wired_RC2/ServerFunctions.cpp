//#include "ESP32_Fibaro_RS485.h"
#include "ServerFunctions.h"

fauxmoESP fauxmo;
AsyncWebServer server(80);
ArduinoQueue<movimiento_t> colaMovimientos(15);



 
// Funcion al recibir petición POST
// 192.168.0.200/cortina?NUM=1&ACTION=U
// U (Subir) | D (bajar) | S (stop) | F (fauvorite)
/*
void accionarSobreCortina() 
{

   server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
   server.send(200);
   // ACTION!
   moverCortina(server.arg(0).toInt(), server.arg(1).charAt(0));

   DEBUG_SERIAL.println("POST RECIBIDO");
   DEBUG_SERIAL.print("Cortina Number: ");
   DEBUG_SERIAL.println(server.arg(0));
   DEBUG_SERIAL.print("Action: ");
   DEBUG_SERIAL.println(server.arg(1));


   // devolver respuesta
   //server.send(200, "text/plain", String("POST ") + server.arg(String("Id")) + " " + server.arg(String("Status")));


      //ledBlink(SENDING_LED_PIN);
}
*/


// Funcion que se ejecutara en la URI '/'
/*
void handleRoot() 
{
   server.send(200, "text/plain", "Hola mundo!");
}
*/

/*
void handleNotFound() 
{
   server.send(404, "text/plain", "Not found");
}
*/


void InitServer()
{
   // Ruteo para '/'
   //server.on("/", handleRoot);
 
   // Definimos dos routeos
   //server.on("/cortina", HTTP_POST, accionarSobreCortina);
   //server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
 
 
   //server.begin();
   DEBUG_SERIAL.println("HTTP server started");

   server.on("/cortina", HTTP_POST, [](AsyncWebServerRequest *request)
             {
                request->send(200, "text/plain", "OK");

                movimiento_t mov;
                // ACTION!
                int params = request->params();
                for (int i = 0; i < params; i++)
                {
                   AsyncWebParameter *p = request->getParam(i);
                   if (p->isFile())
                   { //p->isPost() is also true
                      Serial.printf("FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
                   }
                   else if (p->isPost())
                   {
                      Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
                   }
                   else
                   {
                      Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
                      if (p->name() == "ACTION")
                         mov.accion = p->value().charAt(0);
                      else if (p->name() == "NUM")
                         mov.cortinaNumber = p->value().toInt();
                   }
                }
                colaMovimientos.enqueue(mov);
             });
   //server.onNotFound(handleNotFound);

   // These two callbacks are required for gen1 and gen3 compatibility
   server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
                        {
                           if (fauxmo.process(request->client(), request->method() == HTTP_GET, request->url(), String((char *)data)))
                              return;
                           // Handle any other body request here...
                        });
   server.onNotFound([](AsyncWebServerRequest *request)
                     {
                        String body = (request->hasParam("body", true)) ? request->getParam("body", true)->value() : String();
                        if (fauxmo.process(request->client(), request->method() == HTTP_GET, request->url(), body))
                           return;
                        // Handle not found request here...
                     });

   // Start the server
   server.begin();


   fauxmo.createServer(false);
   // Set fauxmoESP to not create an internal TCP server and redirect requests to the server on the defined port
  // The TCP port must be 80 for gen3 devices (default is 1901)
  // This has to be done before the call to enable()
  fauxmo.createServer(false);
  fauxmo.setPort(80); // This is required for gen3 devices

  // You have to call enable(true) once you have a WiFi connection
  // You can enable or disable the library at any moment
  // Disabling it will prevent the devices from being discovered and switched
  fauxmo.enable(true);

  // You can use different ways to invoke alexa to modify the devices state:
  // "Alexa, turn kitchen on" ("kitchen" is the name of the first device below)
  // "Alexa, turn on kitchen"
  // "Alexa, set kitchen to fifty" (50 means 50% of brightness)

// Add virtual devices
  fauxmo.addDevice("Cortina1");
  fauxmo.addDevice("Cortina2");
  fauxmo.addDevice("Cortina3");
  fauxmo.addDevice("Cortina4");
  fauxmo.addDevice("Cortina5"); 
  fauxmo.addDevice("Cortina6");
  fauxmo.addDevice("Cortina7");
  fauxmo.addDevice("Cortina8");
  fauxmo.addDevice("Cortina9");



  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {

    // Callback when a command from Alexa is received.
    // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
    // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
    // Just remember not to delay too much here, this is a callback, exit as soon as possible.
    // If you have to do something more involved here set a flag and process it in your main loop.

    // if (0 == device_id) digitalWrite(RELAY1_PIN, state);
    // if (1 == device_id) digitalWrite(RELAY2_PIN, state);
    // if (2 == device_id) analogWrite(LED1_PIN, value);

    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

    movimiento_t mov;
   
   if (state)
      mov.accion = 'U';
   else
      mov.accion = 'D';

   if (device_name == "Cortina1")
      mov.cortinaNumber = 1;
   else if (device_name == "Cortina2")
      mov.cortinaNumber = 2;
   else if (device_name == "Cortina3")
      mov.cortinaNumber = 3;
   else if (device_name == "Cortina4")
      mov.cortinaNumber = 4;
   else if (device_name == "Cortina5")
      mov.cortinaNumber = 8;
   else if (device_name == "Cortina6")
      mov.cortinaNumber = 5;
   else if (device_name == "Cortina7")
      mov.cortinaNumber = 6;
   else if (device_name == "Cortina8")
      mov.cortinaNumber = 7;      
   else if (device_name == "Cortina9")
      mov.cortinaNumber = 9;
   
   colaMovimientos.enqueue(mov);

  });
}

