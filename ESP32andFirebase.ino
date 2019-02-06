#include "WiFi.h"
#include "HTTPClient.h"

/*
 * JSON
 * https://howtofirebase.com/firebase-data-modeling-939585ade7f4
 */
const char* ssid = "*********";
const char* password = "******";


void setup() {
 Serial.begin(115200);
 delay(4000);
 WiFi.begin(ssid,password);

 while(WiFi.status() != WL_CONNECTED){
  delay(1000);
  Serial.println("Connecting to WiFi...");
 }
 Serial.println("Connected to the WiFi network");
 
}

int i =0;
void loop() {
  
   if((WiFi.status() == WL_CONNECTED)){

     if(i==0){
        getData();
        patchData();
        i=1;
     }
 
   }

}
  

/*
 * The URL from Firebase
 * "https://<DATABASE_NAME>.firebaseio.com/Name-of-your-Nodo.json?auth=Key-From-your-Database"
 * Name-of-Nodo: The name of the child to get the data.
 * Example:
 * "https://name-8ccrf.firebaseio.com/temperatura.json?auth=lcv31ytuYWoGTJMQ1uQLsN0Jxx2H7EQBmQ8yyMiEBV
*/

void getData(){
      String url = "https://<DATABASE_NAME>.firebaseio.com/Name-of-your-Nodo.json?auth=Key-From-your-Database"
      HTTPClient http;
      http.begin(url);
      int httpCode = http.GET();
      if(httpCode > 0){
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }else{
        Serial.println("Error on HTTP request");
      }
    
      http.end();  
}


/*
 * POST create a new child with a new id. 
 * Change the url 
 */
void postData(){
  String url = "https://<DATABASE_NAME>.firebaseio.com/Name-of-your-Nodo/.json?auth=Key-From-your-Database"
  //Json to saved data.
  char JSONMessage[] = "{\"name\":\"23\"}";
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type",""text/plain");
  int httpResponseCode = http.POST(JSONMessage);
  if(httpResponseCode > 0){
    String response = http.getString();

    Serial.println(httpResponseCode);
    Serial.println(response);
  }else{
    Serial.print("Error on sending POST:");
    Serial.println(httpResponseCode);
  }
  http.end();
}

/*
 * PUT update the data. 
 * Change the url 
 * Let time after saved info. 
 */
void patchData(){
  String url = "https://<DATABASE_NAME>.firebaseio.com/Name-of-your-Nodo/.json?auth=Key-From-your-Database"
  //Json to saved data.
  char JSONMessage[] = "{\"Cen\":\"22\"}";
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "text/plain");
  int httpResponseCode = http.PUT(JSONMessage);
  if(httpResponseCode > 0){
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  }else{
    Serial.print("Error on sending PUT:");
    Serial.println(httpResponseCode);
  }

  http.end();
  delay(500);
}


