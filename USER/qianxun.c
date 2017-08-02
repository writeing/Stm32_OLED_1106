#include  "w5500.h"
#include  "string.h"
#include  "socket_w5500.h"
#include  "dhcp.h"
#include  "main.h"
#include  "socket.h"
#include  "qxwz_rtcm.h"
#include  "prefs.h"


void qxwz_rtcm_response_callback(char* rtcm, size_t length)
{
	//printf("lenth = %d\r\n",length);
	for(int i = 0 ; i < length ; i++)
	{
		printf("%c",rtcm[i]);
	}
}
void qxwz_status_response_callback(qxwz_rtcm_status_code status)
{
//	if(status != 1014)
//		qxwz_soc_error(SOCKET_PORT);
	//qxwz_prefs_flags_set(QXWZ_PREFS_FLAG_ENABLE_LOG);
}
//509873
//f3932d08c9136c101fe150881d34f796570a5dbbdbff7f4f1582edd964a2b1a8
void initqianxun()
{
	qxwz_config config;  

  config.appkey = "509080";      

  config.appsecret= "2f91d3111b878f8371f709ac465d77866b75d3831d4e758b1117b83608c9f578";          

  config.device_ID = "853976858";                

  config.device_Type = "stm32";

  qxwz_setting(&config);  
	
	qxwz_start(qxwz_rtcm_response_callback,qxwz_status_response_callback);
}


qxwz_account_info *p_account_info = NULL;  


void get_qxwz_sdk_account_info(void)  
{  

	 p_account_info = getqxwzAccount();  

	 if(p_account_info->appkey != NULL) {  

			printf("appkey=%s\n",p_account_info->appkey);  

	}  

	 if(p_account_info->NtripPassword != NULL) {  
			printf("NtripPassword=%s\n",p_account_info->NtripPassword);  

	}  

	 if(p_account_info->NtripUserName != NULL) {  

			printf("NtripUserName=%s\n",p_account_info->NtripUserName);  

	}  

	 if(p_account_info->NtripPassword != NULL) {  

			printf("NtripPassword=%s\n",p_account_info->NtripPassword);  

	}  

	 printf("expire_time=%d\n",p_account_info->expire_time);  

}  


qxwz_soc qxwz_soc_create(void)
{
	uint16_t any_port = 	50000;
	int32_t ret;
	uint8_t sw = getSn_SR(SOCKET_PORT);
	if(sw == SOCK_CLOSED)
	{
		close(SOCKET_PORT);
		if((ret=socket(SOCKET_PORT, Sn_MR_TCP, any_port++, 0x00)) != SOCKET_PORT)	
		{
			printf("don't create port\r\n");
		}
		printf("create port success \r\n");
  }
	return SOCKET_PORT;
}


int8_t qxwz_soc_connect(qxwz_soc soc,qxwz_soc_address address)
{
	int32_t ret;
	printf("ip = %s\r\n",address.hostName);
	printf("port = %d\r\n", address.port);
	uint8_t ip[] = {59,110,144,131};
	uint16_t port =  8000;
	if(address.port == 8002)
	{
		ip[0] = 101;
		ip[1] = 201;
		ip[2] = 173;
		ip[3] = 70;
		port = 8002;
	}
	uint8_t sw = getSn_SR(SOCKET_PORT);
	if(sw == SOCK_INIT)
	{
		if( (ret = connect(SOCKET_PORT, ip, port)) != SOCK_OK) 
		{
			printf("connect error %s:%d\r\nr",address.hostName,ret);			
		}
		else		
			printf("connect success %s:%d\r\n",address.hostName,ret);
  }
	return 0;    
}

qxwz_ssize_t qxwz_soc_send(qxwz_soc soc,char *send_buffer,size_t length)
{
	uint8_t sw = getSn_SR(SOCKET_PORT);
	//printf("send = %s\r\n",send_buffer);
	return (qxwz_ssize_t)send(SOCKET_PORT, (uint8_t *)send_buffer, length); 
}

void qxwz_soc_close(qxwz_soc soc)
{
	uint8_t sw = getSn_SR(SOCKET_PORT);
	//printf("close sw = %X\r\n",sw);
	disconnect(SOCKET_PORT);
	close(SOCKET_PORT);
}

int socTime = 1;
void tick_time()
{
		qxwz_tick((socTime++)*1000);		
}



