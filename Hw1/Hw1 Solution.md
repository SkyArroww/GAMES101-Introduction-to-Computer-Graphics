# Hw1

### 作业描述

给定三维空间下一个三角形，三个顶点分别为$v_0(2,0,-2),v_1(0,2,-2),v_2(-2,0,-2)$，把这三个点的坐标变换为屏幕坐标并绘制出对应三角形。

需要修改以下函数：

    1.***get_model_matrix(float rotation_angle)***:逐个元素地构建模型变换矩
	阵并返回该矩阵。在此函数中，你只需要实现三维中绕z轴旋转的变换矩阵，
	而不用处理平移与缩放。

    2.***get_projection_matrix(float eye_fov, float aspect_ratio, float
	zNear, float zFar)***:使用给定的参数逐个元素地构建透视投影矩阵并返回
	该矩阵。


[MVP变换](https://zhuanlan.zhihu.com/p/551648397)：

1. Model Transformation: 首先考虑 Model transformation，这取决于你想怎么放物体，如果保持不动那就是单位矩阵，想变换的话可以随意变换。例如我们可以把所有物体拉伸、所有物体平移等等。
2. View Transformation: 右手系中，规定相机朝向$z$轴负方向，正上方朝向$y$轴正方向。为了方便投影，我们把相机移到原点并调整为上述姿态，这个变换矩阵就是View Transformation。
3. [Projection Transformation](https://zhuanlan.zhihu.com/p/261097735): 分为正射投影和透视投影。

   1. 对于正射投影，假设我们照相机能看到$[l,r]\times[b,t]\times[f,n]$区域的物体，这样正射投影视体框定了一个空间区域。为了方便之后对应到屏幕空间坐标。我们需要把上述区域对应到$[-1,1]^3$这一空间内。不难得出要先scale再translation

      $$
      M_{ortho} = \left[
       \begin{matrix}
         \frac{2}{r-l} & 0 & 0 & 0\\
         0 & \frac{2}{t-b} & 0 & 0\\
         0 & 0 & \frac{2}{n-f} & 0\\
         0 & 0 & 0 & 1
        \end{matrix}
        \right] \left[
       \begin{matrix}
         1 & 0 & 0 & -\frac{r+l}{2}\\
         0 & 1 & 0 & -\frac{t+b}{2}\\
         0 & 0 & 1 & -\frac{n+f}{2}\\
         0 & 0 & 0 & 1
        \end{matrix}
        \right]
      $$

      2. 对于透视投影，我们想先把它变为上述的一个立方体区域，可推导得出
         $$
         M_{persp}=\left[
          \begin{matrix}
            n & 0 & 0 & 0\\
            0 & n & 0 & 0\\
            0 & 0 & n+f & -nf\\
            0 & 0 & 1 & 0
           \end{matrix}
           \right]
         $$


1. 三维空间绕$z$轴旋转$\theta$:


   $$
   \left[
    \begin{matrix}
      cos\theta & -sin\theta & 0 & 0\\
      sin\theta & cos\theta & 0 & 0\\
      0 & 0 & 1 & 0\\
      0 & 0 & 0 & 1
     \end{matrix}
     \right]
   $$
