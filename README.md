# CPU-Raymarching
![最终效果](./Documents/Raymarching.png)
基础的CPU-Raymarching的示例，在CPU端进行计算，使用GLUT库创建窗口和显示最终结果。场景使用距离场表示，从指定的相机位置发射射线进行Raymarching过程。

## Math (数学库)
数学库中封装了基础的数学运算方法，包括:
* MathUtility 基础数学函数
* Vector2f 二维向量
* Vector3f 三维向量
* Quaternion 四元数
* Matrix3x3 三阶方阵

## Image (图像库)
图像库中封装了存储颜色阵列的2D纹理类以及相关算法，包括：
* Color3f RGB颜色
* Texture2D 2D纹理

## Scene (场景库)
场景库中封装了场景绘制的相关类，包括：
* Ray 射线
* Light 光源，包含颜色和位置
* Camera 相机，包含位置和朝向
* Scene 场景，包含多个SDFObject
* SDFObject 场景距离场物体
  * SDFPlane 平面
  * SDFBox 盒子
  * SDFSphere 球
  * SDFUnion 联合，求出A物体和B物体合并的结果
  * SDFSubtract 相减，求出A物体扣掉B物体的部分
  * SDFIntersect 求交，求出A物体和B物体相交的部分
