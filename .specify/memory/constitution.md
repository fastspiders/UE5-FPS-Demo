<!--
SYNC IMPACT REPORT
Version Change: N/A → 1.0.0 (Initial Constitution)
Modified Principles: N/A (New Document)
Added Sections: All (Initial Creation)
Removed Sections: N/A
Templates Requiring Updates:
  - ✅ plan-template.md: Updated Constitution Check section to reflect UE5-specific gates
  - ✅ spec-template.md: No changes required (general purpose)
  - ✅ tasks-template.md: No changes required (general purpose)
Follow-up TODOs: None
-->

# UE5 FPS Demo Constitution

## Core Principles

### I. UE5 Standard Project Structure

**Rule**: 项目必须严格遵循UE5标准文件夹结构，按功能模块组织代码和资产。

**Requirements**:
- Source代码目录使用Private/Public分离模式
- Content目录按功能分类（Maps/Blueprints/Materials等）
- 所有C++类必须添加项目前缀（FPS）避免命名冲突
- 蓝图资产使用标准前缀（BP_/WBP_/MI_等）

**Rationale**: 标准化的项目结构确保代码可维护性，便于团队协作和项目扩展。

### II. Primitive-First Asset Strategy

**Rule**: 无美术资源场景下，所有视觉元素必须使用UE内置Primitive组件替代。

**Requirements**:
- 角色使用胶囊体+立方体+球体组合表示
- 武器使用简单几何体（立方体、圆柱体）表示
- 环境使用立方体构建墙壁、地板、障碍物
- 材质使用纯色设置，不依赖外部纹理资源

**Rationale**: 最小化外部依赖，专注于核心游戏玩法实现，降低开发门槛。

### III. Feature Priority Enforcement

**Rule**: 功能开发必须严格按照优先级顺序执行，禁止跳过基础功能。

**Priority Order**:
1. **移动系统** (P1): WASD移动、鼠标视角、跳跃、地面检测
2. **射击系统** (P2): 射线检测、伤害计算、弹药管理、射击反馈
3. **碰撞交互** (P3): 物理碰撞、物品拾取、生命值、死亡重生

**Requirements**:
- 每个优先级功能必须独立可测试
- 高优先级功能未完成前不得开始低优先级功能
- 功能完成后必须通过独立测试验证

**Rationale**: 确保MVP核心体验优先完成，避免功能蔓延导致项目延期。

### IV. C++/Blueprint Hybrid Architecture

**Rule**: 核心系统使用C++实现，可视化配置使用蓝图扩展。

**Requirements**:
- 角色控制器、武器系统、游戏模式使用C++实现
- UI界面、特效配置、关卡逻辑使用蓝图实现
- C++类必须暴露必要的蓝图可调用的属性和事件
- 禁止在蓝图中实现复杂业务逻辑

**Rationale**: 结合C++的性能优势和蓝图的灵活性，便于调试和迭代。

### V. Student-Friendly Documentation

**Rule**: 所有代码和文档必须面向大三计算机专业学生，兼顾专业性和易理解性。

**Requirements**:
- 代码注释解释UE5特有的概念（反射系统、组件架构等）
- 文档包含常见错误预防和调试技巧
- 提供学习路径建议，标注关键知识点
- 使用中文编写，术语保留英文便于对照学习

**Rationale**: 项目作为教学示例，需要帮助学生理解UE5开发模式和游戏编程概念。

## Development Constraints

### Technology Stack

**Required**:
- Unreal Engine 5.0+ (Windows平台)
- Visual Studio 2022 (C++开发)
- C++17标准

**Prohibited**:
- 外部美术资源依赖
- 第三方插件（除非必要且轻量）
- 复杂的网络同步功能

### Performance Standards

- 目标帧率: 60 FPS (Windows桌面)
- 内存使用: < 500MB
- 加载时间: < 10秒

### Code Quality Gates

- 所有C++代码必须通过编译无警告
- 蓝图变量必须命名规范、分类清晰
- 禁止硬编码数值，使用可配置参数

## Governance

**Authority**: 本Constitution是UE5 FPS Demo项目的最高指导文档，所有开发决策必须符合上述原则。

**Amendment Process**:
1. 任何原则修改需要文档化理由
2. 修改必须经过项目维护者批准
3. 版本号按语义化版本规范更新

**Compliance Verification**:
- 每个功能实现前检查Constitution符合性
- Code Review必须验证命名规范和架构原则
- 项目交付前进行Constitution合规性审查

**Version**: 1.0.0 | **Ratified**: 2026-03-02 | **Last Amended**: 2026-03-02
