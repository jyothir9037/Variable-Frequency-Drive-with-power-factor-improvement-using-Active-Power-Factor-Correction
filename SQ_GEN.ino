#define PHASE_A 2
#define PHASE_B 3
#define PHASE_C 4
#define MODE 5

int T_ON;

void setup() {
  T_ON = 1000;

  Serial.begin(9600);
  
  pinMode(PHASE_A,OUTPUT);
  pinMode(PHASE_B,OUTPUT);
  pinMode(PHASE_C,OUTPUT);
  pinMode(MODE,INPUT);
}

void loop() {
  while(Serial.available()){
    T_ON = Serial.parseInt();
  }
  //  if(MODE == HIGH){
  //  normal();
//  }else{
  //  plug();
  //}
  normal();
  Serial.println("T_ON : "); 
  Serial.print(T_ON);
}

void normal(){
  digitalWrite(PHASE_A,HIGH);
  delay(T_ON);

  digitalWrite(PHASE_C,LOW);
  delay(T_ON);
    
  digitalWrite(PHASE_B,HIGH);
  delay(T_ON);
  
  digitalWrite(PHASE_A,LOW); 
  delay(T_ON);
  
  digitalWrite(PHASE_C,HIGH); 
  delay(T_ON);
  
  digitalWrite(PHASE_B,LOW); 
  delay(T_ON);
}

void plug(){
  digitalWrite(PHASE_A,HIGH);
  delay(T_ON);
  
  digitalWrite(PHASE_C,LOW);
  delay(T_ON);
  
  digitalWrite(PHASE_B,HIGH);
  delay(T_ON);
  
  digitalWrite(PHASE_A,LOW); 
  delay(T_ON);
  
  digitalWrite(PHASE_C,HIGH); 
  delay(T_ON);
  
  digitalWrite(PHASE_B,LOW); 
  delay(T_ON);
}

/*
char mystr[5] = "Hello"; //String data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
}

void loop() {
  Serial.write(mystr,5); //Write the serial data
  delay(1000);
}

//receiver

char mystr[10]; //Initialized variable to store recieved data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
}

void loop() {
  Serial.readBytes(mystr,5); //Read the serial data and store in var
  Serial.println(mystr); //Print data on Serial Monitor
  delay(1000);
}
*/
