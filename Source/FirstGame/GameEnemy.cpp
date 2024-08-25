#include "GameEnemy.h"

AGameEnemy::AGameEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	AttackRangeArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("AttackRangeArrow"));
	AttackRangeArrow->SetupAttachment(RootComponent);
}

void AGameEnemy::BeginPlay()
{
	Super::BeginPlay();
	TargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

}

void AGameEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetActor)
	{
		MoveToTarget();
		PerformAttack();
	}
}

void AGameEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*ÊÜ»÷*/
float AGameEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Enemy Health: %f"), Health);
	if (Health <= 0.0f)
	{
		EnemyDie();
	}
	else {
		if (DamageCauser)
		{
			FVector KnockbackDirection = (GetActorLocation() - DamageCauser->GetActorLocation()).GetSafeNormal();
			ApplyKnockback(KnockbackDirection, 2000.0f); 
		}
	}
	return DamageAmount;
}

void AGameEnemy::EnemyDie()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	SetLifeSpan(3.0f);
}

void AGameEnemy::ApplyKnockback(const FVector& KnockbackDirection, float KnockbackStrength)
{
	if (GetCharacterMovement())
	{
		FVector KnockbackImpulse = KnockbackDirection * KnockbackStrength;
		GetCharacterMovement()->AddImpulse(KnockbackImpulse, true);
	}
}


/*¹¥»÷*/
void AGameEnemy::Attack()
{
    if (CanAttack && AttackMontage) {
        PlayAnimMontage(AttackMontage);
        CanAttack = false;
        FOnMontageEnded MontageEndedDelegate;
        MontageEndedDelegate.BindUObject(this, &AGameEnemy::OnAttackMontageEnded);
        GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, AttackMontage);
    }
}

void AGameEnemy::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (Montage == AttackMontage) {
        CanAttack = true;
    }
}

void AGameEnemy::PerformAttack()
{
	// ¼ì²éµÐÈËÊÇ·ñÔÚ¹¥»÷·¶Î§ÄÚ
	FVector Start = AttackRangeArrow->GetComponentLocation();
	FVector End = Start + AttackRangeArrow->GetForwardVector() * 100.0f; // ¼ÙÉè¹¥»÷·¶Î§Îª200
	TArray<FHitResult> HitResults;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(25.0f); // ¼ÙÉè¹¥»÷·¶Î§°ë¾¶Îª50

	bool bHit = GetWorld()->SweepMultiByObjectType(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		CollisionShape
	);

	if (bHit && !bIsAttacking && Health>0)
	{
		for (auto& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor == TargetActor)
			{
				AttackTarget();
				break; // ÕÒµ½Ö÷½ÇºóÍË³öÑ­»·
			}
		}
	}
}

void AGameEnemy::MoveToTarget()
{
	if (AAIController* AIController = Cast<AAIController>(GetController())){
		if (TargetActor){
			AIController->MoveToActor(TargetActor, 5.0f, true, true, true, 0, true);
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("TargetActor is null"));
		}
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("AIController is null"));
	}
}

void AGameEnemy::AttackTarget()
{
	if (AGamePlayer* Player = Cast<AGamePlayer>(TargetActor))
	{
		bIsAttacking = true;
		FDamageEvent DamageEvent;
		Player->TakeDamage(Damage, DamageEvent, GetController(), this);
		Attack();                // ²¥·Å¹¥»÷¶¯»­
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AGameEnemy::ResetAttack, 1.0f, false);
	}
}

void AGameEnemy::ResetAttack()
{
	bIsAttacking = false;
}
