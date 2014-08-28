/**
 * OpenAPI V3 SDK ʾ�����룬�ϴ��ļ���ӿ�ʾ�����롣������������Ҫ����multipart/form-data��ʽ��post�����OpenAPI
 * @version 3.0.0
 * @author open.qq.com
 * @copyright (c)2013, Tencent Corporation. All rights reserved.
 * @History:
 *               3.0.0 | jixingguan | 2013-05-16 10:20:12 | initialization
 */


#include "OpenApiV3.h"
#include "json/json.h"

/*�����ͼƬ��΢��*/
int add_weibo_pic(class OpenApiV3* sdk, string& openid, string& openkey, string& pf,Json::Value& JsonRes)
{
    map<string,string> params;
    string script_name;

    params["openid"]=openid;
    params["openkey"]=openkey;
    params["pf"]=pf;
    params["content"]="hello world";

	script_name = "/v3/t/add_pic_t";    
	struct FormFileElement fileparam;
	
	fileparam.field_name="pic";
	fileparam.file_full_name="photo/test.jpg";
	
	return sdk->apiUploadFile(script_name, params,JsonRes,fileparam);	
}


int main(int argc,char** argv)
{
    int iRet=0;
    //�����Ĵ��ݿ��Կ�ͬ���Ľű��ļ�
    if( argc < 7)
    {
        printf("usage ./testopenapi appid appkey server_name openid openkey pf\n");
        return 0;
    }
    
    // Ӧ�û�����Ϣ
    unsigned int appid = strtoul(argv[1],NULL,10);
    string appkey = argv[2];

    // OpenAPI�ķ�����IP 
    // ���µ�API��������ַ��ο�wiki�ĵ�: http://wiki.open.qq.com/wiki/API3.0%E6%96%87%E6%A1%A3 
    string server_name = argv[3];

    // �û���OpenID/OpenKey
    string openid=argv[4];
    string openkey = argv[5];

    // ��Ҫ���ʵ�ƽ̨, pf������ȡֵ�ο�wiki�ĵ�: http://wiki.open.qq.com/wiki/API3.0%E6%96%87%E6%A1%A3 
    string pf =argv[6];
    
    //����opeapiv3 �ķ�����
    COpenApiV3 sdk(appid, appkey);      

    //���г�ʼ�������÷�������ַ
    sdk.init();
    sdk.setServerName(server_name);
    sdk.setDebugSwitch(true);
   
   Json::Value JsonRes;     
   iRet=add_weibo_pic(&sdk, openid, openkey, pf,JsonRes);
   if( 0 != iRet)
   {
        printf("add_weibo_pic failed iRet=%d err:%s\n",iRet,sdk.GetErrMsg());
   }
   else
   {
        printf("add_weibo_pic sucess\n");
   }
   return 0;
} 
