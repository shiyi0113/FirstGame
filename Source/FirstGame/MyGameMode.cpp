#include "MyGameMode.h"
#include "MyHUD.h"


void AMyGameMode::InitGameState()
{
	Super::InitGameState();
	if (DefaultPawnClass == ADefaultPawn::StaticClass()||!DefaultPawnClass) {
		DefaultPawnClass = CustomCharacterClass;
	}
	HUDClass = AMyHUD::StaticClass();
}