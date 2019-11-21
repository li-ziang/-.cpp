#include <cstring>
#include <math.h>
#include<tchar.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//ʵ���ļ��ĺ��� 
void fpBin(FILE* out, int num, int len){
    for (int i = 0; i<len; ++i){
        unsigned char buf = num & 255;
        fwrite(&buf,1,1,out);
        num >>= 8;
    }
}
int W,H,R,G,B,Cur_X,Cur_Y,Cur_A;//Cur_X�����ڵĺ����� Cur_Y�����ڵ������� ��Cur_A�����ڵĽǶȣ������Y�������򣬴�Y����X����������ת 
const int WIDTH=2000,HEIGHT=1200;//�������ĳ������� 
bool cloak=false;//��ʾ���ڻ�û������ 
vector<string> sentence;//�������Ҫ��ʱ��ŵľ��ӣ����ҿ��Զ����к� 

struct point{//ÿ�������bitmap�ϵ�һ���㣬ǰһ�������������꣬��һ���Ǻ����� 
	int red;
	int green;
	int blue;
}bitmap[HEIGHT][WIDTH];//����bitmap��ֻ���ǵ�bitmap 

//bmp�� 
void initialize(){//���ڳ�ʼ���ĺ��� 
    int width = W;
    int height = H;
    FILE* out = fopen("����.bmp", "wb");
    int fill = (4 - ((width * 3) & 3)) & 3;
    int size = height*(3*width+fill);
 
    fprintf(out, "BM");  //bfType
    fpBin(out, 0, 4);  //bfSize
    fpBin(out, 0, 2);  //bfReserved1
    fpBin(out, 0, 2);  //bfReserved2
    fpBin(out, 54, 4);  //bfOffBits
 
    fpBin(out, 40, 4);  //biSize
    fpBin(out, width, 4);  //biWidth
    fpBin(out, height, 4);  //biHeight
    fpBin(out, 1, 2);  //biPlanes
    fpBin(out, 24, 2);  //biBitCount
    fpBin(out, 0, 4);  //biCompression
    fpBin(out, 0, 4);  //biSizeImage
    fpBin(out, 0, 4);  //biXPelsPerMeter
    fpBin(out, 0, 4);  //biYPelsPerMeter
    fpBin(out, 0, 4);  //biClrUsed
    fpBin(out, 0, 4);  //biClrImportant
 
    for (int i = 0; i < height; ++i, fpBin(out, 0, fill)){ 
        for (int j = 0; j < width; ++j){
            fpBin(out, B, 1);//��ɫ 
            fpBin(out, G, 1);//��ɫ 
            fpBin(out, R, 1);//��ɫ 
		}
    }
    fclose(out);
}

void output(){//��������ĺ��� 
	int width = W;
    int height = H;
    FILE* out = fopen("����.bmp", "wb");
    int fill = (4 - ((width * 3) & 3)) & 3;
    int size = height*(3*width+fill);
 
    fprintf(out, "BM");  //bfType
    fpBin(out, 0, 4);  //bfSize
    fpBin(out, 0, 2);  //bfReserved1
    fpBin(out, 0, 2);  //bfReserved2
    fpBin(out, 54, 4);  //bfOffBits
 
    fpBin(out, 40, 4);  //biSize
    fpBin(out, width, 4);  //biWidth
    fpBin(out, height, 4);  //biHeight
    fpBin(out, 1, 2);  //biPlanes
    fpBin(out, 24, 2);  //biBitCount
    fpBin(out, 0, 4);  //biCompression
    fpBin(out, 0, 4);  //biSizeImage
    fpBin(out, 0, 4);  //biXPelsPerMeter
    fpBin(out, 0, 4);  //biYPelsPerMeter
    fpBin(out, 0, 4);  //biClrUsed
    fpBin(out, 0, 4);  //biClrImportant
 
    for (int i = 0; i < height; ++i, fpBin(out, 0, fill)){ 
        for (int j = 0; j < width; ++j){
            fpBin(out, bitmap[i][j].blue, 1);//��ɫ 
            fpBin(out, bitmap[i][j].green, 1);//��ɫ 
            fpBin(out, bitmap[i][j].red, 1);//��ɫ 
		}
    }
    fclose(out);
} 
//get��Ҫ��ȫ�ֱ��� ���������ȷ�� 
void getWH(){
	string a,b,c,d;
	cin>>a>>b>>c;
	W=stoi(b);
	H=stoi(c); 
	cin>>a>>b>>c>>d;
	R=stoi(b);
	G=stoi(c);
	B=stoi(d);
	cin>>a>>b>>c;
	Cur_X=stoi(b);
	Cur_Y=stoi(c);
	if(W<320||W>1920)throw"W��ֵ����ȡֵ��Χ��";
	if(H<240||H>1080)throw"H��ֵ����ȡֵ��Χ��";
	if(R<0||R>255)throw"R��ֵ����ȡֵ��Χ��";
	if(B<0||B>255)throw"B��ֵ����ȡֵ��Χ��";
	if(G<0||G>255)throw"G��ֵ����ȡֵ��Χ��";
	if(Cur_X>W-1||Cur_X<0)throw"X��ֵ����ȡֵ��Χ��"; 
	if(Cur_Y>H-1||Cur_Y<0)throw"Y��ֵ����ȡֵ��Χ��"; 
}
int _tmain(int argc, _TCHAR* argv[])
{	

	freopen("test.txt","r",stdin);//�����ļ���ʹ����������� 
	try{getWH();}//�õ���Ҫ����  
	catch (const char* msg) {cerr << msg;return 0;}
	initialize();
   //ע�������ļ��Ķ�������cin����
    //output();  
    return 0;
}

