#pragma once

#include "GamePlayer.h"
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MyAnimNotify.generated.h"


UCLASS()
class FIRSTGAME_API UMyAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
