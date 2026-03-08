// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeapon.generated.h"

class UPointLightComponent;
class UParticleSystemComponent;

/**
 * FPS武器基类
 * 实现基础射击、弹药管理和伤害计算
 */
UCLASS()
class FPSDEMO_API AFPSWeapon : public AActor
{
    GENERATED_BODY()

public:
    AFPSWeapon();

protected:
    virtual void BeginPlay() override;

public:
    // 每帧调用
    virtual void Tick(float DeltaTime) override;

    // 射击
    UFUNCTION(BlueprintCallable, Category = "FPS Weapon")
    void Fire();

    // 换弹
    UFUNCTION(BlueprintCallable, Category = "FPS Weapon")
    void Reload();

    // 补充弹药（拾取弹药包用）
    UFUNCTION(BlueprintCallable, Category = "FPS Weapon")
    void AddAmmo(int32 AmmoAmount);

    // 检查是否可以射击
    UFUNCTION(BlueprintPure, Category = "FPS Weapon")
    bool CanFire() const;

    // 获取当前弹药
    UFUNCTION(BlueprintPure, Category = "FPS Weapon")
    int32 GetCurrentAmmo() const { return CurrentAmmo; }

    // 获取最大弹药
    UFUNCTION(BlueprintPure, Category = "FPS Weapon")
    int32 GetMaxAmmo() const { return MaxAmmo; }

protected:
    // 执行射线检测射击
    void PerformLineTrace();

    // 应用伤害
    void ApplyDamage(AActor* HitActor, const FHitResult& HitResult);

    // 播放射击效果
    void PlayFireEffects();

    // 播放屏幕震动
    void PlayCameraShake();

    // 消耗弹药
    void ConsumeAmmo();

protected:
    /** 武器伤害值 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Weapon Stats")
    float Damage;

    /** 射速（每秒射击次数） */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Weapon Stats")
    float FireRate;

    /** 射程 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Weapon Stats")
    float Range;

    /** 当前弹药 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Weapon Ammo")
    int32 CurrentAmmo;

    /** 弹匣容量 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Weapon Ammo")
    int32 MaxAmmo;

    /** 枪口位置 */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FPS Weapon")
    TObjectPtr<USceneComponent> MuzzleLocation;

    /** 枪口闪光光源 */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FPS Weapon Effects")
    TObjectPtr<UPointLightComponent> MuzzleFlashLight;

    /** 上次射击时间 */
    float LastFireTime;

    /** 射击冷却时间 */
    float FireCooldown;

public:
    // 设置武器持有者
    UFUNCTION(BlueprintCallable, Category = "FPS Weapon")
    void SetOwningCharacter(class AFPSCharacter* Character) { OwningCharacter = Character; }

protected:
    /** 武器持有者 */
    UPROPERTY(BlueprintReadOnly, Category = "FPS Weapon")
    TObjectPtr<AFPSCharacter> OwningCharacter;
};
