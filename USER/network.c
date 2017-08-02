#include  "w5500.h"
#include  "string.h"
#include  "socket_w5500.h"
#include  "dhcp.h"
#include  "main.h"
#include  "stdio.h"


//u32 W5500_Send_Delay=0; //W5500发送延时计数变量(ms)
wiz_NetInfo gWIZNETINFO;

////装载网络参数
////说明: 网关、子网掩码、物理地址、本机IP地址、本机端口号、目的IP地址、目的端口号、端口工作模式
void Load_Net_Parameters(void)
{
	gWIZNETINFO.gw[0] = 192;//加载网关参数
	gWIZNETINFO.gw[1] = 168;
	gWIZNETINFO.gw[2] = 1;
	gWIZNETINFO.gw[3] = 2;

	gWIZNETINFO.sn[0]=255;//加载子网掩码
	gWIZNETINFO.sn[1]=255;
	gWIZNETINFO.sn[2]=255;
	gWIZNETINFO.sn[3]=0;
	

	
	gWIZNETINFO.mac[0]=0x0c;//加载物理地址
	gWIZNETINFO.mac[1]=0x29;
	gWIZNETINFO.mac[2]=0xab;
	gWIZNETINFO.mac[3]=0x7c;
	gWIZNETINFO.mac[4]=0x00;
	gWIZNETINFO.mac[5]=0x01;

	gWIZNETINFO.ip[0]=192;//加载本机IP地址
	gWIZNETINFO.ip[1]=168;
	gWIZNETINFO.ip[2]=1;
	gWIZNETINFO.ip[3]=246;
	
	gWIZNETINFO.dhcp = NETINFO_STATIC;
}
uint8_t destip[4] = 	{59, 110, 144, 131};
uint16_t destport = 	8000;
uint8_t buf[1500];

int32_t loopback_tcpc(uint8_t sn, uint8_t* buf, uint8_t* destip, uint16_t destport)
{
   int32_t ret; // return value for SOCK_ERRORs
   uint16_t size = 0, sentsize=0;

   // Destination (TCP Server) IP info (will be connected)
   // >> loopback_tcpc() function parameter
   // >> Ex)
//   	uint8_t destip[4] = 	{192, 168, 1, 121};
//  	uint16_t destport = 	6000;

   // Port number for TCP client (will be increased)
   uint16_t any_port = 	50000;
	 uint8_t sw = getSn_SR(sn);	 
	 printf("sw = %d\r\n",sw);
   switch(sw)
   {
      case SOCK_ESTABLISHED :
         if(getSn_IR(sn) & Sn_IR_CON)	// Socket n interrupt register mask; TCP CON interrupt = connection with peer is successful
         {
#ifdef _LOOPBACK_DEBUG_
			     printf("%d:Connected to - %d.%d.%d.%d : %d\r\n",sn, destip[0], destip[1], destip[2], destip[3], destport);
#endif
			     setSn_IR(sn, Sn_IR_CON);  // this interrupt should be write the bit cleared to '1'
         }

         //////////////////////////////////////////////////////////////////////////////////////////////
         // Data Transaction Parts; Handle the [data receive and send] process
         //////////////////////////////////////////////////////////////////////////////////////////////
		     if((size = getSn_RX_RSR(sn)) > 0) // Sn_RX_RSR: Socket n Received Size Register, Receiving data length
         {
			     if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE; // DATA_BUF_SIZE means user defined buffer size (array)
			     ret = recv(sn, buf, size); // Data Receive process (H/W Rx socket buffer -> User's buffer)
					 
			     if(ret <= 0) 
						 return ret; // If the received data length <= 0, receive failed and process end
			     sentsize = 0;
//					while(size != sentsize)
//			    {
//						printf("buf = %s\r\n",buf);
//			    	ret = send(sn, buf+sentsize, size-sentsize); // Data send process (User's buffer -> Destination through H/W Tx socket buffer)
//			    	if(ret < 0) // Send Error occurred (sent data length < 0)
//				    {
//				    	close(sn); // socket close
//				    	return ret;
//			     	}
//				    sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
//			    }
					 return size;
			// Data sentsize control

         }
		 //////////////////////////////////////////////////////////////////////////////////////////////
         break;
      case SOCK_CLOSE_WAIT :
#ifdef _LOOPBACK_DEBUG_
         //printf("%d:CloseWait\r\n",sn);
#endif
         if((ret=disconnect(sn)) != SOCK_OK) return ret;
#ifdef _LOOPBACK_DEBUG_
         printf("%d:Socket Closed\r\n", sn);
#endif
         break;

      case SOCK_INIT :
//#ifdef _LOOPBACK_DEBUG_
//    	     printf("%d:Try to connect to the %d.%d.%d.%d : %d\r\n", sn, destip[0], destip[1], destip[2], destip[3], destport);
//#endif
//    	     if( (ret = connect(sn, destip, destport)) != SOCK_OK) return ret;	//	Try to TCP connect to the TCP server (destination)
//             break;

      case SOCK_CLOSED:
    	     close(sn);
    	     if((ret=socket(sn, Sn_MR_TCP, any_port++, 0x00)) != sn) return ret; // TCP socket open with 'any_port' port number
#ifdef _LOOPBACK_DEBUG_
    	    //printf("%d:TCP client loopback start\r\n",sn);
          //printf("%d:Socket opened\r\n",sn);
#endif
         break;
      default:
         break;
   }
   return 0;
}


void network_init(void)
{
//  uint8_t tmpstr[6];	
	ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);	
//	ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);
//	// Display Network Information
//	ctlwizchip(CW_GET_ID,(void*)tmpstr);
//	printf("\r\n=== %s NET CONF ===\r\n",(char*)tmpstr);
//	printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],
//				gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
//	printf("SIP: %d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
//	printf("GAR: %d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
//	printf("SUB: %d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
//	printf("DNS: %d.%d.%d.%d\r\n", gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);
//	printf("======================\r\n");
}
void my_ip_assign(void)
{
   getIPfromDHCP(gWIZNETINFO.ip);
   getGWfromDHCP(gWIZNETINFO.gw);
   getSNfromDHCP(gWIZNETINFO.sn);
   getDNSfromDHCP(gWIZNETINFO.dns);
   gWIZNETINFO.dhcp = NETINFO_DHCP;
   /* Network initialization */
   network_init();      // apply from dhcp
   printf("DHCP LEASED TIME : %d Sec.\r\n", getDHCPLeasetime());
}
void my_ip_conflict(void)
{
	printf("CONFLICT IP from DHCP\r\n");
	//halt or reset or any...
	while(1); // this example is halt.
}


