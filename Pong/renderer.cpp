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
            *pixel++ = 0xff00ff;
        }
    }
}

void clearScreen(int color)
{

}


void draw_rect(int &x, int &y, int &width, int &height, int &color )
{

}
