#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"

// Nombre del dispositivo y credenciales BLE
const char *service_name = "MI_CASA_ESP32";
const char *pop = "12345678";

// Nombres personalizados para los dispositivos (focos)
char deviceName_1[] = "Foco Sala";
char deviceName_2[] = "Foco Comedor";
char deviceName_3[] = "Foco Cuarto";

// Pines de salida conectados a los relés
static uint8_t RelayPin1 = 25;
static uint8_t RelayPin2 = 2;
static uint8_t RelayPin3 = 14;

static uint8_t wifiLed = 26;
static uint8_t gpio_reset = 0;

// Estado de los relés (coincide con el estado real del foco)
bool toggleState_1 = LOW; // LOW = apagado
bool toggleState_2 = LOW;
bool toggleState_3 = LOW;

// Definición de los dispositivos en RainMaker
static Switch my_hall_Light(deviceName_1, &RelayPin1);
static Switch my_Kitchen_Light(deviceName_2, &RelayPin2);
static Switch my_bedroom_Light(deviceName_3, &RelayPin3);

// Eventos del sistema para provisión BLE
void sysProvEvent(arduino_event_t *sys_event)
{
  switch (sys_event->event_id)
  {
  case ARDUINO_EVENT_PROV_START:
    Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\"\n", service_name, pop);
    printQR(service_name, pop, "ble");
    break;
  case ARDUINO_EVENT_WIFI_STA_CONNECTED:
    Serial.printf("\nConnected to Wi-Fi!\n");
    digitalWrite(wifiLed, true);
    break;
  }
}

// Callback de escritura (encender/apagar luces desde RainMaker)
void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
  const char *device_name = device->getDeviceName();
  const char *param_name = param->getParamName();

  if (strcmp(param_name, "Power") == 0)
  {
    bool newState = val.val.b;

    if (strcmp(device_name, deviceName_1) == 0)
    {
      toggleState_1 = newState;
      digitalWrite(RelayPin1, toggleState_1);  // Corregido: ahora HIGH enciende el foco
    }
    else if (strcmp(device_name, deviceName_2) == 0)
    {
      toggleState_2 = newState;
      digitalWrite(RelayPin2, toggleState_2);
    }
    else if (strcmp(device_name, deviceName_3) == 0)
    {
      toggleState_3 = newState;
      digitalWrite(RelayPin3, toggleState_3);
    }

    param->updateAndReport(val);
    Serial.printf("Dispositivo: %s -> Estado: %s\n", device_name, newState ? "ENCENDIDO" : "APAGADO");
  }
}

void init_GPIO()
{
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(wifiLed, OUTPUT);
  pinMode(gpio_reset, INPUT);

  // Inicializar relés en estado apagado (LOW)
  digitalWrite(RelayPin1, toggleState_1);
  digitalWrite(RelayPin2, toggleState_2);
  digitalWrite(RelayPin3, toggleState_3);
  digitalWrite(wifiLed, LOW);
}

void init_RainMaker()
{
  uint32_t chipId = 0;
  Node my_node = RMaker.initNode("Rainmaker_Home_Lights");

  my_hall_Light.addCb(write_callback);
  my_Kitchen_Light.addCb(write_callback);
  my_bedroom_Light.addCb(write_callback);

  my_node.addDevice(my_hall_Light);
  my_node.addDevice(my_Kitchen_Light);
  my_node.addDevice(my_bedroom_Light);

  RMaker.enableOTA(OTA_USING_PARAMS);
  RMaker.enableTZService();
  RMaker.enableSchedule();

  for (int i = 0; i < 17; i += 8)
  {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  Serial.printf("\nChip ID: %d | Service Name: %s\n", chipId, service_name);
  RMaker.start();

  WiFi.onEvent(sysProvEvent);

  WiFiProv.beginProvision(NETWORK_PROV_SCHEME_BLE, NETWORK_PROV_SCHEME_HANDLER_FREE_BTDM, NETWORK_PROV_SECURITY_1, pop, service_name);

  // Reportar estado inicial como apagado
  my_hall_Light.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  my_Kitchen_Light.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
  my_bedroom_Light.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Iniciando sistema solo control por voz...");
  init_GPIO();
  init_RainMaker();
}

void loop()
{
  if (digitalRead(gpio_reset) == LOW)
  {
    delay(100);
    int startTime = millis();
    while (digitalRead(gpio_reset) == LOW)
      delay(50);
    int duration = millis() - startTime;

    if (duration > 10000)
    {
      Serial.println("Factory reset...");
      RMakerFactoryReset(2);
    }
    else if (duration > 3000)
    {
      Serial.println("WiFi reset...");
      RMakerWiFiReset(2);
    }
  }

  digitalWrite(wifiLed, WiFi.status() == WL_CONNECTED);
  delay(100);
}