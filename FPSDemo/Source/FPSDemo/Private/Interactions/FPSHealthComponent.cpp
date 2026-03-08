// Copyright Epic Games, Inc. All Rights Reserved.

#include "Interactions/FPSHealthComponent.h"
#include "Characters/FPSCharacter.h"

UFPSHealthComponent::UFPSHealthComponent()
{
    // 设置此组件每帧不调用 TickComponent()，提高性能
    PrimaryComponentTick.bCanEverTick = false;

    // 初始化生命值
    MaxHealth = 100.f;
    CurrentHealth = MaxHealth;
    bIsDead = false;
}

void UFPSHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    // 确保生命值在有效范围内
    CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

void UFPSHealthComponent::TakeDamage(float DamageAmount)
{
    if (bIsDead || DamageAmount <= 0.f)
    {
        return;
    }

    // 减少生命值
    float NewHealth = CurrentHealth - DamageAmount;
    UpdateHealth(NewHealth);

    UE_LOG(LogTemp, Log, TEXT("Took %f damage, health: %f/%f"), DamageAmount, CurrentHealth, MaxHealth);

    // 检查是否死亡
    if (CurrentHealth <= 0.f)
    {
        Die();
    }
}

void UFPSHealthComponent::Heal(float HealAmount)
{
    if (bIsDead || HealAmount <= 0.f)
    {
        return;
    }

    // 增加生命值
    float NewHealth = CurrentHealth + HealAmount;
    UpdateHealth(NewHealth);

    UE_LOG(LogTemp, Log, TEXT("Healed %f, health: %f/%f"), HealAmount, CurrentHealth, MaxHealth);
}

void UFPSHealthComponent::Die()
{
    if (bIsDead)
    {
        return;
    }

    bIsDead = true;
    CurrentHealth = 0.f;

    // 触发死亡事件
    OnDeath.Broadcast();

    UE_LOG(LogTemp, Log, TEXT("Character died"));

    // 通知角色死亡
    AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
    if (Character)
    {
        Character->Die();
    }
}

void UFPSHealthComponent::Respawn()
{
    bIsDead = false;
    CurrentHealth = MaxHealth;

    // 触发生命值变化事件
    OnHealthChanged.Broadcast(CurrentHealth);

    UE_LOG(LogTemp, Log, TEXT("Character respawned with full health"));

    // 通知角色重生
    AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
    if (Character)
    {
        Character->Respawn();
    }
}

float UFPSHealthComponent::GetHealthPercent() const
{
    if (MaxHealth > 0.f)
    {
        return CurrentHealth / MaxHealth;
    }
    return 0.f;
}

void UFPSHealthComponent::UpdateHealth(float NewHealth)
{
    // 限制生命值在有效范围内
    float OldHealth = CurrentHealth;
    CurrentHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);

    // 只在生命值实际变化时触发事件
    if (!FMath::IsNearlyEqual(OldHealth, CurrentHealth))
    {
        OnHealthChanged.Broadcast(CurrentHealth);
    }
}
