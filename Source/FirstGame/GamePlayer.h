#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GamePlayer.generated.h"

UCLASS()
class FIRSTGAME_API AGamePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AGamePlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

	void MoveFB(float Value);
	void MoveLR(float Value);
	void RotateYaw(float Value);

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.0f;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 1.0f;
};
