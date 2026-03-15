// Copyright Epic Games, Inc. All Rights Reserved.

#include "Interactions/FPSInteractionComponent.h"
#include "Characters/FPSCharacter.h"
#include "Weapons/FPSWeapon.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

UFPSInteractionComponent::UFPSInteractionComponent()
{
    // 设置此组件每帧调用 TickComponent()
    PrimaryComponentTick.bCanEverTick = true;

    // 初始化交互参数
    InteractionDistance = 200.f;
    InteractionRadius = 50.f;
    CurrentInteractable = nullptr;
}

void UFPSInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UFPSInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // 每帧检查可交互对象
    CheckForInteractables();
}

void UFPSInteractionComponent::Interact()
{
    if (CurrentInteractable)
    {
        // 执行交互逻辑
        UE_LOG(LogTemp, Log, TEXT("Interacting with: %s"), *CurrentInteractable->GetName());

        // 检查是否是武器
        AFPSWeapon* Weapon = Cast<AFPSWeapon>(CurrentInteractable);
        if (Weapon)
        {
            // 获取角色
            AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
            if (Character)
            {
                // 拾取武器
                Character->EquipWeapon(Weapon);
                UE_LOG(LogTemp, Log, TEXT("Weapon picked up: %s"), *Weapon->GetName());
            }
        }
        
        // 交互后清除当前可交互对象
        CurrentInteractable = nullptr;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("No interactable object in range"));
    }
}

void UFPSInteractionComponent::CheckForInteractables()
{
    AFPSCharacter* Character = Cast<AFPSCharacter>(GetOwner());
    if (!Character)
    {
        return;
    }

    // 获取相机位置和方向
    UCameraComponent* Camera = Character->GetFirstPersonCameraComponent();
    if (!Camera)
    {
        return;
    }

    FVector CameraLocation = Camera->GetComponentLocation();
    FVector CameraForward = Camera->GetForwardVector();
    FVector EndLocation = CameraLocation + (CameraForward * InteractionDistance);

    // 使用球形射线检测来查找可交互对象
    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(InteractionRadius);
    TArray<FHitResult> HitResults;

    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults,
        CameraLocation,
        EndLocation,
        FQuat::Identity,
        ECC_Visibility,
        CollisionShape
    );

    // 调试可视化（已关闭）
    //#if ENABLE_DRAW_DEBUG
    //DrawDebugLine(GetWorld(), CameraLocation, EndLocation, FColor::Blue, false, 0.1f, 0, 1.f);
    //DrawDebugSphere(GetWorld(), EndLocation, InteractionRadius, 12, FColor::Blue, false, 0.1f);
    //#endif

    // 查找第一个可交互的Actor
    AActor* NewInteractable = nullptr;
    if (bHit)
    {
        for (const FHitResult& Hit : HitResults)
        {
            AActor* HitActor = Hit.GetActor();
            if (HitActor && HitActor != GetOwner())
            {
                // 检查是否是角色当前持有的武器，如果是则忽略
                AFPSWeapon* CurrentWeapon = Character->GetCurrentWeapon();
                if (CurrentWeapon && HitActor == CurrentWeapon)
                {
                    continue;
                }
                
                // 检查是否是已被其他角色持有的武器，如果是则忽略
                AFPSWeapon* HitWeapon = Cast<AFPSWeapon>(HitActor);
                if (HitWeapon && HitWeapon->GetOwningCharacter())
                {
                    continue;
                }
                
                // 检查Actor是否有交互标签或接口
                // 这里简化处理，任何非所有者Actor都可交互
                NewInteractable = HitActor;

                // 调试命中点（已关闭）
                //#if ENABLE_DRAW_DEBUG
                //DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 10.f, FColor::Yellow, false, 0.1f);
                //#endif

                break;
            }
        }
    }

    // 更新当前可交互对象
    if (NewInteractable != CurrentInteractable)
    {
        CurrentInteractable = NewInteractable;

        if (CurrentInteractable)
        {
            UE_LOG(LogTemp, Log, TEXT("Found interactable: %s"), *CurrentInteractable->GetName());
        }
    }
}
