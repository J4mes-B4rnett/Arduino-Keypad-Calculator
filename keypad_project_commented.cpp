#include <Keypad.h> // Include the keypad library.

const byte ROWS = 4; // Define number of Rows on the keypad.
const byte COLM = 4; // Define number of Columns on the keypad.

char keys[ROWS][COLM] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
}; // Define the matrix.

byte rowPins[ROWS] = {13, 12, 11, 10}; // Determine which pins link up to which
byte colmPins[COLM] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colmPins, ROWS, COLM); // Create the new keypad object.

float inputs[2]; // Create an array of floats to store all of the inputs from the keypad.
bool inputs_entered[2]; // Create an array of matching bool values to determine whether the inputs have been entered yet.
bool inputs_displayed[2]; // Create an array of matching bool values to determine whether the input's message has been printed yet.

char arithmetic_op; // Create a character variable to store what arithmetic operator will be used by the calculator.
bool arithmetic_op_entered = false; // Determine whether the char has been entered yet.
bool arithmetic_op_displayed = false; // Determine whether the message has been printed yet.

void setup() { // When the arduino first runs.
  Serial.begin(9600); // Serialize the serial monitor at the frequency of 9600
  
  ResetValues(); // Call the reset-values function.
  Calculator(); // Call the calculator function.
}

void loop() {} // Empty method (Required by the IDE)

void ResetValues() // Resets all of the values
{
  for (int i = 0; i < 2; i++) // Repeat twice
  {
    inputs_entered[i] = false; // Set every input entered to false
    inputs_displayed[i] = false; // Set every input displayed to false

    inputs[i] = 0; // Set every input to 0
  }
  
  arithmetic_op = NULL; // Set the char value to be empty
  arithmetic_op_entered = false; // Set the boolean value to false.
  arithmetic_op_displayed = false; // Set the boolean value to false.
}

void Calculator() // Calculator function
{
  ResetValues(); // Reset all of the values
  
  GetInputs(); // Call the GetInputs function
  GetOperator(); // Call the GetOperator function

  switch(arithmetic_op){ // Switch statement to determine which arithmetic operator is to be used.
    case 'A': // Addition
      Serial.println(inputs[0] + inputs[1]); // Print the values added together.
      break;
    case 'B': // Subtraction
      Serial.println(inputs[0] - inputs[1]); // Print the values subtracted.
      break;
    case 'C': // Multiplication
      Serial.println(inputs[0] * inputs[1]); // Print the values multiplied.
      break;
    case 'D': // Division
      Serial.println(inputs[0] / inputs[1]); // Print the values divided.
      break;
  }

  delay(100); // Wait 100 Milliseconds
  Serial.flush(); // Flush any serial inputs
  Calculator(); // Re-run the calculator function
}

void GetInputs() // Get the inputs
{
  while (!inputs_entered[0]){ // While the inputs have not been entered
    for (int i = 0; i < 2; i++) // Repeat twice
    {
      if (!inputs_entered[i] && !inputs_displayed[i]) // If the current inputs not been entered yet, or displayed.
      {
        Serial.println("Input " + String(i) + ": "); // Print the input message.
        inputs_displayed[i] = true; // Set the displayed boolean to true.
    
        while (!inputs_entered[i]) // While the current input has not been entered
        {
          char customKey = keypad.getKey(); // Get the raw keypad values.
          if (customKey != NO_KEY) // If the value returned is not empty.
          {
            customKey = convertValues(customKey); // Convert the values to an integer
            inputs[i] = customKey; // Set the current input to the value entered
            Serial.println(inputs[i]); // Print the input entered
            inputs_entered[i] = true; // Set the current input as entered to true.
          }
        }
      }
    }
  }
}

void GetOperator() // Get the operator to be used in the calculator function.
{
  while (!arithmetic_op_entered){ // While the arithmetic operator has not been entered yet.
    if (!arithmetic_op_entered && !arithmetic_op_displayed) // If it has not been entered or the message displayed yet.
    {
      Serial.println("Arithmetic Operator: "); // Print the message
      arithmetic_op_displayed = true; // Set the message displayed variable to true
    
      while (!arithmetic_op_entered) // While the arithmetic operator entered is not true
      { 
        char customKey = keypad.getKey(); // Get the raw keypad values.
        if (customKey != NO_KEY) // If the value returned is not empty.
        {
          arithmetic_op = customKey; // Set the arithmetic operator to the raw value.
          Serial.println(keypad.getKey()); // Print the raw value
          arithmetic_op_entered = true; // Set the value entered to true.
        }
      }
    }
  }
}

int convertValues(int x) // Convert the values to an integer
{
  return x - '0'; // Return the modified input.
}
