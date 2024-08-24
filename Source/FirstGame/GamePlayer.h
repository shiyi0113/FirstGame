#pragma once

#include "CoreMinimal.h"
#include "GameEnemy.h"
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

	void PerformAttack();
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
 	bool CanAttack = true;
	UPROPERTY(EditAnywhere)
	float DamageAmount = 10.0f;    //伤害
	float TraceDistance = 200.0f;  //攻击距离
	float TraceRadius = 50.0f;     //攻击半径
	TArray<AActor*> DamagedActors; //存储已经受击的敌人

private://函数
	void MoveForward(float Value);  //前后移动
	void MoveRight(float Value);    //左右移动
	void RotateYaw(float Value);    //X方向旋转
	void RotatePitch(float Value);  //Y方向旋转
	void Attack();                  //攻击动画
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);  //播放完攻击动画才能再播放
	
};
