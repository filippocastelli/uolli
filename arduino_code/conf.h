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
#define echopin 11 //PWM
#define trigpin 10 //PWM

//ir sensors
#define IRsensor4pin 28
#define IRsensor3pin 29
#define IRsensor2pin 30
#define IRsensor1pin 31
#define IRsensor0pin 32

// buzzer
#define buzzpin 6

#define btnpin 33
#define led1pin 34
#define led2pin 35
#define led3pin 36
#define led4pin 37
#define led5pin 38

// IR RECEIVER
#define IRreceiverpin 5

#define IR_AVANTI       0x00FF18E7     
#define IR_INDIETRO     0x00FF4AB5     
#define IR_DX           0x00FF5AA5       
#define IR_SX           0x00FF10EF      
#define IR_STOP          0x00FF38C7      
#define IR_turnsmallleft 0x00FFB04F


#define autodrive_speed 100
#define linefollow_speed 105
#define manual_speed 110

#define manual_time 100

int dist_sx, dist_sxdiag, dist_rx, dist_rxdiag, dist_avanti;
int distancelimit = 15;
int sidedistancelimit = 15;
int tempo_svolta = 250;
int distance;
int robaadiritto;
int ncicli = 0;

int sensori_ir[5];


#define MAX_PACKETSIZE 32    //Serial receive buffer
char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;

#define GUIDA_MANUALE 0
#define LINE_FOLLOW 1
#define ULTRASONIC 2
#define IRMODE 3

int stato_guida = 0;

enum AZIONI
{ 
  AVANTI, 
  SINISTRA, 
  DESTRA,
  INDIETRO,
  FERMA,
  DEF
}azione=DEF;

int mode_leds[4] = {led1pin, led2pin, led3pin, led4pin};

bool stopFlag = true;
bool RunningFlag = false;
uint16_t RunningTimeCnt = 0;
uint32_t RunningTime=0;

char inByte[1];

unsigned long tempo;

//bool bntpressable = true;
unsigned long btntime;

bool invert_ir = false;

bool primae_noctis = true;
