// LoRa 9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (transmitter)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example LoRa9x_RX

#include <SPI.h>
#include <RH_RF95.h>
#include <PinChangeInterrupt.h>

// broches du module LoRa
#define RFM95_CS 6
#define RFM95_RST 5
#define RFM95_INT 2
// Change to 868.0 or other frequency, must match RX's freq!
#define RF95_FREQ 868.0       // fréq. autorisée en France

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// LEDs de contrôle 
#define LED_Tx 13   // ON pendant la transmission   : LED bleue
//#define LED_OK 9    // fixe si OK                   : LED verte
#define button 14   // bouton connecté en A0 et déclenchant une interruption

bool etatButton=false; // indique l'état du bouton "button"
volatile bool demEmission=false; // flag de demande d'émission

bool RF95_OK = false ;  // état du module
const byte TxPw = 5;     // puissance d'émission (de 5 à 23, 13 par défaut)
// tableau de "lenpac" caractères envoyés
const byte lenpac = 22;   // longueur du paquet
char radiopacket[lenpac] = "Bonjour le Monde !   ";
byte cptpac = 0;          // compteur de paquets envoyés
char comptage[11]="0123456789"; // caractère à insérer dans le message
bool etatLED_OK=false;                // donne l'état de la LED_OK : 0=éteinte, 1=allumée, 2=clignotante
bool etatLED_Tx=false;            // donne l'état de la LED_Tx : 0=éteinte, 1=allumée, 2=clignotante


// =============== INITIALISATION ==============
void setup()
{
  sleepMode(SLEEP_POWER_DOWN);
  //pinMode(LED_OK, OUTPUT); digitalWrite(LED_OK, LOW);
  pinMode(LED_Tx, OUTPUT); digitalWrite(LED_Tx, LOW);
  pinMode(RFM95_RST, OUTPUT);
  pinMode(button, INPUT_PULLUP);   // bouton de déclenchement
  // on déclenche le programme "emission" par appui(FALLING) du bouton "button"
  attachPCINT(digitalPinToPCINT(button), demande, FALLING);
  //attachInterrupt(0, demande, LOW);  // interruption 0 broche 2
  
  init_RF95();
}
// ================ FONCTIONS ===================
// initialisation
void init_RF95()
{
// Initialisation du module de communication
  //digitalWrite(LED_OK,LOW);        // LED d'état du module 
  digitalWrite(RFM95_RST, HIGH);
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(1);
  digitalWrite(RFM95_RST, HIGH);
  delay(1);

  while (!rf95.init())
  {
  //    LoRa radio init failed
    while (1);
  }
  if (!rf95.setFrequency(RF95_FREQ))
  {
  //    setFrequency failed
    while (1);
  }
//  LoRa radio init OK!
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
    RF95_OK = true ;              // état du module OK
    //digitalWrite(LED_OK,HIGH);;   // Module OK :LED ON 

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(TxPw, false);
}
// -------------------------------------------------
// fonction de réception
void reception()
{
  if (RF95_OK)
  {
    // Now wait for a reply
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    //  Waiting for reply...
    if (rf95.waitAvailableTimeout(1000))
    { 
      // Should be a reply message for us now   
      if (rf95.recv(buf, &len))
      {
        // Tout est OK - mise en sommeil du module LoRa
        while (!rf95.sleep())
        {
          //    LoRa radio sleep failed
          while (1);
        }
        //digitalWrite(LED_OK,LOW);
      }
      else
      {
      //  Receive failed
        RF95_OK = false ;
      }
    }
    else
    {
    //  No reply, is there a listener around?
      digitalWrite(LED_Tx,LOW);
    }
  }
}
// -------------------------------------------------

// ============ PROGRAMMES PRINCIPAUX ============
// gestion de l'interruption
void demande(){
  demEmission=true;
}
//------------------------------------------------
// fonction d'emission déclenchée par l'appui du bouton "button"
void emission()
{
  //digitalWrite(LED_OK,HIGH);
  if (RF95_OK)
  {
    digitalWrite(LED_Tx, HIGH);
    radiopacket[19]=comptage[cptpac];  // indicateur du n° de paquet
    // Send a message to rf95_server
    rf95.send((uint8_t *)radiopacket, lenpac);
    //  Waiting for packet to complete...
    rf95.waitPacketSent();
  }
  //digitalWrite(LED_OK,LOW);
}
// -------------------------------------------------
void loop()
{
	delay(20);
  while (!digitalRead(button))
  {
    emission();
    delay(100);
  }
  sleep();
}

