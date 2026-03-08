// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactions/FPSHealthComponent.h"
#include "Interactions/FPSInteractionComponent.h"
#include "Weapons/FPSWeapon.h"

AFPSCharacter::AFPSCharacter()
{
    // 设置角色胶囊体大小
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    // 设置旋转
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;

    // 配置角色移动
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // 创建第一人称相机组件
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    // 创建第一人称手臂网格
    Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
    Mesh1P->SetOnlyOwnerSee(true);
    Mesh1P->SetupAttachment(FirstPersonCameraComponent);
    Mesh1P->bCastDynamicShadow = false;
    Mesh1P->CastShadow = false;
    Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

    // 创建生命值组件
    HealthComponent = CreateDefaultSubobject<UFPSHealthComponent>(TEXT("HealthComponent"));

    // 创建交互组件
    InteractionComponent = CreateDefaultSubobject<UFPSInteractionComponent>(TEXT("InteractionComponent"));

    // 初始化状态
    bIsDead = false;
    CurrentWeapon = nullptr;
    DefaultWeaponClass = nullptr;
}

void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 隐藏鼠标光标
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        PlayerController->bShowMouseCursor = false;
    }

    // 生成默认武器
    SpawnDefaultWeapon();
}

void AFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFPSCharacter::MoveForward(float Value)
{
    if (Value != 0.0f && Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AFPSCharacter::MoveRight(float Value)
{
    if (Value != 0.0f && Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AFPSCharacter::StartJump()
{
    Jump();
}

void AFPSCharacter::StopJump()
{
    StopJumping();
}

void AFPSCharacter::FireWeapon()
{
    if (CurrentWeapon && !bIsDead)
    {
        CurrentWeapon->Fire();
    }
}

void AFPSCharacter::ReloadWeapon()
{
    if (CurrentWeapon && !bIsDead)
    {
        CurrentWeapon->Reload();
    }
}

void AFPSCharacter::Interact()
{
    if (InteractionComponent)
    {
        InteractionComponent->Interact();
    }
}

void AFPSCharacter::TakeDamage(float DamageAmount)
{
    if (bIsDead || DamageAmount <= 0.0f)
    {
        return;
    }

    if (HealthComponent)
    {
        HealthComponent->TakeDamage(DamageAmount);
    }
}

void AFPSCharacter::Die()
{
    if (bIsDead)
    {
        return;
    }

    bIsDead = true;
    DisableInput(Cast<APlayerController>(Controller));

    UE_LOG(LogTemp, Log, TEXT("Character died"));
}

void AFPSCharacter::Respawn()
{
    bIsDead = false;
    EnableInput(Cast<APlayerController>(Controller));

    if (HealthComponent)
    {
        HealthComponent->Respawn();
    }

    UE_LOG(LogTemp, Log, TEXT("Character respawned"));
}

void AFPSCharacter::SpawnDefaultWeapon()
{
    if (!DefaultWeaponClass)
    {
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    CurrentWeapon = GetWorld()->SpawnActor<AFPSWeapon>(DefaultWeaponClass, SpawnParams);
    if (CurrentWeapon)
    {
        CurrentWeapon->SetOwningCharacter(this);
        // 将武器附加到 Mesh1P 的 WeaponSocket（在 ik_hand_r 上创建的插槽）
        CurrentWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
    }
}
