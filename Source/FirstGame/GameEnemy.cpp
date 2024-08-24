#include "GameEnemy.h"

AGameEnemy::AGameEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AGameEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

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
