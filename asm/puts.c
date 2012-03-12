extern int _puts(const char *);

int main(int argc, char **argv)
{
	int count;
	const char *str = "rover";

	count = _puts(str);
	printf("%d\n", count);
	count = puts(str);
	printf("%d\n", count);

	return 0;
}
