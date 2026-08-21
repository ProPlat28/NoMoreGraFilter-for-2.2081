#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
class $modify(CreatorLayer) {

	bool init() {

		if (!CreatorLayer::init()) {
			return false;
		};

		// Get the menu.
		auto menu = this->getChildByID("creator-buttons-menu");

		// Get the correct scale for the resolution.
		//auto scaleToUse = getChildOfType<CCSprite>(getChildOfType<CCMenuItemSpriteExtra>(menu, 0), 0)->getScale();

		// Create the sprites for the buttons.
		auto sprmap = CCSprite::createWithSpriteFrameName("GJ_mapBtn_001.png");
		auto sprvers = CCSprite::createWithSpriteFrameName("GJ_versusBtn_001.png");

		// Create a map to associate an ID with its new sprite.
		std::map<std::string, CCSprite*> idsToBtns = {
			{ "map-button", sprmap },
			{ "versus-button", sprvers }
		};
		
		// Iterate on the map to change the sprite of the buttons.
		for (auto pair = idsToBtns.begin(); pair != idsToBtns.end(); pair++) {
			auto id = pair->first.c_str();
			auto superExpertLoaded = ((strcmp("versus-button", id) == 0) && (Loader::get()->isModLoaded("xanii.super_expert")));

			if (!menu->getChildByID(id)) continue; // Avoid crash if child not found.

			auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID(id));
			auto contentSize = btn->getContentSize();
			auto existingSprite = btn->getChildByType<CCSprite*>(0);

			if (!existingSprite) continue; // Better safe than sorry.

			auto scale = existingSprite->getScale();
			pair->second->setScale(scale);

			if (!superExpertLoaded) {
				btn->setNormalImage(pair->second);
			};

			btn->setContentSize(contentSize);

		};

		return true;
	};
};