#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>
const int rs = D0, en = D1, d4 = D4, d5 = D5, d6 = D6, d7 = D7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char *ssid = "Viraj Gholap"; // Enter your WiFi Name
const char *pass = "12345678"; // Enter your WiFi Password/ Enter your WiFi Password

WiFiServer server(80);

double air_quality;
void setup() {
Serial.begin(115200);
lcd.begin(16, 2);
delay(10);
Serial.println("Connecting to ");
lcd.print("Connecting.... ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(550);
Serial.print(".");
lcd.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());
server.begin();
}

void loop() {
delay(500);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Pollution=");
air_quality = ((analogRead(A0)/1024.0)*100.0);
lcd.print(air_quality);
lcd.print("%");
// Serial.println(air_quality);

//// put your main code here, to run repeatedly:

WiFiClient client = server.available();
if ( client.connected()) { // loop while the client's connected
// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println("Refresh: 3"); // update the page after 4 sec
client.println();

// turns the GPIOs on and off
lcd.setCursor(0,1);
lcd.print("Sending Data" );

// Display the HTML web page
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");

// Web Page Heading
client.println("<body><h1 style=\"color:orange;\"> Air Quality Measurement </h1>");

client.println("<body><p style=\"color:blue;\"> Pollution Content(in percentage) = " + String(air_quality) +" %"+ " </p>");
if(air_quality <= 20.0 ){
client.println("<body><p style=\"color:green;\"> Normal </p>");
} else if (air_quality > 20.0 && air_quality < 70.0){
client.println("<body><p style=\"color:purple;\"> Medium </p>");
} else {
client.println("<body><p style=\"font-size:200%; color:red\"> Danger!!! </p>");
}

client.println("</body></html>");
delay(1000);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Pollution=");
lcd.print(air_quality);
lcd.print("%");
}
}

