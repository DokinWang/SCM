#include "DynamicLinkLibraryLoader.h"

__global_reg(6) unsigned int *StaticVariableRelocate;

extern unsigned int *DynamicStaticVar=0;// ָ��dll�ľ�̬����
extern unsigned int HostStaticVar = 0x123455AA;

Fun DelayUs = 0;
TFun RunHostFun = 0;
NFun StaticVarInit = 0;

static unsigned int DLL_Len = 0;
static unsigned int DLL_Version = 0;    

static unsigned int  __attribute__((aligned(8))) DynamicRAM[SIZE_MEM_INT];  

unsigned int Name2Addr(unsigned int addr,unsigned char *src,unsigned char len)
{
    unsigned char *targ = (unsigned char *)(addr);
    unsigned int i = 8,j;
    unsigned int tmp;
    

FindHead:    
    for(j = 0; i < DLL_Len; i ++){// ��ͷ
        if(src[j] == targ[i]){
            j ++;
            i ++;
            break;
        }
    }
    if((i + len) < DLL_Len){// û����
        
    }else{
        return 0;
    }
    
    for(; j < len; j ++,i++){
        if(src[j] != targ[i]){
            goto FindHead;
        }
    }
#if     0    
    if(j == len){// �ҵ�����
        if('%' == targ[i]){ //
            while(1){
                if(targ[i] != '%'){
                    break;
                }else{
                    i ++;
                }
            }
            if((i+4)<DLL_Len){//���ȹ�                
                return  ((targ[i+0] << 8*0) | 
                         (targ[i+1] << 8*1) |
                         (targ[i+2] << 8*2) |
                         (targ[i+3] << 8*3) );
            }
        }        
    }
#else
    if(j == len){// �ҵ�����
        tmp = 4 - len & (4 - 1);
        return  ((targ[i+0+tmp] << 8*0) | 
                 (targ[i+1+tmp] << 8*1) |
                 (targ[i+2+tmp] << 8*2) |
                 (targ[i+3+tmp] << 8*3) ); 
    }
#endif    
    return 0;
}

extern void DynamicLoader(unsigned int AddrDynamicLinkLib)
{
    unsigned int *dst,*src;
    unsigned int *RAM_ADDRESS_DLY = (unsigned int *)DynamicRAM;    
    unsigned int DLL_Static_len,DLL_Static_offset_addr;
    unsigned int i;
    
    
    DLL_Len = *((unsigned int *)AddrDynamicLinkLib);// ��DLL�׵�ַ��ȡ���ļ�����    
    DLL_Version = *((unsigned int *)(AddrDynamicLinkLib + 4));// ��DLL�׵�ַ֮���ȡDLL�汾��
    DLL_Static_offset_addr = *((unsigned int *)(AddrDynamicLinkLib + 8));// ��̬���о�̬������ƫ�Ƶ�ַ
    DLL_Static_len = DLL_Len - DLL_Static_offset_addr;//��̬���о�̬������ȫ��

   
        //��ʼ����̬����
    for(i = 0,dst = RAM_ADDRESS_DLY,src = (unsigned int *)(AddrDynamicLinkLib + DLL_Static_offset_addr); i < ((DLL_Static_len / 4) + 1); i ++){
        *dst ++= *src ++;
    }
    // ��ʼ��������Ҫ�õĵ�������ַ
    DelayUs =           (Fun)   (Name2Addr(AddrDynamicLinkLib,"DelayUs",7)                  + (unsigned int)AddrDynamicLinkLib);
    RunHostFun =        (TFun)  (Name2Addr(AddrDynamicLinkLib,"RunHostFun",10)              + (unsigned int)AddrDynamicLinkLib);   
    StaticVarInit =     (NFun)  (Name2Addr(AddrDynamicLinkLib,"StaticVarInit",13)           + (unsigned int)AddrDynamicLinkLib); 
    
    StaticVariableRelocate = (unsigned int *)((unsigned int)RAM_ADDRESS_DLY);    
    StaticVarInit((unsigned int)LED_B_Control,&DynamicStaticVar,&HostStaticVar);
}

