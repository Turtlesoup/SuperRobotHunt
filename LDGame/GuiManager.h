#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include "JSON.h"
#include "GuiLayoutData.h"
#include "DisplayObject.h"
#include "WidgetTypes.h"
#include "BitmapFont.h"

class BaseGuiWidget;

class GuiManager
{
	public:
		virtual ~GuiManager();
		static GuiManager *Get();
		void loadGuiLayoutData(std::string fileName);
		BaseGuiWidget *createLayout(std::string fileName);
		std::vector<BaseGuiWidget*> getWidgetsOfType(const WIDGET_TYPE type, BaseGuiWidget *widget);
		BaseGuiWidget* getWidgetWithID(std::string id, BaseGuiWidget *widget);
		void addBitmapFont(std::string fontFile, std::string bitmapFontImageFile, std::string textureAtlasName);
		void removeBitmapFont(std::string fontFile);
		BitmapFont &getBitmapFont(std::string fontFile);
	private:
		GuiManager();
		static GuiManager *_instance;
		GuiLayoutData createGuiLayoutDataFromJSONObject(JSONObject jsonObject);
		BaseGuiWidget *createGuiWidget(GuiLayoutData &guiLayoutData);
		void getWidgetsOfTypeHelper(const WIDGET_TYPE type, BaseGuiWidget *widget, std::vector<BaseGuiWidget*> &widgets);
		std::map<std::string, GuiLayoutData> _guiLayoutDatas;
		std::map<std::string, BitmapFont> _fonts;
};

#endif