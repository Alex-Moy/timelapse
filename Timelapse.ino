#include <LiquidCrystal.h>
#include <Stepper.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Stepper moteur(48, A0, A1, A2, A3);

const int btvalid = 8;
const int bthaut = 9;
const int btbas = 10;
const int led = 13;

byte heure;
byte minutes;
int angle;

int vitesse;

unsigned long intervale;

byte mode = 1;
int indicedirection;
boolean valid;

int debounce = 300;
int affichage = 60;
unsigned long lasttime = 0;

byte mycaracteredegre[8]={B00100,B01010,B00100,B00000,B00000,B00000,B00000,B00000};

byte mycaractereeaccent[8]={B00010,B00100,B01110,B10001,B11111,B10000,B01110,B00000};

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  moteur.setSpeed(60);

  pinMode(btvalid, INPUT_PULLUP);
   pinMode(bthaut, INPUT_PULLUP);
    pinMode(btbas, INPUT_PULLUP);
     pinMode(led, OUTPUT);

  lcd.createChar(0, mycaracteredegre);
  lcd.createChar(1, mycaractereeaccent);
}

void loop() {
  selectmode();
  if(mode == 1) {modetempsangle(); selectdirection(); affichetempsangle(); validation();}
  if(mode == 2) {modevitesse(); selectdirection(); affichevitesse(); validation();}
  if(mode == 3) {manuel();}
}

void selectmode() //Testé OK
{
  lcd.clear();
    
  lcd.setCursor(0,0);
  lcd.print("Mode:");
  
  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(0,1);
    if(mode == 1) {lcd.print("Temps et angle ");}
    if(mode == 2) {lcd.print("Temps par degre");}
    if(mode == 3) {lcd.print("Manuel         ");}

    if(digitalRead(bthaut) == 0) {
      mode--;
      allumeled();
      delay(debounce);
    }
    if(digitalRead(btbas) == 0) {
      mode++;
      allumeled();
      delay(debounce);
    }

    if(mode < 1) {mode = 3;}
    if(mode > 3) {mode = 1;}

    delay(affichage);
  }
  allumeled();
  delay(debounce);
}

void modetempsangle() //Testé OK
{
  heure = 0;
  minutes = 0;
  angle = 0;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Temps:  Angle :");

  lcd.setCursor(0,1);
  lcd.print(" 00h00m   000");
  lcd.setCursor(13,1);
  lcd.write((byte)0); //Signe °

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(1,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((heure / 10) == 0) {heure = 90;}
      else {heure = heure - 10;}
      lcd.print(heure / 10);
      allumeled();
      lcd.setCursor(1,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((heure / 10) == 9) {heure = 0;}
      else {heure = heure + 10;}
      lcd.print(heure / 10);
      allumeled();
      lcd.setCursor(1,1);
      delay(debounce);
    }
  }
  allumeled();
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(2,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((heure % 10) == 0) {heure = ((heure / 10) * 10) + 9;}
      else {heure = heure - 1;}
      lcd.print(heure % 10);
      allumeled();
      lcd.setCursor(2,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((heure % 10) == 9) {heure = (heure / 10) * 10;}
      else {heure = heure + 1;}
      lcd.print(heure % 10);
      allumeled();
      lcd.setCursor(2,1);
      delay(debounce);
    }
  }
  allumeled();
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(4,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((minutes / 10) == 0) {minutes = 50;}
      else {minutes = minutes - 10;}
      lcd.print(minutes / 10);
      allumeled();
      lcd.setCursor(4,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((minutes / 10) == 5) {minutes = 0;}
      else {minutes = minutes + 10;}
      lcd.print(minutes / 10);
      allumeled();
      lcd.setCursor(4,1);
      delay(debounce);
    }
  }
  allumeled();
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(5,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((minutes % 10) == 0) {minutes = ((minutes / 10) * 10) + 9;}
      else {minutes = minutes - 1;}
      lcd.print(minutes % 10);
      allumeled();
      lcd.setCursor(5,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((minutes % 10) == 9) {minutes = (minutes / 10) * 10;}
      else {minutes = minutes + 1;}
      lcd.print(minutes % 10);
      allumeled();
      lcd.setCursor(5,1);
      delay(debounce);
    }
  }
  allumeled();
  delay(debounce);



  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(10,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((angle / 100) == 0) {angle = 900;}
      else {angle = angle - 100;}
      lcd.print(angle / 100);
      allumeled();
      lcd.setCursor(10,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((angle / 100) == 9) {angle = 0;}
      else {angle = angle + 100;}
      lcd.print(angle / 100);
      allumeled();
      lcd.setCursor(10,1);
      delay(debounce);
    }
  }
  allumeled();
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(11,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if(((angle % 100) / 10) == 0) {angle = ((angle / 100) * 100) + 90;}
      else {angle = angle - 10;}
      lcd.print((angle % 100) / 10);
      allumeled();
      lcd.setCursor(11,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if(((angle % 100) / 10) == 9) {angle = (angle / 100) * 100;}
      else {angle = angle + 10;}
      lcd.print((angle % 100) / 10);
      allumeled();
      lcd.setCursor(11,1);
      delay(debounce);
    }
  }
  allumeled();
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(12,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((angle % 10) == 0) {angle = ((angle / 10) * 10) + 9;}
      else {angle = angle - 1;}
      lcd.print(angle % 10);
      allumeled();
      lcd.setCursor(12,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((angle % 10) == 9) {angle = (angle / 10) * 10;}
      else {angle = angle + 1;}
      lcd.print(angle % 10);
      allumeled();
      lcd.setCursor(12,1);
      delay(debounce);
    }
  }
  allumeled();
  lcd.noBlink();
  delay(debounce);

  intervale = (((heure * 60) + minutes) * 60000) / (angle * 8);
}

void affichetempsangle()
{
  lcd.clear();
  lcd.setCursor(1,0);
  if(heure < 10) {lcd.print("0");}
  lcd.print(heure);
  lcd.print("h");
  if(heure < 10) {lcd.print("0");}
  lcd.print(minutes);
  lcd.print("m");

  lcd.setCursor(11,0);
  if(angle < 10) {lcd.print("0");}
  if(angle < 100) {lcd.print("0");}
  lcd.print(angle);
  lcd.write((byte)0);
}

void modevitesse()
{
  vitesse = 0;
  
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(" Temps par pas: ");
  
  lcd.setCursor(3,1);
  lcd.print("0,00s/pas");
  
  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(3,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((vitesse / 100) == 0) {vitesse = 900;}
      else {vitesse = vitesse - 100;}
      lcd.print(vitesse / 100);
      allumeled();
      lcd.setCursor(3,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((vitesse / 100) == 9) {vitesse = 0;}
      else {vitesse = vitesse + 100;}
      lcd.print(vitesse / 100);
      allumeled();
      lcd.setCursor(3,1);
      delay(debounce);
    }
  }
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(5,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if(((vitesse % 100) / 10) == 0) {vitesse = ((vitesse / 100) * 100) + 90;}
      else {vitesse = vitesse - 10;}
      lcd.print((vitesse % 100) / 10);
      allumeled();
      lcd.setCursor(5,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if(((vitesse % 100) / 10) == 9) {vitesse = (vitesse / 100) * 100;}
      else {vitesse = vitesse + 10;}
      lcd.print((vitesse % 100) / 10);
      allumeled();
      lcd.setCursor(5,1);
      delay(debounce);
    }
  }
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(6,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((vitesse % 10) == 0) {vitesse = ((vitesse / 10) * 10) + 9;}
      else {vitesse = vitesse - 1;}
      lcd.print(vitesse % 10);
      allumeled();
      lcd.setCursor(6,1);
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((vitesse % 10) == 9) {vitesse = (vitesse / 10) * 10;}
      else {vitesse = vitesse + 1;}
      lcd.print(angle % 10);
      allumeled();
      lcd.setCursor(6,1);
      delay(debounce);
    }
  }
  lcd.noBlink();
  delay(debounce);

  intervale = vitesse * 10;
}

void affichevitesse()
{
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print(vitesse / 100);
  lcd.setCursor(4,0);
  lcd.print(",");
  lcd.setCursor(5,0);
  lcd.print(vitesse % 100);
  lcd.setCursor(7,0);
  lcd.print("s/pas");
}

void selectdirection() //Testé OK
{
  indicedirection = -1;
  
  lcd.clear();
    
  lcd.setCursor(0,0);
  lcd.print("Direction:");
  
  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(0,1);
    if(indicedirection == -1) {lcd.print("Vers la gauche");}
    if(indicedirection == 1) {lcd.print("Vers la droite");}

    if(digitalRead(bthaut) == 0) {
      indicedirection = indicedirection + 2;
      allumeled();
      delay(debounce);
    }
    if(digitalRead(btbas) == 0) {
      indicedirection = indicedirection - 2;
      allumeled();
      delay(debounce);
    }
    
    if(indicedirection < -1) {indicedirection = 1;}
    if(indicedirection > 1) {indicedirection = -1;}

    delay(affichage);
  }
  allumeled();
  delay(debounce);
}

void validation()
{
  valid = false;
  lcd.setCursor(2,1);
  lcd.print("Valider?");

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(11,1);
    if(valid == false) {lcd.print("NON");}
    if(valid == true) {lcd.print("OUI");}

    if(digitalRead(bthaut) == 0 || digitalRead(btbas) == 0) {
      //Synthaxe opérateur conditionnel : "Condition?Instruction1:Instruction2"
      valid = (valid == false ? true : false);
      allumeled();
      delay(debounce);
    }
  }
  allumeled();
  delay(debounce);
  if(valid == true) {execution();}
  else {annulation();}
}

void execution()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Action en cour ");
  lcd.setCursor(0,1);
  lcd.print("      ...       ");
  while(digitalRead(btvalid) == 1) {
    if((millis() - lasttime) >= intervale) {
      lasttime = millis();
      moteur.step(indicedirection);
      allumeled();
    }
  }
  allumeled();
  delay(debounce);
}

void annulation()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Vous avez annul");
  lcd.write((byte)1);
  while(digitalRead(btvalid) == 1) {/* Vide */}
  allumeled();
  delay(debounce);
}

void manuel()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Mode manuel");
  lcd.setCursor(0,1);
  lcd.print("Bougez le moteur");
  
  while(digitalRead(btvalid) == 1) {
    if(digitalRead(btbas) == 0) {
      moteur.step(-8);
      allumeled();
    }
    if(digitalRead(bthaut) == 0) {
      moteur.step(8);
      allumeled();
    }
  }
  delay(debounce);
}

void allumeled()
{
  digitalWrite(led, HIGH);
  delay(1);
  digitalWrite(led, LOW);
}
