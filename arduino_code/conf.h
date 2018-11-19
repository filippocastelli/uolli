//motors
#define L1pin  2    
#define L2pin  4    
#define speed_lpin 6    // Deve essere PWM-enabled
#define R1pin  7    
#define R2pin  8  
#define speed_rpin 5    // Deve essere PWM-enabled

//servo
#define servopin 9

//ultrasonic
#define echopin 11 // Ultrasonic Echo pin connect to D11
#define trigpin 12  // Ultrasonic Trig pin connect to D12

//ir sensors
#define IRsensor0pin  3
#define IRsensor1pin A1
#define IRsensor2pin A2
#define IRsensor3pin A3
#define IRsensor4pin 10

// buzzer
#define buzzpin 13



#define autodrive_speed 200
#define linefollow_speed 200

int dist_sx, dist_sxdiag, dist_rx, dist_rxdiag, dist_avanti;
int distancelimit = 27; //distance limit for obstacles in front           
int sidedistancelimit = 12; //minimum distance in cm to obstacles at both sides (the car will allow a shorter distance sideways)
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
  ULTRASONIC
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

