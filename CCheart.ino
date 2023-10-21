#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 


#define piLOplus_LAamarillo 32 //LO+  
#define piLOmin_RArojo 33  //LO-  
#define paOutput 34  //LO- 
unsigned char dLOplus_LAamarillo;
unsigned char dLOmin_RArojo;
int dOutput = 0;

#define tresholdSinyal 3000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "Ecg";
const char* password = "123456789";

  // Inicializar la comunicación HTTP
HTTPClient http;



void setup()

{

  
if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.display();
  



  Serial.begin(115200);
  pinMode(piLOplus_LAamarillo, INPUT_PULLUP);
  pinMode(piLOmin_RArojo, INPUT_PULLUP);

  
  // Conectar a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red...");
  }
  Serial.println("Conexión exitosa!");
  

  String url = "http://192.168.94.146:8000/api/lecturas"; // Reemplaza con la URL de tu API
  
  // Configurar el encabezado para indicar que es un POST
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
 
  
  // Verificar la respuesta
 /* if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.println("Error en la solicitud");
  }
*/
  // Cerrar la conexión
//  http.end();

  mi_moving_ave_clear();
}


int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1   ; //1000Hz
float BPM = 0;
int mavBPM = 0;
int error = 0;
int msBPM;

int flagBPM = 0;
void loop()
{

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    dLOmin_RArojo = digitalRead(piLOmin_RArojo);
    dLOplus_LAamarillo = digitalRead(piLOplus_LAamarillo);
    dOutput = analogRead(paOutput);

   
    if (dLOmin_RArojo == HIGH || dLOplus_LAamarillo == HIGH) {
      msBPM = 0;
    }


    
    else {


      if (dOutput > tresholdSinyal && flagBPM == 0) {

        flagBPM = 1;


        if (msBPM > 525)
        {
          BPM = 60000.0 / msBPM;
          mavBPM = mi_moving_average(BPM, 0);
          mavBPM -= error;
          Serial.print(BPM); Serial.print(" ");
          Serial.println(mavBPM);
        }



        msBPM = 0;

      }
      else if (dOutput < tresholdSinyal) {
        flagBPM = 0;
        msBPM++;
      }
    }
  }
   display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 10);
  display.println("BPM:");
  display.println(BPM);
  display.display();
  
 String postData = "{\"lectura\":"+String(BPM)+"}"; // Reemplaza con el dato real que quieras enviar
  // Enviar la solicitud POST
  int httpCode = http.POST(postData);

}

void datosPrint() {
  //Serial.print(dLOplus);    Serial.print("+");
  //Serial.print(dLOmin);  Serial.print("-");
  Serial.print(dOutput);
  Serial.println();
}




void datosLOPrint() {
  Serial.print(dLOplus_LAamarillo);    Serial.print("LA");
  Serial.print(dLOmin_RArojo);  Serial.print("RA");
  Serial.println();
}

void datosSignalPrint() {
  Serial.print(dOutput);
  Serial.println();
}



//--------------------------------#mi AVERAGE
#define n_mi_datos 5
float mi_datos[n_mi_datos];
int i_mi_datos = 0;

float mi_moving_average(float in_datos, int debug)
{
  float mi_ave;
  float mi_sum;

  mi_datos[i_mi_datos] = in_datos;

  if (mi_datos[n_mi_datos - 1] == 0)
  {
    mi_sum = 0;

    for (int i = 0; i <= i_mi_datos; i++)
    {
      mi_sum += mi_datos[i];
    }
    mi_ave = mi_sum / (i_mi_datos + 1);
  }
  else
  {
    mi_sum = 0;
    for (int i = 0; i < n_mi_datos; i++)
    {
      mi_sum += mi_datos[i];
    }
    mi_ave = mi_sum / n_mi_datos;
  }


  //#Debug
  if (debug)
  {
    for (int i = 0; i < n_mi_datos; i++)
    {
      Serial.print(i); Serial.print(" "); Serial.println(mi_datos[i]);
    }
    Serial.print("i"); Serial.print(" "); Serial.println(i_mi_datos);
    Serial.print("Last"); Serial.print(" "); Serial.println(mi_datos[n_mi_datos - 1]);

    Serial.print("Sum"); Serial.print(" "); Serial.println(mi_sum);
    Serial.print("Ave"); Serial.print(" "); Serial.println(mi_ave);
    Serial.println();
  }



  i_mi_datos++;
  if (i_mi_datos >= n_mi_datos)
    i_mi_datos = 0;

  return mi_ave;
}

void mi_moving_ave_clear()
{
  //Make sure All Array is 0
  for (int i = 0; i < n_mi_datos; i++)
  {
    mi_datos[i] = 0;
  }
}
