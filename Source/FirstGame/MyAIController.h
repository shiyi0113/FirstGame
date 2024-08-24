#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

UCLASS()
class FIRSTGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	void MoveToTarget(AActor* Target);
};
