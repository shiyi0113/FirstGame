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
 	bool CanAttack = true;
	UPROPERTY(EditAnywhere)
	float DamageAmount = 10.0f;    //�˺�
	float TraceDistance = 200.0f;  //��������
	float TraceRadius = 50.0f;     //�����뾶
	TArray<AActor*> DamagedActors; //�洢�Ѿ��ܻ��ĵ���

private://����
	void MoveForward(float Value);  //ǰ���ƶ�
	void MoveRight(float Value);    //�����ƶ�
	void RotateYaw(float Value);    //X������ת
	void RotatePitch(float Value);  //Y������ת
	void Attack();                  //��������
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);  //�����깥�����������ٲ���
	
};
