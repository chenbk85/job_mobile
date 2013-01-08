#ifndef __Define_H__
#define __Define_H__
#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#ifdef va_start
//#undef va_start
//
//#ifdef _WIN32
//#define va_start(ap,v){int var=_INTSIZEOF(v); __asm lea eax,v __asm add eax,var __asm mov ap,eax }
//#else
//#define va_start(ap,v){ int var=_INTSIZEOF(v); __asm lea ax,v __asm add ax,var __asm mov ap,ax }
//#endif
//#endif

typedef unsigned long DWORD_PTR;

#define SameAnd(a,b)                    ((a)==(b))
#define SameAnd12(v,a,b)                (((a)==(v))&&((b)==(v)))
#define SameAnd13(v,a,b,c)              (((a)==(v))&&((b)==(v))&&((c)==(v)))
#define SameAnd22(a1,a2,b1,b2)          (((a1)==(a2))&&((b1)==(b2)))
#define SameAnd23(a1,a2,b1,b2,c1,c2)    (((a1)==(a2))&&((b1)==(b2))&&((c1)==(c2)))

#define SameOr(a,b)                     ((a)==(b))
#define SameOr12(v,a,b)                 (((a)==(v))||((b)==(v)))
#define SameOr13(v,a,b,c)               (((a)==(v))||((b)==(v))||((c)==(v)))
#define SameOr22(a1,a2,b1,b2)           (((a1)==(a2))||((b1)==(b2)))
#define SameOr23(a1,a2,b1,b2,c1,c2)     (((a1)==(a2))||((b1)==(b2))||((c1)==(c2)))

#define DiffAnd(a,b)                    ((a)!=(b))
#define DiffAnd12(v,a,b)                (((a)!=(v))&&((b)!=(v)))
#define DiffAnd13(v,a,b,c)              (((a)!=(v))&&((b)!=(v))&&((c)!=(v)))
#define DiffAnd22(a1,a2,b1,b2)          (((a1)!=(a2))&&((b1)!=(b2)))
#define DiffAnd23(a1,a2,b1,b2,c1,c2)    (((a1)!=(a2))&&((b1)!=(b2))&&((c1)!=(c2)))

#define DiffOr(a,b)                     ((a)!=(b))
#define DiffOr12(v,a,b)                 (((a)!=(v))||((b)!=(v)))
#define DiffOr13(v,a,b,c)               (((a)!=(v))||((b)!=(v))||((c)!=(v)))
#define DiffOr22(a1,a2,b1,b2)           (((a1)!=(a2))||((b1)!=(b2)))
#define DiffOr23(a1,a2,b1,b2,c1,c2)     (((a1)!=(a2))||((b1)!=(b2))||((c1)!=(c2)))

#define SwitchSame(a,b)                 ((a)==(b))
#define SwitchSame22(a1,a2,b1,b2)       ((((a1)==(a2))&&((b1)==(b2)))||(((a1)==(b2))&&((b1)==(a2))))
#define SwitchSame23(a1,a2,b1,b2,c1,c2) ((((a1)==(a2))&&((b1)==(b2))&&((c1)==(c2)))||(((a1)==(a2))&&((b1)==(c2))&&((c1)==(b2))) \
                                       ||(((a1)==(b2))&&((b1)==(a2))&&((c1)==(c2)))||(((a1)==(b2))&&((b1)==(c2))&&((c1)==(a2))) \
                                       ||(((a1)==(c2))&&((b1)==(a2))&&((c1)==(b2)))||(((a1)==(c2))&&((b1)==(b2))&&((c1)==(a2))))

#define RANDOM_MAX               0x7fff
#define SRandom                  (srand((unsigned int)time(NULL)))
#define SeedSRandom(s)           (srand((unsigned int)(s)))
#define IRandom(r)               (rand()%(r))
#define FRandomF(r)              (((float)rand()/(float)RANDOM_MAX)%((float)r))
#define RandomRange(min,max)     ((rand()%(int)(((max)+1)-(min)))+(min))

#define ReturnNull(x,r)          if(NULL==(x)){return(r);}
#define ReturnSame(x,n,r)        if((n)==(x)){return(r);}
#define ReturnNoSame(x,n,r)      if((n)!=(x)){return(r);}

#define RangeInValue(n,m,v)      (((n)>(v))?((n)):(((m)<(v))?(m):(v)))
#define RangeInValueLoop(n,m,v)  (((n)>(v))?((m)):(((m)<(v))?(n):(v)))
#define IsInRange(v,n,m)         (((n)<=(v))&&((v)<=(m))) //?(true):(false))
#define InRangeValue(n,m,v)      (max((n),min((m),(v))))
#define ARRAY_MOVE(x,y,w)        ((x)+((y)*(w)))
#define REAL_WIDTH(w,b)          ((((w)*(b)+31)&~31)>>3)

#define TO_PTR(p)                ((DWORD_PTR)(p))
#define FLOAT_DWORD(f)           (*((DWORD*)&(f)))
#define PTR_UINT(p)              ((unsigned int)(DWORD_PTR)(p))
#define PTR_INT(p)               ((int)(DWORD_PTR)(p))
#define FLOAT_INT(f)             (int)((0.5<fabs((f)-(int)(f)))?((int)(f)+1):((int)(f)))
#define FLOATtoINT(f)            (int)((0.5<(fabs((f))-((int)fabs((f)))))?((int)(f)+((0<(f))?(1):(-1))):((int)(f)))
#define MaxFLOATtoINT(f)         (int)((0<(fabs((f))-((int)fabs((f)))))?((int)(f)+((0<(f))?(1):(-1))):((int)(f)))
#define MinFLOATtoINT(f)         (int)(*(int*)&(f))
#define MaxFLOAT(f)              (ceilf((f)))
#define MinFLOAT(f)              (floorf((f)))

#define IsMin(a,b)               (((a)<(b))?(1):(((a)>(b))?(-1):(0)))
#define IsMax(a,b)               (((a)>(b))?(1):(((a)<(b))?(-1):(0)))
#define CmpValue(a,b)            (((a)==(b))?(0):(((a)>(b))?(1):(-1)))
#define Min2(a,b)                (((a)>(b))?(b):(a))
#define Max2(a,b)                (((a)>(b))?(a):(b))
#define Min3(a,b,c)              (((a)<(b))?(((a)<(c))?((a)):((c))):(((b)<(c))?((b)):((c))))
#define Middle3(a,b,c)           (((a)<(b))?(((b)<(c))?((b)):(((a)<(c))?((c)):((a)))):(((a)<(c))?((a)):(((b)<(c))?((c)):((b)))))
#define Max3(a,b,c)              (((a)>(b))?(((a)>(c))?((a)):((c))):(((b)>(c))?((b)):((c))))

//f보다 작은 가장 큰 정수
#define AndBits(t,u)             ((t)&(u))
#define XOrBits(t,u)             ((t)^(u))
#define OrBits(t,u)              ((t)|(u))
#define IsAndBITS(t,u)           ((u)==((t)&(u))) //?(true):(false))
#define IsAndZero(t,u)           (0==((t)&(u))) //?(true):(false))
#define IsAndNonZero(t,u)        (0!=((t)&(u))) //?(true):(false))
#define InsertBITS(t,u)          ((t)|(u))
#define RemoveBITS(t,u)          ((t)^((t)&(u)))
#define LOGARITHMIC(t,u)         ((0==log((double)u))?(-1):(log((double)(t))/log((double)(u))))
//실행 시(run time)에 형 변환을 한다.(컴파일러의 RTTI 옵션이 선택된 상태)
//dynamic_cast는 실행 시간에 항상 안전한 형 변환을 시도한다. 안전하지 않다면,NULL을 리턴한다. 
#define DYNAMICCAST(c,o)         (dynamic_cast<c>(o))
//컴파일 때 형 변환이 결정되므로,베이스 클래스가 다형 클래스(polymorphic class)이면 안된다. 즉,베이스 클래스에 가상 함수가 없어야 한다. 
#define STATICCAST(c,o)          (static_cast<c>(o))
//이것은 서로 관계없는 형 사이의 변환이다
#define REINTERPRETCAST(c,o)     (reinterpret_cast<c>(o))

#define TOKEN(o,a)               o##a
#define W_Char(x)                L ## x
#define W_CharZero               L'\0'
#define CharZero                 '\0'
#define MkString(x)              #x
#define MkChar(x)                #@x
#define IsW_Char(x)              (((x)&0x80)==0x80)
#define MKW_Char(b1,b2)          MAKEWORD((b2),(b1))
#define CountOfArray(array)      (sizeof(array)/sizeof(array[0]))

#define AREASet(l,t,r,b)          (CRect((int)(l),(int)(t),(int)(r),(int)(b)))
#define AREASet_WH(l,t,w,h)       (CRect((int)(l),(int)(t),(int)((l)+(w)),(int)((t)+(h))))
#define AREASet_C(l,t,w,h)        (CRect((int)((l)-(w)/2),(int)((t)-(h)/2),(int)((l)+(w)/2),(int)((t)+(h)/2)))
#define AREASet_Empty             (CRect(0,0,0,0))
#define POINTSet(x,y)             (CPoint((int)(x),(int)(y)))
#define IsSAMEVALUE(a,b)          ((a)==(b))  //?(true):(false))
#define IsDIFFVALUE(a,b)          ((a)!=(b))  //?(true):(false))
#define IsNonZeroOR(a,b)          ((0!=(a))||(0!=(b)))   //?(true):(false))
#define IsNonZeroAND(a,b)         ((0!=(a))&&(0!=(b)))   //?(true):(false)) 
#define IsZeroOR(a,b)             ((0==(a))||(0==(b)))   //?(true):(false))
#define IsZeroAND(a,b)            ((0==(a))&&(0==(b)))   //?(true):(false)) 
#define IsREMAIN(n,d)             (0!=((n)%(d)))         //?(false):(true))
#define IsREMAINSign(n,d)         ((0==((n)%(d)))?(0):((0<((n)%(d))?(1):(-1))))
#define REMAIN(n,d)               ((n)%(d))
#define REMAIN_FLOAT(n,d)         (fmod((n),(d)))
#define DIVIDE(n,d)               ((n)/(d))
#define LINE(n,d)                 ((n)%(d))
#define COL(n,d)                  ((n)/(d))
#define LINECOL(t,l,c)            ((t)*(c)+(l))
#define HLLINECOL(l,c)            (((unsigned int)((unsigned short)((UINT_PTR)(l) & 0xffff)))       \
                                  | (((unsigned int)((unsigned short)((UINT_PTR)(c) & 0xffff))) << 16))
#define InCludeToCount(n,d)       (((n)/(d))+((0==((n)%(d)))?(0):(1)))
#define IncludeToCountF(n,d)      (((n)/(d))+((0==((n)%((int)((0.5<fabs((d)-(int)(d)))?((int)(d)+1):((int)(d))))))?(0.0f):(1.0f)))
#define NotValue(n)               ((int)(!((bool)n)))
#define Data_OFFSET(t,f)          ((long)(INT_PTR)&(((t *)0)->f))
#define Pythagoras(x,y)           (sqrtf((float)((x)*(x)+(y)*(y))))
#define Pythagoras2(x1,y1,x2,y2)  (sqrtf((float)(((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))))
//근의 공식
#define Formula_1(a,b,c)          (((-(b)+sqrtf((float)(b)*(b)-4.0f*(a)*(c))))/(2.0f*(a)))
#define Formula_2(a,b,c)          (((-(b)-sqrtf((float)(b)*(b)-4.0f*(a)*(c))))/(2.0f*(a))) 
//탄성 충돌 
//운동량     m1*v1'+m2*v2'=m1*v1+m2*v2
//           m1*(v1-v1')=m2*(v2'-v2)
//반발 계수  e=(v2'-v1')/(v1-v2) (Root(h2/h1))
//운동에너지 1/2*m1*v1'^2+1/2*m2*v2'^2=1/2*m1*v1^2+1/2*m2*v2^2
//           m1*(v1^2-v1'^2)   =m2*(v2'^2-v2^2)
//           m1*(v1-v1')*(v1-v1')=m2*(v2'-v2)*(v2'-v2)
//m1==m2 v1'=v2,v2'=v1
#define Velocity_1(m1,m2,v1,v2)    ((((m1)-(m2))/((m1)+(m2)))*(v1)+(2.0f*(m2)/((m1)+(m2)))*(v2))
#define Velocity_2(m1,m2,v1,v2)    ((2.0f*(m1)/((m1)+(m2)))*(v1)+(((m2)-(m1))/((m1)+(m2)))*(v2))
//vs1'=((m1-e*m2)*vs1+(1+e)*m2*vs2)/(m1+m2)
#define Velocity_E1(e,m1,m2,v1,v2) ((((m1)-(e)*(m2))*(V1)+(1.0f+(e))*(m2)*(v2))/((m1)+(m2)))
//vs2'=((m2-e*m1)*vs2+(1+e)*m1*vs1)/(m1+m2)
#define Velocity_E2(e,m1,m2,v1,v2) ((((m2)-(e)*(m1))*(V2)+(1.0f+(e))*(m1)*(v1))/((m1)+(m2)))
#define Velocity_1V20(m1,m2,v1)    ((((m1)-(m2))/((m1)+(m2)))*(v1))
#define Velocity_2V20(m1,m2,v1)    ((2.0f*(m1)/((m1)+(m2)))*(v1))
//등가속운동 Constant Acceleration
//           v=v0+a*t
//           d=d0+1/2*(v-v0)*t
//           d=d0+v0*t+1/2*a*t^2
//           v^2= v0^2+2*a*(d-d0)
#define CA_Velocity(v,a,t)        ((v)+(a)*(t))
#define CA_Time(v1,v2,a)          (((v2)-(v2))/(a))
#define CA_Distance_VV(d,v1,v2,t) ((d)+0.5f*((v2)-(v1))*(t))
#define CA_Distance_VA(d,v,a,t)   ((d)+(v)*(t)+0.5f*(a)*(t)*(t))
#define CA_Velocity_End(v,a,d)    (sqrtf(((v)*(v))+2.0f*(a)*(d)))

#define Root(a)                   (sqrtf((float)a))
#define IsEvenNumber(a)           (0==(a%2))  //짝수
#define IsUnEvenNumber(a)         (0!=(a%2))  //홀수
#define Multiply(a)               ((a)*(a))
#define Sign(a)                   ((0>(a))?(-1):(1))

#define PositiveSign_char(c)      (static_cast<unsigned char>(((c)^0xff)+1))
#define PositiveSign_short(s)     (static_cast<unsigned short int>(((s)^0xffff)+1))
#define PositiveSign_int(i)       (static_cast<unsigned short>(((i)^0xffffffff)+1))

#define Loop_Prev(a,d,t)          (((t)+((a)-(d)))%(t))
#define Loop_Next(a,d,t)          (((a)+(d))%(t))

#define PI                        ((float)3.14159265358979323846264338327950288419716939937511f)
//((float)3.141592654f)
#define RADIAN                    (PI/180.f)
#define DEGREE                    (180.f/PI)
#define D3D_PI                    ((float)3.141592654f)
#define D3DToRadian(degree)       ((float)(degree)*(D3D_PI/180.0f))
#define D3DToDegree(radian)       ((float)(radian)*(180.0f/D3D_PI))
#define D3DRadian90               D3DToRadian(90.0f)
#define D3DRadian180              D3DToRadian(180.0f)
#define D3DRadian270              D3DToRadian(270.0f)
#define D3DRadian360              D3DToRadian(360.0f)

#define CosRadian(a)              (cosf((float)(a)))
#define SinRadian(a)              (sinf((float)(a)))
#define TanRadian(a)              (tanf((float)(a)))
#define CosDegree(a)              (cosf((float)D3DToRadian(a)))
#define SinDegree(a)              (sinf((float)D3DToRadian(a)))
#define TanDegree(a)              (tanf((float)D3DToRadian(a)))
#define ArcCos(a)                 (acosf((float)(a)))
#define ArcSin(a)                 (asinf((float)(a)))
#define ArcTan(x,y)               (atan2((float)(y),(float)(x)))
#define ArcTan2(x1,y1,x2,y2)      (atan2((float)((y2)-(y1)),(float)((x2)-(x1)))

#define ArcDegreeQ1(a)            ((a)+270)  //Quarter_1=0,// + : - //cos(+),sin(-),tan(-)
#define ArcDegreeQ2(a)            ((a)+180)  //Quarter_2=1,// - : - //cos(-),sin(-),tan(+)
#define ArcDegreeQ3(a)            ((a)+90)   //Quarter_3=2,// - : + //cos(-),sin(+),tan(-)
#define ArcDegreeQ4(a)            (a)      //Quarter_4=3,// + : + //cos(+),sin(+),tan(+)
	
#define FabsCosRadian(a)          (fabs(cosf((float)(a))))
#define FabsSinRadian(a)          (fabs(sinf((float)(a))))
#define FabsTanRadian(a)          (fabs(tanf((float)(a))))
#define FabsCosDegree(a)          (fabs(cosf((float)D3DToRadian(a))))
#define FabsSinDegree(a)          (fabs(sinf((float)D3DToRadian(a))))
#define FabsTanDegree(a)          (fabs(tanf((float)D3DToRadian(a))))
#define FabsArcCos(a)             (fabs(acosf((float)(a))))
#define FabsArcSin(a)             (fabs(asinf((float)(a))))
#define FabsArcTan(x,y)           (fabs(atan2((float)(y),(float)(x))))

#define D_Proportion(a,b,c)       (((b)*(c))/(a))
//a(시작점),b(끝점),f(비율) a+f*(b-a) || a*(1-f)+b*f
#define Value_Lerp(a,b,f)         ((float)(a)+(float)(f)*((float)(b)-(float)(a)))
#define Value_Lerp_Normal(a,b,f)  FLOATtoINT((float)(a)+(float)(f)*((float)(b)-(float)(a)))
#define Value_Lerp_Hyper(a,b,f)   ((__int64)(a)+(__int64)((__int64)((f)*1000000)*(((__int64)(b)-(__int64)(a))/1000000))+(__int64)((f)*(((__int64)(b)-(__int64)(a))%1000000)))
#define Value_Lerp_Ing(a,b,p,n,e) ((float)(a)+(float)(((n)-(p))/((e)-(p)))*((float)(b)-(float)(a)))
#define Rate_Lerp(a,b,c)          (((float)(c)-(float)(a))/((float)(b)-(float)(a)))
#define Rate_Lerp_Normal(a,b,c)   (((int)(c)-(int)(a))/((int)(b)-(int)(a)))
#define Rate_Lerp_Hyper(a,b,c)    (((__int64)(c)-(__int64)(a))/((__int64)(b)-(__int64)(a)))
#define Value_Modulate(a,b)       ((a)*(b))
#define Value_Negative(a)         ((1.0f)-(a))
#define Value_Scale(a,s)          ((a)*(s))
#define Value_Add(a,b)            ((a)+(b))
#define Value_Subtract(a,b)       ((b)-(a))
//r=현재,s=실제,a=(실제 값),b=(현재 비율값) 
#define Coord_Proportion1(a,r,s)  (((((float)(r))/((float)(s)))*((float)(a)))/((float)(r)))
#define Coord_Proportion2(b,r,s)  (((((float)(s))/((float)(r)))*((float)(b)))*((float)(r)))

//회색
#define Value_GreyScale(r,g,b)    ((0.2125f)*(r)+(0.7154f)*(g)+(0.0721f)*(b))
// c= r||g||b,g=greyscale
// s 가 0 보다 크게 1 보다 작은 경우,채도는 작아진다. s 가 1 보다 큰 경우,채도는 커진다.
#define Value_AdjustSaturation(c,s,g) ((g)+(s)*(c-g)) 
// s 가 0 보다 크게 1 보다 작은 경우,콘트라스트는 작아진다. s 가 1 보다 큰 경우,콘트라스트는 커진다.
#define AdjustContrast(c,s)       ((0.5f)+(s)*(c-0.5f)) 

#define USHORT_UINT(a,b)          (((unsigned int)((unsigned short)((UINT_PTR)(a)&0xffff)))       \
								  | (((unsigned int)((unsigned short)((UINT_PTR)(b)&0xffff)))<<16))
#define SHORT_INT(a,b)            (((int)((short)((INT_PTR)(a)&0x7fff)))       \
 								  | (((int)((short)((INT_PTR)(b)&0x7fff)))<<16))

#define UCHAR_UINT(a,b,c,d)       (((unsigned int)((unsigned char)((UINT_PTR)(a)&0xff)))         \
								  | (((unsigned int)((unsigned char)((UINT_PTR)(b)&0xff)))<<8)  \
								  | (((unsigned int)((unsigned char)((UINT_PTR)(c)&0xff)))<<16) \
								  | (((unsigned int)((unsigned char)((UINT_PTR)(d)&0xff)))<<24))
#define CHAR_INT(a,b,c,d)         (((int)((char)((INT_PTR)(a)&0x7f)))         \
								  | (((int)((char)((INT_PTR)(b)&0x7f)))<<8)  \
								  | (((int)((char)((INT_PTR)(c)&0x7f)))<<16) \
								  | (((int)((char)((INT_PTR)(d)&0x7f)))<<24))

#define USHORT_UINT1(i,s)         (((unsigned int)((UINT_PTR)(i)&0xffff0000))|(((unsigned int)((unsigned short)((UINT_PTR)(s)&0xffff)))))
#define USHORT_UINT2(i,s)         (((unsigned int)((UINT_PTR)(i)&0x0000ffff))|(((unsigned int)((unsigned short)((UINT_PTR)(s)&0xffff)))<<16))
#define SHORT_INT1(i,s)           (((int)((INT_PTR)(i)&0xffff0000))|(((int)((short)((INT_PTR)(s)&0x7fff)))))
#define SHORT_INT2(i,s)           (((int)((INT_PTR)(i)&0x0000ffff))|(((int)((short)((INT_PTR)(s)&0x7fff)))<<16))

#define UCHAR_UINT1(i,c)          (((unsigned int)((UINT_PTR)(i)&0xffffff00))|(((unsigned int)((unsigned char)((UINT_PTR)(c)&0xff)))))
#define UCHAR_UINT2(i,c)          (((unsigned int)((UINT_PTR)(i)&0xffff00ff))|(((unsigned int)((unsigned char)((UINT_PTR)(c)&0xff)))<<8))
#define UCHAR_UINT3(i,c)          (((unsigned int)((UINT_PTR)(i)&0xff00ffff))|(((unsigned int)((unsigned char)((UINT_PTR)(c)&0xff)))<<16))
#define UCHAR_UINT4(i,c)          (((unsigned int)((UINT_PTR)(i)&0x00ffffff))|(((unsigned int)((unsigned char)((UINT_PTR)(c)&0xff)))<<24))
#define CHAR_INT1(i,c)            (((int)((INT_PTR)(i)&0xffffff00))|(((int)((char)((INT_PTR)(c)&0x7f)))))
#define CHAR_INT2(i,c)            (((int)((INT_PTR)(i)&0xffff00ff))|(((int)((char)((INT_PTR)(c)&0x7f)))<<8))
#define CHAR_INT3(i,c)            (((int)((INT_PTR)(i)&0xff00ffff))|(((int)((char)((INT_PTR)(c)&0x7f)))<<16))
#define CHAR_INT4(i,c)            (((int)((INT_PTR)(i)&0x00ffffff))|(((int)((char)((INT_PTR)(c)&0x7f)))<<24))

#define UINT_USHORT1(l)           ((unsigned short)((UINT_PTR)(l)&0xffff))
#define UINT_USHORT2(l)           ((unsigned short)(((UINT_PTR)(l)>>16)&0xffff))
#define UINT_UCHAR1(l)            ((unsigned char)((UINT_PTR)(l)&0xff))
#define UINT_UCHAR2(l)            ((unsigned char)(((UINT_PTR)(l)>>8)&0xff))
#define UINT_UCHAR3(l)            ((unsigned char)(((UINT_PTR)(l)>>16)&0xff))
#define UINT_UCHAR4(l)            ((unsigned char)(((UINT_PTR)(l)>>24)&0xff))
#define INT_SHORT1(l)             ((short)((INT_PTR)(l)&0x7fff))
#define INT_SHORT2(l)             ((short)(((INT_PTR)(l)>>16)&0x7fff))
#define INT_CHAR1(l)              ((char)((INT_PTR)(l)&0x7f))
#define INT_CHAR2(l)              ((char)(((INT_PTR)(l)>>8)&0x7f))
#define INT_CHAR3(l)              ((char)(((INT_PTR)(l)>>16)&0x7f))
#define INT_CHAR4(l)              ((char)(((INT_PTR)(l)>>24)&0x7f))

#define UCHAR_BITS4(a,b)          ((unsigned char)((a)&0xf)|(unsigned char)(((b)&0xf)<<4))
#define UCHAR_BITS2(a,b,c,d)      ((unsigned char)((a)&0x3)|(unsigned char)(((b)&0x3)<<2)|(unsigned char)(((c)&0x3)<<4)|(unsigned char)(((d)&0x3)<<6))

#define BITS4_UCHAR1(c)           ((unsigned char)(c)&0xf)
#define BITS4_UCHAR2(c)           ((unsigned char)(c>>4)&0xf)
#define BITS2_UCHAR1(c)           ((unsigned char)(c)&0x3)
#define BITS2_UCHAR2(c)           ((unsigned char)(c>>2)&0x3)
#define BITS2_UCHAR3(c)           ((unsigned char)(c>>4)&0x3)
#define BITS2_UCHAR4(c)           ((unsigned char)(c>>6)&0x3)

#define HALF_MASK555   0x7bde  //0 11110 11110 11110
#define HALF_MASK565   0xf7de  //11110 111110 1 1110
#define R_B_MASK555    0x7c1f  //0 11111 00000 11111
#define G_MASK555      0x03e0  //0 00000 11111 00000
#define R_B_MASK565    0xf81f  //11111 000000 11111
#define G_MASK565      0x07e0  //00000 111111 00000
#define MASK_ATTRIBUTE 0x7fff  //0111 1111 1111 1111

#define RGB_WHITE      RGB(255,255,255)
#define RGB_BLACK      RGB(  0,  0,  0)
#define RGB_GRAY       RGB(128,128,128)
#define RGB_RED        RGB(255,  0,  0)
#define RGB_GREEN      RGB(  0,255,  0)
#define RGB_BLUE       RGB(  0,  0,255)
#define RGB_YELLOW     RGB(255,255,  0)
#define RGB_CYAN       RGB(  0,255,255)
#define RGB_MAGENTA    RGB(255,  0,255)
#define RGB_SCARLETRED RGB(128,  0,  0)
#define RGB_DARKGREEN  RGB(  0,128,  0)
#define RGB_NAVYBLUE   RGB(  0,  0,128)

//Cyan은 백색광선으로부터 R이 흡수=G와 B가 반사되었을 때 보이는 색상, G와 B가 반반씩 혼합된 색상
//Magenta는 백색광선으로부터 G가 흡수=R와 B가 반사되었을 때 보이는 색상, R와 B가 반반씩 혼합된 색상
//Yellow는 백색광선으로부터 B가 흡수=R와 G가 반사되었을 때 보이는 색상, R와 G가 반반씩 혼합된 색상

#define RValue(rgb)      ((unsigned char)(rgb))
#define GValue(rgb)      ((unsigned char)(((unsigned short int)(rgb))>>8))
#define BValue(rgb)      ((unsigned char)((rgb)>>16))

#define RXValue(xrgb)    ((unsigned char)((xrgb)>>16))
#define GXValue(xrgb)    ((unsigned char)(((unsigned short int)(xrgb))>>8))
#define BXValue(xrgb)    ((unsigned char)(xrgb))
#define AXValue(xrgb)    ((unsigned char)((xrgb)>>24))

#define RGBToXRGB(rgb)   ((D3DCOLOR)(((0xff)<<24)|(((((BYTE)(rgb)))&0xff)<<16)|(((((BYTE)(((WORD)(rgb))>>8)))&0xff)<<8)|((((BYTE)((rgb)>>16)))&0xff)))
#define XRGBToRGB(xrgb)  ((COLORREF)(((BYTE)((BYTE)((xrgb)>>16))|((WORD)((BYTE)((BYTE)(((WORD)(xrgb))>>8)))<<8))|(((DWORD)(BYTE)((BYTE)(xrgb)))<<16)))

#define rgb555_USHORT(r,g,b)  (unsigned short int)((((r)&0xF8)<<7)+(((g)&0xF8)<<2)+((b)>>3))
#define rgb565_USHORT(r,g,b)  (unsigned short int)((((r)&0xF8)<<8)+(((g)&0xFC)<<3)+((b)>>3))

// RGB 5:6:5 or 5:5:5 --> 5:6:5 or 5:5:5
#define RGB555_UCHAR(r,g,b)   (unsigned char)(((r)<<10)|((g)<<5)|(b)) // 5:5:5 
#define RGB565_UCHAR(r,g,b)   (unsigned char)(((r)<<11)|((g)<<5)|(b)) // 5:6:5

// RGB 8:8:8 --> RGB 5:6:5 or 5:5:5
#define RGB555_USHORT(r,g,b)  (unsigned short int)(((r)>>3)<<10|((g)>>3)<<5|((b)>>3)|0x8000)
#define RGB565_USHORT(r,g,b)  (unsigned short int)(((r)>>3)<<11|((g)>>2)<<5|((b)>>3))
//#define RGB555(r,g,b) ( ((r>>3)<<10) | ((g>>3)<<5) | (b>>3) ) // 5:5:5 
//#define RGB565(r,g,b) ( ((r>>3)<<11) | ((g>>2)<<5) | (b>>3) ) // 5:6:5

// get 16bit RGB                            // 0111 1111 1111 1111
#define R555_UCHAR(s)  (unsigned char)(((((s)&0x7fff)&0x7c00)>>10)<<3)//red   0111110000000000
#define G555_UCHAR(s)  (unsigned char)(((((s)&0x7fff)&0x03e0)>>5)<<3) //green 0000001111100000
#define B555_UCHAR(s)  (unsigned char)(((((s)&0x7fff)&0x001f))<<3)    //blue  0000000000011111
//#define R555(p)	( (BYTE) ( (p>>11)   ) )
//#define G555_BYTE(p)	( (BYTE) ( (p>>5)&003f ) )
//#define B555_BYTE(p)	( (BYTE) ( (p)&31    ) ) 

#define R565_UCHAR(s)  (unsigned char)((((s)&0xf800)>>11)<<3)//red   1111100000000000
#define G565_UCHAR(s)  (unsigned char)((((s)&0x07e0)>>5)<<2) //green 0000011111100000 
#define B565_UCHAR(s)  (unsigned char)((((s)&0x001f))<<3)    //blue  0000000000011111
//#define R565(p)		( (BYTE) ( (p>>11)   <<3) )
//#define G565(p)		( (BYTE) ( (p>>5)&003f <<2) )
//#define B565(p)		( (BYTE) ( (p)&31    <<3) )



#endif