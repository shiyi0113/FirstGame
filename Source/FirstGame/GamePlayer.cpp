#include "GamePlayer.h"

AGamePlayer::AGamePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetCapsuleComponent());
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetCapsuleComponent());
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
	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AGamePlayer::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AGamePlayer::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("RotateYaw"), this, &AGamePlayer::RotateYaw);
}

void AGamePlayer::MoveFB(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
}

void AGamePlayer::MoveLR(float Value)
{
	AddMovementInput(GetActorRightVector(), Value * MoveSpeed);
}

void AGamePlayer::RotateYaw(float Value)
{
	AddControllerYawInput(Value * RotationSpeed);
}
