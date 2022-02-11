#include <fmt/format.h>
#include <dokkan/files.h>
#include <dokkan/instances.h>
#include <unidokkan/ui/defs.h>
#include <unidokkan/ui/label.h>
#include <unidokkan/ui/scene.h>
#include <unidokkan/ui/button.h>
#include <unidokkan/ui/layout.h>
#include <unidokkan/ui/imageview.h>
#include <unidokkan/ui/progresstimer.h>
#include <cocos/ui/UIButton.h>
#include <cocos/base/CCDirector.h>
#include <cocos/2d/CCActionInterval.h>
#include "main.h"
#include <string>
using namespace UniDokkan::UI;
namespace cocos2d = ud_cocos2d; 
void(*ori__TitleScene_onEnter)(void *self)= nullptr;
void TitleScene_onEnter(void *self) {
	UD_LOGI("RerollHook : Init");
    ori__TitleScene_onEnter(self);
	auto screen_size = cocos2d_Director_getVisibleSize(UniDokkan::Dokkan::cocos2d_Director_getInstance());
	UD_LOGI("RerollHook : Setup");
	auto OriW			=	screen_size.width;
	auto OriH			=	screen_size.height;
	float Ypos			=	OriH/2;
	float YposN			=	Ypos;
	float XPos			=	OriW/2;
	float XPosN			=	XPos;
	auto Reroll_now = new Button("Reroll_nowbtn", self, 100);
    Reroll_now->setDefaultImage("layout/image/common/btn/com_btn_menu_chara_gray.png");
    Reroll_now->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
	Reroll_now->setPosition({XPos, Ypos});
    Reroll_now->addClickEventListener([=](Widget*) {
		//auto getuserinstant	=	UniDokkan::Dokkan::cocos2d_UserDefault_getInstance(void *);
		auto xmlfile		=	cocos2d_UserDefault_getInstance.initXMLFilePath;
		auto setXML_bool	=	DokkanFunction<void *(void *,const char *, bool)>("_ZN7cocos2d11UserDefault13setBoolForKeyEPKcb");
		auto setXML_string	=	DokkanFunction<void *(void *,const char *, std::string)>("_ZN7cocos2d11UserDefault15setStringForKeyEPKcRKNSt6__ndk112basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
		auto setXML_int		=	DokkanFunction<void *(void *,const char *, int)>("_ZN7cocos2d11UserDefault16setIntegerForKeyEPKci");
		auto setXML_float	=	DokkanFunction<void *(void *,const char *, float)>("_ZN7cocos2d11UserDefault14setFloatForKeyEPKcf");
		auto setXML_double	=	DokkanFunction<void *(void *,const char *, double)>("_ZN7cocos2d11UserDefault15setDoubleForKeyEPKcd");
		auto delXML_value	=	DokkanFunction<void *(void *,const char *)>("_ZN7cocos2d11UserDefault17deleteValueForKeyEPKc");
		// auto xmlfile	=	initXML();
		setXML_bool(xmlfile, "is_tutee_finished_key", false);
		setXML_bool(xmlfile, "IsLinkedFacebook", false);
		setXML_string(xmlfile, "LocalUserId", "");
		setXML_int(xmlfile, "tutorial_progress_key", 80);
        auto notice_scene = DokkanFunction<void *()>("_ZN15CreateSceneUtil6createI11NoticeSceneJEEEPT_DpOT0_")();

        TransitionFade transition_fade(0.0f, cocos2d::Color3B::BLACK);
        Scene::pushScene(transition_fade.getRef(notice_scene));
    });
}
extern "C" {
	int unidokkan_init_v2(HookLib *hook_lib) {
		auto res = hook_lib->applyHooks({
			{DOKKAN_LIB, "_ZN13HomeMenuScene7onEnterEv", reinterpret_cast<void *>(TitleScene_onEnter), reinterpret_cast<void **>(&ori__TitleScene_onEnter)},
		 });
		if (!res) {
			return 1;
		}
		return 0;
	}
}
