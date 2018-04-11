// Servo - Version: Latest 
#include <Servo.h>

// Pixy - Version: Latest 
#include <Pixy.h>
#include <PixyI2C.h>
#include <PixySPI_SS.h>
#include <TPixy.h>
#include <SPI.h>  

Pixy pixy;
Servo servo;

//initial variables
double Q[5][2] = { { 0 } };  
double R[5][2] =            
{
    { -1,0 },
    { 0,1 },
    { 0,0 },
    { 1,0 },
    { 0,-1 }
};


double Gamma = 0.8;
int iterations = 50;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  randomSeed(analogRead(0));
  servo.attach(10);
  pixy.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  int randomAction;
int reward;
  for(int i = 1; i<=iterations; i++){
    int currState = checkCurrentState();

    //While current state is not the goal state
    while currState!=2{
      
      while reward != 1{
        //take a random action 
        randomAction = random(0,4);
        //we need to take action only if it is adjacent and not beyond the bound of the world state
          if (R[currState][randomNextAction] >= 0){
              moveServo();
              //Need fixing in the implementation of below function
              Q[currState][randomNextAction] = R[currState][randomNextAction] + Gamma*(findMax(Q,randomNextAction));
          }
          
        //if random action leads to a higher R value update Q value, then update Q value from current state going to next state
        if
      }
    }
  }

}
void moveServo(int randAction){
//taking action
//going to a next random state
int pos = 18; //18 is the center of the state in terms of the servo

//NOTE: ACCORDING TO THE EXAMPLES OF SERVO, THE RANGE IS BETWEEN 0 TO 180 OF THE SERVO
//IN THE 'SERVO' WORLD EACH STATE IS OF SIZE 36
//We want the servo to go to the center position of the state, which will be 18
  if (randAction == 0)//move servo to state 0 in the real world.
      servo.write(((0*36)+pos));
    
  else if(randAction == 1)
      servo.write(((1*36)+pos))
  
  else if(randAction == 2)
      servo.write(((2*36)+pos))
      
  else if(randAction == 3)
      servo.write(((3*36)+pos))
      
  else if(randAction == 4)
      servo.write(((4*36)+pos))
    
}


void defineWorld(){
//This function is used to define the world
//do we need this? IDK  
}


//The below variables should store the max values in row and col
  byte maxRow;
  byte maxCol;

//KEEP IN MIND, WE NEED TO ADJUST THIS FUNCTION FOR IT TO BE 
double findMax(double & Q, int rowOfInterest){
  //This function is intended to find the maximum for the Bellman Equation...
  //...used to update the Q values in the main function
  double maxValue = 0; //we'll return this, hopefully
  int rowSize = sizeof(Q[0]); //THIS NEEDS TO BE TESTED FIRST
  int colSize = sizeof(Q);
  //Check ^_^
  Serial.print("Row size: "); Serial.print(rowSize); Serial.print("\n");
  Serial.print("Col size: "); Serial.print(colSize); Serial.print("\n");


    for (int col = 0; col < colSize; col++)
    {
      Serial.print(anArray[rowOfInterest][col]);
      Serial.print("\t");
      
      if (anArray[rowOfInterest][col] > maxValue)
      {
        maxValue = anArray[rowOfInterest][col];
        //maxRow = row;
        maxCol = col;
      }
    }
   
  Serial.println();
  Serial.print("Max value is : ");
  Serial.print(maxValue);
  Serial.print(" located at row ");
  Serial.print(maxRow);
  Serial.print(" column ");
  Serial.println(maxCol);

  return maxValue;
}


int checkCurrentState(){
//Obtaining the current position of the object and the current state
  int xPos = pixy.blocks[0].x;
  int currentState = 5;//we initialize it out of bounds of world for easier troubleshoot
  
  //0 to 63 is state 0
  if (xPos >= 0 && xPos <=126)
    currentState = 0;
    
  //63 to 126 is state 1
  else if (xPos > 63 && xPos <= 126)
    currentState = 1;
    
  //126 to 189 is state 2 <this is the goal state>
  else if (xPos > 126 && xPos <= 189)
    currentState = 2;

  //189 to 252 is state 3
  else if (xPos > 189 && xPos <= 252)
    currentState = 3;
  //252 to 315 is state 4
  else if (xPos > 252 && xPos <= 315)
    currentState = 4;

  Serial.print("Inside checkCurrentState(), the current state is: ")
  Serial.print(currentState);
  Serial.print('\n');
  
    return currentState;

    
}

