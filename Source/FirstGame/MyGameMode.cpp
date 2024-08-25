#include "MyGameMode.h"



void AMyGameMode::InitGameState()
{
	Super::InitGameState();
	if (DefaultPawnClass == ADefaultPawn::StaticClass()||!DefaultPawnClass) {
		DefaultPawnClass = CustomCharacterClass;
	}
}