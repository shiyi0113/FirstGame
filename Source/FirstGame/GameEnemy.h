#pragma once
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameEnemy.generated.h"

UCLASS()
class FIRSTGAME_API AGameEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AGameEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
protected:
	virtual void BeginPlay() override;

private://����
	UPROPERTY(EditDefaultsOnly)
	float Health = 20.0f;  //����ֵ

private://����
	void EnemyDie();   //��������
	void ApplyKnockback(const FVector& KnockbackDirection, float KnockbackStrength); //δ��������Ч��
};
