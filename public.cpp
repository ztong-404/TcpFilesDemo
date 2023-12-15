/*****************************************************************************************/
/*   ��������public.cpp���˳����ǿ�����ܹ��ú�������Ķ����ļ���                       */
/*****************************************************************************************/

#include "public.h"  

// ��ȫ��strcpy������
// dest��Ŀ���ַ���������Ҫ��ʼ������STRCPY�������г�ʼ�����롣
// destlen��Ŀ���ַ���destռ���ڴ�Ĵ�С��
// src��ԭ�ַ�����
// ����ֵ��Ŀ���ַ���dest�ĵ�ַ��
// ע�⣬����dest���������ݽ�������
char *STRCPY(char* dest,const size_t destlen,const char* src)
{
  if (dest==0) return 0;    // �жϿ�ָ�롣
  memset(dest,0,destlen);   // ��ʼ��dest��
  // memset(dest,0,sizeof(dest));   // ������ôд����64λϵͳ�У�sizeof(dest)��Զ��8��
  if (src==0) return dest;

  if (strlen(src)>destlen-1) strncpy(dest,src,destlen-1); 
  else strcpy(dest,src);

  return dest;
}

// ��ȫ��strncpy������
// dest��Ŀ���ַ���������Ҫ��ʼ������STRCPY�������г�ʼ�����롣
// destlen��Ŀ���ַ���destռ���ڴ�Ĵ�С��
// src��ԭ�ַ�����
// n�������Ƶ��ֽ�����
// ����ֵ��Ŀ���ַ���dest�ĵ�ַ��
// ע�⣬����dest���������ݽ�������
char *STRNCPY(char* dest,const size_t destlen,const char* src,size_t n)
{
  if (dest==0) return 0;    // �жϿ�ָ�롣
  memset(dest,0,destlen);   // ��ʼ��dest��
  // memset(dest,0,sizeof(dest));   // ������ôд����64λϵͳ�У�sizeof(dest)��Զ��8��
  if (src==0) return dest;

  if (n>destlen-1) strncpy(dest,src,destlen-1); 
  else strncpy(dest,src,n);

  return dest;
}

// ��ȫ��strcat������
// dest��Ŀ���ַ�����ע�⣬���dest��δʹ������ô��Ҫ����һ�γ�ʼ����
// destlen��Ŀ���ַ���destռ���ڴ�Ĵ�С��
// src����׷���ַ�����
// ����ֵ��Ŀ���ַ���dest�ĵ�ַ��
// ע�⣬����dest���������ݽ�������
char *STRCAT(char* dest,const size_t destlen,const char* src)
{
  if (dest==0) return 0;    // �жϿ�ָ�롣
  if (src==0) return dest;

  unsigned int left=destlen-1-strlen(dest);

  if (strlen(src)>left) { strncat(dest,src,left); dest[destlen-1]=0; }
  else strcat(dest,src);

  return dest;
}

// ��ȫ��strncat������
// dest��Ŀ���ַ�����ע�⣬���dest��δʹ������ô��Ҫ����һ�γ�ʼ����
// destlen��Ŀ���ַ���destռ���ڴ�Ĵ�С��
// src����׷���ַ�����
// n����׷�ӵ��ֽ�����
// ����ֵ��Ŀ���ַ���dest�ĵ�ַ��
// ע�⣬����dest���������ݽ�������
char *STRNCAT(char* dest,const size_t destlen,const char* src,size_t n)
{
  if (dest==0) return 0;    // �жϿ�ָ�롣
  if (src==0) return dest;

  size_t left=destlen-1-strlen(dest);

  if (n>left) { strncat(dest,src,left); dest[destlen-1]=0; }
  else strncat(dest,src,n);

  return dest;
}

// ��ȫ��sprintf������
// ���ɱ����(...)����fmt�����ĸ�ʽ�����dest�ַ����С�
// dest������ַ���������Ҫ��ʼ������SPRINTF�����л�������г�ʼ����
// destlen������ַ���destռ���ڴ�Ĵ�С�������ʽ������ַ������ݵĳ��ȴ���destlen-1����������ݽ�������
// fmt����ʽ����������
// ...����䵽��ʽ��������fmt�еĲ�����
// ����ֵ����ʽ��������ݵĳ��ȣ�����Աһ�㲻���ķ���ֵ��
int SPRINTF(char *dest,const size_t destlen,const char *fmt,...)
{
  if (dest==0) return -1;    // �жϿ�ָ�롣

  memset(dest,0,destlen);
  // memset(dest,0,sizeof(dest));   // ������ôд����64λϵͳ�У�sizeof(dest)��Զ��8��

  va_list arg;
  va_start(arg,fmt);
  int ret=vsnprintf(dest,destlen,fmt,arg );
  va_end(arg);

  return ret;
}

// ��ȫ��snprintf������
// ���ɱ����(...)����fmt�����ĸ�ʽ�����dest�ַ����С�
// dest������ַ���������Ҫ��ʼ������SNPRINTF�����л�������г�ʼ����
// destlen������ַ���destռ���ڴ�Ĵ�С�������ʽ������ַ������ݵĳ��ȴ���destlen-1����������ݽ�������
// n���Ѹ�ʽ������ַ�����ȡn-1��ŵ�dest�У����n>destlen����ȡdestlen-1��
// fmt����ʽ����������
// ...����䵽��ʽ��������fmt�еĲ�����
// ����ֵ����ʽ��������ݵĳ��ȣ�����Աһ�㲻���ķ���ֵ��
int SNPRINTF(char *dest,const size_t destlen,size_t n,const char *fmt,...)
{
  if (dest==0) return -1;    // �жϿ�ָ�롣

  memset(dest,0,destlen);
  // memset(dest,0,sizeof(dest));   // ������ôд����64λϵͳ�У�sizeof(dest)��Զ��8��

  int len=n;
  if (n>destlen) len=destlen;

  va_list arg;
  va_start(arg,fmt);
  int ret=vsnprintf(dest,len,fmt,arg );
  va_end(arg);

  return ret;
}

// ɾ���ַ������ָ�����ַ���
// str����������ַ�����
// chr����Ҫɾ�����ַ���
void DeleteLChar(char *str,const char chr)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;

  char strTemp[strlen(str)+1];

  int iTemp=0;

  memset(strTemp,0,sizeof(strTemp));
  strcpy(strTemp,str);

  while ( strTemp[iTemp] == chr )  iTemp++;

  memset(str,0,strlen(str)+1);

  strcpy(str,strTemp+iTemp);

  return;
}

// ɾ���ַ����ұ�ָ�����ַ���
// str����������ַ�����
// chr����Ҫɾ�����ַ���
void DeleteRChar(char *str,const char chr)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;

  int istrlen = strlen(str);

  while (istrlen>0)
  {
    if (str[istrlen-1] != chr) break;

    str[istrlen-1]=0;

    istrlen--;
  }
}

// ɾ���ַ�����������ָ�����ַ���
// str����������ַ�����
// chr����Ҫɾ�����ַ���
void DeleteLRChar(char *str,const char chr)
{
  DeleteLChar(str,chr);
  DeleteRChar(str,chr);
}

// ���ַ����е�Сд��ĸת���ɴ�д�����Բ�����ĸ���ַ���
// str����ת�����ַ�����֧��char[]��string�������͡�
void ToUpper(char *str)
{
  if (str == 0) return;

  if (strlen(str) == 0) return;

  int istrlen=strlen(str);

  for (int ii=0;ii<istrlen;ii++)
  {
    if ( (str[ii] >= 'a') && (str[ii] <= 'z') ) str[ii]=str[ii] - 32;
  }
}

void ToUpper(string &str)
{
  if (str.empty()) return;

  char strtemp[str.size()+1];

  STRCPY(strtemp,sizeof(strtemp),str.c_str());

  ToUpper(strtemp);

  str=strtemp;

  return;
}

// ���ַ����еĴ�д��ĸת����Сд�����Բ�����ĸ���ַ���
// str����ת�����ַ�����֧��char[]��string�������͡�
void ToLower(char *str)
{
  if (str == 0) return;

  if (strlen(str) == 0) return;

  int istrlen=strlen(str);

  for (int ii=0;ii<istrlen;ii++)
  {
    if ( (str[ii] >= 'A') && (str[ii] <= 'Z') ) str[ii]=str[ii] + 32;
  }
}

void ToLower(string &str)
{
  if (str.empty()) return;

  char strtemp[str.size()+1];

  STRCPY(strtemp,sizeof(strtemp),str.c_str());

  ToLower(strtemp);

  str=strtemp;

  return;
}

// �ַ����滻����
// ���ַ���str�У���������ַ���str1�����滻Ϊ�ַ���str2��
// str����������ַ�����
// str1���ɵ����ݡ�
// str2���µ����ݡ�
// bloop���Ƿ�ѭ��ִ���滻��
// ע�⣺
// 1�����str2��str1Ҫ�����滻��str��䳤�����Ա��뱣֤str���㹻�ĳ��ȣ������ڴ�������
// 2�����str2�а�����str1�����ݣ���bloopΪtrue�������߼����󣬽���ִ���κ��滻��
void UpdateStr(char *str,const char *str1,const char *str2,bool bloop)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;
  if ( (str1 == 0) || (str2 == 0) ) return;

  // ���bloopΪtrue����str2�а�����str1�����ݣ�ֱ�ӷ��أ���Ϊ�������ѭ�������յ����ڴ������
  if ( (bloop==true) && (strstr(str2,str1)>0) ) return;

  // �����ܷ������Ŀռ䣬�����п��ܳ����ڴ���������������Ż���string��
  int ilen=strlen(str)*10;
  if (ilen<1000) ilen=1000;

  char strTemp[ilen];

  char *strStart=str;

  char *strPos=0;

  while (true)
  {
    if (bloop == true)
    {
      strPos=strstr(str,str1);
    }
    else
    {
      strPos=strstr(strStart,str1);
    }

    if (strPos == 0) break;

    memset(strTemp,0,sizeof(strTemp));
    STRNCPY(strTemp,sizeof(strTemp),str,strPos-str);
    STRCAT(strTemp,sizeof(strTemp),str2);
    STRCAT(strTemp,sizeof(strTemp),strPos+strlen(str1));
    strcpy(str,strTemp);

    strStart=strPos+strlen(str2);
  }
}

// ��һ���ַ�������ȡ�����ֵ����ݣ���ŵ���һ���ַ����С�
// src��Դ�ַ�����
// dest��Ŀ���ַ�����
// bsigned���Ƿ�������ţ�+��-����true-������false-��������
// bdot���Ƿ����С�����Բ����ţ�true-������false-��������
void PickNumber(const char *src,char *dest,const bool bsigned,const bool bdot)
{
  if (dest==0) return;    // �жϿ�ָ�롣
  if (src==0) { strcpy(dest,""); return; }

  char strtemp[strlen(src)+1];
  memset(strtemp,0,sizeof(strtemp));
  strcpy(strtemp,src);
  DeleteLRChar(strtemp,' ');

  int ipossrc,iposdst,ilen;
  ipossrc=iposdst=ilen=0;

  ilen=strlen(strtemp);

  for (ipossrc=0;ipossrc<ilen;ipossrc++)
  {
    if ( (bsigned==true) && (strtemp[ipossrc] == '+') )
    {
      dest[iposdst++]=strtemp[ipossrc]; continue;
    }

    if ( (bsigned==true) && (strtemp[ipossrc] == '-') )
    {
      dest[iposdst++]=strtemp[ipossrc]; continue;
    }

    if ( (bdot==true) && (strtemp[ipossrc] == '.') )
    {
      dest[iposdst++]=strtemp[ipossrc]; continue;
    }

    if (isdigit(strtemp[ipossrc])) dest[iposdst++]=strtemp[ipossrc];
  }

  dest[iposdst]=0;
}

// ������ʽ���ж�һ���ַ����Ƿ�ƥ����һ���ַ�����
// str����Ҫ�жϵ��ַ�������ȷ��ʾ���ַ��������ļ���"_public.cpp"��
// rules��ƥ�������ʽ�����Ǻ�"*"��ʾ�����ַ���������ַ���֮���ð�ǵĶ��ŷָ�����"*.h,*.cpp"��
// ע�⣬str������֧��"*"��rules����֧��"*"���������ж�str�Ƿ�ƥ��rules��ʱ�򣬻������ĸ�Ĵ�Сд��
bool MatchStr(const string &str,const string &rules)
{
  // ������ڱȽϵ��ַ��ǿյģ�����false
  if (rules.size() == 0) return false;

  // ������Ƚϵ��ַ�����"*"������true
  if (rules == "*") return true;

  int ii,jj;
  int  iPOS1,iPOS2;
  CCmdStr CmdStr,CmdSubStr;

  string strFileName,strMatchStr;

  strFileName=str;
  strMatchStr=rules;

  // ���ַ�����ת���ɴ�д�������Ƚ�
  ToUpper(strFileName);
  ToUpper(strMatchStr);

  CmdStr.SplitToCmd(strMatchStr,",");

  for (ii=0;ii<CmdStr.CmdCount();ii++)
  {
    // ���Ϊ�գ���һ��Ҫ����������ͻᱻ����
    if (CmdStr.m_vCmdStr[ii].empty() == true) continue;

    iPOS1=iPOS2=0;
    CmdSubStr.SplitToCmd(CmdStr.m_vCmdStr[ii],"*");

    for (jj=0;jj<CmdSubStr.CmdCount();jj++)
    {
      // ������ļ������ײ�
      if (jj == 0)
      {
        if (strncmp(strFileName.c_str(),CmdSubStr.m_vCmdStr[jj].c_str(),CmdSubStr.m_vCmdStr[jj].size()) != 0) break;
      }

      // ������ļ�����β��
      if (jj == CmdSubStr.CmdCount()-1)
      {
        if (strcmp(strFileName.c_str()+strFileName.size()-CmdSubStr.m_vCmdStr[jj].size(),CmdSubStr.m_vCmdStr[jj].c_str()) != 0) break;
      }

      iPOS2=strFileName.find(CmdSubStr.m_vCmdStr[jj],iPOS1);

      if (iPOS2 < 0) break;

      iPOS1=iPOS2+CmdSubStr.m_vCmdStr[jj].size();
    }

    if (jj==CmdSubStr.CmdCount()) return true;
  }

  return false;
}

CFile::CFile()   // ��Ĺ��캯��
{
  m_fp=0;
  m_bEnBuffer=true;
  memset(m_filename,0,sizeof(m_filename));
  memset(m_filenametmp,0,sizeof(m_filenametmp));
}

// �ر��ļ�ָ��
void CFile::Close() 
{
  if (m_fp==0) return;    // �жϿ�ָ�롣

  fclose(m_fp);  // �ر��ļ�ָ��

  m_fp=0;
  memset(m_filename,0,sizeof(m_filename));

  // ���������ʱ�ļ�����ɾ������
  if (strlen(m_filenametmp)!=0) remove(m_filenametmp);

  memset(m_filenametmp,0,sizeof(m_filenametmp));
}

// �ж��ļ��Ƿ��Ѵ�
bool CFile::IsOpened()
{
  if (m_fp==0) return false;    // �жϿ�ָ�롣

  return true;
}

// �ر��ļ�ָ�룬��ɾ���ļ�
bool CFile::CloseAndRemove()
{
  if (m_fp==0) return true;    // �жϿ�ָ�롣

  fclose(m_fp);  // �ر��ļ�ָ��

  m_fp=0;

  if (remove(m_filename) != 0) { memset(m_filename,0,sizeof(m_filename)); return false; }

  memset(m_filename,0,sizeof(m_filename));
  memset(m_filenametmp,0,sizeof(m_filenametmp));

  return true;
}

CFile::~CFile()   // �����������
{
  Close();
}

// ���ļ���������FOPEN��ͬ���򿪳ɹ�true��ʧ�ܷ���false
bool CFile::Open(const char *filename,const char *openmode,bool bEnBuffer)
{
  Close();

  if ( (m_fp=FOPEN(filename,openmode)) == 0 ) return false;

  memset(m_filename,0,sizeof(m_filename));

  STRNCPY(m_filename,sizeof(m_filename),filename,300);

  m_bEnBuffer=bEnBuffer;

  return true;
}

// רΪ���������ļ���������fopen��ͬ���򿪳ɹ�true��ʧ�ܷ���false
bool CFile::OpenForRename(const char *filename,const char *openmode,bool bEnBuffer)
{
  Close();

  memset(m_filename,0,sizeof(m_filename));
  STRNCPY(m_filename,sizeof(m_filename),filename,300);
  
  memset(m_filenametmp,0,sizeof(m_filenametmp));
  SNPRINTF(m_filenametmp,sizeof(m_filenametmp),300,"%s.tmp",m_filename);

  if ( (m_fp=FOPEN(m_filenametmp,openmode)) == 0 ) return false;

  m_bEnBuffer=bEnBuffer;

  return true;
}

// �ر��ļ�������
bool CFile::CloseAndRename()
{
  if (m_fp==0) return false;    // �жϿ�ָ�롣

  fclose(m_fp);  // �ر��ļ�ָ��

  m_fp=0;

  if (rename(m_filenametmp,m_filename) != 0)
  {
    remove(m_filenametmp);
    memset(m_filename,0,sizeof(m_filename));
    memset(m_filenametmp,0,sizeof(m_filenametmp));
    return false;
  }

  memset(m_filename,0,sizeof(m_filename));
  memset(m_filenametmp,0,sizeof(m_filenametmp));

  return true;
}

// ����fprintf���ļ�д������
void CFile::Fprintf(const char *fmt,...)
{
  if ( m_fp == 0 ) return;

  va_list arg;
  va_start( arg, fmt );
  vfprintf( m_fp, fmt, arg );
  va_end( arg );

  if ( m_bEnBuffer == false ) fflush(m_fp);
}

// ����fgets���ļ��ж�ȡһ�У�bDelCRT=trueɾ�����з���false��ɾ����ȱʡΪfalse
bool CFile::Fgets(char *buffer,const int readsize,bool bdelcrt)
{
  if ( m_fp == 0 ) return false;

  memset(buffer,0,readsize+1);  // �����߱��뱣֤buffer�Ŀռ��㹻������������ڴ������

  if (fgets(buffer,readsize,m_fp) == 0) return false;

  if (bdelcrt==true)
  {
    DeleteRChar(buffer,'\n'); DeleteRChar(buffer,'\r');  // ����ļ���windows��ʽ����Ҫɾ��'\r'��
  }

  return true;
}

// ���ļ��ļ��ж�ȡһ��
// strEndStr��һ�����ݵĽ�����־�����Ϊ�գ����Ի��з�"\n"Ϊ������־��
bool CFile::FFGETS(char *buffer,const int readsize,const char *endbz)
{
  if ( m_fp == 0 ) return false;

  return FGETS(m_fp,buffer,readsize,endbz);
}

// ����fread���ļ��ж�ȡ���ݡ�
size_t CFile::Fread(void *ptr, size_t size)
{
  if ( m_fp == 0 ) return -1;

  return fread(ptr,1,size,m_fp);
}

// ����fwrite���ļ���д����
size_t CFile::Fwrite(const void *ptr, size_t size )
{
  if ( m_fp == 0 ) return -1;

  size_t tt=fwrite(ptr,1,size,m_fp);

  if ( m_bEnBuffer == false ) fflush(m_fp);

  return tt;
}


// ���ı��ļ��ж�ȡһ�С�
// fp���Ѵ򿪵��ļ�ָ�롣
// buffer�����ڴ�Ŷ�ȡ�����ݡ�
// readsize�����δ����ȡ���ֽ���������Ѿ���ȡ���˽�����־���������ء�
// endbz�������ݽ����ı�־��ȱʡΪ�գ���ʾ��������"\n"Ϊ������־��
// ����ֵ��true-�ɹ���false-ʧ�ܣ�һ������£�ʧ�ܿ�����Ϊ���ļ��ѽ�����
bool FGETS(const FILE *fp,char *buffer,const int readsize,const char *endbz)
{
  if ( fp == 0 ) return false;

  memset(buffer,0,readsize+1);   // �����߱��뱣֤buffer�Ŀռ��㹻������������ڴ������

  char strline[readsize+1];

  while (true)
  {
    memset(strline,0,sizeof(strline));

    if (fgets(strline,readsize,(FILE *)fp) == 0) break;

    // ��ֹbuffer���
    if ( (strlen(buffer)+strlen(strline)) >= (unsigned int)readsize ) break;

    strcat(buffer,strline);

    if (endbz == 0) return true;
    else if (strstr(strline,endbz)!= 0) return true;
    // ���ϴ�����Բ���strstr�������Ż�Ϊֻ�Ƚ��������ݡ�
  }

  return false;
}


CCmdStr::CCmdStr()
{
  m_vCmdStr.clear();
}

CCmdStr::CCmdStr(const string &buffer,const char *sepstr,const bool bdelspace)
{
  m_vCmdStr.clear();

  SplitToCmd(buffer,sepstr,bdelspace);
}

// ���ַ�����ֵ�m_vCmdStr�����С�
// buffer������ֵ��ַ�����
// sepstr��buffer�ַ������ֶ����ݵķָ�����ע�⣬�ָ������ַ�������","��" "��"|"��"~!~"��
// bdelspace���Ƿ�ɾ����ֺ���ֶ�����ǰ��Ŀո�true-ɾ����false-��ɾ����ȱʡ��ɾ����
void CCmdStr::SplitToCmd(const string &buffer,const char *sepstr,const bool bdelspace)
{
  // ������еľ�����
  m_vCmdStr.clear();

  int iPOS=0;
  string srcstr,substr;

  srcstr=buffer;

  while ( (iPOS=srcstr.find(sepstr)) >= 0)
  {
    substr=srcstr.substr(0,iPOS);

    if (bdelspace == true)
    {
      char str[substr.length()+1];
      STRCPY(str,sizeof(str),substr.c_str());

      DeleteLRChar(str,' ');

      substr=str;
    }

    m_vCmdStr.push_back(substr);

    iPOS=iPOS+strlen(sepstr);

    srcstr=srcstr.substr(iPOS,srcstr.size()-iPOS);

  }

  substr=srcstr;

  if (bdelspace == true)
  {
    char str[substr.length()+1];
    STRCPY(str,sizeof(str),substr.c_str());

    DeleteLRChar(str,' ');

    substr=str;
  }

  m_vCmdStr.push_back(substr);

  return;
}

int CCmdStr::CmdCount()
{
  return m_vCmdStr.size();
}

bool CCmdStr::GetValue(const int inum,char *value,const int ilen)
{
  if ( (inum>=(int)m_vCmdStr.size()) || (value==0) ) return false;

  if (ilen>0) memset(value,0,ilen+1);   // �����߱��뱣֤value�Ŀռ��㹻������������ڴ������

  if ( (m_vCmdStr[inum].length()<=(unsigned int)ilen) || (ilen==0) )
  {
    strcpy(value,m_vCmdStr[inum].c_str());
  }
  else
  {
    strncpy(value,m_vCmdStr[inum].c_str(),ilen); value[ilen]=0;
  }

  return true;
}

bool CCmdStr::GetValue(const int inum,int *value)
{
  if ( (inum>=(int)m_vCmdStr.size()) || (value==0) ) return false;

  (*value) = 0;

  if (inum >= (int)m_vCmdStr.size()) return false;

  (*value) = atoi(m_vCmdStr[inum].c_str());

  return true;
}

bool CCmdStr::GetValue(const int inum,unsigned int *value)
{
  if ( (inum>=(int)m_vCmdStr.size()) || (value==0) ) return false;

  (*value) = 0;

  if (inum >= (int)m_vCmdStr.size()) return false;

  (*value) = atoi(m_vCmdStr[inum].c_str());

  return true;
}


bool CCmdStr::GetValue(const int inum,long *value)
{
  if ( (inum>=(int)m_vCmdStr.size()) || (value==0) ) return false;

  (*value) = 0;

  if (inum >= (int)m_vCmdStr.size()) return false;

  (*value) = atol(m_vCmdStr[inum].c_str());

  return true;
}

bool CCmdStr::GetValue(const int inum,unsigned long *value)
{
  if ( (inum>=(int)m_vCmdStr.size()) || (value==0) ) return false;

  (*value) = 0;

  if (inum >= (int)m_vCmdStr.size()) return false;

  (*value) = atol(m_vCmdStr[inum].c_str());

  return true;
}

bool CCmdStr::GetValue(const int inum,double *value)
{
  if ( (inum>=(int)m_vCmdStr.size()) || (value==0) ) return false;

  (*value) = 0;

  if (inum >= (int)m_vCmdStr.size()) return false;

  (*value) = (double)atof(m_vCmdStr[inum].c_str());

  return true;
}

bool CCmdStr::GetValue(const int inum,bool *value)
{
  if ( (inum>=(int)m_vCmdStr.size()) || (value==0) ) return false;

  (*value) = 0;

  if (inum >= (int)m_vCmdStr.size()) return false;

  char strTemp[11];
  memset(strTemp,0,sizeof(strTemp));
  strncpy(strTemp,m_vCmdStr[inum].c_str(),10);

  ToUpper(strTemp);  // ת��Ϊ��д���жϡ�
  if (strcmp(strTemp,"TRUE")==0) (*value)=true; 

  return true;
}

CCmdStr::~CCmdStr()
{
  m_vCmdStr.clear();
}

bool GetXMLBuffer(const char *xmlbuffer,const char *fieldname,char *value,const int ilen)
{
  if (value==0) return false;    // �жϿ�ָ�롣

  if (ilen>0) memset(value,0,ilen+1);   // �����߱��뱣֤value�Ŀռ��㹻������������ڴ������

  char *start=0,*end=0;
  char m_SFieldName[51],m_EFieldName[51];

  int m_NameLen = strlen(fieldname);

  SNPRINTF(m_SFieldName,sizeof(m_SFieldName),50,"<%s>",fieldname);
  SNPRINTF(m_EFieldName,sizeof(m_EFieldName),50,"</%s>",fieldname);

  start=0; end=0;

  start = (char *)strstr(xmlbuffer,m_SFieldName);

  if (start != 0)
  {
    end   = (char *)strstr(start,m_EFieldName);
  }

  if ((start==0) || (end == 0))
  {
    return false;
  }

  int   m_ValueLen = end - start - m_NameLen - 2 ;

  if ( ((m_ValueLen) <= ilen) || (ilen == 0) )
  {
    strncpy(value,start+m_NameLen+2,m_ValueLen); value[m_ValueLen]=0;
  }
  else
  {
    strncpy(value,start+m_NameLen+2,ilen); value[ilen]=0;
  }

  DeleteLRChar(value,' ');

  return true;
}

bool GetXMLBuffer(const char *xmlbuffer,const char *fieldname,bool *value)
{
  if (value==0) return false;    // �жϿ�ָ�롣

  (*value) = false;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXMLBuffer(xmlbuffer,fieldname,strTemp,10) == true)
  {
    ToUpper(strTemp);  // ת��Ϊ��д���жϡ�
    if (strcmp(strTemp,"TRUE")==0) { (*value)=true; return true; }
  }

  return false;
}

bool GetXMLBuffer(const char *xmlbuffer,const char *fieldname,int *value)
{
  if (value==0) return false;    // �жϿ�ָ�롣

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXMLBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = atoi(strTemp); return true;
  }

  return false;
}

bool GetXMLBuffer(const char *xmlbuffer,const char *fieldname,unsigned int *value)
{
  if (value==0) return false;    // �жϿ�ָ�롣

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXMLBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = (unsigned int)atoi(strTemp); return true;
  }

  return false;
}

bool GetXMLBuffer(const char *xmlbuffer,const char *fieldname,long *value)
{
  if (value==0) return false;    // �жϿ�ָ�롣

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXMLBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = atol(strTemp); return true;
  }

  return false;
}

bool GetXMLBuffer(const char *xmlbuffer,const char *fieldname,unsigned long *value)
{
  if (value==0) return false;    // �жϿ�ָ�롣

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXMLBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = (unsigned long)atol(strTemp); return true;
  }

  return false;
}

bool GetXMLBuffer(const char *xmlbuffer,const char *fieldname,double *value)
{
  if (value==0) return false;    // �жϿ�ָ�롣

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXMLBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = atof(strTemp); return true;
  }

  return false;
}

// ��������ʾ��ʱ��ת��Ϊ�ַ�����ʾ��ʱ�䡣
// ltime��������ʾ��ʱ�䡣
// stime���ַ�����ʾ��ʱ�䡣
// fmt������ַ���ʱ��stime�ĸ�ʽ����LocalTime������fmt������ͬ�����fmt�ĸ�ʽ����ȷ��stime��Ϊ�ա�
void timetostr(const time_t ltime,char *stime,const char *fmt)
{
  if (stime==0) return;    // �жϿ�ָ�롣

  strcpy(stime,"");

  struct tm sttm = *localtime ( &ltime );
  // struct tm sttm; localtime_r(&ltime,&sttm); 

  sttm.tm_year=sttm.tm_year+1900;
  sttm.tm_mon++;

  if (fmt==0)
  {
    snprintf(stime,20,"%04u-%02u-%02u %02u:%02u:%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min,sttm.tm_sec);
    return;
  }

  if (strcmp(fmt,"yyyy-mm-dd hh24:mi:ss") == 0)
  {
    snprintf(stime,20,"%04u-%02u-%02u %02u:%02u:%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min,sttm.tm_sec);
    return;
  }

  if (strcmp(fmt,"yyyy-mm-dd hh24:mi") == 0)
  {
    snprintf(stime,17,"%04u-%02u-%02u %02u:%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min);
    return;
  }

  if (strcmp(fmt,"yyyy-mm-dd hh24") == 0)
  {
    snprintf(stime,14,"%04u-%02u-%02u %02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour);
    return;
  }

  if (strcmp(fmt,"yyyy-mm-dd") == 0)
  {
    snprintf(stime,11,"%04u-%02u-%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday); 
    return;
  }

  if (strcmp(fmt,"yyyy-mm") == 0)
  {
    snprintf(stime,8,"%04u-%02u",sttm.tm_year,sttm.tm_mon); 
    return;
  }

  if (strcmp(fmt,"yyyymmddhh24miss") == 0)
  {
    snprintf(stime,15,"%04u%02u%02u%02u%02u%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min,sttm.tm_sec);
    return;
  }

  if (strcmp(fmt,"yyyymmddhh24mi") == 0)
  {
    snprintf(stime,13,"%04u%02u%02u%02u%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min);
    return;
  }

  if (strcmp(fmt,"yyyymmddhh24") == 0)
  {
    snprintf(stime,11,"%04u%02u%02u%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour);
    return;
  }

  if (strcmp(fmt,"yyyymmdd") == 0)
  {
    snprintf(stime,9,"%04u%02u%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday); 
    return;
  }

  if (strcmp(fmt,"hh24miss") == 0)
  {
    snprintf(stime,7,"%02u%02u%02u",sttm.tm_hour,sttm.tm_min,sttm.tm_sec); 
    return;
  }

  if (strcmp(fmt,"hh24mi") == 0)
  {
    snprintf(stime,5,"%02u%02u",sttm.tm_hour,sttm.tm_min); 
    return;
  }

  if (strcmp(fmt,"hh24") == 0)
  {
    snprintf(stime,3,"%02u",sttm.tm_hour); 
    return;
  }

  if (strcmp(fmt,"mi") == 0)
  {
    snprintf(stime,3,"%02u",sttm.tm_min); 
    return;
  }
}


/*
  ȡ����ϵͳ��ʱ�䣬����������ʾ��ʱ��ת��Ϊ�ַ�����ʾ�ĸ�ʽ��
  stime�����ڴ�Ż�ȡ����ʱ���ַ�����
  timetvl��ʱ���ƫ��������λ���룬0��ȱʡֵ����ʾ��ǰʱ�䣬30��ʾ��ǰʱ��30��֮���ʱ��㣬-30��ʾ��ǰʱ��30��֮ǰ��ʱ��㡣
  fmt�����ʱ��ĸ�ʽ��ȱʡ��"yyyy-mm-dd hh24:mi:ss"��Ŀǰ֧�����¸�ʽ��
  "yyyy-mm-dd hh24:mi:ss"���˸�ʽ��ȱʡ��ʽ��
  "yyyymmddhh24miss"
  "yyyy-mm-dd"
  "yyyymmdd"
  "hh24:mi:ss"
  "hh24miss"
  "hh24:mi"
  "hh24mi"
  "hh24"
  "mi"
  ע�⣺
    1��Сʱ�ı�ʾ������hh24������hh����ô����Ŀ����Ϊ�˱��������ݿ��ʱ���ʾ����һ�£�
    2�������г��˳��õ�ʱ���ʽ���������������Ӧ�ÿ������������޸�Դ�������Ӹ���ĸ�ʽ֧�֣�
    3�����ú�����ʱ�����fmt��������ʽ��ƥ�䣬stime�����ݽ�Ϊ�ա�
*/
void LocalTime(char *stime,const char *fmt,const int timetvl)
{
  if (stime==0) return;    // �жϿ�ָ�롣

  time_t  timer;

  time( &timer ); timer=timer+timetvl;

  timetostr(timer,stime,fmt);
}


CLogFile::CLogFile(const long MaxLogSize)
{
  m_tracefp = 0;
  memset(m_filename,0,sizeof(m_filename));
  memset(m_openmode,0,sizeof(m_openmode));
  m_bBackup=true;
  m_bEnBuffer=false;
  m_MaxLogSize=MaxLogSize;
  if (m_MaxLogSize<10) m_MaxLogSize=10;

  // pthread_pin_init(&spin,0);  // ��ѧ��ʱ��Ҫ�������д��롣
}

CLogFile::~CLogFile()
{
  Close();

  // pthread_spin_destroy(&spin);  // ��ѧ��ʱ��Ҫ�������д��롣
}

void CLogFile::Close()
{
  if (m_tracefp != 0) { fclose(m_tracefp); m_tracefp=0; }

  memset(m_filename,0,sizeof(m_filename));
  memset(m_openmode,0,sizeof(m_openmode));
  m_bBackup=true;
  m_bEnBuffer=false;
}

// ����־�ļ���
// filename����־�ļ�����������þ���·��������ļ����е�Ŀ¼�����ڣ����ȴ���Ŀ¼��
// openmode����־�ļ��Ĵ򿪷�ʽ����fopen�⺯�����ļ��ķ�ʽ��ͬ��ȱʡֵ��"a+"��
// bBackup���Ƿ��Զ��л���true-�л���false-���л����ڶ���̵ķ�������У����������й���һ����־�ļ���bBackup����Ϊfalse��
// bEnBuffer���Ƿ������ļ�������ƣ�true-���ã�false-�����ã�������û���������ôд����־�ļ��е����ݲ�������д���ļ���ȱʡ�ǲ����á�
bool CLogFile::Open(const char *filename,const char *openmode,bool bBackup,bool bEnBuffer)
{
  // ����ļ�ָ���Ǵ򿪵�״̬���ȹر�����
  Close();

  STRCPY(m_filename,sizeof(m_filename),filename);
  m_bEnBuffer=bEnBuffer;
  m_bBackup=bBackup;
  if (openmode==0) STRCPY(m_openmode,sizeof(m_openmode),"a+");
  else STRCPY(m_openmode,sizeof(m_openmode),openmode);

  if ((m_tracefp=FOPEN(m_filename,m_openmode)) == 0) return false;

  return true;
}

// �����־�ļ�����100M���Ͱѵ�ǰ����־�ļ����ݳ���ʷ��־�ļ����л��ɹ�����յ�ǰ��־�ļ������ݡ�
// ���ݺ���ļ�������־�ļ������������ʱ�䡣
// ע�⣬�ڶ���̵ĳ����У���־�ļ������л������ߵĳ����У���־�ļ������л���
bool CLogFile::BackupLogFile()
{
  if (m_tracefp == 0) return false;

  // ������
  if (m_bBackup == false) return true;

  //fseek(m_tracefp,0,2);

  if (ftell(m_tracefp) > m_MaxLogSize*1024*1024)
  {
    fclose(m_tracefp); m_tracefp=0;

    char strLocalTime[21];
    memset(strLocalTime,0,sizeof(strLocalTime));
    LocalTime(strLocalTime,"yyyymmddhh24miss");

    char bak_filename[301];
    SNPRINTF(bak_filename,sizeof(bak_filename),300,"%s.%s",m_filename,strLocalTime);
    rename(m_filename,bak_filename);

    if ((m_tracefp=FOPEN(m_filename,m_openmode)) == 0) return false;
  }

  return true;
}

// ������д����־�ļ���fmt�ǿɱ������ʹ�÷�����printf�⺯����ͬ��
// Write������д�뵱ǰ��ʱ�䣬WriteEx������дʱ�䡣
bool CLogFile::Write(const char *fmt,...)
{
  if (m_tracefp == 0) return false;

  // pthread_spin_lock(&spin);  // ��ѧ��ʱ��Ҫ�������д��롣

  if (BackupLogFile() == false) return false;

  char strtime[20]; LocalTime(strtime);
  va_list ap;
  va_start(ap,fmt);
  fprintf(m_tracefp,"%s ",strtime);
  vfprintf(m_tracefp,fmt,ap);
  va_end(ap);

  if (m_bEnBuffer==false) fflush(m_tracefp);

  // pthread_spin_unlock(&spin);  // ��ѧ��ʱ��Ҫ�������д��롣

  return true;
}

// ������д����־�ļ���fmt�ǿɱ������ʹ�÷�����printf�⺯����ͬ��
// Write������д�뵱ǰ��ʱ�䣬WriteEx������дʱ�䡣
bool CLogFile::WriteEx(const char *fmt,...)
{
  if (m_tracefp == 0) return false;

  // pthread_spin_lock(&spin);  // ��ѧ��ʱ��Ҫ�������д��롣

  va_list ap;
  va_start(ap,fmt);
  vfprintf(m_tracefp,fmt,ap);
  va_end(ap);

  if (m_bEnBuffer==false) fflush(m_tracefp);

  // pthread_spin_unlock(&spin);  // ��ѧ��ʱ��Ҫ�������д��롣

  return true;
}

CIniFile::CIniFile()
{
  
}

bool CIniFile::LoadFile(const char *filename)
{
  m_xmlbuffer.clear();

  CFile File;

  if ( File.Open(filename,"r") == false) return false;

  char strLine[501];

  while (true)
  {
    memset(strLine,0,sizeof(strLine));

    if (File.FFGETS(strLine,500) == false) break;

    m_xmlbuffer=m_xmlbuffer+strLine;
  }

  if (m_xmlbuffer.length() < 10) return false;

  return true;
}

bool CIniFile::GetValue(const char *fieldname,bool   *value)
{
  return GetXMLBuffer(m_xmlbuffer.c_str(),fieldname,value);
}

bool CIniFile::GetValue(const char *fieldname,char *value,int ilen)
{
  return GetXMLBuffer(m_xmlbuffer.c_str(),fieldname,value,ilen);
}

bool CIniFile::GetValue(const char *fieldname,int *value)
{
  return GetXMLBuffer(m_xmlbuffer.c_str(),fieldname,value);
}

bool CIniFile::GetValue(const char *fieldname,unsigned int *value)
{
  return GetXMLBuffer(m_xmlbuffer.c_str(),fieldname,value);
}

bool CIniFile::GetValue(const char *fieldname,long *value)
{
  return GetXMLBuffer(m_xmlbuffer.c_str(),fieldname,value);
}

bool CIniFile::GetValue(const char *fieldname,unsigned long *value)
{
  return GetXMLBuffer(m_xmlbuffer.c_str(),fieldname,value);
}

bool CIniFile::GetValue(const char *fieldname,double *value)
{
  return GetXMLBuffer(m_xmlbuffer.c_str(),fieldname,value);
}

// �ر�ȫ�����źź��������
void CloseIOAndSignal(bool bCloseIO)
{
  int ii=0;

  for (ii=0;ii<64;ii++)
  {
    if (bCloseIO==true) close(ii);

    signal(ii,SIG_IGN); 
  }
}

// ���ݾ���·�����ļ�����Ŀ¼���𼶵Ĵ���Ŀ¼��
// pathorfilename������·�����ļ�����Ŀ¼����
// bisfilename��˵��pathorfilename�����ͣ�true-pathorfilename���ļ�����������Ŀ¼����ȱʡֵΪtrue��
// ����ֵ��true-�����ɹ���false-����ʧ�ܣ��������ʧ�ܣ�ԭ���д�������������1��Ȩ�޲��㣻 2��pathorfilename�������ǺϷ����ļ�����Ŀ¼����3�����̿ռ䲻�㡣
bool MKDIR(const char *filename,bool bisfilename)
{
  // ���Ŀ¼�Ƿ���ڣ���������ڣ��𼶴�����Ŀ¼
  char strPathName[301];

  int ilen=strlen(filename);

  for (int ii=1; ii<ilen;ii++)
  {
    if (filename[ii] != '/') continue;

    STRNCPY(strPathName,sizeof(strPathName),filename,ii);

    if (access(strPathName,F_OK) == 0) continue; // ���Ŀ¼�Ѵ��ڣ�continue

    if (mkdir(strPathName,0755) != 0) return false;  // ���Ŀ¼�����ڣ���������
  }

  if (bisfilename==false)
  {
    if (access(filename,F_OK) != 0)
    {
      if (mkdir(filename,0755) != 0) return false;
    }
  }

  return true;
}

// ���ļ���
// FOPEN��������fopen�⺯�����ļ�������ļ����а�����Ŀ¼�����ڣ��ʹ���Ŀ¼��
// FOPEN�����Ĳ����ͷ���ֵ��fopen������ȫ��ͬ��
// ��Ӧ�ÿ����У���FOPEN��������fopen�⺯����
FILE *FOPEN(const char *filename,const char *mode)
{
  if (MKDIR(filename) == false) return 0;

  return fopen(filename,mode);
}

// ��ȡ�ļ��Ĵ�С��
// filename������ȡ���ļ�����������þ���·�����ļ�����
// ����ֵ������ļ������ڻ�û�з���Ȩ�ޣ�����-1���ɹ������ļ��Ĵ�С����λ���ֽڡ�
int FileSize(const char *filename)
{
  struct stat st_filestat;

  if (stat(filename,&st_filestat) < 0) return -1;

  return st_filestat.st_size;
}

// �����ļ����޸�ʱ�����ԡ�
// filename�������õ��ļ�����������þ���·�����ļ�����
// stime���ַ�����ʾ��ʱ�䣬��ʽ���ޣ���һ��Ҫ����yyyymmddhh24miss��һ���������١�
// ����ֵ��true-�ɹ���false-ʧ�ܣ�ʧ�ܵ�ԭ�򱣴���errno�С�
bool UTime(const char *filename,const char *mtime)
{
  struct utimbuf stutimbuf;

  stutimbuf.actime=stutimbuf.modtime=strtotime(mtime);

  if (utime(filename,&stutimbuf)!=0) return false;

  return true;
}

// ���ַ�����ʾ��ʱ��ת��Ϊ������ʾ��ʱ�䡣
// stime���ַ�����ʾ��ʱ�䣬��ʽ���ޣ���һ��Ҫ����yyyymmddhh24miss��һ���������١�
// ����ֵ��������ʾ��ʱ�䣬���stime�ĸ�ʽ����ȷ������-1��
time_t strtotime(const char *stime)
{
  char strtime[21],yyyy[5],mm[3],dd[3],hh[3],mi[3],ss[3];
  memset(strtime,0,sizeof(strtime));
  memset(yyyy,0,sizeof(yyyy));
  memset(mm,0,sizeof(mm));
  memset(dd,0,sizeof(dd));
  memset(hh,0,sizeof(hh));
  memset(mi,0,sizeof(mi));
  memset(ss,0,sizeof(ss));

  PickNumber(stime,strtime,false,false);

  if (strlen(strtime) != 14) return -1;

  strncpy(yyyy,strtime,4);
  strncpy(mm,strtime+4,2);
  strncpy(dd,strtime+6,2);
  strncpy(hh,strtime+8,2);
  strncpy(mi,strtime+10,2);
  strncpy(ss,strtime+12,2);

  struct tm time_str;

  time_str.tm_year = atoi(yyyy) - 1900;
  time_str.tm_mon = atoi(mm) - 1;
  time_str.tm_mday = atoi(dd);
  time_str.tm_hour = atoi(hh);
  time_str.tm_min = atoi(mi);
  time_str.tm_sec = atoi(ss);
  time_str.tm_isdst = 0;

  return mktime(&time_str);
}

// ���ַ�����ʾ��ʱ�����һ��ƫ�Ƶ�������õ�һ���µ��ַ�����ʾ��ʱ�䡣
// in_stime��������ַ�����ʽ��ʱ�䡣
// out_stime��������ַ�����ʽ��ʱ�䡣
// timetvl����Ҫƫ�Ƶ���������������ƫ�ƣ�������ǰƫ�ơ�
// fmt������ַ���ʱ��out_stime�ĸ�ʽ����LocalTime������fmt������ͬ��
// ע�⣺in_stime��out_stime����������ͬһ�������ĵ�ַ���������ʧ�ܣ�out_stime�����ݻ���ա�
// ����ֵ��true-�ɹ���false-ʧ�ܣ��������ʧ�ܣ�������Ϊ��in_stime�ĸ�ʽ����ȷ��
bool AddTime(const char *in_stime,char *out_stime,const int timetvl,const char *fmt)
{
  if ( (in_stime==0) || (out_stime==0) ) return false;    // �жϿ�ָ�롣

  time_t  timer;
  if ( (timer=strtotime(in_stime))==-1) { strcpy(out_stime,""); return false; }

  timer=timer+timetvl;

  strcpy(out_stime,"");

  timetostr(timer,out_stime,fmt);

  return true;
}

// ��ȡ�ļ���ʱ�䡣
// filename������ȡ���ļ�����������þ���·�����ļ�����
// mtime�����ڴ���ļ���ʱ�䣬��stat�ṹ���st_mtime��
// fmt������ʱ��������ʽ����LocalTime������ͬ����ȱʡ��"yyyymmddhh24miss"��
// ����ֵ������ļ������ڻ�û�з���Ȩ�ޣ�����false���ɹ�����true��
bool FileMTime(const char *filename,char *mtime,const char *fmt)
{
  // �ж��ļ��Ƿ���ڡ�
  struct stat st_filestat;

  if (stat(filename,&st_filestat) < 0) return false;

  char strfmt[25];
  memset(strfmt,0,sizeof(strfmt));
  if (fmt==0) strcpy(strfmt,"yyyymmddhh24miss");
  else strcpy(strfmt,fmt);

  timetostr(st_filestat.st_mtime,mtime,strfmt);

  return true;
}


CDir::CDir()
{
  m_pos=0;

  STRCPY(m_DateFMT,sizeof(m_DateFMT),"yyyy-mm-dd hh24:mi:ss");

  m_vFileName.clear();

  initdata();
}

void CDir::initdata()
{
  memset(m_DirName,0,sizeof(m_DirName));
  memset(m_FileName,0,sizeof(m_FileName));
  memset(m_FullFileName,0,sizeof(m_FullFileName));
  m_FileSize=0;
  memset(m_CreateTime,0,sizeof(m_CreateTime));
  memset(m_ModifyTime,0,sizeof(m_ModifyTime));
  memset(m_AccessTime,0,sizeof(m_AccessTime));
}

// �����ļ�ʱ��ĸ�ʽ��֧��"yyyy-mm-dd hh24:mi:ss"��"yyyymmddhh24miss"���֣�ȱʡ��ǰ�ߡ�
void CDir::SetDateFMT(const char *in_DateFMT)
{
  memset(m_DateFMT,0,sizeof(m_DateFMT));
  STRCPY(m_DateFMT,sizeof(m_DateFMT),in_DateFMT);
}

// ��Ŀ¼����ȡĿ¼�е��ļ��б���Ϣ�������m_vFileName�����С�
// in_DirName�����򿪵�Ŀ¼����
// in_MatchStr������ȡ�ļ�����ƥ����򣬲�ƥ����ļ������ԡ�
// in_MaxCount����ȡ�ļ������������ȱʡֵΪ10000����
// bAndChild���Ƿ�򿪸�����Ŀ¼��ȱʡֵΪfalse-������Ŀ¼��
// bSort���Ƿ�Ի�ȡ�����ļ��б���m_vFileName�����е����ݣ���������ȱʡֵΪfalse-������
// ����ֵ�����in_DirName����ָ����Ŀ¼�����ڣ�OpenDir�����ᴴ����Ŀ¼���������ʧ�ܣ�����false�����У������ǰ�û���in_DirNameĿ¼�µ���Ŀ¼û�ж�ȡȨ��Ҳ�᷵��false��������������¶��᷵��true��
bool CDir::OpenDir(const char *in_DirName,const char *in_MatchStr,const unsigned int in_MaxCount,const bool bAndChild,bool bSort)
{
  m_pos=0;
  m_vFileName.clear();

  // ���Ŀ¼�����ڣ��ʹ�����Ŀ¼
  if (MKDIR(in_DirName,false) == false) return false;

  bool bRet=_OpenDir(in_DirName,in_MatchStr,in_MaxCount,bAndChild);

  if (bSort==true)
  {
    sort(m_vFileName.begin(), m_vFileName.end());
  }

  return bRet;
}

// ����һ���ݹ麯��������OpenDir()�ĵ��ã���CDir����ⲿ����Ҫ��������
bool CDir::_OpenDir(const char *in_DirName,const char *in_MatchStr,const unsigned int in_MaxCount,const bool bAndChild)
{
  DIR *dir;

  if ( (dir=opendir(in_DirName)) == 0 ) return false;

  char strTempFileName[3001];

  struct dirent *st_fileinfo;
  struct stat st_filestat;

  while ((st_fileinfo=readdir(dir)) != 0)
  {
    // ��"."��ͷ���ļ�������
    if (st_fileinfo->d_name[0]=='.') continue;
        
    SNPRINTF(strTempFileName,sizeof(strTempFileName),300,"%s//%s",in_DirName,st_fileinfo->d_name);

    UpdateStr(strTempFileName,"//","/");

    stat(strTempFileName,&st_filestat);

    // �ж��Ƿ���Ŀ¼������ǣ����������Ŀ¼��
    if (S_ISDIR(st_filestat.st_mode))
    {
      if (bAndChild == true)
      {
        if (_OpenDir(strTempFileName,in_MatchStr,in_MaxCount,bAndChild) == false) 
        {
          closedir(dir); return false;
        }
      }
    }
    else
    {
      // ������ļ�������ƥ���ϵ��ļ�����m_vFileName�����С�
      if (MatchStr(st_fileinfo->d_name,in_MatchStr) == false) continue;

      m_vFileName.push_back(strTempFileName);

      if ( m_vFileName.size()>=in_MaxCount ) break;
    }
  }

  closedir(dir);

  return true;
}

/*
st_gid 
  Numeric identifier of group that owns file (UNIX-specific) This field will always be zero on NT systems. A redirected file is classified as an NT file.
st_atime
  Time of last access of file.
st_ctime
  Time of creation of file.
st_dev
  Drive number of the disk containing the file (same as st_rdev).
st_ino
  Number of the information node (the inode) for the file (UNIX-specific). On UNIX file systems, the inode describes the file date and time stamps, permissions, and content. When files are hard-linked to one another, they share the same inode. The inode, and therefore st_ino, has no meaning in the FAT, HPFS, or NTFS file systems.
st_mode
  Bit mask for file-mode information. The _S_IFDIR bit is set if path specifies a directory; the _S_IFREG bit is set if path specifies an ordinary file or a device. User read/write bits are set according to the file��s permission mode; user execute bits are set according to the filename extension.
st_mtime
  Time of last modification of file.
st_nlink
  Always 1 on non-NTFS file systems.
st_rdev
  Drive number of the disk containing the file (same as st_dev).
st_size
  Size of the file in bytes; a 64-bit integer for _stati64 and _wstati64
st_uid
  Numeric identifier of user who owns file (UNIX-specific). This field will always be zero on NT systems. A redirected file is classified as an NT file.
*/

// ��m_vFileName�����л�ȡһ����¼���ļ�������ͬʱ�õ����ļ��Ĵ�С���޸�ʱ�����Ϣ��
// ����OpenDir����ʱ��m_vFileName��������գ�m_pos���㣬ÿ����һ��ReadDir����m_pos��1��
// ��m_posС��m_vFileName.size()������true�����򷵻�false��
bool CDir::ReadDir()
{
  initdata();

  int ivsize=m_vFileName.size();

  // ����Ѷ��꣬�������
  if (m_pos >= ivsize) 
  {
    m_pos=0; m_vFileName.clear(); return false;
  }

  int pos=0;

  pos=m_vFileName[m_pos].find_last_of("/");

  // Ŀ¼��
  STRCPY(m_DirName,sizeof(m_DirName),m_vFileName[m_pos].substr(0,pos).c_str());

  // �ļ���
  STRCPY(m_FileName,sizeof(m_FileName),m_vFileName[m_pos].substr(pos+1,m_vFileName[m_pos].size()-pos-1).c_str());

  // �ļ�ȫ��������·��
  SNPRINTF(m_FullFileName,sizeof(m_FullFileName),300,"%s",m_vFileName[m_pos].c_str());

  struct stat st_filestat;

  stat(m_FullFileName,&st_filestat);

  m_FileSize=st_filestat.st_size;

  struct tm nowtimer;

  if (strcmp(m_DateFMT,"yyyy-mm-dd hh24:mi:ss") == 0)
  {
    nowtimer = *localtime(&st_filestat.st_mtime);
    // localtime_r(&st_filestat.st_mtime,&nowtimer); 
    nowtimer.tm_mon++;
    snprintf(m_ModifyTime,20,"%04u-%02u-%02u %02u:%02u:%02u",\
             nowtimer.tm_year+1900,nowtimer.tm_mon,nowtimer.tm_mday,\
             nowtimer.tm_hour,nowtimer.tm_min,nowtimer.tm_sec);

    nowtimer = *localtime(&st_filestat.st_ctime);
    // localtime_r(&st_filestat.st_ctime,&nowtimer); 
    nowtimer.tm_mon++;
    snprintf(m_CreateTime,20,"%04u-%02u-%02u %02u:%02u:%02u",\
             nowtimer.tm_year+1900,nowtimer.tm_mon,nowtimer.tm_mday,\
             nowtimer.tm_hour,nowtimer.tm_min,nowtimer.tm_sec);

    nowtimer = *localtime(&st_filestat.st_atime);
    // localtime_r(&st_filestat.st_atime,&nowtimer); 
    nowtimer.tm_mon++;
    snprintf(m_AccessTime,20,"%04u-%02u-%02u %02u:%02u:%02u",\
             nowtimer.tm_year+1900,nowtimer.tm_mon,nowtimer.tm_mday,\
             nowtimer.tm_hour,nowtimer.tm_min,nowtimer.tm_sec);
  }

  if (strcmp(m_DateFMT,"yyyymmddhh24miss") == 0)
  {
    nowtimer = *localtime(&st_filestat.st_mtime);
    // localtime_r(&st_filestat.st_mtime,&nowtimer); 
    nowtimer.tm_mon++;
    snprintf(m_ModifyTime,20,"%04u%02u%02u%02u%02u%02u",\
             nowtimer.tm_year+1900,nowtimer.tm_mon,nowtimer.tm_mday,\
             nowtimer.tm_hour,nowtimer.tm_min,nowtimer.tm_sec);

    nowtimer = *localtime(&st_filestat.st_ctime);
    // localtime_r(&st_filestat.st_ctime,&nowtimer); 
    nowtimer.tm_mon++;
    snprintf(m_CreateTime,20,"%04u%02u%02u%02u%02u%02u",\
             nowtimer.tm_year+1900,nowtimer.tm_mon,nowtimer.tm_mday,\
             nowtimer.tm_hour,nowtimer.tm_min,nowtimer.tm_sec);

    nowtimer = *localtime(&st_filestat.st_atime);
    // localtime_r(&st_filestat.st_atime,&nowtimer); 
    nowtimer.tm_mon++;
    snprintf(m_AccessTime,20,"%04u%02u%02u%02u%02u%02u",\
             nowtimer.tm_year+1900,nowtimer.tm_mon,nowtimer.tm_mday,\
             nowtimer.tm_hour,nowtimer.tm_min,nowtimer.tm_sec);
  }

  m_pos++;

  return true;
}

CDir::~CDir()
{
  m_vFileName.clear();

  // m_vDirName.clear();
}

// ɾ��Ŀ¼�е��ļ�������Linuxϵͳ��rm���
// filename����ɾ�����ļ�����������þ���·�����ļ���������/tmp/root/data.xml��
// times��ִ��ɾ���ļ��Ĵ�����ȱʡ��1�����鲻Ҫ����3����ʵ��Ӧ�õľ��鿴�������ɾ���ļ���1�β��ɹ����ٳ���
// 2���ǿ��Եģ���������岻���ˡ����У����ִ��ɾ��ʧ�ܣ�usleep(100000)�������ԡ�
// ����ֵ��true-ɾ���ɹ���false-ɾ��ʧ�ܣ�ʧ�ܵ���Ҫԭ����Ȩ�޲��㡣
// ��Ӧ�ÿ����У�������REMOVE��������remove�⺯����
bool REMOVE(const char *filename,const int times)
{
  // ����ļ������ڣ�ֱ�ӷ���ʧ��
  if (access(filename,R_OK) != 0) return false;

  for (int ii=0;ii<times;ii++)
  {
    if (remove(filename) == 0) return true;

    usleep(100000);
  }

  return false;
}

// ���ļ�������������Linuxϵͳ��mv���
// srcfilename��ԭ�ļ�����������þ���·�����ļ�����
// dstfilename��Ŀ���ļ�����������þ���·�����ļ�����
// times��ִ���������ļ��Ĵ�����ȱʡ��1�����鲻Ҫ����3����ʵ��Ӧ�õľ��鿴��������������ļ���1�β��ɹ����ٳ�
// ��2���ǿ��Եģ�����ξ����岻���ˡ����У����ִ��������ʧ�ܣ�usleep(100000)�������ԡ�
// ����ֵ��true-�������ɹ���false-������ʧ�ܣ�ʧ�ܵ���Ҫԭ����Ȩ�޲������̿ռ䲻�������ԭ�ļ���Ŀ���ļ���
// ��ͬһ�����̷�����������Ҳ����ʧ�ܡ�
// ע�⣬���������ļ�֮ǰ�����Զ�����dstfilename�����е�Ŀ¼����
// ��Ӧ�ÿ����У�������RENAME��������rename�⺯����
bool RENAME(const char *srcfilename,const char *dstfilename,const int times)
{
  // ����ļ������ڣ�ֱ�ӷ���ʧ��
  if (access(srcfilename,R_OK) != 0) return false;

  if (MKDIR(dstfilename) == false) return false;

  for (int ii=0;ii<times;ii++)
  {
    if (rename(srcfilename,dstfilename) == 0) return true;

    usleep(100000);
  }

  return false;
}


CTcpClient::CTcpClient()
{
  m_connfd=-1;
  memset(m_ip,0,sizeof(m_ip));
  m_port=0;
  m_btimeout=false;
}

bool CTcpClient::ConnectToServer(const char *ip,const int port)
{
  // ��������ӵ�����ˣ���Ͽ������ִ�����û���ر��ԭ�򣬲�Ҫ���ᡣ
  if (m_connfd!=-1) { close(m_connfd); m_connfd=-1; }
 
  // ����SIGPIPE�źţ���ֹ�����쳣�˳���
  // ���send��һ��disconnected socket�ϣ��ں˾ͻᷢ��SIGPIPE�źš�����ź�
  // ��ȱʡ����������ֹ���̣������ʱ���ⶼ�������������ġ��������¶�����
  // ���źŵĴ�����������������ֱ����������
  signal(SIGPIPE,SIG_IGN);   

  STRCPY(m_ip,sizeof(m_ip),ip);
  m_port=port;

  struct hostent* h;
  struct sockaddr_in servaddr;

  if ( (m_connfd = socket(AF_INET,SOCK_STREAM,0) ) < 0) return false;

  if ( !(h = gethostbyname(m_ip)) )
  {
    close(m_connfd);  m_connfd=-1; return false;
  }

  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(m_port);  // ָ������˵�ͨѶ�˿�
  memcpy(&servaddr.sin_addr,h->h_addr,h->h_length);

  if (connect(m_connfd, (struct sockaddr *)&servaddr,sizeof(servaddr)) != 0)
  {
    close(m_connfd);  m_connfd=-1; return false;
  }

  return true;
}

// ���շ���˷��͹��������ݡ�
// buffer���������ݻ������ĵ�ַ�����ݵĳ��ȴ����m_buflen��Ա�����С�
// itimeout���ȴ����ݵĳ�ʱʱ�䣬��λ���룬ȱʡֵ��0-���޵ȴ���
// ����ֵ��true-�ɹ���false-ʧ�ܣ�ʧ�������������1���ȴ���ʱ����Ա����m_btimeout��ֵ������Ϊtrue��2��socket�����Ѳ����á�
bool CTcpClient::Read(char *buffer,const int itimeout)
{
  if (m_connfd==-1) return false;

  // ���itimeout>0����ʾ��Ҫ�ȴ�itimeout�룬���itimeout���û�����ݵ������false��
  if (itimeout>0)
  {
    struct pollfd fds;
    fds.fd=m_connfd;
    fds.events=POLLIN;  
    int iret;
    m_btimeout=false;
    if ( (iret=poll(&fds,1,itimeout*1000)) <= 0 )
    {
      if (iret==0) m_btimeout = true;
      return false;
    }
  }

  m_buflen = 0;
  return (TcpRead(m_connfd,buffer,&m_buflen));
}

bool CTcpClient::Write(const char *buffer,const int ibuflen)
{
  if (m_connfd==-1) return false;

  int ilen=ibuflen;

  if (ibuflen==0) ilen=strlen(buffer);

  return(TcpWrite(m_connfd,buffer,ilen));
}

void CTcpClient::Close()
{
  if (m_connfd > 0) close(m_connfd); 

  m_connfd=-1;
  memset(m_ip,0,sizeof(m_ip));
  m_port=0;
  m_btimeout=false;
}

CTcpClient::~CTcpClient()
{
  Close();
}

CTcpServer::CTcpServer()
{
  m_listenfd=-1;
  m_connfd=-1;
  m_socklen=0;
  m_btimeout=false;
}

bool CTcpServer::InitServer(const unsigned int port,const int backlog)
{
  // �������˵�socket>0���ص��������ִ�����û���ر��ԭ�򣬲�Ҫ���ᡣ
  if (m_listenfd > 0) { close(m_listenfd); m_listenfd=-1; }

  if ( (m_listenfd = socket(AF_INET,SOCK_STREAM,0))<=0) return false;

  // ����SIGPIPE�źţ���ֹ�����쳣�˳���
  signal(SIGPIPE,SIG_IGN);   

  // ��SO_REUSEADDRѡ�����������Ӵ���TIME_WAIT״̬ʱ�����ٴ�������������
  // ����bind()���ܻ᲻�ɹ�������Address already in use��
  //char opt = 1; unsigned int len = sizeof(opt);
  int opt = 1; unsigned int len = sizeof(opt);
  setsockopt(m_listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,len);    

  memset(&m_servaddr,0,sizeof(m_servaddr));
  m_servaddr.sin_family = AF_INET;
  m_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // ����ip��ַ��
  m_servaddr.sin_port = htons(port);
  if (bind(m_listenfd,(struct sockaddr *)&m_servaddr,sizeof(m_servaddr)) != 0 )
  {
    CloseListen(); return false;
  }

  if (listen(m_listenfd,backlog) != 0 )
  {
    CloseListen(); return false;
  }

  return true;
}

bool CTcpServer::Accept()
{
  if (m_listenfd==-1) return false;

  m_socklen = sizeof(struct sockaddr_in);

  if ((m_connfd=accept(m_listenfd,(struct sockaddr *)&m_clientaddr,(socklen_t*)&m_socklen)) < 0)
      return false;

  return true;
}

char *CTcpServer::GetIP()
{
  return(inet_ntoa(m_clientaddr.sin_addr));
}

bool CTcpServer::Read(char *buffer,const int itimeout)
{
  if (m_connfd==-1) return false;

  // ���itimeout>0����ʾ��Ҫ�ȴ�itimeout�룬���itimeout���û�����ݵ������false��
  if (itimeout>0)
  {
    struct pollfd fds;
    fds.fd=m_connfd;
    fds.events=POLLIN;
    m_btimeout=false;
    int iret;
    if ( (iret=poll(&fds,1,itimeout*1000)) <= 0 )
    {
      if (iret==0) m_btimeout = true;
      return false;
    }
  }

  m_buflen = 0;
  return(TcpRead(m_connfd,buffer,&m_buflen));
}

bool CTcpServer::Write(const char *buffer,const int ibuflen)
{
  if (m_connfd==-1) return false;

  int ilen = ibuflen;
  if (ilen==0) ilen=strlen(buffer);

  return(TcpWrite(m_connfd,buffer,ilen));
}

void CTcpServer::CloseListen()
{
  if (m_listenfd > 0)
  {
    close(m_listenfd); m_listenfd=-1;
  }
}

void CTcpServer::CloseClient()
{
  if (m_connfd > 0)
  {
    close(m_connfd); m_connfd=-1; 
  }
}

CTcpServer::~CTcpServer()
{
  CloseListen(); CloseClient();
}

// ����socket�ĶԶ˷��͹��������ݡ�
// sockfd�����õ�socket���ӡ�
// buffer���������ݻ������ĵ�ַ��
// ibuflen�����γɹ��������ݵ��ֽ�����
// itimeout�����յȴ���ʱ��ʱ�䣬��λ���룬-1-���ȴ���0-���޵ȴ���>0-�ȴ���������
// ����ֵ��true-�ɹ���false-ʧ�ܣ�ʧ�������������1���ȴ���ʱ��2��socket�����Ѳ����á�
bool TcpRead(const int sockfd,char *buffer,int *ibuflen,const int itimeout)
{
  if (sockfd==-1) return false;

  // ���itimeout>0����ʾ��Ҫ�ȴ�itimeout�룬���itimeout���û�����ݵ������false��
  if (itimeout>0)
  {
    struct pollfd fds;
    fds.fd=sockfd;
    fds.events=POLLIN;
    if ( poll(&fds,1,itimeout*1000) <= 0 ) return false;
  }

  // ���itimeout==-1����ʾ���ȴ��������ж�socket�Ļ��������Ƿ������ݣ����û�У�����false��
  if (itimeout==-1)
  {
    struct pollfd fds;
    fds.fd=sockfd;
    fds.events=POLLIN;
    if ( poll(&fds,1,0) <= 0 ) return false;
  }

  (*ibuflen) = 0;  // ���ĳ��ȱ�����ʼ��Ϊ0��

  // �ȶ�ȡ���ĳ��ȣ�4���ֽڡ�
  if (Readn(sockfd,(char*)ibuflen,4) == false) return false;

  (*ibuflen)=ntohl(*ibuflen);  // �ѱ��ĳ����������ֽ���ת��Ϊ�����ֽ���

  // �ٶ�ȡ�������ݡ�
  if (Readn(sockfd,buffer,(*ibuflen)) == false) return false;

  return true;
}

// ��socket�ĶԶ˷������ݡ�
// sockfd�����õ�socket���ӡ�
// buffer�����������ݻ������ĵ�ַ��
// ibuflen�����������ݵ��ֽ�����������͵���ascii�ַ�����ibuflen��0���ַ����ĳ��ȣ�
//          ����Ƕ����������ݣ�ibuflenΪ���������ݿ�Ĵ�С��
// ����ֵ��true-�ɹ���false-ʧ�ܣ����ʧ�ܣ���ʾsocket�����Ѳ����á�
bool TcpWrite(const int sockfd,const char *buffer,const int ibuflen)
{
  if (sockfd==-1) return false;

  int ilen=0;  // ���ĳ��ȡ�

  // ���ibuflen==0������Ϊ��Ҫ���͵����ַ��������ĳ���Ϊ�ַ����ĳ��ȡ�
  if (ibuflen==0) ilen=strlen(buffer);
  else ilen=ibuflen;

  int ilenn=htonl(ilen);    // �ѱ��ĳ���ת��Ϊ�����ֽ���

  char TBuffer[ilen+4];     // ���ͻ�������
  memset(TBuffer,0,sizeof(TBuffer));  // �������ͻ�������
  memcpy(TBuffer,&ilenn,4);           // �ѱ��ĳ��ȿ�������������
  memcpy(TBuffer+4,buffer,ilen);      // �ѱ������ݿ�������������
  
  // ���ͻ������е����ݡ�
  if (Writen(sockfd,TBuffer,ilen+4) == false) return false;

  return true;
}

// ���Ѿ�׼���õ�socket�ж�ȡ���ݡ�
// sockfd���Ѿ�׼���õ�socket���ӡ�
// buffer���������ݻ������ĵ�ַ��
// n�����ν������ݵ��ֽ�����
// ����ֵ���ɹ����յ�n�ֽڵ����ݺ󷵻�true��socket���Ӳ����÷���false��
bool Readn(const int sockfd,char *buffer,const size_t n)
{
  int nLeft=n;  // ʣ����Ҫ��ȡ���ֽ�����
  int idx=0;    // �ѳɹ���ȡ���ֽ�����
  int nread;    // ÿ�ε���recv()�����������ֽ�����

  while(nLeft > 0)
  {
    if ( (nread=recv(sockfd,buffer+idx,nLeft,0)) <= 0) return false;

    idx=idx+nread;
    nLeft=nLeft-nread;
  }

  return true;
}

// ���Ѿ�׼���õ�socket��д�����ݡ�
// sockfd���Ѿ�׼���õ�socket���ӡ�
// buffer�����������ݻ������ĵ�ַ��
// n�����������ݵ��ֽ�����
// ����ֵ���ɹ�������n�ֽڵ����ݺ󷵻�true��socket���Ӳ����÷���false��
bool Writen(const int sockfd,const char *buffer,const size_t n)
{
  int nLeft=n;  // ʣ����Ҫд����ֽ�����
  int idx=0;    // �ѳɹ�д����ֽ�����
  int nwritten; // ÿ�ε���send()����д����ֽ�����
  
  while(nLeft > 0 )
  {    
    if ( (nwritten=send(sockfd,buffer+idx,nLeft,0)) <= 0) return false;      
    
    nLeft=nLeft-nwritten;
    idx=idx+nwritten;
  }

  return true;
}


// �����ļ�������Linuxϵͳ��cp���
// srcfilename��ԭ�ļ�����������þ���·�����ļ�����
// dstfilename��Ŀ���ļ�����������þ���·�����ļ�����
// ����ֵ��true-���Ƴɹ���false-����ʧ�ܣ�ʧ�ܵ���Ҫԭ����Ȩ�޲������̿ռ䲻����
// ע�⣺
// 1���ڸ����ļ�֮ǰ�����Զ�����dstfilename�����е�Ŀ¼����
// 2�������ļ��Ĺ����У�������ʱ�ļ������ķ�����������ɺ��ٸ���Ϊdstfilename�������м�״̬���ļ�����ȡ��
// 3�����ƺ���ļ���ʱ����ԭ�ļ���ͬ����һ����Linuxϵͳcp���ͬ��
bool COPY(const char *srcfilename,const char *dstfilename)
{
  if (MKDIR(dstfilename) == false) return false;

  char strdstfilenametmp[301];
  SNPRINTF(strdstfilenametmp,sizeof(strdstfilenametmp),300,"%s.tmp",dstfilename);

  int  srcfd,dstfd;

  srcfd=dstfd=-1;

  int iFileSize=FileSize(srcfilename);

  int  bytes=0;
  int  total_bytes=0;
  int  onread=0;
  char buffer[5000];

  if ( (srcfd=open(srcfilename,O_RDONLY)) < 0 ) return false;

  if ( (dstfd=open(strdstfilenametmp,O_WRONLY|O_CREAT|O_TRUNC,S_IWUSR|S_IRUSR|S_IXUSR)) < 0) { close(srcfd); return false; }

  while (true)
  {
    memset(buffer,0,sizeof(buffer));

    if ((iFileSize-total_bytes) > 5000) onread=5000;
    else onread=iFileSize-total_bytes;

    bytes=read(srcfd,buffer,onread);

    if (bytes > 0) write(dstfd,buffer,bytes);

    total_bytes = total_bytes + bytes;

    if (total_bytes == iFileSize) break;
  }

  close(srcfd);

  close(dstfd);

  // �����ļ����޸�ʱ������
  char strmtime[21];
  memset(strmtime,0,sizeof(strmtime));
  FileMTime(srcfilename,strmtime);
  UTime(strdstfilenametmp,strmtime);

  if (RENAME(strdstfilenametmp,dstfilename) == false) { REMOVE(strdstfilenametmp); return false; }

  return true;
}


CTimer::CTimer()
{
  memset(&m_start,0,sizeof(struct timeval));
  memset(&m_end,0,sizeof(struct timeval));

  // ��ʼ��ʱ
  Start();
}

// ��ʼ��ʱ
void CTimer::Start()
{
  gettimeofday( &m_start, 0 );
}

// ��������ȥ��ʱ�䣬��λ���룬С���������΢��
// ÿ����һ�α�����֮���Զ�����Start�������¿�ʼ��ʱ��
double CTimer::Elapsed()
{

  gettimeofday( &m_end, 0 );

  double dstart,dend;

  dstart=dend=0;

  char strtemp[51];
  SNPRINTF(strtemp,sizeof(strtemp),30,"%ld.%06ld",m_start.tv_sec,m_start.tv_usec);
  dstart=atof(strtemp);

  SNPRINTF(strtemp,sizeof(strtemp),30,"%ld.%06ld",m_end.tv_sec,m_end.tv_usec);
  dend=atof(strtemp);

  // ���¿�ʼ��ʱ
  Start();

  return dend-dstart;
}

CSEM::CSEM()
{
  m_semid=-1;
  m_sem_flg=SEM_UNDO;
}

// ����ź����Ѵ��ڣ���ȡ�ź���������ź��������ڣ��򴴽�������ʼ��Ϊvalue��
bool CSEM::init(key_t key,unsigned short value,short sem_flg)
{
  if (m_semid!=-1) return false;

  m_sem_flg=sem_flg;

  // �ź����ĳ�ʼ������ֱ����semget(key,1,0666|IPC_CREAT)����Ϊ�ź��������󣬳�ʼֵ��0��

  // �ź����ĳ�ʼ�����������裺
  // 1����ȡ�ź���������ɹ����������ء�
  // 2�����ʧ�ܣ��򴴽��ź�����
  // 3) �����ź����ĳ�ʼֵ��

  // ��ȡ�ź�����
  if ( (m_semid=semget(key,1,0666)) == -1)
  {
    // ����ź��������ڣ���������
    if (errno==2)
    {
      // ��IPC_EXCL��־ȷ��ֻ��һ�����̴�������ʼ���ź�������������ֻ�ܻ�ȡ��
      if ( (m_semid=semget(key,1,0666|IPC_CREAT|IPC_EXCL)) == -1)
      {
        if (errno!=EEXIST)
        {
          perror("init 1 semget()"); return false;
        }
        if ( (m_semid=semget(key,1,0666)) == -1)
        { perror("init 2 semget()"); return false; }
    
        return true;
      }

      // �ź��������ɹ��󣬻���Ҫ������ʼ����value��
      union semun sem_union;
      sem_union.val = value;   // �����ź����ĳ�ʼֵ��
      if (semctl(m_semid,0,SETVAL,sem_union) <  0) { perror("init semctl()"); return false; }
    }
    else
    { perror("init 3 semget()"); return false; }
  }

  return true;
}

bool CSEM::P(short sem_op)
{
  if (m_semid==-1) return false;

  struct sembuf sem_b;
  sem_b.sem_num = 0;      // �ź�����ţ�0�����һ���ź�����
  sem_b.sem_op = sem_op;  // P������sem_op����С��0��
  sem_b.sem_flg = m_sem_flg;   
  if (semop(m_semid,&sem_b,1) == -1) { perror("p semop()"); return false; }

  return true;
}

bool CSEM::V(short sem_op)
{
  if (m_semid==-1) return false;

  struct sembuf sem_b;
  sem_b.sem_num = 0;      // �ź�����ţ�0�����һ���ź�����
  sem_b.sem_op = sem_op;  // V������sem_op�������0��
  sem_b.sem_flg = m_sem_flg;
  if (semop(m_semid,&sem_b,1) == -1) { perror("V semop()"); return false; }

  return true;
}

// ��ȡ�ź�����ֵ���ɹ������ź�����ֵ��ʧ�ܷ���-1��
int CSEM::value()
{
  return semctl(m_semid,0,GETVAL);
}

bool CSEM::destroy()
{
  if (m_semid==-1) return false;

  if (semctl(m_semid,0,IPC_RMID) == -1) { perror("destroy semctl()"); return false; }

  return true;
}

CSEM::~CSEM()
{
}

CPActive::CPActive()
{
  m_shmid=0;
  m_pos=-1;
  m_shm=0;
}

// �ѵ�ǰ���̵�������Ϣ���빲���ڴ�������С�
bool CPActive::AddPInfo(const int timeout,const char *pname,CLogFile *logfile)
{
  if (m_pos!=-1) return true;

  if (m_sem.init(SEMKEYP) == false)  // ��ʼ���ź�����
  {
    if (logfile!=0) logfile->Write("����/��ȡ�ź���(%x)ʧ�ܡ�\n",SEMKEYP); 
    else printf("����/��ȡ�ź���(%x)ʧ�ܡ�\n",SEMKEYP);

    return false;
  }

  // ����/��ȡ�����ڴ棬��ֵΪSHMKEYP����СΪMAXNUMP��st_procinfo�ṹ��Ĵ�С��
  if ( (m_shmid = shmget((key_t)SHMKEYP, MAXNUMP*sizeof(struct st_procinfo), 0666|IPC_CREAT)) == -1)
  { 
    if (logfile!=0) logfile->Write("����/��ȡ�����ڴ�(%x)ʧ�ܡ�\n",SHMKEYP); 
    else printf("����/��ȡ�����ڴ�(%x)ʧ�ܡ�\n",SHMKEYP);

    return false; 
  }

  // �������ڴ����ӵ���ǰ���̵ĵ�ַ�ռ䡣
  m_shm=(struct st_procinfo *)shmat(m_shmid, 0, 0);
  
  struct st_procinfo stprocinfo;    // ��ǰ����������Ϣ�Ľṹ�塣
  memset(&stprocinfo,0,sizeof(stprocinfo));

  stprocinfo.pid=getpid();            // ��ǰ���̺š�
  stprocinfo.timeout=timeout;         // ��ʱʱ�䡣
  stprocinfo.atime=time(0);           // ��ǰʱ�䡣
  STRNCPY(stprocinfo.pname,sizeof(stprocinfo.pname),pname,50); // ��������

  // ����id��ѭ��ʹ�õģ����������һ�������쳣�˳���û�������Լ���������Ϣ��
  // ���Ľ�����Ϣ�������ڹ����ڴ��У����ɵ��ǣ���ǰ�����������������̵�id��
  // �����ͻ��ڹ����ڴ��д�����������id��ͬ�ļ�¼���ػ����̼�鵽�������̵�
  // ����ʱ���������id�����˳��źţ�����źŽ���ɱ��ǰ���̡�

  // ��������ڴ��д��ڵ�ǰ���̱�ţ�һ�����������̲��������ݣ���ǰ���̾����ø�λ�á�
  for (int ii=0;ii<MAXNUMP;ii++)
  {
    if ( (m_shm+ii)->pid==stprocinfo.pid ) { m_pos=ii; break; }
  }

  m_sem.P();  // �������ڴ�������

  if (m_pos==-1)
  {
    // ���m_pos==-1�������ڴ�Ľ������в����ڵ�ǰ���̱�ţ���һ����λ�á�
    for (int ii=0;ii<MAXNUMP;ii++)
      if ( (m_shm+ii)->pid==0 ) { m_pos=ii; break; }
  }

  if (m_pos==-1) 
  { 
    if (logfile!=0) logfile->Write("�����ڴ�ռ������ꡣ\n");
    else printf("�����ڴ�ռ������ꡣ\n");

    m_sem.V();  // ������

    return false; 
  }

  // �ѵ�ǰ���̵�������Ϣ���빲���ڴ�Ľ������С�
  memcpy(m_shm+m_pos,&stprocinfo,sizeof(struct st_procinfo)); 

  m_sem.V();   // ������

  return true;
}

// ���¹����ڴ�������е�ǰ���̵�����ʱ�䡣
bool CPActive::UptATime()
{
  if (m_pos==-1) return false;

  (m_shm+m_pos)->atime=time(0);

  return true;
}

CPActive::~CPActive()
{
  // �ѵ�ǰ���̴ӹ����ڴ�Ľ���������ȥ��
  if (m_pos!=-1) memset(m_shm+m_pos,0,sizeof(struct st_procinfo));

  // �ѹ����ڴ�ӵ�ǰ�����з��롣
  if (m_shm!=0) shmdt(m_shm);
}
