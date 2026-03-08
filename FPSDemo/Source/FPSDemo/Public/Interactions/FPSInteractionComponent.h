// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSInteractionComponent.generated.h"

/**
 * FPS交互组件
 * 处理角色与环境的交互，如拾取物品
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSDEMO_API UFPSInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFPSInteractionComponent();

protected:
    virtual void BeginPlay() override;

public:
    // 每帧调用
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // 执行交互
    UFUNCTION(BlueprintCallable, Category = "FPS Interaction")
    void Interact();

    // 检查可交互对象
    UFUNCTION(BlueprintCallable, Category = "FPS Interaction")
    void CheckForInteractables();

protected:
    /** 交互距离 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Interaction")
    float InteractionDistance;

    /** 交互检测半径 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Interaction")
    float InteractionRadius;

    /** 当前可交互对象 */
    UPROPERTY(BlueprintReadOnly, Category = "FPS Interaction")
    TObjectPtr<AActor> CurrentInteractable;

public:
    // 获取当前可交互对象
    UFUNCTION(BlueprintPure, Category = "FPS Interaction")
    AActor* GetCurrentInteractable() const { return CurrentInteractable; }

    // 是否有可交互对象
    UFUNCTION(BlueprintPure, Category = "FPS Interaction")
    bool HasInteractable() const { return CurrentInteractable != nullptr; }
};
