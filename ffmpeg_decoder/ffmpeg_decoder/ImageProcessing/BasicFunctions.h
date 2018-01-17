/*	C�y���v���B�z�禡�w
	Develop by Jimmy HU <s103360021@gmail.com>
	This program is licensed under GNU General Public License v3.
	BasicFunctions.h�Ω�ŧi��¦�Ƶ{��
 */
#pragma once
#include "DIPDefine\\DIPDefine.h"										//	include "ImageProcessing\\DIPDefine.h" header file, �ޤJ���Y��"ImageProcessing\\DIPDefine.h"
#include <math.h>														//	�ޤJ���Y��math.h
#include <stdbool.h>													//	�ޤJ���Y��stdbool.h
#include <stdio.h>														//	�ޤJ���Y��stdio.h
#include <string.h>														//	�ޤJ���Y��string.h
#include "..\\unistd.h"													//	�ޤJ���Y��unistd.h


/*	BmpFillingByteCalc(BMP���ɸ�ư϶�ɦ줸�p��)�Ƶ{��
 */
unsigned char BmpFillingByteCalc(const unsigned int);					//	�ŧiBmpFillingByteCalc(�p���R�줸�դj�p)�Ƶ{��
bool FileExistCheck(char *);											//	�ŧiFileExistCheck(�ɮצs�b�ˬd)�Ƶ{��
bool FileReadPermissionCheck(const char *);								//	�ŧiFileReadPermissionCheck(�ɮ�Ū���v���ˬd)�Ƶ{��
bool FileWritePermissionCheck(const char *);							//	�ŧiFileWritePermissionCheck(�ɮ׼g�J�v���ˬd)�Ƶ{��
bool FileWrite(const char *,const char *,const char *);					//	�ŧiFileWrite(�ɮ׼g�J)�Ƶ{���A�����r�ɮ׼g�J
/*	UCharBubbleSort�Ƶ{���Ω�Ƨ�unsigned char�ƭȰ}�C
	�Ƶ{����J��(���ƧǤ�unsigned char�ƭȫ���(�ӫ��Чt�����r��),���ƧǼƭȭӼ�,�ƧǤ覡)
	�b���ƧǤ覡��J0���Ѥp�ܤj�ƧǡF��J1���Ѥj�ܤp�Ƨ�
	�Ƶ{����X���Ƨǧ�����unsigned char�ƭȫ���
 */
unsigned char *UCharBubbleSort(const unsigned char *,const unsigned long long int,const bool);
int Compare(const void *,const void *);									//	�ŧiCompare�Ƶ{��(��qsort�ƧǨϥ�)
/**	CountCharPointStr�Ƶ{��
	�ӰƵ{���Ω�p��r����Ъ��סF
	�Ĥ@���ѼƬ����p����פ��r��F
	�ĤG���ѼƬ��O�_��ܭp��Ӹ`��bool�ܼơA�Y��JTure�h��ܭp��Ӹ`�A�Ϥ��h�L
	�p�GCountCharPointStr("ABC", False)�A�i�o���׬�3
	�p�GCountCharPointStr("123456789a", True)�A�i���
	��1�Ӧr�����G1
	��2�Ӧr�����G2
	��3�Ӧr�����G3
	��4�Ӧr�����G4
	��5�Ӧr�����G5
	��6�Ӧr�����G6
	��7�Ӧr�����G7
	��8�Ӧr�����G8
	��9�Ӧr�����G9
	��10�Ӧr�����Ga	
	�ño���׬�10
**/
unsigned long long int CountCharPointStr(const char *, const bool);
void Show_char_point_str(const char *);									//	�ŧiShow_char_point_str(��ܦr������)�Ƶ{��
/*	ShowUCharPointStr�Ƶ{���Ω���ܵL���r�����Ф��e
	�Ƶ{����J��(����ܤ��e���L���r������,�L���r�����Ъ���)
	�Ƶ{����X��void
 */
void ShowUCharPointStr(const unsigned char *,unsigned long long int);	//	�ŧiShowUCharPointStr(��ܵL���r������)�Ƶ{��
/*	ShowLongDouble�Ƶ{���Ω����long double(���B�I��)�ƭ�
	��long double(���B�I��)�i�O����1.7��10^(-308)~��1.7��10^308�d�򤺪��ƭ�
	�ѩ�ShowLongDouble�Ƶ{���B�z�P�B��W�ƭȼe�׬�64�줸
	�]���i�B�z��InputNumber�̤j�W����2^64-1
	�Ƶ{����J������ܤ�long double���A�ƭ�
	�Ƶ{����X��void
 */
void ShowLongDouble(const long double InputNumber);						//	�ŧiShowLongDouble�Ƶ{��
/*	InitialIMGArrayTest�Ƶ{���Ω����InitialIMGArray�Ƶ{��
	�����հƵ{������J�B��X�Ҭ�void�A�Ҧ��ѼƬҳ]�p����հƵ{�����A
	�H�[��ϥΰƵ{���һݫŧi�P�y�k
	�Ƶ{����J��void
	�Ƶ{����X��void
 */