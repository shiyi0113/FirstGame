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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;  //受伤函数
protected:
	virtual void BeginPlay() override;

private://变量
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 20.0f;  //最大生命值
	float CurrentHealth;         //当前生命值
	bool CanAttack = true; //控制动画播放
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;     //攻击动画蒙太奇
	AActor* TargetActor;      //主角
	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;     //伤害
	UArrowComponent* AttackRangeArrow; //箭头组件
	bool bIsAttacking = false;  //防止重复攻击
	FTimerHandle AttackTimerHandle; 

private://函数
	void EnemyDie();   //死亡处理
	void ApplyKnockback(const FVector& KnockbackDirection, float KnockbackStrength); //未死亡击退效果
	void PerformAttack();   //攻击总函数
	void MoveToTarget();    //跟踪主角
	void AttackTarget();    //攻击效果
	void ResetAttack();     //防止重复攻击
	void Attack();          //攻击动画
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);  //播放完攻击动画才能再播放

};
