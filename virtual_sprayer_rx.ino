/*

Project:      Virtual dunk tank
Author:       Jason Lawley
Date:         9/3/12

Description:  The following is code is to create a 'Virtual Dunk Tank'
or VDT.  The VDT replaces a conventional dunk tank.  Instead, the person
to be dunked sits in front of three sprinklers.  The sprinklers are controlled
by three different vavles that can be turned on independently.

There are two inputs to the VDT - one is the big red button (BRB) that will have 
a ball thrown at it.  When the BRB is hit, it will cause the three valves
to open can soak the dunkee.  There are three independent valvues that are
controlled to to create different displays of water or to 'dunk' the dunkee
to varying degrees of drenchedness.

There is also a discreet little black button (LBB) located at the controller  
that when pressed will also act as if the BRB had been depressed.  This
eliminates the need for the VDT monitor to run up and press the button when
they deem it should have soaked the dunkee because the BRB was hit,
but the did not trigger.

Finally, the big red button also has an independently controlled LED that will
light up when either the BRB or the LBB have been depressed.
 
 */
 
 // This is a test

 // Constant pin connections
const int LBB         = 4;    // Little black button
const int BRB         = 7;    // Big red button
const volatile int BRB_LED     = 5;    // Big red button LED
const int LED_0       = 13;   // On-board LED
const int CTRL_0      = 12;   // Valve control
const int CTRL_1      = 10;   // Valve control
const int CTRL_2      = 8;    // Valve control

int BRBState = HIGH;          // Variable for pushbuttons
int LBBState = HIGH;          // Variable for pushbuttons
int counter = 0;
int rand_select;
int buttonPush = LOW;


 
void setup(){
  //start serial connection
  Serial.begin(9600);
  // Configure input and output pins
  
  // Pushbutton inputs with internal pull-up resistor
  pinMode(LBB, INPUT_PULLUP);
  pinMode(BRB, INPUT_PULLUP);
  
  // Outputs
  pinMode(LED_0, OUTPUT); 
  pinMode(CTRL_0, OUTPUT);
  pinMode(CTRL_1, OUTPUT);
  pinMode(CTRL_2, OUTPUT);
  pinMode(BRB_LED, OUTPUT);
  
  randomSeed(analogRead(A0)); //Seed the pseudo-random engine with some true randomness.

  
  all_valves_on();
  delay(5000);
  all_valves_off();

}

void loop(){
  
  
  Serial.println("Start of loop");
  
  // Wait for one of the buttons to be pushed
  while (buttonPush == LOW) {
    BRBState = digitalRead(BRB);
    LBBState = digitalRead(LBB);
    if (!BRBState | !LBBState)
      buttonPush = HIGH;
  }

  if (BRBState == LOW) {
    Serial.println("BRB Pressed");
  } else {
    Serial.println("LBB Pressed");
  } 
  
  Serial.println("Get ready to flash BRB");
  flash_BRB();
  
  // Temporary counter
 //if (counter == 7)
 //   counter = 0;
 // else
 //   counter++;

  rand_select = random(8);
  Serial.println("Random pattern selected is:");
  Serial.println(rand_select, DEC);
  
  switch (rand_select) {
    case 0:
      pattern_0();
      break;
    case 1:
      pattern_1();
      break;
    case 2:
      pattern_2();
      break;
    case 3:
      pattern_3();
      break;
    case 4:
      pattern_4();
      break;
    case 5:
      pattern_5();
      break;
    case 6:
      pattern_6();
      break;
    case 7:
      pattern_7();
      break;
  }
  
 
  // Turn everything off
  digitalWrite (BRB_LED, LOW);
  all_valves_off();
  buttonPush = LOW;

  Serial.println("Cycle completed");
  
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//****                    FUNCTIONS                                        ****
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

// Turn off all of the valves
void all_valves_off (){
  digitalWrite (CTRL_0, LOW);
  digitalWrite (CTRL_1, LOW);
  digitalWrite (CTRL_2, LOW);
}


// Turn on all of the valves
void all_valves_on (){
  digitalWrite (CTRL_0, HIGH);
  digitalWrite (CTRL_1, HIGH);
  digitalWrite (CTRL_2, HIGH);
}


// Flash the BRB
void flash_BRB () {
 Serial.println("Flash BRB");
  for (int i=0; i <= 40; i++) {
    digitalWrite (BRB_LED, HIGH);
    delay (50);
    digitalWrite (BRB_LED, LOW);
    delay (30);
  }
}



// Turn on the valves from left to right
// Delay value for how long the valves are on/off
// Also can pass how many times there is a cycle
void cycle_LR (int delay_val, int times) {
  
  for (int i=0; i < times; i++) {
    digitalWrite (CTRL_0, HIGH);
    delay (delay_val);
    digitalWrite (CTRL_0, LOW);
    delay (delay_val);
    digitalWrite (CTRL_1, HIGH);
    delay (delay_val);
    digitalWrite (CTRL_1, LOW);
    delay (delay_val);
    digitalWrite (CTRL_2, HIGH);
    delay (delay_val);
    digitalWrite (CTRL_2, LOW);
    delay (delay_val);
  }
}


// Turn on the valves from left to right
// Delay value for how long the valves are on/off
// Also can pass how many times there is a cycle
void cycle_RL (int delay_val, int times) {
  
  for (int i=0; i < times; i++) {
    digitalWrite (CTRL_2, HIGH);
    delay (delay_val);
    digitalWrite (CTRL_2, LOW);
    delay (delay_val);
    digitalWrite (CTRL_1, HIGH);
    delay (delay_val);
    digitalWrite (CTRL_1, LOW);
    delay (delay_val);
    digitalWrite (CTRL_0, HIGH);
    delay (delay_val);
    digitalWrite (CTRL_0, LOW);
    delay (delay_val);
  }
}

void outside_on (int delay_val) {
  digitalWrite (CTRL_0, HIGH);
  digitalWrite (CTRL_2, HIGH);
  delay (delay_val);
  digitalWrite (CTRL_0, LOW);
  digitalWrite (CTRL_2, LOW);
}

void middle_on (int delay_val) {
  digitalWrite (CTRL_1, HIGH);
  delay (delay_val);
  digitalWrite (CTRL_1, LOW);
}  

void left_two_on (int delay_val) {
  digitalWrite (CTRL_0, HIGH);
  digitalWrite (CTRL_1, HIGH);
  delay (delay_val);
  digitalWrite (CTRL_0, LOW);
  digitalWrite (CTRL_1, LOW);
}

void right_two_on (int delay_val) {
  digitalWrite (CTRL_1, HIGH);
  digitalWrite (CTRL_2, HIGH);
  delay (delay_val);
  digitalWrite (CTRL_1, LOW);
  digitalWrite (CTRL_2, LOW);
}

void rlm_cycle (int delay_val, int times) {
  
  digitalWrite (CTRL_1, HIGH);
  for (int i=0; i < times; i++) {
      digitalWrite (CTRL_2, HIGH);
      digitalWrite (CTRL_0, LOW);
      delay (delay_val);
      digitalWrite (CTRL_2, LOW);
      digitalWrite (CTRL_0, HIGH);
      delay (delay_val);
  }
  digitalWrite (CTRL_0, LOW);
  digitalWrite (CTRL_1, LOW);
  digitalWrite (CTRL_2, LOW);
  
}


  
void pattern_0() {
  
  Serial.println("Pattern 0");
  outside_on(300);
  delay(500);
  middle_on(500);
  delay(500);
  left_two_on(300);
  delay(500);
  right_two_on(300);
  delay(750);
  cycle_RL(300, 1);
  delay(300);
  cycle_LR(300, 1);
}

void pattern_1 () {

  Serial.println("Pattern 1");
  all_valves_on();
  delay (300);
   
  all_valves_off();
  delay (300);
  
  cycle_LR(300, 3);
  cycle_RL(300, 2);
  cycle_LR(300, 1);
}

void pattern_2() {
  
  Serial.println("Pattern 2");
  for (int i=0; i < 5; i++) {
    middle_on(500);
    delay(300);
    outside_on(500);
    delay(300);
  }
}

void pattern_3() {
  
  Serial.println("Pattern 3");
  cycle_LR(300, 2);
  delay(300);
  cycle_RL(300, 2);
  delay(500);
  middle_on(700);
  delay(400);
  middle_on(300);
  delay(200);
  middle_on(300);
}


void pattern_4() {
  
  Serial.println("Pattern 4");
  left_two_on(400);
  delay(300);
  right_two_on(400);
  delay(500);
  cycle_RL(300, 1);
  delay(200);
  cycle_LR(300, 1);
}


void pattern_5() {
  
  Serial.println("Pattern 5");
  middle_on(500);
  delay(500);
  right_two_on(400);
  delay(500);
  left_two_on(400);
  delay(500);
  cycle_RL(200, 2);
  delay(200);
  cycle_LR(200, 2);
}

void pattern_6() {
  
  Serial.println("Pattern 6");
  
  rlm_cycle(600, 3);
  delay(300);
  cycle_RL(300, 3);
  delay(500);
  cycle_LR(300, 3);
  delay(1000);
  middle_on(1000);
  delay(500);
  middle_on(150);
  delay(250);
  middle_on(150);
}


void pattern_7() {
  
  Serial.println("Pattern 7");
  
  left_two_on(500);
  delay (300);
  right_two_on(500);
  delay(500);
  rlm_cycle(500,4);
  delay(300);
  middle_on(500);
}
