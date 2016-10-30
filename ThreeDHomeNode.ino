#include <MultiStepper.h>
#include<AccelStepper.h> // ������� ���������

int lampPin = 7; // Pin ��� �����

// ���� ��� ������������ ����������
int r = 13; // �������
int g = 12; // �������
int b = 11; // �������


// ����������� ����� ��� ���������� ����������
#define motorPin1  3 // IN1 �� 1-� �������� ULN2003
#define motorPin2  4 // IN2 �� 1-� �������� ULN2003
#define motorPin3  5 // IN3 �� 1-� �������� ULN2003
#define motorPin4  6 // IN4 �� 1-� �������� ULN2003

#define HALFSTEP 8 // ��������� ��� �������� ���������
// ���������������� � ������������������� ������� IN1-IN3-IN2-IN4 ��� ������������� AccelStepper � 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);



int isEnableStepper = 0;


void setup()
{
	Serial.begin(9600); // �������� ������
	pinMode(lampPin, OUTPUT);

	// ��������� ������������ ����� ��� RGB
	pinMode(r, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(b, OUTPUT);

	// ������� ���������
	stepper1.setMaxSpeed(1000.0);
	stepper1.setAcceleration(100.0);
	stepper1.setSpeed(200);
	stepper1.moveTo(20000);
}

int result = 0;
void loop()
{
	StepperOn();

	// ��������� ��������� �� com - �����
	if (Serial.available() > 0)
	{
		result = Serial.read();
		if (result == 49)
		{
			digitalWrite(lampPin, HIGH);   // �������� �����
			return;
		}
		if (result == 48)
		{
			digitalWrite(lampPin, LOW);   // �������� �����
			return;
		}
		if (result == 50)
		{
			digitalWrite(r, HIGH); //�������� �������
			digitalWrite(g, LOW); //�������� �������
			digitalWrite(b, LOW); //�������� �������
		}
		if (result == 51)
		{
			digitalWrite(g, HIGH); //�������� �������
			digitalWrite(r, LOW); //�������� �������
			digitalWrite(b, LOW); //�������� �������
		}
		if (result == 52)
		{
			digitalWrite(b, HIGH); //�������� �������
			digitalWrite(r, LOW); //�������� �������
			digitalWrite(g, LOW); //�������� �������
		}
		if (result == 53)
		{
			digitalWrite(b, LOW); //�������� �������
			digitalWrite(r, LOW); //�������� �������
			digitalWrite(g, LOW); //�������� �������
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
		// �������� �����������, ���� ������� ��������� ��������� ���������
		if (stepper1.distanceToGo() == 0)
			stepper1.moveTo(-stepper1.currentPosition());
		stepper1.run();
	}
	else
	{
		stepper1.stop();
	}
}
