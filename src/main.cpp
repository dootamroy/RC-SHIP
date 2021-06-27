#include <main.h>

char auth[] = "Nkz3At3HBoYyqArgMtTkKXW3dvfl-I2Q";
char ssid[] = "Dootam Roy";           //WIFI Name
char pass[] = "rocketman123";           //WIFI Password

int speedX = 0 ;
int speedY = 0;

int turn_speedL = 0;
int turn_speedR = 0;

bool flag = false;
bool flagRotate = false;

void moveControl(int x, int y)
{

    if (x >= 500 && x <= 514 && y >= 500 && y <= 514) // mid point.
    {
      digitalWrite(L_1, LOW);
      digitalWrite(L_2 , LOW);
      digitalWrite( R_1, LOW);
      digitalWrite(R_2, LOW);

      turn_speedL = 0;
      turn_speedR = 0;

      Serial.println("Stop");
    }
    else if(flag == false)   //when button off (v3) 
    {
      speedY = map(y, 0, 1024, -1024, 1024);
      //Serial.println(speedY);
      speedX = map(x, 0, 1024, 1024, -1024);
      //Serial.println(speedX);


      //MOTOR CONTROL.
      if (speedY >= 0){
        
        turn_speedL = speedY - speedX;
        turn_speedR = speedY + speedX;

      
        if (turn_speedL < 0)
        {
          if (speedY < 100)
          {
            turn_speedL = 0;
          }
          else
          {
            if (flagRotate == true)
            {
              turn_speedL = -turn_speedL;   // props rotate opposite to each other to revolve around its axis.
            }
            
            //turn_speedL = -turn_speedL;
          }
        
        }
        else if(turn_speedR < 0)
        {
          if (speedY < 100)
          {
            turn_speedR = 0;
          }
          else
          {
            if (flagRotate == true)
            {
              turn_speedR = -turn_speedR;     // props rotate opposite to each other to revolve around its axis.
            }
            
          }
          //turn_speedR = -turn_speedR;
        }
        

        //turn_speedL = map(turn_speedL, 0, 1024, minSpeed, maxSpeed);
        //turn_speedR = map(turn_speedR, 0, 1024, minSpeed, maxSpeed);

        //Serial.print(turn_speedL);
        //Serial.print("       ");
        //Serial.println(turn_speedR);



        //forward.
        analogWrite(L_2,turn_speedL);
        digitalWrite(L_1, LOW);
        analogWrite(R_2,turn_speedR);
        digitalWrite(R_1, LOW);

      }
      else{
        //backward.
        speedY = -speedY;

        turn_speedL = speedY - speedX;
        turn_speedR = speedY + speedX;

      
        if (turn_speedL < 0)
        {
          if (speedY < 100)
          {
            turn_speedL = 0;
          }
          else
          {
            if (flagRotate == true)
            {
              turn_speedL = -turn_speedL;
            }
            
    
          }
        
        }
        else if(turn_speedR < 0)
        {
          if (speedY < 100)
          {
            turn_speedR = 0;
          }
          else
          {
            if (flagRotate == true)
            {
              turn_speedR = -turn_speedR;   // props rotate opposite to each other to revolve around its axis.
            }
            
            
          }
          //turn_speedR = -turn_speedR;
        }
        

        //turn_speedL = map(turn_speedL, 0, 1024, minSpeed, maxSpeed);
        //turn_speedR = map(turn_speedR, 0, 1024, minSpeed, maxSpeed);

        //Serial.print(turn_speedL);
        //Serial.print("       ");
        //Serial.println(turn_speedR);


        analogWrite(L_1, turn_speedR);
        digitalWrite(L_2, LOW);
        analogWrite(R_1,turn_speedL);
        digitalWrite(R_2, LOW);

      }
    
    }

    else              //when button v3 on [rudder assist]
    {
      speedY = map(y, 0, 1024, 400, 1024);


      int rudder_degree = map(x, 0, 1024, 68, 112);     //rudder
      Servo.write(rudder_degree);
      delay(10);

      if (speedY > 500)       //forward thrust
      {
        speedY = map(speedY,500,1024,100,1000);

        analogWrite(L_2,speedY);
        digitalWrite(L_1, LOW);
        analogWrite(R_2,speedY);
        digitalWrite(R_1, LOW);
      }
      else                    //backward thrust
      {
        speedY = map(speedY,0,500,100,1000);
        analogWrite(L_1, speedY);
        digitalWrite(L_2, LOW);
        analogWrite(R_1,speedY);
        digitalWrite(R_2, LOW);
      }
      
      


    }
    
    
        //Blynk.virtualWrite(V2, turn_speedL);
        //Blynk.virtualWrite(V3, turn_speedR);
  
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

    pinMode(L_1, OUTPUT);
    pinMode(L_2 , OUTPUT);
    pinMode(R_1, OUTPUT);
    pinMode(R_2, OUTPUT);
    //pinMode(A0, INPUT);

    digitalWrite(R_2, LOW);
    digitalWrite(R_1 , LOW);
    digitalWrite( L_2, LOW);
    digitalWrite(L_1, LOW);

   Servo.attach(D8); //D8

  Servo.setSpeed(10);

   Servo.write(90);
   delay(20);

}

void loop() {
  Blynk.run();

}

BLYNK_WRITE(V1)   //joystick
{
    int x = param[0].asInt();
    int y = param[1].asInt();

    // Do something with x and y
    Serial.print("X = ");
    Serial.print(x);
    Serial.print("; Y = ");
    Serial.println(y);


  moveControl(x,y);
  
}

BLYNK_WRITE(V2){     //slider rudder

int slider = param.asInt();

slider = map(slider, 0, 1023, 68, 112);

Servo.write(slider);
   delay(10);

}

BLYNK_WRITE(V3){            //rudder assist

int buttonstate = param.asInt();
if (buttonstate == 0)
{
  flag = false;
}
else
{
  flag = true;
}

}

BLYNK_WRITE(V6){             //   [cw/ccw] btn.

int buttonstate = param.asInt();
if (buttonstate == 0)
{
  flagRotate = false;
}
else
{
  flagRotate = true;
}

}

BLYNK_WRITE(V4){     //thrust 1

int slider = param.asInt();

//slider = map(slider, 0, 1023, 68, 112);
analogWrite(L_2,slider);
digitalWrite(L_1, LOW);
//analogWrite(R_2,turn_speedR);
//digitalWrite(R_1, LOW);
}


BLYNK_WRITE(V5){     //thrust 2

int slider = param.asInt();

//slider = map(slider, 0, 1023, 68, 112);
//analogWrite(L_2,slider);
//digitalWrite(L_1, LOW);
analogWrite(R_2,slider);
digitalWrite(R_1, LOW);
}