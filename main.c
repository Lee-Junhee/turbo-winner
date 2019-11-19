#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char *argv[]) {
	DIR *cwd;
	char path[256];
	char buff[256];
	if (argc == 1) {
		printf("Enter Target Directory: ");
		fgets(buff, 256, stdin);
		printf("\n");
		int c;
		for(c = 0; c < 256; c++) {
			if (buff[c] == *"\0") {
				break;
			}
		}
		strncpy(path, buff, c - 1);
	}else {
		strcpy(path, argv[1]);
	}
	cwd = opendir(path);
	if errno {
		printf("%s\n", strerror(errno));
		return errno;
	}

	struct dirent *entry;

	printf("**********\n");
	unsigned int total = 0;
	char filename[256];
	char full[512];
	struct stat fileinfo;
	int size, mode, i, bit;
	char perms[11];
	char none[11] = "----------";
	char all[11] = "-rwxrwxrwx";
	while (1) {
		entry = readdir(cwd);
		if (entry == NULL) {
			break;
		}
	       	strcpy(filename, entry->d_name);
		strcpy(full, path);
		strcat(full, "/");
		strcat(full, filename);
		stat(full, &fileinfo);
		size = fileinfo.st_size;
		mode = fileinfo.st_mode;
		strcpy(perms, none);
		if (entry->d_type == 4) {
			strncpy(perms, "d", 1);
		}else {
			total += size;
		}
		bit = 1;
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
