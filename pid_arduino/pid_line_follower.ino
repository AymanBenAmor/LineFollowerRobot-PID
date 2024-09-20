
// Moteur 1
int av_m1 = 9;
int re_m1 = 8;
int basespeedm1 = 130 ;
int maxspeedm1 = 255;

// Moteur 2
int av_m2 = 11;
int re_m2 = 10;
int basespeedm2 = 121;
int maxspeedm2 = 255;

//les capteurs 
int cp1 = A0;
int cp2 = A1;
int cp3 = A2;
int cp4 = A3;
int cp5 = A4;
int cp6 = A5;
int cp7 = 2;
int cp8 = 3;


int values[8] = {-100,-50,-25,-10,10,25,50,100};
int sensors[8];

float kp = 1.9;
float kd =1 ;
float ki = 0.05;


int P,D;
int I = 0;
int n=0;

int lasterror = 0;


void setup() {
  pinMode(av_m1, OUTPUT);
  pinMode(re_m1, OUTPUT);
  pinMode(av_m2, OUTPUT);
  pinMode(re_m2, OUTPUT);

  pinMode(cp1, INPUT);
  pinMode(cp2, INPUT);
  pinMode(cp3, INPUT);
  pinMode(cp4, INPUT);
  pinMode(cp5, INPUT);
  pinMode(cp6, INPUT);
  pinMode(cp7, INPUT);
  pinMode(cp8, INPUT);

  Serial.begin(9600);
 
}


void left(int posa, int posb) {
  //set the appropriate values for aphase and bphase so that the robot goes straight
  analogWrite(av_m1, posb);
  digitalWrite(av_m2, 0);
  digitalWrite(re_m1, 0);
  analogWrite(re_m2, posa);
}
void right(int posa, int posb) {
  //set the appropriate values for aphase and bphase so that the robot goes straight
  analogWrite(av_m2, posb);
  digitalWrite(av_m1, LOW);
  digitalWrite(re_m2, LOW);
  analogWrite(re_m1, posa);
}


void forward_brake(int posa, int posb) {
  //set the appropriate values for aphase and bphase so that the robot goes straight
  digitalWrite(re_m1, LOW);
  digitalWrite(re_m2, LOW);
  analogWrite(av_m1, posa);
  analogWrite(av_m2, posb);
}


int lasttime=0;

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
