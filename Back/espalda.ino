
const int ledizq = 12; 
const int ledder = 11; 
const int stateizq = LOW; 
const int stateder = LOW; 
char c;
String string = "";
void setup() {
  Serial.begin(9600);
  pinMode(ledizq, OUTPUT);
  pinMode(ledder, OUTPUT);
}


void loop() {
    c = Serial.read();
      if(c == '/n'){
        if(string = "010"){
          digitalWrite(ledizq, HIGH);
        }
        else if(string = "001"){
          digitalWrite(ledder, HIGH);
        }
         else {
          digitalWrite(ledizq, LOW);
          digitalWrite(ledder, LOW);
        }
        string == "";
      }
         else{
            string+=c;
          }
      
      
}

