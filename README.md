# Geant4 Homework

**Deadline: before 6.7**

### Note!!
* 命名规则与B1一致（方便编译）
* 缩进用tab（4个字符长度）
* 结合B1，B2a例子
* https://zhuanlan.zhihu.com/p/367469881
* GitHub Link: https://github.com/liaoyp0615/Geant4Homework
* GitHub ssh: ```git@github.com:liaoyp0615/Geant4Homework.git```
* Git batch:
    ```
    (option) rm -rf .git
    git init
    git remote add origin git@github.com:liaoyp0615/Geant4Homework.git
    git add *
    git commit -m "XXXX"
    git status
    git branch -m vXXX
    git branch
    git push origin vXXX
    ```


#
### main function
- [x] 修改physicsList

#
### Geometry
- [x] B1DetectorConstruction基本形状
- [x] logical volume 还需要再改一下材料，;脑子+脖子(G4_BRAIN_ICRP脑组织),body(G4_LUNG_ICRP肺组织),leg(G4_MUSCLE_SKELETAL_ICRP骨骼肌组织)
- [x] 头和脖子的重叠部分修改
- [x] ScoringVolume设置
- [x] 增加肿瘤的10^B的含量(10ug/g)


#
### Sensitive detector (SD) 未完成
- [ ] 肿瘤设置为灵敏探测器，写一个MySD的class，继承G4VSD
- [ ] 通过hit/score来记录剂量，写一个HitCollection的class
- [ ] (optional) 可以把其他躯干也设成SD


#
### Beam setting
- [x] 源粒子种类设置（中子），动量+位置
- [x] 源粒子物理过程，physics process设置 (QBBC)
- [x] 设置源-靶物质相互作用


#
### Run action
- [x] B1ActionInitialization调试
- [x] G4UserSteppingAction逻辑判断（是否在肿瘤里面）
- [x] stepping action里面设置score来判断存
- [x] G4Analysis创建，用来存信息的函数（用ROOT存），然后在G4UserSteppingAction实例化（问ChatGPT可以直接有写好的，告诉他存什么量然后它会自动转成root）


#
### Vis / Run
- [x] run.mac (设置beam和process等)
- [x] vis.mac (可视化设置)
- [x] batch mode. --- 不同粒子，不同能量


# 
### Work
* 假如使用某种靶向药物，使肿瘤区内的10B原子浓度达到100 ug/g，请优化中子束线能量，并再次与其它射线的治疗效果进行对比
* 利用源粒子和硼10反应，会放出alpha粒子，alpha粒子的自由程非常短，所以能量全部沉积在肿瘤区域，被癌细胞吸收，达到治疗的效果
* 可以先存成ROOT文件，然后用ROOT-C画图
* 需要画的图：
- [x] 0.5eV, 10eV, 10KeV, 1MeV, 50MeV的 x y z e 四个图 (100,000)
- [x] Body, Tumor, Head的辐射剂量比例 随 能量分布 (不同类型中子)（10,000）
- [x] 改成proton(10KeV, 1MeV, 50MeV)和gamma(10KeV, 1MeV, 50MeV)，画 x y z e 四个图 (100,000)，给出四个辐射剂量
- [x] 中子真实能量分布时的 x y z e 四个图 (100,000)
- [x] 剂量表

#
### 参考
* 中子束的能谱：中子能量范围为慢中子至超热中子（0.5eV~10keV）
    可以使用中子束注入：
* 辐射剂量分布情况：$D=\frac{dE}{dM}$, 1公斤物体质量吸收1焦耳的能量为1Gy
  人员剂量上限是 20mGy（这里忽略了不同粒子种类以及不同人体部位带来的权重差异）
* 能量沉积和径迹长度：慢中子至超热中子（0.5eV~10keV）（depth~8cm）
* (optional) 辐射生物学效应：Geant4-DNA模拟电离辐射和生物学结构导致的电离辐射损失[](https://)https://www.sciencedirect.com/science/article/pii/S1120179723000789
* 强子（质子和C_12）的放射疗法： Geant4 Simulations of Hadron Therapy and Refinement of User Interface
* 基于3.5+MeV射频四极质子加速器硼中子俘获治疗装置的束流整形体设计
