/*
 A tiny Programm to turn your Arduino with Ethernet Shield and 433Mhz transmitter into an RC-Switcher
 The 433Mhz Communication is handled by the RCSwitch Class 
 */
 #include <aSwitch.h>
 #include <SPI.h>
 #include <Ethernet.h>

 // MAC address from Ethernet shield sticker under board
 byte mac[] = { 0x7A, 0x78, 0xD0, 0x23, 0xD4, 0x76 };
 IPAddress ip(192, 168, 2, 204); // IP address, may need to change depending on network
 EthernetServer server(80);  // create a server at port 80



//Definition of the serveral RC-Switches, including the DIP Switch Positions
aSwitch Plug1(7,1,"11111","00000");
aSwitch Plug2(7,1,"11111","00001");
aSwitch Plug3(7,1,"11111","00011");


//Handles the HTML Request and split it into different Actions
void ProcessRequest(String *req)
{
    //Action example:
    if (req->indexOf("Schalter=1") > -1)            //Command is Switch1, in your browser it looks like: 111.111.111.111/?Schalter=1
    {
        Serial.println("Stecker 1, schalten!");     //Some serial status text
        Plug1.Switch();                             //Call the Plug1 object to change the switch status
    }

    if (req->indexOf("Schalter=2") > -1)
    {
      Serial.println("Stecker 2, schalten!");
      Plug2.Switch();
    }

    if (req->indexOf("Schalter=3") > -1)
    {
      Serial.println("Stecker 3, schalten!");
      Plug3.Switch();
  }

    if (req->indexOf("ALLon") > -1)
    {
      Serial.println("alles an!");
        Plug1.TurnON();
        Plug2.TurnON();
        Plug3.TurnON();
    }

    if (req->indexOf("ALLoff") > -1)
    {
      Serial.println("alles aus!");
        Plug1.TurnOFF();
        Plug2.TurnOFF();
        Plug3.TurnOFF();
    }


}

 void setup()
 {
   Ethernet.begin(mac, ip);  // initialize Ethernet device
   server.begin();           // start to listen for clients
   Serial.begin(9600);       // for diagnostics

   // Turn the RC-Switches into an initial position (all off)
   Plug1.TurnOFF();
   Plug2.TurnOFF();
   Plug3.TurnOFF();
 }

 void loop()
 {
   String HTTP_req;
   EthernetClient client = server.available();  // try to get client

   if (client) {  // got client?
       while (client.connected()) {
           if (client.available()) {   // client data available to read
               char c = client.read(); // read 1 byte (character) from client
               HTTP_req += c;          // save the HTTP request 1 char at a time
               Serial.println(HTTP_req);
               if (c == '\n') {               //the first line of the request ended, so lets proceed
                   // send a standard http response header
                   client.println("HTTP/1.1 200 OK");
                   client.println("Content-Type: text/html");
                   client.println("Connection: close");
                   client.println();
                   // send web page
                   client.println("<!DOCTYPE html>");
                   client.println("<html>");
                   client.println("<head>");
                   client.println("<title>Arduino Herickane Home Control</title>");
                   client.println("</head>");
                   client.println("<body>");
                   client.println("<h1>Wird gemacht....</h1>");
                   //Call the request handler to do some actions
                   ProcessRequest(&HTTP_req);
                   client.println("</body>");
                   client.println("</html>");
                   Serial.print(HTTP_req);
                   HTTP_req = "";    // finished with request, empty string
                   break;
               }
           }
       }
       delay(1);      // give the web browser time to receive the data
       client.stop(); // close the connection
   }

 }
