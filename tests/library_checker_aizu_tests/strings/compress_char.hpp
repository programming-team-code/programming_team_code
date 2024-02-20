#pragma once
char compress_char(char c) {
	bool is_let = ('a' <= c && c <= 'z');
	bool is_digit = ('0' <= c && c <= '9');
	assert(is_let || is_digit);
	if (is_digit) return c;
	return c - 'a' + '9' + 1;
}
