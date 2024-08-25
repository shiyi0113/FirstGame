#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameEnemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "EnemySpawner.generated.h"

UCLASS()
class FIRSTGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
public:	
	AEnemySpawner();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawning")
    TSubclassOf<class AGameEnemy> EnemyClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawning")
    TArray<int32> WaveEnemyCounts;
    UBoxComponent* SpawnArea;
    
private:
    int32 CurrentWaveIndex;
    int32 EnemiesRemaining;
    void SpawnWave();
    void SpawnEnemies(int32 EnemyCount);
    int32 GetNumberOfGameEnemies() const;
};
