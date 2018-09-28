//
//  MyTexture.cpp
//  Mine
//
//  Created by xy on 2018/6/22.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyVector.hpp"
#include "MyData.hpp"
#include "../thirdparty/png/include/png.h"
#include "MyImage.hpp"

MINE_NAMESPACE_BEGIN

MyImage* MyImage::image(void) {
    return new MyImage;
}

MyImage* MyImage::imageWithColor(const MyFVector3 &color) {
    return imageWithColor(MyFVector4(color));
}

MyImage* MyImage::imageWithColor(const MyFVector4 &color) {
    return new MyImage(color);
}

MyImage* MyImage::imageWithContentsOfFile(const char *path) {
    return new MyImage(path);
}

MyImage::MyImage(const MyFVector3 &color) {
    initWithColor(MyFVector4(color));
}

MyImage::MyImage(const MyFVector4 &color) {
    initWithColor(color);
}

MyImage::MyImage(const char* path) {
    initWithContentsOfFile(path);
}

MyImage::~MyImage(void) {
    purge();
}

void MyImage::initWithColor(const MyFVector4 &color) {
    _width = _height = 1;
    _format = MyTextureFormat::RGBA;
    unsigned char data[4] = {static_cast<unsigned char>(color.x * 255),
        static_cast<unsigned char>(color.y * 255),
        static_cast<unsigned char>(color.z * 255),
        static_cast<unsigned char>(color.w * 255)};
    _data = MyData<unsigned char>::createWithData(data, sizeof(data));
    _data->addRef();
}

void MyImage::initWithContentsOfFile(const char *path) {
    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if(!png_ptr) {
        return;
    }
    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return;
    }
    
    int iRetVal = setjmp(png_jmpbuf(png_ptr));
    if(iRetVal) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return;
    }
    
    FILE* fp = fopen(path, "rb");
    if(!fp) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return;
    }
    
    png_init_io(png_ptr, fp);
    png_read_info(png_ptr, info_ptr);
    
    png_uint_32 width, height;
    int bit_depth, color_type;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, nullptr, nullptr, nullptr);
    
    png_color_16p pBackground;
    png_get_bKGD(png_ptr, info_ptr, &pBackground);
    
    switch(color_type) {
        case PNG_COLOR_TYPE_PALETTE:
            png_set_palette_to_rgb(png_ptr);
            break;
            
        case PNG_COLOR_TYPE_GRAY:
            if(bit_depth < 8) {
                png_set_expand_gray_1_2_4_to_8(png_ptr);
            }
            break;
            
        default:
            break;
    }
    if(bit_depth == 16) {
        png_set_strip_16(png_ptr);
    }
    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png_ptr);
    }
    if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(png_ptr);
    }
    
    const size_t rgba_size = width * height * 4;
    unsigned char* rgba_data = new unsigned char[rgba_size];
    png_bytepp row_pointers = (png_bytepp)png_malloc(png_ptr, sizeof(png_bytep) * height);
    for(int y = 0; y < height; ++y) {
        row_pointers[y] = (png_bytep)png_malloc(png_ptr, width << 2);
    }
    png_read_image(png_ptr, row_pointers);
    
    size_t pos = rgba_size - (4 * width);
    for(int row = 0; row < height; ++row) {
        for(int col = 0; col < 4 * width; col += 4) {
            rgba_data[pos++] = row_pointers[row][col];
            rgba_data[pos++] = row_pointers[row][col + 1];
            rgba_data[pos++] = row_pointers[row][col + 2];
            rgba_data[pos++] = row_pointers[row][col + 3];
        }
        pos -= width * 8;
    }
    
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(fp);
    
    _data = MyData<unsigned char>::createWithData(rgba_data, rgba_size);
    RETAIN_OBJECT(_data);
    _width = static_cast<int>(width);
    _height = static_cast<int>(height);
    _format = MyTextureFormat::RGBA;
    
    delete[] rgba_data;
}

void MyImage::purge(void) {
    RELEASE_OBJECT(_data);
}

MINE_NAMESPACE_END
