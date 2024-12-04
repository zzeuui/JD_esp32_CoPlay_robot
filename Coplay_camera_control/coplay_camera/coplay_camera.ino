#include "esp_camera.h"

#include "network_utils.h"
#define CAMERA_MODEL_ESP_EYE
#include "camera_utils.h"

const char *websockets_server_host = "cobot.center";
const uint16_t websockets_server_port = 8286;
const char *control_url = "/pang/ws/pub?channel=cmmvr9epjh64ovedk470&track=colink&mode=bundle";
const char *camera_url = "/pang/ws/pub?channel=cmmvr9epjh64ovedk470&track=video";


WebsocketsClient client_control;
WebsocketsClient client_camera;

void setup() {
  Serial.begin(115200);

  setupWiFi();
   
  client_control.onMessage(onMessageControl);
  client_control.onEvent(onEventsControl);

  client_camera.onMessage(onMessageCamera);
  client_camera.onEvent(onEventsCamera);
  
  while (!client_control.connect(websockets_server_host, websockets_server_port, control_url))
  {
    delay(500);
    Serial.print(";");
  }

  Serial.println("Control Websocket Connected.");
  delay(500);

  while (!client_camera.connect(websockets_server_host, websockets_server_port, camera_url))
  {
    delay(500);
    Serial.print("?");
  }

  Serial.println("Camera Websocket Connected.");
  delay(500);

  setupCamera();
}

void loop() {
  client_control.poll();
  client_camera.poll();

  camera_fb_t *fb = esp_camera_fb_get(); // get a camera frame

  if(!fb) {
      Serial.println("Camera capture failed");
      esp_camera_fb_return(fb);
      return;
  }
  
  // send frame to server
  client_camera.sendBinary((const char*) fb-> buf, fb-> len);
  esp_camera_fb_return(fb);

}