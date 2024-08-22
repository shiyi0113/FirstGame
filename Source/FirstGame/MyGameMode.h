#pragma once

#include "CoreMinimal.h"
#include "GamePlayer.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

UCLASS()
class FIRSTGAME_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void InitGameState() override;
protected:

private:
	UPROPERTY(EditAnywhere,NoClear)
	TSubclassOf<AGamePlayer> CustomCharacterClass = AGamePlayer::StaticClass();
};
