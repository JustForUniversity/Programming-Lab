```c++
//11r 11b 11g 10r 10b 10g 01r 01b

/* x| 0 | 1 |
 y  ---------
 0  |rgb|rgb|
 1  |rgb|rgb|*/

#include <iostream>
#include "libbmp.h"
#include <string>

using namespace std;


int conventer_to_int(string temp){
	int result = 0, mult = 128;

	for (int i = 0; i < 8; i++) {
		result += (int)temp[i] * mult;
		mult /= 2;
	}

	return result;
}


bool conventer_to_char(string* str) {
	char temp;

	if (str->size() == 8) {
		if ((char)conventer_to_int(*str) == '\0') return false;
		temp = (char)conventer_to_int(*str);
		*str = temp;
		return true;
	}
	
	return false;
}


int main()
{
	BmpImg image;
	image.read("pic8.bmp");
	int img_height = image.get_height();
	int img_width = image.get_width();

	string answer = "";
	string temp = "";

	for (int i = img_width-1; i >= 0; i--) {

		for (int j = img_height-1; j >= 0; j--) {

			temp += ((int)image.red_at(i, j)) % 2;
			if (conventer_to_char(&temp)) {
				answer += temp;
				temp = "";
			}

			temp += ((int)image.blue_at(i, j)) % 2;
			if (conventer_to_char(&temp)) {
				answer += temp;
				temp = "";
			}

			temp += ((int)image.green_at(i, j)) % 2;
			if (conventer_to_char(&temp)) {
				answer += temp;
				temp = "";
			}

		}
	}
	cout << answer << endl;
	system("pause");
}

```

