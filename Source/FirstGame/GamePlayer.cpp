#include "GamePlayer.h"

AGamePlayer::AGamePlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraArm->SetupAttachment(RootComponent);
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	CameraArm->TargetArmLength = 300.0f;      // 弹簧臂的长度
	CameraArm->bUsePawnControlRotation = true;// 使弹簧臂跟随控制器的旋转
	bUseControllerRotationYaw = false;        // 禁用控制器旋转

	JumpForwardSpeed = 300.0f;
	JumpUpwardSpeed = 200.0f;
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
