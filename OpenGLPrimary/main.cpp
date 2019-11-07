#include <stdio.h>
#include "common.h"
#pragma comment(lib, "opengl32.lib") //可以在工程里面设置
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib") //timeGetTime

#include "command/command_render_point.h"
#include "command/command_render_line.h"
#include "command/command_render_line_loop.h"
#include "command/command_render_line_strip.h"
#include "command/command_render_tringles.h"
#include "command/command_render_tringlestrip.h"
#include "command/command_render_tringlefan.h"
#include "command/command_render_quads.h"
#include "command/command_render_pan_rotate_zoom_matrix_light.h"
#include "command/command_render_texture.h"
#include "command/command_render_objmodel.h"
#include "context/camera.h"

LH::Camera camera;
POINT originalPos;
bool isRotateView;
/* 监听用户操作函数;LRESULT(函数返回值类型); CALLBACK(调用方式)
   hwnd(窗口句柄，用于标记用户操作了哪一个窗口); msg(消息ID，比如1表示用户拖拽了窗口);
   wParam(消息附带参数，比如用户拖拽窗口，具体拖到什么地方去了); lParam(消息附带参数)
*/
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		if (isRotateView)
		{
			camera.Pitch(-0.001);
		}
		break;
	case WM_RBUTTONDOWN:
		originalPos.x = LOWORD(lParam);
		originalPos.y = HIWORD(lParam);
		ClientToScreen(hwnd, &originalPos); //转成屏幕坐标
		SetCapture(hwnd);
		ShowCursor(false);
		isRotateView = true;
		break;
	case WM_RBUTTONUP:
		SetCursorPos(originalPos.x, originalPos.y);
		ReleaseCapture();
		ShowCursor(true);
		isRotateView = false;
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			camera.mIsMoveLeft = true;
			break;
		case 'D':
			camera.mIsMoveRight = true;
			break;
		case 'W':
			camera.mIsMoveForward = true;
			break;
		case 'S':
			camera.mIsMoveBackward = true;
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'A':
			camera.mIsMoveLeft = false;
			break;
		case 'D':
			camera.mIsMoveRight = false;
			break;
		case 'W':
			camera.mIsMoveForward = false;
			break;
		case 'S':
			camera.mIsMoveBackward = false;
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE: //目前只关心退出窗口的消息
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

/* INT（函数返回值类型）; WINAPI（函数修饰符,强调调用方式）;
   操作系统启东时传入的参数：hInstance（当前应用程序的实例),hPrevInstance（上一次该应用程序启动的实例），
   lpCmdLine（命令行启东程序传入的参数）,nShowCmd（窗口显示相关参数）*/ 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//创建窗口包含四步：注册，创建，显示，监听用户操作

	//注册窗口
	WNDCLASSEX windClass; //用此结构体告诉操作系统我们需要一个什么样的窗口
	windClass.cbClsExtra = NULL; //窗口类型的额外空间（在此我们不需要额外的空间）
	windClass.cbSize = sizeof(WNDCLASSEX); //windClass这个对象实际占用的内存
	windClass.cbWndExtra = 0; //窗口的额外内存
	windClass.hbrBackground = NULL; //使用OpenGL擦除背景色，而不是要用GDI所以为NULL
	windClass.hCursor = LoadCursor(NULL, IDC_ARROW); //设置光标（在此设置为箭头光标）
	windClass.hIcon = NULL; //应用程序在文件夹中显示的图标（在此不设置）
	windClass.hIconSm = NULL; //应用程序启动后在左上角显示的图标
	windClass.hInstance = hInstance; //操作系统传入的参数
	windClass.lpfnWndProc = GLWindowProc; //此函数监听用户操作，告诉我们谁操作了我们的窗口
	windClass.lpszClassName = L"GLWindow"; //窗口名称
	windClass.lpszMenuName = NULL; //菜单的名字（没有菜单，赋空）
	windClass.style = CS_VREDRAW | CS_HREDRAW; //窗口刷新时采用的重绘方式（在此采用水平或者垂直重绘的方式）
	ATOM atom = RegisterClassEx(&windClass);
	if (!atom)
	{
		MessageBox(NULL, L"Notice", L"Error", MB_OK);
		return 0;
	}

	//视口大小
	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL); // 窗口风格和菜单句柄
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	//创建窗口
	//参数依次对应为：窗口创建的风格，窗口名称（注册时的名称）, 窗口右上角标题栏，窗口的风格，窗帘起始位置，窗口的宽和高, 附窗口的句柄，菜单句柄， 窗口实例
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"Opengl Window", WS_OVERLAPPEDWINDOW, 100, 100, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

	//创建opengl渲染环境
	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32; //一个像素占用32bit，RGBA分别占用8bit
	pfd.cDepthBits = 24; //深度缓冲区每个像素占24it，浮点数
	pfd.cStencilBits = 8; //蒙板缓冲区每个像素占8bit
	pfd.iPixelType = PFD_TYPE_RGBA; //设置像素类型
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; //设置一下其他的flag
	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);
	HGLRC rc = wglCreateContext(dc); //渲染环境
	wglMakeCurrent(dc, rc); //使渲染环境生效

	//初始化
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f); //擦除背景色

	//command
	LH::RenderCommandBase* commandBase = new LH::RenderObjModelCommand();
	commandBase->Init();
	

	//显示窗口
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd); //窗口显示出来有可能是脏的，需要刷新一次窗口

	//用循环来保持窗口显示
	MSG msg;
	static float sTimeSinceStartUp = timeGetTime() / 1000.0f;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		float currentTime = timeGetTime() / 1000.0f;
		float timeElapse = currentTime - sTimeSinceStartUp;
		sTimeSinceStartUp = currentTime;

		//set up camera
		camera.Update(timeElapse);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //擦除颜色缓冲区

		commandBase->Render();

		SwapBuffers(dc); //交换前后缓冲区使得用户可以看见
	}
	return 0;
}