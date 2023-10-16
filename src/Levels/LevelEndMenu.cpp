#include "LevelEndMenu.h"
#include "../BobbingGameObject.h"
#include "../TextObject.h"
#include "../NextLevelButton.h"

void core::levels::LevelEndMenu::LoadLevel()
{
	auto bobbingGoPtr=GameObject::AddGameObjectToRoot<BobbingGameObject>(BobbingGameObject(-6,8,50));
	auto title1Ptr=bobbingGoPtr->AddChild<TextObject>(TextObject(Drawable::RED,1,1.0f));
	title1Ptr->SetText("Congratulations !");
	title1Ptr->SetLocalPosition({ 0,0 });
	title1Ptr->SetLocalScale({ 4,4 });
	bobbingGoPtr->SetLocalPosition({ WIDTH / 4, 23});

	auto button1Ptr = GameObject::AddGameObjectToRoot<NextLevelButton>(NextLevelButton(Vector2(130, 20), Drawable::Color::WHITE, Drawable::LIGHTER_WHITE, Drawable::GRAY, Drawable::Color::BLACK, true, UIRect::BackgroundFill));
	button1Ptr->SetLocalPosition({ WIDTH/4,65 });
	auto playText=button1Ptr->AddChild<TextObject>(TextObject(Drawable::Color::BLACK, 1, 1));
	playText->SetText("Main menu");
	playText->SetLocalPosition({ 0,0 });
	playText->SetLocalScale({ 6,6 });

	//Credits texts
	auto creditsText1Ptr = GameObject::AddGameObjectToRoot<TextObject>(TextObject(Drawable::Color::WHITE, 1, 1));
	creditsText1Ptr->SetText("You've reached the");
	creditsText1Ptr->SetLocalPosition({ WIDTH / 4,68+30 });
	creditsText1Ptr->SetLocalScale({ 4,4 });
	auto creditsText2Ptr = GameObject::AddGameObjectToRoot<TextObject>(TextObject(Drawable::Color::WHITE, 1, 1));
	creditsText2Ptr->SetText("end of the game !");
	creditsText2Ptr->SetLocalPosition({ WIDTH / 4,68+30+13 });
	creditsText2Ptr->SetLocalScale({ 4,4 });
}
