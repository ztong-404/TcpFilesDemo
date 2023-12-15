/*
 * ��������fileServer.cpp���ļ�����ķ���ˡ�
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
  char srvpathbak[301];     // ������ļ���ŵĸ�Ŀ¼��
  int timetvl;              //ɨ�豾��Ŀ¼�ļ���ʱ��������λ����              
  int timeout;              //���������ĳ�ʱʱ��
  char pname[51];           //�������������á�tcpgetfiles_��׺���ķ�ʽ
} starg;

//��xml����������starg�ṹ��
bool _xmltoArg(char *str_xmlBuffer);

CLogFile logfile;//����������־
CTcpServer TcpServer; //��������˶���

void FathEXIT(int sig); //�������˳�����
void ChldEXIT(int sig); //�ӽ����˳�����

char strRecvBuffer[1024]; //���ͱ��ĵ�buffer
char strSendBuffer[1024]; //���ձ��ĵ�buffer

// �ļ����ص���������ִ��һ���ļ����ص�����
bool _tcpputfiles();
bool bcontinue=true;   // �������_tcpputfiles�������ļ���bcontinueΪtrue����ʼ��Ϊtrue��

// ���ļ������ݷ��͸��Զˡ�
bool SendFile(const int sockfd,const char *filename,const int filesize);

// ɾ������ת�汾�ص��ļ���
bool AckMessage(const char *strRecvBuffer);

// ��¼ҵ��������
bool ClientLogin();

// �ϴ��ļ�����������
void RecvFilesMain();

// �����ļ�����������
void SendFilesMain();

bool ActiveTest();    // ������

// �����ļ������ݡ�
bool RecvFile(const int sockfd,const char *filename,const char *mtime,int filesize);

CPActive PActive;  // ����������


int main(int argc,char *argv[])
{
  if (argc!=3)
  {
    printf("Using:./fileServer port logfile\n"); 
    printf("Example:./fileServer 5005 /home/mininet/demo/net/tcpFiles/fileserver.log\n"); 
    printf("         /project/tools1/bin/procctl 10 /project/tools1/bin/fileserver 5005 /log/idc/fileserver.log\n\n\n");
    return -1;
  }
  
  //�ر�ȫ�����źź��������
  //�����źţ���shell״̬�¿��á�kill+���̺š�������ֹ��Щ����
  //CloseIOAndSignal();signal(SIGINT,FathEXIT); signal(SIGTERM,FathEXIT);
   
   if(logfile.Open(argv[2],"a+")==false)
   {
     printf("logfile.Open(%s) failed.\n",argv[2]);
     return -1;
   }
   
   //����˳�ʼ��
   if(TcpServer.InitServer(atoi(argv[1]))==false)
   {
     logfile.Write("TcpServer.InitServer(%s) failed.\n",argv[1]);
     return -1;
   }
   
   while(true)
   {
     //�ȴ��ͻ��˵���������
     if(TcpServer.Accept()==false)
     {
       logfile.Write("TcpServer.Accept() failed.\n");
       FathEXIT(-1);
     }  
 
     logfile.Write("client(%s) connected. \n",TcpServer.GetIP());
     
      if (fork()>0) { TcpServer.CloseClient(); continue; }  // �����̼����ص�Accept()��
   
      // �ӽ������������˳��źš�
      signal(SIGINT,ChldEXIT); signal(SIGTERM,ChldEXIT);

      TcpServer.CloseListen();
     
     //�����¼�ͻ��˵ĵ�¼����
     if(ClientLogin()==false) ChldEXIT(-1);
     
     
     //���clienttype==1�������ϴ��ļ���������
     if(starg.clienttype==1) RecvFilesMain();
     
     
     //���clienttype==2�����������ļ���������
     if (starg.clienttype==2) SendFilesMain();
  
    ChldEXIT(0);
  }
}

void FathEXIT(int sig) //�������˳�����
{
  //���´�����Ϊ�˷�ֹ�źŴ�������ִ�еĹ����б��ź��жϡ�
  signal(SIGINT,SIG_IGN);
  signal(SIGTERM,SIG_IGN);
  logfile.Write("Fath proc exit.sig=%d\n",sig);
  TcpServer.CloseListen(); //�رռ�����socket
  kill(0,15);  //֪ͨȫ�����ӽ����˳�
  exit(0);
}

void ChldEXIT(int sig) //�ӽ����˳�����
{
//���´�����Ϊ�˷�ֹ�źŴ�������ִ�еĹ����б��ź��жϡ�
  signal(SIGINT,SIG_IGN);
  signal(SIGTERM,SIG_IGN);
  logfile.Write("Chld proc exit. sig=%d\n",sig);
  TcpServer.CloseClient(); //�رտͻ��˵�socket
  exit(0);
}

//��¼
bool ClientLogin()
{
  memset(strSendBuffer,0,sizeof(strSendBuffer));
  memset(strRecvBuffer,0,sizeof(strRecvBuffer));

  if(TcpServer.Read(strRecvBuffer,20)==false)
  {
    logfile.Write("ClientLoing().TcpServer.Read() failed.\n");
    return false;
  }
  logfile.Write("ClientLogin().strRecvBuffer=%s\n",strRecvBuffer);
  //�����ͻ��˵�¼����
  _xmltoArg(strRecvBuffer);
  logfile.Write("test here.........................\n");
  logfile.Write("starg.clienttype: %d\n",starg.clienttype);
  if((starg.clienttype!=1)&&(starg.clienttype!=2))
    strcpy(strSendBuffer,"failed");
  else
    strcpy(strSendBuffer,"ok");
  
  //logfile.Write("starg.clienttype: %s\n",starg.clienttype);
  
  
  if(TcpServer.Write(strSendBuffer)==false)
  {
    logfile.Write("ClientLogin().TcpServer.Write() failed.\n");
    return false;
  }
  logfile.Write("%s login %s .\n", TcpServer.GetIP(),strSendBuffer);
  
  return true;
}

//��xml����������starg�ṹ��
bool _xmltoArg(char *strxmlBuffer)
{
  memset(&starg,0,sizeof(struct st_arg));
  
  GetXMLBuffer(strxmlBuffer,"clienttype", &starg.clienttype);
  GetXMLBuffer(strxmlBuffer,"ptype",&starg.ptype);
  GetXMLBuffer(strxmlBuffer,"clientpath",starg.clientpath);
  GetXMLBuffer(strxmlBuffer,"andchild",&starg.andchild);
  GetXMLBuffer(strxmlBuffer,"matchname",starg.matchname);
  GetXMLBuffer(strxmlBuffer,"srvpath",starg.srvpath);

  GetXMLBuffer(strxmlBuffer,"timetvl",&starg.timetvl);
  if(starg.timetvl>30) starg.timetvl=30;
  
  GetXMLBuffer(strxmlBuffer,"timeout",&starg.timeout);
  if(starg.timeout<50) starg.timeout=50;
  
  GetXMLBuffer(strxmlBuffer,"pname",starg.pname,50);
  strcat(starg.pname,"_srv");
  
  return true;
}



// �ϴ��ļ�����������
void RecvFilesMain()
{
  PActive.AddPInfo(starg.timeout,starg.pname);

  while (true)
  {
    memset(strSendBuffer,0,sizeof(strSendBuffer));
    memset(strRecvBuffer,0,sizeof(strRecvBuffer));

    PActive.UptATime();

    // ���տͻ��˵ı��ġ�
    // �ڶ���������ȡֵ�������starg.timetvl��С��starg.timeout��
    if (TcpServer.Read(strRecvBuffer,starg.timetvl+10)==false)
    {
      logfile.Write("RecvFilesMain().starg.timetvl=%s.\n",starg.timetvl); 
      logfile.Write("RecvFilesMain().TcpServer.Read() failed.\n"); 
      logfile.Write("RecvFilesMain().strRecvBuffer=%s\n",strRecvBuffer);return;
    }else{
      logfile.Write("RecvFilesMain().strRecvBuffer=%s\n",strRecvBuffer);
      logfile.Write("RecvFilesMain().Read01() success\n");
    }

    // �����������ġ�
    if (strcmp(strRecvBuffer,"<activetest>ok</activetest>")==0)
    {
      strcpy(strSendBuffer,"ok");
      logfile.Write("RecvFilesMain()test.ok\n");
      if (TcpServer.Write(strSendBuffer)==false)
      {
        logfile.Write("RecvFilesMain().RecvFilesMain().TcpServer.Write() failed.\n"); return;
      }
    }

    // �����ϴ��ļ��������ġ�
    if (strncmp(strRecvBuffer,"<filename>",10)==0)
    {
      logfile.Write("<filename>\n");
      // �����ϴ��ļ������ĵ�xml��
      char clientfilename[301];  memset(clientfilename,0,sizeof(clientfilename));
      char mtime[21];            memset(mtime,0,sizeof(mtime));
      int  filesize=0;
      GetXMLBuffer(strRecvBuffer,"filename",clientfilename,300);
      GetXMLBuffer(strRecvBuffer,"mtime",mtime,19);
      GetXMLBuffer(strRecvBuffer,"size",&filesize);

      // �ͻ��˺ͷ�����ļ���Ŀ¼�ǲ�һ���ģ����´������ɷ���˵��ļ�����
      // ���ļ����е�clientpath�滻��srvpath��ҪС�ĵ���������
      char serverfilename[301];  memset(serverfilename,0,sizeof(serverfilename));
      strcpy(serverfilename,clientfilename);
      UpdateStr(serverfilename,starg.clientpath,starg.srvpath,false);

      // �����ļ������ݡ�
      logfile.Write("recv %s(%d) ...",serverfilename,filesize);
      if (RecvFile (TcpServer.m_connfd,serverfilename,mtime,filesize)==true)
      {
        logfile.WriteEx("ok.\n");
        SNPRINTF(strSendBuffer,sizeof(strSendBuffer),1000,"<filename>%s</filename><result>ok</result>",clientfilename);
      }
      else
      {
        logfile.WriteEx("failed.\n");
        SNPRINTF(strSendBuffer,sizeof(strSendBuffer),1000,"<filename>%s</filename><result>failed</result>",clientfilename);
      }

      // �ѽ��ս�����ظ��Զˡ�
      // logfile.Write("strSendBuffer=%s\n",strSendBuffer);
      if (TcpServer.Write(strSendBuffer)==false)
      {
        logfile.Write("TcpServer.Write() failed.\n"); return;
      }
    }
  }
}

// �����ļ������ݡ�
bool RecvFile(const int sockfd,const char *filename,const char *mtime,int filesize)
{
  // ������ʱ�ļ�����
  char strfilenametmp[301];
  SNPRINTF(strfilenametmp,sizeof(strfilenametmp),300,"%s.tmp",filename);

  int  totalbytes=0;        // �ѽ����ļ������ֽ�����
  int  onread=0;            // ���δ�����յ��ֽ�����
  char buffer[1000];        // �����ļ����ݵĻ�������
  FILE *fp=NULL;

  // ������ʱ�ļ���
  if ( (fp=FOPEN(strfilenametmp,"wb"))==NULL ) return false;

  while (true)
  {
    memset(buffer,0,sizeof(buffer));

    // ���㱾��Ӧ�ý��յ��ֽ�����
    if (filesize-totalbytes>1000) onread=1000;
    else onread=filesize-totalbytes;

    // �����ļ����ݡ�
    if (Readn(sockfd,buffer,onread)==false) { fclose(fp); return false; }

    // �ѽ��յ�������д���ļ���
    fwrite(buffer,1,onread,fp);

    // �����ѽ����ļ������ֽ���������ļ������꣬����ѭ����
    totalbytes=totalbytes+onread;

    if (totalbytes==filesize) break;
  }

  // �ر���ʱ�ļ���
  fclose(fp);

  // �����ļ���ʱ�䡣
  UTime(strfilenametmp,mtime);

  // ����ʱ�ļ�RENAMEΪ��ʽ���ļ���
  if (RENAME(strfilenametmp,filename)==false) return false;

  return true;
}

// �����ļ�����������
void SendFilesMain()
{
  PActive.AddPInfo(starg.timeout,starg.pname);

  while (true)
  {
    // �����ļ����ص���������ִ��һ���ļ����ص�����
    if (_tcpputfiles()==false) { logfile.Write("_tcpputfiles() failed.\n"); return; }

    if (bcontinue==false)
    {
      sleep(starg.timetvl);

      if (ActiveTest()==false) break;
    }

    PActive.UptATime();
  }
}

// ������
bool ActiveTest()
{
  memset(strSendBuffer,0,sizeof(strSendBuffer));
  memset(strRecvBuffer,0,sizeof(strRecvBuffer));

  SPRINTF(strSendBuffer,sizeof(strSendBuffer),"<activetest>ok</activetest>");
  // logfile.Write("���ͣ�%s\n",strSendBuffer);
  if (TcpServer.Write(strSendBuffer)==false) return false; // �����˷��������ġ�

  if (TcpServer.Read(strRecvBuffer,20)==false) return false; // ���շ���˵Ļ�Ӧ���ġ�
  // logfile.Write("���գ�%s\n",strRecvBuffer);

  return true;
}

// �ļ����ص���������ִ��һ���ļ����ص�����
bool _tcpputfiles()
{
  CDir Dir;

  // ����OpenDir()��starg.srvpathĿ¼��
  if (Dir.OpenDir(starg.srvpath,starg.matchname,10000,starg.andchild)==false)
  {
    logfile.Write("Dir.OpenDir(%s) ʧ�ܡ�\n",starg.srvpath); return false;
  }

  int delayed=0;        // δ�յ��Զ�ȷ�ϱ��ĵ��ļ�������
  int buflen=0;         // ���ڴ��strRecvBuffer�ĳ��ȡ�

  bcontinue=false;

  while (true)
  {
    memset(strSendBuffer,0,sizeof(strSendBuffer));
    memset(strRecvBuffer,0,sizeof(strRecvBuffer));

    // ����Ŀ¼�е�ÿ���ļ�������ReadDir()��ȡһ���ļ�����
    if (Dir.ReadDir()==false) break;

    bcontinue=true;

    // ���ļ������޸�ʱ�䡢�ļ���С��ɱ��ģ����͸��Զˡ�
    SNPRINTF(strSendBuffer,sizeof(strSendBuffer),1000,"<filename>%s</filename><mtime>%s</mtime><size>%d</size>",Dir.m_FullFileName,Dir.m_ModifyTime,Dir.m_FileSize);

    // logfile.Write("strSendBuffer=%s\n",strSendBuffer);
    if (TcpServer.Write(strSendBuffer)==false)
    {
      logfile.Write("TcpServer.Write() failed.\n"); return false;
    }

    // ���ļ������ݷ��͸��Զˡ�
    logfile.Write("send %s(%d) ...",Dir.m_FullFileName,Dir.m_FileSize);
    if (SendFile(TcpServer.m_connfd,Dir.m_FullFileName,Dir.m_FileSize)==true)
    {
      logfile.WriteEx("ok.\n"); delayed++;
    }
    else
    {
      logfile.WriteEx("failed.\n"); TcpServer.CloseClient(); return false;
    }

    PActive.UptATime();

    // ���նԶ˵�ȷ�ϱ��ġ�
    while (delayed>0)
    {
      memset(strRecvBuffer,0,sizeof(strRecvBuffer));
      if (TcpRead(TcpServer.m_connfd,strRecvBuffer,&buflen,-1)==false) break;
      // logfile.Write("strRecvBuffer=%s\n",strRecvBuffer);

      // ɾ������ת�汾�ص��ļ���
      delayed--;
      AckMessage(strRecvBuffer);
    }
  }

  // �������նԶ˵�ȷ�ϱ��ġ�
  while (delayed>0)
  {
    memset(strRecvBuffer,0,sizeof(strRecvBuffer));
    if (TcpRead(TcpServer.m_connfd,strRecvBuffer,&buflen,10)==false) break;
    // logfile.Write("strRecvBuffer=%s\n",strRecvBuffer);

    // ɾ������ת�汾�ص��ļ���
    delayed--;
    AckMessage(strRecvBuffer);
  }

  return true;
}

// ���ļ������ݷ��͸��Զˡ�
bool SendFile(const int sockfd,const char *filename,const int filesize)
{
  int  onread=0;        // ÿ�ε���freadʱ�����ȡ���ֽ�����
  int  bytes=0;         // ����һ��fread���ļ��ж�ȡ���ֽ�����
  char buffer[1000];    // ��Ŷ�ȡ���ݵ�buffer��
  int  totalbytes=0;    // ���ļ����Ѷ�ȡ���ֽ�������
  FILE *fp=NULL;

  // ��"rb"��ģʽ���ļ���
  if ( (fp=fopen(filename,"rb"))==NULL )  return false;

  while (true)
  {
    memset(buffer,0,sizeof(buffer));

    // ���㱾��Ӧ�ö�ȡ���ֽ��������ʣ������ݳ���1000�ֽڣ��ʹ����1000�ֽڡ�
    if (filesize-totalbytes>1000) onread=1000;
    else onread=filesize-totalbytes;

    // ���ļ��ж�ȡ���ݡ�
    bytes=fread(buffer,1,onread,fp);

    // �Ѷ�ȡ�������ݷ��͸��Զˡ�
    if (bytes>0)
    {
      if (Writen(sockfd,buffer,bytes)==false) { fclose(fp); return false; }
    }

    // �����ļ��Ѷ�ȡ���ֽ�����������ļ��Ѷ��꣬����ѭ����
    totalbytes=totalbytes+bytes;

    if (totalbytes==filesize) break;
  }

  fclose(fp);

  return true;
}

// ɾ������ת�汾�ص��ļ���
bool AckMessage(const char *strRecvBuffer)
{
  char filename[301];
  char result[11];

  memset(filename,0,sizeof(filename));
  memset(result,0,sizeof(result));

  GetXMLBuffer(strRecvBuffer,"filename",filename,300);
  GetXMLBuffer(strRecvBuffer,"result",result,10);

  // �������˽����ļ����ɹ���ֱ�ӷ��ء�
  if (strcmp(result,"ok")!=0) return true;

  // ptype==1��ɾ���ļ���
  if (starg.ptype==1)
  {
    if (REMOVE(filename)==false) { logfile.Write("REMOVE(%s) failed.\n",filename); return false; }
  }

  // ptype==2���ƶ�������Ŀ¼��
  if (starg.ptype==2)
  {
    // ����ת���ı���Ŀ¼�ļ�����
    char bakfilename[301];
    STRCPY(bakfilename,sizeof(bakfilename),filename);
    UpdateStr(bakfilename,starg.srvpath,starg.srvpathbak,false);
    if (RENAME(filename,bakfilename)==false)
    { logfile.Write("RENAME(%s,%s) failed.\n",filename,bakfilename); return false; }
  }

  return true;
}





