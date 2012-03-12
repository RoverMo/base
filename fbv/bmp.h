#pragma once

#include "auto_config.h"

#pragma pack(1)
struct bmp_file_header
{
	uint8	type[2];
	uint32	size;
	uint32	reserved;
	uint32	offset;
};

struct bmp_info_header
{
	uint32 size;
	uint32 width;
	uint32 height;
	uint16 planes;
	uint32 bit_count;
	uint16 compress;
	uint32 size_image;
	uint32 x_pels_per_meter;
	uint32 y_pels_per_meter;
	uint32 clr_used;
	uint32 clr_important;
};

struct bmp_pixel
{
	uint8 red;
	uint8 green;
	uint8 blue;
};
#pragma pack()
