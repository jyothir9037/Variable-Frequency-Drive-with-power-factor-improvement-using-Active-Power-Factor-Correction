/*
  AUTHOR  : THE JOULE THEIF
  DATE    : 08:52 - 05-04-2022
  VERSION : v1.00 PHOENIX

  The program measures and corrects power factor of a three phase system.
*/

//Importing necessary libraries
#include <LiquidCrystal.h>
#include <math.h>

//Defining pins for LCD
#define RS 1
#define EN 2
#define D4 3
#define D5 4
#define D6 5
#define D7 6

#define LCD_ROWS 4
#define LCD_COLS 20

//Defining pulse input for different phases
#define PULSE_A 8
#define PULSE_B 9
#define PULSE_C 10

#define v_A A0
#define v_B A1
#define v_C A2
#define i_A A3
#define i_B A4
#define i_C A5

#define MF_V_A 2
#define MF_V_B 2
#define MF_V_C 2

//Declaring runtime variables
float phi_A,phi_B,phi_C;
float pf_A,pf_B,pf_C;
float voltage_A,voltage_B,voltage_C;
float power_A,power_B,power_C;
float req_A,req_B,req_C;
float pulsewidth;

//Initializing the LCD object
LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

void setup() {
  pinMode(v_A,INPUT);
  pinMode(v_B,INPUT);
  pinMode(v_C,INPUT);
  
  pf_A = pf_B = pf_C = 0;
  voltage_A = voltage_B = voltage_C = 0;
  pulsewidth = 0;
  
  lcd.begin(LCD_COLS,LCD_ROWS);
}

void loop() {
  read_voltage();
  //read_pf();
  //print_pf();
  //read_power_active();
  //print_power_active();
  //read_power_reactive();
  //print_power_reactive();
  //correct_pf();
}

void read_voltage(){
  voltage_A = analogRead(v_A);
  voltage_A = (float)(voltage_A * MF_V_A)  ;
  voltage_B = analogRead(v_B);
  voltage_B = voltage_B * MF_V_B ;
  voltage_C = analogRead(v_C);
  voltage_C = voltage_C * MF_V_C ;
}

void read_pf(){
  pulsewidth = pulseIn(PULSE_A,HIGH);
  phi_A = pulsewidth * 3.1415 / 10000 ;
  pf_A = cos(phi_A);

  pulsewidth = pulseIn(PULSE_B,HIGH);
  phi_B = pulsewidth * 3.1415 / 10000;
  pf_B = cos(phi_B);

  pulsewidth = pulseIn(PULSE_C,HIGH);
  phi_C = pulsewidth * 3.1415 / 10000;
  pf_C = cos(phi_C);
}

void read_power_active(){

  //active
  power_A = analogRead(v_A) * analogRead(i_A) * pf_A;
  power_B = analogRead(v_B) * analogRead(i_B) * pf_B;  
  power_C = analogRead(v_C) * analogRead(i_C) * pf_C;
}

void read_power_reactive(){
  //reactive
  power_A = analogRead(v_A) * analogRead(i_A) * sin(phi_A);
  power_B = analogRead(v_B) * analogRead(i_B) * sin(phi_B);  
  power_C = analogRead(v_C) * analogRead(i_C) * sin(phi_C);
}

void correct_pf(){
  req_A = power_A * tan(phi_A);
  req_A = (power_A * tan(phi_A)) /(314.15 * analogRead(v_A) * MF_V_A); 
  req_B = (power_B * tan(phi_B)) /(314.15 * analogRead(v_B) * MF_V_B);
  req_C = (power_C * tan(phi_C)) /(314.15 * analogRead(v_C) * MF_V_C);
}

void print_pf(){
  lcd.setCursor(0,0);
  lcd.print("Power Factor");
  
  lcd.setCursor(0,1);
  lcd.print("Phase A : " + char(pf_A));
  
  lcd.setCursor(0,2);
  lcd.print("Phase B : " + char(pf_B));
  
  lcd.setCursor(0,3);
  lcd.print("Phase C : " + char(pf_C));
}

void print_power_active(){
  lcd.setCursor(0,0);
  lcd.print("Active Power");
  
  lcd.setCursor(0,1);
  lcd.print("Phase A : " + char(power_A));
  
  lcd.setCursor(0,2);
  lcd.print("Phase B : " + char(power_B));
  
  lcd.setCursor(0,3);
  lcd.print("Phase C : " + char(power_C));
}

void print_power_reactive(){
  lcd.setCursor(0,0);
  lcd.print("Reactive Power");
  
  lcd.setCursor(0,1);
  lcd.print("Phase A : " + char(power_A));
  
  lcd.setCursor(0,2);
  lcd.print("Phase B : " + char(power_B));
  
  lcd.setCursor(0,3);
  lcd.print("Phase C : " + char(power_C));
}


/*
i sensor

v sensor

*/
