/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "texture_2d.h"

#include <iostream>

texture_2d::texture_2d()
    :
	texture_width(0),
	texture_height(0),
	internal_format(GL_RGB),
	image_format(GL_RGB),
	wrap_s(GL_REPEAT),
	wrap_t(GL_REPEAT),
	filter_min(GL_LINEAR),
	filter_max(GL_LINEAR)
{
    glGenTextures(1, &this->id);
}

void texture_2d::generate(
	const GLsizei width,
	const GLsizei height,
	const unsigned char* data
)
{
    this->texture_width = width;
    this->texture_height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        this->internal_format,
        this->texture_width,
        this->texture_height,
        0,
        this->image_format,
        GL_UNSIGNED_BYTE,
        data
    );
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_2d::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}