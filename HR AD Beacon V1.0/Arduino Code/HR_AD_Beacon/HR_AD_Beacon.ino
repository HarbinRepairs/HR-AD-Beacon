//THIS SOFTWARE IS PROVIDED BY HARBIN REPAIRS AS-IS WITH ABSOULTEY NO WARRANTY AND NO SUPPORT

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DBG_OUTPUT_PORT Serial
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

const byte DNS_PORT = 53;
                  //Max 31 characters for SSID
                  //*******************************//
const char *ssid = "Your Business Here 123-456-7890";
int clientcount = 0;
int clientcountold = 0;
int displaywake = 0;
int minutetimer = 0;

const unsigned char clockicon [] = {
0x1C, 0x2A, 0x49, 0x4D, 0x41, 0x22, 0x1C, 0x00, 
};

const unsigned char viewicon [] = {
0x1F, 0x80, 0x26, 0x40, 0x49, 0x20, 0x89, 0x10, 0x46, 0x20, 0x20, 0x40, 0x1F, 0x80, 0x00, 0x00
};

const unsigned char Logo [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78,
0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66,
0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0xDE, 0x0F, 0x87, 0xE0, 0x7C, 0x7C, 0x3B, 0xCA,
0xFF, 0x1F, 0xC7, 0xF1, 0xFC, 0xFE, 0x3F, 0xEA, 0xE7, 0x38, 0xC0, 0x71, 0xC5, 0xE7, 0x3C, 0xE0,
0xC7, 0x38, 0xC0, 0x33, 0x81, 0xC7, 0x38, 0xE0, 0xC3, 0x3F, 0xC7, 0xF3, 0x81, 0xC3, 0x38, 0xE0,
0xC7, 0x38, 0x0E, 0x33, 0x81, 0xC3, 0x38, 0xE0, 0xC7, 0x38, 0x0E, 0x33, 0x81, 0xC7, 0x38, 0xE0,
0xFF, 0x1F, 0xCF, 0xF1, 0xFC, 0xFF, 0x38, 0xE0, 0xDC, 0x07, 0x87, 0xB0, 0x78, 0x3C, 0x38, 0xE0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

WiFiEventHandler stationConnectedHandler;
WiFiEventHandler probeRequestPrintHandler;


IPAddress apIP(192, 168, 1, 1);

DNSServer dnsServer;

ESP8266WebServer webServer(80);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.drawBitmap(0, 0, Logo, 64, 48, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.setCursor(16,5);
  display.println("HR|AD");
  display.setCursor(0,30);
  display.println("   v1.0");
  display.setCursor(0,40);
  display.println("");
  display.display();
  delay(4000);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  display.println("Configuring access point...");
  display.display();

  Serial.print("Configuring access point...");
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid);

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  //start debug port
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.print("\n");
  DBG_OUTPUT_PORT.setDebugOutput(true);
  SPIFFS.begin();

  //redirect all traffic to index.html
  webServer.onNotFound([]() {
    if(!handleFileRead(webServer.uri())){
      const char *metaRefreshStr = "<head><meta http-equiv=\"refresh\" content=\"0; url=http://192.168.1.1/index.html\" /></head><body><p>redirecting...</p></body>";
      webServer.send(200, "text/html", metaRefreshStr);
    }
  });
  
  webServer.begin();
  
  Serial.print("AP IP address: ");
  Serial.println(apIP);
  Serial.println("HTTP server started");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Beacon");
  display.println("Name:");
  display.println("");
  display.println(ssid);
  display.display();
  delay(8000);
  


  stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
  probeRequestPrintHandler = WiFi.onSoftAPModeProbeRequestReceived(&onProbeRequestPrint);

}

void onStationConnected(const WiFiEventSoftAPModeStationConnected& evt) {
  Serial.println("New Client Connected");
  clientcount = (clientcount + 1);
  Serial.println("Total Clients: ");
  Serial.println(clientcount);
  
}

void onProbeRequestPrint(const WiFiEventSoftAPModeProbeRequestReceived& evt) {
}

void loop() {

if (minutetimer < millis()){
  minutetimer = (millis()+ 60000);
  displaywake = (millis()+ 5000);
}

//check to see if a client has connected
  dnsServer.processNextRequest();
  webServer.handleClient();
  if (millis() > 5000 && probeRequestPrintHandler) {
    probeRequestPrintHandler = WiFiEventHandler(); 
}

//check to see if a client has connected
if (clientcount > clientcountold){
  displaywake = (millis()+5000); //this will wake the screen for 5 seconds
  display.clearDisplay();
  display.drawRect(0, 0, 64, 21, WHITE);
  display.drawRect(0, 26, 64, 21, WHITE);
  display.drawBitmap(9, 28, clockicon, 8, 8, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(10, 2, viewicon, 16, 8, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.setCursor(12,2);
  display.print("  Views");
  display.setCursor(2,12);
  display.println(clientcount);
  display.setCursor(7,28);
  display.print("  Uptime");
  display.setCursor(2,38);
  display.print(millis() / 60000);
  display.println("Min");
  display.display();
}
if (millis() < displaywake){
  display.ssd1306_command(SSD1306_DISPLAYON);
  display.clearDisplay();
  display.drawRect(0, 0, 64, 21, WHITE);
  display.drawRect(0, 26, 64, 21, WHITE);
  display.drawBitmap(9, 28, clockicon, 8, 8, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(10, 2, viewicon, 16, 8, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.setCursor(12,2);
  display.print("  Views");
  display.setCursor(2,12);
  display.println(clientcount);
  display.setCursor(7,28);
  display.print("  Uptime");
  display.setCursor(2,38);
  display.print(millis() / 60000);
  display.println("Min");
  display.display();
}
else {
    display.ssd1306_command(SSD1306_DISPLAYOFF);

}
clientcountold = clientcount; //previous client count until value goes up

}

String getContentType(String filename){
  if(webServer.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

//Given a file path, look for it in the SPIFFS file storage. Returns true if found, returns false if not found.
bool handleFileRead(String path){
  DBG_OUTPUT_PORT.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.html";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
    if(SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = webServer.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}
