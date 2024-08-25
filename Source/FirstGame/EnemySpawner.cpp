#include "EnemySpawner.h"


AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	WaveEnemyCounts = { 1, 3, 5, 10 };// 初始化每波敌人的数量
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetBoxExtent(FVector(500.0f, 500.0f, 10.0f)); // 初始化生成区域的大小
	RootComponent = SpawnArea;
	CurrentWaveIndex = 0;
	EnemiesRemaining = 0;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnWave();
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//检测当前场景中的敌人数量
	EnemiesRemaining = GetNumberOfGameEnemies();
	if (EnemiesRemaining <= 0)
	{
		CurrentWaveIndex++;
		SpawnWave();
	}
}
void AEnemySpawner::SpawnEnemies(int32 EnemyCount)
{
	if (EnemyClass && SpawnArea)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		FVector Origin = SpawnArea->GetComponentLocation();
		FVector Extent = SpawnArea->GetScaledBoxExtent();
		FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
		AGameEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AGameEnemy>(EnemyClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
		if (!SpawnedEnemy->GetController()){
			SpawnedEnemy->SpawnDefaultController();
		}
	}
}

void AEnemySpawner::SpawnWave()
{
	if (CurrentWaveIndex < WaveEnemyCounts.Num())
	{
		int32 EnemyCount = WaveEnemyCounts[CurrentWaveIndex];
		EnemiesRemaining = EnemyCount;
		UE_LOG(LogTemp, Warning, TEXT("Spawning wave %d with %d enemies"), CurrentWaveIndex + 1, EnemyCount);
		for (int32 i = 0; i < EnemyCount; ++i)
		{
			SpawnEnemies(EnemyCount);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("All waves completed"));
	}
}

int32 AEnemySpawner::GetNumberOfGameEnemies() const
{
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameEnemy::StaticClass(), FoundEnemies);
	return FoundEnemies.Num();
}


