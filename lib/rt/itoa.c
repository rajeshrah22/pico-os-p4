#include <stddef.h>

#include <rt.h>
char* itoa(char* buffer, int number) {
	size_t i = 0, s = 0;
	char c;

	if(!number) {
		buffer[0] = '0';
		buffer[1] = '\0';
		return buffer;
	}

	while(number) {
		c = number & 0xf;
		buffer[i++] = c + ((c > 9) ? 'a' : '0');
		number >>= 4;
	}
	buffer[i--] = '\0';

	while(s < i) {
		c = buffer[s];
		buffer[s++] = buffer[i];
		buffer[i--] = c;
	}

	return buffer;
}

