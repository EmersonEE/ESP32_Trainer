#include <Arduino.h>
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/telegram-esp32-motion-detection-arduino/

  Project created using Brian Lough's Universal Telegram Bot Library: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>

const char *ssid = "CLARO_h9hU3j";
const char *password = "7474FB19FD";

// Initialize Telegram BOT
#define BOTtoken "7728354592:AAG5Egb_-28yP30dIJIA9-9RbW4onO_v4tY" // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "1527971462"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int motionSensor = 27; // PIR Motion Sensor
bool motionDetected = false;
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
const int ledPin = 26;
const int pinBuzzer = 12;
bool pinBuzzerState = LOW;
bool ledState = LOW;
// Indicates when motion is detected

void handleNewMessages(int numNewMessages)
{
    Serial.println("handleNewMessages");
    Serial.println(String(numNewMessages));

    for (int i = 0; i < numNewMessages; i++)
    {
        // Chat id of the requester
        String chat_id = String(bot.messages[i].chat_id);
        if (chat_id != CHAT_ID)
        {
            bot.sendMessage(chat_id, "Unauthorized user", "");
            continue;
        }

        // Print the received message
        String text = bot.messages[i].text;
        Serial.println(text);

        String from_name = bot.messages[i].from_name;

        if (text == "/start")
        {
            String welcome = "Welcome, " + from_name + ".\n";
            welcome += "Use the following commands to control your outputs.\n\n";
            welcome += "/led_on to turn GPIO ON \n";
            welcome += "/led_off to turn GPIO OFF \n";
            welcome += "/state to request current GPIO state \n";
            bot.sendMessage(chat_id, welcome, "");
        }

        if (text == "/led_on")
        {
            bot.sendMessage(chat_id, "LED state set to ON", "");
            ledState = HIGH;
            digitalWrite(ledPin, ledState);
        }

        if (text == "/led_off")
        {
            bot.sendMessage(chat_id, "LED state set to OFF", "");
            ledState = LOW;
            digitalWrite(ledPin, ledState);
        }

        if (text == "/state")
        {
            if (digitalRead(ledPin))
            {
                bot.sendMessage(chat_id, "LED is ON", "");
            }
            else
            {
                bot.sendMessage(chat_id, "LED is OFF", "");
            }
        }
    }
}

void IRAM_ATTR detectsMovement()
{
    // Serial.println("MOTION DETECTED!!!");
    motionDetected = true;
}

void setup()
{
    Serial.begin(115200);

    // PIR Motion Sensor mode INPUT_PULLUP
    pinMode(motionSensor, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    pinMode(pinBuzzer, OUTPUT);
    digitalWrite(ledPin, ledState);
    digitalWrite(pinBuzzer, pinBuzzerState);

    // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
    attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

    // Attempt to connect to Wifi network:
    Serial.print("Connecting Wifi: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop()
{
    if (motionDetected)
    {
        bot.sendMessage(CHAT_ID, "Motion detected!!", "");
        Serial.println("Motion Detected");
        motionDetected = false;
        digitalWrite(pinBuzzer, HIGH);
    }
    if (millis() > lastTimeBotRan + botRequestDelay)
    {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while (numNewMessages)
        {
            Serial.println("got response");
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        lastTimeBotRan = millis();
    }
}