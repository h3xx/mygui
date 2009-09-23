/*!
	@file
	@author		Albert Semenov
	@date		08/2008
	@module
*/
#include "precompiled.h"
#include "DemoKeeper.h"
#include "Base/Main.h"

namespace demo
{

	void DemoKeeper::setupResources()
	{
		base::BaseManager::setupResources();
		addResourceLocation(mRootMedia + "/Demos/Demo_PanelView");
		addResourceLocation(mRootMedia + "/Common/Wallpapers");
	}

	void DemoKeeper::createScene()
	{
		setWallpaper("wallpaper0.png");
		setDescriptionText("Panel View control implementation.");

		mView = new PanelViewWindow();
		mPanelDirector = new PanelDirector();
		mPanelDynamic = new PanelDynamic();
		mPanelStatic = new PanelStatic();

		mPanelDirector->eventChangePanels = MyGUI::newDelegate(this, &DemoKeeper::notifyChangePanels);
		mView->getPanelView()->addItem(mPanelDirector);
		mView->getPanelView()->addItem(mPanelDynamic);
		mView->getPanelView()->addItem(mPanelStatic);
	}

	void DemoKeeper::destroyScene()
	{
		mView->getPanelView()->removeAllItems();
		delete mView;

		delete mPanelDirector;
		delete mPanelDynamic;
		delete mPanelStatic;
	}

	void DemoKeeper::notifyChangePanels(int _key, size_t _value)
	{
		if (_key == EVENT_SHOW_STATIC)
		{
			mView->getPanelView()->setItemShow(mPanelStatic, _value != 0);
		}
		else if (_key == EVENT_SHOW_DYNAMIC)
		{
			mView->getPanelView()->setItemShow(mPanelDynamic, _value != 0);
		}
		else if (_key == EVENT_COUNT_DYNAMIC)
		{
			mPanelDynamic->setVisibleCount(_value);
		}
	}

} // namespace demo

MYGUI_APP(demo::DemoKeeper)
