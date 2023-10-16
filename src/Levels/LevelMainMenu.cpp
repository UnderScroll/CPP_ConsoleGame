#include "LevelMainMenu.h"
#include "../BobbingGameObject.h"
#include "../TextObject.h"
#include "../NextLevelButton.h"

void core::levels::LevelMainMenu::LoadLevel()
{
	auto bobbingGoPtr=GameObject::AddGameObjectToRoot<BobbingGameObject>(BobbingGameObject(-6,8,50));
	auto title1Ptr=bobbingGoPtr->AddChild<TextObject>(TextObject(Drawable::RED,1,2));
	title1Ptr->SetText("Lasciier");
	title1Ptr->SetLocalPosition({ 0,-5 });
	title1Ptr->SetLocalScale({ 4,4 });
	auto title2Ptr = bobbingGoPtr->AddChild<TextObject>(TextObject(Drawable::LIGHTER_WHITE, 1, 2));
	title2Ptr->SetText("Attraction");
	title2Ptr->SetLocalPosition({0,5 });
	title2Ptr->SetLocalScale({ 4,4 });

	bobbingGoPtr->SetLocalPosition({ WIDTH / 4, 23});
	bobbingGoPtr->SetLocalScale({ 2,2 });

	auto button1Ptr = GameObject::AddGameObjectToRoot<NextLevelButton>(NextLevelButton(Vector2(80, 20), Drawable::Color::WHITE, Drawable::LIGHTER_WHITE, Drawable::GRAY, Drawable::Color::BLACK, true, UIRect::BackgroundFill));
	button1Ptr->SetLocalPosition({ WIDTH/4,65 });
	auto playText=button1Ptr->AddChild<TextObject>(TextObject(Drawable::Color::BLACK, 1, 1));
	playText->SetText("Play");
	playText->SetLocalPosition({ 0,0 });
	playText->SetLocalScale({ 6,6 });

	//Credits texts
	auto creditsText1Ptr = GameObject::AddGameObjectToRoot<TextObject>(TextObject(Drawable::Color::WHITE, 1, 1));
	creditsText1Ptr->SetText("Game made by");
	creditsText1Ptr->SetLocalPosition({ WIDTH / 4,68+15 });
	creditsText1Ptr->SetLocalScale({ 4,4 });
	auto creditsText2Ptr = GameObject::AddGameObjectToRoot<TextObject>(TextObject(Drawable::Color::WHITE, 1, 1));
	creditsText2Ptr->SetText("Jeremy Loic Auclair");
	creditsText2Ptr->SetLocalPosition({ WIDTH / 4,68+15+13 });
	creditsText2Ptr->SetLocalScale({ 4,4 });
	auto creditsText3Ptr = GameObject::AddGameObjectToRoot<TextObject>(TextObject(Drawable::Color::WHITE, 1, 1));
	creditsText3Ptr->SetText("Fabien Vallet");
	creditsText3Ptr->SetLocalPosition({ WIDTH / 4,68+15+2*13 });
	creditsText3Ptr->SetLocalScale({ 4,4 });
	/*auto creditsText4Ptr = GameObject::AddGameObjectToRoot<TextObject>(TextObject(Drawable::Color::WHITE, 1, 1));
	creditsText4Ptr->SetText("SFX from OpenDoom(BSD3 License)");
	creditsText4Ptr->SetLocalPosition({ WIDTH  /4,68+15+3*13 });
	creditsText4Ptr->SetLocalScale({ 3,3 });*/
}
