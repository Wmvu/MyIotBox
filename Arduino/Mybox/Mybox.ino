/*********************************************************************
		 声明：模块初始化等代码借用作者神秘藏宝室的代码
*********************************************************************/

#include <TimerOne.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define air780Serail  Serial
SoftwareSerial DebugSerial(10, 11); // RX, TX			
#define Success 1U
#define Failure 0U

int L = 13; //LED指示灯引脚

unsigned long  Time_Cont = 0;       //定时器计数器

const unsigned int AirRxBufferLength = 600;
char air780RxBuffer[AirRxBufferLength];
unsigned int air780BufferCount = 0;
int count = 0;
void removeNewLine(char* str) {
    int len = strcspn(str, "{"); // 找到第一个换行符的位置
    char *a = &str[len];
    len = strcspn(a, "\r"); // 找到第一个换行符的位置
    char doneString[len+1];
    for(int i=0;i<len;i++){
      doneString[i]=a[i];
    }
    doneString[len]='\0';
 strcpy(str,doneString);
 Serial.println(str);
}

void setup() {
	pinMode(L, OUTPUT);
	digitalWrite(L, LOW);

	DebugSerial.begin(9600);
	air780Serail.begin(9600);

	Timer1.initialize(1000);
	Timer1.attachInterrupt(Timer1_handler);

	handAT();	//AT测试

	initair780();		//初始化模块
if (sendCommand("AT+SAPBR=3,1,\"APN\",\"\"\r\n", "OK\r\n", 3000, 1) == Success);
    else errorLog(9); 
    if (sendCommand("AT+SAPBR=1,1\r\n", "OK\r\n", 3000, 1) == Success);
    delay(500);
    if (sendCommand("AT+HTTPINIT\r\n", "OK\r\n", 3000, 1) == Success); 
    delay(500);
    if (sendCommand("AT+HTTPPARA=\"URL\",\"www.wm-f.cn:8089/api/arduino\"\r\n", "OK\r\n", 3000, 3) == Success);
    delay(500);
    if (sendCommand("AT+HTTPACTION=0\r\n", "OK\r\n", 3000, 1) == Success); 
    delay(500);
    readw("AT+HTTPREAD\r\n", "OK\r\n", 5000, 1);
	DebugSerial.println("\r\nsetup end!");
}

void loop() {

	while(1);

}

void handAT()
{
	while (sendCommand("AT\r\n", "OK\r\n", 100, 10) != Success)
	{
		delay(100);
	}
	
}

void initair780()
{
	if (sendCommand("AT\r\n", "OK\r\n", 3000, 10) == Success);
	else errorLog(1);

	if (sendCommand("AT&F\r\n", "OK\r\n", 3000, 10) == Success);
	else errorLog(1);

	if (sendCommand("AT+CSQ\r\n", "OK\r\n", 3000, 10) == Success);
	else errorLog(1);
	delay(100);

	if (sendCommandReceive2Keyword("AT+CPIN?\r\n", "READY","OK\r\n" ,3000, 10) == Success);
	else errorLog(1);
	delay(100);

	if (sendCommand("AT+COPS?\r\n", "OK\r\n", 3000, 10) == Success);
	else errorLog(1);
	delay(100);

	if (sendCommandReceive2Keyword("AT+CREG?\r\n", ",1","OK\r\n", 3000, 10) == Success);	//本地SIM卡
	else if(sendCommandReceive2Keyword("AT+CREG?\r\n", ",5", "OK\r\n",3000, 10) == Success	);//漫游SIM卡
	else	errorLog(3);


	if (sendCommand("AT+CIPSHUT\r\n", "OK\r\n", 5000, 10) == Success);
	else errorLog(13);

	if (sendCommandReceive2Keyword("AT+CGATT?\r\n", "+CGATT: 1","OK\r\n" ,3000, 10) == Success);
	else errorLog(1);
	delay(100);

	if (sendCommand("AT+CSTT\r\n", "OK\r\n", 3000, 10) == Success);
	else errorLog(1);
	delay(100);

	if (sendCommand("AT+CIICR\r\n", "OK\r\n", 3000, 10) == Success);
	else errorLog(1);
	delay(100);

	if (sendCommandReceive2Keyword("AT+CIFSR\r\n", ".","\r\n" ,3000, 10) == Success);
	else errorLog(1);
	delay(100);

}

void(* resetFunc) (void) = 0; //制造重启命令

void errorLog(int num)
{
	DebugSerial.print("ERROR");
	DebugSerial.println(num);
	while (1)
	{
		digitalWrite(L, HIGH);
		delay(100);
		digitalWrite(L, LOW);
		delay(100);
		digitalWrite(L, HIGH);
		delay(100);
		digitalWrite(L, LOW);
		delay(300);

		if (sendCommand("AT\r\n", "OK\r\n", 100, 10) == Success)
		{
			DebugSerial.print("\r\nRESET!!!!!!\r\n");
			resetFunc();
		}
	}
}



unsigned int readw(char *Command, char *Response, unsigned long Timeout, unsigned char Retry)
{
  clrair780RxBuffer();
  for (unsigned char n = 0; n < Retry; n++)
  {
    DebugSerial.print("\r\n---------send AT Command:---------\r\n");
    DebugSerial.write(Command);
    air780Serail.write(Command);
    Time_Cont = 0;
    while (Time_Cont < Timeout)
    {
      air780ReadBuffer();
      DebugSerial.print("."); 

      if (strstr(air780RxBuffer, Response) != NULL)
      {
        removeNewLine(air780RxBuffer);
        StaticJsonDocument<32> doc;
        DeserializationError error = deserializeJson(doc, air780RxBuffer);
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
                resetFunc();
          return;
        } 
        bool pram = doc["pram"];
        if(pram == true)digitalWrite(L, HIGH);
        clrair780RxBuffer();
        return Success;
      }
      
    }
    Time_Cont = 0;
  }
  DebugSerial.print("\r\n==========receive AT Command:==========\r\n");
  DebugSerial.print(air780RxBuffer);//输出接收到的信息
  
  clrair780RxBuffer();
  return Failure;
}
unsigned int sendCommand(char *Command, char *Response, unsigned long Timeout, unsigned char Retry)
{
	clrair780RxBuffer();
	for (unsigned char n = 0; n < Retry; n++)
	{
		DebugSerial.print("\r\n---------send AT Command:---------\r\n");
		DebugSerial.write(Command);

		air780Serail.write(Command);
		// DebugSerial.print("\r\n---------out air780Serail.print(Command);---------\r\n");
		// DebugSerial.print(Time_Cont);
		Time_Cont = 0;
		while (Time_Cont < Timeout)
		{
			air780ReadBuffer();
			DebugSerial.print(".");	//1.8.x的IDE不加这个会有bug

			if (strstr(air780RxBuffer, Response) != NULL)
			{
				DebugSerial.print("\r\n==========receive AT Command:==========\r\n");
				DebugSerial.print(air780RxBuffer); //输出接收到的信息
//       Serial.println(air780RxBuffer);
				clrair780RxBuffer();
				return Success;
			}
			
		}
		Time_Cont = 0;
	}
	DebugSerial.print("\r\n==========receive AT Command:==========\r\n");
	DebugSerial.print(air780RxBuffer);//输出接收到的信息
  
	clrair780RxBuffer();
	return Failure;
}

unsigned int sendCommandReceive2Keyword(char *Command, char *Response, char *Response2, unsigned long Timeout, unsigned char Retry)
{
	clrair780RxBuffer();
	for (unsigned char n = 0; n < Retry; n++)
	{
		DebugSerial.print("\r\n---------send AT Command:---------\r\n");
		DebugSerial.write(Command);


		air780Serail.write(Command);

		Time_Cont = 0;
		
		while (Time_Cont < Timeout)
		{
			air780ReadBuffer();
			DebugSerial.print(".");	//1.8.x的IDE不加这个会有bug
			if (strstr(air780RxBuffer, Response) != NULL && strstr(air780RxBuffer, Response2) != NULL)
			{
				DebugSerial.print("\r\n==========receive AT Command:==========\r\n");
				DebugSerial.print(air780RxBuffer); //输出接收到的信息
				clrair780RxBuffer();
				return Success;
			}
		}
		Time_Cont = 0;
	}
	DebugSerial.print("\r\n==========receive AT Command:==========\r\n");
	DebugSerial.print(air780RxBuffer);//输出接收到的信息
	clrair780RxBuffer();
	return Failure;
}




void Timer1_handler(void)
{
	Time_Cont++;
}



void air780ReadBuffer() {
	while (air780Serail.available())
	{
		air780RxBuffer[air780BufferCount++] = air780Serail.read();
		if (air780BufferCount == AirRxBufferLength)clrair780RxBuffer();
	}
}

void clrair780RxBuffer(void)
{
	memset(air780RxBuffer, 0, AirRxBufferLength);      //清空
	air780BufferCount = 0;
}
