#include "MyAIController.h"

void AMyAIController::MoveToTarget(AActor* Target)
{
    if (Target)
    {
        EPathFollowingRequestResult::Type Result = MoveToActor(Target, 5.0f);
        UE_LOG(LogTemp, Warning, TEXT("MoveToActor Result: %d"), Result);
        //MoveToActor(Target, 5.0f); 
    }
}
