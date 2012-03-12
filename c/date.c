#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <linux/errno.h>

static unsigned int leap_year_month_days[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static unsigned int non_leap_year_month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct date_property
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
};

struct date
{
	struct date_property property[0];
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int *month_days;

	void (*print)(const struct date *d);
	struct date *(*next_date)(const struct date *d);
	struct date *(*get_prior)(struct date *d1, struct date *d2);
	struct date *(*get_later)(struct date *d1, struct date *d2);
	unsigned int (*days_in_year)(struct date *d);
	unsigned int (*days_between_date)(struct date *d1, struct date *d2);
	void (*destory)(struct date *d);
};

int date_init(struct date **new_date, unsigned int year, unsigned int month, unsigned int day);

static int is_leap_year(unsigned int year)
{
	return ((!(year % 4) && (year % 100)) || !(year % 400));
}

static void date_print(const struct date *d)
{
	printf("%04u-%02u-%02u\n", d->year, d->month, d->day);
}

static struct date *date_next_date(const struct date *d)
{
	int ret;
	struct date tmp;
	struct date *next_date;

	if (d->day == d->month_days[d->month - 1])
	{
		tmp.day = 1;
		if (d->month == 12)
		{
			tmp.year = d->year + 1;
			tmp.month= 1;
		}
		else
		{
			tmp.month	= d->month + 1;
			tmp.year	= d->year;
		}
	}
	else
	{
		tmp.day	= d->day + 1;
		tmp.month	= d->month;
		tmp.year	= d->year;
	}

	ret = date_init(&next_date, tmp.year, tmp.month, tmp.day);
	if (ret < 0)
	{
		return NULL;
	}

	return next_date;
}

static struct date *date_get_prior(struct date *d1, struct date *d2)
{
	int ret;

	ret = memcmp(d1->property, d2->property, sizeof(*d1->property));
	if (ret <= 0)
	{
		return d1;
	}

	return d2;
}

static struct date *date_get_later(struct date *d1, struct date *d2)
{
	int ret;

	ret = memcmp(d1->property, d2->property, sizeof(*d1->property));
	if (ret > 0)
	{
		return d1;
	}

	return d2;
}

static unsigned int date_days_between_date(struct date *d1, struct date *d2)
{
	int i;
	int days;
	struct date *tmp;

	tmp	= d1->get_prior(d1, d2);
	d2	= d2->get_later(d1, d2);
	d1	= tmp;

	days = 0;

	for (i = d1->year; i < d2->year; i++)
	{
		if (is_leap_year(i))
		{
			days += 366;
		}
		else
		{
			days += 365;
		}
	}

	days -= d1->days_in_year(d1);
	days += d2->days_in_year(d2);

	return days;
}

static unsigned int date_days_in_year(struct date *d)
{
	int i;
	int days;

	days = d->day;;

	for (i = 0; i < d->month - 1; i++)
	{
		days += d->month_days[i];
	}

	return days;
}

static void date_destory(struct date *d)
{
	free(d);
}

int date_init(struct date **new_date, unsigned int year, unsigned int month, unsigned int day)
{
	(*new_date) = (struct date *)malloc(sizeof(**new_date));
	if (NULL == *new_date)
	{
		return -ENOMEM;
	}

	if (is_leap_year(year))
	{
		(*new_date)->month_days = leap_year_month_days;
	}
	else
	{
		(*new_date)->month_days = non_leap_year_month_days;
	}

	(*new_date)->year	= year;
	(*new_date)->month	= month;
	(*new_date)->day	= day;

	(*new_date)->print			= date_print;
	(*new_date)->next_date		= date_next_date;
	(*new_date)->get_prior		= date_get_prior;
	(*new_date)->get_later		= date_get_later;
	(*new_date)->days_in_year	= date_days_in_year;
	(*new_date)->days_between_date = date_days_between_date;
	(*new_date)->destory		= date_destory;

	return 0;
}

int main(int argc, char *argv[])
{
	int ret;
	unsigned int days;
	struct date *d1, *d2;
	unsigned int year, month, day;

	printf("What date is today?(2008-8-8)\n");
	scanf("%u-%u-%u", &year, &month, &day);

	ret = date_init(&d1, year, month, day);
	if (ret < 0)
	{
		perror("date_init()");
		return ret;
	}

	printf("What is your birthday?\n");
	scanf("%u-%u-%u", &year, &month, &day);

	ret = date_init(&d2, year, month, day);
	if (ret < 0)
	{
		perror("date_init()");
		return ret;
	}

	days = d1->days_between_date(d1, d2);
	printf("days = %d\n", days);

	d1->destory(d1);
	d2->destory(d2);

	return 0;
}
