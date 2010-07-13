int mypow(int n1, int n2){
	int p = 2;
	int num = n1;
	if (n2 == 0){
		return 1;
	}
	if (n2 == 1){
		return n1;
	}
	while (p <= n2){
		num = num * n1;
		p+=1;
	}
	return num;
	
}


int stringtoint(char s[]){
	int len = strlen(s);
	int digit, num, sign;
	num = 0;
	sign = 1;
	
	int pos = 0;
	int curr_digit = 0;
	while (pos < len){
			
		if (s[len-pos-1] != '-'){
			/*
			printf("s: %c\n", s[len-pos-1]);
			printf("s int: %i\n", (int)(s[len-pos-1]));
			printf("pos: %i\n", pos);
			printf("len: %i\n", len);
			*/
			digit = (int)(s[len - pos -1]) - 48;//reverse order
			num += mypow(10, curr_digit) * digit;
			/*
			printf("DIGIT: %i\n", digit);
			printf("\n");
			*/
			curr_digit += 1;
			pos += 1;
		}
		else {
			sign = -1;
			pos += 1;
		}
	}
	return num * sign;
}

