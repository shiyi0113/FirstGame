#pragma once

#include "CoreMinimal.h"
#include "Engine/Canvas.h"
#include "Engine/World.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class FIRSTGAME_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
    virtual void DrawHUD() override;
    void SetCurrentWave(int32 Wave);
    void SetEnemyCount(int32 Count);
    void ShowDamageEffect();

    void UpdateHealth(float HealthPercent);
private:
    int32 CurrentWave;
    int32 EnemyCount;

    bool bIsTakingDamage = false;
    float DamageEffectDuration = 0.5f;
    float DamageEffectTime;
    float CurrentOpacity = 0.0f;

    float HealthPercentage=1.0f;
};
