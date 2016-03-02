#include <LiquidCrystal.h>
#include <Stepper.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Stepper moteur(48, 8, 9, 10, 11);

const int btvalid = 0;
const int bthaut = 0;
const int btbas = 0;
const int led = 13;

byte heure = 0;
byte minutes = 0;
byte angle = 0;

byte vitesse = 0;

unsigned long intervale;

byte mode = 0;
byte indicedirection = -1;
boolean valid = false;

int debounce = 300;

void setup() {
  lcd.begin(16,2);
  moteur.setSpeed(90);

  pinMode(btvalid, INPUT_PULLUP);
   pinMode(bthaut, INPUT_PULLUP);
    pinMode(btbas, INPUT_PULLUP);
     pinMode(led, OUTPUT);
}

void loop() {
  selectmode(); //OK
  if(mode == 0) {modetempsangle(); selectdirection(); affichetempsangle(); validation();}
  if(mode == 1) {modevitesse(); selectdirection(); affichevitesse(); validation();}
  if(mode == 2) {manuel();} //OK
}

void selectmode()
{
  while(digitalRead(btvalid) == 1) {
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("Mode:");
  
    lcd.setCursor(0,1);
    if(mode == 0) {lcd.print("Temps et angle");}
    if(mode == 1) {lcd.print("Temps par degre");}
    if(mode == 2) {lcd.print("Manuel");}

    if(digitalRead(bthaut) == 0) {
      mode++;
      delay(debounce);
    }
    if(digitalRead(btbas) == 0) {
      mode--;
      delay(debounce);
    }

    if(mode < 0) {mode = 2;}
    if(mode > 2) {mode = 0;}
  }
  delay(debounce);
}

void modetempsangle()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Temps:  Angle :");

  lcd.setCursor(0,1);
  lcd.print(" 00h00m   000");
  lcd.setCursor(13,1);
  lcd.print((char)223); //Signe °

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(1,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((heure / 10) == 0) {heure = 90;}
      else {heure = heure - 10;}
      lcd.print(heure / 10);
      allumeled();
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((heure / 10) == 9) {heure = 0;}
      else {heure = heure + 10;}
      lcd.print(heure / 10);
      allumeled();
      delay(debounce);
    }
  }
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(2,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((heure % 10) == 0) {heure = ((heure / 10) * 10) + 9;}
      else {heure = heure - 1;}
      lcd.print(heure % 10);
      allumeled();
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((heure % 10) == 9) {heure = (heure / 10) * 10;}
      else {heure = heure + 1;}
      lcd.print(heure % 10);
      allumeled();
      delay(debounce);
    }
  }
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(4,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((minutes / 10) == 0) {minutes = 90;}
      else {minutes = minutes - 10;}
      lcd.print(minutes / 10);
      allumeled();
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((minutes / 10) == 9) {minutes = 0;}
      else {minutes = minutes + 10;}
      lcd.print(minutes / 10);
      allumeled();
      delay(debounce);
    }
  }
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(5,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((minutes % 10) == 0) {minutes = ((minutes / 10) * 10) + 9;}
      else {minutes = minutes - 1;}
      lcd.print(minutes % 10);
      allumeled();
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((minutes % 10) == 9) {minutes = (minutes / 10) * 10;}
      else {minutes = minutes + 1;}
      lcd.print(minutes % 10);
      allumeled();
      delay(debounce);
    }
  }
  delay(debounce);



  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(10,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((angle / 100) == 0) {angle = 900;}
      else {angle = angle - 100;}
      lcd.print(angle / 100);
      allumeled();
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((angle / 100) == 9) {angle = 0;}
      else {angle = angle + 100;}
      lcd.print(angle / 100);
      allumeled();
      delay(debounce);
    }
  }
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(11,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if(((angle % 100) / 10) == 0) {angle = ((angle / 100) * 100) + 90;}
      else {angle = angle - 10;}
      lcd.print((angle % 100) / 10);
      allumeled();
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if(((angle % 100) / 10) == 9) {angle = (angle / 100) * 100;}
      else {angle = angle + 10;}
      lcd.print((angle % 100) / 10);
      allumeled();
      delay(debounce);
    }
  }
  delay(debounce);

  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(12,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((angle % 10) == 0) {angle = ((angle / 10) * 10) + 9;}
      else {angle = angle - 1;}
      lcd.print(angle % 10);
      allumeled();
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((angle % 10) == 9) {angle = (angle / 10) * 10;}
      else {angle = angle + 1;}
      lcd.print(angle % 10);
      allumeled();
      delay(debounce);
    }
  }
  lcd.noBlink();
  delay(debounce);

  intervale = (((heure * 60) + minutes) * 60 * 1000) / (angle * 8);
}

void affichetempsangle()
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print(heure);
  lcd.setCursor(3,0);
  lcd.print("h");
  lcd.setCursor(4,0);
  lcd.print(minutes);
  lcd.setCursor(6,0);
  lcd.print("m");

  lcd.setCursor(10,0);
  lcd.print(angle);
  lcd.setCursor(13,0);
  lcd.print((char)223);
}

void modevitesse()
{
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(" Temps par pas: ");
  
  lcd.setCursor(4,1);
  lcd.print(",");
  lcd.setCursor(7,1);
  lcd.print("s/pas");
  
  while(digitalRead(btvalid) == 1) {
    lcd.setCursor(3,1);
    lcd.blink();
    if(digitalRead(btbas) == 0) {
      if((vitesse / 100) == 0) {vitesse = 900;}
      else {vitesse = vitesse - 100;}
      lcd.print(vitesse / 100);
      allumeled();
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((vitesse / 100) == 9) {vitesse = 0;}
      else {vitesse = vitesse + 100;}
      lcd.print(vitesse / 100);
      allumeled();
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
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if(((vitesse % 100) / 10) == 9) {vitesse = (vitesse / 100) * 100;}
      else {vitesse = vitesse + 10;}
      lcd.print((vitesse % 100) / 10);
      allumeled();
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
      delay(debounce);
    }
    if(digitalRead(bthaut) == 0) {
      if((vitesse % 10) == 9) {vitesse = (vitesse / 10) * 10;}
      else {vitesse = vitesse + 1;}
      lcd.print(angle % 10);
      allumeled();
      delay(debounce);
    }
  }
  lcd.noBlink();
  delay(debounce);

  intervale = vitesse * 100;
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

void selectdirection()
{
  lcd.clear();
    
  lcd.setCursor(0,0);
  lcd.print("Direction:");
  
  while(digitalRead(btvalid) == 1) {
    lcd.clear();
    
    lcd.setCursor(0,1);
    if(indicedirection == -1) {lcd.print("Vers la gauche");}
    if(indicedirection == 1) {lcd.print("Vers la droite");}

    if(digitalRead(bthaut) == 0) {
      indicedirection = indicedirection + 2;
      delay(debounce);
    }
    if(digitalRead(btbas) == 0) {
      indicedirection = indicedirection - 2;
      delay(debounce);
    }
    
    if(mode < -1) {mode = 1;}
    if(mode > 1) {mode = -1;}
  }
  delay(debounce);
}

void validation()
{
  lcd.setCursor(0,1);
  lcd.print("Valider?");
  lcd.setCursor(10,1);

  while(digitalRead(btvalid) == 1) {
    if(valid == false) {lcd.print("NON");}
    if(valid == true) {lcd.print("OUI");}

    if(digitalRead(bthaut) == 0 || digitalRead(btbas) == 0) {
      //Synthaxe opérateur conditionnel : "Condition?Instruction1:Instruction2"
      valid = (valid == false ? true : false);
      delay(debounce);
    }
  }
  if(valid == true) {
    execution();
  }
}

void execution()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Action en cour ");
  lcd.setCursor(0,1);
  lcd.print("      ...       ");
  while(digitalRead(btvalid) == 1) {
    moteur.step(indicedirection);
    allumeled();
    delay(intervale);
  }
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
