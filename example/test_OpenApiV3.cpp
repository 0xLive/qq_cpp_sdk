/**
 * OpenAPI V3 SDK ʾ�����룬�����ڴ󲿷�OpenAPI��������ϴ��ļ���OpenAPI����ο���SDK���еġ�Test_UploadFile.cpp���ļ��е�ʾ�����롣
 *
 * @version 3.0.0
 * @author open.qq.com
 * @copyright (c) 2013, Tencent Corporation. All rights reserved.
 * @History:
 *               3.0.0 | jixingguan | 2013-05-07 10:20:12 | initialization
 */


#include "OpenApiV3.h"

struct  userinfo
{
    int ret;
    int is_lost;
    string nickname;
    string gender;
    string country;
    string province;
    string city;
    string figureurl;
    int is_yellow_vip;
    int is_yellow_year_vip;
    int yellow_vip_level;
    int is_yellow_high_vip;
    userinfo()
	{
        ret =0;
		is_lost = 0;
		is_yellow_vip =0;
		is_yellow_year_vip=0;
		yellow_vip_level=0;
		is_yellow_high_vip=0;
	}
};

/***********************************************************
**������ get_user_info
**����:   
**          sdk  
**          openid :
**          openkey:  
**          PF
**
**���:  JsonRes  ������Ӧ��
**              
**����:��
**����:
**           ����/v3/user/get_info�ӿ�
**************************************************************/

int get_user_info(class OpenApiV3* sdk, string& openid, string& openkey, string& pf,Json::Value& JsonRes)
{
    map<string,string> params;
    string script_name;

    params["openid"]=openid;
    params["openkey"]=openkey;
    params["pf"]=pf;

	script_name = "/v3/user/get_info";
    
	
	return sdk->api(script_name, params,JsonRes);	
}


/***********************************************************
**������ get_user_info_parse
**����:   
                JsonRes  ��Ӧ��json����

**���:  Info ������Ľṹ 
**              
**����:��
**����:
**           ����/v3/user/get_info�ӿ�,
               ʾ��������JSON��ʽ�ı��Ľ��н���
**************************************************************/

int get_user_info_parse(Json::Value& JsonRes ,struct userinfo& Info)
{

    Info.ret= JsonRes["ret"].asInt();
    if( 0 == Info.ret)
    {
        Info.is_lost= JsonRes["is_lost"].asInt();
        Info.nickname = JsonRes["nickname"].asString();
        Info.gender =  JsonRes["gender"].asString();
        Info.country = JsonRes["country"].asString();
        Info.province = JsonRes["province"].asString();
        Info.city = JsonRes["city"].asString();
        Info.figureurl = JsonRes["figureurl"].asString();
        Info.is_yellow_vip = JsonRes["is_yellow_vip"].asInt();
        Info.is_yellow_year_vip = JsonRes["is_yellow_year_vip"].asInt();
        Info.yellow_vip_level = JsonRes["yellow_vip_level"].asInt();
        Info.is_yellow_high_vip = JsonRes["is_yellow_high_vip"].asInt();
    }    
    return 0;
}


int main(int argc,char** argv)
{
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
    
    COpenApiV3 sdk(appid, appkey);      
    //�����ʼ�������÷�������ַ
    sdk.init();
    sdk.setServerName(server_name);
    sdk.setDebugSwitch(true);    
   
    Json::Value JsonRes;  
    struct userinfo Info;
    int iRet=get_user_info(&sdk, openid, openkey, pf,JsonRes);
    if( 0 != iRet)
    {
        printf("iRet=%d err:%s\n",iRet,sdk.GetErrMsg());
    }
    else
    {
        //�Է��ص���Ϣ���н���
        get_user_info_parse(JsonRes,Info);
        printf("Info.ret=%d\n",Info.ret);
        printf("Info.is_lost=%d\n",Info.is_lost);
        printf("Info.nickname=%s\n",Info.nickname.c_str());
        printf("Info.country=%s\n",Info.country.c_str());
        printf("Info.province=%s\n",Info.province.c_str());
        printf("Info.city=%s\n",Info.city.c_str());
        printf("Info.figureurl=%s\n",Info.figureurl.c_str());
        printf("Info.is_yellow_vip=%d\n",Info.is_yellow_vip);
        printf("Info.is_yellow_year_vip=%d\n",Info.is_yellow_year_vip);
        printf("Info.yellow_vip_level=%d\n",Info.yellow_vip_level);
        printf("Info.is_yellow_high_vip=%d\n",Info.is_yellow_high_vip);
    }
    return 0;
} 

