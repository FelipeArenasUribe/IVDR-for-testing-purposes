#include <SPI.h>
#include <mcp2515.h>
MCP2515 mcp2515(10);

const uint8_t modoOper = 1; //Modo de Operacion del IVDR

/*
   Modo 1= Sniffer, lee todo lo del CAN
   Modo 2= Lee algunos ID de CAN
   Modo 3= PIDs OBD2 + Algunos ID de CAN (Se usa la int pit)
   Modo 4= Solo PIDs OBD2 (Se usa la int pit)
*/

//Declaracion de mensajes CAN
struct can_frame canMsg; //Mensaje de lectura
struct can_frame canMsg1; //Mensaje de escritura

struct Mensaje {
  uint8_t t_stamp[4];
  uint8_t id[2];
  uint8_t bytes[8];
};

union Mensaje_Serial {
  Mensaje como_mensaje;
  uint8_t como_bytes[sizeof(Mensaje)];
};

#define BUFFER_LENGTH 20 //Dimension del Buffer
volatile Mensaje_Serial buffer_Serial[BUFFER_LENGTH];

//Variables y creacion del Buffer
uint8_t k = 0; //Puntero Buffer print
uint8_t j = 0; //Puntero Buffer mensaje
volatile uint8_t i = 0; //Puntero Buffer read
uint8_t p = 0; //Puntero t_stamp
uint8_t s = 0; //Iterador lectura mensaje

//Variables del PIT de escritura de PIDs
volatile uint8_t c = 0; //Contador Timer2 de escritura
const uint8_t PIDS[] = {0x0B, 0x0A, 0x0C, 0x0D}; //PIDs a transmitir por el CAN
volatile uint8_t iPID = 0; //Iterador de PIDs

//Variables del PIT para el Timestamp
//volatile unsigned long mseg=0; //Contador Timestamp
volatile unsigned long t_stamp; //Timestamp

//Variables para filtro de IDs de CAN
const uint16_t CANIDs[] = {0x111, 0x2D1, 0xA03, 0x0BA}; //IDs que se buscan leer
uint8_t iID = 0; //Iterador de IDs

void Sync();
void MsgSetup();
void CAN2BUFF();

void setup() {
  Serial.begin(115200); //Iniciar puerto serial

  Sync(); //Sincronizar Arduino y PC para comunicacion serial

  //Iniciar Modulo MCP2515
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  MsgSetup(); //Crear mensaje PIDs

  //Crear PIT para Timestamp
  /*
    noInterrupts();
    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 250;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= 0b00000011; //62500 ---> 110
    TIMSK1 |= 1 << OCIE1A;
    interrupts();
  */
  
  pinMode(0, INPUT_PULLUP);
  switch (modoOper) {
    case 1:
      attachInterrupt(digitalPinToInterrupt(2), Sniffer, FALLING);
      break;
    case 2:
      attachInterrupt(digitalPinToInterrupt(2), IDCAN, FALLING);
      break;
    case 3:
      attachInterrupt(digitalPinToInterrupt(2), IDCANOBD2, FALLING);
      noInterrupts();
      TCNT2 = 0;
      TIMSK2 |= 1 << TOIE2;
      TCCR2B = 0b00000111;
      interrupts();
      break;
    case 4:
      attachInterrupt(digitalPinToInterrupt(2), OBD2, FALLING);
      noInterrupts();
      TCNT2 = 0;
      TIMSK2 |= 1 << TOIE2;
      TCCR2B = 0b00000111;
      interrupts();
      break;
  }
}

void loop() {
  if (j == i) {
    return;
  }
  j++;
  j = j % BUFFER_LENGTH;
  for (k = 0; k < sizeof(Mensaje_Serial); k++) {
    Serial.write(buffer_Serial[j].como_bytes[k]);
  }
}

ISR(TIMER2_OVF_vect) {
  //Se ejecuta cada 33ms
  canMsg1.data[2] = PIDS[iPID];
  mcp2515.sendMessage(&canMsg1);
  iPID++;
  iPID = iPID % sizeof(PIDS);
}

/*
  ISR(TIMER1_COMPA_vect) {
  mseg++;
  }
*/

void Sniffer() {
  cli();
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    CAN2BUFF();
  }
  sei();
}

void IDCAN() {
  cli();
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {

    //temp = canMsg.can_id XOR CANIDs[0]
    // si .can_id==CANID temp=0000

    for (iID = 0; iID < sizeof(CANIDs) / sizeof(uint16_t); iID++) {
      if (canMsg.can_id == CANIDs[iID]) {
        CAN2BUFF();
      }
    }
  }
  sei();
}

void IDCANOBD2() {
  cli();
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x7E8 || canMsg.can_id == 0x3DF) {
      CAN2BUFF();
    }
  }
  sei();
}

void OBD2() {
  cli();
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x7E8) {
      CAN2BUFF();
    }
  }
  sei();
}

void MsgSetup() {
  canMsg1.can_id  = 0x7DF;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x02;
  canMsg1.data[1] = 0x01;
  canMsg1.data[2] = PIDS[0];
  canMsg1.data[3] = 0x00;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0x00;
  canMsg1.data[6] = 0x00;
  canMsg1.data[7] = 0x00;
}

void CAN2BUFF() {
  // Vuelta de puntero i
  i++;
  i = i % BUFFER_LENGTH;
  t_stamp = millis();
  //t_stamp = mseg;
  for (p = 0; p < sizeof(unsigned long); p++) {
    buffer_Serial[i].como_mensaje.t_stamp[p] = (t_stamp >> (8 * (sizeof(unsigned long) - p - 1))) & 0xFF;
  }
  buffer_Serial[i].como_mensaje.id[0] = (canMsg.can_id & 0xFF00) >> 8;
  buffer_Serial[i].como_mensaje.id[1] = canMsg.can_id & 0xFF;
  for (s = 0; s < 8; s++) {
    buffer_Serial[i].como_mensaje.bytes[s] = canMsg.data[s];
  }
}

void Sync() {
  uint8_t sync_byte;
  byte sync;
  size_t bytes_read;
  Serial.setTimeout(1000);
  while (true) {
    sync_byte = (millis() & 0x7F);
    Serial.write(sync_byte);
    Serial.flush();
    bytes_read = Serial.readBytes(&sync, 1);
    if (bytes_read == 1 && sync == sync_byte) {
      break;
    }
  }
  Serial.write(0xFF);
  Serial.flush();
}
