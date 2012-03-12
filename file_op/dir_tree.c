#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

#define LEN 256

int dir_tree(const char *path, int n)
{
	int i;
	struct dirent *dir;
	char sub_dir[LEN];
	DIR *dirp;

	dirp = opendir(path);
	if (dirp == NULL)
	{
		printf("path:%s\n", path);
		perror("opendir failed");
		return -1;
	}

	while (dir = readdir(dirp))
	{
		memset(sub_dir, 0, LEN);
		strcat(sub_dir, path);

		if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, ".."))
		{
			for (i = 0; i < n; i++)
			{
				printf("\t");
			}
			printf("%s%s\n", path, dir->d_name);
		}

		if ((dir->d_type == DT_DIR) && strcmp(dir->d_name, ".") && strcmp(dir->d_name, ".."))
		{
			strcat(sub_dir, dir->d_name);
			strcat(sub_dir, "/");
			dir_tree(sub_dir, n + 1);
		}
	}

	printf("\n");

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
		dir_tree("./", 0);
	else
		dir_tree(argv[1], 0);

	return 0;
}
