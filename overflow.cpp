#include <stdio.h>

int main()
	{
	FILE* hex = fopen("hex", "wb");
	
	char get_to_hash_str[241] = {};
	int taran_len = sizeof(get_to_hash_str) / sizeof(get_to_hash_str[0]);
	int write_ret = 0;
	write_ret  = fwrite(get_to_hash_str, sizeof(get_to_hash_str[0]), taran_len, hex);
	
	char greeting[62] = "Good morning, sir Matvey!\n";
	int greeting_len = sizeof(greeting) / sizeof(greeting[0]);
	write_ret  += fwrite(greeting, sizeof(greeting[0]), greeting_len, hex);
	
	// hash for "meow" password
	unsigned char hack_hash[] = {0x48, 0x31, 0x50, 0x00, 0x53, 0x77, 0xa6, 0x7b};
	int hack_hash_len = sizeof(hack_hash) / sizeof(hack_hash[0]);
	write_ret += fwrite(hack_hash, sizeof(hack_hash[0]), hack_hash_len, hex);	
	
	putc('\n', hex);
	write_ret++;
	
	// is used to end first read session
	char filler[2248] = {};
	write_ret += fwrite(filler, sizeof(filler[0]), 2248, hex);
	
	write_ret += fwrite("meow", sizeof(char), 5, hex);	
	fclose(hex);
	
	printf("Overloading string for Kriss programm has been generated. Total symbols number: %d\n", write_ret);
	
	return 0;
	}
