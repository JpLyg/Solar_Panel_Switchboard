#define VoltMeter A0
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;
int relay_reset;

int bcklght=0;

int sw1= 13; //switch for main group
int sw2 = 12; //switch for secondary group
int pb1 = 11; // push button
int aux= 10; // auxilarry

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  //pinMode(relay3, OUTPUT);
  //pinMode(relay4, OUTPUT);

  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(pb1,INPUT);
  pinMode(aux,INPUT);

  relay_group_1_on();
  //relay_group_2_off();
  relay_reset = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(VoltMeter);
  double voltage = map(reading,0,1024,0,2500);
  voltage = voltage/100;
  lcd.setCursor(0,0);
  lcd.print(voltage);
  lcd.print("v");
  lcd.print("   Rst-");
  lcd.print(relay_reset);

  if ((voltage >=13)&& (relay_reset <60)){
    relay_reset+=1;
  }

  if (voltage <13){
    relay_reset = 0;
  }

// 1st relay group
  if (((voltage < 12) || (digitalRead(sw1)== HIGH)) || (digitalRead(aux)== LOW)){
    relay_group_1_on();
  }
  else if ((relay_reset >= 60) ||(digitalRead(pb1)== HIGH)) {
    relay_group_1_off();

  }
// 2nd relay group

/*automated relay 2 setup
  if ((voltage < 13) || (digitalRead(sw2)== HIGH)){
    relay_group_2_on();
  }
  else if ((relay_reset >= 60) || (digitalRead(pb1)== HIGH)) {
    relay_group_2_off();
  }

//basic relay 2 setup
  if ((digitalRead(sw2)== HIGH) && (digitalRead(aux)== HIGH)) {
        relay_group_2_on();
  }
  else {
    relay_group_2_off();
  }
 */

  delay(1000);

  //monitor();

  //Serial.println(digitalRead(relay3));  
  backlight_control();
}

/*void monitor (){

  Serial.print("Switch 1 - ");
  Serial.println(digitalRead(sw1));
  Serial.print("Switch 2 - ");
  Serial.println(digitalRead(sw2));

  Serial.print("Button 1 - ");
  Serial.println(digitalRead(pb1));

  Serial.print("Aux - ");
  Serial.println(digitalRead(aux));
  
}*/

void relay_group_1_on(){

    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    lcd.setCursor(0,1);
    lcd.print("R1-On");

}

void relay_group_1_off(){

    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    lcd.setCursor(0,1);
    lcd.print("R1-OFF");
}
/*
void relay_group_2_on(){

    digitalWrite(relay3, LOW);
    digitalWrite(relay4, LOW);
    lcd.setCursor(9,1);
    lcd.print("R2-On  ");

}

void relay_group_2_off(){

    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
    lcd.setCursor(9,1);
    lcd.print("R2-OFF  ");
}
*/

void backlight_control(){

  // controls turning on/off of the backlight

  if (digitalRead(sw2)== HIGH){
    lcd.backlight();
  }
  else{ 
    lcd.noBacklight();
  }

}

