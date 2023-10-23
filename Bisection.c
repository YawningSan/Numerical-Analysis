#include <stdio.h>
#include <math.h>
#define Fractional_Word_Length 11


int floating_float();
float fx_float(float x);

int fixed_short();
short power2_short(short x);
short power3_short(short x);
short fx_short(short x);

void Print_short_to_float(short n);

int main() {

	printf("f(x) = x^3 + 4x^2 -10\n\n");

	floating_float();		//floating point롤 문제 풀기 (자료형 float사용)

	fixed_short();			//fixed point로 문제 풀기 (자료형 short 사용)

	return 0;
}







int floating_float() {

	float x1 = 1;
	float x2 = 2;
	float x3;

	for (int i = 0; i < 30; i++) {

		/* x1과 x2가 같다면 종료 */
		if (x1 == x2) { return 1; }

		x3 = (x1 + x2) / 2;
		
		/* f(x3)와 f(x1)의 부호가 다르면 x1와 x3사이에 근이 있는것이므로 x2에 x3를 할당 */
		if (fx_float(x1) * fx_float(x3) < 0 )  x2 = x3;

		/*부호가 같다면 x3와 x2 사이에 근이 있는것이므로 x1에 x3를 할당*/
		else x1 = x3;
		
		
	}

	printf("floating point : f(x)의 [1,2] 사이의 근은 %.30f 입니다.\n\n", x3);

	return 1;
}

float fx_float(float x) {

	return ((x * x * x) + (4 * x * x) - 10);	//x^3 + 4x^2 - 10
}










int fixed_short() {

	// 정수부를 5bit, 소수부를 11bit 사용할것입니다. 이때 sign bit를 쓰지 않고 2'complement 표현방식을 그대로 채용합니다.
	short x1 = 1 << Fractional_Word_Length;
	short x2 = 2 << Fractional_Word_Length;
	short x3;

	

	
	for (int i = 0; i < 30; i++) {

		/* x1과 x2가 같다면 종료 */
		if (x1 == x2) {  return 1; }

		
		x3 = (x1 + x2) >> 1;			// x3 = (x1+x2)/2
		
		printf("%d. %d, %d, %d, %d, 제%d, 세%d\n", x1, x2, x3, fx_short(x1), fx_short(x3), power2_short(x3), power3_short(x3));
		if (x3 == x1 || x2 == x3) { printf("!!break!!\n"); break; }

		/* f(x3)와 f(x1)의 부호가 다르면 x1와 x3사이에 근이 있는것이므로 x2에 x3를 할당 */
		if ( (fx_short(x1) ^ fx_short(x3)) < 0) x2 = x3;

		/*부호가 같다면 x3와 x2 사이에 근이 있는것이므로 x1에 x3를 할당*/
		else x1 = x3;
		
	}

	printf("fixed point : f(x)의 [1,2] 사이의 근은 %.d 입니다.\n", x3);
	
	Print_short_to_float(x3);
	

	return 1;
}

short power2_short(short x) {

	/*곱셈시 자료형의 두배의 공간이 필요하므로 잠시 4byte long 자료형을 사용합니다.*/
	long tmp= x * x;

	/*long에 들어간 값을 shift해서 short형 format에 맞춰줍니다.*/
	return tmp >> Fractional_Word_Length;
}

short power3_short(short x) {

	long tmp = x * x;

	/*한번에 세제곱을하면 6byte가 필요하므로 1단계 1단계씩 곱해줍니다.*/
	tmp = (tmp >> Fractional_Word_Length) * x;

	
	return tmp >> Fractional_Word_Length;
}


short fx_short(short x) {

	/* overflow 방지하기 위해서 순서 변경했습니다. */
	return (power3_short(x) - (10 << Fractional_Word_Length)) + (4 * power2_short(x));
}











/*custom한 short 타입 변수를 float처럼 출력하는 함수 */
void Print_short_to_float(short n) {

	

	int f = n & 0b11111111111;			//f는 소수부(11bit만 빼오기)
	int check = 0b10000000000;			//소수부 확인용 변수

	int integer = n >> 11;				//integer는 정수부(2'complemnet 방식)
	int sign = n >> 15;					//sign bit 확인용 변수

	int i;
	double fraction = 0;

	/* 2진수 소수 1번째 자리부터 11번째 까지 확인 */
	for (i = 1; i < 12; i++) {

		/* 만약 소수 i번째 자리수가 존재한다면 */
		if (f & check) {

			/* 2^(-i)을 fraction에 누적 */
			fraction += 1 / pow(2, i);
		}

		/* 다음 자릿수를 체크하기 위해 check를 오른쪽으로 shift */
		check = check >> 1;
	}


	if (sign) {
		/* 만약 MSB가 1이면 음수이므로 2'complement를 바꿔주기 */
		integer = integer - 32;			
	}

	printf("이를 소수로 나타내면 %.30lf", (double)integer + fraction);	//정수부+소수부


}