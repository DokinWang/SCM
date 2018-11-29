#ifndef _DYNAMICLINKLIBRARYLOADER_H_
#define _DYNAMICLINKLIBRARYLOADER_H_

#include "../../../../DynamicLinkLibrary/source/User/DynamicLinkLibrary/DynamicLinkLibrary.h"
#include "../../Support/stm32f4xx.h"


#define ADDR_DLL  0x08004000  // ������ļ�ϵͳ���ʹ��ļ�ϵͳ��ȡ��ַ����������������ʽ��ȡ��ַ���������ǿ��Ա仯�ģ�������Ժ�ķ�ʽ���̶���ַ�� 


#define     SIZE_DLL_MEM    48
#define     SIZE_MEM_INT    SIZE_DLL_MEM / sizeof(unsigned int)


extern Fun DelayUs;
extern TFun RunHostFun;
extern void LED_B_Control(unsigned int sw);
extern void DynamicLoader(unsigned int AddrDynamicLinkLib);

#endif /* _DYNAMICLINKLIBRARYLOADER_H_ */
