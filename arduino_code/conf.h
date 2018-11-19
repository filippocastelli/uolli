#define L1pin  2    
#define L2pin  4    
#define speed_lpin 6    // Deve essere PWM-enabled

#define R1pin  7    
#define R2pin  8  
#define speed_rpin 5    // Deve essere PWM-enabled

#define servopin 9

#define echopin 11 // Ultrasonic Echo pin connect to D11
#define trigpin 12  // Ultrasonic Trig pin connect to D12

#define IRsensor0pin  3
#define IRsensor1pin A1
#define IRsensor2pin A2
#define IRsensor3pin A3
#define IRsensor4pin 10

#define buzzpin 13


#define autodrive_speed 200


int ncicli = 0;

int dist_sx, dist_sxdiag, dist_rx, dist_rxdiag, dist_avanti;
int distancelimit = 27; //distance limit for obstacles in front           
int sidedistancelimit = 12; //minimum distance in cm to obstacles at both sides (the car will allow a shorter distance sideways)
int tempo_svolta = 700; //time the car spends turning (miliseconds)
int distance;
int robaadiritto;
