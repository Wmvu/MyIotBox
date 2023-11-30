#include <TimerOne.h>
#include <ArduinoJson.h>

#define air780Serail  Serial 


#define Success 1U
#define Failure 0U

int L = 13; //LED指示灯引脚

unsigned long  Time_Cont = 0;       //定时器计数器

const unsigned int AirRxBufferLength = 300;
char air780RxBuffer[AirRxBufferLength];
unsigned int air780BufferCount = 0;
char myjsonBuffer[250];
//const char address[]="http://evmapi.confluxscan.net/nft/owners?contract=0x4be2a456a71729b1c727868fb54cb7ef89878de5";

//const String ContractAddress = "0x564FCdB3a585871F8C25CcF9cc73a6846EC833D5";
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
}
void setup() {
  pinMode(L, OUTPUT);
  digitalWrite(L, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  air780Serail.begin(9600);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(Timer1_handler);


  handAT(); //AT测试

  initair780();   //初始化模块

  if (sendCommand("AT+SAPBR=3,1,\"APN\",\"\"\r\n", "OK\r\n", 3000, 1) == Success);
    else errorLog(9); 
    if (sendCommand("AT+SAPBR=1,1\r\n", "OK\r\n", 3000, 1) == Success);
    delay(500);
    if (sendCommand("AT+HTTPINIT\r\n", "OK\r\n", 3000, 1) == Success); 
    delay(500);
    String url = "AT+HTTPPARA=\"URL\",\"evmapi.confluxscan.net//nft//owners?contract=0x564FCdB3a585871F8C25CcF9cc73a6846EC833D5&tokenId=0\"\r\n";
    if (sendCommand(url.c_str(), "OK\r\n", 3000, 1) == Success);
    delay(500);
    if (sendCommand("AT+HTTPACTION=0\r\n", "OK\r\n", 3000, 1) == Success); 
    delay(500);
    sendCommandw("AT+HTTPREAD\r\n", "OK\r\n", 5000, 1);
    
    removeNewLine(myjsonBuffer);

StaticJsonDocument<192> doc;

DeserializationError error = deserializeJson(doc, myjsonBuffer);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

JsonObject result = doc["result"];
const char* result_list_0_address = result["list"][0]["address"];
int a = strcmp(result_list_0_address,"0x564fcdb3a585871f8c25ccf9cc73a6846ec833d5");
if(a == 0){
   air780Serail.println("YES");
   digitalWrite(13, HIGH);
  }else{
     air780Serail.println("NO");
  }
    
}

void loop() {
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

  if (sendCommandReceive2Keyword("AT+CREG?\r\n", ",1","OK\r\n", 3000, 10) == Success);  //本地SIM卡
  else if(sendCommandReceive2Keyword("AT+CREG?\r\n", ",5", "OK\r\n",3000, 10) == Success  );//漫游SIM卡
  else  errorLog(3);


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
      resetFunc();
    }
  }
}



unsigned int sendCommand(char *Command, char *Response, unsigned long Timeout, unsigned char Retry)
{
  clrair780RxBuffer();
  for (unsigned char n = 0; n < Retry; n++)
  {
    air780Serail.write(Command);

    Time_Cont = 0;
    while (Time_Cont < Timeout)
    {
      air780ReadBuffer();
      if (strstr(air780RxBuffer, Response) != NULL)
      {
        clrair780RxBuffer();
        return Success;
      }
      
    }
    Time_Cont = 0;
  }
  clrair780RxBuffer();
  return Failure;
}
unsigned int sendCommandw(char *Command, char *Response, unsigned long Timeout, unsigned char Retry)
{
  clrair780RxBuffer();
  for (unsigned char n = 0; n < Retry; n++)
  {
    air780Serail.write(Command);
   
    Time_Cont = 0;
    while (Time_Cont < Timeout)
    {
      air780ReadBuffer();

      if (strstr(air780RxBuffer, Response) != NULL)
      {
        strcpy(myjsonBuffer,air780RxBuffer);
        clrair780RxBuffer();
        return Success;
      }
      
    }
    Time_Cont = 0;
  }
  clrair780RxBuffer();
  return Failure;
}

unsigned int sendCommandReceive2Keyword(char *Command, char *Response, char *Response2, unsigned long Timeout, unsigned char Retry)
{
  clrair780RxBuffer();
  for (unsigned char n = 0; n < Retry; n++)
  {
    air780Serail.write(Command);

    Time_Cont = 0;
    
    while (Time_Cont < Timeout)
    {
      air780ReadBuffer();
      if (strstr(air780RxBuffer, Response) != NULL && strstr(air780RxBuffer, Response2) != NULL)
      {
        clrair780RxBuffer();
        return Success;
      }
    }
    Time_Cont = 0;
  }
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
