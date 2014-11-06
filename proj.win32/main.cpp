#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
	auto director = Director::getInstance();
	CCEGLView* eglView = director->getOpenGLView();
	if (!eglView)
	{
		eglView = GLView::create("TimberMan");
		director->setOpenGLView(eglView);
	}
	eglView->setViewName("resolution");
	 //����ط�������������ʵ���豸�Ĵ�С�ģ��������ֻ���Ļ�ֱ������£�
    /*480X800  �������������и߶˰�׿���ܻ��ķֱ��ʣ����� windows phoneҲ������ֱ���
    480X854  �����WFVGA����480X800�ļӳ���
    540X960  HTC�ĸ߶˻���ϲ��������ֱ���Ҳ����qHD��
    640X960 ����iphone��ʹ�õķֱ���
    1136X640  iphone5�ķֱ���
    1280X720  ��˵�е�HD��Ҳ�����ڸ�Ʒ�������콢���͵ķֱ��ʣ�������Ļ���ܴ�
    1280X800  ����ֻ�����ǵ�9220��5.3Ӣ������������Էֱ���
    1024x768    iPad1�ֱ��� iPad2�ֱ��� iPad mini�ֱ���
    2048��1536  iPad3�ֱ��� iPad4�ֱ��� iPad Air�ֱ��� iPad mini 2�ֱ���
    1920x1080 Nexus5�ֱ���*/
	eglView->setFrameSize(540,960);
    return Application::getInstance()->run();
}
