# UltimateSkill
ue4 plugin demo of note (http://hulefei.github.io/2021/03/20/ue4-plugin-custom-asset/)

## UE4 右键添加菜单

### UE4 Plugin流程

1. IModuleInterface.StartupModule

模块入口

2. IAssetTools 

获取IAssetTools将IAssetTypeActions接口实现的类注册

```cpp
IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
```

3. IAssetTypeActions

* 将IAssetTypeActions接口实现的类注册入IAssetTools

```cpp
RegisterAssetTypeAction(AssetTools, MakeShareable(new FUltimateSkillAssetActions()));
```

* 将IAssetTypeActions接口从IAssetTools中注销

```cpp
AssetTools.UnregisterAssetTypeActions(Action);
```

4. ShutdownModule

模块结束

### 核心类

#### FAssetTypeActions_Base

1. 继承于 [IAssetTypeActions](https://docs.unrealengine.com/en-US/API/Developer/AssetTools/IAssetTypeActions/index.html)(提供asset支持的action和信息)
2. 提供IAssetTypeActions接口的默认实现

#### UFactory

1. 提供创建和导入新资源的方法
2. 有默认实现

### 自定义类

#### FUltimateSkillAssetActions

1. 继承 FAssetTypeActions_Base
2. 实现方法

```cpp
//右键item的分类
virtual uint32 GetCategories() override;
//item 名字
virtual FText GetName() const override;
//右键创建的在内存中创建的资源类类型
virtual UClass* GetSupportedClass() const override;
//资源的颜色
virtual FColor GetTypeColor() const override;
/*
 * 	点击item的调用
 *	@param InObjects 选中的对象，因为可以同时选择多个资源，所以是数组,使用GetTypedWeakObjectPtrs<UUltimateSkillAsset>转换资源
 *	@param MenuBuilder 构建menu，将item添加的到menu中
 */

virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
//是否显示item
virtual bool HasActions(const TArray<UObject*>& InObjects) const override;
```



3. 创建的Asset一直在内存中，直到点击Content后，资源才会使用UFactory序列换到本地

#### UUltimateSkillFactoryNew

1. 继承 UFactory
2. 在点击Content后，序列号内存中定义的资源


