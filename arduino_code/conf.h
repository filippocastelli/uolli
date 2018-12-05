//motors
#define L1pin  22    
#define L2pin  23    
#define speed_lpin 2    // Deve essere PWM-enabled
#define R1pin  24    
#define R2pin  25 
#define speed_rpin 3    // Deve essere PWM-enabled

//servo
#define servopin 4

//ultrasonic
#define echopin 11 // Ultrasonic Echo pin connect to D11
#define trigpin 10  // Ultrasonic Trig pin connect to D12

//ir sensors
#define IRsensor0pin 28
#define IRsensor1pin 29
#define IRsensor2pin 30
#define IRsensor3pin 31
#define IRsensor4pin 32

// buzzer
#define buzzpin 6 //pwm


// IR RECEIVER
#define IRreceiverpin 5

#define IR_AVANTI       0x00FF18E7     
#define IR_INDIETRO     0x00FF4AB5     
#define IR_DX           0x00FF5AA5       
#define IR_SX           0x00FF10EF      
#define IR_STOP          0x00FF38C7      
#define IR_turnsmallleft 0x00FFB04F  

#define autodrive_speed 200
#define linefollow_speed 200

int dist_sx, dist_sxdiag, dist_rx, dist_rxdiag, dist_avanti;
int distancelimit = 15; //distance limit for obstacles in front           
int sidedistancelimit = 15; //minimum distance in cm to obstacles at both sides (the car will allow a shorter distance sideways)
int tempo_svolta = 700; //time the car spends turning (miliseconds)
int distance;
int robaadiritto;
int ncicli = 0;

int sensori_ir[5];


#define MAX_PACKETSIZE 32    //Serial receive buffer
char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;



enum SG
{
  GUIDA_MANUALE,
  LINE_FOLLOW,
  ULTRASONIC,
  IRMODE
}stato_guida=GUIDA_MANUALE;

enum AZIONI
{ 
  AVANTI, 
  SINISTRA, 
  DESTRA,
  INDIETRO,
  FERMA,
  DEF
}azione=DEF;



bool stopFlag = true;
bool RunningFlag = false;
uint16_t RunningTimeCnt = 0;
uint32_t RunningTime=0;

char inByte[1];

unsigned long tempo;
