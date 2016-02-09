#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 177);
//IPAddress myDns(192, 168, 0, 1);

char server[] = "www.arduino.cc";
//IPAddress server(64,131,82,241);

EthernetClient client;

unsigned long lastConnectionTime = 0;             
const unsigned long postingInterval = 10L * 1000L; 

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  delay(1000);
  //Ethernet.begin(mac, ip, myDns);
  Ethernet.begin(mac, ip);

  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }
}

void httpRequest() {
  client.stop();

  if (client.connect(server, 80)) {
    Serial.println("connecting...");

    client.println("GET /latest.txt HTTP/1.1");
    client.println("Host: www.arduino.cc");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    lastConnectionTime = millis();
  } else { Serial.println("connection failed"); }
}
