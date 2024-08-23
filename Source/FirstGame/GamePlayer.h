#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpForwardSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpUpwardSpeed;
private:
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* CameraArm;
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateYaw(float Value);
	void RotatePitch(float Value);

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.0f;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 1.0f;



};
