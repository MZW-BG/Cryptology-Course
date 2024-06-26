#include<stdio.h>
#include<string.h>
#include <stdlib.h>

//IP置换矩阵
int IP_Table[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7 };
//扩展矩阵
int E_Table[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1 };
//P盒
int P_Table[32] = {
    16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
    2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25 };
//逆IP置换矩阵
int IPR_Table[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25 };
//密钥第一次置换矩阵
int PC1_Table[56] = {
    57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4 };
//密钥第二次置换矩阵
int PC2_Table[48] = {
    14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };
//8个S盒   三维数组
int S_Box[8][4][16] = {
    // S1
    14, 4,  13, 1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
    0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
    4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
    // S2
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
    3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
    0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
    // S3
    10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
    1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
    // S4
    7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
    10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
    3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
    // S5
    2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
    4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
    // S6
    12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
    10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
    9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
    4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
    // S7
    4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
    1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
    6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
    // S8
    13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
    1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
    7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
    2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

//把CHAR转换为INT
static void CharToBit(const char input[], int output[], int bits) {
    int i, j;
    for (j = 0; j < 8; j++) {
        for (i = 0; i < 8; i++) {
            output[8 * j + 7 - i] = (input[j] >> i) & 1;
        }
    }
};

//把INT转换为CHAR
static void BitToChar(const int intput[], char output[], int bits) {
    int i, j;
    for (j = 0; j < 8; j++) {
        for (i = 0; i < 8; i++) {
            output[j] = output[j] * 2 + intput[i + 8 * j];
        }
    }
};

//3.3.1.1 E扩展32->48
static void E(const int input[32], int output[48], int table[48]) {
    /*补充代码，利用表table将输入的32比特扩展成48比特*/

    for(int i=0;i<48;i++)
    {
    	output[i]=input[table[i]-1];
	}
};

//3.3.1.2 异或
static void Xor(int* INA, int* INB, int len) {
    /*补充代码，实现异或功能*/

    for(int i=0;i<len;i++)
    {
    	if(INA[i]==INB[i]){
    		INA[i]=0;
		}
		else
		{
			INA[i]=1; 
		}
	}
    
};

//3.3.1.3 S盒压缩
static void S(const int input[48], int output[32], int table[8][4][16]) {
    /*补充代码，利用表table将输入数据48比特压缩为32比特*/

    for(int i=0;i<8;i++)//s盒的编号 
    {
    	
    	int row=input[i*6]*2+input[i*6+5];
    	int col=input[i*6+1]*8+input[i*6+2]*4+input[i*6+3]*2+input[i*6+4];
    	int num=table[i][row][col];
    	for(int j=0;j<4;j++)
		{
			output[i*4+3-j]=num%2;
			num=num/2;
		}   	
		
	}
};

//3.3.1.4  P置换
static void P(const int input[32], int output[32], int table[32]) {
    /*补充代码，利用表table将输入数据置换*/
 
    for(int i=0;i<32;i++)
    {
    	output[i]=input[table[i]-1];
	}
    
};

//3.3.1 f轮函数（完成DES算法轮变换,就是f函数的内部实现）
static void F_func(int input[32], int output[32], int subkey[48]) {
    int len = 48;
    int temp[48] = { 0 };
    int temp_1[32] = { 0 };

    /*根据以上函数及定义的参数补全代码，提示：需要四步函数调用*/

    E(input,temp,E_Table);
    Xor(temp,subkey,48);
    S(temp,temp_1,S_Box);
    P(temp_1,output,P_Table);
};

//3.1 初始置换IP（64->64,左右分别32）
static void IP(const int input[64], int output[64], int table[64]) {
    /*补充代码，利用表table将输入数据置换*/
   
    for(int i=0;i<64;i++)
    {
    	output[i]=input[table[i]-1];
	}
};

//3.4逆置换
static  void IP_In(const int input[64], int output[64], int table[64]) {
    /*补充代码，利用表table将输入数据置换*/

    for(int i=0;i<64;i++)
    {
    	output[i]=input[table[i]-1];
	}
};

//PC_1，用于密钥置换
static void PC_1(const int input[64], int output[56], int table[56]) {
    int i;
    for (i = 0; i < 56; i++) {
        output[i] = input[table[i] - 1];
    }
};
//PC_2，用于密钥置换
static void PC_2(const int input[56], int output[48], int table[48]) {
    int i;
    for (i = 0; i < 48; i++) {
        output[i] = input[table[i] - 1];
    }
};

//密钥循环左移
static void RotateL(const int input[28], int output[28], int leftCount) {
    int i;
    int len = 28;//因为不是位运算，所以可以不用unsigned
    for (i = 0; i < len; i++) {
        output[i] = input[(i + leftCount) % len];
    }
};

//子密钥生成
static void subKey_fun(const int input[64], int Subkey[16][48]) {//注意输入和输出的位数,int只存放01,密钥为18位16轮
    int loop = 1, loop_2 = 2;
    int i, j;
    int c[28], d[28];
    int pc_1[56] = { 0 };
    int pc_2[16][56] = { 0 };
    int rotatel_c[16][28] = { 0 };
    int rotatel_d[16][28] = { 0 };
    PC_1(input, pc_1, PC1_Table);
    for (i = 0; i < 28; i++) {
        c[i] = pc_1[i];//L
        d[i] = pc_1[i + 28];//R
    }
    int leftCount = 0;
    for (i = 1; i < 17; i++) {
        if (i == 1 || i == 2 || i == 9 || i == 16) {//左移一位
            leftCount += loop;
            RotateL(c, rotatel_c[i - 1], leftCount);
            RotateL(d, rotatel_d[i - 1], leftCount);
        }
        else {//左移两位
            leftCount += loop_2;
            RotateL(c, rotatel_c[i - 1], leftCount);
            RotateL(d, rotatel_d[i - 1], leftCount);
        }
    }
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 28; j++) {
            pc_2[i][j] = rotatel_c[i][j];
            pc_2[i][j + 28] = rotatel_d[i][j];
        }
    }
    for (i = 0; i < 16; i++) {
        PC_2(pc_2[i], Subkey[i], PC2_Table);
    }
};


//3 加密实现
static void  DES_Efun(char input[8], char key_in[8], int output[64]) {
    int Ip[64] = { 0 };//存储初始置换后的矩阵
    int output_1[64] = { 0 };
    int subkeys[16][48];
    int chartobit[64] = { 0 };
    int key[64];
    int l[17][32], r[17][32];

    CharToBit(input, chartobit, 8);//转换为64个二进制数
    // 3.1初始置换
    /*补充代码，调用函数实现初始置换，并输出置换结果*/
    IP(chartobit,Ip,IP_Table);
    for(int i=0;i<4;i++)
    {
    	for(int j=0;j<16;j++)
    	{
    		printf("%d",Ip[i*16+j]);
		 } 
		 printf("\n");

	}
    printf("\n");

    //子密钥生成
    CharToBit(key_in, key, 8);
    subKey_fun(key, subkeys);

    //3.2数据块分组
    for (int i = 0; i < 32; i++) {
        l[0][i] = Ip[i];
        r[0][i] = Ip[32 + i];
    }

    printf("L0：\n");
    for (int i = 0; i < 32; i++) {
        printf("%d", l[0][i]);
        if ((i + 1) % 8 == 0)
            printf("\n");
    }
    printf("\n");
    printf("R0：\n");
    for (int i = 0; i < 32; i++) {
        printf("%d", r[0][i]);
        if ((i + 1) % 8 == 0)
            printf("\n");
    }
    printf("\n");

    //3.3 迭代加密
    /*补充代码，调用函数实现16轮迭代过程*/
    for(int i=1;i<=16;i++)
    {
    	for(int j=0;j<32;j++)
    	{
    		l[i][j]=r[i-1][j];
		}
		F_func(r[i-1],r[i],subkeys[i-1]);
		Xor(r[i],l[i-1],32);
	}
	
	for(int i=0;i<32;i++)
	{
		output_1[i]=r[16][i];
	} 
	for(int i=0;i<32;i++)
	{
		output_1[i+32]=l[16][i];
	}
    printf("16轮迭代：\n");
    for (int i = 0; i < 64; i++) {
        printf("%d", output_1[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    printf("\n");

    //3.4 逆置换
    /*补充代码，调用函数实现逆置换*/
    IP_In(output_1,output,IPR_Table);
    
   
};


//4 解密实现
static void  DES_Dfun(int input[64], char key_in[8], char output[8]) {
    /*根据加密代码补全解密部分代码*/
    int Ip[64] = { 0 };//存储初始置换后的矩阵
    int output_1[64] = { 0 };
    int subkeys[16][48];
    int chartobit[64] = { 0 };
    int key[64];
    int l[17][32], r[17][32];
    // 3.1初始置换
    /*补充代码，调用函数实现初始置换，并输出置换结果*/
    IP(input,Ip,IP_Table);
    //子密钥生成
    CharToBit(key_in, key, 8);
    subKey_fun(key, subkeys);

    //3.2数据块分组
    for (int i = 0; i < 32; i++) {
       l[0][i] = Ip[i];
       r[0][i] = Ip[32 + i];
    }
    //3.3 迭代解密
    /*补充代码，调用函数实现16轮迭代过程*/
    for(int i=1;i<=16;i++)
    {
    for(int j=0;j<32;j++)
    	{
    		l[i][j]=r[i-1][j];
		}
		F_func(r[i-1],r[i],subkeys[16-i]);
		Xor(r[i],l[i-1],32);
	}
	
	for(int i=0;i<32;i++)
	{
		output_1[i]=r[16][i];
	} 
	for(int i=0;i<32;i++)
	{
		output_1[i+32]=l[16][i];
	}
    //3.4 逆置换
    /*补充代码，调用函数实现逆置换*/
    int output_2[64]={0};
    IP_In(output_1,output_2,IPR_Table);
    BitToChar(output_2,output,8);

};


int main() {
    int output[64] = { 0 };
    char MIN[9] = { 0 };
    char MI[9] = { 0 };
    //1、输入明文
    printf("请输入明文\n");
    gets(MIN);
    printf("\n");
    //2、输入密钥
    printf("请输入密钥\n");
    gets(MI);
    printf("\n");
    //3、加密
    DES_Efun(MIN, MI, output);
    printf("密文如下:\n");

    for (int i = 0; i < 64; i++) {
        printf("%d", output[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    printf("\n");
    printf("解密功能\n");
    //4、解密
    DES_Dfun(output, MI, MIN);
    printf("明文如下:\n");
    for (int i = 0; i < 8; i++) {
        printf("%c", MIN[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}
