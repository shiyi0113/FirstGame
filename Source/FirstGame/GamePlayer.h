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
	void PerformAttack();   //��������
	UPROPERTY(EditAnywhere)
	float Health = 100.0f;            //����ֵ
protected:
	virtual void BeginPlay() override;
	
private://����
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* CameraArm;  //���ɱ�
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;  //�����
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;     //��������
	UArrowComponent* ArrowComponent; //��ͷ���


	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.0f;          //�ƶ��ٶ�
	UPROPERTY(EditAnywhere) 
	float RotationSpeed = 1.0f;      //ת���ӽ��ٶ�
	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;      //�˺�

	bool CanAttack = true;
	TArray<AActor*> DamagedActors; //�洢�Ѿ��ܻ��ĵ���

private://����
	void MoveForward(float Value);  //ǰ���ƶ�
	void MoveRight(float Value);    //�����ƶ�
	void RotateYaw(float Value);    //X������ת
	void RotatePitch(float Value);  //Y������ת
	void Attack();                  //��������
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);  //�����깥�����������ٲ���
	void PlayerDie();   //��������
	void ApplyKnockback(const FVector& KnockbackDirection, float KnockbackStrength); //δ��������Ч��
};
