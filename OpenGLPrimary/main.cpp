#include <windows.h>
#include<gl/GL.h>
#include <gl/GLU.h> //数学好可以不必用他

#include "texture.h"
#include "objmodel.h"
#include "camera.h"
#include "skybox.h"
#include "imagesprite.h"
#include "ground.h"

Camera camera;
SkyBox skyBox;
Ground ground;
ImageSprite imageSprite;
POINT originalPoint;
bool isRotate = false;
/* 监听用户操作函数;LRESULT(函数返回值类型); CALLBACK(调用方式)
   hwnd(窗口句柄，用于标记用户操作了哪一个窗口); msg(消息ID，比如1表示用户拖拽了窗口);
   wParam(消息附带参数，比如用户拖拽窗口，具体拖到什么地方去了); lParam(消息附带参数)
*/
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		if (isRotate)
		{
			POINT currentPoint;
			currentPoint.x = LOWORD(lParam);
			currentPoint.y = HIWORD(lParam);
			ClientToScreen(hwnd, &currentPoint);
			int deltaX = currentPoint.x - originalPoint.x;
			int deltaY = currentPoint.y - originalPoint.y;
			float rotateAngleRoll = deltaY / 1000.0; //极限公式支撑
			float rotateAnglePitch = deltaX / 1000.0;
			camera.Pitch(-rotateAngleRoll);
			camera.Yam(-rotateAnglePitch);
			SetCursorPos(originalPoint.x, originalPoint.y);
		}
		break;
	case WM_RBUTTONDOWN:
		originalPoint.x = LOWORD(lParam);
		originalPoint.y = HIWORD(lParam);
		ClientToScreen(hwnd, &originalPoint);
		SetCapture(hwnd);
		ShowCursor(false);
		isRotate = true;
		break;
	case WM_RBUTTONUP:
		SetCursorPos(originalPoint.x, originalPoint.y);
		ReleaseCapture();
		ShowCursor(true);
		isRotate = false;
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			camera.mMoveLeft = true;
			break;
		case 'D':
			camera.mMoveRight = true;
			break;
		case 'W':
			camera.mMoveFoward = true;
			break;
		case 'S':
			camera.mMoveBackWord = true;
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'A':
			camera.mMoveLeft = false;
			break;
		case 'D':
			camera.mMoveRight = false;
			break;
		case 'W':
			camera.mMoveFoward = false;
			break;
		case 'S':
			camera.mMoveBackWord = false;
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
	rect.right = 1280;
	rect.top = 0;
	rect.bottom = 720;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL); // 窗口风格和菜单句柄

	//创建窗口
	//参数依次对应为：窗口创建的风格，窗口名称（注册时的名称）, 窗口右上角标题栏，窗口的风格，窗帘起始位置，窗口的宽和高, 附窗口的句柄，菜单句柄， 窗口实例
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"Opengl Window", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
	GetClientRect(hwnd, &rect);
	int viewportWidth = rect.right - rect.left;
	int viewportHeight = rect.bottom - rect.top;

	//创建opengl渲染环境
	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd; //像素格式描述符
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32; //一个像素占用32bit，RGBA分别占用8bit
	pfd.cDepthBits = 24; //深度缓冲区每个像素占24it，浮点数
	pfd.cStencilBits = 8; //蒙板缓冲区每个像素占8bit
	pfd.iPixelType = PFD_TYPE_RGBA; //设置像素类型
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; //设置一下其他的flag
	int pixelFormat = ChoosePixelFormat(dc, &pfd); //让系统选格式
	SetPixelFormat(dc, pixelFormat, &pfd);
	HGLRC rc = wglCreateContext(dc); //渲染环境
	wglMakeCurrent(dc, rc); //使渲染环境生效

	glViewport(0, 0, viewportWidth, viewportHeight);
	//初始化
	camera.viewPortWidth = viewportWidth;
	camera.viewPortHeight = viewportHeight;


	glClearColor(0.1f, 0.4f, 0.6f, 1.0f); //擦除背景色
	glEnable(GL_CULL_FACE); //只绘制正面，提高效率，如果电连接为顺时针则无法显示
	glEnable(GL_DEPTH_TEST);

	//glFrontFace(GL_CW); //设置正方向为顺时针

	//glPolygonMode(GL_BACK, GL_LINE); //线框模式，GL_POINT:点。默认：GL_FILL
	//glPolygonMode(GL_BACK, GL_POINT);
	//glPointSize(10.0f);
	//glEnable(GL_POINT_SMOOTH);

	//显示窗口
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd); //窗口显示出来有可能是脏的，需要刷新一次窗口

	float blackColor[] = { 0.0f,0.0f,0.0f,1.0f };
	float whiteColor[] = { 1.0f,1.0f,1.0f,1.0f };
	float lightPosition[] = { 0.0f,1.0f,0.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //direction,point,spot

	float blackMatri[] = { 0.0f,0.0f,0.0f,1.0f };
	float ambintMatri[] = { 0.1f,0.1f,0.1f,1.0f };
	float diffuseMatri[] = { 0.4f,0.4f,0.4f,1.0f };
	float specularMatri[] = { 0.9f,0.9f,0.9f,1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambintMatri);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMatri);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMatri);
	//glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
	glEnable(GL_LIGHTING); //开启光照
	glEnable(GL_LIGHT0);

	Texture* texture = Texture::LoadTexture("./res/earth.bmp");
	Texture* spriteTexture = Texture::LoadTexture("./res/head.png");

	ObjModel model;
	model.Init("./res/Sphere.obj");
	skyBox.Init("./res/skybox");
	//imageSprite
	imageSprite.SetTexture(spriteTexture);
	imageSprite.SetRect(-300.0, -200.0, 100.0, 100.0);
	//ground
	ground.Init();

	static float sTimeSinceStartUp = timeGetTime() / 1000.0f;
	//用循环来保持窗口显示
	MSG msg;
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
		camera.SwitchTo3D();
		glLoadIdentity();//进来之后先给MV矩阵设为单位矩阵
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //擦除颜色缓冲区
		//GL_DEPTH_BUFFER_BIT，深度1.0，深度最远

		float currentTime = timeGetTime() / 1000.0f;
		float timeElapse = currentTime - sTimeSinceStartUp;
		sTimeSinceStartUp = currentTime;
		//printf("%f\n", timeElapse);

		camera.Update(0.016f);

		//先画最远的才行
		skyBox.Draw(camera.mPos.x, camera.mPos.y, camera.mPos.z);
		//ground
		ground.Draw();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->mTextureId);
		model.Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		//draw ui
		camera.SwitchTo2D();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		imageSprite.Draw();

		SwapBuffers(dc); //交换前后缓冲区使得用户可以看见
	}

	return 0;
}