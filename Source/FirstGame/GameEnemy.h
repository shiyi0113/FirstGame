#pragma once

#include "GamePlayer.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameEnemy.generated.h"

UCLASS()
class FIRSTGAME_API AGameEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AGameEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;  //���˺���
protected:
	virtual void BeginPlay() override;

private://����
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 20.0f;  //�������ֵ
	float CurrentHealth;         //��ǰ����ֵ
	bool CanAttack = true; //���ƶ�������
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;     //����������̫��
	AActor* TargetActor;      //����
	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;     //�˺�
	UArrowComponent* AttackRangeArrow; //��ͷ���
	bool bIsAttacking = false;  //��ֹ�ظ�����
	FTimerHandle AttackTimerHandle; 

private://����
	void EnemyDie();   //��������
	void ApplyKnockback(const FVector& KnockbackDirection, float KnockbackStrength); //δ��������Ч��
	void PerformAttack();   //�����ܺ���
	void MoveToTarget();    //��������
	void AttackTarget();    //����Ч��
	void ResetAttack();     //��ֹ�ظ�����
	void Attack();          //��������
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);  //�����깥�����������ٲ���

};
