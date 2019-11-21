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

//实现文件的函数 
void fpBin(FILE* out, int num, int len){
    for (int i = 0; i<len; ++i){
        unsigned char buf = num & 255;
        fwrite(&buf,1,1,out);
        num >>= 8;
    }
}
int W,H,R,G,B,Cur_X,Cur_Y,Cur_A;//Cur_X是现在的横坐标 Cur_Y是现在的纵坐标 ，Cur_A是现在的角度，相对于Y轴正方向，从Y轴向X轴正方向旋转 
const int WIDTH=2000,HEIGHT=1200;//最大允许的长度与宽度 
bool cloak=false;//表示现在还没有隐身 
vector<string> sentence;//用来存放要临时存放的句子，并且可以读得行号 

struct point{//每个点就是bitmap上的一个点，前一个参数是纵坐标，后一个是横坐标 
	int red;
	int green;
	int blue;
}bitmap[HEIGHT][WIDTH];//整个bitmap就只我们的bitmap 

//bmp类 
void initialize(){//用于初始化的函数 
    int width = W;
    int height = H;
    FILE* out = fopen("桌面.bmp", "wb");
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
            fpBin(out, B, 1);//蓝色 
            fpBin(out, G, 1);//绿色 
            fpBin(out, R, 1);//红色 
		}
    }
    fclose(out);
}

void output(){//用于输出的函数 
	int width = W;
    int height = H;
    FILE* out = fopen("桌面.bmp", "wb");
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
            fpBin(out, bitmap[i][j].blue, 1);//蓝色 
            fpBin(out, bitmap[i][j].green, 1);//绿色 
            fpBin(out, bitmap[i][j].red, 1);//红色 
		}
    }
    fclose(out);
} 
//get重要的全局变量 并检查其正确性 
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
	if(W<320||W>1920)throw"W的值不在取值范围中";
	if(H<240||H>1080)throw"H的值不在取值范围中";
	if(R<0||R>255)throw"R的值不在取值范围中";
	if(B<0||B>255)throw"B的值不在取值范围中";
	if(G<0||G>255)throw"G的值不在取值范围中";
	if(Cur_X>W-1||Cur_X<0)throw"X的值不在取值范围中"; 
	if(Cur_Y>H-1||Cur_Y<0)throw"Y的值不在取值范围中"; 
}
int _tmain(int argc, _TCHAR* argv[])
{	

	freopen("test.txt","r",stdin);//打开文文件并使得其进入流中 
	try{getWH();}//得到重要参数  
	catch (const char* msg) {cerr << msg;return 0;}
	initialize();
   //注意现在文件的东西还在cin里面
    //output();  
    return 0;
}

