#include <windows.h>
#include<gl/GL.h>
#include <gl/GLU.h> //数学好可以不必用他

#include "texture.h"

/* 监听用户操作函数;LRESULT(函数返回值类型); CALLBACK(调用方式)
   hwnd(窗口句柄，用于标记用户操作了哪一个窗口); msg(消息ID，比如1表示用户拖拽了窗口);
   wParam(消息附带参数，比如用户拖拽窗口，具体拖到什么地方去了); lParam(消息附带参数)
*/
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
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

	//初始化
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0, 800.0 / 600.0, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f); //擦除背景色
	glEnable(GL_CULL_FACE); //只绘制正面，提高效率，如果电连接为顺时针则无法显示

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

	glEnable(GL_LIGHTING); //开启光照
	glEnable(GL_LIGHT0);

	Texture texture;
	texture.Init("./res/test.bmp");

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
		//glLoadIdentity();//进来之后先给MV矩阵设为单位矩阵
		glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT); //擦除颜色缓冲区

		glEnable(GL_TEXTURE_2D); //开启纹理
		glBindTexture(GL_TEXTURE_2D, texture.mTextureId);

		//glScalef(1.0f, 1.0f, 0.5f); //缩放的是坐标
		//glRotatef(30.0f, 0.0f, 0.0f, -1.0f);
		//glTranslatef(2.0f, 0.0f, 0.0f);

		//默认方向：ccw，逆时针方向
		//GL_POLYGON:必须是凸多边形
		glBegin(GL_POLYGON); 
		//glColor4ub(255.0, 0.0, 0.0, 255.0); //颜色差值
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(-1.0, -0.5, -2);

		//glColor4ub(0.0, 255.0, 0.0, 255.0);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(1.0, -0.5, -2);

		//glColor4ub(0.0, 0.0, 255.0, 255.0);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.5, 1.0);
		glVertex3f(0.0, -0.5, -10);

		glEnd();

		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);

		SwapBuffers(dc); //交换前后缓冲区使得用户可以看见
	}

	return 0;
}