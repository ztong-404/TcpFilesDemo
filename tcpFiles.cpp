/*
 * ��������tcpFile.cpp�� ����tcpЭ�飬 ʵ���ļ��ϴ��Ŀͻ��ˡ�
*/
#include"public.h"

//�������еĲ����ṹ�塣
struct st_arg
{
  int clienttype; //�ͻ������ͣ�1-�ϴ��ļ��� 2-�����ļ�
  char ip[31];    //����˵�IP��ַ
  int port;       //����˵Ķ˿�
  int ptype;      //�ļ��ϴ��ɹ���Ĵ���ʽ��1-ɾ���ļ���2-�ƶ�������Ŀ¼
  char clientpath[301];    //�����ļ���ŵĸ�Ŀ¼
  char clientpathbak[301];  //�ļ��ɹ��ϴ��󣬱����ļ����ݵĸ�Ŀ¼����ptype==2ʱ��Ч
  bool andchild;            //�Ƿ��ϴ�clientpathĿ¼���¸�����Ŀ¼���ļ���true-�ǣ�false-��
  char matchname[301];      //���ϴ��ļ�����ƥ�䷽ʽ���硰��TxT������XML��
  char srvpath[301];        //������ļ���ŵĸ�Ŀ¼
  int timetvl;              //ɨ�豾��Ŀ¼�ļ���ʱ��������λ����              
  int timeout;              //���������ĳ�ʱʱ��
  char pname[51];           //�������������á�tcpgetfiles_��׺���ķ�ʽ
} starg;

//��xml����������starg�ṹ��
bool _xmltoArg(char *str_xmlBuffer);

CLogFile logfile; //��������������־
CTcpClient TcpClient;

char strRecvBuffer[1024]; //���ͱ��ĵ�buffer
char strSendBuffer[1024]; //���ձ��ĵ�buffer

//�����˻����ź�2��15 �Ĵ�������
void EXIT(int sig);

void _help();

//��xml����������starg�ṹ��
bool _xmltoArg(char *strxmlBuffer);

bool Login(const char *argv);  //��¼

bool ActiveTest(); //����

CPActive PActive; //��������


int main(int argc,char *argv[])
{
  if (argc!=3) { _help(); return -1; }

  // �ر�ȫ�����źź����������
  // �����ź�,��shell״̬�¿��� "kill + ���̺�" ������ֹЩ���̡�
  CloseIOAndSignal(); signal(SIGINT,EXIT); signal(SIGTERM,EXIT);

  // ����־�ļ���
  if (logfile.Open(argv[1],"a+")==false)
  {
    printf("Open log failed(%s).\n",argv[1]); return -1;
  }

  // ����xml���õ��������еĲ�����
  if (_xmltoArg(argv[2])==false){
    logfile.Write("XML wrong.\n");
   return -1;
  }

  PActive.AddPInfo(starg.timeout,starg.pname);  // �ѽ��̵�������Ϣд�빲���ڴ档

  // �����˷�����������
  if (TcpClient.ConnectToServer(starg.ip,starg.port)==false)
  {
    logfile.Write("TcpClient.ConnectToServer(%s,%d) failed.\n",starg.ip,starg.port); EXIT(-1);
  }

  // ��¼ҵ��
  if (Login(argv[2])==false) { logfile.Write("Login() failed.\n"); EXIT(-1); }

  for (int ii=3;ii<5;ii++)
  {
    if (ActiveTest()==false) break;

    sleep(ii);
  }
   
  EXIT(0);
}

// ������ 
bool ActiveTest()    
{
  memset(strSendBuffer,0,sizeof(strSendBuffer));
  memset(strRecvBuffer,0,sizeof(strRecvBuffer));
 
  SPRINTF(strSendBuffer,sizeof(strSendBuffer),"<activetest>ok</activetest>");
   logfile.Write("Active Send: %s\n",strSendBuffer);
  if (TcpClient.Write(strSendBuffer)==false) return false; // �����˷��������ġ�

  if (TcpClient.Read(strRecvBuffer,20)==false) return false; // ���շ���˵Ļ�Ӧ���ġ�
   logfile.Write("Active Recv: %s\n",strRecvBuffer);

  return true;
}

// ��¼ҵ�� 
bool Login(const char *argv)    
{
  memset(strSendBuffer,0,sizeof(strSendBuffer));
  memset(strRecvBuffer,0,sizeof(strRecvBuffer));
 
  SPRINTF(strSendBuffer,sizeof(strSendBuffer),"%s<clienttype>1</clienttype>",argv);
  logfile.Write("send:%s\n",strSendBuffer);
  if (TcpClient.Write(strSendBuffer)==false)// �����˷��������ġ�
  {
  logfile.Write("tcpClient Write to strSendBuffer wrong");
   return false; // �����˷��������ġ�
  }
  if (TcpClient.Read(strRecvBuffer,20)==false){// ���շ���˵Ļ�Ӧ���ġ�
  logfile.Write("tcpClient Read to strRecvBuffer wrong");
  return false;
  }
  
  logfile.Write("recevie:%s\n",strRecvBuffer);

  logfile.Write("Login (%s:%d)success.\n",starg.ip,starg.port); 

  return true;
}

//�˳����̺���
void EXIT(int sig)
{
  logfile.Write("process exit, sig=%d\n\n",sig);

  exit(0);
}

void _help()
{
  printf("\n");
  printf("Using:/home/mininet/demo/net/tcpFiles logfilename xmlbuffer\n\n");

  printf("Sample:/project/tools1/bin/procctl 20 ./tcpFiles /home/mininet/demo/net/tcpFiles/tcpFile.log \"<ip>192.168.174.128</ip><port>5005</port><ptype>1</ptype><clientpath>/home/mininet/demo/net/tcpFiles</clientpath><clientpathbak>/home/mininet/demo/net/tcpFiles</clientpathbak><andchild>true</andchild><matchname>*.xml,*.SCV,*.JSON</matchname><srvpath>/home/mininet/demo/net/tcpFiles</srvpath><timetvl>10</timetvl><timeout>50</timeout><pname>tcpputfiles_surfdata</pname>\"\n");
  printf("/home/mininet/demo/net/tcpFiles 20 /project/tools1/bin/tcpputfiles /log/idc/tcpputfiles_surfdata.log \"<ip>192.168.174.128</ip><port>5005</port><ptype>2</ptype>-<clientpath>/home/mininet/demo/net/tcpFiles</clientpath>-<clientpathbak>/home/mininet/demo/net/tcpFiles</clientpathbak>-<andchild>true</andchild><matchname>*.XML,*.CSV</matchname><srvpath>/home/mininet/demo/net/tcpFiles/temp</srvpath><timetvl>10</timetvl><timeout>50</timeout><pname>tcpputfiles_surfdata</pname>\"\n\n\n");

  printf("���������������ĵĹ�������ģ�飬����tcpЭ����ļ����͸�����ˡ�\n");
  printf("logfilename   ���������е���־�ļ���\n");
  printf("xmlbuffer     ���������еĲ��������£�\n");
  printf("server ip     ����˵�IP��ַ��\n");
  printf("server port   ����˵Ķ˿ڡ�\n");
  printf("ptype         �ļ��ϴ��ɹ���Ĵ���ʽ��1-ɾ���ļ���2-�ƶ�������Ŀ¼��\n");
  printf("clientpath    �����ļ���ŵĸ�Ŀ¼��\n");
  printf("clientpathbak �ļ��ɹ��ϴ��󣬱����ļ����ݵĸ�Ŀ¼����ptype==2ʱ��Ч��\n");
  printf("andchild      �Ƿ��ϴ�clientpathĿ¼�¸�����Ŀ¼���ļ���true-�ǣ�false-��ȱʡΪfalse��\n");
  printf("matchname     ���ϴ��ļ�����ƥ�������\"*.TXT,*.XML\"\n");
  printf("srvpath       ������ļ���ŵĸ�Ŀ¼��\n");
  printf("timetvl       ɨ�豾��Ŀ¼�ļ���ʱ��������λ���룬ȡֵ��1-30֮�䡣\n");
  printf("timeout       ������ĳ�ʱʱ�䣬��λ���룬���ļ���С����������������������50���ϡ�\n");
  printf("pname         �������������ܲ����׶��ġ����������̲�ͬ�����ƣ���������Ų顣\n\n");
  
  //printf("test!!!!!!!!");
}

// ��xml����������starg�ṹ
bool _xmltoArg(char *strxmlBuffer)
{
  memset(&starg,0,sizeof(struct st_arg));

  GetXMLBuffer(strxmlBuffer,"ip",starg.ip);
  if (strlen(starg.ip)==0) { logfile.Write("ip is null.\n"); return false; }

  GetXMLBuffer(strxmlBuffer,"port",&starg.port);
  if ( starg.port==0) { logfile.Write("port is null.\n"); return false; }

  GetXMLBuffer(strxmlBuffer,"ptype",&starg.ptype);
  if ((starg.ptype!=1)&&(starg.ptype!=2)) { logfile.Write("ptype not in (1,2).\n"); return false; }

  GetXMLBuffer(strxmlBuffer,"clientpath",starg.clientpath);
  if (strlen(starg.clientpath)==0) { logfile.Write("clientpath is null.\n"); return false; }

  GetXMLBuffer(strxmlBuffer,"clientpathbak",starg.clientpathbak);
  if ((starg.ptype==2)&&(strlen(starg.clientpathbak)==0)) { logfile.Write("clientpathbak is null.\n"); return false; }

  GetXMLBuffer(strxmlBuffer,"andchild",&starg.andchild);

  GetXMLBuffer(strxmlBuffer,"matchname",starg.matchname);
  if (strlen(starg.matchname)==0) { logfile.Write("matchname is null.\n"); return false; }

  GetXMLBuffer(strxmlBuffer,"srvpath",starg.srvpath);
  if (strlen(starg.srvpath)==0) { logfile.Write("srvpath is null.\n"); return false; }

  GetXMLBuffer(strxmlBuffer,"timetvl",&starg.timetvl);
  if (starg.timetvl==0) { logfile.Write("timetvl is null.\n"); return false; }

  // ɨ�豾��Ŀ¼�ļ���ʱ��������λ���롣
  // starg.timetvlû�б�Ҫ����30�롣
  if (starg.timetvl>30) starg.timetvl=30;

  // ���������ĳ�ʱʱ�䣬һ��Ҫ����starg.timetvl��û�б�ҪС��50�롣
  GetXMLBuffer(strxmlBuffer,"timeout",&starg.timeout);
  if (starg.timeout==0) { logfile.Write("timeout is null.\n"); return false; }
  if (starg.timeout<50) starg.timeout=50;

  GetXMLBuffer(strxmlBuffer,"pname",starg.pname,50);
  if (strlen(starg.pname)==0) { logfile.Write("pname is null.\n"); return false; }

  return true;
}
