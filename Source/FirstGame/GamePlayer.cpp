#include "GamePlayer.h"
#include "GameEnemy.h"
#include "MyHUD.h"
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
	CurrentHealth = MaxHealth;
	bIsCharacterDead = false;
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

/*ÒÆ¶¯*/
void AGamePlayer::MoveForward(float Value)
{
	if (Controller && Value != 0.0f&& !bIsCharacterDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGamePlayer::MoveRight(float Value)
{
	if (Controller && Value != 0.0f&& !bIsCharacterDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AGamePlayer::RotateYaw(float Value)
{
	if (Controller && Value != 0.0f && !bIsCharacterDead){
		AddControllerYawInput(Value * RotationSpeed);
	}
}

void AGamePlayer::RotatePitch(float Value)
{
	if (Controller && Value != 0.0f && !bIsCharacterDead) {
		AddControllerPitchInput(Value * RotationSpeed);
	}
}

/*¹¥»÷*/
void AGamePlayer::Attack()
{
	if (CanAttack && AttackMontage&& !bIsCharacterDead){
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
	FVector End = Start + ArrowComponent->GetForwardVector() * 100.0f;
	TArray<FHitResult> HitResults;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(25.0f);
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
					Enemy->TakeDamage(Damage, DamageEvent, GetController(), this);
					DamagedActors.Add(HitActor);
				}
			}
		}
	}
	DamagedActors.Empty();
}


/*ÊÜ»÷*/
float AGamePlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHealth -= DamageAmount;
	float HealthPercent = FMath::Clamp(CurrentHealth / MaxHealth, 0.0f, 1.0f);
	AMyHUD* HUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD&& !bIsCharacterDead)
	{
		HUD->ShowDamageEffect();
		HUD->UpdateHealth(HealthPercent);
	}

	UE_LOG(LogTemp, Warning, TEXT("Player Health: %f"), CurrentHealth);
	if (CurrentHealth <= 0.0f)
	{
		PlayerDie();
	}
	else {
		if (DamageCauser)
		{
			FVector KnockbackDirection = (GetActorLocation() - DamageCauser->GetActorLocation()).GetSafeNormal();
			ApplyKnockback(KnockbackDirection, 1000.0f);
		}
	}
	return DamageAmount;
}

void AGamePlayer::PlayerDie()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	bIsCharacterDead = true;
}

void AGamePlayer::ApplyKnockback(const FVector& KnockbackDirection, float KnockbackStrength)
{
	if (GetCharacterMovement())
	{
		FVector KnockbackImpulse = KnockbackDirection * KnockbackStrength;
		GetCharacterMovement()->AddImpulse(KnockbackImpulse, true);
	}
}





