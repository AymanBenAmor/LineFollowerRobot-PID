
//moteur 1
int av_m1 = 22;
int re_m1 = 23;
int vitt_1 = 21;
int basespeedm1 = 180 ;
int maxspeedm1 = 255;

// Moteur 2
int av_m2 = 19;
int re_m2 = 18;
int vitt_2 = 5;
int basespeedm2 = 180;
int maxspeedm2 = 255;

const int freq = 30000;
const int pwmChannel_1 = 0;
const int pwmChannel_2 = 1;
const int resolution = 8;

//les capteurs 
int cp1 = 34;
int cp2 = 35;
int cp3 = 32;
int cp4 = 33;
int cp5 = 25;
int cp6 = 26;
int cp7 = 27;
int cp8 = 14;


int values[8] = {-100,-50,-25,-10,10,25,50,100};
int sensors[8];

float kp = 1.9;
float ki = 0.05;
float kd =1 ;

int P,D;
int I = 0;


int lasterror = 0;



void setup() {
  // put your setup code here, to run once:
  pinMode(av_m1, OUTPUT);
  pinMode(re_m1, OUTPUT);
  pinMode(vitt_1, OUTPUT);
  
  pinMode(av_m2, OUTPUT);
  pinMode(re_m2, OUTPUT);
  pinMode(vitt_2, OUTPUT);
  
  ledcSetup(pwmChannel_1, freq, resolution);
  ledcSetup(pwmChannel_2, freq, resolution);
  ledcAttachPin(vitt_1, pwmChannel_1);
  ledcAttachPin(vitt_2, pwmChannel_2);
  
  pinMode(cp1, INPUT);
  pinMode(cp2, INPUT);
  pinMode(cp3, INPUT);
  pinMode(cp4, INPUT);
  pinMode(cp5, INPUT);
  pinMode(cp6, INPUT);
  pinMode(cp7, INPUT);
  pinMode(cp8, INPUT);
Serial.begin(115200);
}

void right(int posa, int posb) {
  //set the appropriate values for aphase and bphase so that the robot goes straight
  digitalWrite(re_m1, HIGH);
  digitalWrite(av_m1, LOW);
  ledcWrite(pwmChannel_1,posa);

  digitalWrite(re_m2, LOW);
  digitalWrite(av_m2, HIGH);
  ledcWrite(pwmChannel_2,posb);
}
void left(int posa, int posb) {
  //set the appropriate values for aphase and bphase so that the robot goes straight
  digitalWrite(re_m1, LOW);
  digitalWrite(av_m1, HIGH);
  ledcWrite(pwmChannel_1,posa);

  digitalWrite(re_m2, HIGH);
  digitalWrite(av_m2, LOW);
  ledcWrite(pwmChannel_2,posb);
}


void forward_brake(int posa, int posb) {
  //set the appropriate values for aphase and bphase so that the robot goes straight
  digitalWrite(re_m1, LOW);
  digitalWrite(av_m1, HIGH);
  ledcWrite(pwmChannel_1,posa);

  digitalWrite(re_m2, LOW);
  digitalWrite(av_m2, HIGH);
  ledcWrite(pwmChannel_2,posb);
}

void back(int posa, int posb) {
  //set the appropriate values for aphase and bphase so that the robot goes straight
  digitalWrite(re_m1, HIGH);
  digitalWrite(av_m1, LOW);
  ledcWrite(pwmChannel_1,posa);

  digitalWrite(re_m2, HIGH);
  digitalWrite(av_m2, LOW);
  ledcWrite(pwmChannel_2,posb);
}

int lasttime =0;


void loop() {
  
  int currenttime=millis();

  int somme = 0;
  int error = 0;
  
  sensors[0] = digitalRead(cp1);
  sensors[1] = digitalRead(cp2);
  sensors[2] = digitalRead(cp3);
  sensors[3] = digitalRead(cp4);
  sensors[4] = digitalRead(cp5);
  sensors[5] = digitalRead(cp6);
  sensors[6] = digitalRead(cp7);
  sensors[7] = digitalRead(cp8);
  




  for (int i=0 ; i<8 ; i++){
    error += sensors[i]*values[i];
    somme += sensors[i];
  }


    
 
  P = error;
  
  D = error - lasterror;
  lasterror = error;

  int motorspeed = P*kp + D*kd ;

  int speedm1 = basespeedm1 - motorspeed;
  int speedm2 = basespeedm2 + motorspeed;
  
  if (speedm1 > maxspeedm1) {
    speedm1 = maxspeedm1;
  }
  if (speedm1 < 0) {
    speedm1 = 0;
  }
  if (speedm2 > maxspeedm2) {
    speedm2 = maxspeedm2;
  }
  if (speedm2 < 0) {
    speedm2 = 0;
  }

  forward_brake(speedm1 , speedm2);
  

  
}