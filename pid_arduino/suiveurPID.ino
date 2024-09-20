
int inrf=5;
int inrb=6;

int inlf=10;
int inlb=11;

int s1,s2,s3,s4,s5,s6;

float error,lastError,P,I,D;

int leftspeed,rightspeed,u;
float kp=0.5,kd=0,ki;
int basespeed=100;
n=0;

void setup() {
  pinMode(inrf,OUTPUT);
  pinMode(inrb,OUTPUT);
  pinMode(inlf,OUTPUT);
  pinMode(inlb,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
}

void loop() {
  float current_time=millis();
  s1=digitalRead(A0);
  s2=digitalRead(A1);
  s3=digitalRead(A2);
  s4=digitalRead(A3);
  s5=digitalRead(A4);
  s6=digitalRead(A5);

  if (n==0 && s6==1 && s5==1  && current_time>1000){
    right();
    delay(200);
    last_time=current_time;
    n=1;
  }
  else if ( n==1 && s6==1 && s5==1&& &&current_time -last_time>500){

    right();
    delay(200);

    n=2
  }



  

  else {
    PID();
  frowardPID();
  }
  


}
void PID(){
  error=40*s1+20*s2+10*s3-10*s4-20*s5-40*s6;
  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  u=kp*P+kd*D+ki*I;

  leftspeed=basespeed+u;
  rightspeed=basespeed-u;

  leftspeed=min(255,max(0,leftspeed));
  rightspeed=min(255,max(0,rightspeed));
}
void forwardPID(){
  analogWrite(inrf,rightspeed);
  analogWrite(inlf,leftspeed);
  analogWrite(inrb,0);
  analogWrite(inlb,0);
}












void forward(){
  analogWrite(inrf,100);
  analogWrite(inlf,100);
   analogWrite(inrb,0);
  analogWrite(inlb,0);
}
void back(){
  analogWrite(inrf,0);
  analogWrite(inlf,0);
   analogWrite(inrb,100);
  analogWrite(inlb,100);
}
void right(){
  analogWrite(inrf,100);
  analogWrite(inlf,0);
   analogWrite(inrb,0);
  analogWrite(inlb,0);
}
void left(){
  analogWrite(inrf,0);
  analogWrite(inlf,100);
   analogWrite(inrb,0);
  analogWrite(inlb,0);
}
