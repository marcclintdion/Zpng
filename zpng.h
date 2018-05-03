#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ZPNG_Buffer
{
    // Pointer to data
    unsigned char* Data;

    // Size of buffer in bytes
    unsigned Bytes;
};

struct ZPNG_Header
{
    uint16_t Magic;
    uint16_t Width;
    uint16_t Height;
    uint8_t Channels;
    uint8_t BytesPerChannel;
};

#define ZPNG_HEADER_MAGIC 0xFBF8
#define ZPNG_HEADER_OVERHEAD_BYTES 8

struct ZPNG_ImageData
{
    // Pixel data
    ZPNG_Buffer Buffer;

    /*
        This supports 1-2 bytes per channel.
        And 1-4 channels per pixel.
        There is no support for separate color planes with different sizes.
    */

    // Number of bytes for each color channel
    unsigned BytesPerChannel;

    // Number of channels for each pixel
    unsigned Channels;

    // Width in pixels of image
    unsigned WidthPixels;

    // Height in pixels of image
    unsigned HeightPixels;

    // Width of pixel row in bytes
    unsigned StrideBytes;
};


//------------------------------------------------------------------------------
// API

// Compress image into a buffer.
// The returned buffer should be passed to ZPNG_Free().
ZPNG_Buffer ZPNG_Compress(
    const ZPNG_ImageData* imageData
);

// Decompress image from a buffer.
// The returned ZPNG_Buffer should be passed to ZPNG_Free().
ZPNG_ImageData ZPNG_Decompress(
    ZPNG_Buffer buffer
);

// Free buffer when done to avoid leaks
void ZPNG_Free(
    ZPNG_Buffer* buffer
);


#ifdef __cplusplus
}
#endif
