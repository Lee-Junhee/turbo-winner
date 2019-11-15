#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>

int main() {
	DIR *cwd = opendir(".");

	struct dirent *entry;

	printf("----------\n");
	while (1) {
		entry = readdir(cwd);
		if (!entry) {
			break;
		}
		char filename[256] = entry->d_name;
		fd = open(filename);
		struct stat fileinfo;
		stat(fd, &fileinfo);
		int size = fileinfo.st_size;
		int mode = fileinfo.st_mode;
		char perms[16] = "----------";

		printf("%s\t%d\t%s\n", perms, size, filename);
	}
	printf("----------\n");

	return 0;
}
