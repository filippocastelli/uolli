/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid     = "Uolli_WiFi";
const char* password = "ulbabrab";


IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);


// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
String drive_status = "";


// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

void setup() {
  Serial.begin(9600);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  //WiFi.begin(ssid, password);
  WiFi.softAPConfig(local_IP, gateway,subnet);
  WiFi.softAP(ssid);

  // Print local IP address and start web server
  //Serial.println("");
  //Serial.println("WiFi connected.");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.softAPIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    //Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /stop") >= 0) {
              drive_status = "stop";
              Serial.println(5);
            }
            if (header.indexOf("GET /manual") >= 0){
              drive_status = "manual";
            }

            if (header.indexOf("GET /avanti") >= 0){
              Serial.println(2);
            }
            else if (header.indexOf("GET /indietro") >= 0){
              Serial.println(8);
            }
            else if (header.indexOf("GET /sx") >= 0){
              Serial.println(4);
            }
            else if (header.indexOf("GET /dx") >= 0){
              Serial.println(6);
            }

            if (header.indexOf("GET /auto") >= 0) {
              Serial.println(3);
              drive_status = "auto";
            }
            else if (header.indexOf("GET /line") >=0){
              Serial.println(1);
              drive_status = "line";
            }
            else if (header.indexOf("GET /ir") >=0){
              Serial.println(7);
              drive_status = "ir";
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 10px 20px;");
            client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Uolli</h1>");
            
            client.println("<p>mod. corrente " + drive_status + "</p>");
            client.println("<p><a href=\"/auto\"><button class=\"button\">AUTO</button></a>");
            client.println("<a href=\"/manual\"><button class=\"button\">MANUALE</button></a>");
            client.println("<a href=\"/line\"><button class=\"button\">LINE</button></a>");
            client.println("<a href=\"/ir\"><button class=\"button\">IR</button></a>");
            client.println("<a href=\"/stop\"><button class=\"button\">STOP</button></a></p>");

            if (drive_status=="manual") {
              client.println("<p><a href=\"/avanti\"><button class=\"button\">AVANTI</button></a></p>");
              client.println("<p><a href=\"/sx\"><button class=\"button\">SX</button></a>");
              client.println("<a href=\"/dx\"><button class=\"button\">DX</button></a></p>");
              client.println("<p><a href=\"/indietro\"><button class=\"button\">INDIETRO</button></a></p>");
            }

            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    //Serial.println("Client disconnected.");
    Serial.println("");
  }
}
