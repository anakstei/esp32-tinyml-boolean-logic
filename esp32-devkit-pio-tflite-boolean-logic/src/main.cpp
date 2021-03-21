#include <Arduino.h>
#include "neural_network.h"

#define LED       4
#define BUTTON_A  25
#define BUTTON_B  26

NeuralNetwork *nn;

void setup()
{
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);

  nn = new NeuralNetwork();
}

void loop()
{
  // int a = random(2);
  // int b = random(2);
  int a = (digitalRead(BUTTON_A) == LOW) ? 1 : 0;
  int b = (digitalRead(BUTTON_B) == LOW) ? 1 : 0;

  nn->getInputBuffer()[0] = a;
  nn->getInputBuffer()[1] = b;

  float y = nn->predict();
  int expected = a ^ b;
  int predicted = (y > 0.5) ? 1 : 0;

  Serial.printf("Input: a=%d b=%d, Output: y=%.2f, Expected=%d, Predicted=%d\n",
      a, b, y, expected, predicted);

  digitalWrite(LED, predicted);

  delay(1000);
}