#include <iostream>
#include "renderer.cpp"

bool running = true;

// The Render state handles buffer memory allocation for graphics?
RenderState renderState;


// The WndProc handles messages and correspond to windows based messages to carry out commands.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message){

    case WM_DESTROY:
        running = false;
        PostQuitMessage(0);
        break;
    
    case WM_SIZE: {

        // rect struct uses four coordinates corresponding to each side of a rectangle
        RECT rect;
        GetClientRect(hWnd, &rect);
        renderState.width = rect.right - rect.left;
        renderState.height = rect.bottom - rect.top;

        int buffer = renderState.width * renderState.height * sizeof(unsigned int);

        // if buffer memory needs to be updated, then free up the memory
        if (renderState.memory) VirtualFree(renderState.memory, 0, MEM_RELEASE);

        // this gives the buffer the memory it needs!
        renderState.memory = VirtualAlloc(0, buffer, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        //Sets renderState.bitmap_info qualities
        renderState.bitmapInfo.bmiHeader.biSize = sizeof(renderState.bitmapInfo.bmiHeader);
        renderState.bitmapInfo.bmiHeader.biWidth = renderState.width;
        renderState.bitmapInfo.bmiHeader.biHeight = renderState.height;
        renderState.bitmapInfo.bmiHeader.biPlanes = 1;
        renderState.bitmapInfo.bmiHeader.biBitCount = 32;
        renderState.bitmapInfo.bmiHeader.biCompression = BI_RGB;

    } break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// WinMain is the entry point to any windows based application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //Creating a window class
    WNDCLASS wc = {};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = L"MyWindowClass";

    //Registering the window 
    RegisterClass(&wc);

    //Creating the window
    HWND hWnd = CreateWindowEx(0, L"MyWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);
    HDC hdc = GetDC(hWnd);

    // Main Game Loop
    while (running)
    {
        // Input
        MSG message;
        while (PeekMessage(&message, hWnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
            }
        // Simulate

        // Render
        StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
        makeBackground(renderState);
        draw_rect(renderState, 490, 490, 650, 500, 0x20ff20);
        draw_rect(renderState, 10, 10, 50, 500, 0x202020);

    }

    return 0;
}
