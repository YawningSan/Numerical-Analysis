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

	floating_float();		//floating point�� ���� Ǯ�� (�ڷ��� float���)

	fixed_short();			//fixed point�� ���� Ǯ�� (�ڷ��� short ���)

	return 0;
}







int floating_float() {

	float x1 = 1;
	float x2 = 2;
	float x3;

	for (int i = 0; i < 30; i++) {

		/* x1�� x2�� ���ٸ� ���� */
		if (x1 == x2) { return 1; }

		x3 = (x1 + x2) / 2;
		
		/* f(x3)�� f(x1)�� ��ȣ�� �ٸ��� x1�� x3���̿� ���� �ִ°��̹Ƿ� x2�� x3�� �Ҵ� */
		if (fx_float(x1) * fx_float(x3) < 0 )  x2 = x3;

		/*��ȣ�� ���ٸ� x3�� x2 ���̿� ���� �ִ°��̹Ƿ� x1�� x3�� �Ҵ�*/
		else x1 = x3;
		
		
	}

	printf("floating point : f(x)�� [1,2] ������ ���� %.30f �Դϴ�.\n\n", x3);

	return 1;
}

float fx_float(float x) {

	return ((x * x * x) + (4 * x * x) - 10);	//x^3 + 4x^2 - 10
}










int fixed_short() {

	// �����θ� 5bit, �Ҽ��θ� 11bit ����Ұ��Դϴ�. �̶� sign bit�� ���� �ʰ� 2'complement ǥ������� �״�� ä���մϴ�.
	short x1 = 1 << Fractional_Word_Length;
	short x2 = 2 << Fractional_Word_Length;
	short x3;

	

	
	for (int i = 0; i < 30; i++) {

		/* x1�� x2�� ���ٸ� ���� */
		if (x1 == x2) {  return 1; }

		
		x3 = (x1 + x2) >> 1;			// x3 = (x1+x2)/2
		
		printf("%d. %d, %d, %d, %d, ��%d, ��%d\n", x1, x2, x3, fx_short(x1), fx_short(x3), power2_short(x3), power3_short(x3));
		if (x3 == x1 || x2 == x3) { printf("!!break!!\n"); break; }

		/* f(x3)�� f(x1)�� ��ȣ�� �ٸ��� x1�� x3���̿� ���� �ִ°��̹Ƿ� x2�� x3�� �Ҵ� */
		if ( (fx_short(x1) ^ fx_short(x3)) < 0) x2 = x3;

		/*��ȣ�� ���ٸ� x3�� x2 ���̿� ���� �ִ°��̹Ƿ� x1�� x3�� �Ҵ�*/
		else x1 = x3;
		
	}

	printf("fixed point : f(x)�� [1,2] ������ ���� %.d �Դϴ�.\n", x3);
	
	Print_short_to_float(x3);
	

	return 1;
}

short power2_short(short x) {

	/*������ �ڷ����� �ι��� ������ �ʿ��ϹǷ� ��� 4byte long �ڷ����� ����մϴ�.*/
	long tmp= x * x;

	/*long�� �� ���� shift�ؼ� short�� format�� �����ݴϴ�.*/
	return tmp >> Fractional_Word_Length;
}

short power3_short(short x) {

	long tmp = x * x;

	/*�ѹ��� ���������ϸ� 6byte�� �ʿ��ϹǷ� 1�ܰ� 1�ܰ辿 �����ݴϴ�.*/
	tmp = (tmp >> Fractional_Word_Length) * x;

	
	return tmp >> Fractional_Word_Length;
}


short fx_short(short x) {

	/* overflow �����ϱ� ���ؼ� ���� �����߽��ϴ�. */
	return (power3_short(x) - (10 << Fractional_Word_Length)) + (4 * power2_short(x));
}











/*custom�� short Ÿ�� ������ floató�� ����ϴ� �Լ� */
void Print_short_to_float(short n) {

	

	int f = n & 0b11111111111;			//f�� �Ҽ���(11bit�� ������)
	int check = 0b10000000000;			//�Ҽ��� Ȯ�ο� ����

	int integer = n >> 11;				//integer�� ������(2'complemnet ���)
	int sign = n >> 15;					//sign bit Ȯ�ο� ����

	int i;
	double fraction = 0;

	/* 2���� �Ҽ� 1��° �ڸ����� 11��° ���� Ȯ�� */
	for (i = 1; i < 12; i++) {

		/* ���� �Ҽ� i��° �ڸ����� �����Ѵٸ� */
		if (f & check) {

			/* 2^(-i)�� fraction�� ���� */
			fraction += 1 / pow(2, i);
		}

		/* ���� �ڸ����� üũ�ϱ� ���� check�� ���������� shift */
		check = check >> 1;
	}


	if (sign) {
		/* ���� MSB�� 1�̸� �����̹Ƿ� 2'complement�� �ٲ��ֱ� */
		integer = integer - 32;			
	}

	printf("�̸� �Ҽ��� ��Ÿ���� %.30lf", (double)integer + fraction);	//������+�Ҽ���


}