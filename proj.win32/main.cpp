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
	 //这个地方就是用来设置实际设备的大小的，常见的手机屏幕分辨率如下：
    /*480X800  现在最主流的中高端安卓智能机的分辨率，包括 windows phone也是这个分辨率
    480X854  这个是WFVGA，是480X800的加长版
    540X960  HTC的高端机很喜欢用这个分辨率也就是qHD了
    640X960 最经典的iphone所使用的分辨率
    1136X640  iphone5的分辨率
    1280X720  传说中的HD，也是现在各品牌主流旗舰机型的分辨率，而且屏幕都很大。
    1280X800  现在只有三星的9220的5.3英寸巨屏用了这以分辨率
    1024x768    iPad1分辨率 iPad2分辨率 iPad mini分辨率
    2048×1536  iPad3分辨率 iPad4分辨率 iPad Air分辨率 iPad mini 2分辨率
    1920x1080 Nexus5分辨率*/
	eglView->setFrameSize(540,960);
    return Application::getInstance()->run();
}
