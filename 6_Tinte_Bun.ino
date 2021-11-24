// pornire/oprire releu 1/2/3/4/5/6 de pe serverul http://192.168.1.1

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// alocare iesiri GPIO, iesiri relee
int releu1 = 13;
int releu2 = 12;
int releu3 = 14;
int releu4 = 16;
int releu5 = 2;
int releu6 = 5;


bool PowerReleu1  = true;
bool PowerReleu2  = true;
bool PowerReleu3  = true;
bool PowerReleu4  = true;
bool PowerReleu5  = true;
bool PowerReleu6  = true;

long timerreleu1 = -1;
long timerreleu2 = -1;
long timerreleu3 = -1;
long timerreleu4 = -1;
long timerreleu5 = -1;
long timerreleu6 = -1;


const char* host = "pornire/oprire tinte";

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer server(80);

void setup() {
	pinMode(releu1 , OUTPUT);
	digitalWrite(releu1 , PowerReleu1);
	pinMode(releu2 , OUTPUT);
	digitalWrite(releu2 , PowerReleu2);
	pinMode(releu3 , OUTPUT);
	digitalWrite(releu3 , PowerReleu3);
	pinMode(releu4 , OUTPUT);
	digitalWrite(releu4 , PowerReleu4);
	pinMode(releu5 , OUTPUT);
	digitalWrite(releu5 , PowerReleu5);
	pinMode(releu6 , OUTPUT);
	digitalWrite(releu6 , PowerReleu6);

  
	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
	WiFi.softAP("Server tinte");

	// modify TTL associated  with the domain name (in seconds)
	// default is 60 seconds
	dnsServer.setTTL(300);
	// set which return code will be used for all other domains (e.g. sending
	// ServerFailure instead of NonExistentDomain will reduce number of queries
	// sent by clients)
	// default is DNSReplyCode::NonExistentDomain
	dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

	// start DNS server for a specific domain name
	dnsServer.start(DNS_PORT, "www.example.com", apIP);
	MDNS.begin(host);
	server.on ( "/", HTTP_handleRoot );
	server.onNotFound ( HTTP_handleRoot );
	server.begin();

}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}


void HTTP_handleRoot(void) {
  bool statreleu1 = false;
  bool statreleu2 = false;
  bool statreleu3 = false;
  bool statreleu4 = false;
  bool statreleu5 = false;
  bool statreleu6 = false;
  
// Releul 1
  if( server.hasArg("statreleu1") ){
     if( strncmp(server.arg("statreleu1").c_str(),"1",1) == 0 )
     statreleu1 = true;
  }
  else {
     statreleu1 = PowerReleu1;
  }

// Releul 2
  if( server.hasArg("statreleu2") ){
     if( strncmp(server.arg("statreleu2").c_str(),"1",1) == 0 )
     statreleu2 = true;
  }
  else {
     statreleu2 = PowerReleu2;
  }
  
// Releul 3
    if( server.hasArg("statreleu3") ){
     if( strncmp(server.arg("statreleu3").c_str(),"1",1) == 0 )
     statreleu3 = true;
  }
  else {
     statreleu3 = PowerReleu3;
  }

// Releu 4
 if( server.hasArg("statreleu4") ){
     if( strncmp(server.arg("statreleu4").c_str(),"1",1) == 0 )
     statreleu4 = true;
  }
  else {
     statreleu4 = PowerReleu4;
  }

//Releu 5
 if( server.hasArg("statreleu5") ){
     if( strncmp(server.arg("statreleu5").c_str(),"1",1) == 0 )
     statreleu5 = true;
  }
  else {
     statreleu5 = PowerReleu5;
  }

//Releu 6

 if( server.hasArg("statreleu6") ){
     if( strncmp(server.arg("statreleu6").c_str(),"1",1) == 0 )
     statreleu6 = true;
  }
  else {
     statreleu6 = PowerReleu6;
  }

// Creare pagină HTML
  String out = "";

  out =
"<html>\
  <head>\
    <meta charset=\"utf-8\" />\
    <title>Pornire tinte</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; font-size: 35px; }\
    </style>\
    <meta http-equiv=\"refresh\" content=\"5;URL=\'http://192.168.1.1/\'\"/>\
  </head>\
  <body>\
";

// Releul 1
  
  if( statreleu1 ){
      out+="\
    <hr width=100 size=100 align=left color=red><h2><a href=\"/?statreleu1=0\" >PORNIRE TINTA 1</a></h2>\
    ";
  }
  else {
      out+="\
    <hr width=100 size=100 align=center color=green><h2><a href=\"/?statreleu1=1\">OPRIRE TINTA 1</a></h2>\
    ";            
  }

  // Releul 2
  if( statreleu2 ){
      out+="\
    <hr width=100 size=100 align=left color=red><h2><a href=\"/?statreleu2=0\">PORNIRE TINTA 2</a></h2>\
    ";
  }
  else {
      out+="\
    <hr width=100 size=100 align=center color=green><h2><a href=\"/?statreleu2=1\">OPRIRE TINTA 2</a></h2>\
    ";            
  }

    // Releul 3
  if( statreleu3 ){
      out+="\
    <hr width=100 size=100 align=left color=red><h2><a href=\"/?statreleu3=0\">PORNIRE TINTA 3</a></h2>\
    ";
  }
  else {
      out+="\
    <hr width=100 size=100 align=center color=green><h2><a href=\"/?statreleu3=1\">OPRIRE TINTA 3</a></h2>\
    ";            
  }

  // Releu 4
    if( statreleu4 ){
      out+="\
    <hr width=100 size=100 align=left color=red><h2><a href=\"/?statreleu4=0\">PORNIRE TINTA 4</a></h2>\
    ";
  }
  else {
      out+="\
    <hr width=100 size=100 align=center color=green><h2><a href=\"/?statreleu4=1\">OPRIRE TINTA 4</a></h2>\
    ";            
  }

  // Releu 5
   if( statreleu5 ){
      out+="\
    <hr width=100 size=100 align=left color=red><h2><a href=\"/?statreleu5=0\">PORNIRE TINTA 5</a></h2>\
    ";
  }
  else {
      out+="\
    <hr width=100 size=100 align=center color=green><h2><a href=\"/?statreleu5=1\">OPRIRE TINTA 5</a></h2>\
    ";            
  }

  // Releu 6
  
  if( statreleu6 ){
      out+="\
    <hr width=100 size=100 align=left color=red><h2><a href=\"/?statreleu6=0\">PORNIRE TINTA 6</a></h2>\
    ";
  }
  else {
      out+="\
    <hr width=100 size=100 align=center color=green><h2><a href=\"/?statreleu6=1\">OPRIRE TINTA 6</a></h2>\
    ";            
  }

   
   // Global ????
   out+= "\
  </body>\
</html>";
   server.send ( 200, "text/html", out );

      bool a;
      int c=0;
      // Releul 1
   if( statreleu1 != PowerReleu1 ){
      PowerReleu1 = statreleu1;
      if(PowerReleu1==false)
      {
        digitalWrite(releu1 , PowerReleu1);
        timerreleu1=millis() + 30000L;
      }
      else
      {
        digitalWrite(releu1 , PowerReleu1);
        timerreleu1=-1;
      }
  }
  if(timerreleu1!=-1 && timerreleu1<millis())
  {
    PowerReleu1 = true;
    statreleu1=true;
    digitalWrite(releu1 , PowerReleu1);
    timerreleu1=-1;
  }
  
      // Releul 2

      if( statreleu2 != PowerReleu2 ){
      PowerReleu2 = statreleu2;
      if(PowerReleu2==false)
      {
        digitalWrite(releu2 , PowerReleu2);
        timerreleu2=millis() + 30000L;
      }
      else
      {
        digitalWrite(releu2 , PowerReleu2);
        timerreleu2=-1;
      }
  }
  if(timerreleu2!=-1 && timerreleu2<millis())
  {
    PowerReleu2 = true;
    statreleu2 = true;
    digitalWrite(releu2 , PowerReleu2);
    timerreleu2 = -1;
  }

  
      // Releul 3
  if( statreleu3 != PowerReleu3 ){
      PowerReleu3 = statreleu3;
      if(PowerReleu3==false)
      {
        digitalWrite(releu3 , PowerReleu3);
        timerreleu3=millis() + 30000L;
      }
      else
      {
        digitalWrite(releu3 , PowerReleu3);
        timerreleu3=-1;
      }
  }
  if(timerreleu3!=-1 && timerreleu3<millis())
  {
    PowerReleu3 = true;
    statreleu3 = true;
    digitalWrite(releu3 , PowerReleu3);
    timerreleu3=-1;
  }


    // Releu 4

     if( statreleu4 != PowerReleu4 ){
      PowerReleu4 = statreleu4;
      if(PowerReleu4==false)
      {
        digitalWrite(releu4 , PowerReleu4);
        timerreleu4=millis() + 30000L;
      }
      else
      {
        digitalWrite(releu4 , PowerReleu4);
        timerreleu4=-1;
      }
  }
  if(timerreleu4!=-1 && timerreleu4<millis())
  {
    PowerReleu4 = true;
    statreleu4 = true;
    digitalWrite(releu4 , PowerReleu4);
    timerreleu4=-1;
  }

  
   //Releu 5
    if( statreleu5 != PowerReleu5 ){
      PowerReleu5 = statreleu5;
      if(PowerReleu5==false)
      {
        digitalWrite(releu5 , PowerReleu5);
        timerreleu5=millis() + 30000L;
      }
      else
      {
        digitalWrite(releu5 , PowerReleu5);
        timerreleu5=-1;
      }
  }
  if(timerreleu5!=-1 && timerreleu5<millis())
  {
    PowerReleu5 = true;
    statreleu5 = true;
    digitalWrite(releu5 , PowerReleu5);
    timerreleu5=-1;
  }

   //Releu 6
    if( statreleu6 != PowerReleu6 ){
      PowerReleu6 = statreleu6;
      if(PowerReleu6==false)
      {
        digitalWrite(releu6 , PowerReleu6);
        timerreleu6=millis() + 30000L;
      }
      else
      {
        digitalWrite(releu6 , PowerReleu6);
        timerreleu6=-1;
      }
  }
  if(timerreleu6!=-1 && timerreleu6<millis())
  {
    PowerReleu6 = true;
    statreleu6 = true;
    digitalWrite(releu6 , PowerReleu6);
    timerreleu6=-1;
  }
}
  

     
