// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
    }

    if (!CollisionComponent)
    {
        // 用球体进行简单的碰撞展示。
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        // 将球体的碰撞配置文件名称设置为"Projectile"。
        CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
        // 组件击中某物时调用的事件。
        CollisionComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
        // 设置球体的碰撞半径。
        CollisionComponent->InitSphereRadius(15.0f);
        // 将根组件设置为碰撞组件。
        RootComponent = CollisionComponent;
        CollisionComponent->SetSimulatePhysics(true);
    }

    if (!ProjectileMovementComponent)
    {
        // 使用此组件驱动发射物的移动。
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        ProjectileMovementComponent->InitialSpeed = ProjectileSpeed;
        ProjectileMovementComponent->MaxSpeed = ProjectileSpeed;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }

    //if (!ProjectileMeshComponent)
    //{
    //    ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
    //    ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Sphere.Sphere'"));
    //    if (Mesh.Succeeded())
    //    {
    //        ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
    //    }

    //    ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/SphereMaterial.SphereMaterial'"));
    //    if (Material.Succeeded())
    //    {
    //        ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
    //    }
    //    ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
    //    ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
    //    ProjectileMeshComponent->SetupAttachment(RootComponent);
    //}

    // 3 秒后删除发射物。
    InitialLifeSpan = 3.0f;

    //this->DisableComponentsSimulatePhysics();
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    //if (AEnemy* enemy = Cast<AEnemy>(OtherActor)) {
    //    
    //    enemy->Health -= 0.3f;
    //    if (enemy->Health <= 0.001f)
    //    {
    //        enemy->OnDeath();
    //    }
    //    Destroy();
    //}
}

// 初始化射击方向上发射物速度的函数。
void ABaseProjectile::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
    {
        OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
    }
//    Destroy();
}
