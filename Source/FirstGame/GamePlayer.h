#pragma once

#include "CoreMinimal.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void PerformAttack();   //攻击函数
	UPROPERTY(EditAnywhere)
	float Health = 100.0f;            //生命值
protected:
	virtual void BeginPlay() override;
	
private://变量
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* CameraArm;  //弹簧臂
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;  //摄像机
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;     //攻击动画
	UArrowComponent* ArrowComponent; //箭头组件


	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.0f;          //移动速度
	UPROPERTY(EditAnywhere) 
	float RotationSpeed = 1.0f;      //转动视角速度
	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;      //伤害

	bool CanAttack = true;
	TArray<AActor*> DamagedActors; //存储已经受击的敌人

private://函数
	void MoveForward(float Value);  //前后移动
	void MoveRight(float Value);    //左右移动
	void RotateYaw(float Value);    //X方向旋转
	void RotatePitch(float Value);  //Y方向旋转
	void Attack();                  //攻击动画
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);  //播放完攻击动画才能再播放
	void PlayerDie();   //死亡处理
	void ApplyKnockback(const FVector& KnockbackDirection, float KnockbackStrength); //未死亡击退效果
};
