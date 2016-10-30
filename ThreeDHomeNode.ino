#include <MultiStepper.h>
#include<AccelStepper.h> // Шаговый двигатель

int lampPin = 7; // Pin для лампы

// Пины для трехцветного светодиода
int r = 13; // Красный
int g = 12; // Зеленый
int b = 11; // Голубой


// Определение пинов для управления двигателем
#define motorPin1  3 // IN1 на 1-м драйвере ULN2003
#define motorPin2  4 // IN2 на 1-м драйвере ULN2003
#define motorPin3  5 // IN3 на 1-м драйвере ULN2003
#define motorPin4  6 // IN4 на 1-м драйвере ULN2003

#define HALFSTEP 8 // Настройка для шагового двигателя
// Инициализируемся с последовательностью выводов IN1-IN3-IN2-IN4 для использования AccelStepper с 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);



int isEnableStepper = 0;


void setup()
{
	Serial.begin(9600); // Скорость обмена
	pinMode(lampPin, OUTPUT);

	// Объявляем используемые порты для RGB
	pinMode(r, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(b, OUTPUT);

	// Шаговый двигатель
	stepper1.setMaxSpeed(1000.0);
	stepper1.setAcceleration(100.0);
	stepper1.setSpeed(200);
	stepper1.moveTo(20000);
}

int result = 0;
void loop()
{
	StepperOn();

	// Принимаем состояние из com - порта
	if (Serial.available() > 0)
	{
		result = Serial.read();
		if (result == 49)
		{
			digitalWrite(lampPin, HIGH);   // Включаем лампу
			return;
		}
		if (result == 48)
		{
			digitalWrite(lampPin, LOW);   // Включаем лампу
			return;
		}
		if (result == 50)
		{
			digitalWrite(r, HIGH); //включаем красный
			digitalWrite(g, LOW); //включаем красный
			digitalWrite(b, LOW); //включаем красный
		}
		if (result == 51)
		{
			digitalWrite(g, HIGH); //включаем красный
			digitalWrite(r, LOW); //включаем красный
			digitalWrite(b, LOW); //включаем красный
		}
		if (result == 52)
		{
			digitalWrite(b, HIGH); //включаем красный
			digitalWrite(r, LOW); //включаем красный
			digitalWrite(g, LOW); //включаем красный
		}
		if (result == 53)
		{
			digitalWrite(b, LOW); //включаем красный
			digitalWrite(r, LOW); //включаем красный
			digitalWrite(g, LOW); //включаем красный
		}
		if (result == 54)
		{
			isEnableStepper = 1;


		}
		if (result == 55)
		{
			isEnableStepper = 0;
		}
	}
}

void StepperOn()
{
	if (isEnableStepper == 1)
	{
		// Изменяем направление, если шаговик достигает заданного положения
		if (stepper1.distanceToGo() == 0)
			stepper1.moveTo(-stepper1.currentPosition());
		stepper1.run();
	}
	else
	{
		stepper1.stop();
	}
}
