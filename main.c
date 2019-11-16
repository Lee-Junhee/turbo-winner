#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>

int main() {
	DIR *cwd = opendir(".");

	struct dirent *entry;

	printf("**********\n");
	unsigned int total = 0;
	while (1) {
		entry = readdir(cwd);
		if (!entry) {
			break;
		}
		char filename[256];
	       	strcpy(filename, entry->d_name);
		struct stat fileinfo;
		stat(filename, &fileinfo);
		int size = fileinfo.st_size;
		int mode = fileinfo.st_mode;
		char perms[11] = "----------";
		if (!(entry->d_type - 4)) {
			strncpy(perms, "d", 1);
		}else {
			total += size;
		}
		int i;
		char all[11] = "-rwxrwxrwx";
		int bit = 1;
		for(i = 9; i > 0; i--) {
			if (bit & mode) {
				strncpy(perms + i, all + i, 1);
			}
			bit *= 2;
		}

		printf("%s\t%d\t%s\n", perms, size, filename);
	}
	printf("\nTotal Directory Size: %d bytes\n", total);
	printf("**********\n");

	return 0;
}
