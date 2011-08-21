#pragma once

const unsigned int backgroundID=16777215;

struct TempColor
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

static struct TempColor uint2Color(unsigned int id)
{
	struct TempColor *temp=(struct TempColor *)&id;
	return *temp;
}

static int color2UInt(struct TempColor color)
{
	int *temp=(int *)&color;
	return *temp;
}