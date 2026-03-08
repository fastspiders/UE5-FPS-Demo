// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

/**
 * FPS生命值组件
 * 管理角色的生命值、受伤和死亡逻辑
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSDEMO_API UFPSHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFPSHealthComponent();

protected:
    virtual void BeginPlay() override;

public:
    // 受到伤害
    UFUNCTION(BlueprintCallable, Category = "FPS Health")
    void TakeDamage(float DamageAmount);

    // 恢复生命值
    UFUNCTION(BlueprintCallable, Category = "FPS Health")
    void Heal(float HealAmount);

    // 死亡处理
    UFUNCTION(BlueprintCallable, Category = "FPS Health")
    void Die();

    // 重生
    UFUNCTION(BlueprintCallable, Category = "FPS Health")
    void Respawn();

    // 获取当前生命值
    UFUNCTION(BlueprintPure, Category = "FPS Health")
    float GetCurrentHealth() const { return CurrentHealth; }

    // 获取最大生命值
    UFUNCTION(BlueprintPure, Category = "FPS Health")
    float GetMaxHealth() const { return MaxHealth; }

    // 获取生命值百分比
    UFUNCTION(BlueprintPure, Category = "FPS Health")
    float GetHealthPercent() const;

    // 是否已死亡
    UFUNCTION(BlueprintPure, Category = "FPS Health")
    bool IsDead() const { return bIsDead; }

    // 是否满血
    UFUNCTION(BlueprintPure, Category = "FPS Health")
    bool IsFullHealth() const { return FMath::IsNearlyEqual(CurrentHealth, MaxHealth); }

public:
    // 生命值变化委托
    UPROPERTY(BlueprintAssignable, Category = "FPS Health Events")
    FOnHealthChanged OnHealthChanged;

    // 死亡委托
    UPROPERTY(BlueprintAssignable, Category = "FPS Health Events")
    FOnDeath OnDeath;

protected:
    /** 最大生命值 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Health")
    float MaxHealth;

    /** 当前生命值 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FPS Health")
    float CurrentHealth;

    /** 是否已死亡 */
    UPROPERTY(BlueprintReadOnly, Category = "FPS Health")
    bool bIsDead;

    // 更新生命值并触发事件
    void UpdateHealth(float NewHealth);
};
