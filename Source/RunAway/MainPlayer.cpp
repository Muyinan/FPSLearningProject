// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "BaseProjectile.h"
#include "Animation/AnimInstance.h"
#include "RunAwayGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Target.h"
#include "TargetSpawner.h"
#include "AmmoTarget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Inventory/InventoryComponent.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// 创建第一人称摄像机组件。
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	check(FPCameraComponent != nullptr);
	FPCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	// 启用Pawn控制摄像机旋转。
	FPCameraComponent->bUsePawnControlRotation = true;
	FPCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));

	// 为所属玩家创建第一人称网格体组件。
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));
	check(FPMesh != nullptr);
	// 仅所属玩家可以看见此网格体。
	FPMesh->SetOnlyOwnerSee(true);
	// 将 FP 网格体附加到 FP 摄像机。
	FPMesh->SetupAttachment(FPCameraComponent);
	// 禁用某些环境阴影以便实现只有单个网格体的感觉。
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;
	// 所属玩家看不到常规（第三人称）全身网格体。
	GetMesh()->SetOwnerNoSee(true);
	//FPMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	//FPMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
		
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	//check(FP_Gun != nullptr);
	//FP_Gun->SetupAttachment(FPMesh);
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetPlayRate(TimeBetweenShot);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	//this->TakeDamage()
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// 背包
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	// 显示调试消息五秒。 
	// -1"键"值参数可以防止更新或刷新消息。
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	//FP_Gun->AttachToComponent(FPMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	FP_Gun->AttachToComponent(FPMesh, FAttachmentTransformRules(FAttachmentTransformRules::KeepRelativeTransform), TEXT("GripPoint"));

	GameMode = Cast<ARunAwayGameModeBase>(UGameplayStatics::GetGameMode(this));

	TArray<AActor*> targetSpawnerArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetSpawner::StaticClass(), targetSpawnerArray);
	TargetSpawner = Cast<ATargetSpawner>(targetSpawnerArray[0]);

}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Targets.size() is %d"), TargetSpawner->Targets.Num());
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMainPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainPlayer::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainPlayer::StopJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainPlayer::BeginFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMainPlayer::EndFire);
	PlayerInputComponent->BindAction("GetDamage", IE_Pressed, this, &AMainPlayer::ReduceHealth);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMainPlayer::Reload);

	//PlayerInputComponent->BindAction("OpenOrCloseInventory", IE_Pressed, this, &AMainPlayer::OpenOrCloseInventoryWidget);	// 背包开关
}

void AMainPlayer::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AMainPlayer::MoveRight(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AMainPlayer::StartJump()
{
	bPressedJump = true;
}

void AMainPlayer::StopJump()
{
	bPressedJump = false;
}

void AMainPlayer::Fire()
{
	if (ProjectileClass && Ammo > 0)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			Ammo -= 1;

			UAnimInstance* AnimInstance = FPMesh->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation);
			}

			//FP_Gun->Play(false);
			//FP_Gun->PlayAnimation(FP_Gun->getanima, false);

			//// 生成子弹
			//const FRotator SpawnRotation = GetControlRotation();
			//// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			//const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			////Set Spawn Collision Handling Override
			//FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			//// spawn the projectile at the muzzle
			//World->SpawnActor<ABaseProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			
			FVector traceStartLocation = FPCameraComponent->GetComponentLocation();
			FVector traceEndLocation = traceStartLocation + FPCameraComponent->GetForwardVector() * 10000;
			//UE_LOG(LogTemp, Warning, TEXT("FPCameraComponent->GetForwardVector(): %s"), *FPCameraComponent->GetForwardVector().ToString());

			FHitResult fireHitResult;
			if (GetWorld()->LineTraceSingleByChannel(fireHitResult, traceStartLocation, traceEndLocation, ECC_Visibility))
			{
				AAmmoTarget* ammoTarget = Cast<AAmmoTarget>(fireHitResult.Actor);
				if (ammoTarget)
				{
					ammoTarget->SetActorLocation(TargetSpawner->GetSpawnLocation());
					Ammo = UKismetMathLibrary::Clamp(Ammo + ammoTarget->AddAmmoNumber, 0, 30);
				}
				else {
					ATarget* target = Cast<ATarget>(fireHitResult.Actor);
					if (target)
					{
						GameMode->Score += 10 / target->Scale;
						target->ReLoction();
					}
				}
			}
		}
	}
}

void AMainPlayer::ReduceHealth()
{
	Health -= 0.1f;
}

void AMainPlayer::Reload()
{
	Ammo = MaxAmmo;
}

void AMainPlayer::BeginFire()
{
	if (m_bEnableFire) {
		GetWorldTimerManager().SetTimer(TimerHandleBetweenShot, this, &AMainPlayer::Fire, TimeBetweenShot, true, 0.0f);
		FP_Gun->Play(true);
	}
}

void AMainPlayer::EndFire()
{
	if (m_bEnableFire) {
		GetWorldTimerManager().ClearTimer(TimerHandleBetweenShot);
		FP_Gun->Play(false);
	}
}

void AMainPlayer::SetEnableFire(bool enableFire)
{
	m_bEnableFire = enableFire;
}

void AMainPlayer::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, "MainMenuMap");
}

void AMainPlayer::GameRestart()
{
	GetWorldTimerManager().SetTimer(TimerHandle_GameRestart, this, &AMainPlayer::RestartLevel, 1.0f, false, 1.5f);
}

void AMainPlayer::PrintLog()
{
	UE_LOG(LogTemp, Warning, TEXT("PrintLog has been called: %d"), ++cnt);
}