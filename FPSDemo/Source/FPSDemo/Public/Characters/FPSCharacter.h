// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class AFPSWeapon;
class UFPSHealthComponent;
class UFPSInteractionComponent;

/**
 * FPS角色类
 * 实现第一人称角色的移动、射击和交互功能
 */
UCLASS()
class FPSDEMO_API AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AFPSCharacter();

protected:
    virtual void BeginPlay() override;

public:
    // 每帧调用
    virtual void Tick(float DeltaTime) override;

    // 输入绑定
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // 移动函数
    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void MoveForward(float Value);

    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void MoveRight(float Value);

    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void StartJump();

    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void StopJump();

    // 武器相关
    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void FireWeapon();

    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void ReloadWeapon();

    // 交互
    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void Interact();

    // 受到伤害
    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void TakeDamage(float DamageAmount);

    // 死亡处理
    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void Die();

    // 重生
    UFUNCTION(BlueprintCallable, Category = "FPS Character")
    void Respawn();

    // 武器生成事件（蓝图调用）
    UFUNCTION(BlueprintImplementableEvent, Category = "FPS Character Events")
    void OnWeaponSpawned(AFPSWeapon* SpawnedWeapon);

protected:
    /** 第一人称相机组件 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FPS Camera")
    TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

    /** 第一人称手臂网格 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FPS Mesh")
    TObjectPtr<USkeletalMeshComponent> Mesh1P;

    /** 当前武器 */
    UPROPERTY(BlueprintReadOnly, Category = "FPS Weapon")
    TObjectPtr<AFPSWeapon> CurrentWeapon;

    /** 默认武器类（在蓝图中配置） */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Weapon")
    TSubclassOf<AFPSWeapon> DefaultWeaponClass;

    /** 生命值组件 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FPS Health")
    TObjectPtr<UFPSHealthComponent> HealthComponent;

    /** 交互组件 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FPS Interaction")
    TObjectPtr<UFPSInteractionComponent> InteractionComponent;

    /** 是否已死亡 */
    UPROPERTY(BlueprintReadOnly, Category = "FPS Character")
    bool bIsDead;

    /** 生成默认武器 */
    void SpawnDefaultWeapon();

public:
    // 获取相机组件
    UFUNCTION(BlueprintPure, Category = "FPS Camera")
    UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

    // 获取手臂网格
    UFUNCTION(BlueprintPure, Category = "FPS Mesh")
    USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

    // 获取当前武器
    UFUNCTION(BlueprintPure, Category = "FPS Weapon")
    AFPSWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

    // 获取生命值组件
    UFUNCTION(BlueprintPure, Category = "FPS Health")
    UFPSHealthComponent* GetHealthComponent() const { return HealthComponent; }

    // 检查是否死亡
    UFUNCTION(BlueprintPure, Category = "FPS Character")
    bool IsDead() const { return bIsDead; }
};
