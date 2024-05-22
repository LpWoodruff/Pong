#include <Windows.h>


struct RenderState
{
    void* memory;
    int width, height;
    BITMAPINFO bitmapInfo;
    int buffer = width * height * sizeof(unsigned int);

};

void makeBackground(RenderState& renderState)
{
    unsigned int* pixel = (unsigned int*)renderState.memory;
    for (int y = 0; y < renderState.height; y++)
    {
        for (int x = 0; x < renderState.width; x++)
        {
            *pixel++ = 0xdf0040;
        }
    }
}

void clearScreen(RenderState& renderState, unsigned int color)
{
    unsigned int* pixel = (unsigned int*)renderState.memory;
     for (int y = 0; y < renderState.height; y++)
    {
        for (int x = 0; x < renderState.width; x++)
        {
            *pixel++ = color;
        }
    }
}

void draw_rect(RenderState& renderState, int x0, int y0, int x1, int y1, unsigned int color)
{
    for (int y = y0; y < y1; y++)
    {
        unsigned int* pixel = (unsigned int*)renderState.memory + x0 + y*renderState.width;
        for (int x = x0; x < x1; x++)
        {
            *pixel++ = color;
        }
    }
}

