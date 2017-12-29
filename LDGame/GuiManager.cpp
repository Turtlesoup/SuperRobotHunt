#include "GuiManager.h"
#include "StringHelper.h"
#include "BaseGuiWidget.h"
#include "BaseSpriteGuiWidget.h"
#include "TextGuiWidget.h"
#include "ButtonGuiWidget.h"
#include "GUIConsts.h"

GuiManager* GuiManager::_instance = nullptr;

GuiManager::GuiManager()
{
}

GuiManager::~GuiManager()
{
}

GuiManager *GuiManager::Get()
{
	if(_instance == nullptr)
	{
		_instance = new GuiManager();
	}

	return _instance;
}

void GuiManager::loadGuiLayoutData(std::string fileName)
{
	std::wstring jsonString = StringHelper::loadFromFile(fileName);
	JSONObject jsonObject = JSON::Parse(jsonString.c_str())->AsObject();

	_guiLayoutDatas[fileName] = createGuiLayoutDataFromJSONObject(jsonObject);
}

GuiLayoutData GuiManager::createGuiLayoutDataFromJSONObject(JSONObject jsonObject)
{
	GuiLayoutData returnGuiLayoutData;

	returnGuiLayoutData.id = StringHelper::wideStringToString(jsonObject[GUIConsts::ID]->AsString());
	returnGuiLayoutData.name = StringHelper::wideStringToString(jsonObject[GUIConsts::NAME]->AsString());

	std::string typeString = StringHelper::wideStringToString(jsonObject[GUIConsts::TYPE]->AsString());
	if(typeString == GUIConsts::WIDGET_GROUP)
	{
		returnGuiLayoutData.type = WIDGET_GROUP;
	}
	else if(typeString == GUIConsts::WIDGET_PANEL)
	{
		returnGuiLayoutData.type = WIDGET_PANEL;
	}
	else if(typeString == GUIConsts::WIDGET_BUTTON)
	{
		returnGuiLayoutData.type = WIDGET_BUTTON;
	}
	else if(typeString == GUIConsts::WIDGET_TEXT)
	{
		returnGuiLayoutData.type = WIDGET_TEXT;
	}

	returnGuiLayoutData.x = jsonObject[GUIConsts::X]->AsNumber();
	returnGuiLayoutData.y = jsonObject[GUIConsts::Y]->AsNumber();

	JSONArray propertiesArray = jsonObject[GUIConsts::PROPERTIES]->AsArray();
	JSONObject propertyKeyValuePair;
	std::string key;
	JSONValue* value;
	unsigned int propertiesArrayLength = propertiesArray.size();
	for(unsigned int propertiesArrayIndex = 0; propertiesArrayIndex < propertiesArrayLength; ++ propertiesArrayIndex)
	{
		propertyKeyValuePair = propertiesArray[propertiesArrayIndex]->AsObject();
		key = StringHelper::wideStringToString(propertyKeyValuePair[GUIConsts::KEY]->AsString());
		value = propertyKeyValuePair[GUIConsts::VALUE];

		if(value->IsNumber())
		{
			returnGuiLayoutData.properties[key] = GuiLayoutProperty(value->AsNumber());
		}
		else if(value->IsString())
		{
			returnGuiLayoutData.properties[key] = GuiLayoutProperty(StringHelper::wideStringToString(value->AsString()));
		}
		else if(value->IsBool())
		{
			returnGuiLayoutData.properties[key] = GuiLayoutProperty(value->AsBool());
		}
		else
		{
			returnGuiLayoutData.properties[key] = GuiLayoutProperty(/*NULL*/);
		}
	}

	JSONArray childrenArray = jsonObject[GUIConsts::CHILDREN]->AsArray();
	JSONObject child;
	GuiLayoutData childGuiLayoutData;
	unsigned int childrenArrayLength = childrenArray.size();
	for(unsigned int childrenArrayIndex = 0; childrenArrayIndex < childrenArrayLength; ++ childrenArrayIndex)
	{
		child = childrenArray[childrenArrayIndex]->AsObject();
		childGuiLayoutData = createGuiLayoutDataFromJSONObject(child);

		//add the child to the list of children
		returnGuiLayoutData.children.push_back(childGuiLayoutData);
	}

	return returnGuiLayoutData;
}

BaseGuiWidget *GuiManager::createLayout(std::string fileName)
{
	return createGuiWidget(_guiLayoutDatas[fileName]);
}

BaseGuiWidget *GuiManager::createGuiWidget(GuiLayoutData &guiLayoutData)
{
	BaseGuiWidget *widget;

	switch(guiLayoutData.type)
	{
		case WIDGET_GROUP:
			widget = new BaseGuiWidget(guiLayoutData);
			break;
		case WIDGET_PANEL:
			widget = new BaseSpriteGuiWidget(guiLayoutData);
			break;
		case WIDGET_BUTTON:
			widget = new ButtonGuiWidget(guiLayoutData);
			break;
		case WIDGET_TEXT:
			std::string fontFile = guiLayoutData.properties[GUIConsts::FONT_FILE].asString();

			widget = new TextGuiWidget(guiLayoutData, _fonts[fontFile]);
			break;
	}

	//create and add children
	std::vector<GuiLayoutData>::iterator childrenIterator, childrenBegin, childrenEnd;
	childrenBegin = guiLayoutData.children.begin();
	childrenEnd = guiLayoutData.children.end();
	BaseGuiWidget *child;
	for(childrenIterator = childrenBegin; childrenIterator != childrenEnd; ++ childrenIterator)
	{
		child = createGuiWidget(*childrenIterator);
		widget->addChild(child);
	}

	return widget;
}

std::vector<BaseGuiWidget*> GuiManager::getWidgetsOfType(const WIDGET_TYPE type, BaseGuiWidget *widget)
{
	std::vector<BaseGuiWidget*> widgets;
	getWidgetsOfTypeHelper(type, widget, widgets);
	return widgets;
}

void GuiManager::getWidgetsOfTypeHelper(const WIDGET_TYPE type, BaseGuiWidget *widget, std::vector<BaseGuiWidget*> &widgets)
{
	if(widget != nullptr)
	{
		if(widget->getGuiLayoutData().type == type)
		{
			widgets.push_back(widget);
		}

		std::vector<GameObject*>::iterator childrenIterator, childrenBegin, childrenEnd;
		childrenBegin = widget->getGameObjects().begin();
		childrenEnd = widget->getGameObjects().end();
		for(childrenIterator = childrenBegin; childrenIterator != childrenEnd; ++ childrenIterator)
		{
			getWidgetsOfTypeHelper(type, dynamic_cast<BaseGuiWidget*>(*childrenIterator), widgets);
		}
	}
}

BaseGuiWidget* GuiManager::getWidgetWithID(std::string id, BaseGuiWidget *widget)
{
	if(widget != nullptr)
	{
		if(widget->getGuiLayoutData().id == id)
		{
			return widget;
		}

		BaseGuiWidget* childWidget;
		std::vector<GameObject*>::iterator childrenIterator, childrenBegin, childrenEnd;
		childrenBegin = widget->getGameObjects().begin();
		childrenEnd = widget->getGameObjects().end();
		for(childrenIterator = childrenBegin; childrenIterator != childrenEnd; ++ childrenIterator)
		{
			childWidget = dynamic_cast<BaseGuiWidget*>(*childrenIterator);
			if(childWidget)
			{
				widget = getWidgetWithID(id, childWidget);
				if(widget)
				{
					return widget;
				}
			}
		}
	}

	return nullptr;
}

void GuiManager::addBitmapFont(std::string fontFile, std::string bitmapFontImageFile, std::string textureAtlasName)
{
	BitmapFont font;
	font.create(fontFile, bitmapFontImageFile, textureAtlasName);
	_fonts[fontFile] = font;
}

void GuiManager::removeBitmapFont(std::string fontFile)
{
	_fonts.erase(fontFile);
}

BitmapFont &GuiManager::getBitmapFont(std::string fontFile)
{
	return _fonts[fontFile];
}