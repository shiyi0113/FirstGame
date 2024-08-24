#include "GamePlayer.h"

AGamePlayer::AGamePlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraArm->SetupAttachment(RootComponent);
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

	CameraArm->TargetArmLength = 300.0f;      // µ¯»É±ÛµÄ³¤¶È
	CameraArm->bUsePawnControlRotation = true;// Ê¹µ¯»É±Û¸úËæ¿ØÖÆÆ÷µÄÐý×ª
	bUseControllerRotationYaw = false;        // ½ûÓÃ¿ØÖÆÆ÷Ðý×ª
}

void AGamePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGamePlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGamePlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("RotateYaw"), this, &AGamePlayer::RotateYaw);
	PlayerInputComponent->BindAxis(TEXT("RotatePitch"), this, &AGamePlayer::RotatePitch);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AGamePlayer::Attack);
}

void AGamePlayer::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGamePlayer::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AGamePlayer::RotateYaw(float Value)
{
	AddControllerYawInput(Value * RotationSpeed);
}

void AGamePlayer::RotatePitch(float Value)
{
	AddControllerPitchInput(Value * RotationSpeed);
}

void AGamePlayer::Attack()
{
	if (CanAttack && AttackMontage){
		PlayAnimMontage(AttackMontage);
		CanAttack = false;
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &AGamePlayer::OnAttackMontageEnded);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, AttackMontage);
	}
}

void AGamePlayer::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == AttackMontage){
		CanAttack = true;
	}
}

void AGamePlayer::PerformAttack()
{
	FVector Start = ArrowComponent->GetComponentLocation();
	FVector End = Start + ArrowComponent->GetForwardVector() * TraceDistance;
	TArray<FHitResult> HitResults;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(TraceRadius);
	/*»æÖÆ¹¥»÷·¶Î§*/
	//DrawDebugSphere(GetWorld(), Start, TraceRadius, 12, FColor::Red, false, 1.0f);
	//DrawDebugSphere(GetWorld(), End, TraceRadius, 12, FColor::Red, false, 1.0f);
	bool bHit = GetWorld()->SweepMultiByObjectType(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		CollisionShape
	);
	if (bHit){
		for (auto& Hit : HitResults){
			AActor* HitActor = Hit.GetActor();
			if (HitActor && !DamagedActors.Contains(HitActor)){
				AGameEnemy* Enemy = Cast<AGameEnemy>(HitActor);
				if (Enemy){
					FDamageEvent DamageEvent;
					Enemy->TakeDamage(DamageAmount, DamageEvent, GetController(), this);
					DamagedActors.Add(HitActor);
				}
			}
		}
	}
	DamagedActors.Empty();
}
