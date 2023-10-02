#include "usr_server.h"
#include "usr_wifi.h"



#define TCP_SERVER_ADDR "bemfa.com"     // 云服务器地址
#define TCP_SERVER_PORT "8344"          // 服务器端口

#define upDataTime 2*1000               // 上传速率2s (1s<=upDataTime<=60s）
#define MAX_PACKETSIZE 512              // 最大字节数

String UID = "04cbbb009ce722b9fe048e7dbc01f419";    //用户私钥(这是我的,自己改成自己的)
String TOPIC = "YZTtemp";                              //用于传输温湿度的主题


/* tcp初始化相关 */
WiFiClient TCPclient;
String TcpClient_Buff = "";
unsigned int TcpClient_BuffIndex = 0;
unsigned long TcpClient_preTick = 0;
unsigned long preHeartTick = 0;//心跳
unsigned long preTCPStartTick = 0;//连接
bool preTCPConnected = false;



/************************** 函数原型 ************************************/


//发送数据到TCP服务器
void sendtoTCPServer(String p)
{
  
  if (!TCPclient.connected()) 
  {
    Serial.println("Client is not readly");
    return;
  }
  TCPclient.print(p);
  Serial.println("[Send to TCPServer]:String");
  Serial.println(p);
}



// 初始化和服务器建立连接
void startTCPClient()
{
  if(TCPclient.connect(TCP_SERVER_ADDR, atoi(TCP_SERVER_PORT)))
  {
    Serial.print("\nConnected to server:");
    Serial.printf("%s:%d\r\n",TCP_SERVER_ADDR,atoi(TCP_SERVER_PORT));
    String tcpTemp="";
    tcpTemp = "cmd=1&uid="+UID+"&topic="+TOPIC+"\r\n";

    sendtoTCPServer(tcpTemp);
    preTCPConnected = true;
    preHeartTick = millis();
    TCPclient.setNoDelay(true);
  }
  else
  {
    Serial.print("Failed connected to server:");
    Serial.println(TCP_SERVER_ADDR);
    TCPclient.stop();
    preTCPConnected = false;
  }
  preTCPStartTick = millis();
}


// 检查数据发送数据
void doTCPClientTick()
{
    //检查是否断开，断开后重连
   if(WiFi.status() != WL_CONNECTED) return;

  if (!TCPclient.connected()) //断开重连
  {

    if(preTCPConnected == true)
    {
        preTCPConnected = false;
        preTCPStartTick = millis();
        Serial.println();
        Serial.println("TCP Client disconnected.");
        TCPclient.stop();
    }
    else if(millis() - preTCPStartTick > 1*1000)//重新连接
        startTCPClient();
  }
  else
  {
    if (TCPclient.available())  //收数据
    {
      char c =TCPclient.read();
      TcpClient_Buff +=c;
      TcpClient_BuffIndex++;
      TcpClient_preTick = millis();
      
      if(TcpClient_BuffIndex>=MAX_PACKETSIZE - 1)
      {
        TcpClient_BuffIndex = MAX_PACKETSIZE-2;
        TcpClient_preTick = TcpClient_preTick - 200;
      }
      preHeartTick = millis();
    }
    if(millis() - preHeartTick >= upDataTime)  //上传数据
    {
      preHeartTick = millis();

      /*****************获取DHT11 温湿度*****************/
      byte temperature = 50;
      byte humidity = 100;
 
      
      /*********************数据上传*******************/
      /*
        数据用#号包裹，以便app分割出来数据，&msg=#23#80#on#\r\n，即#温度#湿度#按钮状态#，app端会根据#号分割字符串进行取值，以便显示
        如果上传的数据不止温湿度，可在#号后面继续添加&msg=#23#80#data1#data2#data3#data4#\r\n,app字符串分割的时候，要根据上传的数据进行分割
      */
      String upstr = "";
      upstr = "cmd=2&uid="+UID+"&topic="+TOPIC+"&msg=#"+temperature+"#"+humidity+"#"+0+"#\r\n";
      sendtoTCPServer(upstr);
      upstr = "";
    }
  }
}

