#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <linux/fb.h>

#include "bmp.h"

#define FB_DEV_NAME	"/dev/fb0"
#define	DEBUG() do { \
					printf("%s():%d\n", __FUNCTION__, __LINE__); \
					perror(""); \
				} while(0)

static int screen_size;
static struct fb_var_screeninfo fb_var;

void bmp_file_header_print(const struct bmp_file_header *this)
{
	printf("bmp_file_header:\n");
	printf("\ttype:%s\n", this->type);
	printf("\tsize:%d\n", this->size);
	printf("\toffset:%d\n\n", this->offset);
}

void bmp_info_header_print(const struct bmp_info_header *this)
{
	printf("bmp_info_header:\n");
	printf("\tsize:%d\n", this->size);
	printf("\twidth:%d\n", this->width);
	printf("\theight:%d\n", this->height);
	printf("\tplanes:%d\n", this->planes);
	printf("\tbit_count:%d\n", this->bit_count);
	printf("\tcompress:%d\n", this->compress);
	printf("\tsize_image:%d\n", this->size_image);
	printf("\tx_pels_per_meter:%d\n", this->x_pels_per_meter);
	printf("\ty_pels_per_meter:%d\n", this->y_pels_per_meter);
	printf("\tclr_used:%d\n", this->clr_used);
	printf("\tclr_important:%d\n\n", this->clr_important);
}

void fb_var_screeninfo_print(const struct fb_var_screeninfo *this)
{
	printf("fb_var_screeninfo:\n");
	printf("\tdepth:%d\n", this->bits_per_pixel);
	printf("\trgb:%d/%d %d/%d %d/%d\n\n", this->red.length, this->red.offset, this->green.length, this->green.offset, this->blue.length, this->blue.offset);
}

static int fb_init(struct screen_pixel **fb_mem)
{
	int fd;
	int ret;

	fd = open(FB_DEV_NAME, O_RDWR);
	if (fd < 0)
	{
		return fd;
	}

	ret = ioctl(fd, FBIOGET_VSCREENINFO, &fb_var);
	if (ret < 0)
	{
		close(fd);
		return ret;
	}
	fb_var_screeninfo_print(&fb_var);

	screen_size = fb_var.xres * fb_var.yres * fb_var.bits_per_pixel >> 3;
	*fb_mem = (struct screen_pixel *)mmap(0, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (NULL == fb_mem)
	{
		close(fd);
		return -ENOMEM;
	}
	memset(*fb_mem, 0, screen_size);

	close(fd);

	return 0;
}

void pixel_bmp2screen(  struct screen_pixel *screen_pix,
						const struct bmp_pixel *bmp_pix,
						const struct fb_var_screeninfo *fb_var)
{
	screen_pix->red		= bmp_pix->red >> (8 - fb_var->red.length);
	screen_pix->green	= bmp_pix->green >> (8 - fb_var->green.length);
	screen_pix->blue	= bmp_pix->blue >> (8 - fb_var->blue.length);
}

static int display(struct screen_pixel *fb_mem, const char *image_name)
{
	int		ret, i;
	int		fd;
	off_t	offset;
	struct	bmp_file_header file_hdr;
	struct	bmp_info_header imge_hdr;
	int		xres, yres;
	int		step;
	struct	bmp_pixel bmp_pix;
	struct	screen_pixel screen_pix;

	fd = open(image_name, O_RDONLY);
	if (fd < 0)
	{
		return fd;
	}

	ret = read(fd, &file_hdr, sizeof(file_hdr));
	if (ret < 0)
	{
		close(fd);
		return ret;
	}

	bmp_file_header_print(&file_hdr);

	ret = read(fd, &imge_hdr, sizeof(imge_hdr));
	if (ret < 0)
	{
		close(fd);
		return ret;
	}

	bmp_info_header_print(&imge_hdr);

	offset = lseek(fd, file_hdr.offset, SEEK_SET);
	if (offset < 0)
	{
		close(fd);
		return offset;
	}

	xres = imge_hdr.width;
	yres = imge_hdr.height;
	step = 1;

	while (fb_var.xres < xres || fb_var.yres < yres)
	{
		xres >>= 1;
		yres >>= 1;
		step++;
	}
	printf("xres:%d\n", xres);
	printf("yres:%d\n", yres);

	fb_mem += fb_var.xres * fb_var.yres - xres;

	do {
		for (i = 0; i < xres; i++)
		{
			if (step > 1)
			{
				lseek(fd, (step - 1) * sizeof(bmp_pix), SEEK_CUR);
			}

			ret = read(fd, &bmp_pix, sizeof(bmp_pix));
			if (ret < 0)
			{
				close(fd);
				return ret;
			}
			pixel_bmp2screen(&screen_pix, &bmp_pix, &fb_var);
			memcpy(fb_mem, &screen_pix, sizeof(bmp_pix));
			fb_mem++;

			if (ret < sizeof(bmp_pix))
			{
				break;
			}
		}
		lseek(fd, (step - 1) * imge_hdr.width * sizeof(bmp_pix), SEEK_CUR);
		fb_mem -= fb_var.xres + xres;
	} while (ret == sizeof(bmp_pix));

	close(fd);

	return 0;
}

void fb_destory(struct screen_pixel *fb_mem)
{
	munmap(fb_mem, screen_size);
}

int main(int argc, char *argv[])
{
	static struct screen_pixel *fb_mem;

	if (argc != 2)
	{
		printf("Usage: ./bmp xxx.bmp\n");
		return -EINVAL;
	}

	fb_init(&fb_mem);

	display(fb_mem, argv[1]);

	fb_destory(fb_mem);

	return 0;
}
