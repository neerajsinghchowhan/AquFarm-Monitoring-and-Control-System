#include <WiFiClientSecure.h>
#include <DHT.h>
#define dhpin 33
#define dhtype DHT11
DHT dht(dhpin,dhtype);


const int buzzer=27;
const int waterin=14;
const int waterout=22;
const int turbine=23;
float h=0;
float t=0;
float wl=0;
float ph=0;
float od=0;
char wi='0';
char wo='0';
char tur='0';
char buz='0';
char phi='0';

String api=String();
const char* ssid     = "Galaxy A5185DB";     // your network SSID (name of wifi network)
const char* password = "1234567890"; // your network password

const char*  server = "aquasystem.000webhostapp.com";  // Server URL

// www.howsmyssl.com root certificate authority, to verify the server
// change it to your server root CA
// SHA1 fingerprint is broken now!

const char* test_root_ca= \
     "-----BEGIN CERTIFICATE-----\n" \
      "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n" \
      "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n" \
      "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n" \
      "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n" \
      "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n" \
      "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n" \
      "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n" \
      "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n" \
      "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n" \
      "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n" \
      "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n" \
      "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n" \
      "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n" \
      "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n" \
      "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n" \
      "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n" \
      "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n" \
      "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n" \
      "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n" \
      "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n" \
      "-----END CERTIFICATE-----";










WiFiClientSecure client;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(waterin, OUTPUT);
  pinMode(waterout, OUTPUT);
  pinMode(turbine, OUTPUT);

  pinMode (35 , INPUT);
  pinMode (25 , INPUT);
  digitalWrite(buzzer,HIGH);
  digitalWrite(waterin,HIGH);
  digitalWrite(waterout, HIGH);
  digitalWrite(turbine,HIGH);
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  dht.begin();
  delay(100);
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);

  
  //client.setCertificate(test_client_key); // for client verification
  //client.setPrivateKey(test_client_cert);  // for client verification

  
}

void loop() {
  // do nothing

  char a[17];
  
  int i=0,j;

  
  api+="";
  
  if(h==0 && t==0 && wl==0 && ph==0 && od==0){
  delay(100);
  float h=hum();
  float t=te() ;
  float wl=waterlevel();
  float ph=phsensor();
  float od=dosensor();
  float tbd=turbd();
  
  Serial.println(h);
  Serial.println(t); 
  Serial.println(wl);
  Serial.println(ph);
  Serial.println(od);
  Serial.println(tbd);

  
  api+="&temp=";
  api+=String(t);
  api+="&hum=";
  api+=String(h);
  api+="&ph=";
  api+=String(ph);
  api+="&wl=";
  api+=String(wl);
  api+="&od=";
  api+=String(od);

  }
  client.setCACert(test_root_ca);
  
  Serial.println("\nStarting connection to server...");
  if (!client.connect(server, 443))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    
    client.println("GET https://aquasystem.000webhostapp.com/test.php?"+api+" HTTP/1.0");
    client.println("Host: aquasystem.000webhostapp.com");
    client.println("Connection: close");
    client.println();
    
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      a[i]=c;
      i=i+1;
      Serial.write(c);
    }

    client.stop();  

  
    if(a[3]=='1'){

      


 if(wl<=20){
        
          if(wi=='0'){
            
            Serial.println("Water in motor on");
            digitalWrite(waterin, LOW);
            wi='1';
            }

          
          }else if(wl>=90){
            
            
            if(wo=='0'){
                Serial.println("Water out motor on");
                digitalWrite(waterout, LOW);
                wo='1';
              
              }
            }else{

            if(wi=='1'){
              Serial.println("Water in motor off");
              digitalWrite(waterin, HIGH);
              wi='0';
              
              }
             if(wo=='1'){
              
              Serial.println("Water out motor off");
              digitalWrite(waterout, HIGH);
              wo='0';
              }        
           }

            

         if(od<=6 || t>=40){

            ///turb on
            if(tur=='0'){
             
            Serial.println("turbine on");
             digitalWrite(turbine, LOW);
             tur='1';
              }
          
          }else{

            if(tur=='1'){
              Serial.println("turbine off");
              digitalWrite(turbine, HIGH);
              tur='0';
              
              }
            
        
            }

        


         if(ph<=5){
          phi='1';
          }else{
           phi='0'; 
            }

         if((phi=='1') || (wi=='1') || (wo=='1') || (tur=='1') ){

          if(buz=='0'){
            Serial.println("buzzer on");
            digitalWrite(buzzer, LOW);
            buz='1';
            }
          
          }else{
            if(buz=='1'){

              Serial.println("buzzer off");
              digitalWrite(buzzer,HIGH);
              buz='0';
              
              }
            
          
            }
          


     
      ////
      
      }else{
              
        
                if(a[7]=='0'){

                  if(wi=='1'){       
                    Serial.println("Water in motor off");
                    digitalWrite(waterin, HIGH);
                    wi='0';
                  
                  }
            
                    
                  }else{

                      if(wi=='0'){
                      Serial.println("Water in motor on");
                      digitalWrite(waterin, LOW);
                      wi='1';
                      Serial.print("----------");
                      Serial.println(wi);
                    
                    }
                    
                    
                  }
        
                 if(a[11]=='0'){

                  if(wo=='1'){       
                    Serial.println("Water out motor off");
                    digitalWrite(waterout, HIGH);
                    wo='0';
                    
                  
                  }
        
                    
                  }else{

                      if(wo=='0'){
                      Serial.println("Water out motor on");
                      digitalWrite(waterout, LOW);
                      wo='1';
                    
                    }
                    
                    
                  }

                  if(a[15]=='0'){

                  if(tur=='1'){       
                    Serial.println("turbine off");
                    digitalWrite(turbine, HIGH);
                    tur='0';
                                     
                  }  
                  }else{

                      if(tur=='0'){
                      Serial.println("turbine on");
                      digitalWrite(turbine, LOW);
                      tur='1';
                    
                    }
                    
                    
               }


                 
               if((a[3]=='1') ||( a[7]=='1') || (a[11]=='1') || (a[15]=='1')){
                
                if(buz=='0'){
                  Serial.println("buzzer on");
                  digitalWrite(buzzer, LOW);
                  buz='1';
                  }
              
                }else{
                    if(buz=='1'){
                      Serial.println("buzzer off");
                      digitalWrite(buzzer,HIGH);
                      buz='0';
                      
                      }
                    
                    
                    }    
      }
  }









  
}


float phsensor(){
    int j=analogRead(32);
    Serial.println("PH:");
    j=map(j,0,4095,14,0);
    Serial.println(j);
    return j;
  }

float dosensor(){
    int j=analogRead(34);
    Serial.println("DO:");
    j=map(j,0,4095,10,0);
    Serial.println(j);
    return j;
  }

float te(){
    float t=dht.readTemperature();
    Serial.println("temp:");
    Serial.println(t);
    return t;
  }

float hum(){
    float h=dht.readHumidity();
    Serial.println("humidity:");
    Serial.println(h);
    return h;
  }
 float waterlevel(){
    int k=analogRead(35);
    int p=0;
    Serial.println("Waterlevel"); 
    if(k>=1400){
      p=90;
      Serial.println("high"); 
      }else if(k>=800 && k<1400){
        Serial.println("normal"); 
        p=50;
        }else{
          p=20;
          Serial.println("Low"); 
        } 
    return p;
  }

float turbd(){
    
    int ans=0;
    int k=analogRead(25);
    
    int l=map(k,0,3101,100,0);
    ans=l;
    if(l<0){
      ans=0;
      }
    
    Serial.println("Turbidity");
    Serial.println(k);
    Serial.println(ans);
    Serial.println("-----------");
    return ans;
  
  
  }
