# Tasks: 功能实现优先级系统

**Input**: Design documents from `/specs/001-priority-system/`
**Prerequisites**: plan.md (required), spec.md (required for user stories)

**Organization**: Tasks are grouped by user story to enable independent implementation and testing of each story.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3)
- Include exact file paths in descriptions

## Path Conventions

- **UE5 Project**: D:/UElearning/MyAIGame/FPSDemo/
- **Source Code**: D:/UElearning/MyAIGame/FPSDemo/Source/FPSDemo/
- **Content**: D:/UElearning/MyAIGame/FPSDemo/Content/

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: UE5项目初始化和基本结构搭建

- [x] T001 Create UE5 C++ project named FPSDemo in D:/UElearning/MyAIGame/
- [x] T002 Configure FPSDemo.Build.cs with required module dependencies (Engine, InputCore, GameplayTasks)
- [x] T003 [P] Create project directory structure: Source/FPSDemo/{Private,Public}/{Characters,Weapons,Core,Interactions}
- [x] T004 [P] Create Content directory structure: Content/{Maps,Blueprints,Materials}/{Prototype,Characters,Weapons,UI,Prototyping}

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: 核心基础设施，必须在任何用户故事实现前完成

**⚠️ CRITICAL**: No user story work can begin until this phase is complete

- [x] T005 Setup base game mode class FPSGameMode in Source/FPSDemo/Public/Core/FPSGameMode.h
- [x] T006 Implement FPSGameMode in Source/FPSDemo/Private/Core/FPSGameMode.cpp
- [x] T007 [P] Setup player controller class FPSPlayerController in Source/FPSDemo/Public/Core/FPSPlayerController.h
- [x] T008 [P] Implement FPSPlayerController in Source/FPSDemo/Private/Core/FPSPlayerController.cpp
- [x] T009 Configure Enhanced Input system mappings in Source/FPSDemo/Private/Core/FPSPlayerController.cpp
- [x] T010 Create test map TestMap.umap in Content/Maps/Prototype/
- [x] T011 [P] Configure project settings: 60 FPS target, Windows platform, C++17

**Checkpoint**: Foundation ready - user story implementation can now begin in parallel

---

## Phase 3: User Story 1 - 基础移动系统 (Priority: P1) 🎯 MVP

**Goal**: 实现流畅的第一人称角色移动和视角控制

**Independent Test**: 玩家可以通过WASD键移动，鼠标控制视角，空格键跳跃

### Implementation for User Story 1

- [x] T012 [P] [US1] Create FPSCharacter header in Source/FPSDemo/Public/Characters/FPSCharacter.h
- [x] T013 [P] [US1] Create FPSCharacter implementation in Source/FPSDemo/Private/Characters/FPSCharacter.cpp
- [x] T014 [US1] Add UCameraComponent for first-person view in FPSCharacter
- [x] T015 [US1] Add UStaticMeshComponent for first-person arms visualization
- [x] T016 [US1] Implement MoveForward(float Value) function in FPSCharacter
- [x] T017 [US1] Implement MoveRight(float Value) function in FPSCharacter
- [x] T018 [US1] Implement Turn(float Value) function for horizontal camera rotation
- [x] T019 [US1] Implement LookUp(float Value) function for vertical camera pitch
- [x] T020 [US1] Implement StartJump() and StopJump() functions
- [x] T021 [US1] Configure CharacterMovementComponent parameters (speed, acceleration, jump height)
- [x] T022 [US1] Setup input bindings in FPSPlayerController for movement controls
- [x] T023 [US1] Create BP_FPSCharacter blueprint in Content/Blueprints/Characters/
- [x] T024 [US1] Configure BP_FPSCharacter with capsule collision (inherited from C++)
- [x] T025 [US1] Place BP_FPSCharacter in TestMap and configure as player start

**Checkpoint**: At this point, User Story 1 should be fully functional and testable independently

---

## Phase 4: User Story 2 - 射击系统 (Priority: P2)

**Goal**: 实现基础射击机制，包括射线检测、伤害计算和视觉反馈

**Independent Test**: 玩家可以瞄准并射击目标，看到射击反馈效果

### Implementation for User Story 2

- [x] T026 [P] [US2] Create FPSWeapon header in Source/FPSDemo/Public/Weapons/FPSWeapon.h
- [x] T027 [P] [US2] Create FPSWeapon implementation in Source/FPSDemo/Private/Weapons/FPSWeapon.cpp
- [x] T028 [US2] Implement Fire() function with line trace for target detection
- [x] T029 [US2] Add ammo management variables (CurrentAmmo, MaxAmmo) to FPSWeapon
- [x] T030 [US2] Implement CanFire() function with ammo and cooldown checks
- [x] T031 [US2] Add damage calculation and ApplyDamage interface
- [x] T032 [US2] Create TakeDamage interface in FPSCharacter for receiving damage
- [x] T033 [US2] Add muzzle flash effect using point light component
- [x] T034 [US2] Add screen shake camera effect on firing
- [x] T035 [US2] Setup input binding for fire action in FPSPlayerController
- [x] T036 [US2] Create BP_Weapon_Rifle blueprint in Content/Blueprints/Weapons/ ✅ 2026-03-05
- [x] T037 [US2] Create WBP_Crosshair UI widget in Content/Blueprints/UI/ ✅ 2026-03-05
- [x] T038 [US2] Attach weapon to character and configure first-person view ✅ 2026-03-05 (使用 WeaponSocket)
- [x] T039 [US2] Add destructible targets to TestMap for shooting practice ✅ 2026-03-05
  - Created BP_Target blueprint with Event AnyDamage
  - Implemented physics-based knockdown effect
  - Target falls in the direction of the shot using Instigator's forward vector × 500 impulse
- [ ] T040 [US2] Configure weapon pickup and equip mechanics

**Checkpoint**: At this point, User Stories 1 AND 2 should both work independently

---

## Phase 5: User Story 3 - 碰撞与交互系统 (Priority: P3)

**Goal**: 实现物理碰撞、物品拾取、生命值管理和死亡重生机制

**Independent Test**: 角色不能穿过墙壁，可以拾取物品，具有生命值系统

### Implementation for User Story 3

- [x] T041 [P] [US3] Create FPSInteractionComponent header in Source/FPSDemo/Public/Interactions/FPSInteractionComponent.h
- [x] T042 [P] [US3] Create FPSInteractionComponent implementation in Source/FPSDemo/Private/Interactions/FPSInteractionComponent.cpp
- [x] T043 [US3] Implement overlap detection for interactable objects
- [x] T044 [US3] Add pickup functionality with E key binding
- [x] T045 [P] [US3] Create FPSHealthComponent header in Source/FPSDemo/Public/Interactions/FPSHealthComponent.h
- [x] T046 [P] [US3] Create FPSHealthComponent implementation in Source/FPSDemo/Private/Interactions/FPSHealthComponent.cpp
- [x] T047 [US3] Implement TakeDamage(float Damage) function with health reduction
- [x] T048 [US3] Implement Die() function with death state management
- [x] T049 [US3] Add Respawn() function with spawn point logic
- [x] T050 [US3] Configure collision channels (Pawn, Visibility, Camera, WorldDynamic)
- [x] T051 [US3] Create BP_Pickup_Health blueprint in Content/Blueprints/Pickups/ ✅ 2026-03-11
- [x] T052 [US3] Create BP_Pickup_Ammo blueprint in Content/Blueprints/Pickups/ ✅ 2026-03-11
- [x] T053 [US3] Add health/ammo visual indicators to HUD ✅ 2026-03-11
- [ ] T054 [US3] Configure respawn points in TestMap
- [ ] T055 [US3] Add death and respawn sound effects

**Checkpoint**: All user stories should now be independently functional

---

## Phase 6: Polish & Cross-Cutting Concerns

**Purpose**: 系统整合、性能优化和文档完善

- [x] T056 [P] Create quickstart.md documentation with setup and testing instructions
- [x] T057 [P] Add Chinese comments and documentation to all C++ classes
- [ ] T058 Optimize performance: reduce draw calls, profile frame rate
- [ ] T059 [P] Create user manual with control scheme and gameplay instructions
- [ ] T060 Conduct final playtesting and bug fixing
- [ ] T061 [P] Verify Constitution compliance (UE5 standards, Primitive assets, priority enforcement)
- [ ] T062 Package final demo build for Windows platform
- [ ] T063 Create demonstration video showcasing all implemented features

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies - can start immediately
- **Foundational (Phase 2)**: Depends on Setup completion - BLOCKS all user stories
- **User Stories (Phase 3+)**: All depend on Foundational phase completion
  - User stories can then proceed in parallel (if staffed)
  - Or sequentially in priority order (P1 → P2 → P3)
- **Polish (Final Phase)**: Depends on all desired user stories being complete

### User Story Dependencies

- **User Story 1 (P1)**: Can start after Foundational (Phase 2) - No dependencies on other stories
- **User Story 2 (P2)**: Can start after Foundational (Phase 2) - May integrate with US1 but should be independently testable
- **User Story 3 (P3)**: Can start after Foundational (Phase 2) - May integrate with US1/US2 but should be independently testable

### Within Each User Story

- Models before services
- Services before endpoints
- Core implementation before integration
- Story complete before moving to next priority

### Parallel Opportunities

- All Setup tasks marked [P] can run in parallel
- All Foundational tasks marked [P] can run in parallel (within Phase 2)
- Once Foundational phase completes, all user stories can start in parallel (if team capacity allows)
- All header/implementation pairs within a story marked [P] can run in parallel
- Different user stories can be worked on in parallel by different team members

---

## Implementation Strategy

### MVP First (User Story 1 Only)

1. Complete Phase 1: Setup
2. Complete Phase 2: Foundational (CRITICAL - blocks all stories)
3. Complete Phase 3: User Story 1
4. **STOP and VALIDATE**: Test User Story 1 independently
5. Deploy/demo if ready

### Incremental Delivery

1. Complete Setup + Foundational → Foundation ready
2. Add User Story 1 → Test independently → Deploy/Demo (MVP!)
3. Add User Story 2 → Test independently → Deploy/Demo
4. Add User Story 3 → Test independently → Deploy/Demo
5. Each story adds value without breaking previous stories

### Parallel Team Strategy

With multiple developers:

1. Team completes Setup + Foundational together
2. Once Foundational is done:
   - Developer A: User Story 1
   - Developer B: User Story 2
   - Developer C: User Story 3
3. Stories complete and integrate independently

---

## Notes

- [P] tasks = different files, no dependencies
- [Story] label maps task to specific user story for traceability
- Each user story should be independently completable and testable
- Commit after each task or logical group
- Stop at any checkpoint to validate story independently
- Avoid: vague tasks, same file conflicts, cross-story dependencies that break independence
