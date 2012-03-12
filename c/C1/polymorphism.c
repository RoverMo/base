#include <stdio.h>

#define SON_ADD(ptr, type, member) ((struct type *)((void *)ptr - (void *)&((struct type*)0)->member))

enum
{
	NET = 1,
	VIDEO,
};

struct dev
{
	int type;
	int (*init)(struct dev *d);
};

struct net_dev
{
	int (*net_init)(struct net_dev *nd);
	struct dev pd;
};

struct video_dev
{
	int (*video_init)(struct video_dev *vd);
	struct dev pd;
};

int n_init(struct net_dev *nd)
{
	printf("net init\n");
	return 0;
}

int v_init(struct video_dev *vd)
{
	printf("video init\n");
	return 0;
}

int init(struct dev *d)
{
	int (*pinit)(void *);
	void *p;

	switch (d->type)
	{
	case NET:
		p = SON_ADD(d, net_dev, pd);
		pinit = ((struct net_dev *)p)->net_init;
		break;

	case VIDEO:
		p = SON_ADD(d, video_dev, pd);
		pinit = ((struct video_dev *)p)->video_init;
		break;

	default:
		printf("error\n");
		return -1;
	}

	pinit(p);

	return 0;
}

int main()
{
	struct net_dev nd;
	nd.pd.init = init;
	nd.pd.type = NET;
	nd.net_init = n_init;

	struct video_dev vd;
	vd.pd.init = init;
	vd.pd.type = VIDEO;
	vd.video_init = v_init;

	nd.pd.init(&(nd.pd));
	vd.pd.init(&(vd.pd));

	return 0;
}
