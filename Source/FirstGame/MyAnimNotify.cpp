#include "MyAnimNotify.h"

void UMyAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        AGamePlayer* Character = Cast<AGamePlayer>(MeshComp->GetOwner());
        if (Character)
        {
            Character->PerformAttack();
        }
    }
}
