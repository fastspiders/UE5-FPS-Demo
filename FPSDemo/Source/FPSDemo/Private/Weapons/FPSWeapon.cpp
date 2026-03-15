// Copyright Epic Games, Inc. All Rights Reserved.

#include "Weapons/FPSWeapon.h"
#include "Characters/FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AFPSWeapon::AFPSWeapon()
{
    // 设置此 actor 每帧调用 Tick()
    PrimaryActorTick.bCanEverTick = true;

    // 创建根组件
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // 创建枪口位置组件
    MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    MuzzleLocation->SetupAttachment(RootComponent);
    MuzzleLocation->SetRelativeLocation(FVector(100.f, 0.f, 10.f));

    // 创建枪口闪光光源
    MuzzleFlashLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("MuzzleFlashLight"));
    MuzzleFlashLight->SetupAttachment(MuzzleLocation);
    MuzzleFlashLight->SetVisibility(false);
    MuzzleFlashLight->SetLightColor(FLinearColor(1.f, 0.8f, 0.4f));
    MuzzleFlashLight->SetIntensity(5000.f);
    MuzzleFlashLight->SetAttenuationRadius(200.f);

    // 初始化武器属性
    Damage = 25.f;
    FireRate = 10.f; // 每秒10发
    Range = 10000.f;
    MaxAmmo = 30;
    CurrentAmmo = MaxAmmo;
    LastFireTime = 0.f;
    FireCooldown = 1.f / FireRate;

    OwningCharacter = nullptr;
}

void AFPSWeapon::BeginPlay()
{
    Super::BeginPlay();

    // 确保枪口闪光初始不可见
    if (MuzzleFlashLight)
    {
        MuzzleFlashLight->SetVisibility(false);
    }
}

void AFPSWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 枪口闪光自动关闭
    if (MuzzleFlashLight && MuzzleFlashLight->IsVisible())
    {
        // 闪烁效果
        float TimeSinceFire = GetWorld()->GetTimeSeconds() - LastFireTime;
        if (TimeSinceFire > 0.05f)
        {
            MuzzleFlashLight->SetVisibility(false);
        }
    }
}

void AFPSWeapon::Fire()
{
    if (!CanFire())
    {
        return;
    }

    // 更新射击时间
    LastFireTime = GetWorld()->GetTimeSeconds();

    // 消耗弹药
    ConsumeAmmo();

    // 执行射线检测
    PerformLineTrace();

    // 播放射击效果
    PlayFireEffects();

    // 播放屏幕震动
    PlayCameraShake();

    UE_LOG(LogTemp, Log, TEXT("Weapon fired! Ammo remaining: %d"), CurrentAmmo);
}

void AFPSWeapon::Reload()
{
    if (CurrentAmmo < MaxAmmo)
    {
        CurrentAmmo = MaxAmmo;
        UE_LOG(LogTemp, Log, TEXT("Weapon reloaded! Ammo: %d/%d"), CurrentAmmo, MaxAmmo);
        
        // 触发弹药变化事件
        OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
    }
}

void AFPSWeapon::AddAmmo(int32 AmmoAmount)
{
    if (AmmoAmount <= 0)
    {
        return;
    }

    int32 OldAmmo = CurrentAmmo;
    CurrentAmmo = FMath::Min(CurrentAmmo + AmmoAmount, MaxAmmo);
    
    UE_LOG(LogTemp, Log, TEXT("Weapon ammo added: %d -> %d (+%d)"), 
           OldAmmo, CurrentAmmo, AmmoAmount);
    
    // 触发弹药变化事件
    OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
}

bool AFPSWeapon::CanFire() const
{
    // 检查弹药和冷却时间
    if (CurrentAmmo <= 0)
    {
        return false;
    }

    float TimeSinceLastFire = GetWorld()->GetTimeSeconds() - LastFireTime;
    if (TimeSinceLastFire < FireCooldown)
    {
        return false;
    }

    return true;
}

void AFPSWeapon::PerformLineTrace()
{
    if (!OwningCharacter)
    {
        return;
    }

    // 获取相机位置和方向
    UCameraComponent* Camera = OwningCharacter->GetFirstPersonCameraComponent();
    if (!Camera)
    {
        return;
    }

    FVector CameraLocation = Camera->GetComponentLocation();
    FVector CameraForward = Camera->GetForwardVector();
    FVector EndLocation = CameraLocation + (CameraForward * Range);

    // 射线检测参数
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.AddIgnoredActor(OwningCharacter);

    // 执行射线检测
    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        CameraLocation,
        EndLocation,
        ECC_Visibility,
        QueryParams
    );

    if (bHit)
    {
        // 绘制调试线（已注释 - 保持视角干净）
        // DrawDebugLine(GetWorld(), CameraLocation, HitResult.ImpactPoint, FColor::Red, false, 2.f, 0, 1.f);
        // DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 10.f, FColor::Red, false, 2.f);

        // 应用伤害
        ApplyDamage(HitResult.GetActor(), HitResult);

        UE_LOG(LogTemp, Log, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());
    }
    else
    {
        // 未击中，绘制到最大射程的线（已注释 - 保持视角干净）
        // DrawDebugLine(GetWorld(), CameraLocation, EndLocation, FColor::Green, false, 2.f, 0, 1.f);
    }
}

void AFPSWeapon::ApplyDamage(AActor* HitActor, const FHitResult& HitResult)
{
    if (!HitActor)
    {
        return;
    }

    // 对所有 Actor 应用通用伤害，包括角色
    // 这会触发 Actor 的 Event AnyDamage 事件
    AController* InstigatorController = GetInstigatorController();
    UGameplayStatics::ApplyDamage(
        HitActor,
        Damage,
        InstigatorController,
        this,
        nullptr
    );
    
    UE_LOG(LogTemp, Log, TEXT("Hit actor: %s - Damage: %.1f"), *HitActor->GetName(), Damage);
}

void AFPSWeapon::PlayFireEffects()
{
    // 显示枪口闪光
    if (MuzzleFlashLight)
    {
        MuzzleFlashLight->SetVisibility(true);
    }

    // 播放射击音效（占位符）
    // UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
}

void AFPSWeapon::PlayCameraShake()
{
    // 屏幕震动效果
    if (OwningCharacter)
    {
        APlayerController* PlayerController = Cast<APlayerController>(OwningCharacter->GetController());
        if (PlayerController)
        {
            // 使用简单的相机震动
            // PlayerController->ClientStartCameraShake(FireCameraShake);
        }
    }
}

void AFPSWeapon::ConsumeAmmo()
{
    int32 OldAmmo = CurrentAmmo;
    CurrentAmmo = FMath::Max(0, CurrentAmmo - 1);
    
    // 只在弹药实际变化时触发事件
    if (OldAmmo != CurrentAmmo)
    {
        OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
    }
}
