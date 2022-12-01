// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class ABaseProjectile;
class UAnimMontage;
class ARunAwayGameModeBase;
class ATarget;
class ATargetSpawner;
class UInventoryComponent;

UCLASS()
class RUNAWAY_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void StartJump();
	void StopJump();

	// Fire相关
	UFUNCTION()
	void Fire();

	UFUNCTION()
	void ReduceHealth();

	UFUNCTION()
	void Reload();

	void BeginFire();
	void EndFire();
	FTimerHandle TimerHandleBetweenShot;

	void SetEnableFire(bool);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenShot = 0.243f;

	ARunAwayGameModeBase* GameMode;
	FTimerHandle TimerHandle_GameRestart;

	void RestartLevel();
	void GameRestart();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPCameraComponent;

	// 第一人称网格体（手臂），仅对所属玩家可见。
	UPROPERTY(EditAnywhere, Category = Mesh)
	USkeletalMeshComponent* FPMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	// 枪口相对于摄像机位置的偏移。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	// 要生成的发射物类。
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class ABaseProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UFUNCTION(BlueprintCallable)
		void PrintLog();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int Ammo = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MaxAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Health = 1.0f;

	ATargetSpawner* TargetSpawner;

	//// 背包相关
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	UInventoryComponent* InventoryComponent;

private:
	int cnt = 0;

	bool m_bEnableFire = true;
};
