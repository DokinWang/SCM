            
DLL_VERSION EQU 0x00000008

                         
        AREA    FunctionArray, DATA, READONLY, ALIGN=0


Fun_Start

       ;IMPORT  |Image$$LR_IROM1$$Length| 
        IMPORT  |Image$$ER_IROM1$$Length| 
        IMPORT  |Image$$RW_IRAM1$$Length| 
        IMPORT  |Image$$ER_IROM2$$Length|            
            
        IMPORT  |Image$$ER_IROM1$$RO$$Base|
        IMPORT  |Image$$RW_IRAM1$$RO$$Base|  
        IMPORT  |Image$$ER_IROM2$$RO$$Base|    

        IMPORT  |Image$$ER_IROM1$$RO$$Limit|
        IMPORT  |Image$$RW_IRAM1$$RO$$Limit|  
        IMPORT  |Image$$ER_IROM2$$RO$$Limit|    
           
        ;IMPORT  DelayUs
        ;ENTRY  
        DCD     |Image$$ER_IROM1$$Length| + |Image$$RW_IRAM1$$Length| + |Image$$ER_IROM2$$Length|   
            ; - |Image$$ER_IROM1$$RO$$Base| ;0x000000C4              ;//��̬��ĳ���
        DCD     DLL_VERSION  ;0x00000007  ;��̬��汾 version   
            
        DCD     |Image$$ER_IROM1$$Length| ;  |Image$$ER_IROM2$$RO$$Limit| - |Image$$ER_IROM1$$RO$$Base|   ;   ;;;; |Image$$ER_IROM2$$RO$$Limit| - |Image$$ER_IROM1$$RO$$Base|;;|Image$$ER_IROM1$$RO$$Limit| ; |Image$$RW_IRAM1$$RO$$Base| ;- |Image$$ER_IROM1$$RO$$Base|  ;0x080040B4 - 0x08004000    ;// ��̬������ƫ�Ƶ�ַ
        DCB     "DelayUs" 
        ;DCB     "%"     ;ע��Ҫ��%����ȱ���������DCDָ���4����ַ��    �����ARM Code������&�����
        ;��������β����%��ʾ�� Thumb Code�������&,Ҳ��ʾ�Ǻ�������β����&��ʾ��ARM Code
        DCD     0x0800404C - 0x08004000 + 1   ;��Thumb Code�Ļ����Լ���1

        DCB     "RunHostFun"
        ;DCB     "%%"                  ;ע��Ҫ��%����ȱ���������DCDָ���4����ַ��   �����ARM Code������&�����
        DCD     0x08004064 - 0x08004000 + 1  ;��Thumb Code�Ļ����Լ���1
    
        DCB     "StaticVarInit" 
        ;DCB     "%%%"               ;ע��Ҫ��%����ȱ���������DCDָ���4����ַ��    �����ARM Code������&�����
        DCD     0x080040A4 - 0x08004000 + 1        ;��Thumb Code�Ļ����Լ���1
    
        END




