#include <iostream>
#include <Windows.h>

bool running = true;

// buffer related stuff - Whatever that is...
void* buffer_memory;
int buffer_width;
int buffer_height;
BITMAPINFO buffer_bitmap_info;

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
        buffer_width = rect.right - rect.left;
        buffer_height = rect.bottom - rect.top;

        int buffer = buffer_width * buffer_height * sizeof(unsigned int);

        // if buffer memory needs to be updated, then free up the memory
        if (buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);

        // this gives the buffer the memory it needs!
        buffer_memory = VirtualAlloc(0, buffer, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
        buffer_bitmap_info.bmiHeader.biWidth = buffer_width;
        buffer_bitmap_info.bmiHeader.biHeight = buffer_height;
        buffer_bitmap_info.bmiHeader.biPlanes = 1;
        buffer_bitmap_info.bmiHeader.biBitCount = 32;
        buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;

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
        StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width, buffer_height, buffer_memory, &buffer_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    
    }

    return 0;
}
